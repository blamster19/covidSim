[![MIT license](https://img.shields.io/badge/License-MIT-blue.svg)](https://lbesson.mit-license.org/)
# covidSim
Simple pandemic simulator project for an assignment. NOTE: "covidSim" is just the subject of an assignment and in no way relates to real event.

## Table of contents
* [General](#general)
* [Dependencies](#dependencies)
* [Compilation](#compilation)
* [Usage](#usage)
* [Examples](#examples)
* [License](#license)

## General
The simulation takes place in a square representing a city. Inside there are dots representing people, with varying velocities, directions and radii, travelling in straight lines and bouncing off the boundaries. Color of a dot represents its state: green is healthy, red is infected, blue is recovered. Infected people infect healthy people, while recovered people do not infect and cannot be infected.
The program outputs series of frames in PNG format into `plots/` directory. If `--doFrames` option is passed on start, the frames are merged into an animated GIF `animation.gif` and PNG frames are deleted.

## Dependencies
- The program depends on an external library `deps/Plotter.h` provided with the assignment and written by someone else. The library in turn depends on `<Python.h>`, but this is beyond the scope of this README. It is a kind of Matplotlib wrapper, but I intentionally wrote the simulator to be as independent of image generation as possible, so it should be relatively easy to substitute its few calls with something else.
- The program calls `mergeFrames.py` script provided with the assignment to merge frames generated with `Plotter.h` into animated GIF. You can change this call to something else, like `convert` from ImageMagick suite.
- The program utilizes C++14 functionality and assumes the use of g++. The code should compile with any other modern compiler, but none besides g++ has been tested.

## Compilation
To compile covidSim, `cd` into the project directory and type:
```
$ make
```
The Makefile is written with external dependencies in mind. If you wish to use some other plotter, you can delete `-I/usr/include/python3.9 -lpython3.9` from `CPPFLAGS` variable, remove `obj/Plotter.o` in `OBJS` variable and remove `obj/Plotter.o` compilation part (last two lines).
The binary file will be created in `bin/covidSim`.

## Usage
To use the program, run it in the terminal:
```
$ ./bin/covidSim
```
You have to supply argument(s) to execute the binary. The mandatory argument is `-i` or `--input`, which specifies the source of population to generate. It accepts options: `random`, generates random population of 50, `test`, generates hardcoded population of 3 and `file`, generates population from file. For more information, simulation parameters and output options, pass `-h`, or `--help`.
Input file must be named `input_config` and be placed in the project directory. The data of one person is provided in the following format:
```
[x] [y] [vx] [vy] [radius] [color]
```
where `[vx]`, `[vy]` are person's x and y velocity, and `color` is _red_, _green_ or _blue_. It is not required, but advised to put one person in one line. The values are separated with whitespace characters.
Example file below:
```
0.1 0.2 0.1 0.2 0.002 green
0.1 0.1 0.5 0.3 0.005 green
0.2 0.1 0.3 0.6 0.003 red
```

## Examples
### Generate random population and save animation to GIF
```sh
$ ./bin/covidSim --input random --doFrames true
```
### Load population from file and change number of iterations to 25
```sh
$ ./bin/covidSim --input file --nIter 25
```
### Preview what the simulator does in detail
```sh
$ ./bin/covidSim --Verbose
```

## License
 The MIT License (MIT)

 Copyright © 2022 blamster19

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
