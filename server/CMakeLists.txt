target_sources(taller_server
    PRIVATE
    # .cpp files
    serverProtocol.cpp
    messageSender.cpp
    model/event/PlayerEventListener.cpp
    model/event/EventsManager.cpp
    model/map/staticMap.cpp
    model/DynamicObj.cpp
    model/Duck.cpp
    model/Game.cpp
    handlerGames.cpp
    main.cpp
    PUBLIC
    # .h files
    model/types.h
    model/map/staticObject.h
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
    )
