# OpenCircuit
A simple, lightweight electronic component simulator written in C++

## About
OpenCircuit aims to be an easy to use, transistor level circuit designer. Most circuit apps online are clunky, or overcomplicated just to fufill the purpose of playing around with transistors. This program allows you to build circuits from scratch, with nothing but wires and transitors. You can design your own logic gates and build up to a full CPU if wanted.

## Dependencies
This program is written in C++, using the SFML rendering framework and IMGUI for the user interface.

## Building
### Windows
1. Build or download the static libraries for SFML, the project will look in OpenCircuit\depen\SFML\lib
2. Run premake on the projects root directory specifying what program to create files for (e.g. vs2019)
3. Open and build

### Linux
1. Install SFML, either with your package manager or building it from source and placing the lib files in OpenCircuit/depen/SFML/lib and the headers in Opencircuit/depen/SFML/include
2. Run premake on the projects root directory, specifying what program to create files fro (e.g. gmake)
3. Run make
4. The binary is now in bin/Release/
