// This file is a part of Treadmill project.
// Copyright 2018 Disco WTMH S.A.

#pragma once

#include <udpbox.h>
#include <model/Model.h>


namespace network {
struct Matcher
{
    static bio::Segment match(const udpbox::Datagram& datagram)
    {
        static std::unordered_map<std::string, bio::Segment> mapping = {
                std::make_pair(std::string("192.168.20.122"), bio::Segment::UpperLegLeft),
                std::make_pair(std::string("192.168.20.121"), bio::Segment::LowerLegLeft),
                std::make_pair(std::string("192.168.20.123"), bio::Segment::UpperLegRight),
                std::make_pair(std::string("192.168.20.124"), bio::Segment::LowerLegRight),
        };
        std::string originalSender(reinterpret_cast<const char *>(&datagram.payload[0]));
#ifdef DEBUG
        std::cout << originalSender << std::endl;
#endif
        return mapping[originalSender];
    }
};
}
