#include "Tile.h"

Tile::Tile(float x, float y, int s, TileType t) : type(t) {
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
    shape.setOutlineColor(sf::Color::Black);   // bordo nero fisso
    shape.setSize(sf::Vector2f(s,s));
    shape.setOutlineThickness(1.f);             // spessore bordo (1 pixel)
}

void Tile::setType(TileType newType) {
    type = newType;
    switch (type) {
        case TileType::Empty:    shape.setFillColor(sf::Color::White); break;
        case TileType::Obstacle: shape.setFillColor(sf::Color::Black); break;
        case TileType::Start:    shape.setFillColor(sf::Color::Green); break;
        case TileType::Goal:     shape.setFillColor(sf::Color::Blue); break;
    }
}

TileType Tile::getType() const {
    return type;
}

void Tile::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}
sf::RectangleShape Tile::getShape(){
    return shape;
}
