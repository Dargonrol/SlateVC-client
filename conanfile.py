from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMakeToolchain

class Project(ConanFile):
    name = "project"
    version = "0.1"

    settings = "os", "compiler", "build_type", "arch"

    requires = (
        "glfw/3.4",
        "imgui/1.92.9b-docking",
    )

    def configure(self):
        self.options["imgui"].with_glfw = True
        self.options["imgui"].with_opengl3 = True

    generators = ("CMakeDeps",)

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.user_presets_path = "CMakeUserPresets.json"
        tc.presets_prefix = ""
        tc.generate()