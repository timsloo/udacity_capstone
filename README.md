# Capstone Project: PacMan

This is the repository of the final Capstone project which is part of the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).
It was built upon the provided [Snake starter pack repository](https://github.com/udacity/CppND-Capstone-Snake-Game).

## How to play the game 
This repository provides a simple version of the well-known PacMan game. The pac man is controlled via the arrow keys on the keyboard. 
The game's goal is to collect all points and the score is indicated in the window title. One may not collide with the blue ghosts that randomly 
move through the map. 

## Overview of File Structure

### cmake/ 
Includes CMake files for building the project.

### src/ 
Includes all source files for the project. 

### maps/ 
Includes .txt files which define the map. The '#' symbol stands for a wall, '-' represents a point (+10 score when collecting it) and an empty space for no static object.  

## Overview of Code Structure
### `Controller`
The controller class handles user events such as key presses and adjusts the direction of the corresponding `DynamicGameElement` (here: instance of `PacMan`) accordingly. 

### `DynamicGameElement`
This class is a superclass for both subclasses `PacMan` and `Ghost` as they share many attributes and behaviours such as their position within the grid, speed, and moving direction.
It inherits from the pure virtual class `Renderable` but does not implement the `Renderable::Render` method. Hence, its subclasses are required to do so. 

### `Game`
This is the central class which runs the Input / Update / Render loop within the function `Game::Run`. Furthermore, it keeps references to all `DynamicGameElement` instances. 

### `Ghost`
This class inherits from `DynamicGameElement`. Hence, it implements the `Renderable::Render` function to display the ghost. 
It also implements the `Update` method which handles the movement of the ghost depending on its state and the map. Unlike the `PacMan` class, the movement direction is 
not given by a `Controller` but an own strategy is used to navigate randomly in the map. 

### `main.cpp`
This file includes the main-function and defines game and render settings. 

### `Map`
This class owns a 2D grid defining the static environment (empty, Wall, Point, ...) and provides clear access functions for other classes. The method `Map::readMapFromFile` reads text files from the maps/ folder and builds the grid based on the input file.
`Map` also implements the `Renderable` interface to display all static elements. 

### `PacMan`
This class inherits from `DynamicGameElement`. Hence, it implements the `Renderable::Render` function to display the pac man symbol.
This class also implements the `Update` method which handles the movement of the pac man based on the state of the Map and his moving direction (which is set by the `Controller` class).

### `Renderable`
To simplify the `Render` class and further decouple it from the specific game that is implemented, this interface class defines a common method `Renderable::Render`. 
All elements that need to be displayed, have to implement this method. This specifically holds for the subclasses of `DynamicGameElement` and `Map`.

### `Renderer`
This class constructs the window and displays all game elements by calling the objects corresponding `Renderable::Render` function. 

## How this project satisfies the rubric 

### Loops, Functions, I/O 
#### The project demonstrates an understanding of C++ functions and control structures. 
Helper functions are used in the whole codebase. A good example for using control structures and splitting code into suitable 
subroutines can be found in `Ghost::Update`. 

#### The project reads data from a file and process the data, or the program writes data to a file.
The method `Map::ReadMapFromFile` reads a textfile and constructs the 2D grid accordingly. 

#### The project accepts user input and processes the input.
The method `Controller::HandleInput` evaluates user events and changes the movement of the pac man depending on that input. 

### Object Oriented Programming

#### The project uses Object Oriented Programming techniques.
This should be obvious.

#### Classes use appropriate access specifiers for class members.
Some example classes that make use of this: `Ghost`, `DynamicGameElement`, `Map`. 

#### Class constructors utilize member initialization lists.
The following classes utilize member initialization list: `DynamicGameElement`, `Game`, `Ghost`, `Map` and `PacMan`

#### Classes abstract implementation details from their interfaces. 
and
#### Classes encapsulate behavior.
These holds for all classes. One example is the `Map` class which hides the memory management of the 2D grid from the user. 

#### Classes follow an appropriate inheritance hierarchy.
Examples: `DynamicGameElement` is the superclass of both `PacMan`and `Ghost`. The pure virtual class `Renderable` defines the interface to render elements. 

#### Overloaded functions allow the same function to operate on different parameters.
Example: The function `Map::at` is overloaded. 

#### Derived class functions override virtual base class functions.
Example: `PacMan` and `Ghost` override the pure virutal function `Renderable::Render`. 

### Memory Management 

#### The project makes use of references in function declarations.
References are used several times, for example in `PacMan::Update` or in `Map::at`. 

#### The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
Used for all statically allocated resources in the code. 

#### The project follows the Rule of 5.
See class `Map`. 

#### The project uses move semantics to move data, instead of copying it, where possible.
This principle is explicitely used to move the instance of `Map` from the main function to the `Game` instance. It is also implicitly used whenever stl containers 
such as vectors are used. 

#### The project uses smart pointers instead of raw pointers.
Shared pointers are used for the `PacMan` instance as well as all `Ghost` instances which are managed inside the `Game` object.


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./PacManGame`.

## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
