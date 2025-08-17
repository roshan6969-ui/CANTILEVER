#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio> // for remove(), rename()

using namespace std;

// Global variables
bool isLoggedIn = false;
string currentUser;

// Function Declarations
void registerUser();
bool loginUser(string username, string password);
void login();
void logout();
void createPost(string username);
void viewPosts(string username);
void viewTimeline(string username);
void likePost(string username, string postContent);
void viewLikes(string username);
void commentOnPost(string username, string postContent);
void viewComments(string username);
void followUser(string currentUser, string followUser);
void unfollowUser(string currentUser, string unfollowUser);
void viewFollowers(string currentUser);
void editProfile(string username);
void deletePost(string username, string postContent);

// Function Definitions

void registerUser() {
    string username, password, email;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter password: ";
    cin >> password;

    ofstream userFile(username + "_profile.txt");
    userFile << "Username: " << username << endl;
    userFile << "Email: " << email << endl;
    userFile << "Password: " << password << endl;
    userFile.close();

    cout << "Registration successful!" << endl;
}

bool loginUser(string username, string password) {
    ifstream userFile(username + "_profile.txt");
    string fileUsername, fileEmail, filePassword;

    if (userFile.is_open()) {
        getline(userFile, fileUsername);
        getline(userFile, fileEmail);
        getline(userFile, filePassword);
        userFile.close();

        fileUsername = fileUsername.substr(fileUsername.find(": ") + 2);
        filePassword = filePassword.substr(filePassword.find(": ") + 2);

        return (username == fileUsername && password == filePassword);
    }

    return false;
}

void login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (loginUser(username, password)) {
        isLoggedIn = true;
        currentUser = username;
        cout << "Login successful!" << endl;
    } else {
        cout << "Invalid username or password." << endl;
    }
}

void logout() {
    isLoggedIn = false;
    currentUser = "";
    cout << "You have logged out." << endl;
}

void createPost(string username) {
    string post;
    cout << "Enter your post: ";
    cin.ignore();
    getline(cin, post);

    ofstream postFile(username + "_posts.txt", ios::app);
    postFile << "Post: " << post << endl;
    postFile.close();

    cout << "Post created successfully!" << endl;
}

void viewPosts(string username) {
    ifstream postFile(username + "_posts.txt");
    string line;

    cout << "Posts by " << username << ":\n";
    while (getline(postFile, line)) {
        cout << line << endl;
    }

    postFile.close();
}

void viewTimeline(string currentUser) {
    ifstream followFile(currentUser + "_following.txt");
    string followedUser;

    while (getline(followFile, followedUser)) {
        cout << "Posts from " << followedUser << ":\n";
        viewPosts(followedUser);
        cout << "---------------------\n";
    }

    followFile.close();
}

void likePost(string username, string postContent) {
    ofstream likeFile(username + "_likes.txt", ios::app);
    likeFile << "Liked post: " << postContent << endl;
    likeFile.close();

    cout << "You liked the post!" << endl;
}

void viewLikes(string username) {
    ifstream likeFile(username + "_likes.txt");
    string line;

    cout << "Your liked posts: \n";
    while (getline(likeFile, line)) {
        cout << line << endl;
    }

    likeFile.close();
}

void commentOnPost(string username, string postContent) {
    string comment;
    cout << "Enter your comment: ";
    cin.ignore();
    getline(cin, comment);

    ofstream commentFile(username + "_comments.txt", ios::app);
    commentFile << "Post: " << postContent << "\nComment by " << username << ": " << comment << endl;
    commentFile.close();

    cout << "Your comment has been posted!" << endl;
}

void viewComments(string username) {
    ifstream commentFile(username + "_comments.txt");
    string line;

    cout << "Your comments: \n";
    while (getline(commentFile, line)) {
        cout << line << endl;
    }

    commentFile.close();
}

