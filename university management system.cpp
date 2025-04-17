#include <iostream>
#include <string>
using namespace std;

//1. Student Records Management: Single Linked List

class Student { //for the SLL
public:
    int studentID;
    string studentName;
    string studentEmail;
    int studentPhone;
    string studentAddress;
    string studentPassword;

    Student() {
        cout << "Enter Student ID: ";
        cin >> studentID;
        cin.ignore();

        cout << "Enter Student Name: ";
        getline(cin, studentName);

        cout << "Enter Student Email: ";
        getline(cin, studentEmail);

        cout << "Enter Student Phone: ";
        cin >> studentPhone;
        cin.ignore();

        cout << "Enter Student Address: ";
        getline(cin, studentAddress);

        cout << "Enter Student Password: ";
        getline(cin, studentPassword);
    }
};

class SLLNode {
public:
    Student data;
    SLLNode* next; // Redefine next to avoid using dynamic_cast
    SLLNode(Student s) : data(s) { next = nullptr; }
};

//Store and manage student records in a Single Linked List.
class StudentSLL {
private:
    SLLNode* head;
    SLLNode* tail;

public:
    StudentSLL() { head = tail = nullptr; }

    SLLNode* getHead() { //used in binary search
        return head;
    }

    //add(): Add a new student with attributes such as ID, Name, Email, Phone, Address, and Password.
    void addStudent() {
        Student s;
        SLLNode* newNode = new SLLNode(s);

        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        cout << "Student added successfully!\n";
    }

    //delete(): Remove a student by their ID.
    void deleteStudent() {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }

        int id;
        cout << "Enter Student ID to delete: ";
        cin >> id;

        SLLNode* temp = head;
        SLLNode* prev = nullptr;

        if (head->data.studentID == id) {
            head = head->next;
            delete temp;
            cout << "Student deleted successfully.\n";
            return;
        }

        while (temp && temp->data.studentID != id) {
            prev = temp;
            temp = temp->next;
        }

        if (!temp) {
            cout << "Student with ID " << id << " not found.\n";
            return;
        }

        prev->next = temp->next;
        if (temp == tail) tail = prev;
        delete temp;
        cout << "Student deleted successfully.\n";
    }

    //display(): Print all student details.
    void displayStudents() {
        if (!head) {
            cout << "No students to display.\n";
            return;
        }

        SLLNode* temp = head;
        int count = 1;
        while (temp) {
            cout << "Student " << count;
            cout << "\nID: " << temp->data.studentID
                 << "\nName: " << temp->data.studentName
                 << "\nEmail: " << temp->data.studentEmail
                 << "\nPhone: " << temp->data.studentPhone
                 << "\nAddress: " << temp->data.studentAddress << "\n";
            cout << "-----------------\n";
            count++;
            temp = temp->next;
        }
    }

    void selectionSort() { //It was requered to implement a search and sort functionalities for Students by ID. so we used selection sort with O(n^2)
        //then we used a binary search function O(nlogn)

        if (!head || !head->next) return; //if head is not null or if the next is not null

        SLLNode* temp = head;
        while (temp) {
            SLLNode* minNode = temp;
            SLLNode* r = temp->next;

            while (r) {
                if (r->data.studentID < minNode->data.studentID) {
                    minNode = r;
                }
                r = r->next;
            }

            if (minNode != temp) {
                swap(temp->data, minNode->data);
            }
            temp = temp->next;
        }
    }

    void binarysearch(SLLNode* head, int studentID); //due to the use of scope resolution operator -used when a function is needed to be defined outside of the class scoop-
};


// 2. Course Records Management: Binary Search Tree (BST)

class Course { // used in BST and The hashmap
public:
    int CourseID;
    string CourseName;
    string CourseInstructor;
    int CourseCredits;

