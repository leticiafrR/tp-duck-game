target_sources(taller_server
    PRIVATE
    # .cpp files
    config.cpp
    model/MotionHandler.cpp
    model/Equipment.cpp

    model/event/CollectableEventListener.cpp
    model/event/EventsManager.cpp
    model/event/ProjectileEventListener.cpp
    model/event/PlayerEventListener.cpp
    model/event/ThrowableEventListener.cpp
    model/event/BoxEventListener.cpp

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
    model/weaponCollectable/AK47.cpp
    model/weaponCollectable/Magnum.cpp

    model/projectile/ProjectilesController.cpp
    model/projectile/Projectile.cpp
    model/projectile/BounceProjectile.cpp

    
    model/collectable/spawning/CollectableWrapper.cpp
    model/collectable/spawning/CollectableSpawner.cpp
    model/collectable/spawning/Collectables.cpp
    model/collectable/CollectablesController.cpp
    model/collectable/Collectable.cpp
    model/collectable/Armor.cpp
    model/collectable/Helmet.cpp



    model/throwable/Throwable.cpp
    model/throwable/Grenade.cpp
    model/throwable/Banana.cpp
    model/throwable/ThrowablesController.cpp

    model/throwableCollectable/BananaCollectable.cpp
    model/throwableCollectable/GrenadeCollectable.cpp

    model/box/BoxesController.cpp
    model/box/Box.cpp

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
    model/map/staticMap.h
    model/MotionHandler.h
    model/DynamicObj.h
    model/Duck.h
    model/Game.h

    model/event/CollectableEventListener.h
    model/event/EventsManager.h
    model/event/ProjectileEventListener.h
    model/event/PlayerEventListener.h
    model/event/ThrowableEventListener.h
    model/event/BoxEventListener.h
    
    model/Equipment.h

    model/weaponCollectable/Weapon.h
    model/weaponCollectable/PistolaCowboy.h
    model/weaponCollectable/DuelingPistol.h
    model/weaponCollectable/LaserRifle.h
    model/weaponCollectable/PewPewLaser.h
    model/weaponCollectable/Shotgun.h
    model/weaponCollectable/AK47.h
    model/weaponCollectable/Magnum.h

    model/projectile/ProjectilesController.h
    model/projectile/Projectile.h
    model/projectile/BounceProjectile.h
    

    model/collectable/spawning/CollectableWrapper.h
    model/collectable/spawning/CollectableSpawner.h
    model/collectable/spawning/Collectables.h
    model/collectable/CollectablesController.h
    model/collectable/Collectable.h
    model/collectable/Armor.h
    model/collectable/Helmet.h



    model/throwable/Throwable.h
    model/throwable/Grenade.h
    model/throwable/Banana.h
    model/throwable/ThrowablesController.h

    model/throwableCollectable/BananaCollectable.h
    model/throwableCollectable/GrenadeCollectable.h
    model/throwableCollectable/ThrowableCollectable.h


    model/box/BoxesController.h
    model/box/Box.h

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
