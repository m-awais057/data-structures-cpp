#include <iostream>
using namespace std;

struct Node {
  int participantNumber;
  Node* next;

  Node(int num) {
    participantNumber = num;
    next = nullptr;
  }
};

void displayGroup(Node* head) {
  if (head == nullptr)
    return;
  Node* temp = head;
  cout << "{";
  do {
    cout << temp->participantNumber;
    temp = temp->next;
    if (temp != head)
      cout << ", ";
  } while (temp != head);
  cout << "} ";
}

Node* findMiddle(Node* head) {
  if (head == nullptr) {
    return nullptr;
  }

  Node* slow = head;
  Node* fast = head;

  while (fast->next != head && fast->next->next != head) {
    slow = slow->next;
    fast = fast->next->next;
  }

  return slow;
}

void splitCircle(Node* head, Node*& firstHalf, Node*& secondHalf) {
  if (head == nullptr || head->next == head) {
    firstHalf = head;
    secondHalf = nullptr;
    return;
  }

  Node* middle = findMiddle(head);

  firstHalf = head;
  secondHalf = middle->next;

  Node* temp = secondHalf;
  while (temp->next != head) {
    temp = temp->next;
  }

  temp->next = secondHalf;
  middle->next = firstHalf;
}

void divideCircle(Node* head, int level = 0) {
  if (head == nullptr) {
    return;
  }

  if (head->next == head) {
    cout << "Level " << level << ": ";
    displayGroup(head);
    cout << endl;

    delete head;
    return;
  }

  Node* firstHalf = nullptr;
  Node* secondHalf = nullptr;

  splitCircle(head, firstHalf, secondHalf);

  cout << "Level " << level + 1 << " split: ";
  displayGroup(firstHalf);
  displayGroup(secondHalf);
  cout << endl;

  divideCircle(firstHalf, level + 1);
  divideCircle(secondHalf, level + 1);
}

int main() {
  Node* head = nullptr;
  Node* tail = nullptr;
  int n = 8;

  // 1. Dynamically create the initial circular linked list of participants
  for (int i = 1; i <= n; i++) {
    Node* newNode = new Node(i);
    if (head == nullptr) {
      head = newNode;
      tail = newNode;
      newNode->next = head; // Initialize circular connection
    } else {
      tail->next = newNode;
      tail = newNode;
      tail->next = head; // Maintain circular connection
    }
  }

  // 2. Display the initial state
  cout << "Initial Circular List: ";
  Node* temp = head;
  do {
    cout << temp->participantNumber;
    temp = temp->next;
    if (temp != head)
      cout << " -> ";
  } while (temp != head);
  cout << " -> back to " << head->participantNumber << endl
       << endl;

  // 3. Trigger the recursive division
  divideCircle(head);

  head = nullptr;
  tail = nullptr;

  return 0;
}