#include <SFML/Graphics.hpp>
#include <cmath>
#include "Map.h"

bool checkCircleCollision(const sf::CircleShape& circle1, const sf::CircleShape& circle2) {
    // Calcola i centri dei cerchi (posizione + raggio)
    sf::Vector2f center1 = circle1.getPosition() + sf::Vector2f(circle1.getRadius(), circle1.getRadius());
    sf::Vector2f center2 = circle2.getPosition() + sf::Vector2f(circle2.getRadius(), circle2.getRadius());

    // Distanza tra i centri
    float dx = center1.x - center2.x;
    float dy = center1.y - center2.y;
    float distanceSquared = dx * dx + dy * dy;

    // Somma dei raggi
    float radiusSum = circle1.getRadius() + circle2.getRadius();

    // Collisione se distanza tra i centri <= somma raggi
    return distanceSquared <= (radiusSum * radiusSum);
}


int main()
{
    int windowsWidth = 800; 
    int windowsHeigt = 600;
    sf::RenderWindow window(sf::VideoMode(windowsWidth, windowsHeigt), "SFML Window");
    sf::Color colorBackGround = sf::Color::Black;
    
    Map map(windowsWidth, windowsHeigt);

    int robotR = 25;
    sf::CircleShape robot(robotR);
    robot.setPosition(sf::Vector2f(0,0));
    robot.setFillColor(sf::Color::Red);
    //ciclo di rendering
    while (window.isOpen())
    {
        sf::Event event;
        //ciclo di eventi
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(colorBackGround);
        //render of the map 
        for (const auto& tile : map.getTiles())
            window.draw(tile);
        
        window.draw(robot);
        window.display();
    }

    return 0;
}