void followUser(string currentUser, string followUsername) {
    ofstream followFile(currentUser + "_following.txt", ios::app);
    followFile << followUsername << endl;
    followFile.close();

    cout << "You are now following " << followUsername << "!" << endl;
}

void unfollowUser(string currentUser, string unfollowUsername) {
    ifstream followFile(currentUser + "_following.txt");
    ofstream tempFile("temp.txt");
    string line;

    while (getline(followFile, line)) {
        if (line != unfollowUsername) {
            tempFile << line << endl;
        }
    }

    followFile.close();
    tempFile.close();

    remove((currentUser + "_following.txt").c_str());
    rename("temp.txt", (currentUser + "_following.txt").c_str());

    cout << "You have unfollowed " << unfollowUsername << "." << endl;
}

void viewFollowers(string currentUser) {
    // Simple reverse check - inefficient for large systems
    cout << "Feature not implemented: Requires scanning all users for followers." << endl;
}

void editProfile(string username) {
    string newEmail, newPassword;
    cout << "Enter new email: ";
    cin >> newEmail;
    cout << "Enter new password: ";
    cin >> newPassword;

    ofstream userFile(username + "_profile.txt");
    userFile << "Username: " << username << endl;
    userFile << "Email: " << newEmail << endl;
    userFile << "Password: " << newPassword << endl;
    userFile.close();

    cout << "Profile updated successfully!" << endl;
}

void deletePost(string username, string postContent) {
    ifstream postFile(username + "_posts.txt");
    ofstream tempFile("temp.txt");
    string line;

    while (getline(postFile, line)) {
        if (line != "Post: " + postContent) {
            tempFile << line << endl;
        }
    }

    postFile.close();
    tempFile.close();

    remove((username + "_posts.txt").c_str());
    rename("temp.txt", (username + "_posts.txt").c_str());

    cout << "Post deleted successfully!" << endl;
}

// Main Program
int main() {
    int choice;
    string postContent;

    cout << "Welcome to Simple Social!" << endl;

    while (true) {
        if (!isLoggedIn) {
            cout << "\n1. Login\n2. Register\nChoice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    login();
                    break;
                case 2:
                    registerUser();
                    break;
                default:
                    cout << "Invalid choice!" << endl;
            }
        } else {
            cout << "\n--- Menu ---\n";
            cout << "1. View Timeline\n2. Create Post\n3. View My Posts\n4. Edit Profile\n";
            cout << "5. Follow User\n6. Unfollow User\n7. View Followers\n";
            cout << "8. Like Post\n9. Comment on Post\n10. View Likes\n11. View Comments\n12. Logout\n";
            cout << "Choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    viewTimeline(currentUser);
                    break;
                case 2:
                    createPost(currentUser);
                    break;
                case 3:
                    viewPosts(currentUser);
                    break;
                case 4:
                    editProfile(currentUser);
                    break;
                case 5: {
                    string followUsername;
                    cout << "Enter username to follow: ";
                    cin >> followUsername;
                    followUser(currentUser, followUsername);
                    break;
                }
                case 6: {
                    string unfollowUsername;
                    cout << "Enter username to unfollow: ";
                    cin >> unfollowUsername;
                    unfollowUser(currentUser, unfollowUsername);
                    break;
                }
                case 7:
                    viewFollowers(currentUser);
                    break;
                case 8:
                    cout << "Enter post content to like: ";
                    cin.ignore();
                    getline(cin, postContent);
                    likePost(currentUser, postContent);
                    break;
                case 9:
                    cout << "Enter post content to comment on: ";
                    cin.ignore();
                    getline(cin, postContent);
                    commentOnPost(currentUser, postContent);
                    break;
                case 10:
                    viewLikes(currentUser);
                    break;
                case 11:
                    viewComments(currentUser);
                    break;
                case 12:
                    logout();
                    break;
                default:
                    cout << "Invalid choice!" << endl;
            }
        }
    }

    return 0;
}
``
