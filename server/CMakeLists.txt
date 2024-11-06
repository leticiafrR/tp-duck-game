target_sources(taller_server
    PRIVATE
    # .cpp files
    acceptor.cpp
    handlerGames.cpp
    main.cpp
    match.cpp
    messageSender.cpp
    receiver.cpp
    sender.cpp
    serverProtocol.cpp

    PUBLIC
    # .h files
    model/gameWorld.h
    model/types.h
    acceptor.h
    config.h
    handlerGames.h
    match.h
    messageSender.h
    receiver.h
    sender.h
    serverProtocol.h
    )
