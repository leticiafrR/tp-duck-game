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

    model/weaponCollectable/Weapon.cpp
    model/weaponCollectable/PistolaCowboy.cpp
    model/weaponCollectable/DuelingPistol.cpp
    model/weaponCollectable/LaserRifle.cpp
    model/weaponCollectable/PewPewLaser.cpp
    model/weaponCollectable/Shotgun.cpp

    model/projectile/Projectile.cpp
    model/projectile/ProjectilesController.cpp
    model/projectile/instant/InstantProjectilesController.cpp
    model/projectile/instant/InstantProjectile.cpp
    model/projectile/instant/BounceInstantProjectile.cpp

    
    model/collectable/spawning/CollectableWrapper.cpp
    model/collectable/spawning/CollectableSpawner.cpp
    model/collectable/spawning/Collectables.cpp
    model/collectable/CollectablesController.cpp
    model/collectable/Collectable.cpp



    model/throwable/Throwable.cpp
    model/throwable/Grenade.cpp
    model/throwable/ThrowablesController.cpp

    model/throwableCollectable/GrenadeCollectable.cpp
    model/throwableCollectable/ThrowableCollectable.cpp


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
    

    model/weaponCollectable/Weapon.h
    model/weaponCollectable/PistolaCowboy.h
    model/weaponCollectable/DuelingPistol.h
    model/weaponCollectable/LaserRifle.h
    model/weaponCollectable/PewPewLaser.h
    model/weaponCollectable/Shotgun.h

    model/projectile/instant/InstantProjectile.h
    model/projectile/instant/BounceInstantProjectile.h
    model/projectile/instant/InstantProjectilesController.h
    model/projectile/Projectile.h
    model/projectile/ProjectilesController.h
    

    model/collectable/spawning/CollectableWrapper.h
    model/collectable/spawning/CollectableSpawner.h
    model/collectable/spawning/Collectables.h
    model/collectable/CollectablesController.h
    model/collectable/Collectable.h
    model/collectable/Armor.h
    model/collectable/Helmet.h



    model/throwable/Throwable.h
    model/throwable/Grenade.h
    model/throwable/ThrowablesController.h


    model/throwableCollectable/GrenadeCollectable.h
    model/throwableCollectable/ThrowableCollectable.h

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
