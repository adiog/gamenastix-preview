// This file is a part of Treadmill project.
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
