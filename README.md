# Pong Final Project

## Rubric

### The project demonstrates an understanding of C++ functions and control structures.
There are while loops and if statements.

### The project uses Object Oriented Programming techniques.
Classes for paddles and the ball.

### Classes use appropriate access specifiers for class members.
Ball class has public as well as private members.

### Overloaded functions allow the same function to operate on different parameters.
Both classes have overloaded constructor.

### Classes encapsulate behavior.
Implementation of class behaviour is hidden from the user.



## Dependencies

- [Git][]
- C Compiler (gcc, ...)
- [CMake][]
- [SDL2][SDL] library
- [SDL2_ttf][] library

**On Debian/Ubuntu based distributions, use the following command:**

```sh
sudo apt install git build-essential pkg-config cmake cmake-data libsdl2-dev libsdl2-ttf-dev
```

## Build instructions

```sh
# Clone this repo
git clone https://github.com/JFaustoGC/final-capstone
cd sdl2-ttf-sample

# Create a build folder
mkdir build
cd build

# Build
cmake ..
make

# Run
./sdl2-ttf-sample
```
