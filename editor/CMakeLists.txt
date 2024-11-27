target_sources(taller_editor
    PRIVATE
    # .cpp files
    main.cpp
    mapEditor.cpp
    MenuScreen.cpp
    editLevel/LevelsScreen.cpp
    editLevel/LevelWidget.cpp
    createLevel/setLevelName.cpp
    EditorRunner.cpp
    PUBLIC
    # .h files
    mapEditor.h
    editLevel/LevelsScreen.h
    MenuScreen.h
    editLevel/LevelWidget.h
    createLevel/setLevelName.h 
    EditorRunner.h
    )
