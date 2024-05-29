
add_library(pulsar-modules)

target_sources(pulsar-modules
  PUBLIC
    FILE_SET CXX_MODULES FILES
      foo.cxx
)

#add_executable(hello main.cxx)
#target_link_libraries(hello pulsar-modules)