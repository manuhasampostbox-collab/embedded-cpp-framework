#pragma once
#include "IDevice.hpp"
#include "Logger.hpp"
#include <vector>
#include <memory>
#include <string>
#include <sstream>

template<typename T>
class DeviceManager {
    static_assert(std::is_base_of<IDevice, T>::value,
                  "T must derive from IDevice");
public:
    void registerDevice(std::shared_ptr<T> device) {
        devices_.push_back(device);
        Logger::getInstance().info(
            "DeviceManager registered: " + device->getName());
    }

    void initAll() {
        for (auto& d : devices_) {
            if (!d->init()) {
                Logger::getInstance().error(
                    "Init failed: " + d->getName());
            }
        }
    }

    void readAll() {
        for (auto& d : devices_) {
            try {
                if (!d->read()) {
                    Logger::getInstance().warn(
                        "Read failed: " + d->getName());
                }
            } catch (const std::exception& e) {
                Logger::getInstance().error(
                    std::string("Exception in ") + d->getName()
                    + ": " + e.what());
            }
        }
    }

    void printReport() const {
        Logger::getInstance().info("========= DEVICE REPORT =========");
        for (const auto& d : devices_) {
            std::ostringstream oss;
            oss << d->getName()
                << " | Status=" << statusStr(d->getStatus());
            Logger::getInstance().info(oss.str());
        }
        std::ostringstream oss;
        oss << "Total devices: " << devices_.size();
        Logger::getInstance().info(oss.str());
        Logger::getInstance().info("=================================");
    }

    size_t count() const { return devices_.size(); }

private:
    std::vector<std::shared_ptr<T>> devices_;

    static std::string statusStr(DeviceStatus s) {
        switch(s) {
            case DeviceStatus::OK:       return "OK";
            case DeviceStatus::ERROR:    return "ERROR";
            case DeviceStatus::TIMEOUT:  return "TIMEOUT";
            case DeviceStatus::NOT_INIT: return "NOT_INIT";
            default:                     return "UNKNOWN";
        }
    }
};
