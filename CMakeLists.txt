cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project(semantic-segmentation)

# Find the Ignition_Transport library
find_package(ignition-transport11 QUIET REQUIRED OPTIONAL_COMPONENTS log)
set(IGN_TRANSPORT_VER ${ignition-transport11_VERSION_MAJOR})
find_package(ignition-msgs8 QUIET REQUIRED)

include_directories(${CMAKE_BINARY_DIR})

if (EXISTS "${CMAKE_SOURCE_DIR}/segmentation_node.cc")
  add_executable(segmentation_node segmentation_node.cc)
  target_link_libraries(segmentation_node ignition-transport${IGN_TRANSPORT_VER}::core)
endif()


if (EXISTS "${CMAKE_SOURCE_DIR}/subscriber.cc")
  add_executable(subscriber subscriber.cc)
  target_link_libraries(subscriber ignition-transport${IGN_TRANSPORT_VER}::core)
endif()


if (EXISTS "${CMAKE_SOURCE_DIR}/publisher.cc")
  add_executable(publisher publisher.cc)
  target_link_libraries(publisher ignition-transport${IGN_TRANSPORT_VER}::core)
endif()



if (EXISTS "${CMAKE_SOURCE_DIR}/msgs/")
  # Message generation. Only required when using custom Protobuf messages.
  find_package(Protobuf REQUIRED)
  add_subdirectory(msgs)
  set_source_files_properties(${PROTO_SRC} ${PROTO_HEADER} PROPERTIES GENERATED TRUE)
endif()
