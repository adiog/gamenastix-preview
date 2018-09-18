// This file is a part of Treadmill project.
// Copyright 2018 Disco WTMH S.A.

#pragma once

#include <component/Scene.h>
#include <glm/vec3.hpp>
#include "glout.h"


struct OpenGLContext
{
    int old_y, old_x;
    int mouse_y, mouse_x;
    int pas_mouse_y, pas_mouse_x;

    int gwidth;
    int gheight;

    int gyaw = 0;
    int gpitch = 0;
    float cameraDistance = 25.0;
    static constexpr const float cameraDistanceStep = 0.5;
    glm::vec3 cam;
    glm::vec3 top;

    component::Scene scene;
    unsigned char lastKey;

    glout out;
};

extern OpenGLContext openGLContext;
