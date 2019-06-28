
#ifndef GRAPH_AM_HPP
#define GRAPH_AM_HPP


// Class used to represent a  weighted graph using an adjacency matrix: 
#include <regex>
#include <cassert>
#include <iostream>
#include <set>
#include <fstream>
#include <limits>
#include <cmath>
using namespace std;










class City
{
    public:

        City();

        City(int n, float x, float y): n{n},x{x},y{y}{}
        friend std::ostream &operator<<(std::ostream& os, const City& c);

   
        int n;

        float x,y;

  
};

std::ostream &operator<<(std::ostream& os, const City& c)
{
   

    os<<"< City: "<<c.n<<" | CoordX: "<<c.x<<" | CoordY: "<<c.y<<" >";

        

    os<<'\n'<<std::endl;
       


    

    return os;
    
}


class Graph
{
    public:

    typedef int Vertex;
    typedef float** Adjacency_Matrix;
    typedef std::pair<Vertex,Vertex> Edge;
    typedef std::set<Edge> Edges; 

    Graph(); //empty graph.
    Graph(size_t k_nodes); // random graph with size k. // not implemented
    Graph(Edges); // construct a graph given a set of Edges. // not implemented
    Graph(const char*,const char* ); // contruct a graph given a file that represent the edges.

    // Graph(const Graph&); //not implemented
    // Graph& operator =(const Graph&); //not implemented
    
    
    int num_vertices(){ return n_vertices_;};
    int num_edges(){return n_edges_;}

    int num_vertices()const{ return n_vertices_;};
    int num_edges()const{return n_edges_;}

    int optimal_cost(){return optimal_cost_;}
    const int optimal_cost()const{return optimal_cost_;}

    Adjacency_Matrix& adMat(){ return am_;}
    const Adjacency_Matrix& adMat()const{ return am_;}

    const Adjacency_Matrix& adlist()const{return am_;};

    friend std::ostream &operator<<(std::ostream& os, const Graph& g);
    // friend void ncol2SAT(const Graph& g,size_t ncol);


    

    private:
    
    float** am_;
    std::vector<City> cities;
    vector<pair<int,int>> edges;// tour solution

    float optimal_cost_;
    float aproximation_cost;

    int n_vertices_;
    size_t n_edges_;


};


