cmake_minimum_required(VERSION 3.30...3.31)

project(Pulsar VERSION 0.1.0 LANGUAGES C CXX)

# 设置语言标准
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置开启显示详细的构建过程
set(CMAKE_VERBOSE_MAKEFILE ON)

# 启用测试
enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})
link_directories(${PROJECT_BINARY_DIR})

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

set(APP_NAME MTPulsar)

add_executable(${APP_NAME})

file(GLOB_RECURSE APP_SOURCES pulsar/*.cpp quark/*.cpp)

target_sources(${APP_NAME} PUBLIC ${APP_SOURCES})

file(GLOB_RECURSE APP_MODULES pulsar/*.cxx quark/*.cxx)

target_sources(${APP_NAME}
        PUBLIC
        FILE_SET CXX_MODULES FILES
        ${APP_MODULES}
)

# 查找并引用Boost库
find_package(Boost COMPONENTS system thread chrono filesystem url REQUIRED)
target_include_directories(${APP_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${APP_NAME} PRIVATE ${Boost_LIBRARIES})

# 查找Workflow库，实现HTTP服务
set(WORKFLOW_BUILD_STATIC_RUNTIME ON)
find_library(workflow_lib workflow)
target_link_libraries(${APP_NAME} PRIVATE ${workflow_lib})

# 查找并引用日志库
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${APP_NAME} PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

# 查找JSON库
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${APP_NAME} PRIVATE nlohmann_json::nlohmann_json)

# 查找并链接模板库
find_package(inja CONFIG REQUIRED)
target_link_libraries(${APP_NAME} PRIVATE pantor::inja)

# 查找并引用env解析库
find_package(libenvpp CONFIG REQUIRED)
target_link_libraries(${APP_NAME} PRIVATE libenvpp::libenvpp)

# 查找并引用日期库
find_package(date CONFIG REQUIRED)
target_link_libraries(${APP_NAME} PRIVATE date::date-tz)

# 查找并引用Sqlite解析库
find_package(unofficial-sqlite3 CONFIG REQUIRED)
target_link_libraries(${APP_NAME} PRIVATE unofficial::sqlite3::sqlite3)

# 查找并引用yaml-cpp解析库
find_package(yaml-cpp CONFIG REQUIRED)
target_link_libraries(${APP_NAME} PRIVATE yaml-cpp::yaml-cpp)

# 查找并引用Markdown解析库
find_package(cmark CONFIG REQUIRED)
target_link_libraries(${APP_NAME} PRIVATE cmark::cmark)

# 查找并引用PostgreSQL解析库
find_package(libpqxx CONFIG REQUIRED)
target_link_libraries(${APP_NAME} PRIVATE libpqxx::pqxx)

# 拷贝资源文件到二进制目录，方便调试
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# 配置安装内容
install(TARGETS ${APP_NAME}
        RUNTIME_DEPENDENCY_SET ${APP_NAME}-dependencies
        DESTINATION lib)
install(RUNTIME_DEPENDENCY_SET ${APP_NAME}-dependencies)
 