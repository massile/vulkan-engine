cmake_minimum_required(VERSION 3.7.1)
set(ProjectName "vulkan-engine")
project(${ProjectName})

# Windows specific define
add_definitions(-DVK_USE_PLATFORM_WIN32_KHR)

# /!\ Path to the vulkan API (TO EDIT depending on the platform)
set(VULKAN_PATH "C:/VulkanSDK/1.1.97.0")
include_directories(AFTER ${VULKAN_PATH}/Include)
link_directories(${VULKAN_PATH}/Bin)
set(VULKAN_LIB_LIST "${VULKAN_PATH}/Lib/vulkan-1.lib")

# Source files to compile
source_group("include" REGULAR_EXPRESSION "include/*")
source_group("src" REGULAR_EXPRESSION "src/*")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB_RECURSE CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.*)

# Compile everything
add_executable(${ProjectName} ${CPP_FILES} ${HPP_FILES})
target_link_libraries(${ProjectName} ${VULKAN_LIB_LIST})

# Output directories
set_property(TARGET ${ProjectName} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set_property(TARGET ${ProjectName} PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/build)
set_property(TARGET ${ProjectName} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/build)
set_property(TARGET ${ProjectName} PROPERTY RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_SOURCE_DIR}/build)
set_property(TARGET ${ProjectName} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/build)

# C++ version to use
set_property(TARGET ${ProjectName} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${ProjectName} PROPERTY CXX_STANDARD_REQUIRED ON)
