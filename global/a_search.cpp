#include <iostream>
#include <string> 
#include <vector>
#include <utility>
#include <cstdint>
#include <stdlib.h>
#include <chrono>
#include <map>
#include <algorithm>
#include "node.hpp"
#include "priority_queue.hpp"
#include "inputOutput.h"
#define INFINITY 1000 //May lower it later, have to read about it

using namespace std;

//VERY IMPORTANT DO NOT FORGET UNDER ANY CIRCUMSTANCES: CHANGE MAX_LENGTH ARGUMENT IN SPRINT STATE

//state_map_t * h_map = new_state_map(); // contains the cost-to-goal for all states that have been generated
abstraction_t * abst[16];
state_map_t * pdb[16];
state_t state, abst_state;
state_t* child;
unsigned f_value, h_value, cost;
int hist, pdbNumber;
vector<int> path;
chrono::high_resolution_clock::time_point tstart, tend, tstartiter, tenditer;
string newline = "\n";
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

unsigned get_h_value(state_t* state){
    char staterep[40];
    unsigned h;
    int start, end, position, tile;

    sprint_state(staterep, 40, state);

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

}


unsigned get_h_value_max_pdb(state_t* state){
    int * value_pointer;
    int total = 0;
    for (int i = 0; i <  pdbNumber; i++){
        abstract_state(abst[i], state, &abst_state);
        value_pointer = state_map_get(pdb[i], &abst_state);
        total = max(total, (*value_pointer));
    }

    return total;
}

unsigned get_h_value_additive_pdb(state_t* state){
    int * value_pointer;
    int total = 0;
    for (int i = 0; i <  pdbNumber; i++){
        abstract_state(abst[i], state, &abst_state);
        value_pointer = state_map_get(pdb[i], &abst_state);
        total += (*value_pointer);
    }

    return total;
}


void a_star_search(string state_description){
    int ruleid, original_history;
    ruleid_iterator_t iter;
    hist = init_history;

    if (read_state(state_description.c_str(), &state)==-1){
        cout << "Error leyendo el estado inicial" << newline;
        return;
    }

    PriorityQueue<Node*> q;
    map<uint64_t, unsigned> distance;

    Node* node = new Node(&state);
    distance[hash_state(node->state)] = 0;
    h_value = get_h_value_max_pdb(node->state);
    q.Add(h_value, h_value, node);

    tstart = chrono::high_resolution_clock::now();

    while( !q.Empty() ) {
        node = q.Top();
        q.Pop();

        if (node->g < distance[hash_state(node->state)] || distance[hash_state(node->state)] == 0) {
            distance[hash_state(node->state)] = node->g;

            // Estado goal
            if (is_goal(node->state)) {
                tend = chrono::high_resolution_clock::now();
                chrono::milliseconds time_taken = chrono::duration_cast<std::chrono::milliseconds>( tend - tstart );
                cout << "SOL. ENCONTRADA" << "\n";
                cout << "Tiempo transcurrido: " << time_taken.count() << "\n"; 

                node->extract_path(path);
                return;
            }

            // Iteramos por los estados hijos del estado actual
            init_fwd_iter(&iter, node->state);
            while((ruleid = next_ruleid(&iter) ) >= 0){

                if (!fwd_rule_valid_for_history(hist,ruleid)){
                    continue;
                }
                original_history = hist;
                hist = next_fwd_history(hist, ruleid);
                child = new state_t;
                apply_fwd_rule(ruleid, node->state, child);

                h_value = get_h_value_max_pdb(child);
                if (h_value < INFINITY) {
                    f_value = node->g + get_fwd_rule_cost(ruleid) + h_value;
                    q.Add(f_value, f_value, node->make_node(child, ruleid));
                }

                hist = original_history;
            }
        }


    }
    return;

}

int main(int argc, char **argv){
    string instance, pdb_name;
    pdbNumber = 3;
    get_problem_instace(argv[1], instance);
    load_pdbs(abst, pdb, argv[2], pdbNumber);
    tstart = chrono::high_resolution_clock::now();
    a_star_search(instance);
    reconstruct_solution(instance, newline, path);
    cout << "FLAWLESS VICTORY\n";

    return 0;

}

