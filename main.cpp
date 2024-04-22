//  Copyright 2024 Vy Tran

#include <iomanip>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Universe.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " T deltaT" << std::endl;
        return 1;
    }

    // Parse command-line arguments
    double totalTime = std::stod(argv[1]);  // Total simulation time
    double deltaT = std::stod(argv[2]);  // Time step

    // Load a sound file into a buffer
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("assets/2001.wav")) {
        std::cerr << "Error loading sound file!" << std::endl;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.setLoop(true);
    sound.play();

    // Load universe from standard input
    std::unique_ptr<NB::Universe> universe = std::make_unique<NB::Universe>();
    std::cin >> *universe;
    // std::cout << "Initialized universe: " << universe << std::endl;

    // Create a render window with a specified size
    sf::RenderWindow window(sf::VideoMode(800, 800),
    "NBody Simulation", sf::Style::Titlebar | sf::Style::Close);

    const double secondsPerDay = 86400.0;
    const double secondsPerYear = 31536000.0;
    double elapsedTime = 0;
    while (window.isOpen() && elapsedTime < totalTime) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        // Draw the universe
        window.draw(*universe);
        window.display();
        universe->step(deltaT);

        // Update window title with elapsed time
        std::ostringstream titleStream;
        if (elapsedTime < secondsPerDay) {
            // Display in seconds if less than a day
            titleStream << "NBody Simulation - Time: " << std::fixed << std::setprecision(2)
                        << elapsedTime << " s";
        } else if (elapsedTime < secondsPerYear) {
            // Convert to days and display if more than a day but less than a year
            double days = elapsedTime / secondsPerDay;
            titleStream << "NBody Simulation - Time: " << std::fixed << std::setprecision(2)
                        << days << " days";
        } else {
            // Convert to years and display if more than a year
            double years = elapsedTime / secondsPerYear;
            titleStream << "NBody Simulation - Time: " << std::fixed << std::setprecision(2)
                        << years << " years";
        }
        window.setTitle(titleStream.str());
        elapsedTime += deltaT;
    }

    std::cout << *universe << std::endl;
    return 0;
}
