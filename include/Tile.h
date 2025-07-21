#pragma once
#include <SFML/Graphics.hpp>

enum class TileType {
    Empty,
    Obstacle,
    Start,
    Goal
};

class Tile {
    private:
        sf::RectangleShape shape;
        TileType type;
        int Size;
    public: 
        Tile(float x, float y,  int s, TileType type = TileType::Empty);
        void setType(TileType newType);
        TileType getType() const;
        void draw(sf::RenderWindow& window) const;
        sf::RectangleShape getShape();
        void setPosition(float x, float y){shape.setPosition(x,y);}
        void setFillColor(const sf::Color& color){shape.setFillColor(color);}
        sf::FloatRect getGlobalBounds() const { return shape.getGlobalBounds();}

};