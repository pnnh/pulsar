add_library(pulsar-common STATIC
        utils/md5.cc
        utils/md5.h
        utils/mime.cpp
        utils/mime.h
        utils/datetime.cpp
        utils/datetime.h
        utils/query.cpp
        utils/query.h
        utils/uuid.cpp
        utils/uuid.h
)

# 查找并引用日志库
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(pulsar-common PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

# 查找并引用Boost库
find_package(Boost COMPONENTS system thread chrono url REQUIRED)
target_include_directories(pulsar-common PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(pulsar-common PUBLIC ${Boost_LIBRARIES})

# # 测试程序
# add_executable(pulsar-common-test main.cpp)
# target_link_libraries(pulsar-common-test PRIVATE pulsar-common)

# # 添加测试用例
# add_test(NAME pulsar-common-test COMMAND pulsar-common-test)