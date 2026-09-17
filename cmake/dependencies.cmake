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

#imgui backends
add_library(imgui_backends STATIC EXCLUDE_FROM_ALL
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui_backends/imgui_impl_glfw.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui_backends/imgui_impl_opengl3.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui_backends/imgui_impl_opengl3_loader.h"
)
target_include_directories(imgui_backends PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui_backends"
)
target_link_libraries(imgui_backends PUBLIC
        imgui::imgui
        glfw
)