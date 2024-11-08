target_sources(taller_client
    PRIVATE
    # .cpp files
    Object2D.cpp
    Button.cpp
    Camera.cpp
    main.cpp
    clientProtocol.cpp
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
    )
