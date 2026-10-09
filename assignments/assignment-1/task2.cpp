#include <iostream>
using namespace std;

struct Node {
  int marks;
  Node* next;

  Node(int data, Node* next = nullptr) {
    this->marks = data;
    this->next = next;
  }
};

void insertAtTail(Node*& head, Node*& tail, int marks) {
  Node* newNode = new Node(marks);
  if (head == nullptr) {
    head = newNode;
    tail = newNode;
  } else {
    tail->next = newNode;
    tail = newNode;
  }
}

void splitList(Node* head1, Node*& head2) {
  if (head1 == nullptr || head1->next == nullptr) {
    head2 = nullptr;
    return;
  }

  Node* slow = head1;
  Node* fast = head1->next;

  while (fast != nullptr && fast->next != nullptr) {

    slow = slow->next;
    fast = fast->next->next;
  }

  head2 = slow->next;
  slow->next = nullptr;
}

void sortDescending(Node*& head) {

  if (head == nullptr || head->next == nullptr)
    return;

  bool swapped;
  do {
    swapped = false;
    Node* prev = nullptr;
    Node* curr = head;

    while (curr->next != nullptr) {
      Node* nextNode = curr->next;

      if (curr->marks < nextNode->marks) {

        // STEP 1 & 2: The Physical Swap
        curr->next = nextNode->next;
        nextNode->next = curr;

        // STEP 3: Fix the trailing train
        if (prev == nullptr) {
          head = nextNode; // Updating the main starting pointer
        } else {
          prev->next = nextNode; // Linking the rest of the train
        }

        // STEP 4: Step Forward
        prev = nextNode;
        swapped = true;
      } else {
        // No swap needed. Just take one normal step forward.
        prev = curr;
        curr = nextNode;
      }
    }
  } while (swapped);
}

void printList(Node* head) {
  Node* temp = head;
  while (temp != nullptr) {
    cout << temp->marks << " -> ";
    temp = temp->next;
  }
  cout << "NULL" << endl;
}

void freeList(Node*& head) {
  Node* current = head;
  while (current != nullptr) {
    Node* nextNode = current->next;
    delete current;
    current = nextNode;
  }
  head = nullptr;
}

int main() {
  Node* head1 = nullptr;
  Node* tail = nullptr;

  int testMarks[] = {47, 33, 12, 89, 21, 50, 65, 30};
  int numberOfStudents = 8;

  for (int i = 0; i < numberOfStudents; i++) {
    insertAtTail(head1, tail, testMarks[i]);
  }

  Node* head2 = nullptr;

  splitList(head1, head2);
  cout << "After splitting: " << endl;

  cout << "List 1:" << endl;
  printList(head1);

  cout << "\nList 2:" << endl;
  printList(head2);

  sortDescending(head1);
  sortDescending(head2);

  cout << "\nAfter sorting each half in descending order: " << endl;
  cout << "List 1:" << endl;
  printList(head1);

  cout << "\nList 2:" << endl;
  printList(head2);

  // Free the allocated memory
  freeList(head1);
  freeList(head2);

  return 0;
}
