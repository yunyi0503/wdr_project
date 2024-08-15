cmake_policy(SET CMP0009 NEW)
cmake_minimum_required(VERSION 3.8)
project(ros_7489)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(turtlesim REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2 REQUIRED)
find_package(geometry_msgs REQUIRED)  # 确保添加这个依赖

# Specify the executable and its dependencies
add_executable(spawn_jerry src/spawn_jerry.cpp)
ament_target_dependencies(spawn_jerry rclcpp turtlesim)

add_executable(subscribe_jerry_position src/subscribe_jerry_position.cpp)
ament_target_dependencies(subscribe_jerry_position rclcpp turtlesim)

add_executable(rotate_jerry src/rotate_jerry.cpp)
ament_target_dependencies(rotate_jerry rclcpp turtlesim geometry_msgs)  # 添加对 geometry_msgs 的依赖

add_executable(follow_jerry src/follow_jerry.cpp)
ament_target_dependencies(follow_jerry rclcpp turtlesim tf2_ros tf2 geometry_msgs)

add_executable(broadcast_tf src/broadcast_tf.cpp)
ament_target_dependencies(broadcast_tf rclcpp tf2_ros turtlesim)

add_executable(set_background_color src/set_background_color.cpp)
ament_target_dependencies(set_background_color rclcpp turtlesim)


# Install the executables
install(TARGETS
  spawn_jerry
  subscribe_jerry_position
  rotate_jerry
  follow_jerry
  broadcast_tf
  set_background_color  # 添加 set_background_color 到安装目标
  DESTINATION lib/${PROJECT_NAME}
)

# Install the launch directory
install(DIRECTORY
  launch/
  DESTINATION share/${PROJECT_NAME}/
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
