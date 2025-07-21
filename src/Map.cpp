#include "Map.h"

Map::Map(int const windowsWidth, int const windowHeight){
    cols = windowsWidth / tilesSize;
    rows = windowHeight / tilesSize;


    //generate the rect
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            //generete a rect in the right position 
            Tile t(tilesSize-1, tilesSize-1, tilesSize);
            t.setFillColor(sf::Color::White);
            t.setPosition(c*tilesSize, r*tilesSize);
            if(c%2==0)
                t.setType(TileType::Obstacle);
            tiles.push_back(t);
        }
    }
}
//the first const means => receive a pointer to a vector which cannot be modified 
//it is used to "protect" the internal data of the classe
//the second const means the function cannot modify the members of the class
const std::vector<Tile>& Map::getTiles() const {
    return tiles;
}
void Map::buildGraph(){
    int totalNodes = rows*cols; 
    graph.clear();
    graph.resize(totalNodes); 
    for(int r=0; r<rows; r++){
        for(int c=0; c<cols; c++){
            int nodeID= r*cols + c; 
            //non sono sul bordo superiore => c'è un nodo sopra
            if (r > 0){
                int upNodeID = (r-1)*cols+c; 
                graph[nodeID].push_back(upNodeID);
            }
            // non sono sul bordo inferiore => c'è un nodo sotto
            if (r < rows - 1){
                int downNodeID = (r + 1) * cols + c;
                graph[nodeID].push_back(downNodeID);
            }
            //non sono sul bordo sx => c'è un nodo sinistra
            if(c>0){
                int leftNodeID = r * cols + (c - 1);
                graph[nodeID].push_back(leftNodeID);
            }
            // Nodo destra
            if (c < cols - 1) {
                int rightNodeID = r * cols + (c + 1);
                graph[nodeID].push_back(rightNodeID);
            }
        }
    }   
}

const std::vector<std::vector<int>>& Map::getGraph() const{
    return graph; 
}
void Map::printGraph() const{
    for (int i = 0; i < graph.size(); ++i) {
        std::cout << "Nodo " << i << " -> ";
        for (int neighbor : graph[i]) {
            std::cout << neighbor << " ";
        }
        std::cout << "\n";
    }
}
void Map::draw(sf::RenderWindow& window) const {
    for (const auto& tile : tiles) {
        tile.draw(window);  // Il metodo draw di Tile
    }
}
