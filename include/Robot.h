#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Sensor.h"
#include "Direction.h"
/*enum class Direction {
    Up,
    Down, 
    Right, 
    Left,
    None,
};*/
class Robot{
    private: 
        int r=25;
        //position
        int x, y;
        sf::CircleShape shape;
        float speed=0.1f;
        Map * map; 
        //in phase3 the robot doesn't have the exact map with obstacles, but just a map with the same size of the original but no obstacles 
        //robotMap.
        Map robotMap; 
        int currentTile = -1;
        std::vector<int> pathToFollow; 
        int currentStep = 0;
        int startTile = -1; 
        int endTile = -1;
        bool pathComputed = false; 
        bool robotPlaced = false; 
        sf::RenderWindow * win; 
        bool canRunAlgo = false;
        //Sensor sensorUp, sensorDown, sensorLeft, sensorRight; 
        std::vector<Sensor> sensors; 
        std::vector<bool> detected; 
        bool nextMoveIsValide = true;
        bool needToComputePath = true; 
    public: 
        Robot(Map * m, int x_init, int y_init, int initR, sf::RenderWindow * w);
        void setX(int new_x);
        void setY(int new_y);
        void setCanRunAlgo(bool b){canRunAlgo = b;}
        void setStartTile(int i){startTile = i; currentTile =i;}
        void setEndTile(int i){endTile= i;}
        void update(sf::RenderWindow& window);
        void moveXpos();
        void moveXneg();
        void moveYpos();
        void moveYneg();
        void setPathComputed(bool b){pathComputed = b;}
        Direction getNewDirection(int tile);
        //void setPath(std::vector<int> p){pathToFollow = p;}
        void placeRobot(int c, int r);
        void setPath(const std::vector<int>& newPath);
        int  getCurrentTile(){return currentTile;}

        //phase3
        void deleteObstacleRobotMap();
        Map * getRobotMap(){return &robotMap;}

};
