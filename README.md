# Mute Filter Plugin for OBS Studio

## Introduction

This plugin will discard audio of a source.

Even though a user muted a source in the mixer of OBS Studio,
the source sometimes triggers OBS Studio to add more audio buffers.
```
adding 21 milliseconds of audio buffering, total audio buffering is now 85 milliseconds (source: cam3)
```
It should not cause any problem but it's better to avoid unnecessary process.

This plugin provides two filter types;
1. Discard Audio --
   This filter will just discard all audio data from the source.
2. Discard Audio by UI --
   This filter will discard audio data from the source while the source is muted in the mixer.

## Properties

No property is provided.

## Build and install
### Linux
Use cmake to build on Linux. After checkout, run these commands.
```
sed -i 's;${CMAKE_INSTALL_FULL_LIBDIR};/usr/lib;' CMakeLists.txt
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_INSTALL_LIBDIR=/usr/lib ..
make
sudo make install
```
You might need to adjust `CMAKE_INSTALL_LIBDIR` for your system.

### macOS
Build flow is similar to that for Linux.
