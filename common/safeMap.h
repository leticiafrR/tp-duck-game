#ifndef SAFE_MAP_H_
#define SAFE_MAP_H_

#include <climits>
#include <map>
#include <mutex>
#include <stdexcept>

/* This is an implementation of a map that can be acced concurrently, the operations of
 * reading/writing are mutually exclusive and atomic*/
template <typename K, typename V>
class SafeMap {
private:
    std::map<K, V> map;
    const unsigned int max_size;

    std::mutex mtx;

public:
    explicit SafeMap(unsigned int max_size): max_size(max_size) {}

    /* Add an element in a non-blocking way; does not overwrites the value if the key already
     * exists, in that cse also returns false.*/
    bool tryInsert(const K& key, const V& value) {
        std::unique_lock<std::mutex> lck(mtx);
        if (map.size() == max_size || map.find(key) != map.end()) {
            // if the map was fulled or if the key already was in the mp returns false
            return false;
        }
        map[key] = value;
        return true;
    }

    /* Removes an element in a non-blocking way; returns true if it existed and was deleted.*/
    bool tryErase(const K& key) {
        std::unique_lock<std::mutex> lck(mtx);

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
        std::unique_lock<std::mutex> lck(mtx);

        auto it = map.find(key);
        if (it == map.end()) {
            return false;
        }

        value = it->second;
        return true;
    }

private:
    SafeMap(const SafeMap&) = delete;
    SafeMap& operator=(const SafeMap&) = delete;
};

// OJO: Tambien me gustaria que se pueda obtener la losta de claves para poder (luego de que un game
// termine y soo contenga a un id de un client) instanciar una nueva ronda/game con los ids que se
// guardaron aquì

#endif
