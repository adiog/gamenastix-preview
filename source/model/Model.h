// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <unordered_map>
#include <model/Layout.h>
#include <sensor/Sensor.h>
#include <utility>

namespace model {
struct Model : public std::unordered_map<bio::Segment, sensor::Sensor, EnumClassHash>
{
    Layout getLayout()
    {
        Layout layout;

        for(auto &sensorEntry : *this)
        {
            layout.segmentLayout.emplace(std::make_pair(sensorEntry.first, sensorEntry.second.get().arrow));
        }

        layout.segmentLayout[bio::Segment::FootLeft] = {-90,0,0};
        layout.segmentLayout[bio::Segment::FootRight] = {-90,0,0};

        return layout;
    }
};
}
