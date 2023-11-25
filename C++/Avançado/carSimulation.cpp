#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "MathHelpers.hpp"
#include <deque>

// Centro de massa do carro é entre as rodas traseiras.

#define M_PI_6 (M_PI / 6.0)


class Car
{
private:
    // Changeble Values
    float wheelBase = 100.f;
    float rearTrack = 50.f;
    float turn = 30.f;
    float enginePower = 150.f;
    float maxAcceleration = 100.f;
    float maxVelocity = 600.f;

    // Not Changeble Values
    float steering = 0.f;
    float acceleration = 0.f;
    float angle = 0.f;
    sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);
    sf::Vector2f position;
public:
    Car(float x, float y) : position(x, y) {}

    friend std::ostream& operator<<(std::ostream& os, const Car& car) {
        os << "Car: \n" << 
        "\nVelocidade: (" << car.velocity.x << "," << car.velocity.y << ")" <<
        "\nSteering: " << car.steering <<
        "\nAcceleration: " << car.acceleration <<
        "\nÂngulo: " << car.angle;
        return os;
    }

    void update(float dt) {
        handleInput(dt);
        updatePosition(dt);
    }

    void handleInput(float dt) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            acceleration += enginePower * dt;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            acceleration -= enginePower * dt;
        } else {
            acceleration = 0;
        }
        acceleration = std::max(-maxAcceleration, std::min(acceleration, maxAcceleration));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            steering = turn;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            steering = -turn;
        } else {
            steering = 0;
        }

    }

    void updatePosition(float dt) {
        velocity += sf::Vector2f(acceleration, 0);
        velocity.x = std::max(-maxVelocity, std::min(velocity.x, maxVelocity));

        float angular_velocity;
        if (steering) {
            float turnRadius = wheelBase / std::sin(steering);
            angular_velocity = velocity.x / turnRadius;
        } else {
            angular_velocity = 0;
        }

        position += sf::Transform().rotate(angle).transformPoint(-velocity) * dt;
        angle += MathHelpers::toDegrees(angular_velocity) * dt;
    }

    void draw(sf::RenderWindow& window) const {
        sf::RectangleShape carShape(sf::Vector2f(wheelBase, rearTrack));
        carShape.setFillColor(sf::Color::Blue);
        carShape.setPosition(position);
        carShape.setRotation(angle);

        window.draw(carShape);
    }

};

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Car Steering Simulation");
    window.setFramerateLimit(60);

    sf::Clock clock;

    Car car(400.f, 300.f);

    while (window.isOpen()) {
        sf::Event event;
        sf::Time time = clock.restart();
        float dt = time.asSeconds();
        std::cout << "Delta Time in Seconds: " << dt << std::endl;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        car.update(dt);

        window.clear();

        std::cout << car << std::endl;

        car.draw(window);

        window.setView(window.getDefaultView());

        window.display();
    }

    return 0;
}