    // Constructor
    Course() {
        cout << "Enter Course ID: ";
        cin >> CourseID;
        cin.ignore();  // To clear the newline character

        cout << "Enter Course Name: ";
        getline(cin, CourseName);

        cout << "Enter Course Instructor: ";
        getline(cin, CourseInstructor);

        cout << "Enter Course Credits: ";
        cin >> CourseCredits;
        cin.ignore();
    }
};

// TreeNode class
class TreeNode{
public:
    Course data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Course c) : data(c), left(nullptr), right(nullptr) {}
};

// Store course information in a Binary Search Tree (BST).
// Functionalities to implement:
// Each node contains: CourseID, CourseName, CourseCredits, and CourseInstructor.
// The tree is structured so that for any node, all nodes in the left subtree have smaller IDs, and all nodes in the right subtree have larger IDs.

// Bonus Part:
// 7.
// Fast Access Using Hashing
// Enhance lookup efficiency with a Hash Table.


//this class is defined here because a hashmap object is created in the BST class. We did this becuse we wanted the Course to be added or deleted
//in both the BST and the hashmap at the same time in order for it to be fully functioning and avoiding edge cases. It could have been done with "forward declaration" but it caused
//an error so we chose this way


// HashNode
class HashNode {
public:
    int key;
    Course value;
    HashNode* next;

    HashNode(int k, Course v) : key(k), value(v), next(nullptr) {}
};

class HashMap {
private:
    int numOfElements, capacity;
    HashNode** arr;

    // Requirements:
    // Design a hashing function.

    int hashFunction(int key) {
        return key % capacity;
    }

public:
    // Constructor
    HashMap(int cap = 100) {
        capacity = cap;
        numOfElements = 0;
        arr = new HashNode*[capacity](); // Allocate array of pointers initialized to nullptr
    }

    // Insert Course
    // Implement collision handling (e.g., Chaining or Open Addressing). -chaining is implemented- Instead of storing the keys directly in the table, each position in the table contains a linked list
    //of keys.

    //called in BST
    void addcourse_to_hashmap(Course value) {
        int key = value.CourseID;  // Use CourseID as the key

        // Calculate the index using the hash function
        int positionIndex = hashFunction(key);

        // Create a new HashNode with the generated key and the passed Course value
        HashNode* newNode = new HashNode(key, value);

        // Insert the node in the appropriate position in the hash map
        if (!arr[positionIndex]) {
            arr[positionIndex] = newNode;  // No collision, place directly
        } else {
            newNode->next = arr[positionIndex];  // Collision, use chaining
            arr[positionIndex] = newNode;  // Place at the front of the list
        }
    }

//called in BST
    void deletecourse_from_hashmap(int courseID) {
        for (int i = 0; i < capacity; i++) {
            HashNode* prevNode = nullptr;
            HashNode* currNode = arr[i];

            // Traverse the linked list at the index
            while (currNode) {
                if (currNode->value.CourseID == courseID) {
                    if (!prevNode) {
                        arr[i] = currNode->next;  // Remove from the front
                    } else {
                        prevNode->next = currNode->next;  // Remove from the middle or end
                    }
                    delete currNode;  // Free the memory
                    return;
                }
                prevNode = currNode;
                currNode = currNode->next;
            }
        }
        cout << "No course found with ID " << courseID << endl;
    }


    // // searchWithHashing(): to improve course search efficiency.
    void searchWithHashing(int courseID) { //called within the searchCourse
        for (int i = 0; i < capacity; i++) {
            HashNode* positionHead = arr[i];
            while (positionHead) {
                if (positionHead->value.CourseID == courseID) {
                    cout << "Course with ID " << courseID << " is found using a Hash table." << endl;
                    cout << "Course Name: " << positionHead->value.CourseName << endl;
                    cout << "Course Instructor: " << positionHead->value.CourseInstructor << endl;
                    cout << "Course Credits: " << positionHead->value.CourseCredits << endl;
                    return;
                }
                positionHead = positionHead->next;
            }
        }
        cout << "No course found with ID " << courseID << endl;
    }
};

