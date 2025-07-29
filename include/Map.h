#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Tile.h"
#include <limits>

class Map{
    private: 
        int tilesSize = 50;
        std::vector<Tile> tiles;
        int rows; 
        int cols; 

        //lista di adiacenza per il grafo
        //std::vector<std::vector<int>> graph;
        std::vector<std::vector<std::pair<int,float>>> graph; 
    public: 
        //given the windows, the construct set the number of rows and cols and create the tiles (empty)
        Map(int const windowsWidth, int const windowHeight);
        Map() : tilesSize(50), rows(0), cols(0) {}

        //copy constructor 
        Map cloneStructureWithoutObstacles() const; 
        std::vector<Tile>& getTiles(); 
        void buildGraph();
        const std::vector<std::vector<std::pair<int,float>>>& getGraph() const;
        void printGraph() const; 
        void draw(sf::RenderWindow& window) const;
        std::vector<int> dijkstra(int start, int goal);
        int getTileSize(){return tilesSize;}
        int getCols(){return cols;}
        int getRows(){return rows;}
        void setBorderColorTile(sf::Color c, int id);
        void setColorPath(std::vector<int> p);
        void defaultColorTile(std::vector<int> p);
};