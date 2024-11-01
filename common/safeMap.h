#ifndef SAFE_MAP_H_
#define SAFE_MAP_H_

#include <climits>
#include <functional>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <stdexcept>
#include <vector>

/* This is an implementation of a map that can be acced concurrently, the operations of
 * reading/writing are mutually exclusive and atomic*/
template <typename K, typename V>
class SafeMap {
private:
    std::map<K, V> map;
    const unsigned int max_size;
    // mutex sharable to allow concurrent read operations , but still maaking the write operations
    // mutually exclusive of itself and the rest of operations.
    mutable std::shared_mutex rw_mtx;

public:
    explicit SafeMap(unsigned int max_size): max_size(max_size) {}

    /* Add an element in a non-blocking way; does not overwrites the value if the key already
     * exists, in that cse also returns false.*/
    bool tryInsert(const K& key, const V& value) {
        // Exclusive lock for write operation
        std::unique_lock<std::shared_mutex> lck(rw_mtx);
        if (map.size() == max_size || map.find(key) != map.end()) {
            // if the map was fulled or if the key already was in the mp returns false
            return false;
        }
        map[key] = value;
        return true;
    }

    /* Removes an element in a non-blocking way; returns true if it existed and was deleted.*/
    bool tryErase(const K& key) {
        // Exclusive lock for write operation
        std::unique_lock<std::shared_mutex> lck(rw_mtx);
        auto it = map.find(key);
        if (it == map.end()) {
            return false;
        }
        map.erase(it);
        return true;
    }

    /* Method to obtain the value associated with a key in a thread-safe manner, returning a booelan
     * that indicates whether the value was obtained and left in the received reference (true) or if
     * the value was not obtained (false)*/
    bool get(const K& key, V& value) const {
        // Shared lock for read operation
        std::shared_lock<std::shared_mutex> lck(rw_mtx);
        auto it = map.find(key);
        if (it == map.end()) {
            return false;
        }

        value = it->second;
        return true;
    }

    /* Method to obtain a vector with all the keys in the map */
    /* OJO: Implemento metodo para obtener un container con las claves, esto porque creo que luego
     * de que un game termine y la logica del game solo tenga el id de un client, el ganador, se
     * necesitarà instanciar una nueva ronda/game con los id que se guardaron aquì*/
    std::vector<K> getKeys() const {
        // Shared lock for read operation
        std::unique_lock<std::shared_mutex> lck(rw_mtx);
        std::vector<K> keys;
        keys.reserve(map.size());

        for (const auto& pair: map) {
            // cppcheck-suppress useStlAlgorithm
            keys.push_back(pair.first);
        }

        return keys;
    }

    void clear() {
        std::unique_lock<std::mutex> lck(rw_mtx);
        map.clear();
    }

    void applyToItems(const std::function<void(K&, V&)>& func) {
        std::unique_lock<std::shared_mutex> lck(rw_mtx);
        for (auto& [key, value]: map) {
            func(key, value);
        }
    }

    int size() {
        std::shared_lock<std::shared_mutex> lck(rw_mtx);
        int n = map.size();
        return n;
    }

private:
    SafeMap(const SafeMap&) = delete;
    SafeMap& operator=(const SafeMap&) = delete;
};


#endif
