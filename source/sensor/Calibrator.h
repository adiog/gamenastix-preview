// This file is a part of Treadmill project.
// Copyright 2018 Disco WTMH S.A.

#pragma once

#include <math/LinearAlgebra.h>
#include <math/MathTypes.h>

#include <SensorData.h>
#include <glm/detail/type_mat3x3.hpp>

namespace sensor {

enum class CalibrationStep
{
    NPose,
    SPose
};

class Calibrator
{
public:
    Calibrator()
            : calibrationMatrix(glm::mat3{1.0})
    {
    }

    void calibrate(glm::vec3 referenceV3, CalibrationStep calibrationStep)
    {
        switch (calibrationStep)
        {
            case CalibrationStep::NPose:
                referenceZCalibrationVector = referenceV3;
                break;
            case CalibrationStep::SPose:
                referenceXZCalibrationVector = referenceV3;
                break;
        }

        calibrationMatrix = math::getCalibrationMatrix(referenceZCalibrationVector, referenceXZCalibrationVector);
    }

    sensorFusion::SensorData transform(const sensorFusion::SensorData &rawData)
    {
        sensorFusion::SensorData transformedData;
        transformedData.accelerometer = rawData.accelerometer * calibrationMatrix;
        transformedData.gyroscope = rawData.gyroscope * calibrationMatrix;
        transformedData.magnetometer = rawData.magnetometer * calibrationMatrix;
        return transformedData;
    }

private:
    glm::vec3 referenceZCalibrationVector;
    glm::vec3 referenceXZCalibrationVector;
    glm::mat3 calibrationMatrix;
};
}
