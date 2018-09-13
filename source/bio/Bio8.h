// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <bio/Medium.h>


namespace bio {
struct Bio8 : public Medium
{
    Model getModel() const override
    {
        static Model model = {
            Segment::UpperArmLeft,
            Segment::ForearmLeft,
            Segment::UpperArmRight,
            Segment::ForearmRight,
            Segment::UpperLegLeft,
            Segment::LowerLegLeft,
            Segment::UpperLegRight,
            Segment::LowerLegRight};
        return model;
    }
};
}