#ifndef EDITORRUNNER_H
#define EDITORRUNNER_H
#include "multimedia/Camera.h"

#include "mapEditor.h"

class EditorRunner {
private:
    MapEditor writeArchive;

public:
    void run(Camera& cam);
};
#endif
