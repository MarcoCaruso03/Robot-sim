#ifndef DIRECTION_H
#define DIRECTION_H

enum class Direction {
    Up,
    Down,
    Left,
    Right,
    None
};

inline const char* directionToString(Direction d) {
    switch(d) {
        case Direction::Up: return "Up";
        case Direction::Down: return "Down";
        case Direction::Left: return "Left";
        case Direction::Right: return "Right";
        case Direction::None: return "None";
        default: return "Unknown";
    }
}

#endif
