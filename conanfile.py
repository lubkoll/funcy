from conans import ConanFile, CMake
from conan.tools.files import get
from conan.tools.layout import basic_layout

required_conan_version = ">=1.50.0"


class BoostConan(ConanFile):
    name = "funcy"
    version = "1.6.4"
    author = "Lars Lubkoll"
    description = ""
    url = "https://github.com/lubkoll/funcy"
    license = "GPL3"
    settings = "os", "arch", "compiler", "build_type"

    def layout(self):
        basic_layout(self)

    def source(self):
        get(self, "https://github.com/lubkoll/funcy/archive/refs/tags/v1.6.4.tar.gz")

    def package(self):
        cmake = CMake(self)
        cmake.configure(source_folder=f'{self.source_folder}/funcy-1.6.4')
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
