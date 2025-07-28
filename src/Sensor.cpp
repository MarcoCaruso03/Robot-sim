#include "Sensor.h"
#include "Sensor.h"
#include "Robot.h"
#include "Map.h"


Sensor::Sensor(Direction Direction, Robot * r, Map * m){
    detectionChecked = false; 
    robot = r; 
    d = Direction;
    map = m;
}

void Sensor::active(){
    //get the current position of the robot 
    int currentTile = robot->getCurrentTile();
    int tileToBeChecked = -1;
    int row = currentTile / map->getCols();;
    int col = currentTile % map->getCols();;
    
    //find the idTile to be checked based on the position (check also the border positions)
    if(d==Direction::Right && col<map->getCols()-1)
        tileToBeChecked = currentTile+1;
    else if(d==Direction::Left && col>0)
        tileToBeChecked = currentTile-1;
    else if(d==Direction::Down && row<map->getRows()-1)
        tileToBeChecked = currentTile + map->getCols();
    else if(d==Direction::Up && row > 0)
        tileToBeChecked = currentTile - map->getCols();
    else 
        tileToBeChecked = -1;
    
    std::vector<Tile> tiles = map->getTiles();
    if(tiles[tileToBeChecked].getType()==TileType::Obstacle)
        //obstacle detected
        detectionChecked = true; 
    else 
        detectionChecked = false; 
    //std::cout<<"Obstacled: "<<detectionChecked<<" Direction:"<<directionToString(d)<<std::endl;
    return; 
}
//forse non serve a niente
void Sensor::disable(){
    detectionChecked = false; 
    return; 
}