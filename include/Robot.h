#pragma once
#include <SFML/Graphics.hpp>

class Robot{
    private: 
        int r=25;
        //position
        int x, y;
        sf::CircleShape shape;
        float speed=0.05f;
    public: 
        Robot(int x_init, int y_init, int initR);
        void setX(int new_x);
        void setY(int new_y);
        void update(sf::RenderWindow& window);
        void moveXpos();
        void moveXneg();
        void moveYpos();
        void moveYneg();
};
