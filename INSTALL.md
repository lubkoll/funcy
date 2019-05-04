## Installation
funcy is header-only and requires no installation. To make it available in the local cmake-registry you still may find it useful install funcy using cmake.


### Install funcy via cmake
```
mkdir build
cd build
cmake .. -DBuildTest=ON -DCMAKE_INSTALL_PREFIX=<install-prefix>
cmake --build . --target install
```
### To include funcy in your project add this to your CMakeLists.txt:
```
find_package(funcy REQUIRED)
target_link_libraries(<target> PRIVATE funcy::funcy)
```
[back](README.md)