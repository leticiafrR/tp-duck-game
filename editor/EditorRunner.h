#ifndef EDITORRUNNER_H
#define EDITORRUNNER_H
#include <utility>

#include "multimedia/Camera.h"

#include "mapEditor.h"

class EditorRunner {
private:
    Camera cam;
    MapEditor writeArchive;

public:
    explicit EditorRunner(Renderer& render, int fps);
    void run();
};
#endif