class CourseBST {
private:
    TreeNode* root;
    HashMap hashmap1;  // Declare hashmap as a member of CourseBST

public:
    CourseBST() : root(nullptr), hashmap1(100) {} //constructor

    TreeNode* getRoot() { //used in searchCourse()
        return root;
    }

    // Methods:
    // addCourse()
    void addCourse() {
        Course c; //when this instance is intialized it takes the input

        TreeNode* newNode = new TreeNode(c);

        if (!root) {
            root = newNode;
            cout<<"Course added successfully" <<endl;

        } else {
            TreeNode* current = root;
            TreeNode* parent = nullptr;

            while (current) { //simple search in order to avoide adding two courses with the same ID
                parent = current;
                if (c.CourseID < current->data.CourseID)
                    current = current->left;
                else if (c.CourseID > current->data.CourseID)
                    current = current->right;
                else {
                    // CourseID already exists (optional handling)
                    cout << "Course with this ID already exists." << endl;
                    delete newNode;
                    return;
                }
            }

            if (c.CourseID < parent->data.CourseID)
                parent->left = newNode;

            else
                parent->right = newNode;

            cout<<"Course added successfully" <<endl;
        }
        hashmap1.addcourse_to_hashmap(c); //used to add to hashmap in the same time
    }

    // dropCourse()
    void dropCourse() {
        int id;
        cout << "Enter Course ID to drop: ";
        cin >> id;

        TreeNode* current = root;
        TreeNode* parent = nullptr;

        // Find the node to delete
        while (current && current->data.CourseID != id) { //while current ensures it is not NULL
            parent = current;
            if (id < current->data.CourseID)
                current = current->left;
            else
                current = current->right;
        }

        if (!current) {
            cout << "Course with ID " << id << " not found." << endl;
            return;
        }

        // Case 1: Node to be deleted has no children
        if (!current->left && !current->right) {
            if (current == root)
                root = nullptr;
            else if (parent->left == current)
                parent->left = nullptr;
            else
                parent->right = nullptr;

            delete current;
            cout<<"Course dropped successfully" <<endl;
        }
        // Case 2: Node to be deleted has one child
        else if (!current->left || !current->right) {
            TreeNode* child = (current->left) ? current->left : current->right;

            if (current == root)
                root = child;
            else if (parent->left == current)
                parent->left = child;
            else
                parent->right = child;

            delete current;
            cout<<"Course dropped successfully" <<endl;
        }

        // Case 3: Node to be deleted has two children
        else {
            TreeNode* successorParent = current;
            TreeNode* successor = current->right;

            while (successor->left) {
                successorParent = successor;
                successor = successor->left;
            }

            current->data = successor->data;

            if (successorParent->left == successor)
                successorParent->left = successor->right;
            else
                successorParent->right = successor->right;

            delete successor;
            cout<<"Course dropped successfully" <<endl;
        }

        hashmap1.deletecourse_from_hashmap(id); //used to drop from hashmap in the same time
    }


    // Call the searchWithHashing() method from HashMap
    void searchCourse_BST_Hash(int courseID) {
        hashmap1.searchWithHashing(courseID);  // Call searchWithHashing() using hashmap1
    }

};


// 3. Course Enrollment History: Double Linked List
// Track each student's course enrollment history using a Double Linked List.

// Enrollment class
class Enrollment {
public:
    int studentID;
    string studentName;
    int courseID;
    string courseName;
    int courseCredits;

    // Constructor
    Enrollment(int sid, string sname, int cid, string cname, int credits)
        : studentID(sid), studentName(sname), courseID(cid), courseName(cname), courseCredits(credits) {}
};

// DLL Node class
class DLLNode {
public:
    Enrollment data;
    DLLNode* next;
    DLLNode* prev;

    DLLNode(Enrollment e) : data(e), next(nullptr), prev(nullptr) {} // Constructor
};

