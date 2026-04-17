#include "Tree_Graph.h"
                                                                        //BST


// Constructor
BST::BST() : root(nullptr) {}

// Destructor
BST::~BST() {
    // Use an in-place stack-based traversal to delete all nodes
    while (root != nullptr)
    {
        remove(root->data);
    }
}


// Find the minimum value in a subtree (private)
Node_tree* BST::findMin(Node_tree* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Insert helper (private)
Node_tree* BST::insert(Node_tree* node, const string& value) {
    if (node == nullptr) {
        return new Node_tree(value);
    }

    if (value < node->data) {
        node->left = insert(node->left, value);
    }
    else if (value > node->data) {
        node->right = insert(node->right, value);
    }

    return node;
}

// Insert a value into the BST (public)
void BST::insert(const string& value) {
    root = insert(root, value);
}


// Search for a value in the BST (public)
bool BST::search(const string& value) {
    return search(root, value) != nullptr;
}

// Search helper (private)
Node_tree* BST::search(Node_tree* node, const string& value) {
    if (node == nullptr || node->data == value) {
        return node;
    }

    if (value < node->data) {
        return search(node->left, value);
    }
    else {
        return search(node->right, value);
    }
}

// Remove a value from the BST (public)
void BST::remove(const string& value) {
    root = remove(root, value);
}

// Remove helper (private)
Node_tree* BST::remove(Node_tree* node, const string& value) {
    if (node == nullptr) {
        return nullptr;
    }

    if (value < node->data) {
        node->left = remove(node->left, value);
    }
    else if (value > node->data) {
        node->right = remove(node->right, value);
    }
    else {
        // Node to be deleted found
        if (node->left == nullptr) {
            Node_tree* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            Node_tree* temp = node->left;
            delete node;
            return temp;
        }

        // Node with two children: Get the inorder successor
        Node_tree* temp = findMin(node->right);
        node->data = temp->data;
        node->right = remove(node->right, temp->data);
    }

    return node;
}

// Inorder traversal helper (private)
void BST::inorderTraversal(Node_tree* node) {
    if (node == nullptr) {
        return;
    }

    inorderTraversal(node->left);
    cout << node->data << " ";
    inorderTraversal(node->right);
}

// Perform inorder traversal (public)
void BST::inorder() {
    inorderTraversal(root);
    cout << endl;
}









                                                                        // Graph
// VQNode constructor
Graph::VQNode::VQNode() {
    data = nullptr;
    next = nullptr;
}

// vertexQueue constructor
Graph::vertexQueue::vertexQueue() {
    front = nullptr;
    back = nullptr;
}

// vertexQueue
bool Graph::vertexQueue::VIsEmpty() {
    return (front == nullptr);
}

// vertexQueue
void Graph::vertexQueue::Venqueue(Vertex* v) {
    VQNode* nd = new VQNode;
    nd->data = v;
    nd->next = nullptr;

    if (VIsEmpty()) {
        front = back = nd;
    }
    else {
        back->next = nd;
        back = nd;
    }
}

// vertexQueue
Graph::Vertex* Graph::vertexQueue::Vdequeue() {
    if (VIsEmpty()) {
        return nullptr;
    }
    VQNode* temp = front;
    Vertex* v = front->data;
    front = front->next;
    delete temp;
    if (!front) {
        back = nullptr;
    }
    return v;
}

// Graph constructor
Graph::Graph() {
    head = nullptr;
}

// Graph destructor
Graph::~Graph() {
    while (head) {
        Vertex* toDelete = head;
        head = head->next;

        Edge* temp = toDelete->adj;
        while (temp) {
            Edge* toDeleteEdge = temp;
            temp = temp->next;
            delete toDeleteEdge;
        }

        delete toDelete;
    }
}

bool Graph::DigitsInPass(string p) {
    for (char c : p) {
        if (isdigit(c)) {
            return true;
        }
    }
    return false;
}

void Graph::addVertex(string name, string password, string city, string address, string security) {
    Vertex* newVertex = new Vertex();
    newVertex->obj.input(name, password, city, address, security);
    newVertex->color = "white";
    newVertex->adj = nullptr;
    newVertex->next = nullptr;

    if (!head) {
        head = newVertex;
        return;
    }

    Vertex* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newVertex;
}

void Graph::addEdge(string fromName, string toName, string relation, string status) {
    Vertex* fromVertex = findVertex(fromName);
    Vertex* toVertex = findVertex(toName);

    if (fromVertex && toVertex) {
        Edge* newNode = new Edge;
        newNode->data = toName;
        newNode->relation = relation;
        newNode->status = status;
        newNode->next = fromVertex->adj;
        fromVertex->adj = newNode;
    }
    else {
        cout << "Cannot add the relation from " << fromName << " to " << toName << endl;
    }
}

Graph::Vertex* Graph::findVertex(string name) {
    Vertex* current = head;
    while (current) {
        if (current->obj.Name == name) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void Graph::displayGraph() {
    Vertex* current = head;

    cout << "Following are all the Accounts:\n";
    while (current) {
        cout << "Account Name: " << current->obj.Name << " (" << current->obj.City << " ) -> ";
        Edge* temp = current->adj;
        while (temp) {
            cout << temp->data << " [Relation: " << temp->relation << " | Status: " << temp->status << "] ";
            temp = temp->next;
        }
        cout << endl;
        current = current->next;
    }
}

bool Graph::bfs(string targetName) {
    if (!head) {
        cout << "No Accounts Made Till Now.\n";
        return false;
    }

    // Reset all vertices to "white"
    Vertex* temp = head;
    while (temp) {
        temp->color = "white";
        temp = temp->next;
    }

    vertexQueue q;

    // Start BFS for all components
    temp = head;
    while (temp) {
        if (temp->color == "white") {
            q.Venqueue(temp);
            temp->color = "gray";

            while (!q.VIsEmpty()) {
                Vertex* u = q.Vdequeue();
                if (u->obj.Name == targetName) {
                    return true;
                }

                Edge* edge = u->adj;
                while (edge) {
                    Vertex* adjVertex = findVertex(edge->data);
                    if (adjVertex && adjVertex->color == "white") {
                        adjVertex->color = "gray";
                        q.Venqueue(adjVertex);
                    }
                    edge = edge->next;
                }

                u->color = "black";
            }
        }
        temp = temp->next;
    }
    return false;
}

bool Graph::passwordChecker(string name, string pass) {
    Vertex* vertex = findVertex(name);
    if (!vertex || vertex->obj.Password != pass) 
    {
        return false;
    }
    return true;
}

void Graph::displayVertex(string name) {
    Vertex* vertex = findVertex(name);
    if (vertex) {
        cout << "Name: " << vertex->obj.Name << "\n";
        cout << "Password: " << vertex->obj.Password << "\n";
        cout << "City: " << vertex->obj.City << "\n";
        cout << "Address: " << vertex->obj.Address << endl;
        cout << "Followers:\n";

        Edge* edge = vertex->adj;
        while (edge) {
            cout << "  - " << edge->data << " [Relation: " << edge->relation << " | Status: " << edge->status << "]\n";
            edge = edge->next;
        }
    }
}