# LVEq: Lotka-Volterra equations - A simulation on C++ and OpenGL

## Purpose

This project is a C++ rewrite of [sy3c4ll/LVEq](https://github.com/sy3c4ll/LVEq.git).

This project aims to verify the accuracy of the Lotka-Volterra equations on the ecology dynamics of predator and prey species. 100 predators, 1,000 preys and 1,000 plants with hunger needs are simulated within a fixed world and their populations are measured and logged each frame. The measurements offer a more realistic outlook to the idealised Lotka-Volterra equations.

## Compiling

### Prerequisites

[OpenGL](https://www.opengl.org/) and [GLFW](https://www.glfw.org/) are needed to compile this project, with `pkg-config` support. `pkg-config` also needs to be locatable within `PATH`.

### On Linux

The Makefile has been configured to use `/usr/bin/c++` with `pkg-config` to automatically link to relevant versions of OpenGL and GLFW.

Running `make all` or simply `make` will compile and link the necessary files and place the executable in `build/lveq-cpp`.

Running `make clean` will clean the executable along with the `build/` folder.

## Usage

Running the compiled executable will render an OpenGL screen with species marked as coloured square dots in their respective locations, and also populate a `data.csv` on the same folder with time and species populations every frame.

Pressing Space will emit current populations to `stdout`. Pressing ESC will quit the simulation. `data.csv` is updated in real time.

## License

This project is licensed under the free and permissive [MIT license](https://github.com/sy3c4ll/lveq-cpp/blob/master/LICENSE).
