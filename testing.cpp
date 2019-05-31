#include <iostream>
#include <regex>
#include "Graph.hpp"


void imprimir(float** matrix, int n)
{
    for(int i = 0; i < n; ++i) 
    {
        for(int j = 0; j < n; ++j)
        {
          std::cout<<"| "<<matrix[i][j]<<" | ";
        }

        std::cout<<std::endl;
    }

    std::cout<<std::endl;


}






vector<pair<int,int>> edges{};

// class City
// {
//     public:

//         City(int n, float x, float y): n{n},x{x},y{y}{}
//         friend std::ostream &operator<<(std::ostream& os, const City& c);

   
//         int n;

//         float x,y;

  
// };


vector<City> cities;
float** mcoste;


void input()
{
    int n_vertices_ =6;

    cities.push_back(City(1,1,1));
    cities.push_back(City(2,2,2));
    cities.push_back(City(3,3,3));
    cities.push_back(City(4,4,4));
    cities.push_back(City(5,5,5));
    cities.push_back(City(6,6,6));

    mcoste=new float*[n_vertices_];

    for(int i = 0; i < n_vertices_; ++i)
        mcoste[i] = new float[n_vertices_];


    for(auto o:cities)
    {
        for(auto d:cities)
        {
            if(o.n == d.n)
                mcoste[o.n-1][d.n-1] = std::numeric_limits<int>::max(); // equals to infinite
            else
            {
                // mcoste[o.n-1][d.n-1] = sqrt(pow((o.x-d.x),2)+pow((o.y-d.y),2));
                mcoste[o.n-1][d.n-1] =1;
            }
            
        }
    }

    imprimir(mcoste,6);

    int city[2];


   for (size_t i = 1; i < 6; i++)
   {
       edges.push_back(pair<int,int>(i,i+1));
       
   }


    for(auto c:edges)
        std::cout<<c.first<<" "<<c.second<<std::endl;

    float optimal_cost;
    for(auto e:edges)
    {
        optimal_cost+= mcoste[e.first-1][e.second-1];
    }


    std::cout<<"Optimal Cost: "<<optimal_cost<<std::endl;
    std::cout<<"Optimal Cost: "<<optimal_cost<<std::endl;

   
             




    

}










int main()
{

    // Graph<int> G("TSPLIB/kroC100.tsp/kroC100.tsp","TSPLIB/kroC100.opt.tour/kroC100.opt.tour" );
    
    // input("TSPLIB/st70.tsp/st70.tsp");// checked
    // input("TSPLIB/eil76.tsp/eil76.tsp");// checked
    // input("TSPLIB/pr76.tsp/pr76.tsp"); // cheked
    // input("TSPLIB/kroC100.tsp/kroC100.tsp"); //cheked
    // input("TSPLIB/lin105.tsp/lin105.tsp"); //checked

    // input("TSPLIB/kroC100.opt.tour/kroC100.opt.tour");// checked

    // input();

            srand(1);



            // for(;;)
            // {

            // float prob = ((double) rand() / (RAND_MAX));

            // std::cout<<prob;
            // }



            vector<int> prueba;

            // prueba.fills(0);


            

            for(auto e: prueba)
            if(e!=0)
                std::cout<<e;


    

}