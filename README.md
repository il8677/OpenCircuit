# OpenCircuit
A simple, lightweight electronic component simulator written in C++

[xor](https://user-images.githubusercontent.com/14109217/116185302-9f1a6a80-a721-11eb-8f87-3867d2232abb.mp4)

_An XOR gate made in open circuit_

## About
OpenCircuit aims to be an easy to use, transistor level circuit designer. Most circuit apps online are clunky, or overcomplicated just to fufill the purpose of playing around with transistors. This program allows you to build circuits from scratch, with nothing but wires and transitors. You can design your own logic gates and build up to a full CPU if wanted.

## Dependencies
To build you only need vcpkg set up.
This program is written in C++, using the SFML rendering framework and IMGUI for the user interface. All dependencies are either already in the source tree, or are configured to be downloaded.

## Building
### Windows
1. mkdir build
2. cd build
3. cmake ..
4. Open in visual studio and build the .exe target
### Linux
Who knows if this works
1. mkdir build
2. cd build
3. cmake ..
4. make