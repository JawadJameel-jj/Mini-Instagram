#include "Stack_Queue.h"
                                                                        //Stack
// Constructor
Stack::Stack() : top(nullptr), size(0) {}

// Destructor
Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

// Push operation
void Stack::push(string value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = top;
    top = newNode;
    size++;
}

// Pop operation
void Stack::pop() {
    if (isEmpty()) {
        cout << "Stack Underflow! Cannot pop from an empty stack.\n";
        return;
    }
    Node* temp = top;
    top = top->next;
    delete temp;
    size--;
}

// Peek operation
string Stack::peek() const {
    if (isEmpty()) {
        cout << "Stack is empty! No top element.\n";
        return " ";
    }
    return top->data;
}

// Check if the stack is empty
bool Stack::isEmpty() const {
    return top == nullptr;
}

// Get the size of the stack
int Stack::getSize() const {
    return size;
}

// Display the stack elements
void Stack::display( Stack &obj) const {
    if (obj.isEmpty()) {
        cout << "Stack is empty.\n";
        return;
    }
    Node* current = obj.top;
    cout << "Stack elements (top to bottom): ";
    while (current != nullptr)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void Stack::display() const {
    if (isEmpty()) {
        cout << "Stack is empty.\n";
        return;
    }
    Node* current = top;
    cout << "Stack elements (top to bottom): ";
    while (current != nullptr)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}



                                                                       //Queue





Queue::Queue() : front(nullptr), rear(nullptr), size(0) {}

Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

// Enqueue operation: Add an element to the rear
void Queue::enqueue(string value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;

    if (isEmpty()) {
        front = rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}

void Queue::dequeue() {
    if (isEmpty()) {
        cout << "Queue Underflow! Cannot dequeue from an empty queue.\n";
        return;
    }

    Node* temp = front;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
    size--;
}

// Dequeue a specific node
void Queue::dequeueSpecific(string value) {
    if (isEmpty()) {
        cout << "Queue is empty! Cannot remove specific element.\n";
        return;
    }

    Node* current = front;
    Node* prev = nullptr;

    // Traverse to find the node with the specified value
    while (current != nullptr && current->data != value) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Element " << value << " not found in the queue.\n";
        return;
    }

    // If the node to be removed is the front
    if (current == front) {
        front = front->next;
        if (front == nullptr) { // If the queue becomes empty
            rear = nullptr;
        }
    }
    else if (current == rear) { // If the node to be removed is the rear
        rear = prev;
        rear->next = nullptr;
    }
    else { // If the node is in the middle
        prev->next = current->next;
    }

    delete current;
    size--;

    cout << "Element " << value << " removed from the queue.\n";
}


string Queue::getFront() const {
    if (isEmpty()) {
        cout << "Queue is empty! No front element.\n";
        return " "; 
    }
    return front->data;
}

// Check if the queue is empty
bool Queue::isEmpty() const {
    return front == nullptr;
}

// Get the size of the queue
int Queue::getSize() const {
    return size;
}

// Display all elements in the queue
void Queue::display() const {
    if (isEmpty()) {
        cout << "Queue is empty.\n";
        return;
    }

    Node* current = front;
    cout << "Queue elements (front to rear): ";
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

