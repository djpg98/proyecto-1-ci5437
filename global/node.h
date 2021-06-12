
class Node {
    public:
        state_t* state;    // Estado del nodo
        Node* parent;      // Nodo padre del nodo
        int rule_id;       // Accion que generó el estado del nodo
        unsigned g;        // Costo camino parcial

        /* Constructor */
        Node(state_t* state, Node* parent=NULL, int rule_id=-1, unsigned g=0) {
            this->state = state;
            this->parent = parent;
            this->rule_id = rule_id;
            this->g = g;
        }

        /* Crea un nuevo nodo a partir de aplicar la acción en el nodo actual */
        Node* make_node(state_t* state, int rule_id) {
            return new Node(state, this, rule_id, get_fwd_rule_cost(rule_id) + this->g);
        }
};