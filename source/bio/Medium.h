// This file is a part of Treadmill project.
// Copyright 2018 Disco WTMH S.A.

#pragma once

#include <bio/Model.h>


namespace bio {
struct Medium
{
    virtual Model getModel() const = 0;
};
}
