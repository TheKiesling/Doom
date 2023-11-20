# Raycasting Game

https://github.com/TheKiesling/CG-Project-Doom/assets/84196494/ca278bbb-3b53-4b02-b09c-e0dc09cb2bdc

## Overview

This project is a raycasting game developed in C++ that recreates a 3D environment using the raycasting rendering technique. The game simulates a first-person view where the player navigates through a maze-like world. The project aims to replicate the graphical style of classic games like Wolfenstein 3D.

### Screenshots

| ![image](https://github.com/TheKiesling/CG-Project-Doom/assets/84196494/849623d8-c987-4937-b948-2a30e2112d25) | ![image](https://github.com/TheKiesling/CG-Project-Doom/assets/84196494/60e8318d-97d4-424c-9892-7f2c8cb163bf) |
|------------  | -------------  |
![image](https://github.com/TheKiesling/CG-Project-Doom/assets/84196494/ce6f6a33-8129-401e-8fa6-57d669402f6d) | ![image](https://github.com/TheKiesling/CG-Project-Doom/assets/84196494/d1428221-a2e7-4760-9144-38ed2b8348d3)
| ![image](https://github.com/TheKiesling/CG-Project-Doom/assets/84196494/dc1610b5-35f5-48b2-8aef-9c7ca5b46c1e) | ![image](https://github.com/TheKiesling/CG-Project-Doom/assets/84196494/79a9cf9b-04ee-47e4-b871-97a99fb7f5ba) |  

## Getting Started

Follow these steps to get the raycasting game running on your local machine:

1. Clone this repository to your local machine.
2. Ensure you have a C++ development environment set up, including the required libraries, such as SDL2.
3. Build the project using your preferred C++ development tools or compile it using a C++ compiler.

## Prerequisites

Make sure you have the following installed before running the project:

- **C++ Development Environment:** Ensure you have a C++ development environment configured on your system.
- **SDL2:** You can get it in https://github.com/libsdl-org/SDL/releases
- **SDL2_image:** You can get it in https://github.com/libsdl-org/SDL_image/releases. (Take care to download the developer version)

## Features

- **Raycasting Rendering:** Utilizes raycasting techniques to render a 3D-like environment.
- **First-person Perspective:** Offers a first-person view for the player to explore the game world.
- **Interactive Controls:** Allows movement and interaction within the game environment.
- **Map Loading:** Loads maps from files to create diverse gaming environments.
- **Dynamic Textures:** Renders textures onto walls based on the map and player location.

## Project Structure

- `main.cpp`: Entry point for the application.
- `raycaster.h`: Contains the raycasting logic and rendering.
- `imageloader.h`: Handles image loading and manipulation.
- `color.h`: Defines color structures and utilities.

## Usage

- Run the game executable after building the project.
- Navigate through the environment using the arrow keys or other specified controls.
- Interact with the environment based on the game's mechanics (if any).

## Contributing

Contributions to improve the game or add new features are welcome! Follow these steps:

1. Fork the repository.
2. Create a new branch: `git checkout -b feature/new-feature`.
3. Make your changes and commit them: `git commit -m 'Add a new feature'`.
4. Push to the branch: `git push origin feature/new-feature`.
5. Open a pull request.

## License

This project is licensed under the [MIT License](LICENSE).
