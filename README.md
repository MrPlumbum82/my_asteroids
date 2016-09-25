# My Asteroids

![screenshot](https://cloud.githubusercontent.com/assets/11234396/18334742/4990e3f6-7593-11e6-8c87-1317ab1f7d60.png)

This is an asteroids game written in OpenGL. More needs to be added, additional information about the TODO below.

##TODO
 * Implement a menu system
 * Add music/sound effects to the menus and game
 * Add more ship types
 * Add more weapon types
 * Add more obstacles

##How to run:

###Linux:
 1. Install opengl, glut and soil libraries
 ```bash
  sudo apt-get install freeglut3-dev libsoil-dev
 ```

 2. Clone the repository
 
 ```bash
  git clone https://github.com/MrPlumbum82/my_asteroids
 ```

 3. Compile
 
 ```bash
  g++ -std=c++11 asteroids.cpp -lGL -lGLU -lglut -lSOIL
 ```
 
 4. Execute
 
 ```bash
  ./a.out
 ```

###Windows:
 1. Clone the repository
 2. Install Visual Studio 2013
 3. Open project in Visual Studio
 4. Run project in Visual Studio
