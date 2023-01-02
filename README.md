# mini_3D_game
A 3D game inspired by Wolfenstein's 3D, built using C and raycasting.

## getting started
This project is inspired by the world-famous eponymous 90's games (Doom, Wolfenstein's 3D), and a great project to explore ray casting 
### - why is this project useful ?
As a graphic design project, this project will enable you to improve skills in these areas : windows, colors, events, fill shapes, etc.
and it's remarkable playground to explore the playful practical applications of mathematics.
## Prerequisites
 - [Minilibx library](https://github.com/42Paris/minilibx-linux)
 - gcc
 - make
## Installing
  - clone the repository
  - ``` cd mini_3d_game ```
  - ``` make ```
## Running the game
  - ``` ./cub3D maps/*.cub ```
## the project Constraints
  - The management of your window must remain smooth: changing to another window, minimizing, etc.
  - Display different wall textures (the choice is yours) that vary depending on which
  side the wall is facing (North, South, East, West).
  - Your program must be able to set the floor and ceiling colors to two different ones.
## game control
  - the left and right arrow keys of the keyboard and the left/right keys of the mouse, allow you to look left and right of tha maze.
  - the W, A, S, and D keys allow you to move the point of view through the maze.
  - pressing ESC close the window and quit the program cleanly
  - clicking on the red cross on the window's frame close the window and quit the program cleanly
## map management

  - The map must be composed of only 6 possible characters: 0 for an empty space,
  1 for a wall, and N,S,E or W for the player’s start position and spawning
  orientation.
  - The map must be closed/surrounded by walls, if not the program must return
an error.
  - Except for the map content, each type of element can be separated by one or
more empty line(s).
  - Except for the map content which always has to be the last, each type of
element can be set in any order in the file.
  - Except for the map, each type of information from an element can be separated
by one or more space(s).
  - The map must be parsed as it looks in the file. Spaces are a valid part of the
map as long as they're not surrounded by a player or a '0'
