target_sources(taller_client
    PRIVATE
    # .cpp files
    tweening/ImageTween.cpp
    tweening/TransformTween.cpp
    tweening/Tween.cpp
    tweening/TweenManager.cpp

    utils/Timer.cpp
    utils/Animator.cpp
    utils/TransformFollow.cpp

    gameplay/CameraController.cpp
    gameplay/Gameplay.cpp
    gameplay/GameplayGUI.cpp

    rendering/SpriteRendererData.cpp
    rendering/DuckClientRenderer.cpp
    rendering/BulletRenderer.cpp
    rendering/CollectableRenderer.cpp
    rendering/HandItemRenderer.cpp
    rendering/ChestplateRenderer.cpp
    rendering/HelmetRenderer.cpp

    screens/BaseScreen.cpp
    screens/MenuScreen.cpp
    screens/LoadingScreen.cpp
    screens/MatchListScreen.cpp
    screens/LobbyScreen.cpp
    screens/LobbyItemWidget.cpp
    screens/ControlsScreen.cpp
    screens/GameStatusScreen.cpp
    screens/PlayersCountSelection.cpp
    screens/ShowColorsScreen.cpp

    ClientRunner.cpp
    main.cpp

    network/ClientProtocol.cpp

    PUBLIC
    # .h files
    Framework.h

    tweening/ImageTween.h
    tweening/TransformTween.h
    tweening/Tween.h
    tweening/TweenManager.h

    utils/Timer.h
    utils/Animator.h
    utils/TransformFollow.h

    gameplay/CameraController.h
    gameplay/Gameplay.h
    gameplay/GameplayGUI.h

    screens/BaseScreen.h
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
    rendering/ChestplateRenderer.h
    rendering/HelmetRenderer.h

    ClientRunner.h

    network/ClientProtocol.h
    network/Client.h
    network/Receiver.h
    network/Sender.h
    )
