#pragma once
#include<iostream>
#include<string>
using namespace std;

struct Node {
    string data;
    Node* next;
};

                                                                // Stack class declaration
class Stack {
private:
    Node* top;
    int size;

public:

    Stack();

    ~Stack();

    void push(string value);
    void pop();
    string peek() const;       // View the top element
    bool isEmpty() const;
    int getSize() const;
    void display() const;   // Display all stack elements
    void display(Stack& obj) const;
};



                                                                // Queue class declaration
class Queue {
private:
    Node* front;
    Node* rear;
    int size;

public:
    // Constructor
    Queue();

    // Destructor
    ~Queue();

    // Queue operations (ADTs)
    void enqueue(string value);
    void dequeue();
    void dequeueSpecific(string value); // Remove a specific node
    string getFront() const;      // View the front element
    bool isEmpty() const;      
    int getSize() const;       // Get the number of elements in the queue
    void display() const;      // Display all elements in the queue
};
