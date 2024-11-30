target_sources(taller_server
    PRIVATE
    # .cpp files
    config.cpp

    model/event/CollectableEventListener.cpp
    model/event/EventsManager.cpp
    model/event/InstantProjectileEventListener.cpp
    model/event/PlayerEventListener.cpp

    model/DynamicObj.cpp
    model/Duck.cpp
    model/Game.cpp
    model/map/staticMap.cpp

    model/weapon/Weapon.cpp
    model/weapon/instantCreator/InstantWeapon.cpp
    model/weapon/instantCreator/PistolaCowboy.cpp
    model/weapon/instantCreator/DuelingPistol.cpp
    model/weapon/instantCreator/LaserRifle.cpp
    model/weapon/instantCreator/PewPewLaser.cpp
    model/weapon/instantCreator/Shotgun.cpp

    model/projectile/Projectile.cpp
    model/projectile/ProjectilesController.cpp
    model/projectile/instant/InstantProjectilesController.cpp
    model/projectile/instant/InstantProjectile.cpp
    model/projectile/instant/BounceInstantProjectile.cpp

    model/collectable/Collectable.cpp
    model/collectable/CollectableWrapper.cpp
    model/collectable/CollectableSpawner.cpp
    model/collectable/Collectables.cpp
    model/collectable/CollectablesSpawner.cpp
    model/collectable/CollectablesController.cpp



    model/throwable/Throwable.cpp

    model/weapon/throwableCreator/ThrowableCreator.cpp

    #network
    network/sender.cpp
    network/receiver.cpp
    network/serverProtocol.cpp
    network/messageSender.cpp
    network/acceptor.cpp
    
    gamesHandler.cpp
    match.cpp
    matchesMonitor.cpp
    server.cpp
    
    main.cpp

    PUBLIC
    # .h files
    config.h
    model/types.h
    model/map/staticMap.h
    model/MotionHandler.h
    model/DynamicObj.h
    model/Duck.h
    model/Game.h

    model/event/CollectableEventListener.h
    model/event/EventsManager.h
    model/event/InstantProjectileEventListener.h
    model/event/PlayerEventListener.h
    
    model/Equipment.h
    
    model/weapon/Weapon.h
    model/weapon/instantCreator/InstantWeapon.h
    model/weapon/instantCreator/PistolaCowboy.h
    model/weapon/instantCreator/DuelingPistol.h
    model/weapon/instantCreator/LaserRifle.h
    model/weapon/instantCreator/PewPewLaser.h
    model/weapon/instantCreator/Shotgun.h

    model/projectile/instant/InstantProjectile.h
    model/projectile/instant/BounceInstantProjectile.h
    model/projectile/instant/InstantProjectilesController.h
    model/projectile/Projectile.h
    model/projectile/ProjectilesController.h
    
    

    model/collectable/CollectableWrapper.h
    model/collectable/Collectable.h
    model/collectable/CollectableSpawner.h
    model/collectable/Collectables.h
    model/collectable/CollectablesSpawner.h
    model/collectable/CollectablesController.h
    model/collectable/Armor.h
    model/collectable/Helmet.h



    model/throwable/Throwable.h
    model/throwable/Grenade.h
    model/throwable/ThrowablesController.h

    model/weapon/throwableCreator/ThrowableCreator.h
    model/weapon/throwableCreator/GrenadeCreator.h

    network/serverProtocol.h
    network/messageSender.h
    network/sender.h
    network/receiver.h
    network/acceptor.h

    config.h
    gamesHandler.h
    match.h
    matchesMonitor.h
    matchStatus.h
    clientInfo.h
    server.h
    )
