#include <iostream>
using namespace std;

struct Node {
  int data;
  Node* next;

  Node(int data, Node* next = nullptr) {
    this->data = data;
    this->next = next;
  }
};

void insertAtTail(Node*& head, Node*& tail, int data) {
  Node* newNode = new Node(data);
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

Node* merge(Node* left, Node* right) {
  // Base Cases: If one list is empty, return the other
  if (left == nullptr)
    return right;
  if (right == nullptr)
    return left;

  // Recursive sorting (Descending Order)
  if (left->data >= right->data) {
    left->next = merge(left->next, right);
    return left;
  } else {
    right->next = merge(left, right->next);
    return right;
  }
}

Node* mergeSort(Node* head) {
  // Base Case: A list of 0 or 1 nodes is already sorted
  if (head == nullptr || head->next == nullptr) {
    return head;
  }

  // Divide
  Node* secondHalf = nullptr;
  splitList(head, secondHalf);

  // Conquer (Recursively sort the halves)
  Node* leftSorted = mergeSort(head);
  Node* rightSorted = mergeSort(secondHalf);

  // Merge
  return merge(leftSorted, rightSorted);
}

void printList(Node* head) {
  Node* temp = head;
  while (temp != nullptr) {
    cout << temp->data << " -> ";
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

  head1 = mergeSort(head1);
  head2 = mergeSort(head2);

  cout << "\nAfter sorting each half in descending order: " << endl;
  cout << "List 1:" << endl;
  printList(head1);

  cout << "\nList 2:" << endl;
  printList(head2);

  // Free the allocated memory
  freeList(head1);
  freeList(head2);
}
