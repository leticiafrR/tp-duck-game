target_sources(taller_editor
    PRIVATE
    # .cpp files
   
    editWorld/mapEditor.cpp
    MenuScreen.cpp
    editLevel/LevelsScreen.cpp
    editLevel/LevelWidget.cpp
    createLevel/setLevelName.cpp
    EditorRunner.cpp
    editWorld/PlatformOptionWidget.cpp
    editWorld/EditorScreen.cpp
    editWorld/SpawnPointWidget.cpp
    ExitOptions.cpp
    selectTheme/themesScreen.cpp 
    selectTheme/themeWidget.cpp 
    main.cpp
    PUBLIC
    # .h files
    editWorld/mapEditor.h
    editLevel/LevelsScreen.h
    MenuScreen.h
    editLevel/LevelWidget.h
    createLevel/setLevelName.h 
    EditorRunner.h
    editWorld/PlatformOptionWidget.h
    editWorld/EditorScreen.h
    editWorld/SpawnPointWidget.h
    ExitOptions.h
    selectTheme/themesScreen.h
    selectTheme/themeWidget.h
    )
