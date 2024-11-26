#ifndef COLLECTABLES_CONTROLLER_H
#define COLLECTABLES_CONTROLLER_H

#include <algorithm>
#include <vector>

#include "server/config.h"
#include "server/model/projectile/ProjectilesController.h"
#include "server/model/weapon/instant/PewPewLaser.h"

#include "Collectable.h"
class Transform;

class CollectablesController {
private:
    std::vector<Vector2D> weaponSpawnPoints;
    ProjectilesController& projectilesController;
    // std::vector<Collectable*> collectables;
    Collectable* unicCollectable;
    const Config& conf;
    // CreateWeapons(const std::vector<Vector2D>& weaponsSpawnPoints, Config& conf){
    //     for (auto& point: weaponSpawnPoints) {
    //         //PewPewLaser* weapon = new PewPewLaser(projectilesController,
    //         Transform(point,Vector2D(conf)),conf); collectables.push_back(weapon);
    //     }
    // }
public:
    // explicit CollectablesController(ProjectilesController&
    // projectilesController,std::vector<Vector2D> weaponSpawnPoints ):
    //         projectilesController(projectilesController), unicCollectable(new
    //         PewPewLaser(projectilesController,Transform())){}
    explicit CollectablesController(ProjectilesController& projectilesController,
                                    const Config& conf,
                                    const std::vector<Vector2D>& weaponSpawnPoints);
    void ReleasePewPew();


    void SayHello();


    // CollectablesController(ProjectilesController& projectilesController,const
    // std::vector<Vector2D>& weaponsSpawnPoints):projectilesController(projectilesController){
    //     CreateWeapons(weaponsSpawnPoints);
    // }

    Collectable* PickCollectable(const Transform& collectorSpace,
                                 TypeCollectable& collectorTyperRef);
    void Drop(Collectable* obj, const Vector2D& position);
    // /*void Respawn(); faltante*/
    ~CollectablesController();
};


#endif
