add_executable(pulsar-wetee 
    main.cpp)

# target_include_directories(pulsar-wetee PRIVATE src /usr/include)
# target_link_directories(pulsar-wetee PRIVATE /usr/lib)

# target_link_libraries(pulsar-wetee PRIVATE expat)

# 查找并引用Boost库
# find_package(Boost COMPONENTS system thread chrono filesystem program_options REQUIRED)
# target_include_directories(pulsar-wetee PUBLIC ${Boost_INCLUDE_DIRS})
# target_link_libraries(pulsar-wetee PUBLIC ${Boost_LIBRARIES})

# 查找WT库，实现HTTP服务
find_package(wt CONFIG REQUIRED)
target_link_libraries(pulsar-wetee PUBLIC Wt::Wt Wt::HTTP)     

# find_package(unofficial-libffi CONFIG REQUIRED)
# target_link_libraries(pulsar-wetee PUBLIC unofficial::libffi::libffi)

# find_package(Fontconfig REQUIRED) 
# target_link_libraries(pulsar-wetee PUBLIC Fontconfig::Fontconfig)

# find_package(pcre2 REQUIRED) 
# target_link_libraries(pulsar-wetee PUBLIC PCRE2::8BIT PCRE2::16BIT PCRE2::32BIT PCRE2::POSIX)

# find_package(pango CONFIG REQUIRED)
# target_link_libraries(pulsar-server PRIVATE pango::pango)
# find_library(pango_lib pango-1.0 REQUIRED)
# message(STATUS "pango_lib222: ${pango_lib}")
# target_link_libraries(pulsar-wetee PUBLIC ${pango_lib})

# find_package(harfbuzz CONFIG REQUIRED)
# target_link_libraries(pulsar-wetee PUBLIC harfbuzz::harfbuzz)

# 查找并引用日志库
# find_package(spdlog CONFIG REQUIRED)
# target_link_libraries(pulsar-wetee PUBLIC spdlog::spdlog)

# 查找并引用env解析库
# find_package(libenvpp CONFIG REQUIRED)
# target_link_libraries(pulsar-wetee PUBLIC libenvpp::libenvpp)

# 引用公共库
# target_include_directories(pulsar-wetee PRIVATE ${pulsar-common_INCLUDE_DIRS})
# target_link_libraries(pulsar-wetee PRIVATE pulsar-common)
