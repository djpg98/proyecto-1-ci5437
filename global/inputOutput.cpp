#include "inputOutput.h"

void reconstruct_solution(string state_description, string newline, vector<int> path){
    char str_state[120];
    state_t state, child;
    vector<int>::iterator iter;

    if (read_state(state_description.c_str(), &state)==-1){
        cout << "Error leyendo el estado inicial" << newline;
    }

    sprint_state(str_state, 120, &state);

    cout << str_state << "\n";

    for (iter = path.begin(); iter != path.end(); iter++){
        apply_fwd_rule(*iter, &state, &child);

        sprint_state(str_state, 120, &child);

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

void get_all_instances(string file_name, vector<string> & instances){
    ifstream file;
    string line;
    int blank;

    file.open(file_name, ios_base::in);

    while(getline(file, line)){
        instances.push_back(line);
    }

    file.close();
}

void load_pdbs(abstraction_t** abst, state_map_t** pdb_maps, string name, int pdb_number){
    
    ifstream file;
    string pdb_filename, abst_filename, temp;

    for (int i =0; i !=  pdb_number; i++){

        temp.assign(name);
        temp.append("_");
        temp.append(to_string(i));

        pdb_filename.assign(temp);
        abst_filename.assign(temp);

        pdb_filename.append(".pdb");
        abst_filename.append(".abst");

        abst[i] = read_abstraction_from_file(abst_filename.c_str());

        FILE *pdb_file = fopen(pdb_filename.c_str(), "r");
        pdb_maps[i] = read_state_map(pdb_file);
        fclose(pdb_file);


    }  
}