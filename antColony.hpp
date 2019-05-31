

#include "Graph.hpp"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <map>

//Calculate the cost.
//input: a tour and the cost matrix
//output: the cost.
float cost(vector<int>,float**);


//Generate a tour
std::vector<int>generate_solution(float** pheromone_matrix,float** cost_matrix,
 float heuristic_coefficient,float history_coefficient ,float greediness_factor, int n_cities);


//Generate the set of candidates in wich will be chosen the next city
std::map<int,float>generate_candidates(int origin,bool* visited,float** pheromone_matrix,float**cost_matrix,
float heuristic_coefficient, float history_coefficient, int n_cities);

//Upate of the pheromone_matrix per ant.
void update_pheromone_matrix_local(float ** pheromone_matrix,vector<int>local_tour,
float history_coefficient, float local_pheromone);


//Update to reinforce the best solution ()
void update_pheromone_matrix_global(float ** pheromone_matrix,vector<int>local_tour,float decay_factor, float best_cost);






float cost(vector<int> tour, float** mc)
{
    vector<pair<int,int>> edges{};// tour solution

    int n_cities = tour.size();

    for(int i = 0 ; i < n_cities; i++)
        edges.push_back(pair<int,int>(tour[i],tour[i+1]));

    float cost = 0;
    for(auto e:edges)
    {
        // std::cout<<mc[e.first-1][e.second-1]<<std::endl;
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

        // std::cout<<"Hola holita vamos a generate candidates"<<std::endl;

        map<int,float>candidates = generate_candidates(origin_end-1,visited,pheromone_matrix,cost_matrix,
        heuristic_coefficient, history_coefficient,n_cities);

        // std::cout<<"Hola holita salgo de generate candidates"<<std::endl;



        float prob = ((double) rand() / (RAND_MAX));



        //selection function

        if(prob<= greediness_factor) // common 0.9, the randomization and skip second calculation
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


                prob = ((double) rand() / (RAND_MAX)); 

                do
                {

                    p_candidate = it->second/sumatory;

                    it++;
                } while (it!= candidates.end() && p_candidate > prob);

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

    // std::cout<<"Hola holita valor de origin: "<<origin<<std::endl;




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
                                    float history_coefficient, float local_pheromone)
{

    vector<pair<int,int>> edges{};// tour solution

    float pheromore_value = 0.0; 

    int n_cities = local_tour.size();

    // for(int i =0 ; i<local_tour.size(); i++)
    //     std::cout<<"Camino: "<<local_tour[i]<<std::endl;



    for(int i =0 ; i<local_tour.size()-1; i++)
        edges.push_back(pair<int,int>(local_tour[i],local_tour[i+1]));


    // std::cout<<"Hormiga: "<<std::endl;


    int i = 0;
    for(auto e:edges)
    {
        // std::cout<<"loop: "<<i<<" < "<<e.first<<","<<e.second<<" >"<<std::endl;

        pheromore_value = ( (1.0-history_coefficient)*pheromone_matrix[e.first-1][e.second-1])
                            +(history_coefficient * local_pheromone);
        
        pheromone_matrix[e.first-1][e.second-1] = pheromore_value;
        pheromone_matrix[e.second-1][e.first-1] = pheromore_value;
        i++;

    }

    // std::cout<<"Hormiga: "<<std::endl;


    


    pheromore_value = ( (1.0-history_coefficient)*pheromone_matrix[ local_tour[n_cities-1]-1 ][local_tour[0]-1])
                        +(history_coefficient * local_pheromone);
    
    pheromone_matrix[local_tour[n_cities-1]-1][ local_tour[0]-1] = pheromore_value;
    pheromone_matrix[local_tour[0]-1][local_tour[n_cities-1]-1] = pheromore_value;


    

}

void update_pheromone_matrix_global(float ** pheromone_matrix,vector<int>local_tour,float decay_factor, float best_cost)
{

     vector<pair<int,int>> edges;// tour solution

    float pheromore_value = 0.0; 

    int n_cities = local_tour.size();

    for(int i =0 ; i<local_tour.size()-1; i++)
        edges.push_back(pair<int,int>(local_tour[i],local_tour[i+1]));

    for(auto e:edges)
    {
        pheromore_value = ( (1.0-decay_factor)*pheromone_matrix[e.first-1][e.second-1])
                            +(decay_factor*(1.0/best_cost));
        
        pheromone_matrix[e.first-1][e.second-1] = pheromore_value;
        pheromone_matrix[e.second-1][e.first-1] = pheromore_value;

    }


    pheromore_value = ( (1.0-decay_factor)*pheromone_matrix[ local_tour[n_cities-1]-1 ][local_tour[0]-1])
                       +(decay_factor*(1.0/best_cost));
    
    pheromone_matrix[local_tour[n_cities-1]-1][ local_tour[0]-1] = pheromore_value;
    pheromone_matrix[local_tour[0]-1][local_tour[n_cities-1]-1] = pheromore_value;

    
}





float ant_colony(const Graph& map, int max_it,int num_ants,
                    float decay_factor, float heuristic_coefficient,
                    float history_coefficient,float greediness_factor)
{
    std::cout<<"Inicio ant_colony"<<std::endl;



    // srand(1);

    // geneterate a initial tour solution
    int n_cities = map.num_vertices();
    
    // std::cout<<"Cuantos vertices: "<<n_cities<<std::endl;


    float** pheromone_matrix = new float* [n_cities];

    // std::cout<<"Creado puntero"<<n_cities<<std::endl;


    

    for(int i = 0; i < n_cities; i++)
    {

        pheromone_matrix[i] = new float[n_cities];
    }

    // std::cout<<"Me creo la matriz de feromonas"<<std::endl;
    


    std::vector<int>best_tour;

    for(size_t i = 0; i < n_cities; i++)
        best_tour.push_back(i+1);

    // std::cout<<"Genero una solucion inicial"<<std::endl;


    
    std::random_shuffle(best_tour.begin(),best_tour.end());

    // std::cout<<"La desordeno"<<std::endl;


    
    //best_cost = initial cost

    float best_cost = cost(best_tour,map.adMat());


    // std::cout<<"Calculo coste asociado: "<<best_cost<<std::endl;



    //get value of pheromone

    float local_pheromone = 1.0/(n_cities*best_cost);

    // std::cout<<"Inicializo feromona valor: "<<local_pheromone<<std::endl;


    //initialize pheromone matriz 

    for(size_t i = 0; i < n_cities; i++)
    {
        for (size_t j = 0; j < n_cities; j++)
        {
            pheromone_matrix[i][j] = local_pheromone;
        }
        
    }


    // std::cout<<"Inicializo matriz de feromonas"<<std::endl;



    std::vector<int> local_tour{};
    float local_cost = 0;
    

    for (size_t i = 0; i < max_it; i++)
    {
        for (size_t j = 0; j < num_ants; j++)// ants
        {
            // std::cout<<"Inicializa camino hormiga: "<<std::endl;

            //genetare a local solution. // lo suyo seria solo pasarle la matriz ni la euristica ni nada.
            local_tour = generate_solution(pheromone_matrix,map.adMat(),
            heuristic_coefficient,history_coefficient,greediness_factor,n_cities);

            // std::cout<<"Hormiga: "<<j+1<<" Ha generador un camino "<<std::endl;




            
            //calculate cost

            local_cost = cost(local_tour,map.adMat());

            // std::cout<<"Hormiga: "<<j+1<<" Ha generador un camino con coste: "<<local_cost<<std::endl;

            
            // if improvement, update best_cost and tour
            if(local_cost<best_cost)
            {
                best_cost = local_cost;
                best_tour = local_tour;
            }

            // update pheromone_matrix 

            update_pheromone_matrix_local(pheromone_matrix,local_tour,history_coefficient, local_pheromone);
            
            // std::cout<<"Hormiga: "<<j+1<<" Actualiza PH local "<<std::endl;

        }


        //update global de la matriz feromonica ( se hace con el mejor) elitist
        update_pheromone_matrix_global(pheromone_matrix,best_tour,decay_factor,best_cost);

        std::cout<<"Iteracion: "<<i<<"Best : "<<best_cost<<endl;

        

    }



    return best_cost;
    

}



