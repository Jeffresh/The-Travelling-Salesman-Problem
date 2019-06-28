

#include "Graph.hpp"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <map>

//Calculate the cost.
float cost(vector<int> tour,float** mc);


//Generate a tour
std::vector<int>generate_solution(float** pheromone_matrix,float** cost_matrix,
 float heuristic_coefficient,float history_coefficient ,float greediness_factor, int n_cities);


//Generate the set of candidates in wich will be chosen the next city
std::map<int,float>generate_candidates(int origin,bool* visited,float** pheromone_matrix,float**cost_matrix,
float heuristic_coefficient, float history_coefficient, int n_cities);

//Upate of the pheromone_matrix per ant.
void update_pheromone_matrix_local(float ** pheromone_matrix,vector<int>local_tour,
float history_coefficient, float local_pheromone,float decay_factor);


//Update to reinforce the best solution(Elitist.)
void update_pheromone_matrix_global(float ** pheromone_matrix,
vector<int>local_tour,float history_coefficient,float decay_factor, float best_cost);

//Main algorithm of ACO
float ant_colony(const Graph& map, int max_it,int num_ants,
                    float decay_factor, float heuristic_coefficient,
                    float history_coefficient,float greediness_factor,bool elitist);






float cost(vector<int> tour, float** mc)
{

    vector<pair<int,int>> edges{};// tour solution

    int n_cities = tour.size();

    for(int i = 0 ; i < n_cities; i++)
        edges.push_back(pair<int,int>(tour[i],tour[i+1]));



    float cost = 0;

    for(auto e:edges)
    {
        //  std::cout<<mc[e.first-1][e.second-1]<<std::endl;
        cost+= mc[e.first-1][e.second-1];
    }


    
    //the cycle
    cost+= mc[ tour[n_cities-1] -1 ][ tour[0] -1 ];


    return cost;


}




std::vector<int>generate_solution(float** pheromone_matrix,float** cost_matrix,
                                float heuristic_coefficient,float history_coefficient ,float greediness_factor, int n_cities)
{

    vector<int> local_tour;
    bool visited [n_cities];

    for (size_t i = 0; i < n_cities; i++)
        visited[i] = false;
 
    

    int origin_end = rand()%n_cities + 1; // generate de oring_end city randomly 1...n_cities 
    local_tour.push_back(origin_end);
    visited[origin_end-1] = true;




    do
    {


        map<int,float>candidates = generate_candidates(origin_end-1,visited,pheromone_matrix,cost_matrix,
        heuristic_coefficient, history_coefficient,n_cities);




        float prob = ((double) rand() / (RAND_MAX));



        //selection function

        if(prob< greediness_factor) // common 0.9, the randomization and skip second calculation
        {


            pair<int,float> city;
            city.first =0; city.second =0;
            for(auto a:candidates)
            {
                if(a.second> city.second)
                {
                    city.first =a.first;
                    city.second = a.second;

                }
            }

            int next_city = city.first;
            local_tour.push_back(next_city);
            visited[next_city-1]= true;

        }
        else
        {

            float sumatory = 0;


            map<int,float>::iterator it = candidates.begin();

            for(auto city:candidates)
                sumatory += city.second;


            if(sumatory != 0)
            {

                float p_candidate = 0;


                prob = ((float) rand() / (RAND_MAX)); 

                do
                {

                    prob -= it->second/sumatory;

                    it++;
                } while (it!= candidates.end() && prob < 0.0);

                it--;
                local_tour.push_back(it->first);

                visited[it->first-1]= true;
            }
            else// if else is equal to 0 chose randomly
            {
                map<int,float>::iterator it= candidates.begin();
                int city = rand()%candidates.size();

                for (size_t i = 0; i < city; i++)
                it++;

                it--;
              
                

                

                local_tour.push_back((it)->first);
                visited[it->first-1]= true;

            }
            
            

        }

        //end selection function

    }while (local_tour.size() < n_cities);



    return local_tour;
    


}


std::map<int,float>generate_candidates(int origin,bool* visited,float** pheromone_matrix,float**cost_matrix,
                                        float heuristic_coefficient, float history_coefficient, int n_cities)
{
    float local_history = 0, local_distance = 0, local_heuristic = 0, partial_cost = 0;

    std::map<int,float> candidates{};





    for(int i = 0 ; i < n_cities; i++)
    {
        if(!visited[i])
        {

            local_history = pow( pheromone_matrix[origin][i], history_coefficient);
            local_heuristic = pow( (1.0/cost_matrix[origin][i]) ,heuristic_coefficient);
            partial_cost = local_heuristic * local_history;

            candidates.insert(make_pair(i+1,partial_cost));



        }


    }


    return candidates;


}

