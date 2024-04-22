//  Copyright 2024 Vy Tran

#include "Universe.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

namespace NB {
    const double G = 6.67e-11;  // Gravitational constant

    Universe::Universe() : mRadius(0) {
        if (!backgroundTexture.loadFromFile("assets/starfield.jpg")) {
            std::cerr << "Failed to load background image" << std::endl;
        }
    }

    Universe::Universe(const std::string& filename) : Universe() {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }
        file >> *this;
        file.close();
    }

    void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        sf::Sprite backgroundSprite;
        backgroundSprite.setTexture(backgroundTexture);

        // Get the size of the target window and the texture
        sf::Vector2u windowSize = target.getSize();
        sf::Vector2u textureSize = backgroundTexture.getSize();

        // Calculate the scale factors for the sprite to cover the whole window
        float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

        // Use the larger scale factor to ensure full coverage
        float scale = std::max(scaleX, scaleY);

        // Set the scale of the sprite
        backgroundSprite.setScale(scale, scale);

        // Draw the scaled sprite as the background
        target.draw(backgroundSprite, states);

        // Then draw all celestial bodies on top of the background
        for (const auto& body : bodies) {
            target.draw(body, states);
        }
    }

    double Universe::radius() const {
        return mRadius;
    }

    int Universe::numPlanets() const {
        return bodies.size();
    }

    CelestialBody& Universe::operator[](int index) {
        return bodies.at(index);  // Use .at() for bounds checking
    }

    const CelestialBody& Universe::operator[](int index) const {
        return bodies.at(index);  // Use .at() for bounds checking
    }

    std::ostream& operator<<(std::ostream& out, const Universe& universe) {
        out << universe.bodies.size() << std::endl << universe.mRadius << std::endl;
        for (const auto& body : universe.bodies) {
            out << body << std::endl;
        }
        return out;
    }

    std::istream& operator>>(std::istream& in, Universe& universe) {
        int numberOfBodies;
        in >> numberOfBodies >> universe.mRadius;

        universe.bodies.clear();
        universe.bodies.reserve(numberOfBodies);
        for (int i = 0; i < numberOfBodies; ++i) {
            CelestialBody body = CelestialBody(universe.radius());
            in >> body;
            universe.bodies.push_back(body);
        }
        return in;
    }

    void Universe::step(double seconds) {
        for (auto& body : bodies) {
            double netFx = 0.0;
            double netFy = 0.0;

            // Calculate the net force on this body
            for (const auto& otherBody : bodies) {
                //  Make sure we're not calculating a body's force on itself
                if (&body != &otherBody) {
                    auto force = calculateGravitationalForce(body, otherBody);
                    netFx += force.first;
                    netFy += force.second;
                }
            }

            // Apply the net force to the body
            body.applyForce(netFx, netFy, seconds);
        }
    }

    // Function to calculate gravitational force between two celestial bodies
    std::pair<double, double> Universe::calculateGravitationalForce
    (const CelestialBody& body, const CelestialBody& otherBody) {
        double dx = otherBody.position().x - body.position().x;  // Difference in x positions
        double dy = otherBody.position().y - body.position().y;  // Difference in y positions
        double distanceSquared = dx * dx + dy * dy;  // Square of the distance between the bodies
        double distance = std::sqrt(distanceSquared);  // Distance between the bodies

        if (distance == 0) {
            return {0, 0};  // Avoid division by zero
        }

        // Magnitude of the gravitational force
        double forceMagnitude = G * body.mass() * otherBody.mass() / distanceSquared;
        double fx = forceMagnitude * dx / distance;  // x component of the gravitational force
        double fy = forceMagnitude * dy / distance;  // y component of the gravitational force

        return {fx, fy};
    }

}  //  namespace NB

