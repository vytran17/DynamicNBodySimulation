# PS4: N-Body Simulation

## Contact
Name: Vy Tran
Section: 201
Time to Complete: 5 hours

## Description
The NBody simulation is a command-line application designed to simulate the motion of celestial bodies within a universe based on Newton's laws of motion and universal gravitation. This simulation employs a numerical integration method known as the "leapfrog" scheme to advance the positions and velocities of celestial bodies over time. The program reads the initial state of a universe from standard input, runs the simulation for a specified duration with a given time step, and outputs the final state of the universe.

### Features
- Scalable Universe: The simulation can handle a configurable number of celestial bodies, allowing for both small and large-scale simulations.
- Graphical Visualization: Utilizes SFML (Simple and Fast Multimedia Library) for rendering the simulation, providing a real-time visual representation of celestial movements.
- File Input: The initial state of the universe (positions, velocities, masses, and images of celestial bodies) can be loaded from a file, allowing for customizable simulations.
- Command-Line Interface: The application accepts two critical command-line arguments: the total simulation time (T) and the time step (∆t). This design allows for flexible simulation runs tailored to specific needs or inquiries.
- Leapfrog Integration Scheme: The leapfrog method is used for updating the positions and velocities of celestial bodies. This method is symplectic, making it particularly suitable for long-term simulations of gravitational systems due to its excellent energy conservation properties.
- Gravitational Forces Calculation: The program calculates the gravitational forces between all pairs of bodies using Newton's law of universal gravitation. This includes breaking down the forces into their x and y components based on the bodies' positions.

### Memory
Program is using auto storage duration for local variables and dynamic memory allocations for the vector of celestial bodies. SFML resources like textures and sounds are managed through their respective classes, which handle resource allocation and deallocation internally. There was no inherent need for smart pointers in simulation code. Smart pointer is used in main.cpp for demonstration purposes.

### Extra Credit
Elapsed time is displayed in window title. It shows it in appropriate units (seconds, days, or years). See screenshot.
