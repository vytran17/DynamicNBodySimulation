//  Copyright 2024 Vy Tran

#ifndef CELESTIALBODY_HPP
#define CELESTIALBODY_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

namespace NB {

class CelestialBody : public sf::Drawable {
 public:
    CelestialBody();
    // Single-parameter constructors should be marked explicit.
    explicit CelestialBody(double universeRadius);
    friend std::istream& operator>>(std::istream& in, CelestialBody& body);
    friend std::ostream& operator<<(std::ostream& out, const CelestialBody& body);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Vector2f position() const;
    sf::Vector2f velocity() const;
    float mass() const;
    void applyForce(double xForce, double yForce, double seconds);
 private:
    sf::Texture texture;  // Texture to hold the image of the celestial body
    double xPos, yPos;    // Position of the celestial body
    double xVel, yVel;    // Velocity of the celestial body
    double mMass;          // Mass of the celestial body
    double universeRadius;
    std::string textureFilename;
};

}  //  namespace NB

#endif  //  CELESTIALBODY_HPP
