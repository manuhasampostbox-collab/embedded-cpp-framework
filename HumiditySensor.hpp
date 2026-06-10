#pragma once
#include "ISensor.hpp"
#include <string>

class HumiditySensor : public ISensor {
public:
    explicit HumiditySensor(const std::string& name);
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
private:
    std::string  name_;
    float        value_;
    uint32_t     readCount_, errorCount_;
    DeviceStatus status_;
    int          callCount_;
};
