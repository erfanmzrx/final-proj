#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class Task {
private:
    string name;
    bool isStarred;
    time_t alertTime;
    string description;
    bool isCompleted;
    string assignedUser;
public:
    Task(const string& taskName) : name(taskName), isStarred(false), isCompleted(false) {}


    friend ostream& operator<<(ostream& os, const Task& task);
};

class TaskNode {
public:
    Task data;
    TaskNode* next;
    TaskNode(const Task& task) : data(task), next(nullptr) {}
};

class TaskList {
private:
    string name;
    string color;
    TaskNode* head;
public:
    TaskList(const string& listName, const string& listColor)
        : name(listName), color(listColor), head(nullptr) {}

    void addTask(const Task& task) {
        TaskNode* newNode = new TaskNode(task);
        if (!head) {
            head = newNode;
        } else {
            TaskNode* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    friend TaskList& operator>>(const Task& task, TaskList& list) {
        list.addTask(task);
        return list;
    }

};

class User {
private:
    string username;
    string password;
    vector<TaskList> lists;
public:
    User(const string& name, const string& pass) : username(name), password(pass) {}

    void addList(const TaskList& list) {
        lists.push_back(list);
    }

};

class TodoApp {
private:
    vector<User> users;
public:
    void registerUser(const string& username, const string& password) {
        users.emplace_back(username, password);
    }

};


ostream& operator<<(ostream& os, const Task& task) {
    os << "Task: " << task.name;
    if (task.isStarred) os << " (Starred)";
    if (task.isCompleted) os << " (Completed)";
    return os;
}

int main() {
    TodoApp app;


    app.registerUser("user1", "password1");

    TaskList myList("Personal", "Blue");
    Task task1("Buy groceries");
    Task task2("Call mom");

    task1 >> myList;
    task2 >> myList;


    return 0;
}
