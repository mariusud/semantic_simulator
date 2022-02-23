cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project(semantic-segmentation)

# Find the Ignition_Transport library
find_package(ignition-transport11 QUIET REQUIRED OPTIONAL_COMPONENTS log)
set(IGN_TRANSPORT_VER ${ignition-transport11_VERSION_MAJOR})
find_package(ignition-msgs8 QUIET REQUIRED)
find_package(ignition-rendering6 REQUIRED)

include_directories(${CMAKE_BINARY_DIR})

if (EXISTS "${CMAKE_SOURCE_DIR}/segmentation_node.cc")
  add_executable(segmentation_node segmentation_node.cc)
  target_link_libraries(segmentation_node ignition-transport${IGN_TRANSPORT_VER}::core)
endif()

if (EXISTS "${CMAKE_SOURCE_DIR}/spiral_movement.cc")
  add_executable(spiral_movement spiral_movement.cc)
  target_link_libraries(spiral_movement ignition-transport${IGN_TRANSPORT_VER}::core)
endif()
if (EXISTS "${CMAKE_SOURCE_DIR}/subscriber_pose.cc")
  add_executable(subscriber_pose subscriber_pose.cc)
  target_link_libraries(subscriber_pose ignition-transport${IGN_TRANSPORT_VER}::core)
endif()


if (EXISTS "${CMAKE_SOURCE_DIR}/random_walk_collision_avoidance.cc")
  add_executable(random_walk_collision_avoidance random_walk_collision_avoidance.cc)
  target_link_libraries(random_walk_collision_avoidance ignition-transport${IGN_TRANSPORT_VER}::core)
endif()


if (EXISTS "${CMAKE_SOURCE_DIR}/publish_random.cc")
  add_executable(publish_random publish_random.cc)
  target_link_libraries(publish_random ignition-transport${IGN_TRANSPORT_VER}::core)
endif()


if (EXISTS "${CMAKE_SOURCE_DIR}/msgs/")
  # Message generation. Only required when using custom Protobuf messages.
  find_package(Protobuf REQUIRED)
  add_subdirectory(msgs)
  set_source_files_properties(${PROTO_SRC} ${PROTO_HEADER} PROPERTIES GENERATED TRUE)
endif()


if (EXISTS "${CMAKE_SOURCE_DIR}/creator.cc")
  add_executable(creator creator.cc)
  target_link_libraries(creator
    ignition-transport${IGN_TRANSPORT_VER}::core)
  endif()
