#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Tile.h"

class Map{
    private: 
        int tilesSize = 50;
        std::vector<Tile> tiles;
        int rows; 
        int cols; 

        //lista di adiacenza per il grafo
        std::vector<std::vector<int>> graph;
    public: 
        //given the windows, the construct set the number of rows and cols and create the tiles (empty)
        Map(int const windowsWidth, int const windowHeight);
        const std::vector<Tile>& getTiles() const; 
        void buildGraph();
        const std::vector<std::vector<int>>& getGraph() const;
        void printGraph() const; 
        void draw(sf::RenderWindow& window) const;
};