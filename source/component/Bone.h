// This file is a part of Treadmill project.
// Copyright 2018 Disco WTMH S.A.

#pragma once

#include <GL/glu.h>
#include <glm/gtx/rotate_vector.hpp>
#include <math/MathTypes.h>
#include <model/Layout.h>

namespace component {
class Bone
{
public:
    static constexpr const Real thicknessRatio = 0.13;
    Real thickness;
    Real lengthPart;
    Real lengthRemain;

    Bone(bio::Segment segment, Real length, Real weight)
            : segment(segment)
            , length(length)
            , weight(weight)
    {
        thickness = length * thicknessRatio;
        lengthPart = length * weight;
        lengthRemain = length * (1.0F - weight);
    }

    Real getThickness()
    {
        return thickness;
    }

    Real getThicknessOffset()
    {
        return lengthPart;
    }

    void rotate(const model::Layout& layout)
    {
        auto it = layout.segmentLayout.find(segment);
        if (it != layout.segmentLayout.end())
        {
            auto& q4 = it->second;

            float roll = q4[2];
            float pitch = q4[1];
#define SUPPORT_ROLL
#define SUPPORT_PITCH
#ifdef SUPPORT_ROLL
            if (roll != 0)
            {
                glRotatef(roll, 0, 1, 0);
            }
#endif
#ifdef SUPPORT_PITCH
            if (pitch != 0)
            {
                glRotatef(pitch, -1, 0, 0);
            }
#endif
        }
    }

    void derotate(const model::Layout& layout)
    {
        auto it = layout.segmentLayout.find(segment);
        if (it != layout.segmentLayout.end())
        {
            auto& q4 = it->second;

            float roll = q4[2];
            float pitch = q4[1];

#ifdef SUPPORT_PITCH
            if (pitch != 0)
            {
                glRotatef(-pitch, -1, 0, 0);
            }
#endif
#ifdef SUPPORT_ROLL
            if (roll != 0)
            {
                glRotatef(-roll, 0, 1, 0);
            }
#endif
        }

    }

    void render(const model::Layout& layout)
    {
        ContextPreserver contextPreserver;
        rotate(layout);
        gluSphere(quads[2].get(), 0.02, 20, 50);

        glBegin(GL_TRIANGLES);
        glColor4ub(0xD4, 0x12, 0x82, 0xFF);
        glVertex3f(0, 0, 0);
        glColor4ub(0x18, 0x54, 0x76, 0xFF);
        glVertex3f(-thickness, -thickness, lengthPart);
        glColor4ub(0x45, 0x84, 0xD4, 0xFF);
        glVertex3f(-thickness, thickness, lengthPart);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor4ub(0xD4, 0x12, 0x82, 0xFF);
        glVertex3f(0, 0, 0);
        glColor4ub(0x18, 0x54, 0x76, 0xFF);
        glVertex3f(-thickness, thickness, lengthPart);
        glColor4ub(0x45, 0x84, 0xD4, 0xFF);
        glVertex3f(thickness, thickness, lengthPart);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor4ub(0xD4, 0x12, 0x82, 0xFF);
        glVertex3f(0, 0, 0);
        glColor4ub(0x18, 0x54, 0x76, 0xFF);
        glVertex3f(thickness, thickness, lengthPart);
        glColor4ub(0x45, 0x84, 0xD4, 0xFF);
        glVertex3f(thickness, -thickness, lengthPart);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor4ub(0xD4, 0x12, 0x82, 0xFF);
        glVertex3f(0, 0, 0);
        glColor4ub(0x18, 0x54, 0x76, 0xFF);
        glVertex3f(thickness, -thickness, lengthPart);
        glColor4ub(0x45, 0x84, 0xD4, 0xFF);
        glVertex3f(-thickness, -thickness, lengthPart);
        glEnd();

        glTranslatef(0.0, 0.0, length);

        glBegin(GL_TRIANGLES);
        glColor4ub(0x18, 0x54, 0x76, 0xFF);
        glVertex3f(0, 0, 0);
        glColor4ub(0x45, 0x84, 0xD4, 0xFF);
        glVertex3f(-thickness, -thickness, -lengthRemain);
        glColor4ub(0xD4, 0x12, 0x82, 0xFF);
        glVertex3f(-thickness, thickness, -lengthRemain);
        glEnd();

        glBegin(GL_POLYGON);
        glColor4ub(0x18, 0x54, 0x76, 0xFF);
        glVertex3f(0, 0, 0);
        glColor4ub(0x45, 0x84, 0xD4, 0xFF);
        glVertex3f(-thickness, thickness, -lengthRemain);
        glColor4ub(0xD4, 0x12, 0x82, 0xFF);
        glVertex3f(thickness, thickness, -lengthRemain);
        glEnd();
        glBegin(GL_POLYGON);
        glColor4ub(0x18, 0x54, 0x76, 0xFF);
        glVertex3f(0, 0, 0);
        glColor4ub(0x45, 0x84, 0xD4, 0xFF);
        glVertex3f(thickness, -thickness, -lengthRemain);
        glColor4ub(0xD4, 0x12, 0x82, 0xFF);
        glVertex3f(thickness, thickness, -lengthRemain);
        glEnd();
        glBegin(GL_POLYGON);
        glColor4ub(0x18, 0x54, 0x76, 0xFF);
        glVertex3f(-thickness, -thickness, -lengthRemain);
        glColor4ub(0x45, 0x84, 0xD4, 0xFF);
        glVertex3f(thickness, -thickness, -lengthRemain);
        glColor4ub(0xD4, 0x12, 0x82, 0xFF);
        glVertex3f(0, 0, 0);
        glEnd();
    }

    void follow(const model::Layout& layout)
    {
        rotate(layout);
        glTranslatef(0.0, 0.0, length);
        derotate(layout);
    }

private:
    bio::Segment segment;
    Real length;
    Real weight;

    opengl::Quad quads[3];
};
}
