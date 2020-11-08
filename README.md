# Marching Cubes with OpenGL

By [dgr582.com](www.dgr582.com).

&copy; 2020 DGR582 Ltd

This repo is a companion to the article [Marching Cubes with OpenGL](www.dgr582.com/articles/2020/marching-cubes). For more detail, check out the article.

If you have an issue, see the [contact details here](www.dgr582.com/contact) or send over a message on [discord](https://discord.gg/2VVXRBz).


# Running the code

You will need to download and install [CMake](https://cmake.org/).

If you want to change their versions, you can download [GLFW from here](https://www.glfw.org/) and [GLAD from here](https://glad.dav1d.de/).

The code has been tested with Visual Studio 2019. The code itself should be cross-platform (but I didn't check!).

## Setup

To change the GLFW library:
1. Download [GLFW](https://www.glfw.org/).
2. Download an OpenGL extension loader from [here](https://glad.dav1d.de/). To do this, set gl API to at least 3.3 or higher. The other API's can be left as none. Set the profile to `Core`. Click generate and download then the zip file.
3. Extract the downloaded glfw zip (at the time of writing, this is `glfw-3.3.2.zip`) into `libs`.
4. The next step is to extract the contents of the `glad.zip` file into `libs/glfw-3.3.2/glfw-3.3.2/deps`. For gl version 4.6, when this done you should have copied:
    * The folder `KHR` into `deps`
    * The file `glad.h` into `deps/glad`
    * The file `glad.c` into `deps/src`


### Preparing to compile

Note that you can modify the GLFW compile options by following the [official guide](https://www.glfw.org/docs/latest/compile_guide.html).

To build, the basic pattern is to go to the `marchingCubes/build` directory and run `cmake ..`.

If the `build` directory isn't there, you should create it first.

Then run:
```shell
$ cd build
$ cmake ..
```
(Note that on Windows, if you want a 64-bit build you should run `cmake -DCMAKE_GENERATOR_PLATFORM=x64 ..` instead!).

The easiest thing to do if anything goes wrong is to just delete the contents of `build` and try again.

You can run `cmake` from anywhere, as long as the second argument points to the directory that the file CMakeLists.txt is in.

### Running on Windows

On Windows, running CMake (from build) will create Visual Studio project in the `build` directory. Open the project file in Visual Studio (by opening `marchingCubes.sln`).

Run the program `main` in the `marchingCubes.sln` and hope fully everything should just run.

### Getting help

If you get stuck, see the [contact details](www.dgr582.com/contact) or send over a message on [discord](https://discord.gg/2VVXRBz).
