# Newtonian Gravity Simulator

A simple simulation of planetary motion using Newtonian Physics and SDL2 for visualization. Designed for educational purposes and quick experimentation with gravity simulations.

This project is coded entirely in C++ and requires you to have SDL2, SDL-ttf, and SDL_image. Below is how to install and use the program

# Cloning the repository

If you would like to clone the repository:
```bash
git clone https://github.com/Areeb-Rehman05/Newtonian-Gravity-Simulation
```
Install the following dependencies:
- SDL2
- SDL2_ttf
- SDL2_image
- Eigen3

Build the project using CMake.

# Downloading the program without cloning

If you don't want to clone the repository you can also download the release build. Simply navigate to the releases page and find the desired version and download the .zip. Extract the folder and navigate to solarSim and run solarSim.exe (Currently this is only for windows installations)

# Usage

At first it will ask you the Sun Mass and the desired amount of bodies in your simulation.

The Sun is not a true celestial body that can move on its own, rather its the gravitational pull towards the center of the screen, hgiher mass means more pull towards the center of the screen.

<img width="1420" height="878" alt="image" src="https://github.com/user-attachments/assets/bb8a9273-5d99-4835-9a48-89ce8c0650fc" />

The next screen will ask you to add new bodies to the simulation with their x,y position and vectors. It's important to note that each unit is a pixel away from the center so any x value above 720 and y value above 450 would not be visible. The preview at the bottom is meant to show the user a general idea of where each body will be with the size of each body increasing relative to its mass. Scale also increases to match the largest distance body(default is 100).

<img width="1363" height="855" alt="image" src="https://github.com/user-attachments/assets/accc0b7f-1e7e-4fce-a6aa-c3132d9042aa" />

Finally when you add the final body the simulation will begin and all the bodies you added will begin interacting with one another. Below is a picture showing 4 celestial bodies orbiting with two of them colliding and pinging off each other.

<img width="1418" height="879" alt="image" src="https://github.com/user-attachments/assets/7823bbd5-981c-45c7-8e18-f119f887027d" />

