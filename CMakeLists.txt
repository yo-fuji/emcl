cmake_minimum_required(VERSION 3.8)
project(emcl)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

ament_auto_add_library(Pose SHARED src/Pose.cpp)
ament_auto_add_library(Scan SHARED src/Scan.cpp)
ament_auto_add_library(LikelihoodFieldMap SHARED src/LikelihoodFieldMap.cpp)
ament_auto_add_library(OdomModel SHARED src/OdomModel.cpp)
ament_auto_add_library(Particle SHARED src/Particle.cpp)
ament_auto_add_library(Mcl SHARED src/Mcl.cpp)
ament_auto_add_library(ExpResetMcl SHARED src/ExpResetMcl.cpp)
ament_auto_add_library(mcl SHARED src/mcl_node.cpp)
ament_auto_add_library(emcl SHARED src/emcl_node.cpp)

rclcpp_components_register_node(mcl
  PLUGIN "emcl::MclNode"
  EXECUTABLE mcl_node)
rclcpp_components_register_node(emcl
  PLUGIN "emcl::EMclNode"
  EXECUTABLE emcl_node)
target_compile_features(mcl PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_compile_features(emcl PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(mcl PRIVATE "EMCL_BUILDING_LIBRARY")
target_compile_definitions(emcl PRIVATE "EMCL_BUILDING_LIBRARY")

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_auto_package(INSTALL_TO_SHARE config)
