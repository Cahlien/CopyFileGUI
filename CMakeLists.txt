cmake_minimum_required(VERSION 3.19.7)

set(CMAKE_CXX_COMPILER /usr/bin/g++)

project(copyfile VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-fabi-version=15 -fno-exceptions -O3)

if(${CMAKE_HOST_WIN32})
	set(${PROJECT_NAME}_SYSTEM_FLAGS "WIN32")
endif()

find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SYSTEM_FLAGS})
target_sources(${PROJECT_NAME} PRIVATE src/copyapp.cpp src/guimanager.cpp src/copier.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES} Threads::Threads)
target_include_directories(${PROJECT_NAME} PRIVATE src/include)
