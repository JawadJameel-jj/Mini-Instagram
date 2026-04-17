# 📸 Mini Instagram (C++ Console Application)

A simplified **Instagram-like social media application** built in **C++**, demonstrating core **data structures** like **Graphs, Trees, Stacks, and Queues**.

---

## 🚀 Features

### 👤 User Management

* Sign Up with validation
* Login with password authentication
* Password reset using security question
* Logout functionality

### 🤝 Social Features

* Send follow requests
* Accept / Reject follow requests
* Bulk approve requests
* View followers list

### 📝 Content System

* Create posts
* View news feed
* Notifications system

### 💬 Messaging

* Send messages to other users

### 🔍 Search

* Search users using **Binary Search Tree (BST)**

---

## 🧠 Data Structures Used

This project demonstrates practical usage of:

* **Graph** → User connections (followers/following)
* **Binary Search Tree (BST)** → User search
* **Stack & Queue** → Notifications, requests, messaging

---

## 🗂️ Project Structure

```
├── Main.cpp              # Entry point (menus & interaction)
├── Tree_Graph.h         # Graph + BST implementation
├── Stack_Queue.h        # Stack and Queue structures
├── Main.h               # Supporting declarations
```

---

## 🧭 Program Flow

1. Application starts with:

   ```
   Welcome to Mini Instagram!
   ```

2. Main Menu:

   * Sign Up
   * Login
   * Exit

3. After login:

   * Follow system
   * Posts
   * Messages
   * Notifications
   * Search users
   * News feed

---

## 🔐 Validation Rules

* Username must be **unique**
* Password must:

  * Be at least **6 characters long**
  * Contain **at least one digit**

---

## ⚙️ How to Run

### 🖥️ Requirements

* C++ Compiler (e.g., g++, MSVC)

### ▶️ Compile & Run

```bash
g++ Main.cpp -o mini_instagram
./mini_instagram
```

*(Make sure all header files are in the same directory)*

---

## 📌 Key Functions

| Function         | Description                |
| ---------------- | -------------------------- |
| `mainMenu()`     | Handles startup menu       |
| `signUp()`       | Registers a new user       |
| `login()`        | Authenticates user         |
| `loggedInMenu()` | Main user interaction menu |

---

## 🎯 Learning Objectives

* Implement real-world systems using **DSA concepts**
* Practice **Graph-based relationships**
* Use **BST for efficient searching**
* Manage workflows using **Stacks & Queues**

---

## ⚠️ Limitations

* Console-based UI (no GUI)
* No persistent storage (data resets on restart)
* Basic security (no encryption)

---

## 🔮 Future Improvements

* Add file/database storage
* GUI version (Qt / Web)
* Image/media support
* Like & comment system
* Profile customization

---

## 👨‍💻 Author

Developed as a **Data Structures project** to simulate a social media platform.

---
