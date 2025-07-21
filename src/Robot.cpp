#include "Robot.h"

Robot::Robot(int initX, int initY, int initR){
    x=initX; 
    y=initY;
    r=initR;
    shape=sf::CircleShape(r);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(sf::Vector2f(x,y));


}
void Robot::setX(int new_x){
    x=new_x;
}
void Robot::setY(int new_y){
    y=new_y;
}
void Robot::update(sf::RenderWindow& window){
    //moveYpos();
    window.draw(shape);
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