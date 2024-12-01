#ifndef EDITORRUNNER_H
#define EDITORRUNNER_H
#include <utility>

#include "editWorld/mapEditor.h"
#include "multimedia/Camera.h"

class EditorRunner {
private:
    Camera cam;
    MapEditor writeArchive;

public:
    explicit EditorRunner(Renderer& render, int fps);
    void run();
    ~EditorRunner() = default;
};
#endif
