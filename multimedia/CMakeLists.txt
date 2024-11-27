target_sources(taller_multimedia
    PRIVATE
    # .cpp files
    Camera.cpp
    Rate.cpp
    KeyboardExtension.cpp
    ColorExtension.cpp

    2d/Object2D.cpp
    2d/MapBlock2D.cpp

    audio/AudioManager.cpp
    
    gui/RectTransform.cpp
    gui/GraphicUI.cpp
    gui/Text.cpp
    gui/Image.cpp
    gui/Button.cpp
    gui/GUIManager.cpp
    gui/ButtonsManager.cpp

    cache/TextureCache.cpp
    cache/AudioCache.cpp
    cache/FontCache.cpp
    cache/SheetDataCache.cpp

    PUBLIC
    # .h files
    Camera.h
    Rate.h
    Definitions.h
    KeyboardExtension.h
    ColorExtension.h
    
    2d/Object2D.h
    2d/MapBlock2D.h
    
    audio/AudioManager.h
    
    gui/RectTransform.h
    gui/GraphicUI.h
    gui/Text.h
    gui/Image.h
    gui/Button.h
    gui/GUIManager.h
    gui/ButtonsManager.h

    cache/TextureCache.h
    cache/AudioCache.h
    cache/FontCache.h
    cache/SheetDataCache.h
    )
