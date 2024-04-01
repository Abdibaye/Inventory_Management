#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Item {
public:
    string Item_ID;
    string Item_name;
    double Item_price;
    int Item_quantity;
};

vector<Item> Item_data;

void add_Item() {
    int permission = 1;
    while (permission == 1) {
        Item item;

        cout << "Enter Item ID: ";
        getline(cin, item.Item_ID);

        cout << "Enter Item name: ";
        getline(cin, item.Item_name);

        cout << "Enter Item Price: ";
        cin >> item.Item_price;

        cout << "Enter Item quantity: ";
        cin >> item.Item_quantity;

        cin.ignore(); // Clear input buffer

        Item_data.push_back(item);

        cout << endl;
        cout << "Enter 1 to continue" << endl;
        cout << "Enter 2 to Exit" << endl;
        cout << "1 or 2: ";
        cout << endl;
        cin >> permission;
        cin.ignore(); // Clear input buffer
    }
}

void Delete() {
    cout << "List of items:" << endl;
    for (const auto& item : Item_data) {
        cout << item.Item_name << endl;
    }

    string name;
    cout << "Enter the name of the item you want to delete: ";
    getline(cin, name);

    auto iter = remove_if(Item_data.begin(), Item_data.end(), [&](const Item& item) {
        return item.Item_name == name;
    });

    if (iter != Item_data.end()) {
        Item_data.erase(iter, Item_data.end());
        cout << "Item '" << name << "' deleted successfully." << endl;
    } else {
        cout << "Item '" << name << "' not found in the list." << endl;
    }
}

void save_Items() {
    ofstream outFile("items.txt");
    if (!outFile) {
        cerr << "Error opening file." << endl;
        return;
    }

    for (const auto& item : Item_data) {
        outFile << item.Item_ID << "," << item.Item_name << "," << item.Item_price << "," << item.Item_quantity << endl;
    }

    outFile.close();
    cout << "Items saved to file successfully." << endl;
}

void load_Items() {
    ifstream inFile("items.txt");
    if (!inFile) {
        cerr << "Error opening file." << endl;
        return;
    }

    Item_data.clear(); // Clear existing data

    string line;
    while (getline(inFile, line)) {
        Item item;
        stringstream ss(line);
        getline(ss, item.Item_ID, ',');
        getline(ss, item.Item_name, ',');
        ss >> item.Item_price;
        ss.ignore(); // Ignore comma
        ss >> item.Item_quantity;
        Item_data.push_back(item);
    }

    inFile.close();
    cout << "Items loaded from file successfully." << endl;
}

int main() {
    load_Items(); // Load items from file

    int option = 1;
    while (option != 4) {
        cout << "Press 1 to add element" << endl;
        cout << "Press 2 to delete element" << endl;
        cout << "Press 3 to save items" << endl;
        cout << "Press 4 to exit" << endl;
        cout << "Your choice: ";
        cin >> option;
        cin.ignore();

        switch (option) {
            case 1:
                add_Item();
                break;
            case 2:
                Delete();
                break;
            case 3:
                save_Items();
                break;
            case 4:
                cout << "You have seccessfully logout!" << endl; 

            default:
                break;
        }
    }
    
    return 0;
}
