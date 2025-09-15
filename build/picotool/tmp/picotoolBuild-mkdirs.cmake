# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/gm/Projects/PlatformIO/Projects/ChiamaCambio3/build/_deps/picotool-src"
  "/home/gm/Projects/PlatformIO/Projects/ChiamaCambio3/build/_deps/picotool-build"
  "/home/gm/Projects/PlatformIO/Projects/ChiamaCambio3/build/_deps"
  "/home/gm/Projects/PlatformIO/Projects/ChiamaCambio3/build/picotool/tmp"
  "/home/gm/Projects/PlatformIO/Projects/ChiamaCambio3/build/picotool/src/picotoolBuild-stamp"
  "/home/gm/Projects/PlatformIO/Projects/ChiamaCambio3/build/picotool/src"
  "/home/gm/Projects/PlatformIO/Projects/ChiamaCambio3/build/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/gm/Projects/PlatformIO/Projects/ChiamaCambio3/build/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/gm/Projects/PlatformIO/Projects/ChiamaCambio3/build/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
