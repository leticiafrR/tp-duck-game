target_sources(taller_editor
    PRIVATE
    # .cpp files
   
    mapEditor.cpp
    MenuScreen.cpp
    editLevel/LevelsScreen.cpp
    editLevel/LevelWidget.cpp
    createLevel/setLevelName.cpp
    EditorRunner.cpp
    PlatformOptionWidget.cpp
    EditorScreen.cpp
    editWorld/GameWorld.cpp
    SpawnPointWidget.cpp
     main.cpp
    PUBLIC
    # .h files
    mapEditor.h
    editLevel/LevelsScreen.h
    MenuScreen.h
    editLevel/LevelWidget.h
    createLevel/setLevelName.h 
    EditorRunner.h
    PlatformOptionWidget.h
    EditorScreen.h
    editWorld/GameWorld.h
    SpawnPointWidget.h
    )