Graph::Graph(const char* name_file, const char* name_file_tour)
{




    //process tsp file

    std::ifstream myfile(name_file);


    size_t pos1,pos2, end;
    int j =0;
    int n_edges_ = 0;
    int n_vertices_ =0;

    // std::ifstream myfile("TSPLIB/a280.tsp/a280.tsp");

    regex number("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?");
    regex word("[[:alpha:]]+(_)*[[:space:]]*(:)*(\\([[:space:]]*[[:alpha:]]+[[:space:]]*\\))*");

    regex more_space("(([[:space:]])[[:space:]]*)\t*");
    string clean_numbers,clean_words,line;
    //Replace with an empty string
    const string format="";
    const string format2=" ";

    string numbers{};

    int i=0;

    if(myfile.is_open())
    {

        while(getline (myfile,line) )
        {
            
            
            if(i>5) // se salta las 6 primeras lineas
            {
                clean_words=regex_replace(line,word,format,regex_constants::format_default);


                clean_words=regex_replace(clean_words,more_space,format2,regex_constants::format_default);


                
            

                clean_words = std::regex_replace(clean_words, std::regex("^\\s+"), std::string(""));
                clean_words = std::regex_replace(clean_words, std::regex("\\s+$"), std::string(""));
                // clean_words = std::regex_replace(clean_words, std::regex("\n+$"), std::string(""));

                numbers = clean_words+"\n";



                pos1 =0;
                end =numbers.find("\n");

                int city[3];

                int k =0;   

                do
                {
                    pos2 = numbers.find(" ", pos1);
                    
                    if(pos2 == std::string::npos)
                        pos2 =end;
                    
                    if(pos1!=end)
                    {
                   

                    std::string substring = numbers.substr(pos1, pos2-pos1);

                    // std::cout<<substring<<std::endl;

                    // std::cout<<stoi(substring)<<std::endl;

                    // if(!substring.find("\n",0)&&k<3)
                        city[k]= std::stoi(substring);

                    pos1 = pos2+1;

                    k++;
                    }
                    
                }while (pos2!=end);

                if(pos1!=end)
                cities.push_back(City(city[0],city[1],city[2]));
            }

            i++;

        
        }


        n_vertices_ = i -7;
        // cout<<"Número de vertices: "<<n_vertices_<<endl;

        // for(auto c:cities)
        //     cout<<c;

       



    }
    else
    {
            std::cout<<"Error opening the file";

    }




    myfile.close();

    //end process tsp file


    // initialize adjacency matrix


    am_ =new float*[n_vertices_];

    for(int i = 0; i < n_vertices_; ++i)
        am_[i] = new float[n_vertices_];


    for(auto o:cities)
    {
        for(auto d:cities)
        {
            if(o.n == d.n)
                am_[o.n-1][d.n-1] = std::numeric_limits<int>::max(); // equals to infinite
            else
            {
                am_[o.n-1][d.n-1] = sqrt(pow((o.x-d.x),2)+pow((o.y-d.y),2));
            }
            
        }
    }

    // end adjacency matrix

    



    //Processing tour file

    int cities[2];

    std::ifstream myfile_tour(name_file_tour);


   
    j =0;
    n_edges_ = 0;
    n_vertices_ =0;

    // std::ifstream myfile("TSPLIB/a280.tsp/a280.tsp");

    // regex number("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?");
    // regex word("[[:alpha:]]+(_)*[[:space:]]*(:)*(\\([[:space:]]*[[:alpha:]]+[[:space:]]*\\))*");

    // regex more_space("(([[:space:]])[[:space:]]*)\t*");
    clean_numbers= string(),clean_words = string(),line =string();
    //Replace with an empty string
  

    numbers = string();

    i=0;
    int k = 0;
    

    if(myfile_tour.is_open())
    {

        while(getline (myfile_tour,line) )
        {
            
            
            if(i>4) // se salta las 5 primeras lineas
            {
                clean_words=regex_replace(line,word,format,regex_constants::format_default);


                clean_words=regex_replace(clean_words,more_space,format2,regex_constants::format_default);


                
            

                clean_words = std::regex_replace(clean_words, std::regex("^\\s+"), std::string(""));
                clean_words = std::regex_replace(clean_words, std::regex("\\s+$"), std::string(""));
                // clean_words = std::regex_replace(clean_words, std::regex("\n+$"), std::string(""));

                numbers = clean_words+"\n";



                pos1 =0;
                end =numbers.find("\n");

                int city[3];


                do
                {
                    pos2 = numbers.find(" ", pos1);
                    
                    if(pos2 == std::string::npos)
                        pos2 =end;
                    
                    if(pos1!=end)
                    {
                   

                        std::string substring = numbers.substr(pos1, pos2-pos1);

                        if(substring!="-1")
                        {
                            // std::cout<<substring<<std::endl;
                            city[k]= std::stoi(substring);
                        }


                        // std::cout<<stoi(substring)<<std::endl;

                        // if(!substring.find("\n",0)&&k<3)

                        pos1 = pos2+1;

                    }
                    
                }while (pos2!=end);





                if(k ==1 && city[0]!=city[1])
                {
                    edges.push_back(pair<int,int>(city[0],city[1]));
                    city[0]=city[1];
                    k=0;

                }

                k++;


                
            }

            i++;

        
        }


        n_vertices_ = i -7;
        // std::cout<<"Número de vertices: "<<n_vertices_<<endl;

        // for(auto c:cities)
        //     std::cout<<c;


        // for(auto c:edges)
        //     std::cout<<c.first<<" "<<c.second<<std::endl;

       



    }
    else
    {
            std::cout<<"Error opening the file";

    }




    myfile.close();

    //end processing tour file


    //calculate optimal cost


    for(auto e:edges)
    {
        optimal_cost_+= am_[e.first-1][e.second-1];
    }

    optimal_cost_+= am_[edges[edges.size()-1].second][edges[0].first-1 ];


    // std::cout<<"Optimal Cost: "<<optimal_cost<<std::endl;

    // std::cout<<"N edges: "<<edges.size()<<std::endl;

    this->n_vertices_ = edges.size()+1;




   




}



#endif