#include "Robot.h"
#include <cmath>

/*Robot::Robot(Map * m, int initX, int initY, int initR, sf::RenderWindow * w){
    map = m;
    x=initX; 
    y=initY;
    r=initR;
    shape=sf::CircleShape(r);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(sf::Vector2f(x,y));
    int tileSize = map->getTileSize();
    int robot_col = x / tileSize; 
    int robot_row = y / tileSize; 
    currentTile = robot_row*map->getCols()+robot_col; 
    std::cout<<"CurrentRobotTile: "<<currentTile<<"\n";
    win = w; 
    //sensorDown = Sensor(Direction::Down, this, map);
    //sensorUp = Sensor(Direction::Up, this, map);
    //sensorLeft = Sensor(Direction::Left, this, map);
    //sensorRight = Sensor(Direction::Right, this, map);
    
}*/
Robot::Robot(Map* m, int initX, int initY, int initR, sf::RenderWindow* w)
    : map(m),
      sensorUp(Direction::Up, this, m),
      sensorDown(Direction::Down, this, m),
      sensorLeft(Direction::Left, this, m),
      sensorRight(Direction::Right, this, m)
{
    x=initX; 
    y=initY;
    r=initR;
    shape=sf::CircleShape(r);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(sf::Vector2f(x,y));
    int tileSize = map->getTileSize();
    int robot_col = x / tileSize; 
    int robot_row = y / tileSize; 
    currentTile = robot_row*map->getCols()+robot_col; 
    std::cout<<"CurrentRobotTile: "<<currentTile<<"\n";
    win = w; 
}
void Robot::setX(int new_x){
    //x=new_x;
    sf::Vector2f pos = shape.getPosition();
    shape.setPosition(new_x, pos.y);
}
void Robot::setY(int new_y){
    sf::Vector2f pos = shape.getPosition();
    shape.setPosition(pos.x, new_y);
    //y=new_y;
}
void Robot::update(sf::RenderWindow& window) {
    if(robotPlaced){
        if(canRunAlgo){

            sensorLeft.active();
            if (currentStep >= pathToFollow.size()) {
                //std::cout<<"Finito il percorso\n";
                window.draw(shape);
                return;  // Finito il percorso
                canRunAlgo = false; 
            }

            int nextTile = pathToFollow[currentStep];

            // Calcolo posizione target (centro della tile)
            int tileSize = map->getTileSize();
            int col = nextTile % map->getCols();
            int row = nextTile / map->getCols();


            float radius = shape.getRadius();
            sf::Vector2f targetPosition = {
                col * tileSize + tileSize / 2.0f - radius,
                row * tileSize + tileSize / 2.0f - radius
            };

            sf::Vector2f currentPosition = shape.getPosition();
            float dx = targetPosition.x - currentPosition.x;
            float dy = targetPosition.y - currentPosition.y;
            float distance = std::sqrt(dx * dx + dy * dy);

            if (distance < 1.0f) {
                // Raggiunta la tile
                currentTile = nextTile;
                currentStep++;
            } else {
                //std::cout<<"TIle current:"<<currentTile<<std::endl; 
                // Muoviti verso la tile
                Direction d = getNewDirection(nextTile);

                if (d == Direction::Right) moveXpos();
                else if (d == Direction::Left) moveXneg();
                else if (d == Direction::Up) moveYneg();
                else if (d == Direction::Down) moveYpos();
            }
        }
        window.draw(shape);
        
    }
        

    
}

void Robot::moveXpos(){
    shape.move(speed, 0);
}
void Robot::moveXneg(){
    shape.move(-speed, 0);
}
//giu
void Robot::moveYpos(){
    shape.move(0, speed);
}
void Robot::moveYneg(){
    shape.move(0, -speed);
}
Direction Robot::getNewDirection(int tile){
    int currentRow = currentTile / map->getCols();
    int currentCol = currentTile % map->getCols();

    int targetRow = tile / map->getCols();
    int targetCol = tile % map->getCols();

    if (targetRow < currentRow) return Direction::Up;
    if (targetRow > currentRow) return Direction::Down;
    if (targetCol < currentCol) return Direction::Left;
    if (targetCol > currentCol) return Direction::Right;
    return Direction::None; // già sulla tile

}

void Robot::placeRobot(int c, int r){
    std::cout<<"Robot posizionato\n";
    //x = c * map.getTileSize()+map.getTileSize()/2;
    x = c*map->getTileSize()+map->getTileSize()/2;
    x-=25;
    y = r * map->getTileSize()+map->getTileSize()/2;
    y-=25;
    robotPlaced = true; 
    setX(x);
    setY(y);
}