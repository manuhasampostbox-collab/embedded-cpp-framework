#pragma once
#include "ISensor.hpp"
#include <string>

class TemperatureSensor : public ISensor {
public:
    explicit TemperatureSensor(const std::string& name, float minR=-40.0f, float maxR=80.0f);
    bool         init()             override;
    bool         read()             override;
    DeviceStatus getStatus()  const override;
    std::string  getName()    const override;
    void         reset()            override;
    float        getValue()   const override;
    float        getMinRange() const override;
    float        getMaxRange() const override;
    uint32_t     getReadCount()  const override;
    uint32_t     getErrorCount() const override;
    void         setThreshold(float high) { threshold_ = high; }
    bool         isThresholdExceeded() const { return value_ > threshold_; }
private:
    std::string  name_;
    float        value_;
    float        minRange_, maxRange_, threshold_;
    uint32_t     readCount_, errorCount_;
    DeviceStatus status_;
    int          callCount_;
};
