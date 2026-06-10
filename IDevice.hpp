#pragma once
#include <string>
#include <cstdint>

enum class DeviceStatus { OK, ERROR, TIMEOUT, NOT_INIT };

class IDevice {
public:
    virtual ~IDevice() = default;
    virtual bool        init()            = 0;
    virtual bool        read()            = 0;
    virtual DeviceStatus getStatus() const = 0;
    virtual std::string  getName()  const = 0;
    virtual void        reset()           = 0;
};
