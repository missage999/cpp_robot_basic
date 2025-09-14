# 可执行文件名字自取，这里叫 cmake_demo，新建项目需要改名
set(TARGET_NAME cmake_demo)

# ① 收集库源码（不含 main.cpp）
file(GLOB_RECURSE lib_srcs CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
list(FILTER lib_srcs EXCLUDE REGEX ".*main\\.cpp$")

# ② 建静态库
add_library(${TARGET_NAME}_lib STATIC ${lib_srcs})
target_include_directories(${TARGET_NAME}_lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${TARGET_NAME}_lib PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ③ 可执行文件
add_executable(${TARGET_NAME} src/main.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE ${TARGET_NAME}_lib)