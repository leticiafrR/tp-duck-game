target_sources(taller_client
    PRIVATE
    # .cpp files
    GraphicUI.cpp
    tweening/Tween.cpp
    Object2D.cpp
    Button.cpp
    Camera.cpp
    main.cpp
    #mainNetwork.cpp
    

    # receiver.cpp
    # sender.cpp
    network/ClientProtocol.cpp
    # client.cpp
    PUBLIC
    # .h files
    GraphicUI.h
    Object2D.h
    Camera.h
    CameraController.h
    Animator.h
    TextureCache.h
    MapBlock2D.h
    SheetDataCache.h
    ColorExtension.h
    Image.h
    Text.h
    Button.h
    ButtonsManager.h

    # DataMatch.h
    # round.h
    # dataReceive.h
    # receiver.h
    # sender.h
    network/ClientProtocol.h
    network/Client.h
    network/Receiver.h
    network/Sender.h
    )
