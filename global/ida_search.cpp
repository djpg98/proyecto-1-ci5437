#include <iostream>
#include <vector>
#include <utility>
#define INFINITY = 1000 //May lower it later, have to read about it

using namespace std;

state_t state, final_state;
vector<int> path;
string newline = "\n";

/* FUNCTIONS CALLED BUT NOT YET IMPLEMENTED 
- get_h_value(state_t s): Value of heuristic h, for state_t s.
*/

/* Hay dos versiones porque no sé si psvn me deja usar la regla al inverso así a lo malandro. La versión 1 supone que sí
   Y sí voy a escribir en spanglish
*/

//Constant memory
void ida_search_1(string state_description){
    int64_t totalNodes, numAtD;  // counters
    unsigned bound;

    if (read_state(state_description.c_str(), &state)==-1){
        cout << "Error leyendo el estado inicial" << newline;
    }

    bound = get_h_value(state);

    while (true){
        pair<bool, unsigned> ret_value = f_bounded_dfs_visit_1(bound, 0);
        if (ret_value.first){
            return
        }
        bound = ret_value.second
    }

}

pair<bool, unsigned> f_bounded_dfs_visit_1(unsigned bound, unsigned g_value){
    unsigned f_value, h_value, cost, current_min;
    int d, ruleid;
    ruleid_iterator_t iter;

    h_value = get_h_value(state);
    f_value = g_value + h_value;

    if (f_value > bound){
        return make_pair(false, f_value);
    }

    if (h_value == 0){
        return make_pair(true, g_value);
    }

    current_min = INFINITY; 

    init_fwd_iter(&iter, &state);

    for((ruleid = next_ruleid(&iter) ) >= 0){
        cost = g_value + get_fwd_rule_cost(ruleid);
        apply_fwd_rule(ruleid, &state, &state);

        if (get_h_value(state) < INFINITY){
            path.push_back(ruleid);
                    pair<bool, unsigned> ret_value = f_bounded_dfs_visit_1(bound, 0);
            if (ret_value.first){
                return;
            }
            current_min = (ret_value.second < current_min) ? ret_value.second : current_min;
            path.pop_back();

        }

        //I am not sure if this applies the same operator as before but backwards or if it applies a different one
        apply_bwd_rule(ruleid, &state, &state)

    }
    

}

//Linear memory
void ida_search_2(string state_description){
    state_t state;
    int64_t totalNodes, numAtD;  // counters
    unsigned bound;

    if (read_state(state_description.c_str(), &state)==-1){
        cout << "Error leyendo el estado inicial" << newline;
    }

    bound = get_h_value(state);

    while (true){
        pair<bool, unsigned> ret_value = f_bounded_dfs_visit_2(state, bound, 0);
        if (ret_value.first){
            return
        }
        bound = ret_value.second
    }

}

pair<bool, unsigned> f_bounded_dfs_visit_2(state_t state, unsigned bound, unsigned g_value){
    state_t child;
    unsigned f_value, h_value, cost, current_min;
    int d, ruleid;
    ruleid_iterator_t iter;

    h_value = get_h_value(state);
    f_value = g_value + h_value;

    if (f_value > bound){
        return make_pair(false, f_value);
    }

    if (h_value == 0){
        copy_state(&final_state, &state);
        return make_pair(true, g_value);
    }

    current_min = INFINITY; 

    init_fwd_iter(&iter, &state);

    for((ruleid = next_ruleid(&iter) ) >= 0){
        cost = g_value + get_fwd_rule_cost(ruleid);
        apply_fwd_rule(ruleid, &state, &child);

        if (get_h_value(state) < INFINITY){
            path.push_back(ruleid);
            pair<bool, unsigned> ret_value = f_bounded_dfs_visit_2(child, bound, 0);
            if (ret_value.first){
                return;
            }
            current_min = (ret_value.second < current_min) ? ret_value.second : current_min;
            path.pop_back();

        }

    }
    

}

