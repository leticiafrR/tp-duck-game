target_sources(taller_multimedia
    PRIVATE
    # .cpp files
    Camera.cpp
    Rate.cpp
    KeyboardExtension.cpp
    ColorExtension.cpp

    2d/Object2D.cpp
    2d/MapBlock2D.cpp
    2d/MapBlockRenderData.cpp

    audio/AudioManager.cpp
    
    gui/RectTransform.cpp
    gui/GraphicUI.cpp
    gui/Text.cpp
    gui/Image.cpp
    gui/Button.cpp
    gui/GUIManager.cpp
    gui/ButtonsManager.cpp
    gui/MapBlockGUI.cpp

    cache/TextureCache.cpp
    cache/AudioCache.cpp
    cache/FontCache.cpp
    cache/SheetDataCache.cpp
    cache/YamlDataCache.cpp

    resource/ResourceManager.cpp
    resource/ResourceParser.cpp
    ThemeInfo.cpp

    PUBLIC
    # .h files
    Camera.h
    Rate.h
    Definitions.h
    KeyboardExtension.h
    ColorExtension.h
    
    2d/Object2D.h
    2d/MapBlock2D.h
    2d/MapBlockRenderData.h
    
    audio/AudioManager.h
    
    gui/RectTransform.h
    gui/GraphicUI.h
    gui/Text.h
    gui/Image.h
    gui/Button.h
    gui/GUIManager.h
    gui/ButtonsManager.h
    gui/MapBlockGUI.h

    cache/TextureCache.h
    cache/AudioCache.h
    cache/FontCache.h
    cache/SheetDataCache.h
    cache/YamlDataCache.h

    resource/ResourceManager.h
    resource/ResourceParser.h
    resource/ResourceConstants.h
    resource/ResourceData.h
    
    ThemeInfo.h
    )
