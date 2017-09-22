# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             extmath

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/DumbCalc.cpp
             src/ExtMath.cpp)


set(CMAKE_CXX_FLAGS
   "${CMAKE_CXX_FLAGS} -std=c++0x -O2 -D_FORTIFY_SOURCE=2 -fstack-protector-all -fPIE")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pie")
