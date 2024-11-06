target_sources(taller_common
    PRIVATE
    # .cpp files
    liberror.cpp
    protocolAssistant.cpp
    resolver.cpp
    resolvererror.cpp
    socket.cpp
    PUBLIC
    # .h files
    liberror.h
    resolver.h
    resolvererror.h
    socket.h
    queue.h
    thread.h
    Vector2D.h
    Transform.h
    protocolAssistant.h
    safeMap.h
    timeManager.h
    )
