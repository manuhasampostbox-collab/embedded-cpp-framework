#include "TemperatureSensor.hpp"
#include "Logger.hpp"
#include <sstream>

TemperatureSensor::TemperatureSensor(const std::string& name, float minR, float maxR)
    : name_(name), value_(0), minRange_(minR), maxRange_(maxR),
      threshold_(30.0f), readCount_(0), errorCount_(0),
      status_(DeviceStatus::NOT_INIT), callCount_(0) {}

bool TemperatureSensor::init() {
    status_ = DeviceStatus::OK;
    Logger::getInstance().info(name_ + " initialized");
    return true;
}

bool TemperatureSensor::read() {
    callCount_++;
    // Simulate I2C error every 8th read
    if (callCount_ % 8 == 0) {
        status_ = DeviceStatus::ERROR;
        errorCount_++;
        Logger::getInstance().error(name_ + " read failed (I2C timeout)");
        return false;
    }
    // Simulate realistic temperature
    value_ = 24.0f + (callCount_ % 10) * 0.7f;
    readCount_++;
    status_ = DeviceStatus::OK;

    std::ostringstream oss;
    oss << name_ << " | Temp=" << value_ << "C"
        << " | reads=" << readCount_
        << " | errors=" << errorCount_;
    Logger::getInstance().info(oss.str());

    if (isThresholdExceeded()) {
        std::ostringstream alert;
        alert << name_ << " exceeded threshold! "
              << value_ << "C > " << threshold_ << "C";
        Logger::getInstance().alert(alert.str());
    }
    return true;
}

DeviceStatus TemperatureSensor::getStatus()    const { return status_; }
std::string  TemperatureSensor::getName()      const { return name_; }
float        TemperatureSensor::getValue()     const { return value_; }
float        TemperatureSensor::getMinRange()  const { return minRange_; }
float        TemperatureSensor::getMaxRange()  const { return maxRange_; }
uint32_t     TemperatureSensor::getReadCount() const { return readCount_; }
uint32_t     TemperatureSensor::getErrorCount() const { return errorCount_; }
void         TemperatureSensor::reset() {
    readCount_ = errorCount_ = callCount_ = 0;
    status_ = DeviceStatus::NOT_INIT;
}
