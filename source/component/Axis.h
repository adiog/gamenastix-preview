// This file is a part of treadmill-t2-opengl project.
// Copyright 2018 Disco WTMH S.A.

#pragma once

#include <opengl/ContextPreserver.h>


struct Axis
{
    static void render()
    {
        ContextPreserver contextPreserver;
        glLoadIdentity();
        glPointSize(5.0);
        glBegin(GL_POINTS);
        glColor3f(1, 1, 1);
        glVertex3f(0.0F, 0.0F, 0.0F);
        glColor3f(1, 0, 0);
        glVertex3f(3.0F, 0.0F, 0.0F);
        glVertex3f(4.0F, 0.0F, 0.0F);
        glVertex3f(5.0F, 0.0F, 0.0F);
        glColor3f(0, 1, 0);
        glVertex3f(0.0F, 3.0F, 0.0F);
        glVertex3f(0.0F, 4.0F, 0.0F);
        glVertex3f(0.0F, 5.0F, 0.0F);
        glColor3f(0, 0, 1);
        glVertex3f(0.0F, 0.0F, 3.0F);
        glVertex3f(0.0F, 0.0F, 4.0F);
        glVertex3f(0.0F, 0.0F, 5.0F);
        glEnd();
    }
};