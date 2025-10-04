Simple Events Manager written in C++ using Qt 6 that presents both an admin and a user interface and offers mutliple options of repository type.

Requirements:
Visual Studio 2022
Qt 6.9.0
CMake 3.21+

To build the project, clone the repository and run the following commands:
1. cd Events-Manager
2. cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH="C:/Qt/6.9.0/msvc2022_64" (adjust CMAKE_PREFIX_PATH if your Qt is located somewhere else)
3. cmake --build build --config Release

After building, to use the project run:
build\Release\EventsManager.exe

If you see any missing DLL errors, either:

Add Qt to your Path (you can use set PATH=C:\Qt\6.9.0\msvc2022_64\bin;%PATH%)

or

Run the project from the Qt 6.9.0 (MSVC 2022 64-bit)



