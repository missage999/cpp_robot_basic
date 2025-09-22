cmake_minimum_required(VERSION 3.5)
project(cmake_tutorial VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 OpenCV
find_package(OpenCV REQUIRED)

# 创建静态库
add_library(robot_lib STATIC src/librobot.cpp)

# 👇 关键！告诉 robot_lib 和它的使用者：“头文件在 include/”
target_include_directories(robot_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 创建可执行文件
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/math_utils.cpp
)

# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE robot_lib ${OpenCV_LIBS})

# 👇 给主程序设置 OpenCV 头文件路径（robot_lib 不需要，除非它用 OpenCV）
target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})