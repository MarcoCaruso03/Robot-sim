#include "Map.h"

Map::Map(int const windowsWidth, int const windowHeight){
    cols = windowsWidth / tilesSize;
    rows = windowHeight / tilesSize;


    //generate the rect
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            //generete a rect in the right position 
            sf::RectangleShape tile(sf::Vector2f(tilesSize - 1, tilesSize - 1)); // -1 for visual sepration
            tile.setPosition(c*tilesSize, r*tilesSize); 
            tile.setFillColor(sf::Color::White);
            tiles.push_back(tile);
        }
    }
}
//the first const means => receive a pointer to a vector which cannot be modified 
//it is used to "protect" the internal data of the classe
//the second const means the function cannot modify the members of the class
const std::vector<sf::RectangleShape>& Map::getTiles() const {
    return tiles;
}
