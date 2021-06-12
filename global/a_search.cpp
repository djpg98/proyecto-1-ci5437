#include <iostream>
#include <string> 
#include <vector>
#include <utility>
#include <cstdint>
#include <stdlib.h>
#include <map>
#include "node.h"
#include "priority_queue.hpp"
#define INFINITY 1000 //May lower it later, have to read about it

using namespace std;

//VERY IMPORTANT DO NOT FORGET UNDER ANY CIRCUMSTANCES: CHANGE MAX_LENGTH ARGUMENT IN SPRINT STATE

//state_map_t * h_map = new_state_map(); // contains the cost-to-goal for all states that have been generated
state_t state;
state_t* child;
unsigned f_value, h_value, cost;
int hist;
vector<int> path;
string newline = "\n";
unsigned mtable0[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned mtable1[9] = {0, 1, 2, 1, 2, 3, 2, 3, 4};
unsigned mtable2[9] = {1, 0, 1, 2, 1, 2, 3, 2, 3};
unsigned mtable3[9] = {2, 1, 0, 3, 2, 1, 4, 3, 2};
unsigned mtable4[9] = {1, 2, 3, 0, 1, 2, 1, 2, 3};
unsigned mtable5[9] = {2, 1, 2, 1, 0, 1, 2, 1, 2};
unsigned mtable6[9] = {3, 2, 1, 2, 1, 0, 3, 2, 1};
unsigned mtable7[9] = {2, 3, 4, 1, 2, 3, 0, 1, 2};
unsigned mtable8[9] = {3, 2, 3, 2, 1, 2, 1, 0, 1};
unsigned * mtable[9] = {mtable0, mtable1, mtable2, mtable3, mtable4, mtable5, mtable6, mtable7, mtable8};



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

void a_star_search(string state_description){
    int ruleid;
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
    h_value = get_h_value(node->state);
    q.Add(h_value, h_value, node);

    char str_state[40];

    while( !q.Empty() ) {
        node = q.Top();
        q.Pop();

        if (node->g < distance[hash_state(node->state)] || !distance.empty()) {
            distance[hash_state(node->state)] = node->g;

            // Estado goal
            if (is_goal(node->state)) {
                node->extract_path(path);
                return;
            }

            // Iteramos por los estados hijos del estado actual
            init_fwd_iter(&iter, node->state);
            while((ruleid = next_ruleid(&iter) ) >= 0){

                if (!fwd_rule_valid_for_history(hist,ruleid)){
                    continue;
                }
                hist = next_fwd_history(hist, ruleid);
                child = new state_t;
                apply_fwd_rule(ruleid, node->state, child);

                h_value = get_h_value(child);
                if (h_value < INFINITY) {
                    f_value = node->g + get_fwd_rule_cost(ruleid) + h_value;
                    q.Add(f_value, f_value, node->make_node(child, ruleid));
                }

                hist = next_bwd_history(hist, ruleid);
            }
        }


    }
    return;

}

void reconstruct_solution(string state_description){
    char str_state[40];
    state_t state, child;
    vector<int>::iterator iter;

    if (read_state(state_description.c_str(), &state)==-1){
        cout << "Error leyendo el estado inicial" << newline;
    }

    sprint_state(str_state, 40, &state);

    cout << str_state << "\n";

    for (iter = path.begin(); iter != path.end(); iter++){
        apply_fwd_rule(*iter, &state, &child);

        sprint_state(str_state, 40, &child);

        cout << str_state << "\n";
        copy_state(&state, &child);
    }

}

int main(int argc, char **argv){
    string hey = "1 8 2 b 4 3 7 6 5";
    a_star_search(hey);
    reconstruct_solution(hey);
    return 0;
}

