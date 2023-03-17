To build this project you'll need CMake, which you can download [here](https://cmake.org/download/), and a C++ compiler, such as MSVC, which you can get with Visual Studio

**Make sure you're building in 32 bit mode**, as gd (atleast the windows version) is 32 bit, meaning your dll has to be too.

### Build
1. Configure (you only need to do this when editing the cmake file, or adding new cpp files)
``` bash
cmake -B build -A win32
```
2. Build
```bash
cmake --build build --config Release
```
