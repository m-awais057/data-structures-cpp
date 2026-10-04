#include <iostream>
using namespace std;

struct DemoSlot
{
    int demoID;
    string startupName;
    string startTime;

    DemoSlot* nextDemo;

    DemoSlot(int id, string startup, string time){
        demoID = id;
        startupName = startup;
        startTime = time;
        nextDemo = nullptr;
    }
};

struct Category
{
    int categoryID;
    string categoryName;

    Category* nextCategory;
    DemoSlot* demoHead;

    Category(int id, string name){
        categoryID = id;
        categoryName = name;
        nextCategory = nullptr;
        demoHead = nullptr;
    }

};

void insertByCategoryAndDemoID(Category *&categoryHead, int catID,string catName, int demoID, string startup, string time)
{

    if (categoryHead == nullptr)
    {
        categoryHead = new Category(catID, catName);

        categoryHead->demoHead = new DemoSlot(demoID, startup, time);

        return;
    }

    Category *prevCat = nullptr;
    Category *currCat = categoryHead;

    while (currCat != nullptr && currCat->categoryID < catID)
    {
        
        prevCat = currCat;
        currCat = currCat->nextCategory;
    }

    if (currCat == nullptr || currCat->categoryID != catID)
    {
        Category *newCat = new Category(catID, catName);
        newCat->nextCategory = currCat;

        if (prevCat == nullptr)
        {
            categoryHead = newCat;
        }
        else{
            prevCat->nextCategory = newCat;
        }
        currCat = newCat;
    }

    DemoSlot *prevDemo = nullptr;
    DemoSlot *currDemo = currCat->demoHead;

    while (currDemo != nullptr && currDemo->demoID < demoID)
    {
        prevDemo = currDemo;
        currDemo = currDemo->nextDemo;
    }

    DemoSlot *newDemo = new DemoSlot(demoID, startup, time);

    newDemo->nextDemo = currDemo;

    if (prevDemo == nullptr){
        currCat->demoHead = newDemo;
    }
    else{
        prevDemo->nextDemo = newDemo;        
    }
}

void deleteByDemoID(Category *categoryHead, int demoID)
{
    Category* currCat = categoryHead;
    
    while(currCat != nullptr){

        DemoSlot* prevDemo = nullptr;
        DemoSlot* currDemo = currCat->demoHead;
        
        bool foundID = false;
        while(currDemo != nullptr){

            if (currDemo->demoID == demoID){
                foundID = true;
                if(prevDemo == nullptr){
                    currCat->demoHead = currDemo->nextDemo;
                }
                else{
                    prevDemo->nextDemo = currDemo->nextDemo;
                }
                delete(currDemo);
                return;
            }
            prevDemo = currDemo;
            currDemo = currDemo->nextDemo;
        
        }

        currCat = currCat->nextCategory;
    }
    cout << "Error: Demo ID " << demoID << " not found in the schedule." << endl;
}

void displaySchedule(Category *categoryHead)
{
    if(categoryHead == nullptr){
        cout << "The Schedule is completely empty" << endl;
        return;
    }

    Category* currCat = categoryHead;
    while(currCat != nullptr){
        cout << "Category " << currCat->categoryID << " - " << currCat->categoryName << ":" << endl;

        DemoSlot* currDemo = currCat->demoHead;

        if (currDemo == nullptr){
            cout << "\t(No demos scheduled yet)" << endl;
        }

        while(currDemo != nullptr){
            cout << "\t-> Demo ID: " << currDemo->demoID
                 << " | Startup: " << currDemo->startupName
                 << " | Time: " << currDemo->startTime << endl;
                
            currDemo = currDemo->nextDemo;
        }
        cout << "---------------------------------------------------" << endl;
        currCat = currCat->nextCategory;
    }
}

void clearEntireSchedule(Category *&categoryHead)
{
    Category *currCat = categoryHead;

    
    while (currCat != nullptr)
    {

        
        DemoSlot *currDemo = currCat->demoHead;
        while (currDemo != nullptr)
        {
            DemoSlot *tempDemo = currDemo; 
            currDemo = currDemo->nextDemo; 
            delete tempDemo;               
        }

        
        Category *tempCat = currCat;     
        currCat = currCat->nextCategory; 
        delete tempCat;                  
    }

    categoryHead = nullptr;
}

int main()
{
    Category* categoryHead = nullptr;
    
    // 1. Test inserting into an empty list (Creates Cat 5, Demo 102)
    insertByCategoryAndDemoID(categoryHead, 5, "AI Startups", 102, "NeuroTech", "10:00 AM");

    // 2. Test inserting a category at the BEGINNING (Cat 2 < Cat 5)
    insertByCategoryAndDemoID(categoryHead, 2, "Robotics", 10, "AutoBot", "09:00 AM");

    // 3. Test inserting a category at the END (Cat 8 > Cat 5)
    insertByCategoryAndDemoID(categoryHead, 8, "Cyber Security", 200, "LockDown", "11:00 AM");

    // 4. Test inserting a demo at the BEGINNING of an existing category (Demo 100 < 102 in Cat 5)
    insertByCategoryAndDemoID(categoryHead, 5, "AI Startups", 100, "VisionAI", "09:30 AM");

    // 5. Test inserting a demo at the END of an existing category (Demo 105 > 102 in Cat 5)
    insertByCategoryAndDemoID(categoryHead, 5, "AI Startups", 105, "DataMind", "10:30 AM");

    // 6. Test inserting a demo in the MIDDLE of an existing category (Demo 103 between 102 and 105)
    insertByCategoryAndDemoID(categoryHead, 5, "AI Startups", 103, "SmartBot", "10:15 AM");

    cout << "\nSchedule after all insertions:" << endl;
    displaySchedule(categoryHead);

    // 7. Test deleting a demo from the MIDDLE of a list
    cout << "\nDeleting Demo 103 (Middle of Category 5)..." << endl;
    deleteByDemoID(categoryHead, 103);

    // 8. Test the "Empty Category" rule (Deleting the ONLY demo in Category 2)
    cout << "Deleting Demo 10 (Last demo in Category 2)..." << endl;
    deleteByDemoID(categoryHead, 10);

    // 9. Test deleting a non-existent Demo ID
    cout << "Attempting to delete Demo 999 (Non-existent)..." << endl;
    deleteByDemoID(categoryHead, 999);

    cout << "\nSchedule after deletions:" << endl;
    
    displaySchedule(categoryHead);

    clearEntireSchedule(categoryHead);

    return 0;
}