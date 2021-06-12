#include "node.h"

Node::Node(state_t* state, Node* parent, int rule_id, unsigned g) {
    this->state = state;
    this->parent = parent;
    this->rule_id = rule_id;
    this->g = g;
}

Node* Node::make_node(state_t* state, int rule_id) {
    return new Node(state, this, rule_id, get_fwd_rule_cost(rule_id) + this->g);
}

void Node::extract_path(vector<int> &path) {
    Node* node = this;
    while (node != NULL && node->parent != NULL ) {
        path.insert(path.begin(), node->rule_id);
        node = node->parent;
    }
}