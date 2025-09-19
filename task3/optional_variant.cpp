// ✅ 5. optional_variant.cpp
// 实现：

// 用 optional<double> 表示传感器读数（可能失败）。
// 用 variant<int, string, SensorData> 表示多种返回类型。
// 用 visit + Lambda 处理 variant。

#include <iostream>
#include <optional>
#include <variant>
#include <string>

// 用 optional<double> 表示传感器读数（可能失败）。
std::optional<double> readSensor(bool success) {
    if (success) {
        return 42.5; // 假设读到的数据
    } else {
        return std::nullopt; // 读数失败
    }
}

// 用于 variant 的自定义类型
struct SensorData {
    double value;
    std::string unit;
};

// 用 variant<int, string, SensorData> 表示多种返回类型。
using ResultType = std::variant<int, std::string, SensorData>;

ResultType processSensorReading(const std::optional<double>& reading) {
    if (!reading.has_value()) {
        return std::string("Sensor read failed");
    }
    if (reading.value() > 40.0) {
        return SensorData{reading.value(), "Celsius"};
    }
    return int(reading.value());
}

int main() {
    // 测试1：成功读取
    auto reading1 = readSensor(true);
    ResultType result1 = processSensorReading(reading1);

    std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>) {
            std::cout << "Int result: " << arg << std::endl;
        } else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << "String result: " << arg << std::endl;
        } else if constexpr (std::is_same_v<T, SensorData>) {
            std::cout << "SensorData result: " << arg.value << " " << arg.unit << std::endl;
        }
    }, result1);

    // 测试2：读取失败
    auto reading2 = readSensor(false);
    ResultType result2 = processSensorReading(reading2);

    std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>) {
            std::cout << "Int result: " << arg << std::endl;
        } else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << "String result: " << arg << std::endl;
        } else if constexpr (std::is_same_v<T, SensorData>) {
            std::cout << "SensorData result: " << arg.value << " " << arg.unit << std::endl;
        }
    }, result2);

    return 0;
}