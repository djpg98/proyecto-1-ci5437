/*
This program computes the distance to goal (i.e. the cost of the least-cost path to the goal)
of every state from which the goal can be reached.
It does this by executing Dijkstra's algorithm backwards from the goal.
It prints on stdout the number of states at each distance from goal and, if a filename is
provided as a command line argument, it prints the state_map it builds to that file.

Copyright (C) 2013 by the PSVN Research Group, University of Alberta
*/

#include <vector>
#include "priority_queue.hpp"

int main(int argc, char **argv) {
    int64_t totalNodes, numAtD;  // counters
    state_t state, child;   // NOTE: "child" will be a predecessor of state, not a successor
    int d, ruleid;
    ruleid_iterator_t iter;

    PriorityQueue<state_t> open; // used for the states we have generated but not yet expanded (the OPEN list)
    state_map_t *map = new_state_map(); // contains the cost-to-goal for all states that have been generated
    FILE *file; // the final state_map is written to this file if it is provided (command line argument)

    // add goal states
    first_goal_state(&state, &d);
    do {
        open.Add(0, 0, state);
    } while( next_goal_state(&state, &d) );

    d = 0;
    numAtD = 0;
    totalNodes = 0;
    while( !open.Empty() ) {
        // get current distance from goal; since operator costs are
        // non-negative this distance is monotonically increasing
        if( open.CurrentPriority() > d ) {
            printf("%"PRId64" states at distance %d\n", numAtD, d);
            d = open.CurrentPriority();
            numAtD = 0;
        }

        // remove top state from priority state
        state = open.Top();
        open.Pop();
        
        // check if we already expanded this state.
        // (entries on the open list are not deleted if a cheaper path to a state is found)
        /*const int *best_dist = state_map_get(map, &state);
        assert(best_dist != NULL);
        if( *best_dist < d ) continue;*/
        
        numAtD++;
        totalNodes++;

        // look at all predecessors of the state
        init_bwd_iter(&iter, &state);
        while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
            apply_bwd_rule(ruleid, &state, &child);
            const int child_d = d + get_bwd_rule_cost(ruleid);

            // check if either this child has not been seen yet or if
            // there is a new cheaper way to get to this child.
            const int *old_child_d = state_map_get(map, &child);
            // add to open with the new distance
            //state_map_add(map, &child, child_d);
            open.Add(child_d, child_d, child);
        }
    }
    
    // print last level and total states
    if( numAtD > 0 ) {
        printf("%"PRId64" states at distance %d\n", numAtD, d);
    }
    printf("%"PRIu64" states in total.\n", totalNodes);
    
    // write the state map to a file
    if( argc >= 2 ) {
        file = fopen(argv[1], "w");
        if( file == NULL ) {
            fprintf(stderr, "could not open %s for writing\n", argv[1]);
            exit(-1);
        }
        write_state_map(file, map);
        fclose(file);
    }
    
    return 0;
}

