cmake_minimum_required(VERSION 3.10)
project(PlugProjectTest)

# 可执行文件输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../Bin)

if (NOT PlugToolPath)
    # 单独设置PlugTool的头文件搜索路径
    set(PlugToolPath ${PROJECT_SOURCE_DIR}/../include/)
endif()

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Test.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${PlugToolPath})