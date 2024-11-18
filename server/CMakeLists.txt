target_sources(taller_server
    PRIVATE
    # .cpp files
    model/event/InstantProjectileEventListener.cpp
    model/event/PlayerEventListener.cpp
    model/event/EventsManager.cpp
    model/DynamicObj.cpp
    model/Duck.cpp
    model/Game.cpp
    model/map/staticMap.cpp

    #network
    network/sender.cpp
    network/receiver.cpp
    network/serverProtocol.cpp
    network/messageSender.cpp

    acceptor.cpp
    gamesHandler.cpp
    match.cpp
    matchesMonitor.cpp
    
    main.cpp

    PUBLIC
    # .h files
    model/types.h
    model/map/staticMap.h
    model/MotionHandler.h
    model/map/mapConstants.h
    model/DynamicObj.h
    model/Duck.h
    model/Game.h
    model/event/EventsManager.h
    model/event/PlayerEventListener.h
    model/event/InstantProjectileEventListener.h
    # model/Equipment.h
    # model/collectable/CollectablesController.h
    # model/collectable/Protection.h
    # model/collectable/Collectable.h
    model/weapon/Weapon.h
    model/weapon/InstantWeapon.h
    model/weapon/instant/PistolaCowboy.h
    model/projectile/InstantProjectile.h
    model/projectile/Projectile.h
    model/projectile/ProjectilesController.h

    network/serverProtocol.h
    network/messageSender.h
    network/sender.h
    network/receiver.h
    network/matchBinder.h
    config.h
    gamesHandler.h
    match.h
    matchesMonitor.h
    matchStatus.h
    playerInfo.h
    acceptor.h

    )
