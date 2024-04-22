//  Copyright 2024 Vy Tran

#include <vector>
#include "CelestialBody.hpp"
#include <SFML/Graphics.hpp>

namespace NB {
    CelestialBody::CelestialBody()
    : xPos(0),
      yPos(0),
      xVel(0),
      yVel(0),
      mMass(0),
      universeRadius(0)
    {}
    CelestialBody::CelestialBody(double universeRadius)
    : xPos(0),
      yPos(0),
      xVel(0),
      yVel(0),
      mMass(0),
      universeRadius(universeRadius)
    {}
    // Input stream overload for reading CelestialBody data
    std::istream& operator>>(std::istream& in, CelestialBody& body) {
        in >> body.xPos >> body.yPos >> body.xVel >> body.yVel
        >> body.mMass >> body.textureFilename;
        if (!body.texture.loadFromFile("assets/" + body.textureFilename)) {
            std::cerr << "Could not load image: " + body.textureFilename << std::endl;
        }
        return in;
    }

    // Output stream overload for writing CelestialBody data
    std::ostream& operator<<(std::ostream& out, const CelestialBody& body) {
        out << body.xPos << " " << body.yPos << " " << body.xVel << " " << body.yVel << " "
        << body.mMass << " " << body.textureFilename;
        return out;
    }

    void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2, bounds.height / 2);

        // Get the center of the target (window/screen)
        sf::Vector2u targetSize = target.getSize();
        float centerX = targetSize.x / 2.0f;
        float centerY = targetSize.y / 2.0f;

        // Assuming `universeRadius` is passed or accessible here
        double scaleFactor = std::min(targetSize.x, targetSize.y) / (universeRadius * 2.0);

        // Translate and scale universe coordinates to screen coordinates
        float screenX = centerX + (xPos * scaleFactor);
        float screenY = centerY - (yPos * scaleFactor);  // Y is going up.

        // Set the position of the sprite based on translated and scaled coordinates
        sprite.setPosition(screenX, screenY);

        target.draw(sprite, states);
    }

    sf::Vector2f CelestialBody::position() const {
        return sf::Vector2f(static_cast<float>(xPos), static_cast<float>(yPos));
    }

    sf::Vector2f CelestialBody::velocity() const {
        return sf::Vector2f(static_cast<float>(xVel), static_cast<float>(yVel));
    }

    float CelestialBody::mass() const {
        return static_cast<float>(mMass);
    }

    void CelestialBody::applyForce(double xForce, double yForce, double seconds) {
        // Calculate acceleration x and y given the force. a = F/m
        double ax = xForce / mMass;
        double ay = yForce / mMass;
        // Update the velocity using the acceleration. v1 = v0 + a * t
        xVel += ax * seconds;
        yVel += ay * seconds;
        // Update the position using the speed. x1 = x0 + v1 * t
        xPos += xVel * seconds;
        yPos += yVel * seconds;
    }


}  //  namespace NB
