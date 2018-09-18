// This file is a part of Treadmill project.
// Copyright 2018 Disco WTMH S.A.

#pragma once

#include <bio/Medium.h>


namespace bio {
struct RigidBody : public Medium
{
    Model getModel() const override
    {
        static Model model = {
            Segment::Head,
            Segment::Chest,
            Segment::Pelvis,
            Segment::ShoulderLeft,
            Segment::ShoulderRight,
            Segment::UpperArmLeft,
            Segment::UpperArmRight,
            Segment::ForearmLeft,
            Segment::ForearmRight,
            Segment::HandLeft,
            Segment::HandRight,
            Segment::UpperLegLeft,
            Segment::UpperLegRight,
            Segment::LowerLegLeft,
            Segment::LowerLegRight,
            Segment::FootLeft,
            Segment::FootRight};
        return model;
    }
};
}
