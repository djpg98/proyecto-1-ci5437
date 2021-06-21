#include <iostream>
#include <string> 
#include <vector>
#include <utility>
#include <cstdint>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>
#include "inputOutput.h"
#define INFINITY 10000 //May lower it later, have to read about it

using namespace std;

//VERY IMPORTANT DO NOT FORGET UNDER ANY CIRCUMSTANCES: CHANGE MAX_LENGTH ARGUMENT IN SPRINT STATE

abstraction_t * abst[16];
state_map_t * pdb[16];
state_t state, child, abst_state, final_state;
unsigned f_value, h_value, cost, bound, initial_bound;
int hist,  explored, total_nodes, pdbNumber;
vector<int> path;
string newline = "\n";
chrono::high_resolution_clock::time_point tstart, tend, tstartiter, tenditer;
unsigned mtable0[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned mtable1[16] = {1, 0, 1, 2, 2, 1, 2, 3, 3, 2, 3, 4, 4, 3, 4, 5};
unsigned mtable2[16] = {2, 1, 0, 1, 3, 2, 1, 2, 4, 3, 2, 3, 5, 4, 3, 4};
unsigned mtable3[16] = {3, 2, 1, 0, 4, 3, 2, 1, 5, 4, 3, 2, 6, 5, 4, 3};
unsigned mtable4[16] = {1, 2, 3, 4, 0, 1, 2, 3, 1, 2, 3, 4, 2, 3, 4, 5};
unsigned mtable5[16] = {2, 1, 2, 3, 1, 0, 1, 2, 2, 1, 2, 3, 3, 2, 3, 4};
unsigned mtable6[16] = {3, 2, 1, 2, 2, 1, 0, 1, 3, 2, 1, 2, 4, 3, 2, 3};
unsigned mtable7[16] = {4, 3, 2, 1, 3, 2, 1, 0, 4, 3, 2, 1, 5, 4, 3, 2};
unsigned mtable8[16] = {2, 3, 4, 5, 1, 2, 3, 4, 0, 1, 2, 3, 1, 2, 3, 4};
unsigned mtable9[16] = {3, 2, 3, 4, 2, 1, 2, 3, 1, 0, 1, 2, 2, 1, 2, 3};
unsigned mtable10[16] = {4, 3, 2, 3, 3, 2, 1, 2, 2, 1, 0, 1, 3, 2, 1, 2};
unsigned mtable11[16] = {5, 4, 3, 2, 4, 3, 2, 1, 3, 2, 1, 0, 4, 3, 2, 1};
unsigned mtable12[16] = {3, 4, 5, 6, 2, 3, 4, 5, 1, 2, 3, 4, 0, 1, 2, 3};
unsigned mtable13[16] = {4, 3, 4, 5, 3, 2, 3, 4, 2, 1, 2, 3, 1, 0, 1, 2};
unsigned mtable14[16] = {5, 4, 3, 4, 4, 3, 2, 3, 3, 2, 1, 2, 2, 1, 0, 1};
unsigned mtable15[16] = {6, 5, 4, 3, 5, 4, 3, 2, 4, 3, 2, 1, 3, 2, 1, 0};
unsigned * mtable[16] = {mtable0, mtable1, mtable2, mtable3, mtable4, mtable5, mtable6, mtable7, mtable8, mtable9, mtable10, mtable11, mtable12, mtable13, mtable14, mtable15};


/* Hay dos versiones porque no sé si psvn me deja usar la regla al inverso así a lo malandro. La versión 1 supone que sí
   Por lo menos para n_puzzle funcionó a lo malandro. YEY
*/

/*This get_h_value just defines the manhattan distance heuristic. Later I will make sure it supports the others*/

/*unsigned get_h_value(state_t state){
    char staterep[40];
    unsigned h;
    int start, end, position, tile;

    sprint_state(staterep, 40, &state);

    string line(staterep);

    start = 0;
    position = 0;
    h = 0;
    end = line.find(' ');

    while(end != string::npos){
        if (line.substr(start, end - start).compare("B") != 0){
            tile = stoi(line.substr(start, end - start));
            h = h + mtable[tile][position];
        }

        position++;
        end++;
        start = end;
        end = line.find(' ', start);
    }

    return h;

}*/

unsigned get_h_value(state_t state){
    int * value_pointer;
    int total = 0;
    for (int i = 0; i <  pdbNumber; i++){
        abstract_state(abst[i], &state, &abst_state);
        value_pointer = state_map_get(pdb[i], &abst_state);
        total += (*value_pointer);
    }

    return total;
}

unsigned get_h_value_max_pdb(state_t state){
    int * value_pointer;
    int total = 0;
    for (int i = 0; i <  pdbNumber; i++){
        abstract_state(abst[i], &state, &abst_state);
        value_pointer = state_map_get(pdb[i], &abst_state);
        total = max(total, (*value_pointer));
    }

    return total;
}

void sigalrm_handler(int sig){
    /*cout << "Explored: " << explored << "\n";
    cout << "Time's up mate, maybe next time\n";*/
    cout << initial_bound << ", " << bound << ", " << -1 << ", " << total_nodes << ", " << explored << ", false, " << 900000 << newline;
    exit(EXIT_SUCCESS);
}

void sigint_handler(int sig){
    chrono::milliseconds time_taken = chrono::duration_cast<std::chrono::milliseconds>( tend - tstart );   
    cout << newline << "Tiempo transcurrido: " << time_taken.count() << "\n"; 
    cout << "Nodos explorados (Última iter.): " << explored << newline;
    exit(EXIT_FAILURE);
}

//Constant memory
pair<bool, unsigned> f_bounded_dfs_visit_1(unsigned g_value){
    unsigned current_min;
    int ruleid, original_history;
    ruleid_iterator_t iter;

    original_history = hist;

    f_value = g_value + h_value;

    if (f_value > bound){

        return make_pair(false, f_value);
    }

    if (h_value == 0){
        return make_pair(true, g_value);
    }

    current_min = INFINITY; 

    init_fwd_iter(&iter, &state);

    while((ruleid = next_ruleid(&iter) ) >= 0){

        if (!fwd_rule_valid_for_history(hist,ruleid)){
            continue;
        }
        explored++;
        hist = next_fwd_history(hist, ruleid);
        cost = g_value + get_fwd_rule_cost(ruleid);
        apply_fwd_rule(ruleid, &state, &child);
        copy_state(&state, &child);

        h_value = get_h_value_max_pdb(state);
        if (h_value < INFINITY){
            path.push_back(ruleid);
            pair<bool, unsigned> ret_value = f_bounded_dfs_visit_1(cost);
            if (ret_value.first){
                return make_pair(true, ret_value.second);
            }

            current_min = (ret_value.second < current_min) ? ret_value.second : current_min;
            path.pop_back();

        }

        hist = original_history;
        apply_bwd_rule(ruleid, &state, &child);
        //cout << "END HISTORY " << hist << "\n";
        copy_state(&state, &child);

    }

    return make_pair(false, current_min);
    

}

void ida_search_1(string state_description){
    int64_t totalNodes, numAtD;  // counters

    if (read_state(state_description.c_str(), &state)==-1){
        cout << "Error leyendo el estado inicial" << newline;
        exit(EXIT_FAILURE);
    }

    signal(SIGALRM, &sigalrm_handler);  // set a signal handler
    signal (SIGINT,&sigint_handler);
    alarm(900);  // set an alarm for 900 seconds from now

    tstart = chrono::high_resolution_clock::now();

    bound = get_h_value_max_pdb(state);
    initial_bound = bound;
    total_nodes = 0;

    while (true){
        hist = init_history;
        explored = 0;
        //cout << "Nueva iter." << bound << "\n";
        h_value = get_h_value_max_pdb(state);
        pair<bool, unsigned> ret_value = f_bounded_dfs_visit_1(0);
        if (ret_value.first){
            tend = chrono::high_resolution_clock::now();
            chrono::milliseconds time_taken = chrono::duration_cast<std::chrono::milliseconds>( tend - tstart );
            /*cout << "SOL. ENCONTRADA" << "\n";
            cout << "Costo sol: " << ret_value.second << "\n";
            cout << "Tiempo transcurrido: " << time_taken.count() << "\n"; 
            cout << "Nodos explorados (Última iter.): " << explored << newline;*/
            total_nodes = total_nodes + explored;
            cout << initial_bound << ", " << bound << ", " << ret_value.second << ", " << total_nodes << ", " << explored << ", true, " << time_taken.count() << newline;
            return;
        }
        bound = ret_value.second;
        //cout << "Explored: " << explored << "\n";
        total_nodes = total_nodes + explored;
    }

}


//Linear memory
/*pair<bool, unsigned> f_bounded_dfs_visit_2(state_t state, unsigned bound, unsigned g_value){
    state_t child;
    unsigned f_value, h_value, cost, current_min;
    int * state_value;
    int d, ruleid, original_history;
    ruleid_iterator_t iter;

    //char staterep[40];

    original_history = hist;

    h_value = get_h_value(state);
    f_value = g_value + h_value;

    //sprint_state(staterep, 40, &state);

    if (f_value > bound){
        return make_pair(false, f_value);
    }

    if (h_value == 0){
        copy_state(&final_state, &state);
        return make_pair(true, g_value);
    }

    explored++;

    state_map_add(prueba, &state, g_value);

    current_min = INFINITY; 

    init_fwd_iter(&iter, &state);

    while((ruleid = next_ruleid(&iter) ) >= 0){

        if (!fwd_rule_valid_for_history(hist,ruleid)){
            continue;
        }

        hist = next_fwd_history(hist, ruleid);
        cost = g_value + get_fwd_rule_cost(ruleid);
        apply_fwd_rule(ruleid, &state, &child);

        state_value = state_map_get(prueba, &child);
        if ((state_value != NULL) && (*state_value <= cost)){
            hist = original_history;
            continue;
        }

        if (get_h_value(child) < INFINITY){
            path.push_back(ruleid);
            pair<bool, unsigned> ret_value = f_bounded_dfs_visit_2(child, bound, cost);
            if (ret_value.first){
                return make_pair(true, ret_value.second);
            }
            current_min = (ret_value.second < current_min) ? ret_value.second : current_min;
            path.pop_back();

        }

        hist = original_history;

    }

    return make_pair(false, current_min);
    

}

void ida_search_2(string state_description){
    state_t state;
    int64_t totalNodes, numAtD;  // counters
    unsigned bound;
    //int i = 0;

    if (read_state(state_description.c_str(), &state)==-1){
        cout << "Error leyendo el estado inicial" << newline;
        exit(EXIT_FAILURE);
    }

    signal(SIGALRM, &sigalrm_handler);  // set a signal handler
    alarm(900);  // set an alarm for 900 seconds from now

    auto tstart = chrono::high_resolution_clock::now();

    bound = get_h_value(state);

    while (true){
        prueba = new_state_map();
        hist = init_history;
        explored = 0;
        cout << "Nueva iter." << bound << "\n";
        pair<bool, unsigned> ret_value = f_bounded_dfs_visit_2(state, bound, 0);
        if (ret_value.first){
            auto tend = chrono::high_resolution_clock::now();
            chrono::milliseconds time_taken = chrono::duration_cast<std::chrono::milliseconds>( tend - tstart );
            cout << "SOL. ENCONTRADA" << "\n";
            cout << "Costo sol: " << ret_value.second << "\n";
            cout << "Tiempo transcurrido: " << time_taken.count() << "\n"; 
            return;
        }
        bound = ret_value.second;
        cout << "Explored: " << explored << "\n";
        destroy_state_map(prueba);
        //i++;
    }

}*/

int main(int argc, char **argv){
    vector<string>::iterator instanceIter;
    vector<string> instances;
    string instance, pdb_name;
    pdbNumber = 3;
    get_all_instances(argv[1], instances);
    //get_problem_instace(argv[1],instance);
    cout << "value, valueF, solution, nodesT, nodesF, solution, sec" << newline;
    load_pdbs(abst, pdb, argv[2], pdbNumber);
    for (instanceIter = instances.begin(); instanceIter != instances.end(); instanceIter++){
        ida_search_1(*instanceIter);
    }
    //reconstruct_solution(instance, newline, path);
    cout << "FLAWLESS VICTORY\n";

    return 0;

}

