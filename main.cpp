#include <iostream>
#include <memory>
#include "IDevice.hpp"
#include "ISensor.hpp"
#include "TemperatureSensor.hpp"
#include "HumiditySensor.hpp"
#include "DeviceManager.hpp"
#include "TaskScheduler.hpp"
#include "RingBuffer.hpp"
#include "Logger.hpp"

int main() {
    Logger::getInstance().info("========================================");
    Logger::getInstance().info("  Embedded C++ Device Framework");
    Logger::getInstance().info("  OOP + Templates + RTOS Scheduler");
    Logger::getInstance().info("========================================");

    // Create sensors using smart pointers
    auto tempSensor = std::make_shared<TemperatureSensor>("TempSensor-1");
    auto humSensor  = std::make_shared<HumiditySensor>("HumSensor-1");

    // Set temperature alert threshold
    tempSensor->setThreshold(30.0f);

    // Device manager with polymorphism
    DeviceManager<ISensor> manager;
    manager.registerDevice(tempSensor);
    manager.registerDevice(humSensor);
    manager.initAll();

    // Ring buffer for sensor readings
    RingBuffer<float, 8> tempHistory;
    RingBuffer<float, 8> humHistory;

    // Task scheduler with lambdas
    TaskScheduler scheduler;

    scheduler.addTask("SensorPoll", [&]() {
        manager.readAll();
        if (tempSensor->getStatus() == DeviceStatus::OK)
            tempHistory.push(tempSensor->getValue());
        if (humSensor->getStatus() == DeviceStatus::OK)
            humHistory.push(humSensor->getValue());
    }, 1000);

    scheduler.addTask("HealthCheck", [&]() {
        Logger::getInstance().info("--- Health Check ---");
        manager.printReport();
        std::ostringstream oss;
        oss << "TempHistory size=" << tempHistory.size()
            << " HumHistory size=" << humHistory.size();
        Logger::getInstance().info(oss.str());
    }, 3000);

    scheduler.addTask("FinalReport", [&]() {
        Logger::getInstance().info("========= FINAL REPORT =========");
        std::ostringstream oss;
        oss << "TempSensor reads=" << tempSensor->getReadCount()
            << " errors=" << tempSensor->getErrorCount();
        Logger::getInstance().info(oss.str());
        oss.str("");
        oss << "HumSensor  reads=" << humSensor->getReadCount()
            << " errors=" << humSensor->getErrorCount();
        Logger::getInstance().info(oss.str());
        scheduler.printStats();
        Logger::getInstance().info("================================");
    }, 8000);

    // Run for 10 seconds simulation
    scheduler.run(10000);

    return 0;
}
