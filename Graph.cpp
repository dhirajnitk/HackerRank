#include <iostream>
#include <algorithm>
#include <list>
#include <unordered_map>
#include <unordered_set>
using namespace std;
class Graph{
    private:
        public: class Node;
        unordered_map<int,Node*> nodeLookUp;
        Node* getNode(int id) {
            return nodeLookUp[id];
        }
        bool hasPathDFS( Node * source, Node * destination, unordered_set<int>visited){
            int id = source->getId();
            auto search = visited.find(id);
            if(search != visited.end()){
                return false;
            }
            else{
                visited.emplace(id);
                if(source == destination){
                    return true;
                }
                for (Node * child: source->getAdjacent()){
                    if(hasPathDFS(child, destination, visited))
                        return true;
                }
            }
            return false;
        }
        bool hasPathBFS( Node * source, Node * destination){
            list<Node*> nextToVisit;
            unordered_set<int>visited;
            nextToVisit.emplace_back(source);
            while(!nextToVisit.empty()) {
                Node* node = nextToVisit.front();
                nextToVisit.pop_front();
                if(node == destination)
                    return true;
                int id = node->getId();
                auto search = visited.find(id);
                if(search != visited.end()){
                    continue;
                }
                visited.emplace(id);
                for (Node * child: node->getAdjacent()){
                    nextToVisit.emplace_back(child);
                }

            }
            return false;
        }
    public:
         class Node{
            private:
                int id;
                list<Node*> adjacent;
            public:
                Node(int id) {
                    this->id = id;
                }
            list<Node*> & getAdjacent(){
                    return adjacent;
                }
            int  getId() {
                return id;
               }
                
        };
         void addNodes(list<int> nodes){
            for(int key: nodes){
                Node* node =  new Node(key);
                nodeLookUp.emplace(std::make_pair(key, node));
            }
        }
        void addEdge( int source, int destination) {
            Node *s = getNode(source);
            Node *d = getNode(destination);
            s->getAdjacent().push_back(d);
        }
        bool hasPathDFS( int source, int destination) {
            Node * s = getNode(source);
            Node * d = getNode(destination);
            unordered_set<int> visited;
            return hasPathDFS(s, d, visited);
        }
        bool hasPathBFS( int source, int destination) {
            Node * s = getNode(source);
            Node * d = getNode(destination);
            return hasPathBFS(s, d);
        }
};

int main(){
    Graph g;
    list<int> vertices = { 0,1,2,3,4,5,6};
    g.addNodes(vertices);
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(1,3);
    g.addEdge(2,4);
    g.addEdge(3,5);
    cout<<g.hasPathDFS(0,5)<<endl;
    cout<<g.hasPathBFS(0,5)<<endl;
}