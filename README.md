# OpenCircuit
A simple, lightweight electronic component simulator written in C++

## About
OpenCircuit aims to be an easy to use, transistor level circuit designer. Most circuit apps online are clunky, or overcomplicated just to fufill the purpose of playing around with transistors. This program allows you to build circuits from scratch, with nothing but wires and transitors. You can design your own logic gates and build up to a full CPU if wanted.

## Dependencies
This program is written in C++, using the SFML rendering framework and IMGUI for the user interface.

## Building
Only configured for windows so far
1. Build the static libraries for SFML
2. Run premake on the projects root directory specifying the relevant action (e.g. vs2019)
3. Build
