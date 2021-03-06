// This file is a part of Treadmill project.
// Copyright 2018 Disco WTMH S.A.

#pragma once

#include <bio/Medium.h>


namespace bio {
struct Bio4 : public Medium
{
    Model getModel() const override
    {
        static Model model = {
            Segment::UpperLegLeft,
            Segment::LowerLegLeft,
            Segment::UpperLegRight,
            Segment::LowerLegRight};
        return model;
    }
};
}
