
//BSCS-15-D
//Shivam Kumar 555585


//I used linkedlist since insersion is easier
// i made the linkedlist sorted so that we can chaeck for duplicates and also searching is faster
// Implemented the help ddesk from queue

// Time Complexity:
// Insersion: O(n) worst-case due to traversal to the correct sorted position.
// Searching: O(n) linear search worst-case, with early stopping enabled because the list is sorted.


#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct Record {
	string name;
	int rollNum;
	Record* next;
};

class LinkedList {
	// using linked list creates simpler code, and allows for easier insertion.
private:
	Record* head;
	// not need for tail

public:
	LinkedList() {
		head = nullptr;
	}

	int insert(string name, int rollNum) {
		// init new node
		Record* newRecord = new Record;
		newRecord->name = name;
		newRecord->rollNum = rollNum;
		newRecord->next = nullptr;

		// check if list is empty or new record belongs at the very head
		if (head == nullptr || head->rollNum > rollNum) {
			if (head != nullptr && head->rollNum == rollNum) {
				delete newRecord;
				return -1; // duplicate found at head
			}
			newRecord->next = head;
			head = newRecord;
			return 0;
		}

		// traverse to find the correct sorted position
		Record* curr = head;
		Record* prev = nullptr;

		while (curr != nullptr) {
			if (curr->rollNum == rollNum) {
				delete newRecord;
				return -1; // duplicate found, reject
			}
			else if (curr->rollNum < rollNum) {
				prev = curr;
				curr = curr->next;
			}
			else {
				break; // found spot between prev and curr
			}
		}

		// insert node
		prev->next = newRecord;
		newRecord->next = curr;
		return 0;
	}

	void display() {
		// check if empty
		if (head == nullptr) {
			cout << "List is empty.\n";
			return;
		}

		Record* curr = head;
		while (curr != nullptr) {
			cout << "Roll: " << curr->rollNum << ", Name: " << curr->name << endl;
			curr = curr->next;
		}
	}

	Record* search(int rollNum) {
		// traverse to find record
		Record* curr = head;
		while (curr != nullptr) {
			if (curr->rollNum == rollNum) {
				return curr; // found
			}
			if (curr->rollNum > rollNum) {
				break; // early stop because list is sorted
			}
			curr = curr->next;
		}
		return nullptr; // not found
	}

	// cleanup function to clear memory
	void cleanup() {
		Record* curr = head;
		while (curr != nullptr) {
			Record* nextNode = curr->next;
			delete curr;
			curr = nextNode;
		}
		head = nullptr; // reset head after clearing
	}
};

// Helper function to display queue
void displayQueue(queue<int> q) {
	if (q.empty()) {
		cout << "Queue is empty.\n";
		return;
	}
	int pos = 1;
	while (!q.empty()) {
		cout << pos++ << ". Roll: " << q.front() << endl;
		q.pop();
	}
}

int main() {
	LinkedList studentList;
	queue<int> helpQueue; // Using STL queue for help requests
	int choice;

	do {
		cout << "\n=== Menu ===\n";
		cout << "1. Add Student\n";
		cout << "2. Search Student\n";
		cout << "3. Display All\n";
		cout << "4. Help Desk Queue\n";
		cout << "5. Clean Up\n";
		cout << "6. Exit\n";
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {
		case 1: {
					int roll;
					string name;
					cout << "Enter Roll Number: ";
					cin >> roll;
					cout << "Enter Name: ";
					cin >> ws; // clear buffer for string
					getline(cin, name);

					int result = studentList.insert(name, roll);
					if (result == -1) {
						cout << "Duplicate roll num\n";
					}
					else {
						cout << "Student added successfully!\n";
					}
					break;
		}
		case 2: {
					int roll;
					cout << "Enter Roll Number to search: ";
					cin >> roll;

					Record* found = studentList.search(roll);
					if (found != nullptr) {
						cout << "Result: Roll: " << found->rollNum << ", Name: " << found->name << endl;
					}
					else {
						cout << "Student not found\n";
					}
					break;
		}
		case 3:
			studentList.display();
			break;
		case 4: {
					int qChoice;
					do {
						cout << "\n--- Help Queue ---\n";
						cout << "1. Add Request\n";
						cout << "2. Serve Next\n";
						cout << "3. View Queue\n";
						cout << "4. Back\n";
						cout << "Enter choice: ";
						cin >> qChoice;

						if (qChoice == 1) {
							int roll;
							cout << "Enter Roll Number: ";
							cin >> roll;

							// reject unregistered
							if (studentList.search(roll) != nullptr) {
								helpQueue.push(roll);
								cout << "Added roll " << roll << " to queue.\n";
							}
							else {
								cout << "Student not registered!\n";
							}
						}
						else if (qChoice == 2) {
							if (helpQueue.empty()) {
								cout << "Queue is empty.\n";
							}
							else {
								cout << "Serving roll: " << helpQueue.front() << endl;
								helpQueue.pop();
							}
						}
						else if (qChoice == 3) {
							displayQueue(helpQueue);
						}
					} while (qChoice != 4);
					break;
		}
		case 5:
			studentList.cleanup();
			cout << "Memory cleaned up.\n";
			break;
		case 6:
			studentList.cleanup();
			cout << "Exiting...\n";
			break;
		default:
			cout << "Invalid choice.\n";
		}
	} while (choice != 6); // fixed loop condition so option 6 actually exits

	return 0;
}
