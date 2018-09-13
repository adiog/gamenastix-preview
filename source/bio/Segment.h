// This file is a part of Treadmill project.
// Copyright 2018 Disco WTMH S.A.

#pragma once


namespace bio {
enum class Segment
{
    Head,
    Chest,
    Pelvis,
    ShoulderLeft,
    ShoulderRight,
    UpperArmLeft,
    UpperArmRight,
    ForearmLeft,
    ForearmRight,
    HandLeft,
    HandRight,
    UpperLegLeft,
    UpperLegRight,
    LowerLegLeft,
    LowerLegRight,
    FootLeft,
    FootRight
};
}

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

