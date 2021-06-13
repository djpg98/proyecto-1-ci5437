#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>

using namespace std;

void reconstruct_solution(string state_description, string newline, vector<int> path);
void get_problem_instace(string file_name, string & instance);
void load_pdbs(abstraction_t ** abst, state_map_t ** pdb, string name, int pdb_number);
