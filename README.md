# Basic Voronoi Partitioner

"A Voronoi diagram is a partitioning of a plane into regions based on distances to points in a specific subset of the plane. That set of points (called seeds, sites, or generators) is specified beforehand, and for each seed there is a corresponding region consisting of all points closer to that seed than to any other. These regions are called Voronoi cells." (https://en.wikipedia.org/wiki/Voronoi_diagram)

A very basic voronoi partitioner written in C++ using the SDL2 graphics library.

It uses a brute force approach, which can result in a performance drop when there are over 20 sites present, although the application is great for illustration purposes.

# Dependencies
On Linux systems with the apt package manager:
```
sudo apt install libsdl2-dev libsdl2-gfx-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
```

# How to install
  1. Install the above dependencies.
  1. Clone the repo
  1. `cd ./voronoi`
  1. `cmake .` 
  1. `make`
  1. `./voronoi` to run the application

# Usage
Press `:` to acces a console-like interface, then type in a command.

Type `help` and press enter to check the functions available:

  - `help`     displays the help window
  - `save`     saves the Voronoi diagram as `output.bmp`
  - `nodes`    toggle display of nodes
  - `seeds`    toggle display of seeds
  - `sites`    toggle display of sites
  - `cap`      toggle capping the nr. of nodes at 16 on/off
  - `shuffle`  shuffle the position of the nodes
  - `clear`    clear all the nodes

# Examples
![without sites](https://i.imgur.com/Gf9FUSG.png)
![with sites](https://i.imgur.com/Y1YkAkH.png)


