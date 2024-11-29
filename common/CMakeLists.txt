target_sources(taller_common
    PRIVATE
    # .cpp files
    liberror.cpp
    resolver.cpp
    resolvererror.cpp
    socket.cpp
    protocolAssistant.cpp

    Vector2D.cpp
    Collision.cpp
    Transform.cpp
    RigidBody.cpp

    PUBLIC
    # .h files
    liberror.h
    resolver.h
    resolvererror.h
    socket.h
    queue.h
    thread.h
    safeMap.h
    timeManager.h
    protocolAssistant.h
    playerIdentifier.h

    Vector2D.h
    Collision.h
    Transform.h
    RigidBody.h
    )
