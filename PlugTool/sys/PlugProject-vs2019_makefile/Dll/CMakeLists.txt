cmake_minimum_required(VERSION 3.10)
project(PlugProject)

# 动态编译开关
option(BUILD_SHARED_LIB_T "This library build shared" ON)
# 库输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../Bin)
# 当前模块头文件搜索路径
set(PlugProject_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../ CACHE STRING "woll-shaderc header dir")

if (NOT PlugToolPath)
    # 单独设置PlugTool的头文件搜索路径
    set(PlugToolPath ${PROJECT_SOURCE_DIR}/../include/)
endif()

file(GLOB_RECURSE T_SRC ${PROJECT_SOURCE_DIR}/../Src/*.cpp ${PROJECT_SOURCE_DIR}/../Src/*.c)

if (BUILD_SHARED_LIB_T)
    add_library(${PROJECT_NAME} SHARED ${T_SRC})
    set_target_properties(${PROJECT_NAME} PROPERTIES VERSION 1.0 SOVERSION 1)
else ()
    add_library(${PROJECT_NAME} STATIC ${T_SRC})
endif ()

target_include_directories(${PROJECT_NAME} PRIVATE ${PlugProject_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${PlugToolPath})
