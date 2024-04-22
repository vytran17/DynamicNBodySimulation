//  Copyright 2024 Vy Tran

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <cmath>
#include <fstream>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include "CelestialBody.hpp"
#include "Universe.hpp"

namespace NB {

BOOST_AUTO_TEST_CASE(testCelestialBodyStreamOperators) {
    std::cout << "testCelestialBodyStreamOperators" << std::endl;
    std::stringstream ss;
    ss << "1 2 0.1 0.2 1e5 test.gif\n";  //  x, y, vx, vy, mass, filename
    CelestialBody body(1e11);  //  Assuming universe radius is needed for scaling
    ss >> body;
    BOOST_CHECK_CLOSE(body.position().x, 1.0f, 0.01f);
    BOOST_CHECK_CLOSE(body.position().y, 2.0f, 0.01f);
    BOOST_CHECK_CLOSE(body.velocity().x, 0.1f, 0.01f);
    BOOST_CHECK_CLOSE(body.velocity().y, 0.2f, 0.01f);
    BOOST_CHECK_CLOSE(body.mass(), 1e5f, 0.01f);

    std::stringstream out;
    out << body;
    BOOST_CHECK(!out.str().empty());  //  Check if the output is non-empty
}

BOOST_AUTO_TEST_CASE(testUniverseConstruction) {
    std::cout << "testUniverseConstruction" << std::endl;
    Universe universe;
    // Check if radius is initialized to 0
    BOOST_CHECK_SMALL(universe.radius(), 0.01);
}

BOOST_AUTO_TEST_CASE(testUniverseStreamOperators) {
    std::cout << "testUniverseStreamOperators" << std::endl;
    std::stringstream ss;
    // numBodies, radius, and bodies
    ss << "2 1e11\n1 2 0.1 0.2 1e5 test1.gif\n3 4 0.3 0.4 2e5 test2.gif\n";
    Universe universe;
    ss >> universe;
    BOOST_CHECK_EQUAL(universe.numPlanets(), 2);
    BOOST_CHECK_CLOSE(universe.radius(), 1e11, 0.01);

    const CelestialBody& body1 = universe[0];
    BOOST_CHECK_CLOSE(body1.position().x, 1.0f, 0.01f);
    BOOST_CHECK_CLOSE(body1.mass(), 1e5f, 0.01f);

    const CelestialBody& body2 = universe[1];
    BOOST_CHECK_CLOSE(body2.position().x, 3.0f, 0.01f);
    BOOST_CHECK_CLOSE(body2.mass(), 2e5f, 0.01f);

    std::stringstream out;
    out << universe;
    BOOST_CHECK(!out.str().empty());  //  Check if the output is non-empty
}

BOOST_AUTO_TEST_CASE(testUniverseConstructor) {
    std::cout << "testUniverseConstructor" << std::endl;
    Universe universe;
    BOOST_CHECK_EQUAL(universe.numPlanets(), 0);
}

BOOST_AUTO_TEST_CASE(testUniverseInputOperator) {
    std::cout << "testUniverseInputOperator" << std::endl;
    Universe universe;
    std::istringstream input("3\n"
                             "10.0\n"
                             "1.0 2.0 3.0 4.0 5.0 body1.png\n"
                             "2.0 3.0 4.0 5.0 6.0 body2.png\n"
                             "3.0 4.0 5.0 6.0 7.0 body3.png\n");
    input >> universe;

    BOOST_CHECK_EQUAL(universe.numPlanets(), 3);
    BOOST_CHECK_EQUAL(universe[0].position().x, 1.0f);
    BOOST_CHECK_EQUAL(universe[1].position().x, 2.0f);
    BOOST_CHECK_EQUAL(universe[2].position().x, 3.0f);
}

BOOST_AUTO_TEST_CASE(testUniverseOutputOperator) {
    std::cout << "testUniverseOutputOperator" << std::endl;
    Universe universe;
    std::istringstream input("3\n"
                             "10.0\n"
                             "1.0 2.0 3.0 4.0 5.0 body1.png\n"
                             "2.0 3.0 4.0 5.0 6.0 body2.png\n"
                             "3.0 4.0 5.0 6.0 7.0 body3.png\n");
    input >> universe;

    std::ostringstream output;
    output << universe;

    std::string expectedOutput = "3\n"
                                 "10\n"
                                 "1 2 3 4 5 body1.png\n"
                                 "2 3 4 5 6 body2.png\n"
                                 "3 4 5 6 7 body3.png\n";
    BOOST_CHECK_EQUAL(output.str(), expectedOutput);
}

BOOST_AUTO_TEST_CASE(testCelestialBodyConstructor) {
    std::cout << "testCelestialBodyConstructor" << std::endl;
    CelestialBody body;
    BOOST_CHECK_EQUAL(body.position().x, 0.0f);
    BOOST_CHECK_EQUAL(body.position().y, 0.0f);
}

BOOST_AUTO_TEST_CASE(testCelestialBodyOperatorInput) {
    std::cout << "testCelestialBodyOperatorInput" << std::endl;
    CelestialBody body;
    std::istringstream input("1.0 2.0 3.0 4.0 5.0 body.png\n");
    input >> body;

    BOOST_CHECK_EQUAL(body.position().x, 1.0f);
    BOOST_CHECK_EQUAL(body.position().y, 2.0f);
}

BOOST_AUTO_TEST_CASE(testStepZero) {
    std::cout << "testStepZero" << std::endl;

    Universe universe;
    std::istringstream input("3\n"
                             "1.25e11\n"
                             "0.00e00  0.00e00  0.05e04  0.00e00  5.974e24  earth.gif\n"
                             "0.00e00  4.50e10  3.00e04  0.00e00  1.989e30  sun.gif\n"
                             "0.00e00 -4.50e10 -3.00e04  0.00e00  1.989e30  sun.gif\n");
    input >> universe;

    // Perform zero step of the simulation
    universe.step(0);

    // Retrieve the updated positions of the bodies
    const CelestialBody& body1 = universe[0];
    const CelestialBody& body2 = universe[1];
    const CelestialBody& body3 = universe[2];

    // Check that the bodies have not moved.
    BOOST_CHECK_CLOSE(body1.position().x, 0, 0.01);
    BOOST_CHECK_CLOSE(body1.position().y, 0, 0.01);
    BOOST_CHECK_CLOSE(body2.position().x, 0, 0.01);
    BOOST_CHECK_CLOSE(body2.position().y, 4.50e10, 0.01);
    BOOST_CHECK_CLOSE(body3.position().x, 0, 0.01);
    BOOST_CHECK_CLOSE(body3.position().y, -4.50e10, 0.01);
}

BOOST_AUTO_TEST_CASE(testFixedDeltasWithSpecificPositions) {
    std::cout << "testFixedDeltasWithSpecificPositions" << std::endl;

    Universe universe;
    std::istringstream input("3\n"
                             "1.25e11\n"
                             "0.00e00  0.00e00  0.05e04  0.00e00  5.974e24  earth.gif\n"
                             "0.00e00  4.50e10  3.00e04  0.00e00  1.989e30  sun.gif\n"
                             "0.00e00 -4.50e10 -3.00e04  0.00e00  1.989e30  sun.gif\n");
    input >> universe;

    double deltaT = 250.0;

    // Perform one step of the simulation
    universe.step(deltaT);

    // Retrieve the updated positions of the bodies
    const CelestialBody& body1 = universe[0];
    const CelestialBody& body2 = universe[1];
    const CelestialBody& body3 = universe[2];

    // Check that the bodies have moved to the expected positions
    BOOST_CHECK_CLOSE(body1.position().x, 125000, 0.01);
    BOOST_CHECK_CLOSE(body1.position().y, 0, 0.01);
    BOOST_CHECK_CLOSE(body2.position().x, 7.5e+06, 0.01);
    BOOST_CHECK_CLOSE(body2.position().y, 4.5e+10, 0.01);
    BOOST_CHECK_CLOSE(body3.position().x, -7.5e+06, 0.01);
    BOOST_CHECK_CLOSE(body3.position().y, -4.5e+10, 0.01);

    // Check that velocities changed as expected.
    BOOST_CHECK_CLOSE(body1.velocity().x, 500, 0.01);
    BOOST_CHECK_CLOSE(body1.velocity().y, 0, 0.01);
    BOOST_CHECK_CLOSE(body2.velocity().x, 30000, 0.01);
    BOOST_CHECK_CLOSE(body2.velocity().y, -4.09468842, 0.01);
    BOOST_CHECK_CLOSE(body3.velocity().x, -30000, 0.01);
    BOOST_CHECK_CLOSE(body3.velocity().y, 4.09468842, 0.01);
}

//  Test for antimatter.txt
BOOST_AUTO_TEST_CASE(testAntimatter) {
    std::cout << "testAntimatter" << std::endl;

    Universe universe;
    std::istringstream input("3\n"
                           " 2.50e+11\n"
                            "-1.5000e+11 0  0  0  8.0000e+30  sun.gif\n"
                            "1.5000e+11  0  0  0  8.0000e+30  sun.gif\n"
                            "0.0000e+11  0  0  0 -2.0000e+30  uranus.gif\n");
    input >> universe;

    double deltaT = 20000.0;

    // Perform one step of the simulation
    universe.step(deltaT);

    // Retrieve the updated positions of the bodies
    const CelestialBody& body1 = universe[0];
    const CelestialBody& body2 = universe[1];
    const CelestialBody& body3 = universe[2];

    // Make sure the bodies are not moved
    BOOST_CHECK_CLOSE(body1.position().x, -1.5000e+11, 0.01);
    BOOST_CHECK_CLOSE(body1.position().y, 0.0000e+00, 0.01);
    BOOST_CHECK_CLOSE(body2.position().x, 1.5000e+11, 0.01);
    BOOST_CHECK_CLOSE(body2.position().y, 0.0000e+00, 0.01);
    BOOST_CHECK_CLOSE(body3.position().x, 0.0000e+11, 0.01);
    BOOST_CHECK_CLOSE(body3.position().y, 0.0000e+00, 0.01);
}

BOOST_AUTO_TEST_CASE(testZeroGravity) {
    std::cout << "testZeroGravity" << std::endl;

    Universe universe;
    std::istringstream input("3\n"
                             "512\n"
                             "0   0  1  1  1e-30 earth.gif\n"
                             "128   0  2  1  1e-40 venus.gif\n"
                             "0 128  1  2  1e-50 mars.gif\n");
    input >> universe;

    double deltaT = 2500.0;
    universe.step(deltaT);

    // Retrieve the updated positions of the bodies
    const CelestialBody& body1 = universe[0];
    const CelestialBody& body2 = universe[1];
    const CelestialBody& body3 = universe[2];

    // Check that the bodies have moved to the expected positions
    BOOST_CHECK_CLOSE(body1.position().x, 2500, 0.01);
    BOOST_CHECK_CLOSE(body1.position().y, 2500, 0.01);
    BOOST_CHECK_CLOSE(body2.position().x, 5128, 0.01);
    BOOST_CHECK_CLOSE(body2.position().y, 2500, 0.01);
    BOOST_CHECK_CLOSE(body3.position().x, 2500, 0.01);
    BOOST_CHECK_CLOSE(body3.position().y, 5128, 0.01);
}

BOOST_AUTO_TEST_CASE(testInvertedGravitation) {
    std::cout << "testInvertedGravitation" << std::endl;

    // Set up a universe with bodies that have negative masses
    Universe universe;
    std::istringstream input("2\n"
                             "1e11\n"
                             "0 0 0 0 -1.989e30 body1.gif\n"  // Negative mass for body1
                             "1e10 0 0 0 1.989e30 body2.gif\n");  // Positive mass for body2
    input >> universe;

    double deltaT = 10000.0;

    // Perform one step of the simulation
    universe.step(deltaT);

    // Check that the bodies have moved apart, indicating repulsion
    const CelestialBody& body2 = universe[1];
    BOOST_CHECK(body2.position().x > 1e10);
}

BOOST_AUTO_TEST_CASE(testLeapfrogIntegration) {
    std::cout << "testLeapfrogIntegration" << std::endl;

    // Mass of the central body (e.g., sun)
    double centralMass = 1e10;
    // Distance of the orbiting body from the central body
    double orbitRadius = 1e5;
    // Calculating orbital velocity for a circular orbit
    double orbitalVelocity = std::sqrt(6.67e-11 * centralMass / orbitRadius);

    // Set up a universe with two bodies: a central body and an orbiting body
    Universe universe;
    std::istringstream input(
        std::string("2\n") +
        "1e11\n" +  // Universe radius
        "0 0 0 0 " + std::to_string(centralMass) + " 1.gif\n" +  // Central body at the origin
        std::to_string(orbitRadius) + " 0 0 " + std::to_string(orbitalVelocity) + " 1e5 2.gif\n");
    input >> universe;

    double deltaT = 100.0;  // Time step for the simulation

    // Perform a few steps of the simulation
    int steps = 10;
    for (int i = 0; i < steps; ++i) {
        universe.step(deltaT);
    }

    // Retrieve the updated position of the orbiting body
    const CelestialBody& orbitingBody = universe[1];

    // Check position after full orbit.
    BOOST_CHECK_CLOSE(orbitingBody.position().x, orbitRadius, 1.0);
    BOOST_CHECK_CLOSE(orbitingBody.velocity().y, orbitalVelocity, 1.0);
}


}  //  namespace NB