// Functionalities to implement:
// add(): Add a new enrollment record for a student.
class EnrollmentDLL {
private:
    DLLNode* head;
    DLLNode* tail;

public:
    EnrollmentDLL() : head(nullptr), tail(nullptr) {}  // Constructor to initialize head and tail

    // Add a new enrollment record
    void addEnrollment() {
        int studentID, courseID, courseCredits;
        string studentName, courseName;

        cout << "Enter Student ID: ";
        cin >> studentID;
        cin.ignore();

        cout << "Enter Student Name: ";
        getline(cin, studentName);

        cout << "Enter Course ID: ";
        cin >> courseID;
        cin.ignore();

        cout << "Enter Course Name: ";
        getline(cin, courseName);

        cout << "Enter Course Credits: ";
        cin >> courseCredits;

        // Create an instance of class Enrollment
        Enrollment newEnrollment(studentID, studentName, courseID, courseName, courseCredits);

        // Store the instance in the node
        DLLNode* newNode = new DLLNode(newEnrollment);

        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        cout << "Enrollment added successfully!" << endl;
    }

    // view(): Display the enrollment history of a specific student.
    void viewEnrollmentHistory_of_specif_student() {
        if (!head) { //if empity
            cout << "No enrollment records found." << endl;
            return;
        }

        int studentID;
        cout << "Enter Student ID to view enrollment history: ";
        cin >> studentID;

        DLLNode* temp = head;
        bool found = false;
        while (temp) {
            if (temp->data.studentID == studentID) {
                found = true;
                cout << "Student ID: " << temp->data.studentID
                     << "\nName: " << temp->data.studentName
                     << "\nCourse ID: " << temp->data.courseID
                     << "\nCourse Name: " << temp->data.courseName
                     << "\nCredits: " << temp->data.courseCredits << "\n-----------------" << endl;
            }
            temp = temp->next;
        }

        if (!found) { //if student doesn't exist
            cout << "No enrollment records found for Student ID " << studentID << "." << endl;
        }
    }
};



// 4. Course Registration: Stack
// Validate course prerequisites using a Stack.
// How it works:
// Push all required prerequisites onto the stack.
// Pop completed prerequisites from the stack based on the student's record.
// If the stack is empty, the student is eligible to register.

//Stake Node
class StackNode {
public:
    int courseID;
    StackNode* next;  // Pointer to the next node in the stack.

    StackNode(int id) : courseID(id), next(nullptr) {}  // Constructor to initialize courseID and next pointer.
};

class PrerequisitesStack { // Course Registration: Stack
private:
    StackNode* top;  // Top node of the stack.

public:
    PrerequisitesStack() : top(nullptr) {} // Constructor to initialize top as nullptr.

    void push(int courseID) {
        StackNode* newNode = new StackNode(courseID);  // Create new stack node.
        newNode->next = top;  // Link the new node to the previous top.
        top = newNode;  // Update the top to the new node.
        cout << "Course ID " << courseID << " added to prerequisites stack." << endl;
    }

    bool isEmpty() {
        return top == nullptr;  // Return true if the stack is empty.
    }

    void pop() {
        if (!isEmpty()) {
            StackNode* temp = top;  // Store the top node.
            top = top->next;  // Move the top to the next node.
            cout << "Removed prerequisite: Course ID " << temp->courseID << endl;
            delete temp;  // Delete the removed node.
        } else {
            cout << "No prerequisites remaining." << endl;
        }
    }

    // Functionalities to implement:

    // validatePrerequisites(courseID, studentID): Check if a student meets the prerequisites for a course.
    // Display remaining prerequisites if validation fails.
    void validatePrerequisites() {
        if (top == nullptr) {  // Directly check if the stack is empty
            cout << "Student meets all prerequisites and is eligible to register." << endl;
            return;
        }

        cout << "Student still has pending prerequisites." << endl;

        StackNode* temp = top;  // Pointer to traverse the stack
        while (temp != nullptr) {
            cout << "Pending prerequisite: Course ID " << temp->courseID << endl;
            temp = temp->next;
        }
    }

};

