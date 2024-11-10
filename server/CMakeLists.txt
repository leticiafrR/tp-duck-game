target_sources(taller_server
    PRIVATE
    # .cpp files
    serverProtocol.cpp
    messageSender.cpp
    model/event/PlayerEventListener.cpp
    model/event/EventsManager.cpp
    model/DynamicObj.cpp
    model/Duck.cpp
    model/Game.cpp
    handlerGames.cpp
    match.cpp
    model/map/staticMap.cpp
    #the part of the communications
    sender.cpp
    receiver.cpp
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
    serverProtocol.h
    messageSender.h
    config.h
    handlerGames.h
    match.h
    sender.h
    receiver.h
    acceptor.h

    )
