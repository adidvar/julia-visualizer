from conan import ConanFile

class Recipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps", "VirtualRunEnv"

    def layout(self):
        self.folders.generators = "conan"

    def requirements(self):
        self.requires("opengl/system")
        self.requires("glfw/3.4")
        self.requires("glm/1.0.1")

    def build_requirements(self):
        self.test_requires("catch2/3.7.1")
