# Header library for Waveshare Jetank running on Jetson Nano


## Table of Contents

- [Requirements](#requirements)
- [Setup](#setup)
- [Usage](#usage)
- [Program Description](#program-description-and-assumptions)
- [Maintainers](#maintainers)


## Usage
This program is intended to provide a low latency interface to the Waveshare Jetank robot on the Nvidia Jetson Nano, by using C++ to control the movement.

## Program Description and assumptions
The motor interaction are provided as headers files in ![](./Jetank) folder and the ![](./demo.cpp) file is provide as a demonstration to the capability of the library. The demo program can be compiled via CMake. An automated build script for this demo program is included (demo_launch).

## Requirements

Requires `gcc` and `cmake`.

## Setup

	$ run the `demo_launch` script

	---

	OR;

	---

    $ mkdir build
    $ cd build
    $ cmake ../
    $ make
    $ ./main

# Maintainers
- Ole Kjepso [@olemikole](https://github.com/olemikole)
- Christian Danø [@varuld](https://github.com/varuld)
- Tellef Østereng [@tellefo92](https://github.com/tellefo92)
