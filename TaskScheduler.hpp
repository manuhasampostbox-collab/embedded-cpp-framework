#pragma once
#include <vector>
#include <functional>
#include <string>
#include <chrono>
#include "Logger.hpp"

struct Task {
    std::string            name;
    std::function<void()>  callback;
    uint32_t               period_ms;
    uint32_t               last_run_ms;
    uint32_t               run_count;
};

class TaskScheduler {
public:
    TaskScheduler() : start_time_(std::chrono::steady_clock::now()) {}

    void addTask(const std::string& name,
                 std::function<void()> cb,
                 uint32_t period_ms) {
        tasks_.push_back({name, cb, period_ms, 0, 0});
        Logger::getInstance().info(
            "Scheduler: task added '" + name +
            "' period=" + std::to_string(period_ms) + "ms");
    }

    void run(uint32_t total_ms) {
        Logger::getInstance().info("Scheduler started");
        uint32_t elapsed = 0;
        while (elapsed < total_ms) {
            for (auto& t : tasks_) {
                if (elapsed - t.last_run_ms >= t.period_ms) {
                    std::string msg = "Task '" + t.name +
                        "' executing at t=" +
                        std::to_string(elapsed) + "ms";
                    Logger::getInstance().info(msg);
                    t.callback();
                    t.last_run_ms = elapsed;
                    t.run_count++;
                }
            }
            elapsed += 500;
        }
        Logger::getInstance().info("Scheduler finished");
    }

    void printStats() const {
        Logger::getInstance().info("===== SCHEDULER STATS =====");
        for (const auto& t : tasks_) {
            Logger::getInstance().info(
                "Task '" + t.name + "' ran " +
                std::to_string(t.run_count) + " times");
        }
    }

private:
    std::vector<Task> tasks_;
    std::chrono::steady_clock::time_point start_time_;
};
