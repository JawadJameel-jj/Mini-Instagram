#include "Stack_Queue.h"
#include "Tree_Graph.h"
#include <iomanip>
#include <ctime>
#include <sstream>



class Insta {
    
    Stack News;
    BST users;
    Graph graph;

public:

    void signup(string username, string password, string city, string address, string security) {
        graph.addVertex(username, password, city, address, security);
        users.insert(username);
    }

    bool resetPassword(string username, string Fathername) {
        string password;
        Graph::Vertex* temp = graph.findVertex(username);
        if (Fathername==temp->obj.Security)
        {
            while (true) {
                cout << "Enter Password: ";
                cin >> password;

                if (password.length() < 6) {
                    cout << "Password should be at least 6 characters long. Please try again. " << endl;
                }
                else if (graph.DigitsInPass(password)) { // Checks for at least one digit
                    cout << "Password should contain at least 1 digit to make it strong. Please try again. " << endl;
                }
                else {
                    break; // Valid password
                }
            }
            temp->obj.Password = password;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool findVertex(string username) {
        if (graph.findVertex(username) != nullptr)
        {
            return true;
        }
        return false;
    }

    bool DigitsInPass(string password) {
        if (!graph.DigitsInPass(password))
        {
            return true;
        }
        return false;
    }

    bool isUserExist(string username) {
        if (graph.bfs(username))
        {
            return true;
        }
        return false;
    }

    bool isUserLoggedIn(string username, string password) {
        if (graph.passwordChecker(username, password))
        {
            return true;
        }
        return false;
    }

    void sendFriendRequest(string loggedInUser, string toUser) {
        if (this->isUserExist(toUser))
        {
            Graph::Vertex* temp = graph.findVertex(toUser);
            temp->obj.FriendRequests.enqueue(loggedInUser);
            cout << "Friend request send " << endl;
        }
        else
        {
            cout << "No user with that Id is present " << endl;
        }
    }

    void postMessage(string loggedInUser, string message) {
        News.push(message);
        Graph::Vertex* temp = graph.findVertex(loggedInUser);   // finding the node
        temp->obj.UsersPosts.push(message);                     // pushing the message
        Graph::Edge* temp1 = temp->adj;                         // giving address of edge friends
        while (temp1)
        {
            Graph::Vertex* temp2 = graph.findVertex(temp1->data); // finding vertex of every friend
            Stacks* tempobj = temp2->obj.header;                  // takind address of Stacks in friends 
            while (tempobj)                                       // untile that friend found
            {
                if (temp2->obj.header->nameOfFriend==tempobj->nameOfFriend)   // specific friend
                {
                    tempobj->friendsPosts.push(message);
                }
                tempobj = tempobj->next;
            }
            temp1 = temp1->next;
        }
    }

    void viewNotifications(string loggedInUser) {
        Graph::Vertex* temp = graph.findVertex(loggedInUser);
        temp->obj.Notifications.display();
    }

    bool hasPendingRequests(string loggedInUser) {
        Graph::Vertex* temp = graph.findVertex(loggedInUser);
        if (temp->obj.FriendRequests.isEmpty())
        {
            return false;
        }
        return true;
    }

    void displayPendingRequests(string loggedInUser) {
        Graph::Vertex* temp = graph.findVertex(loggedInUser);
        if (temp->obj.FriendRequests.isEmpty())
        {
            temp->obj.FriendRequests.display();
        }
        else
        {
            cout << "No friend request " << endl;
        }
    }

    void bulkApproveFollowRequests(string loggedInUser) {
        Graph::Vertex* temp = graph.findVertex(loggedInUser);
        string a = temp->obj.FriendRequests.getFront();
        while (acceptFriendRequest(loggedInUser,a))
        {
            a = temp->obj.FriendRequests.getFront();
        }
    }

    bool acceptFriendRequest(string loggedInUser, string requestFrom) {
        Graph::Vertex* temp = graph.findVertex(loggedInUser);
        Graph::Vertex* temp1 = graph.findVertex(requestFrom);
        if (temp&&temp1)
        {
            graph.addEdge(loggedInUser, requestFrom, "Friend", "active");
            temp->obj.FriendRequests.dequeueSpecific(requestFrom);
            Stacks* n = new Stacks();
            n->nameOfFriend = requestFrom;
            temp->obj.header->next = n;
            temp->obj.Followers.push(requestFrom);

            Stacks* a = new Stacks();
            a->nameOfFriend = requestFrom;
            temp1->obj.header->next = a;
            temp1->obj.Following.push(loggedInUser);
            return true;
        }        
        return false;
    }

    bool rejectFriendRequest(string loggedInUser, string requestFrom) {
        Graph::Vertex* temp = graph.findVertex(loggedInUser);
        if (!temp->obj.FriendRequests.isEmpty())
        {
            temp->obj.FriendRequests.dequeueSpecific(requestFrom);
            return true;
        }
        return false;
    }

    void sendMessage(string loggedInUser, string recipient, string content) {
        Graph::Vertex* temp = graph.findVertex(loggedInUser);
        Graph::Vertex* temp1 = graph.findVertex(recipient);

        Stacks* tempobj = temp1->obj.header;
        while (tempobj->nameOfFriend != recipient && tempobj != NULL)
        {
            tempobj = tempobj->next;
        }
        tempobj->messagesToFriend.push(content);

        tempobj = temp->obj.header;

        while (tempobj->nameOfFriend != loggedInUser && tempobj != NULL)
        {
            tempobj = tempobj->next;
        }
        tempobj->messagesToFriend.push(content);
    }

    bool searchUserInBST(string searchUsername) {
        if (users.search(searchUsername))
        {
            return true;
        }
        return false;
    }

    void getFollowersList(string loggedInUser) {
        Graph::Vertex* temp = graph.findVertex(loggedInUser);
        temp->obj.Followers.display();
    }

    void displayNews() {
        News.display();
    }

};

//int main() {
//    // Generate and display the timestamp
//    string timestamp = getTimestamp();
//    cout << "Current Timestamp: " << timestamp << endl;
//
//    return 0;
//}


    //// Function to format the current timestamp as a string
    //string getTimestamp() {
    //    // Get the current time
    //    time_t now = time(nullptr);
    //    tm* localTime = localtime(&now);

    //    // Manually format the timestamp
    //    char buffer[20];
    //    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);


    //    return string(buffer);
    //}