#代码解释：https://lxblog.com/qianwen/share?shareId=e0d19615-7ace-4a99-98c0-23f18d2675bf
# 可执行文件名字自取，这里叫 cmake_demo，新建项目需要改名
set(TARGET_NAME thread_singleton)

# 👇 新增：监控 include/ 下所有头文件，触发重新配置
file(GLOB_RECURSE lib_headers CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
     ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

# ① 收集库源码（不含 main.cpp）
file(GLOB_RECURSE lib_srcs CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
list(FILTER lib_srcs EXCLUDE REGEX ".*main\\.cpp$")

# 👇 新增：判断是否有库源文件，有才创建库
if(lib_srcs)
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
endif()

# ③ 可执行文件
add_executable(${TARGET_NAME} src/main.cpp)

# 👇 新增：无论有没有库，main.cpp 都需要访问 include/ 下的头文件！
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 👇 新增：如果库存在，才链接
if(TARGET ${TARGET_NAME}_lib)
    target_link_libraries(${TARGET_NAME} PRIVATE ${TARGET_NAME}_lib)
endif()