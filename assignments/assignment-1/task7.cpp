#include <iostream>
using namespace std;

struct Tab {

  int id;
  string title;
  string url;

  Tab* next;
  Tab* prev;

  Tab(int tabID, string tabTitle, string URL) {
    id = tabID;
    title = tabTitle;
    url = URL;
    next = nullptr;
    prev = nullptr;
  }
};

void openTab(Tab*& head, Tab*& tail, int id, string title, string url) {

  Tab* newTab = new Tab(id, title, url);

  if (head == nullptr) {
    head = newTab;
    tail = newTab;

    return;
  }

  tail->next = newTab;
  newTab->prev = tail;
  tail = newTab;
}

void closeTabByID(Tab*& head, Tab*& tail, int id) {
  if (head == nullptr) {
    cout << "No Tabs opened." << endl;
    return;
  }

  Tab* currTab = head;

  while (currTab != nullptr) {

    if (currTab->id == id) {

      if (currTab == head && currTab == tail) { // It's the single Node
        head = nullptr;
        tail = nullptr;
      } else if (currTab->prev == nullptr) { // It's the head
        head = currTab->next;
        head->prev = nullptr;
      } else if (currTab->next == nullptr) { // It's the tail
        tail = currTab->prev;
        tail->next = nullptr;
      } else { // It's in the middle
        currTab->next->prev = currTab->prev;
        currTab->prev->next = currTab->next;
      }
      delete currTab;
      return;
    }
    currTab = currTab->next;
  }
  cout << "Error: Tab with ID " << id << " not found." << endl;
}

void switchTab(Tab*& head, Tab*& activeTab, int id) {
  if (head == nullptr) {
    cout << "No Tabs opened." << endl;
    return;
  }

  Tab* currTab = head;

  while (currTab != nullptr) {

    if (currTab->id == id) {
      activeTab = currTab;
      cout << "Switched to tab: " << activeTab->title << endl;
      return;
    }
    currTab = currTab->next;
  }
  cout << "Error: Tab with ID " << id << " not found." << endl;
}

void displayTabsForward(Tab* head) {
  if (head == nullptr) {
    cout << "No open tabs to display." << endl;
    return;
  }

  Tab* currTab = head;

  while (currTab != nullptr) {
    cout << "[" << currTab->id << "] " << currTab->title << " (" << currTab->url << ")" << endl;
    currTab = currTab->next;
  }
}

void displayTabsReverse(Tab* head, Tab* tail) {
  if (head == nullptr) {
    cout << "No open tabs to display." << endl;
    return;
  }

  Tab* currTab = tail;

  while (currTab != nullptr) {
    cout << "[" << currTab->id << "] " << currTab->title << " (" << currTab->url << ")" << endl;
    currTab = currTab->prev;
  }
}

void clearAllTabs(Tab*& head, Tab*& tail, Tab*& activeTab) {
  if (head == nullptr) {
    cout << "No Tabs opened." << endl;
    return;
  }

  Tab* currTab = head;
  while (currTab != nullptr) {
    Tab* nextTab = currTab->next;
    delete currTab;
    currTab = nextTab;
  }

  head = nullptr;
  tail = nullptr;
  activeTab = nullptr;

  cout << "\n[System] All tabs closed. Memory successfully freed." << endl;
}

int main() {

  Tab* head = nullptr;
  Tab* tail = nullptr;
  Tab* activeTab = nullptr;

  cout << "--- BROWSER TAB MANAGER STARTUP ---\n";

  // TEST 1: Open New Tabs (Normal Case)
  openTab(head, tail, 1, "Google", "www.google.com");
  openTab(head, tail, 2, "GitHub", "www.github.com");
  openTab(head, tail, 3, "Instagram", "www.instagram.com");
  openTab(head, tail, 4, "YouTube", "www.youtube.com");

  cout << "\n[Forward Display]" << endl;
  displayTabsForward(head);

  cout << "\n[Reverse Display]" << endl;
  displayTabsReverse(head, tail);

  // TEST 2: Switch Tab (Normal and Edge Case)
  cout << "\n[Switching Tabs]" << endl;
  switchTab(head, activeTab, 3);  // Valid ID
  switchTab(head, activeTab, 99); // Edge Case: Invalid ID

  // TEST 3: Close Tabs (Edge Cases)
  cout << "\n[Closing Tabs]" << endl;

  cout << "Closing Tail (ID 4)..." << endl;
  closeTabByID(head, tail, 4);

  cout << "Closing Head (ID 1)..." << endl;
  closeTabByID(head, tail, 1);

  cout << "Closing Middle (ID 2)..." << endl;
  closeTabByID(head, tail, 2);

  cout << "Closing Non-Existent Tab (ID 100)..." << endl;
  closeTabByID(head, tail, 100);

  cout << "\n[Remaining Tabs]" << endl;
  displayTabsForward(head);

  // TEST 4: Single Node Deletion (Edge Case)
  cout << "\nClosing the last remaining tab (ID 3)..." << endl;
  closeTabByID(head, tail, 3);
  displayTabsForward(head);

  openTab(head, tail, 10, "Canvas", "canvas.comsats.edu.pk");
  openTab(head, tail, 11, "Gmail", "mail.google.com");

  clearAllTabs(head, tail, activeTab);

  return 0;
}