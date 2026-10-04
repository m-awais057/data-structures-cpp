#include <iostream>
using namespace std;

struct ShuttleStop {
  int id;
  string name;
  int distance;
  ShuttleStop* nextStop;

  ShuttleStop(int stopID, string stopName, int dist) {
    id = stopID;
    name = stopName;
    distance = dist;
    nextStop = nullptr;
  }
};

void addStopAtEnd(ShuttleStop*& shuttleHead, ShuttleStop*& tail, int id, string name, int distance) {
  ShuttleStop* newShuttleStop = new ShuttleStop(id, name, distance);

  if (shuttleHead == nullptr) {
    shuttleHead = newShuttleStop;
    shuttleHead->nextStop = shuttleHead;
    tail = newShuttleStop;
    return;
  }
  newShuttleStop->nextStop = shuttleHead;
  tail->nextStop = newShuttleStop;
  tail = newShuttleStop;
}

void addStopAfter(ShuttleStop*& shuttleHead, ShuttleStop*& tail, int id, int newId, string newName, int distance) {

  if (shuttleHead == nullptr) {
    cout << "The shuttle route is currently empty." << endl;
    return;
  }

  ShuttleStop* currStop = shuttleHead;
  do {
    if (currStop->id == id) {
      ShuttleStop* newShuttleStop = new ShuttleStop(newId, newName, distance);

      if (currStop == tail) {
        newShuttleStop->nextStop = shuttleHead;
        tail->nextStop = newShuttleStop;
        tail = newShuttleStop;
      } else {
        newShuttleStop->nextStop = currStop->nextStop;
        currStop->nextStop = newShuttleStop;
      }
      return;
    }
    currStop = currStop->nextStop;

  } while (currStop != shuttleHead);
}

void removeStop(ShuttleStop*& shuttleHead, ShuttleStop*& tail, int id) {
  if (shuttleHead == nullptr) {
    cout << "The shuttle route is currently empty." << endl;
    return;
  }

  ShuttleStop* currStop = shuttleHead;
  ShuttleStop* prevStop = nullptr;

  do {
    if (currStop->id == id) {

      if (prevStop == nullptr) { // Handling the Head

        if (currStop == tail) {
          shuttleHead = nullptr;
          tail = nullptr;

        } else {
          shuttleHead = currStop->nextStop;
          tail->nextStop = shuttleHead;
        }
      } else { // Handling the Middle or Tail
        if (currStop == tail) {
          prevStop->nextStop = shuttleHead;
          tail = prevStop;
        } else {
          prevStop->nextStop = currStop->nextStop;
        }
      }

      delete currStop;
      return;
    }

    prevStop = currStop;
    currStop = currStop->nextStop;

  } while (currStop != shuttleHead);
}

void displayRoute(ShuttleStop* shuttleHead) {
  if (shuttleHead == nullptr) {
    cout << "The shuttle route is currently empty." << endl;
    return;
  }

  ShuttleStop* currStop = shuttleHead;

  do {
    std::cout << "[" << currStop->id << ", " << currStop->name << ", "
              << currStop->distance << " km] -> ";

    currStop = currStop->nextStop;

  } while (currStop != shuttleHead);

  cout << "back to " << shuttleHead->name << endl;
}

void findLongestDistance(ShuttleStop* shuttleHead) {
  if (shuttleHead == nullptr) {
    cout << "The shuttle route is currently empty." << endl;
    return;
  }

  ShuttleStop* hold = nullptr;
  ShuttleStop* currStop = shuttleHead;

  int max = 0;
  do {
    if (currStop->distance > max) {
      max = currStop->distance;
      hold = currStop;
    }

    currStop = currStop->nextStop;

  } while (currStop != shuttleHead);

  cout << hold->name << " has the longest distance of " << hold->distance
       << " km to the next stop" << endl;
}

void deleteRoute(ShuttleStop*& shuttleHead, ShuttleStop*& tail) {
  if (shuttleHead == nullptr) {
    cout << "The shuttle route is currently empty. Nothing to delete." << endl;
    return;
  }

  tail->nextStop = nullptr;

  ShuttleStop* currStop = shuttleHead;

  while (currStop != nullptr) {

    ShuttleStop* tempStop = currStop;
    currStop = currStop->nextStop;
    delete (tempStop);
  }

  shuttleHead = nullptr;
  tail = nullptr;

  cout << "The entire route has been deleted and memory is freed." << endl;
}

int main() {
  // 1. Initialize empty list pointers
  ShuttleStop* shuttleHead = nullptr;
  ShuttleStop* tail = nullptr;

  // 2. Build the initial route from the example
  addStopAtEnd(shuttleHead, tail, 1, "Main Gate", 2);
  addStopAtEnd(shuttleHead, tail, 2, "Roller Coaster", 3);
  addStopAtEnd(shuttleHead, tail, 3, "Water Park", 5);

  cout << "Initial Route:" << endl;
  displayRoute(shuttleHead);

  // 3. Test insertion at the end
  cout << "\nAfter:\naddStopAtEnd(4, \"Zoo\", 4)\nThe route becomes:" << endl;
  addStopAtEnd(shuttleHead, tail, 4, "Zoo", 4);
  displayRoute(shuttleHead);

  // 4. Test the maximum distance search
  cout << "\nAfter:\nfindLongestDistance()\nOutput:" << endl;
  findLongestDistance(shuttleHead);

  cout << "\n--- Additional Edge Case Testing ---" << endl;

  cout << "Inserting after ID 2 (Middle):" << endl;
  addStopAfter(shuttleHead, tail, 2, 99, "Food Court", 1);
  displayRoute(shuttleHead);

  cout << "\nRemoving Head (ID 1):" << endl;
  removeStop(shuttleHead, tail, 1);
  displayRoute(shuttleHead);

  cout << "\nRemoving Tail (ID 4):" << endl;
  removeStop(shuttleHead, tail, 4);
  displayRoute(shuttleHead);

  deleteRoute(shuttleHead, tail);
  return 0;
}