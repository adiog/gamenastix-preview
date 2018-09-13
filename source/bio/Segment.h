// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

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

