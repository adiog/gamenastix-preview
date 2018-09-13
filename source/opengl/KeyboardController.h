// This file is a part of treadmill-t2-opengl project.
// Copyright 2018 Disco WTMH S.A.

#pragma once


struct KeyboardController
{
    static void keyboardCallback(unsigned char key, int x, int y)
    {
        if (key == 'q')
        {
            exit(0);
        }
        else
        {
            openGLContext.lastKey = key;
        }
        Display::redisplay();
    }
};
