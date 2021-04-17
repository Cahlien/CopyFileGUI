# specify the minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.19.7)

# specify the name of the project and its current version number
project(copyfile VERSION 1.0.0)

# look for wxWidgets and fail if it can't be found
find_package(wxWidgets REQUIRED)

# load and run the code from the convenience file, wxWidgets_USE_FILE
include(${wxWidgets_USE_FILE})

# create an executable with the same name as the project
add_executable(${PROJECT_NAME})

# specify the source files for the executable with the same name as the project 
target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)

# link the wxWidgets libraries to the executable with the same name as the project
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES})

# look for headers included in source code for specified executable in the src/include directory
target_include_directories(${PROJECT_NAME} PRIVATE src/include)
