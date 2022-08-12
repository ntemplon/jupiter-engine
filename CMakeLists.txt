# Experimenting with PackageName_ROOT to help direct to a sphinx installation in the virtual environment,
#  which requires 3.12
cmake_minimum_required(VERSION 3.12.0)

# Set Project Name and Version
project(JupiterGameEngine VERSION 0.1.0)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
message(STATUS "SRC_FILES=${SRC_FILES}")
# This defines a build target called "Application" that makes an executable out of these source files
add_library(libjupiter-engine ${SRC_FILES})
# Specify that the libjupiter-engine target will use C++14
set_property(TARGET libjupiter-engine
             PROPERTY C_STANDARD 14
)
set_property(TARGET libjupiter-engine
    PROPERTY CXX_STANDARD 14
)

# Put the Find*.cmake files at ./cmake onto the module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# Add the ./include directories to the build path so header files and images are available
target_include_directories(libjupiter-engine PUBLIC ${PROJECT_SOURCE_DIR}/include/)
target_include_directories(libjupiter-engine PUBLIC ${PROJECT_SOURCE_DIR}/include/event/)
target_include_directories(libjupiter-engine PUBLIC ${PROJECT_SOURCE_DIR}/include/entity/)

# Load SFML. MODULE is used to force usage of the FindSFML.cmake file over the .config file that comes
#  with the SFML installation from the Ubuntu 22.04 repositories.
find_package(SFML 2.5 MODULE COMPONENTS system window graphics REQUIRED)

# Specify that what is found by the SFML find above should be linked to the RunMe target as a public dependency
target_link_libraries(libjupiter-engine PUBLIC ${SFML_LIBRARIES})