void update_pheromone_matrix_local(float ** pheromone_matrix,vector<int>local_tour,
                                    float history_coefficient, float local_pheromone,float decay_factor)
{

    vector<pair<int,int>> edges{};// tour solution

    float pheromore_value = 0.0; 

    int n_cities = local_tour.size();



    for(int i =0 ; i<local_tour.size()-1; i++)
        edges.push_back(pair<int,int>(local_tour[i],local_tour[i+1]));





    int i = 0;
    for(auto e:edges)
    {

        pheromore_value = ( (1.0-decay_factor)*pheromone_matrix[e.first-1][e.second-1])+
        (history_coefficient * local_pheromone);
        // pheromore_value = (history_coefficient * local_pheromone);
        
        pheromone_matrix[e.first-1][e.second-1] = pheromore_value;
        pheromone_matrix[e.second-1][e.first-1] = pheromore_value;
        i++;

    }



    


    pheromore_value = ( (1.0-decay_factor)*pheromone_matrix[ local_tour[n_cities-1]-1 ][local_tour[0]-1])
                        +(history_coefficient * local_pheromone);
    
    pheromone_matrix[local_tour[n_cities-1]-1][ local_tour[0]-1] = pheromore_value;
    pheromone_matrix[local_tour[0]-1][local_tour[n_cities-1]-1] = pheromore_value;


    

}

void update_pheromone_matrix_global(float ** pheromone_matrix,vector<int>best_tour,
                                    float history_coefficient,float decay_factor, float best_cost)
{

     vector<pair<int,int>> edges;// tour solution

    float pheromore_value = 0.0; 

    int n_cities = best_tour.size();

    for(int i =0 ; i<best_tour.size()-1; i++)
        edges.push_back(pair<int,int>(best_tour[i],best_tour[i+1]));

    for(auto e:edges)
    {
        pheromore_value = ( (1.0-decay_factor)*pheromone_matrix[e.first-1][e.second-1])
                            +(history_coefficient*(1.0/best_cost));
        
        pheromone_matrix[e.first-1][e.second-1] = pheromore_value;
        pheromone_matrix[e.second-1][e.first-1] = pheromore_value;

    }


    pheromore_value = ( (1.0-decay_factor)*pheromone_matrix[ best_tour[n_cities-1]-1 ][best_tour[0]-1])
                       +(history_coefficient*(best_cost));
    
    pheromone_matrix[best_tour[n_cities-1]-1][best_tour[0]-1] = pheromore_value;
    pheromone_matrix[best_tour[0]-1][best_tour[n_cities-1]-1] = pheromore_value;

    
}


float ant_colony(const Graph& map, int max_it,int num_ants,
                    float decay_factor, float heuristic_coefficient,
                    float history_coefficient,float greediness_factor,bool elitist)
{



    srand(1);

    // geneterate a initial tour solution
    int n_cities = map.num_vertices();
    


    float** pheromone_matrix = new float* [n_cities];



    

    for(int i = 0; i < n_cities; i++)
    {

        pheromone_matrix[i] = new float[n_cities];
    }

    


    std::vector<int>best_tour{};

    for(size_t i = 0; i < n_cities; i++)
        best_tour.push_back(i+1);



    
    std::random_shuffle(best_tour.begin(),best_tour.end());





    
    //best_cost = initial cost

    float best_cost = cost(best_tour,map.adMat());

    std::cout<<"Iteracion: 0  Best : "<<best_cost<<endl;






    //get value of pheromone

    float local_pheromone = 1.0/(n_cities*best_cost);



    //initialize pheromone matrix

    for(size_t i = 0; i < n_cities; i++)
    {
        for (size_t j = 0; j < n_cities; j++)
        {
            pheromone_matrix[i][j] = local_pheromone;
        }
        
    }





    std::vector<int> local_tour{};
    float local_cost = 0;


    

    for (size_t i = 0; i < max_it; i++)
    {
        for (size_t j = 0; j < num_ants; j++)// ants
        {

            //genetare a local solution. // lo suyo seria solo pasarle la matriz ni la euristica ni nada.

            local_tour = generate_solution(pheromone_matrix,map.adMat(),
            heuristic_coefficient,history_coefficient,greediness_factor,n_cities);





            
            //calculate cost

            local_cost = cost(local_tour,map.adMat());


            
            // if improvement, update best_cost and tour
            if(local_cost<best_cost)
            {
                best_cost = local_cost;
                best_tour = local_tour;
            }

            // update pheromone_matrix 

            update_pheromone_matrix_local(pheromone_matrix,local_tour,history_coefficient, local_pheromone,decay_factor);
            
        }


        //update global de la matriz feromonica ( with the best solution and tour) Elitist version

        if(elitist)
        update_pheromone_matrix_global(pheromone_matrix,best_tour,history_coefficient,decay_factor,best_cost);

        std::cout<<"Iteration: "<<i<<" Best : "<<best_cost<<endl;

        

    }



    return best_cost;
    

}



