#include "Tile.h"
std::string tileTypeToString(TileType type) {
    switch(type) {
        case TileType::Empty: return "Empty";
        case TileType::Obstacle: return "Obstacle";
        case TileType::Start: return "Start";
        case TileType::Goal: return "Goal";
        default: return "Unknown";
    }
}
