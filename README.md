# OBS Mute Filter Plugin

## Introduction

This plugin to mute audio of a source.

Even though a user muted a source in the mixer of OBS Studio,
the source sometimes triggers OBS Studio to add more audio buffers.
```
adding 21 milliseconds of audio buffering, total audio buffering is now 85 milliseconds (source: cam3)
```
It should not cause any problem but it's better to avoid unnecessary process.

## Properties

No property is provided.

## Build and install
### Linux
Use cmake to build on Linux. After checkout, run these commands.
```
sed -i 's;${CMAKE_INSTALL_FULL_LIBDIR};/usr/lib;' CMakeLists.txt
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr ..
make
sudo make install
```

### macOS
Build flow is similar to that for Linux.
