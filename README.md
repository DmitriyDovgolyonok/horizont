## How to build.
Requirements:
* CMake
* GCC/Clang
* Visual Studio 2022(for Windows)
### Linux 
```bash
git clone https://github.com/DmitriyDovgolyonok/horizont.git ./horizont
cd horizont
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Windows
Open x86_x64 Cross Tools Command Prompt 
```bash
git clone https://github.com/DmitriyDovgolyonok/horizont.git ./horizont
cd horizont
mkdir build
cd build
cmake ..
cmake --build . --config Release
cd Release
```
PS: Use the Latin alphabet in files ;)
