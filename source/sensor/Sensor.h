// This file is a part of treadmill-t2-opengl project.
// Copyright 2018 Disco WTMH S.A.

#pragma once

#include <memory>
#include <mutex>

#include <FusionData.h>
#include <Kalman.h>
#include <SensorData.h>
#include <sensor/Calibrator.h>


namespace sensor {
class Sensor
{
public:
    Sensor()
            : sensorMutex{std::make_unique<std::mutex>()}
            , fusion(std::make_unique<sensorFusion::Kalman>())
    {
    }

    void calibrate(CalibrationStep calibrationStep)
    {
        std::unique_lock<std::mutex> sensorLock{*sensorMutex};
        calibrator.calibrate(rawData.accelerometer, calibrationStep);
    }

    void init(sensorFusion::SensorData rawData)
    {
        fusion->initialize(rawData);
    }

    void update(sensorFusion::SensorData rawData)
    {
        std::unique_lock<std::mutex> sensorLock{*sensorMutex};
        this->rawData = rawData;
        this->data = calibrator.transform(rawData);
        fusionData = fusion->apply(this->data);
        fusionData.arrow[0] -= 90.0F;
        fusionData.arrow[0] *= -1.0F;
        fusionData.arrow[1] *= -1.0F;
    }

    sensorFusion::FusionData get()
    {
        std::unique_lock<std::mutex> sensorLock{*sensorMutex};
        return fusionData;
    }

private:
    std::unique_ptr<std::mutex> sensorMutex;
    sensorFusion::SensorData rawData;
    sensorFusion::SensorData data;
    sensorFusion::FusionData fusionData;
    Calibrator calibrator;
    std::unique_ptr<sensorFusion::SensorFusion> fusion;
};
}
