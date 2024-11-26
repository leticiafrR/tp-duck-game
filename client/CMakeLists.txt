target_sources(taller_client
    PRIVATE
    # .cpp files
    tweening/Tween.cpp
    main.cpp
    network/ClientProtocol.cpp

    PUBLIC
    # .h files
    tweening/ImageTween.h
    tweening/TransformTween.h
    tweening/Tween.h
    tweening/TweenManager.h
    SDLExtension.h
    Timer.h
    CameraController.h
    Animator.h
    MenuScreen.h
    LoadingScreen.h
    MatchListScreen.h
    LobbyScreen.h
    LobbyItemWidget.h
    Gameplay.h
    ClientRunner.h
    ShowColorsScreen.h
    DuckClientRenderer.h

    network/ClientProtocol.h
    network/Client.h
    network/Receiver.h
    network/Sender.h
    )
