#include "Tree_Graph.h"
#include "Stack_Queue.h"
#include "Main.h"

void mainMenu(Insta& g, string& loggedInUser);
void signUp(Insta& g, string& loggedInUser);
void login(Insta& g, string& loggedInUser);
void loggedInMenu(Insta& g, string& loggedInUser);

int main() {
    cout << "Welcome to Mini Instagram!\n";

    Insta g; // Instance of the Insta class to manage users
    string loggedInUser; // Keeps track of the currently logged-in user

    mainMenu(g, loggedInUser);

    system("pause");
    return 0;
}

// Main menu function
void mainMenu(Insta& g, string& loggedInUser) {
    int choice;

    while (true) {
        cout << "\n1. Sign Up\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            signUp(g, loggedInUser);
            if (!loggedInUser.empty()) {
                loggedInMenu(g, loggedInUser);
            }
            break;
        case 2:
            login(g, loggedInUser);
            if (!loggedInUser.empty()) {
                loggedInMenu(g, loggedInUser);
            }
            break;
        case 3:
            cout << "Exiting....\n";
            return; // Exit the program
        default:
            cout << "Invalid Choice! Please enter a valid option.\n";
        }
    }
}

// Sign-up function
void signUp(Insta& g, string& loggedInUser) {
    string username, password, city, address, security;

    // Username validation
    while (true) {
        cout << "Enter Username: ";
        cin >> username;
        if (g.findVertex(username)) { // Checks if username already exists
            cout << "Username '" << username << "' already exists! Please try a different username.\n";
        }
        else {
            break; // Valid username
        }
    }

    // Password validation
    while (true) {
        cout << "Enter Password: ";
        cin >> password;

        if (password.length() < 6) {
            cout << "Password should be at least 6 characters long. Please try again.\n";
        }
        else if (g.DigitsInPass(password)) { // Checks for at least one digit
            cout << "Password should contain at least 1 digit to make it strong. Please try again.\n";
        }
        else {
            break; // Valid password
        }
    }

    // City input
    cout << "Enter City: ";
    cin >> city;
    cout << "Enter address: ";
    cin >> address;
    cout << "Enter your Fathers name for security question: ";
    cin >> security;
    // Call the signup function from Graph
    g.signup(username, password, city, address, security);
    cout << "Sign Up Successful! Welcome, " << username << "!\n";

    // Automatically log in after signup
    loggedInUser = username;
}

// Login function
void login(Insta& g, string& loggedInUser) {
    string username, password;

    cout << "Enter Username: ";
    cin >> username;

    if (g.isUserExist(username)) { // Checks if the username exists in the graph
        cout << "1. Login with password\n";
        cout << "2. Reset password\n";
        int option;
        cin >> option;

        if (option == 1) { // Login option
            bool validPassword = false;
            while (!validPassword) {
                cout << "Enter Password: ";
                cin >> password;

                if (g.isUserLoggedIn(username, password)) { // Verifies password for the username
                    validPassword = true;
                    loggedInUser = username; // Log in successful
                    cout << "Login Successful! Welcome back, " << username << "!\n";
                }
                else {
                    cout << "Incorrect Password! Try Again.\n";
                }
            }
        }
        else if (option == 2) { // Reset password option
            cout << "Enter your Father name : ";
            string a;
            cin >> a;

            if (g.resetPassword(username, a)) {
                cout << "Password reset successful. You can now log in with your new password.\n";
            }
        }
        else {
            cout << "Invalid option!\n";
        }
    }
    else {
        cout << "No Account with this Username! Please Sign Up first.\n";
    }
}

