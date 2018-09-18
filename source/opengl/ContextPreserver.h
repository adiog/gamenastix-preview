// This file is a part of treadmill-t2-opengl project.
// Copyright 2018 Disco WTMH S.A.

#pragma once

#include <GL/gl.h>


struct ContextPreserver {
    ContextPreserver()
    {
        glPushMatrix();
    }

    ~ContextPreserver()
    {
        glPopMatrix();
    }
};
