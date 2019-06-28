#include <iostream>
#include <ctime>
#include "Graph.hpp"
#include "antColony.hpp"



int main()
{

    Graph map("TSPLIB/kroC100.tsp/kroC100.tsp","TSPLIB/kroC100.opt.tour/kroC100.opt.tour" );
    // Graph map("TSPLIB/st70.tsp/st70.tsp","TSPLIB/st70.opt.tour/st70.opt.tour" );
    // Graph map("TSPLIB/pr76.tsp/pr76.tsp","TSPLIB/pr76.opt.tour/pr76.opt.tour" );
    // Graph map("TSPLIB/lin105.tsp/lin105.tsp","TSPLIB/lin105.opt.tour/lin105.opt.tour" );




    int max_it = 100;
    int num_ants = 100;
    float decay_factor = 0.1;
    float heuristic_coefficient = 2;
    float history_coefficient = 1;
    float greediness_factor = 0.9;
    bool elitist = false;



    float solution = 0;


    std::cout<< "Initializing ant_colony"<<std::endl;

    std::cout<< "Number of cities: "<<map.num_vertices()<<std::endl;
    std::cout<<"Optimal Cost: "<<map.optimal_cost()<<std::endl;




    clock_t start; 
    start = clock();

    float aproximation = ant_colony(map, max_it, num_ants, decay_factor, heuristic_coefficient,
    history_coefficient,greediness_factor,elitist); 

    clock_t end = clock() - start; 
    double timeACO = ((double)end)/CLOCKS_PER_SEC; // in seconds 



    std::cout<<"Time  ACO version: "<<timeACO<<std::endl;        
    std::cout<<"Aproximation  ACO version: "<<aproximation<<std::endl;    

    
    

   

}