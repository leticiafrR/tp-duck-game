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
    model/weapon/instant/InstantWeapon.cpp

    model/weapon/instant/PistolaCowboy.cpp
    model/weapon/instant/DuelingPistol.cpp
    model/weapon/instant/LaserRifle.cpp
    model/weapon/instant/PewPewLaser.cpp
    model/weapon/instant/Shotgun.cpp

    model/projectile/ProjectilesController.cpp
    model/projectile/InstantProjectile.cpp
    model/projectile/BounceInstantProjectile.cpp

    model/collectable/CollectableWrapper.cpp
    model/collectable/CollectableSpawner.cpp
    model/collectable/Collectables.cpp
    model/collectable/CollectablesSpawner.cpp
    model/collectable/CollectablesController.cpp

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
    model/collectable/CollectablesController.h
    # model/collectable/Protection.h
    model/collectable/Collectable.h
    model/weapon/Weapon.h
    model/weapon/instant/InstantWeapon.h
    model/weapon/instant/PistolaCowboy.h
    model/weapon/instant/DuelingPistol.h
    model/weapon/instant/LaserRifle.h
    model/weapon/instant/PewPewLaser.h
    model/weapon/instant/Shotgun.h

    model/projectile/InstantProjectile.h
    model/projectile/Projectile.h
    model/projectile/ProjectilesController.h
    model/projectile/BounceInstantProjectile.h

    model/collectable/CollectableWrapper.h
    model/collectable/Collectable.h
    model/collectable/CollectableSpawner.h
    model/collectable/Collectables.h
    model/collectable/CollectablesSpawner.h
    model/collectable/CollectablesController.h
    model/collectable/Armor.h
    model/collectable/Helmet.h

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
