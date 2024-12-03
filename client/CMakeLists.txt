target_sources(taller_client
    PRIVATE
    # .cpp files
    tweening/ImageTween.cpp
    tweening/TransformTween.cpp
    tweening/Tween.cpp

    utils/Timer.cpp
    utils/Animator.cpp
    utils/TransformFollow.cpp

    game/ClientControls.cpp
    game/CameraController.cpp
    game/GameScreen.cpp
    game/GameGUI.cpp
    game/ShowColorsPanel.cpp

    game/player/DuckPlayer.cpp
    game/player/HandItem.cpp
    game/player/Armor.cpp
    game/player/Helmet.cpp
    game/items/Projectile.cpp
    game/items/Collectable.cpp
    game/items/Throwable.cpp
    game/controllers/ThrowablesController.cpp
    game/controllers/CollectablesController.cpp
    game/controllers/ProjectilesController.cpp
    game/controllers/BoxesController.cpp
    game/controllers/PlayersController.cpp

    menus/MenuScreen.cpp
    menus/LoadingScreen.cpp
    menus/LobbiesListScreen.cpp
    menus/LobbyScreen.cpp
    menus/LobbyItemWidget.cpp
    menus/ControlsPanel.cpp
    menus/GameStatusScreen.cpp
    menus/PlayersCountSelectionPanel.cpp

    ClientRunner.cpp
    main.cpp

    network/ClientProtocol.cpp
    network/Receiver.cpp
    network/Sender.cpp

    PUBLIC
    # .h files
    Framework.h
    FrameworkUI.h

    tweening/ImageTween.h
    tweening/TransformTween.h
    tweening/Tween.h

    utils/Timer.h
    utils/Animator.h
    utils/TransformFollow.h

    game/ClientControls.h
    game/CameraController.h
    game/GameScreen.h
    game/GameGUI.h
    game/ShowColorsPanel.h

    menus/MenuScreen.h
    menus/LoadingScreen.h
    menus/LobbiesListScreen.h
    menus/LobbyScreen.h
    menus/LobbyItemWidget.h
    menus/ControlsPanel.h
    menus/GameStatusScreen.h
    menus/PlayersCountSelectionPanel.h

    game/player/DuckPlayer.h
    game/player/HandItem.h
    game/player/Armor.h
    game/player/Helmet.h
    game/items/Projectile.h
    game/items/Collectable.h
    game/items/Throwable.h
    game/controllers/ThrowablesController.h
    game/controllers/CollectablesController.h
    game/controllers/ProjectilesController.h
    game/controllers/BoxesController.h
    game/controllers/PlayersController.h
    game/controllers/Controllers.h

    ClientRunner.h

    network/ClientProtocol.h
    network/Client.h
    network/Receiver.h
    network/Sender.h
    )
