#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string FILE_NAME = "STUDENT.DAT";

class Student {
private:
    int roll;
    string name;
    string division;
    string address;

public:
    void input();
    void display() const;
    int getRoll() const { return roll; }

    void addRecord(int count);
    void showAll() const;
    void searchRecord(int rollNo) const;
    void deleteRecord(int rollNo);
    void editRecord(int rollNo);
};

// Get student details from user
void Student::input() {
    cout << "\nEnter Roll No: ";
    cin >> roll;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Division: ";
    getline(cin, division);
    cout << "Enter Address: ";
    getline(cin, address);
}

// Display student details
void Student::display() const {
    cout << "\nRoll: " << roll
         << "\nName: " << name
         << "\nDivision: " << division
         << "\nAddress: " << address << endl;
}

// Add multiple student records
void Student::addRecord(int count) {
    ofstream out(FILE_NAME, ios::binary | ios::app);
    if (!out) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    for (int i = 0; i < count; ++i) {
        input();
        out.write(reinterpret_cast<char*>(this), sizeof(*this));
    }

    out.close();
}

// Show all student records
void Student::showAll() const {
    ifstream in(FILE_NAME, ios::binary);
    if (!in) {
        cerr << "Error opening file.\n";
        return;
    }

    bool found = false;
    Student s;
    while (in.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        found = true;
        s.display();
    }

    if (!found)
        cout << "\nNo records found.\n";

    in.close();
}

// Search for a student record
void Student::searchRecord(int rollNo) const {
    ifstream in(FILE_NAME, ios::binary);
    if (!in) {
        cerr << "Error opening file.\n";
        return;
    }

    Student s;
    bool found = false;
    while (in.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.getRoll() == rollNo) {
            cout << "\nRecord found:\n";
            s.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nRecord not found.\n";

    in.close();
}

// Delete a student record
void Student::deleteRecord(int rollNo) {
    ifstream in(FILE_NAME, ios::binary);
    ofstream out("TEMP.DAT", ios::binary);

    if (!in || !out) {
        cerr << "Error opening file.\n";
        return;
    }

    Student s;
    bool found = false;
    while (in.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.getRoll() != rollNo)
            out.write(reinterpret_cast<char*>(&s), sizeof(s));
        else
            found = true;
    }

    in.close();
    out.close();
    remove(FILE_NAME.c_str());
    rename("TEMP.DAT", FILE_NAME.c_str());

    if (found)
        cout << "\nRecord deleted successfully.\n";
    else
        cout << "\nRecord not found.\n";
}

// Edit a student record
void Student::editRecord(int rollNo) {
    ifstream in(FILE_NAME, ios::binary);
    ofstream out("TEMP.DAT", ios::binary);

    if (!in || !out) {
        cerr << "Error opening file.\n";
        return;
    }

    Student s;
    bool found = false;
    while (in.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.getRoll() == rollNo) {
            cout << "\nEnter new details:\n";
            s.input();
            found = true;
        }
        out.write(reinterpret_cast<char*>(&s), sizeof(s));
    }

    in.close();
    out.close();
    remove(FILE_NAME.c_str());
    rename("TEMP.DAT", FILE_NAME.c_str());

    if (found)
        cout << "\nRecord updated successfully.\n";
    else
        cout << "\nRecord not found.\n";
}

// Main menu
int main() {
    Student s;
    int choice, n, roll;

    do {
        cout << "\n--- Student Database Menu ---\n";
        cout << "1. Add Student\n2. Display All\n3. Search\n4. Delete\n5. Edit\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter number of students to add: ";
                cin >> n;
                s.addRecord(n);
                break;
            case 2:
                s.showAll();
                break;
            case 3:
                cout << "Enter roll number to search: ";
                cin >> roll;
                s.searchRecord(roll);
                break;
            case 4:
                cout << "Enter roll number to delete: ";
                cin >> roll;
                s.deleteRecord(roll);
                break;
            case 5:
                cout << "Enter roll number to edit: ";
                cin >> roll;
                s.editRecord(roll);
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
