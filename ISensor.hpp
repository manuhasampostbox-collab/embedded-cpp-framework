#pragma once
#include "IDevice.hpp"

class ISensor : public IDevice {
public:
    virtual ~ISensor() = default;
    virtual float    getValue()    const = 0;
    virtual float    getMinRange() const = 0;
    virtual float    getMaxRange() const = 0;
    virtual uint32_t getReadCount() const = 0;
    virtual uint32_t getErrorCount() const = 0;
};
