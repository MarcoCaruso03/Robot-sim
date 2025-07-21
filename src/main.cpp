#include <SFML/Graphics.hpp>
#include <cmath>


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
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
    sf::Color colorBackGround = sf::Color::Black;

    sf::CircleShape circle(50), ostacolo(100);

    circle.setFillColor(sf::Color::Red);
    ostacolo.setFillColor(sf::Color::Blue);
    circle.setPosition(0, window.getSize().y/3);
    ostacolo.setPosition(500, window.getSize().y/3);
    float speed = 0.2f; 
    bool isMoving = false; 
    bool collision = false;
    //ciclo di rendering
    while (window.isOpen())
    {
        sf::Event event;
        //ciclo di eventi
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            //gestione colore
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::R)
                    colorBackGround = sf::Color::Red;
            }
            if(event.type == sf::Event::KeyReleased)
                colorBackGround = sf::Color::Black;
        }
        window.clear(colorBackGround);

        //bordi
        // Ottieni posizione attuale e raggio
        sf::Vector2f circlepos = circle.getPosition();
        sf::Vector2f obspos = ostacolo.getPosition(); 
        

        float r = circle.getRadius();
        float winW = window.getSize().x;
        float winH = window.getSize().y;

        // Movimento con controllo bordi
        /*
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pos.x > 0)
            circle.move(-speed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pos.x + r * 2 < winW)
            circle.move(speed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pos.y > 0)
            circle.move(0, -speed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pos.y + r * 2 < winH)
            circle.move(0, speed);
        */

        //Animazione di un cerchio
        //check is moving=Collisione altri object/bordi
            
        sf::Vector2f centerCircle = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());
        sf::Vector2f centerOstacolo = ostacolo.getPosition() + sf::Vector2f(ostacolo.getRadius(), ostacolo.getRadius());

        if (circle.getPosition().x + circle.getRadius() * 2 < window.getSize().x &&
            !checkCircleCollision(circle, ostacolo)) {
            isMoving = true;
        } else {
            isMoving = false;
        }       


        if(isMoving)
            circle.move(speed, 0);
        window.draw(circle); 
        window.draw(ostacolo);
        window.display();
    }

    return 0;
}
