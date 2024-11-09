target_sources(taller_client
    PRIVATE
    # .cpp files
    Object2D.cpp
    Button.cpp
    Camera.cpp
    main.cpp

    receiver.cpp
    sender.cpp
    clientProtocol.cpp
    client.cpp
    PUBLIC
    # .h files
    Object2D.h
    Camera.h
    CameraController.h
    Animator.h
    TextureCache.h
    MapBlock2D.h
    SheetDataCache.h
    ColorExtension.h
    Button.h
    ButtonsManager.h

    DataMatch.h
    round.h
    dataReceive.h
    receiver.h
    sender.h
    clientProtocol.h
    client.h
    )
