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

    model/weapon/InstantWeapon.cpp
    model/weapon/PistolaCowboy.cpp
    model/weapon/DuelingPistol.cpp
    model/weapon/LaserRifle.cpp
    model/weapon/PewPewLaser.cpp
    model/weapon/Shotgun.cpp

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
    model/throwable/Grenade.cpp
    model/throwable/ThrowablesController.cpp
    model/throwable/creator/GrenadeCreator.cpp
    model/throwable/creator/ThrowableCreator.cpp

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
    

    model/weapon/InstantWeapon.h
    model/weapon/PistolaCowboy.h
    model/weapon/DuelingPistol.h
    model/weapon/LaserRifle.h
    model/weapon/PewPewLaser.h
    model/weapon/Shotgun.h

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


    model/throwable/creator/GrenadeCreator.h
    model/throwable/creator/ThrowableCreator.h

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