// 5. Course Waitlist: Queue
// Manage course waitlists using a Queue.

// QueueNode class
class QueueNode {
public:
    int studentID;
    QueueNode* next;  // Pointer to the next node in the queue.

    QueueNode(int id) : studentID(id), next(nullptr) {} // Constructor
};

// WaitlistQueue class
class WaitlistQueue {
private:
    QueueNode* front;
    QueueNode* rear;

public:
    WaitlistQueue() : front(nullptr), rear(nullptr) {} //Constructor

    // Functionalities to implement:
    // enqueue(): Add a student to the waitlist when a course is full.
    void enqueue(int studentID) {
        QueueNode* newNode = new QueueNode(studentID);
        if (rear == nullptr) {
            front = rear = newNode;  // If the queue is empty, set both front and rear to the new node.
        } else {
            rear->next = newNode;  // Link the new node after the current rear.
            rear = newNode;  // Update the rear to the new node.
        }
        cout << "Student " << studentID << " added to waitlist. " << endl;
    }

    // dequeue(): Enroll the first student on the waitlist when a spot becomes available.
    void dequeue() {
        if (front == nullptr) {
            cout << "Waitlist is empty. No students to remove." << endl;
            return;
        }

        QueueNode* temp = front;
        front = front->next;  // Move the front pointer to the next node in the queue.
        if (front == nullptr) {
            rear = nullptr;  // If the queue becomes empty, set the rear to nullptr.
        }
        cout << "Student " << temp->studentID << " removed from waitlist." << endl;
        delete temp;  // Free the memory of the removed node.
    }
};


// 6. Search and Sort Operations
// Implement search and sort functionalities for:

// Students by ID.  //search for students in the single linked list

void StudentSLL::binarysearch(SLLNode *head, int studentID) { //this StudentSLL:: is used when creating a method related to a class oustide of the class //O(n log n)
    selectionSort(); //if  StudentSLL::-scope resolution operator- is removed this will not work
    // Check if the list is empty
    if (head == nullptr) {
        cout << "SLL is empty." << endl;
        return;
    }

    // Count the number of nodes
    int length = 0;
    SLLNode* temp = head;
    while (temp) {
        length++;
        temp = temp->next;
    }

    SLLNode* left = head;
    SLLNode* right = nullptr;
    bool found = false;

    while (left != right) {
        // Find the middle node by traversing half of the list
        int midIndex = length / 2;
        SLLNode* mid = left;
        for (int i = 0; i < midIndex && mid->next; i++) {
            mid = mid->next;
        }

        if (mid) { // Check if mid is valid
            // If the student ID matches, print the student data
            if (mid->data.studentID == studentID) {
                cout << "Student with ID " << mid->data.studentID << " is found.";
                cout << "\nName: " << mid->data.studentName
                     << "\nEmail: " << mid->data.studentEmail
                     << "\nPhone: " << mid->data.studentPhone
                     << "\nAddress: " << mid->data.studentAddress << "\n";

                found = true; //if found is still false, it prints "Student not found.". in the if function below
                break;  //exit loop if student is found
            }
        } else { //If mid is nullptr, the else block executes, calling break;, which stops the while loop immediately. -to avoid edge cases-
            break;  // Exit if mid is null
        }

        // Move the search boundaries
        if (mid->data.studentID < studentID) { //if not mid and mid is not NULL
            left = mid->next; // Search the right half
            length = length - midIndex - 1; // Reduce the search space
        } else {
            right = mid; // Search the left half
            length = midIndex; // Reduce the search space
        }
    }

    // If the student was not found, print "not found"
    if (!found) {
        cout << "Student not found." << endl;
    }
}

