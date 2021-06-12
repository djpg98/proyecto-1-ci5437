#include "inputOutput.h"

void reconstruct_solution(string state_description, string newline, vector<int> path){
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

void get_problem_instace(string file_name, string & instance){
    ifstream file;

    file.open(file_name, ios_base::in);

    getline(file, instance);

    file.close();
}