target_sources(taller_server
    PRIVATE
    # .cpp files
    model/event/PlayerEventListener.cpp
    model/event/EventsManager.cpp
    model/DynamicObj.cpp
    model/Duck.cpp
    model/Game.cpp
    gamesHandler.cpp
    match.cpp
    model/map/staticMap.cpp
    #communications
    network/sender.cpp
    network/receiver.cpp
    network/serverProtocol.cpp
    network/messageSender.cpp
    acceptor.cpp
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
    # model/Equipment.h
    # model/collectable/CollectablesController.h
    # model/collectable/Weapon.h
    # model/collectable/Protection.h
    # model/collectable/Collectable.h

    network/serverProtocol.h
    network/messageSender.h
    network/sender.h
    network/receiver.h
    config.h
    gamesHandler.h
    match.h
    acceptor.h

    )
