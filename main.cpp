#include <iostream>
#include "Graph.hpp"
#include "antColony.hpp"





int main()
{

    // Graph map("TSPLIB/kroC100.tsp/kroC100.tsp","TSPLIB/kroC100.opt.tour/kroC100.opt.tour" );
    // Graph map("TSPLIB/st70.tsp/st70.tsp","TSPLIB/st70.opt.tour/st70.opt.tour" );
    // Graph map("TSPLIB/pr76tsp/pr76.tsp","TSPLIB/pr76.opt.tour/pr76.opt.tour" );
    Graph map("TSPLIB/lin105.tsp/lin105.tsp","TSPLIB/lin105.opt.tour/lin105.opt.tour" );




    int max_it = 1000;
    int num_ants = 105;
    float decay_factor = 0.7;
    float heuristic_coefficient = 2;
    float history_coefficient = 1;
    float greediness_factor = 0.0;


    float aprox_solution = 0;

    std::cout<< "Voy a iniciar ant_colony"<<std::endl;

    std::cout<< "Número de vertices: "<<map.num_vertices()<<std::endl;
    std::cout<<"Optimal Cost: "<<map.optimal_cost()<<std::endl;




    aprox_solution = ant_colony(map, max_it, num_ants, decay_factor, heuristic_coefficient,
    history_coefficient,greediness_factor);



    
    // input("TSPLIB/st70.tsp/st70.tsp");// checked
    // input("TSPLIB/eil76.tsp/eil76.tsp");// checked
    // input("TSPLIB/pr76.tsp/pr76.tsp"); // cheked
    // input("TSPLIB/kroC100.tsp/kroC100.tsp"); //cheked
    // input("TSPLIB/lin105.tsp/lin105.tsp"); //checked

    // input("TSPLIB/kroC100.opt.tour/kroC100.opt.tour");// checked


    

}