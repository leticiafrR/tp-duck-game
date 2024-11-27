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

    utils/SDLExtension.h
    utils/Timer.h

    gameplay/CameraController.h
    gameplay/Animator.h
    gameplay/Gameplay.h
    gameplay/GameplayGUI.h

    screens/MenuScreen.h
    screens/LoadingScreen.h
    screens/MatchListScreen.h
    screens/LobbyScreen.h
    screens/LobbyItemWidget.h
    screens/ControlsScreen.h
    screens/GameStatusScreen.h
    screens/PlayersCountSelection.h
    screens/ShowColorsScreen.h

    rendering/SpriteRendererData.h
    rendering/DuckClientRenderer.h
    rendering/BulletRenderer.h
    rendering/CollectableRenderer.h
    rendering/HandItemRenderer.h

    ClientRunner.h

    network/ClientProtocol.h
    network/Client.h
    network/Receiver.h
    network/Sender.h
    )
