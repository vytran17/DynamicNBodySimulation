//  Copyright 2024 Vy Tran

#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

namespace NB {

class Universe : public sf::Drawable {
 public:
    Universe();
    explicit Universe(const std::string& filename);
    friend std::istream& operator>>(std::istream& in, Universe& universe);
    friend std::ostream& operator<<(std::ostream& out, const Universe& universe);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    double radius() const;
    int numPlanets() const;
    void step(double seconds);
    CelestialBody& operator[](int index);
    const CelestialBody& operator[](int index) const;
 private:
    sf::Texture backgroundTexture;
    std::vector<CelestialBody> bodies;  //  Container for all celestial bodies in the universe
    double mRadius;  //  Radius of the universe, used for scaling
    std::pair<double, double> calculateGravitationalForce
    (const CelestialBody& body, const CelestialBody& otherBody);
};

}  //  namespace NB

#endif  //  UNIVERSE_HPP
