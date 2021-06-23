
#include <vector>

using namespace std;

struct stateinfo {
    short int pos[16];
    short int blank;
};

class Node {
    public:
        state_t* state;    // Estado del nodo
        Node* parent;      // Nodo padre del nodo
        int rule_id;       // Accion que generó el estado del nodo
        unsigned g;        // Costo camino parcial
        int h;
        stateinfo* aux;     // Posición de las fichas

        /* Constructor */
        Node(state_t* state, Node* parent=NULL, int rule_id=-1, unsigned g=0, int h=0, stateinfo * aux =NULL) {
            this->state = state;
            this->parent = parent;
            this->rule_id = rule_id;
            this->g = g;
            this->h = h;
            this->aux = aux;
        }

        /* Crea un nuevo nodo a partir de aplicar la acción en el nodo actual */
        Node* make_node(state_t* state, int rule_id, int h, stateinfo * aux =NULL) {
            return new Node(state, this, rule_id, get_fwd_rule_cost(rule_id) + this->g, h, aux);
        }

        void extract_path(vector<int> &path) {
            Node* node = this;
            while (node != NULL && node->parent != NULL ) {
                path.insert(path.begin(), node->rule_id);
                node = node->parent;
            }
        }
};