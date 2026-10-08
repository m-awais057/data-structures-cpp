#include <iostream>
using namespace std;

struct Node {
  string word;
  Node* next;
  Node* prev;

  Node(string w) {
    word = w;
    next = nullptr;
    prev = nullptr;
  }
};

void insert(Node*& head, Node*& tail, Node*& cursor, string word) {

  Node* newWord = new Node(word);
  if (head == nullptr && tail == nullptr) {
    head = newWord;
    tail = newWord;
    cursor = newWord;

    newWord->next = newWord;
    newWord->prev = newWord;
  } else {
    newWord->next = head;
    newWord->prev = tail;
    tail->next = newWord;
    head->prev = newWord;
    tail = newWord;
  }
}

void deleteCurrent(Node*& head, Node*& tail, Node*& cursor) {
  if (head == nullptr) {
    cout << "Document is empty." << endl;
    return;
  }

  Node* temp = cursor;

  if (head == tail) { // single word
    head = nullptr;
    tail = nullptr;
    cursor = nullptr;
  }

  else if (cursor == head) {
    head = head->next;
    head->prev = tail;
    tail->next = head;
    cursor = head;

  }

  else if (cursor == tail) {
    cursor->prev->next = head;
    head->prev = cursor->prev;
    tail = cursor->prev;
    cursor = head;
  }

  else {
    cursor->prev->next = cursor->next;
    cursor->next->prev = cursor->prev;
    cursor = cursor->next;
  }

  delete temp;
}

void findAndReplace(Node* head, string oldWord, string newWord) {
  if (head == nullptr) {
    cout << "Document is empty." << endl;
    return;
  }

  Node* temp = head;
  bool found = false;
  do {
    if (temp->word == oldWord) {
      temp->word = newWord;
      found = true;
    }
    temp = temp->next;
  } while (temp != head);

  if (!found) {
    cout << "Error: " << oldWord << " not found." << endl;
  }
}

int count(Node* head) {
  if (head == nullptr) {
    return 0;
  }
  Node* temp = head;
  int count = 0;
  do {
    count++;
    temp = temp->next;
  } while (temp != head);

  return count;
}

void gotoNext(Node* head, Node*& cursor) {
  if (head == nullptr) {
    cout << "Document is empty." << endl;
    return;
  }

  cursor = cursor->next;
}

void gotoPrevious(Node* head, Node*& cursor) {
  if (head == nullptr) {
    return;
  }

  cursor = cursor->prev;
}

void displayForward(Node* head) {
  if (head == nullptr) {
    cout << "Document is empty." << endl;
    return;
  }
  Node* temp = head;
  cout << "Text: ";
  do {
    cout << temp->word << " ";
    temp = temp->next;

  } while (temp != head);

  cout << endl;
}

void displayBackward(Node* tail) {
  if (tail == nullptr) {
    cout << "Document is empty." << endl;
    return;
  }
  Node* temp = tail;
  cout << "Text: ";
  do {
    cout << temp->word << " ";
    temp = temp->prev;

  } while (temp != tail);

  cout << endl;
}

int main() {

  Node* head = nullptr;
  Node* tail = nullptr;
  Node* cursor = nullptr;

  // 1. EMPTY LIST TESTS
  cout << "\n[TEST 1: Empty List Handling]" << endl;
  displayForward(head);
  cout << "Total words: " << count(head) << endl;

  // 2. SINGLE NODE TESTS
  cout << "\n[TEST 2: Single-Word List & Insertion]" << endl;
  insert(head, tail, cursor, "First");
  displayForward(head);
  cout << "Current Cursor on: " << cursor->word << endl;

  // 3. MULTIPLE INSERTIONS & DISPLAY
  cout << "\n[TEST 3: Normal Insertions & Display Directions]" << endl;
  insert(head, tail, cursor, "Second");
  insert(head, tail, cursor, "Third");
  insert(head, tail, cursor, "Fourth");

  cout << "Forward Display: " << endl;
  displayForward(head);

  cout << "Reverse Display: " << endl;
  displayBackward(tail);

  cout << "Total words: " << count(head) << endl;

  // 4. CURSOR NAVIGATION & WRAP-AROUND
  cout << "\n[TEST 4: Cursor Movement & Wrap-Around]" << endl;
  cursor = tail; // Manually jump to end for testing
  cout << "Cursor currently at tail: " << cursor->word << endl;

  gotoNext(head, cursor);
  cout << "Cursor after gotoNext() (Wrap tail to head): " << cursor->word << endl;

  gotoPrevious(head, cursor);
  cout << "Cursor after gotoPrevious() (Wrap head to tail): " << cursor->word << endl;

  // 5. FIND AND REPLACE (INCLUDING EDGE CASES)
  cout << "\n[TEST 5: Find and Replace]" << endl;
  // Normal case
  findAndReplace(head, "Second", "ReplacedWord");
  cout << "After replacing 'Second': ";
  displayForward(head);

  // Edge case: Searching for a word that does not exist
  cout << "Searching for non-existent word: " << endl;
  findAndReplace(head, "Ghost", "Spooky");

  // 6. DELETION AND CURSOR UPDATING
  cout << "\n[TEST 6: Deletion & Cursor Updates]" << endl;
  cursor = head->next; // Move cursor to "ReplacedWord"
  cout << "Cursor before deletion: " << cursor->word << endl;

  deleteCurrent(head, tail, cursor);
  cout << "List after deleting current word: " << endl;
  displayForward(head);
  cout << "Cursor updated to next word automatically: " << cursor->word << endl;

  // 7. DELETION OF THE ONLY WORD
  cout << "\n[TEST 7: Deletion of the Only Word]" << endl;
  // Delete the remaining words to get down to 1
  deleteCurrent(head, tail, cursor);
  deleteCurrent(head, tail, cursor);
  cout << "List reduced to single word: ";
  displayForward(head);

  // Delete the final word
  deleteCurrent(head, tail, cursor);
  cout << "List after deleting the final word: ";
  displayForward(head);

  return 0;
}