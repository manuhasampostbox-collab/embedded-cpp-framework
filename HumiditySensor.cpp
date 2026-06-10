#include "HumiditySensor.hpp"
#include "Logger.hpp"
#include <sstream>

HumiditySensor::HumiditySensor(const std::string& name)
    : name_(name), value_(0), readCount_(0), errorCount_(0),
      status_(DeviceStatus::NOT_INIT), callCount_(0) {}

bool HumiditySensor::init() {
    status_ = DeviceStatus::OK;
    Logger::getInstance().info(name_ + " initialized");
    return true;
}

bool HumiditySensor::read() {
    callCount_++;
    if (callCount_ % 6 == 0) {
        status_ = DeviceStatus::ERROR;
        errorCount_++;
        Logger::getInstance().error(name_ + " read failed (CRC error)");
        return false;
    }
    value_ = 55.0f + (callCount_ % 8) * 1.5f;
    readCount_++;
    status_ = DeviceStatus::OK;
    std::ostringstream oss;
    oss << name_ << " | Hum=" << value_ << "%"
        << " | reads=" << readCount_
        << " | errors=" << errorCount_;
    Logger::getInstance().info(oss.str());
    return true;
}

DeviceStatus HumiditySensor::getStatus()     const { return status_; }
std::string  HumiditySensor::getName()       const { return name_; }
float        HumiditySensor::getValue()      const { return value_; }
float        HumiditySensor::getMinRange()   const { return 0.0f; }
float        HumiditySensor::getMaxRange()   const { return 100.0f; }
uint32_t     HumiditySensor::getReadCount()  const { return readCount_; }
uint32_t     HumiditySensor::getErrorCount() const { return errorCount_; }
void         HumiditySensor::reset() {
    readCount_ = errorCount_ = callCount_ = 0;
    status_ = DeviceStatus::NOT_INIT;
}
