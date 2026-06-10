# Embedded C++ Device Framework — Project

## Overview
Production-quality embedded C++ framework demonstrating OOP design patterns,
templates, RTOS-style task scheduling, and hardware abstraction.
Compiled and tested on Linux host — portable to ARM/AVR targets.

## C++ Concepts Demonstrated

| Concept | Where Used |
|---------|-----------|
| Abstract base class + pure virtual | IDevice.hpp → ISensor.hpp |
| Inheritance + polymorphism | TemperatureSensor, HumiditySensor extend ISensor |
| Templates | RingBuffer<T,SIZE>, DeviceManager<T> |
| Singleton pattern | Logger (single global instance) |
| Smart pointers | std::shared_ptr for device ownership |
| Lambda functions | Task callbacks in TaskScheduler |
| Exception handling | try/catch in DeviceManager::readAll() |
| STL containers | std::vector for devices and tasks |
| RAII | Resources acquired in constructor, released in destructor |

## Architecture
## Sample Output
## How to Build

```bash
g++ -std=c++17 -o framework main.cpp TemperatureSensor.cpp HumiditySensor.cpp -Wall
./framework
```

## Files

| File | Description |
|------|-------------|
| IDevice.hpp | Abstract base class with pure virtual interface |
| ISensor.hpp | Sensor interface extending IDevice |
| TemperatureSensor.hpp/cpp | Concrete sensor with threshold alert |
| HumiditySensor.hpp/cpp | Concrete sensor with CRC error simulation |
| DeviceManager.hpp | Template device manager with polymorphism |
| TaskScheduler.hpp | RTOS-style scheduler with lambda callbacks |
| RingBuffer.hpp | Generic template ring buffer |
| Logger.hpp | Singleton logger |
| main.cpp | Application layer |

## Resume Bullet Point
Designed an embedded C++ device management framework using abstract base classes,
inheritance, templates (RingBuffer<T>, DeviceManager<T>), singleton Logger,
smart pointers, and lambda-based task scheduler; demonstrated I2C error handling,
threshold alerts, and RTOS-style scheduling compiled with GCC C++17 on Linux.
