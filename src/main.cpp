#include <SFML/Graphics.hpp>
#include <cmath>
#include "Map.h"
#include "Robot.h"
#include "Utils.h"
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
    sf::RenderWindow window1(sf::VideoMode(windowsWidth, windowsHeigt), "True Map");
    sf::RenderWindow window2(sf::VideoMode(windowsWidth, windowsHeigt), "Robot Map");

    sf::Color colorBackGround = sf::Color::Black;
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")){
        // gestisci errore caricamento font
        return -1;
    }
    bool generateMap = false;
    int clickStage = 0; // 0 = start, 1 = goal, 2+ = ostacoli
    int startTile = 0;
    int goalTile = -1;
    //int TileIDRobot = 0; 


    
    Map map(windowsWidth, windowsHeigt);


    //Robot => Starting point is startTile 
    int xR, yR, colR, rowR;
    bool robotPlaced = false, canMove=false; 
    Robot robot(&map, 0,0,25, &window1);
    //Robot robot(&map, 0,0,25);
    auto& tiles = map.getTiles();
    Map * rMap = robot.getRobotMap();

    //algo
    bool canRunAlgo = false; 

    
    //ciclo di rendering
    while (window1.isOpen() || window2.isOpen())
    {
        sf::Event event;
        //ciclo di eventi
        while (window1.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window1.close();
            sf::Vector2i mousePos = sf::Mouse::getPosition(window1);

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                int tileSize = map.getTileSize();
                int col = mousePos.x / tileSize;
                int row = mousePos.y / tileSize;
                if (col >= 0 && col < map.getCols() && row >= 0 && row < map.getRows()) {
                    int index = row*map.getCols()+col;
                    //starting point 
                    if(clickStage == 0){
                        tiles[index].setFillColor(sf::Color::Magenta);
                        std::cout << "Start set on tile: " << index << "\n";
                        startTile = index;
                        rowR = startTile / map.getCols();
                        colR = startTile % map.getCols();
                        //robotPlaced=true;
                        robot.placeRobot(colR, rowR);
                        robot.setStartTile(startTile);
                    }
                    //goal point
                    else if(clickStage == 1){
                        tiles[index].setFillColor(sf::Color::Green);
                        std::cout << "Goal set on tile: " << index << "\n";
                        goalTile = index;
                        robot.setEndTile(goalTile);
                    }
                    //obstacle
                    else{
                        if(tiles[index].getType() != TileType::Obstacle){
                            tiles[index].setType(TileType::Obstacle);
                            tiles[index].setFillColor(sf::Color::Black);
                            std::cout << "Tile " << index << " set as obstacle\n";
                        }
                    }
                    clickStage++;
                }
            }

            //user delete obs: 
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                //find the tile position
                int tileSize = map.getTileSize();
                int col = mousePos.x / tileSize;
                int row = mousePos.y / tileSize;
                if(col >= 0 && col<map.getCols() && row >= 0 && row < map.getRows()){
                    //mouse è nella mappa
                    int index = row*map.getCols()+col; 
                    if(tiles[index].getType() == TileType::Obstacle){
                        tiles[index].setType(TileType::Empty);
                        tiles[index].setFillColor(sf::Color::White);
                        std::cout << "Tile " << index << " is not an obstacle anymore\n";
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E && clickStage>=1){
                //canRunAlgo = true;
                /*
                if(generateMap == false){
                    map.buildGraph();
                    generateMap = true; 
                    map.printGraph();
                }     
                std::vector<int> path = map.dijkstra(startTile, goalTile);
                for(auto p : path){
                    std::cout<<p<<"->"; 
                }
                std::cout<<"\n";
                std::cout<<"Tile INFO\n";
                for(int i=0; i<tiles.size(); i++){
                    std::cout << i << ": " << tileTypeToString(tiles[i].getType()) << "\n";
                }
                robot.setPath(path);
                robot.setCanRunAlgo(true);*/
                //rMap->buildGraph();
                //std::vector<int> path = rMap->dijkstra(startTile, goalTile);
                //robot.setPath(path);
                robot.setCanRunAlgo(true);

            }

        }
        while(window2.pollEvent(event)){
            if(event.type==sf::Event::Closed)
                window2.close();
        }

        window1.clear(colorBackGround);
        window2.clear(colorBackGround);
        //render of the map         
        map.draw(window1);
        //robot 
        robot.update(window1);
       
        //for debugging
        for (int i = 0; i < tiles.size(); ++i) {
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
            window1.draw(text);  
        }
        robot.getRobotMap()->draw(window2);

        const std::vector<Tile>& robotTiles = robot.getRobotMap()->getTiles();

        for (int i = 0; i < robotTiles.size(); ++i) {
            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(i));
            text.setCharacterSize(12);
            text.setFillColor(sf::Color::Red);

            sf::FloatRect tileBounds = robotTiles[i].getGlobalBounds();
            sf::FloatRect textBounds = text.getLocalBounds();

            float x = tileBounds.left + (tileBounds.width - textBounds.width) / 2.f;
            float y = tileBounds.top + (tileBounds.height - textBounds.height) / 2.f;

            text.setPosition(x, y);
            window2.draw(text);
        }


        window2.display();
        window1.display();
    }

    return 0;
}
