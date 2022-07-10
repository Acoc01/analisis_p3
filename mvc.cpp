#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

//Edge
struct Edge{
    int u,v;
};

//Definitions for easy typing
typedef std::vector<Edge> Graph;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<vi::iterator> va;

//Approximate Minimum Vertex Cover
vi minvc(Graph G);

int main(){
    std::cout << "Ingrese cantidad de vertices" << '\n';
    int n;
    std::cin >> n;
    Graph G(n);
    std::cout << "Ingrese aristas" << '\n';
    for(int i = 0; i < n; ++i){
        int u,v;
        std::cin>>u>>v;
        G[i].u = u, G[i].v = v;
    }
    vi vcover = minvc(G);
    std::cout << "Aproximado: " << '\n';
    for(int i = 0; i < vcover.size(); ++i){
        std::cout << vcover[i] << " ";
    }std::cout << '\n';
    return 0;
}

vi minvc(Graph G){
    vi C; //Vertex vector
    Graph E = G; //A new instance of the original graph
    while(!E.empty()){ 
       int u = E[0].u;
       int v = E[0].v;
       //We only choose vertex that haven't been chosen yet
        if(std::find(C.begin(),C.end(),u) == C.end()){
            if(std::find(C.begin(),C.end(),v) == C.end()){
                C.push_back(u);
                C.push_back(v);
            }
        }
        //We erase always the first Edge.
       E.erase(E.begin());
    }
    return C;
}