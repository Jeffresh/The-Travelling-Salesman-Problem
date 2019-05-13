
#ifndef GRAPH_AM_HPP
#define GRAPH_AM_HPP


// Class used to represent a  weighted graph using an adjacency matrix: 

#include <cassert>
#include <iostream>
#include <set>
#include <fstream>

template<typename T>
class Graph
{
    public:

    typedef int Vertex;
    typedef T** Adjacency_Matrix;
    typedef std::pair<Vertex,Vertex> Edge;
    typedef std::set<Edge> Edges; 

    Graph(); //empty graph.
    Graph(size_t k_nodes); // random graph with size k. // not implemented
    Graph(Edges); // construct a graph given a set of Edges. // not implemented
    Graph(const char*); // contruct a graph given a file that represent the edges.

    Graph(const Graph&); //not implemented
    Graph& operator =(const Graph&); //not implemented
    
    
    int num_vertices(){ return n_vertices_;};
    int num_edges(){return n_edges_;}

    const int num_vertices()const{ return n_vertices_;};
    const int num_edges()const{return n_edges_;}

    Adjacency_Matrix& adMat(){ return am_;}
    const Adjacency_Matrix& adlist()const{return am_;};

    friend std::ostream &operator<<(std::ostream& os, const Graph& g);
    // friend void ncol2SAT(const Graph& g,size_t ncol);


    

    private:
    
    Adjacency_Matrix am_;
    size_t n_vertices_;
    size_t n_edges_;


};


template<typename T>
Graph<T>::Graph(const char* name_file)
{
    std::ifstream myfile(name_file);
    std::string line;
    int a;
    size_t pos1,pos2, end;
    const char* b="\0";
    int i =0;
    n_edges_ = 0;
    n_vertices_ =0;

    // fprintf (myfile, "%f %s", 3.1416, "PI");

    // if(myfile.is_open())
    // {

    //     while ( getline (myfile,line) )
    //     {
    //         pos1 = line.find(":")+1;

    //         end =line.find(";");
    //         adl_.push_back(std::vector<Vertex>());

            
    //         do
    //         {

    //             pos2 = line.find(":", pos1);
                
    //             if(pos2== std::string::npos)
    //                 pos2 =end;
                
    //             std::string substring = line.substr(pos1, pos2-pos1);
    //             adl_[i].push_back(std::stoi(substring));

    //             pos1 = pos2+1;

    //             n_edges_++;
             

    //         }while(pos2!=end);

    //         pos1 =0;
    //         i++;


    //     }

    //     n_vertices_ =i;

    // }

    // else
    // {
    //     std::cout<<"Error opening the file";
    // }
    



    myfile.close();
}

// template<typename T>
// std::ostream &operator<<(std::ostream& os, const Graph<T>& g)
// {
//     int i=0;

//     for(auto lista:g.adl_)
//     {

//         for(auto nodo:lista)
//         {

//             os<<"< "<<i<<" , "<<nodo<<" >"<<" ";

//         }

//         os<<'\n'<<std::endl;
//         i++;


//     }

//     return os;
    
// }

// void ncol2SAT(const Graph& g, size_t n_col)
// {
//     std::ofstream myfile;
//     myfile.open ("dimacsformatSAT.txt");

//     int i=0;
//     int n_vertices = g.adl_.size();
//     int n_edges = 0;
//     int sub_index =0;
//     int vert=0;
//     int nodes = n_col;
//     int n_combinations = factorial(n_col)/(factorial(2)*factorial(n_col-2));

//     bool mask[nodes];

//     std::fill(mask,mask+nodes,false);

//     for(int i = nodes-1; i> nodes-1-2; i--)
//       mask[i] = true;

//     myfile << "p cnf "<<n_col*g.n_vertices_<<' '<<(1+n_combinations)*g.n_vertices_+n_col*g.n_edges_<<'\n';

//     for(auto lista:g.adl_)
//     {
//         myfile<<"c For each vertex "<<i<<std::endl;
//         for(size_t j = 1; j <= n_col; j++)
//         {
//             myfile<<j+sub_index<<' ';
//         }

//         myfile<<0<<'\n';

//         do 
//         {
//             for(int i = 0; i < n_col; i++)
//             {
//                 if(mask[i])
//                 myfile<<-(i+1+sub_index)<<' ';
//             }
//              myfile<<0<<'\n';
//         } while ( std::next_permutation(mask,mask+nodes) );

                

//         myfile<<"c For each edge "<<i<<std::endl;

//         for(auto nodo:lista)
//         {
//             for(size_t j = 1; j <= n_col; j++)
//                 myfile<<'-'<<(i * n_col+j)<<' '<<'-'<<nodo*n_col+j<<' '<<"0\n";
            
//             myfile<<'\n';

//         }



//         myfile<<'\n';
//         i++;
//         sub_index+=n_col;

//     }

//     myfile.close();
// }


#endif