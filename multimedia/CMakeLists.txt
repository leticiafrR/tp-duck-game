target_sources(taller_multimedia
    PRIVATE
    # .cpp files
    Button.cpp
    Camera.cpp
    GraphicUI.cpp
    SheetDataCache.cpp
    Object2D.cpp
    AudioCache.cpp
    FontCache.cpp
    KeyboardExtension.cpp

    PUBLIC
    # .h files
    AudioCache.h
    AudioManager.h
    Button.h
    ButtonsManager.h
    Camera.h
    ColorExtension.h
    KeyboardExtension.h
    Definitions.h
    FontCache.h
    GraphicUI.h
    GUIManager.h
    Image.h
    MapBlock2D.h
    Object2D.h
    Rate.h
    RectTransform.h
    SheetDataCache.h
    Text.h
    TextureCache.h
    SDLExtendion.h
    )
