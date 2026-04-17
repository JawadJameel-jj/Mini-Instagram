#pragma once
#include "Stack_Queue.h"

// Node structure for the BST
struct Node_tree {
    string data;
    Node_tree* left;
    Node_tree* right;

    Node_tree(const string& value) : data(value), left(nullptr), right(nullptr) {}
};

// BST class declaration
class BST {
private:
    Node_tree* root;

    Node_tree* insert(Node_tree* node, const string& value);  // Insert helper
    Node_tree* search(Node_tree* node, const string& value);  // Search helper
    Node_tree* remove(Node_tree* node, const string& value);  // Delete helper
    Node_tree* findMin(Node_tree* node);// Find the minimum value in a subtree
    void inorderTraversal(Node_tree* node);   // Inorder traversal helper

public:

    BST();

    ~BST();

    // Public BST operations
    void insert(const string& value); // Insert 
    bool search(const string& value); // Search
    void remove(const string& value); // Remove
    void inorder();// Perform inorder traversal
};



                                                                        // Graph



struct Stacks {
    string nameOfFriend;                        //name of friend
    Stack messagesToFriend, friendsPosts;       // stacks for there conversation and memes
    Stacks* next;
    Stacks() {
        nameOfFriend = " ";
        next=nullptr;
    }
};

struct User {
    string Name, Password, City, Address, Security;
    Stack UsersPosts, Followers, Following;
    Stacks* header;                             // linked list for friends conversation
    Queue FriendRequests, Notifications;
    void input(string name, string password, string city, string address, string security) {
        Name = name;
        Password = password;
        City = city;
        Address = address;
        Security = security;
    }
};



class Graph {
public:
    struct Edge {
        string data;            //name of user
        string relation;
        string status;          // active, block
        Edge* next;
    };

    struct Vertex {
        User obj;
        string color; // For BFS traversal (white, gray, black)
        Edge* adj;
        Vertex* next;
    };

    struct VQNode {
        Vertex* data;
        VQNode* next;
        VQNode();
    };

    class vertexQueue {
        VQNode* front;
        VQNode* back;

    public:
        vertexQueue();
        bool VIsEmpty();
        void Venqueue(Vertex* v);
        Vertex* Vdequeue();
    };

    Graph();
    ~Graph();

    bool DigitsInPass(string p);
    void addVertex(string name, string password, string city, string address, string ecurity);
    void addEdge(string fromName, string toName, string relation, string status);
    Vertex* findVertex(string name);
    void displayGraph();
    bool bfs(string targetName);
    bool passwordChecker(string name, string pass);
    void displayVertex(string name);

private:
    Vertex* head;
};