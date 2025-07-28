#pragma once
#include <SFML/Graphics.hpp>
//#include "Robot.h"
//#include "Tile.h"
#include "Direction.h"


class Robot; // forward declaration
class Map;   // forward declaration

class Sensor{
    private: 
        bool detectionChecked; 
        //Direction to check
        Direction d; 
        Robot * robot; 
        Map * map; 
    public: 
        Sensor(Direction direction, Robot * r, Map * m);
        void active(); 
        void disable();
};