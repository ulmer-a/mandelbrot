## Cross platform Mandelbrot fractal Renderer (OpenGL)

Current project status: incomplete

### Building

Make sure to do a recursive clone, so that you get all the submodule
source code as well.

`git clone --recursive https://github.com/ulmer-a/mandelbrot`

Build the project using `CMake`. To be able to run the application as
a standalone binary, all the support library sources are compiled into
static libraries and shipped with the program.

```
$ mkdir build
$ cd build
$ cmake ..
$ ./mandelbrot
```

### External libraries

* `cmdline`: C++20 command line parser (ulmer-a)
* `glm`: OpenGL maths library
* `glew`: OpenGL loader library (GPU interface)
* `glfw`: simple window and OpenGL context creation