// Logged-in menu function
void loggedInMenu(Insta& g, string& loggedInUser) {
    int userChoice;

    while (!loggedInUser.empty()) { // Menu loop
        cout << "\nWelcome, " << loggedInUser << "!\n";
        cout << "3. Logout\n";
        cout << "4. Follow Requests\n";
        cout << "5. Cancel/Accept Requests\n";
        cout << "6. Posts\n";
        cout << "7. Notifications\n";
        cout << "8. Messages\n";
        cout << "9. Search User\n";
        cout << "10. Follower List\n";
        cout << "11. News Feed\n";
        cout << "Enter your choice: ";
        cin >> userChoice;

        switch (userChoice) {
        case 3: // Logout
            cout << "Logged out successfully!\n";
            loggedInUser.clear(); // Clear logged-in user
            return; // Exit to main menu
        case 4: { // Send follow requests
            string toUser;
            cout << "Enter the username you want to send a follow request to: ";
            cin >> toUser;
            g.sendFriendRequest(loggedInUser, toUser); // Assuming this function exists in Graph
            break;
        }
        case 5: { // Cancel/Accept Requests
            cout << "Manage your follow requests:\n";
            cout << "Pending Friend Requests:\n";
            g.displayPendingRequests(loggedInUser); // Display pending requests
            if (g.hasPendingRequests(loggedInUser)) { // Assuming this function exists in Graph
                cout << "Do you want to bulk approve all follow requests? (y/n): ";
                char bulkChoice;
                cin >> bulkChoice;

                if (bulkChoice == 'y' || bulkChoice == 'Y') {
                    g.bulkApproveFollowRequests(loggedInUser); // Function assumed to exist
                    cout << "All follow requests approved.\n";
                }
                else {
                    while (true) {
                        // Display pending requests
                        cout << "Pending Friend Requests:\n";
                        g.displayPendingRequests(loggedInUser); // Display pending requests

                        int choice;
                        cout << "\nOptions:\n";
                        cout << "1. Accept Request\n";
                        cout << "2. Reject Request\n";
                        cout << "3. Back to Menu\n";
                        cout << "Enter your choice: ";
                        cin >> choice;

                        if (choice == 1) {
                            // Accept a request
                            string requestFrom;
                            cout << "Enter the username of the request to accept: ";
                            cin >> requestFrom;
                            if (g.acceptFriendRequest(loggedInUser, requestFrom)) {
                                cout << "You are now friends with " << requestFrom << "!\n";
                            }
                            else {
                                cout << "Invalid username or no such request found.\n";
                            }
                        }
                        else if (choice == 2) {
                            // Reject a request
                            string requestFrom;
                            cout << "Enter the username of the request to reject: ";
                            cin >> requestFrom;
                            if (g.rejectFriendRequest(loggedInUser, requestFrom)) {
                                cout << "You have rejected the friend request from " << requestFrom << ".\n";
                            }
                            else {
                                cout << "Invalid username or no such request found.\n";
                            }
                        }
                        else if (choice == 3) {
                            // Go back to the previous menu
                            break;
                        }
                        else {
                            cout << "Invalid choice. Please try again.\n";
                        }
                    }
                }
            }
            else {
                cout << "You have no pending friend requests.\n";
            }
            break;
        }
        case 6: { // Posts
            string message;
            cin.ignore(); // Clear the input buffer
            cout << "Enter your post content: ";
            getline(cin, message);
            g.postMessage(loggedInUser, message); // Assuming this function exists in Graph
            break;
        }
        case 7: // Notifications
            cout << "Your notifications:\n";
            g.viewNotifications(loggedInUser); // Assuming this function exists in Graph
            break;
        case 8: { // Messages
            string recipient, content;
            cout << "Enter the recipient's username: ";
            cin >> recipient;
            cin.ignore();
            cout << "Enter your message: ";
            getline(cin, content);
            cout << "Message sent to " << recipient << ": " << content << endl;
            g.sendMessage(loggedInUser, recipient, content); // Function assumed to exist
            break;
        }
        case 9: { // Search User
            string searchUsername;
            cout << "Enter the username to search: ";
            cin >> searchUsername;

            if (g.searchUserInBST(searchUsername)) { // Assuming this function exists in Graph
                cout << "User '" << searchUsername << "' found!\n";
            }
            else {
                cout << "User '" << searchUsername << "' not found.\n";
            }
            break;
        }
        case 10: // Follower List
            cout << "Your followers:\n";
            g.getFollowersList(loggedInUser); // Function assumed to exist
            break;
        case 11: { // News Feed
            cout << "Your news feed:\n";
            g.displayNews(); // Assuming this function exists in Graph
            break;
        }
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}


