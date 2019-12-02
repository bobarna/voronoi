# Basic Voronoi Partitioner

"A Voronoi diagram is a partitioning of a plane into regions based on distances to points in a specific subset of the plane. That set of points (called seeds, sites, or generators) is specified beforehand, and for each seed there is a corresponding region consisting of all points closer to that seed than to any other. These regions are called Voronoi cells." (https://en.wikipedia.org/wiki/Voronoi_diagram)

A very basic voronoi partitioner written in C++ using the SDL2 graphics library.

It uses a brute force approach, which can result in a performance drop when there are over 20 sites present, although the application is great for illustration purposes.

Press ":" to acces a console-like interface.
Type help and press enter to check the functions available:

  help     displays the help window
  save     saves the Voronoi diagram as output.bmp
  nodes  | 
  seeds  | toggle display
  sites  | 
  cap      toggle capping the nr. of nodes at 16 on/off
  shuffle  shuffle the position of the nodes
  clear    clear all the nodes



