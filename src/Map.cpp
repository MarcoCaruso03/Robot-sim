#include "Map.h"
#include <queue>

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
            //if(c%2==0)
            //    t.setType(TileType::Obstacle);
            //Test dijsktra 1
            if(r == 1 && c == 1){
                t.setType(TileType::Obstacle);
                std::cout<<"Osb\n";
            }
            /*if(r == 0 && c == 1){
                t.setType(TileType::Obstacle);
                std::cout<<"Osb\n";
            }*/
            if(r == 2 && c == 1){
                t.setType(TileType::Obstacle);
                std::cout<<"Osb\n";
            }
            if(r == 3 && c == 2){
                t.setType(TileType::Obstacle);
                std::cout<<"Osb\n";
            }
            if(r == 3 && c == 3){
                t.setType(TileType::Obstacle);
                std::cout<<"Osb\n";
            }               
            
            
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
            if(tiles[nodeID].getType() == TileType::Obstacle)
                continue;
            //non sono sul bordo superiore => c'è un nodo sopra
            if (r > 0){
                int upNodeID = (r-1)*cols+c; 
                if(tiles[upNodeID].getType() != TileType::Obstacle)
                    graph[nodeID].emplace_back(upNodeID, 1.0f);
            }
            // non sono sul bordo inferiore => c'è un nodo sotto
            if (r < rows - 1){
                int downNodeID = (r + 1) * cols + c;
                if(tiles[downNodeID].getType() != TileType::Obstacle)
                    graph[nodeID].emplace_back(downNodeID, 1.0f);
            }
            //non sono sul bordo sx => c'è un nodo sinistra
            if(c>0){
                int leftNodeID = r * cols + (c - 1);
                if(tiles[leftNodeID].getType() != TileType::Obstacle)
                    graph[nodeID].emplace_back(leftNodeID, 1.0f);
            }
            // Nodo destra
            if (c < cols - 1) {
                int rightNodeID = r * cols + (c + 1);
                if(tiles[rightNodeID].getType() != TileType::Obstacle)
                    graph[nodeID].emplace_back(rightNodeID, 1.0f);
            }
        }
    }   
}
const std::vector<std::vector<std::pair<int,float>>>& Map::getGraph() const{
    return graph; 
}
void Map::printGraph() const {
    for (int i = 0; i < graph.size(); ++i) {
        std::cout << "Nodo " << i << " -> ";
        for (const auto& [neighbor, weight] : graph[i]) {
            std::cout << "(" << neighbor << ", peso=" << weight << ") ";
        }
        std::cout << "\n";
    }
}

void Map::draw(sf::RenderWindow& window) const {
    for (const auto& tile : tiles) {
        tile.draw(window);  // Il metodo draw di Tile
    }
}


std::vector<int> Map::dijkstra(int start, int goal){
    int totalNodes = graph.size();
    //vector of distances 
    std::vector<float> distance (totalNodes, std::numeric_limits<float>::infinity());

    //vector of previous
    std::vector<int> previous(totalNodes, -1);

    distance[start]=0.0f;

    //priority queue 
    //std::pair<float, int>, is the distance and the node
    std::priority_queue<std::pair<float, int>,
                    std::vector<std::pair<float, int>>,
                    std::greater<std::pair<float, int>>> pq;
    pq.emplace(0.0f, start);

    //Algorithm: 
    while(!pq.empty()){
        //get the element with the shortest distance: 
        auto [dist, u] = pq.top(); 
        pq.pop();

        //get the neighbo of u and check the distances
        for(auto [v, weight] : graph[u]){
            if(distance[u] + weight < distance[v]){
                distance[v] = distance[u]+weight; 
                previous[v] = u; 
                pq.emplace(distance[v], v);
            }
        }
    }

    //reconstruction of the path 
    std::vector<int> path; 
    for(int at = goal; at!=-1; at = previous[at]){
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    return path; 

}
