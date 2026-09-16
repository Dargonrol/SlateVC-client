# external packages via conan
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# glad
add_library(glad STATIC EXCLUDE_FROM_ALL
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/src/glad.c"
)

target_include_directories(glad PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
)