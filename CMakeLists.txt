#代码解释：https://lxblog.com/qianwen/share?shareId=f9f7b000-69f0-476f-aace-026e95f59f10
cmake_minimum_required(VERSION 3.15)
project(VCPP_ROBOT_BASIC CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# ① 所有可执行文件统一输出到 <工程顶层-build>/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ② 扫描“单文件”任务：task* 根目录下的 *.cpp
file(GLOB tasks CONFIGURE_DEPENDS RELATIVE ${CMAKE_SOURCE_DIR} task*)

foreach(t ${tasks})
    # 只取 *.cpp → 一个文件一个 exe
    file(GLOB cpp_files CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/${t}/*.cpp)
    foreach(c ${cpp_files})
        get_filename_component(name ${c} NAME_WE)
        add_executable(${name} ${c})
        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(${name} PRIVATE -Wall -Wextra -Wpedantic)
        endif()
    endforeach()

    # ③ 如果 task* 里还有“多文件子文件夹”，就再扫一遍
    file(GLOB multi_dirs CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/${t}/*)
    foreach(d ${multi_dirs})
        if(IS_DIRECTORY ${d} AND EXISTS ${d}/CMakeLists.txt)
            add_subdirectory(${d})
        endif()
    endforeach()
endforeach()