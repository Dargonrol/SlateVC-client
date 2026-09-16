cmake_minimum_required(VERSION 3.23)
project(DiscordClone VERSION 0.6 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(options)
include(dependencies)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
        "src/*.cpp" "src/*.h" "src/*.hpp" "src/*.c"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw
        glad
        imgui::imgui
)

include(compiler_warnings)
enable_warnings("${PROJECT_NAME}")