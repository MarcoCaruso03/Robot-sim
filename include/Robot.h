#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
enum class Direction {
    Up,
    Down, 
    Right, 
    Left,
    None,
};
class Robot{
    private: 
        int r=25;
        //position
        int x, y;
        sf::CircleShape shape;
        float speed=0.05f;
        Map * map; 
        int currentTile = -1;
        std::vector<int> pathToFollow; 
        int currentStep = 0;
        bool pathComputed = false; 
        bool robotPlaced = false; 
        sf::RenderWindow * win; 
        bool canRunAlgo = false;
    public: 
        Robot(Map * m, int x_init, int y_init, int initR, sf::RenderWindow * w);
        void setX(int new_x);
        void setY(int new_y);
        void setCanRunAlgo(bool b){canRunAlgo = b;}
        void update(sf::RenderWindow& window);
        void moveXpos();
        void moveXneg();
        void moveYpos();
        void moveYneg();
        void setPathComputed(bool b){pathComputed = b;}
        Direction getNewDirection(int tile);
        //void setPath(std::vector<int> p){pathToFollow = p;}
        void placeRobot(int c, int r);
        void setPath(const std::vector<int>& newPath){pathToFollow = newPath;}
};