// Courses by ID.   //search in binary search tree
void searchCourse(TreeNode* root, int id) {
    TreeNode* current = root;

    while (current) {
        if (id == current->data.CourseID) {

            // Course found
            cout << "Course Found!" << endl;
            cout << "Course ID: " << current->data.CourseID << endl;
            cout << "Course Name: " << current->data.CourseName << endl;
            cout << "Course Instructor: " << current->data.CourseInstructor << endl;
            cout << "Course Credits: " << current->data.CourseCredits << endl;
            return;

        } else if (id < current->data.CourseID) { //traverse
            current = current->left;
        } else {
            current = current->right;
        }
    }

    cout << "Course with ID " << id << " not found." << endl;
}




//options for user
void menu() {
    cout<< "\n\n\n\t\t\tWelcome to BTATS University!\n";

    cout << "What do you want to do?:\n"<< endl;

//SLL
    cout << "1. Add a Student. " << endl; //

    cout << "2. Delete a Student." << endl;

    cout << "3. Show all students."<< endl; //

//BST
    cout << "4. Add a course." << endl; // add a cousre to the tree

    cout << "5. Drop a course." <<endl; //

//DLL
    cout << "6. Add a new enrollment record for a student. " <<endl;

    cout << "7. Display the enrollment history of a specific student." <<endl;

//Stack
    cout << "8. Add a prerequisites course  " <<endl; //to the stack.

    cout << "9. Remove a prerequisite." <<endl;

    cout << "10. Validate Prerequisites." <<endl;

//Queue
    cout << "11. Add a student to waitlist." <<endl;

    cout << "12. Remove a student from waitlist"<<endl;

//Search and sort
    cout << "13. Search for students using ID." <<endl;

    cout << "14. Search for Courses using ID." <<endl;


//Hashing
    cout << "15. fast search for course-use hashing-."<<endl;

//Exit
    cout << "16. Exit.\n";
}


int main() {
    // class initlization
    StudentSLL StudentSLL1;

    CourseBST CourseBST1;

    EnrollmentDLL EnrollmentDLL1;

    PrerequisitesStack PrerequisitesStack1;

    WaitlistQueue WaitlistQueue1;

    //menu
    int choice;

    while (1){
        menu();

         cin >> choice;

         switch(choice) {

    case 1:
       StudentSLL1.addStudent();
    break;

    case 2:
        StudentSLL1.deleteStudent();
    break;

    case 3:
        StudentSLL1.displayStudents();
    break;

    case 4:
        CourseBST1.addCourse();
    break;

    case 5:
        CourseBST1.dropCourse();
    break;

    case 6:
        EnrollmentDLL1.addEnrollment();
    break;

    case 7:
        EnrollmentDLL1.viewEnrollmentHistory_of_specif_student();
    break;

    case 8:
        int courseID;
        cout << "Enter Course ID to add a prerequisite: ";
        cin >> courseID;
        PrerequisitesStack1.push(courseID);
        break;

    case 9:
        PrerequisitesStack1.pop();
    break;

    case 10:
        PrerequisitesStack1.validatePrerequisites();
    break;

    case 11:
       int studentToEnqueue;
           cout << "Enter Student ID to add to waitlist: ";
           cin >> studentToEnqueue;

           WaitlistQueue1.enqueue(studentToEnqueue);
    break;

    case 12:
           WaitlistQueue1.dequeue();
    break;

    case 13:
        int studentid;
             cout << "Enter Student ID to search for: ";
             cin >> studentid;

             StudentSLL1.binarysearch(StudentSLL1.getHead(), studentid); //
    break;

    case 14:
        int searchID;
             cout << "Enter Course ID to search: ";
             cin >> searchID;

             searchCourse(CourseBST1.getRoot(), searchID);
    break;

    case 15:
        int searchID2;
             cout << "Enter Course ID to search: ";
             cin >> searchID2;

             CourseBST1.searchCourse_BST_Hash(searchID2);
    break;

    case 16:
        exit(0);
    break;

    default:
        cout<< "you can only choose from the optiones!" <<endl;
    break;

        }
    }
    return 0;
}