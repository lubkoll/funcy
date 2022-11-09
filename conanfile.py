from conans import ConanFile, CMake
from conan.tools.files import get, copy
from conan.tools.layout import basic_layout
import os

required_conan_version = ">=1.50.0"


class FuncyConan(ConanFile):
    name = "funcy"
    version = "1.6.3"
    author = "Lars Lubkoll"
    description = ""
    url = "https://github.com/lubkoll/funcy"
    license = "GPL3"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "CMakeLists.txt", "include/*", "cmake/*"
    
    def layout(self):
        basic_layout(self)

    def package(self):
        print("hi")
        print(self.source_folder)
        cmake = CMake(self)
        cmake.configure()
        cmake.install()

    def package_id(self):
        self.info.clear()

    def package_info(self):
        self.cpp_info.includedirs = ["include"]
        self.cpp_info.set_property("cmake_file_name", "Funcy")
        self.cpp_info.set_property("cmake_target_name", "Funcy")

        # TODO: to remove in conan v2 once cmake_find_package* generators removed
        self.cpp_info.names["cmake_find_package"] = "Funcy"
        self.cpp_info.names["cmake_find_package_multi"] = "Funcy"
