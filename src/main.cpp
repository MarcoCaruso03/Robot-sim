#include <SFML/Graphics.hpp>
#include <cmath>
#include "Map.h"
#include "Robot.h"

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
    std::cout<<"Hello\n";
    int windowsWidth = 800; 
    int windowsHeigt = 600;
    sf::RenderWindow window(sf::VideoMode(windowsWidth, windowsHeigt), "SFML Window");
    sf::Color colorBackGround = sf::Color::Black;
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")){
        // gestisci errore caricamento font
        return -1;
    }




    Map map(windowsWidth, windowsHeigt);

    //int robotR = 25;
    //sf::CircleShape robot(robotR);
    //robot.setPosition(sf::Vector2f(0,0));
    //robot.setFillColor(sf::Color::Red);
    Robot robot(0,0,25);
    const auto& tiles = map.getTiles();
    map.buildGraph();
    const auto& graph = map.getGraph();
    map.printGraph();
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
        map.draw(window);


        /*for (int i = 0; i < tiles.size(); ++i) {
            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(i));
            text.setCharacterSize(12);
            text.setFillColor(sf::Color::Red);

            // Posiziona il testo al centro del tile
            sf::FloatRect tileBounds = tiles[i].getGlobalBounds();
            sf::FloatRect textBounds = text.getLocalBounds();

            float x = tileBounds.left + (tileBounds.width - textBounds.width) / 2.f;
            float y = tileBounds.top + (tileBounds.height - textBounds.height) / 2.f;

            text.setPosition(x, y);
            window.draw(text);  
        }
        */
        robot.update(window);
        
        window.display();
    }

    return 0;
}
