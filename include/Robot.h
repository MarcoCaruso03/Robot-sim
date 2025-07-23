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
    public: 
        Robot(Map * m, int x_init, int y_init, int initR);
        void setX(int new_x);
        void setY(int new_y);
        void update(sf::RenderWindow& window);
        void moveXpos();
        void moveXneg();
        void moveYpos();
        void moveYneg();
        Direction getNewDirection(int tile);
        //void setPath(std::vector<int> p){pathToFollow = p;}
        void setPath(const std::vector<int>& newPath){pathToFollow = newPath;}
};
