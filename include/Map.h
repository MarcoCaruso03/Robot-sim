#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Map{
    private: 
        int tilesSize = 50;
        std::vector<sf::RectangleShape> tiles;
        int rows; 
        int cols; 
    public: 
        //given the windows, the construct set the number of rows and cols and create the tiles
        Map(int const windowsWidth, int const windowHeight);
        const std::vector<sf::RectangleShape>& getTiles() const; 
};