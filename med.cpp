#include <iostream>
#include <fstream>
#include <string.h>
#include <limits>
#include <string>

using namespace std;

class MedicineData
{
public:
    char medicine_name[100];
    char company[100];
    int qty;
    string compositions[50];
    int compositionCount;

    float price;
};

class Medicine
{
public:
    void inputdetails();
    void modifydetails();
    void deletedetails();
    void alldetails();
    void searchdetails();
};

void Medicine ::inputdetails()
{
    fstream ofp;
    ofp.open("medicine.dat", ios ::out | ios ::binary | ios ::app);

    if (!ofp)
    {
        cout << "Unable to open file" << endl;
        return;
    }

    MedicineData Medicine;

    cout << "Enter name of the Medicines: ";
    cin.ignore();
    cin.getline(Medicine.medicine_name, sizeof(Medicine.medicine_name));

    cout << "Enter Company's name: ";
    cin.getline(Medicine.company, sizeof(Medicine.company));

    cout << "Enter the number of compositions: ";
    cin >> Medicine.compositionCount;

    for (int i = 0; i < Medicine.compositionCount; i++)
    {
        cout << "Enter composition " << i + 1 << ": ";
        cin.ignore();
        getline(cin, Medicine.compositions[i]);
    }

    cout << "Enter Medicine Quantity: ";
    cin >> Medicine.qty;

    while (true)
    {
        cout << "Enter price of the medicine per unit: ";
        if (cin >> Medicine.price)
        {
            break;
        }
        else
        {
            cout << "Enter a valid numeric value for the price!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    ofp.write((char *)&Medicine, sizeof(MedicineData));
    ofp.close();
    cout << "Record Added!" << endl;
}

void Medicine ::modifydetails()
{
    fstream file;
    file.open("medicine.dat", ios ::binary | ios ::in | ios ::out);

    if (!file)
    {
        cout << "Unable to open file" << endl;
        return;
    }

    file.seekg(0, ios ::beg);

    MedicineData Medicine;
    char name[30];
    bool found = false;

    cout << "Enter the name of the medicine you want to modify: ";
    cin >> name;

    while (file.read((char *)&Medicine, sizeof(MedicineData)))
    {
        if (strcmp(Medicine.medicine_name, name) == 0)
        {
            int position = (-1) * sizeof(MedicineData);
            file.seekp(position, ios ::cur);
            cout << "Enter new Medicine Name: ";
            cin >> Medicine.medicine_name;
            cout << "Enter new Medicine's Company: ";
            cin >> Medicine.company;
            cout << "Enter new Quantity: ";
            cin >> Medicine.qty;
            cout << "Enter new price: ";
            cin >> Medicine.price;

            file.write((char *)&Medicine, sizeof(MedicineData));
            found = true;
        }
    }
    file.close();

    if (found)
    {
        cout << "Record Updated!" << endl;
    }
    else
    {
        cout << "Medicine not found!" << endl;
    }
    cin.get();
    cin.get();
}

void Medicine ::deletedetails()
{
    fstream file, temp;
    file.open("medicine.dat", ios::in | ios::binary);
    temp.open("temp.dat", ios::out | ios::binary);

    if (!file || !temp)
    {
        cout << "Unable to open file" << endl;
        cin.get();
        cin.get();
        return;
    }

    MedicineData Medicine;
    string name;
    bool found = false;

    cout << "Enter the name of the medicine you want to delete: ";
    cin.ignore();
    getline(cin, name);

    while (file.read((char *)&Medicine, sizeof(MedicineData)))
    {
        if (Medicine.medicine_name != name)
        {
            temp.write((char *)&Medicine, sizeof(MedicineData));
        }
        else
        {
            found = true;
        }
    }

    file.close();
    temp.close();

    if (found)
    {
        remove("medicine.dat");
        rename("temp.dat", "medicine.dat");
        cout << "Medicine deleted successfully." << endl;
    }
    else
    {
        cout << "Medicine not found." << endl;
    }

    cin.ignore();
    cin.get();
    return;
}

void Medicine ::searchdetails()
{
    fstream file;
    file.open("medicine.dat", ios ::in | ios ::binary);

    if (!file)
    {
        cout << "Unable to open file";
        cin.get();
        cin.get();
        return;
    }

    MedicineData Medicine;
    char name[30];
    bool found = false;
    cout << "Enter name of the medicine's company you want to Search: ";
    cin >> name;

    file.seekg(0, ios::beg);
    while (file.read((char *)&Medicine, sizeof(MedicineData)))
    {
        if (strcmp(Medicine.company, name) == 0)
        {
            cout << "Medicine Name: " << Medicine.medicine_name << endl;
            cout << "Medicine Company:" << Medicine.company << endl;
            cout << "Medicine Quantity: " << Medicine.qty << endl;
            cout << "Medicine Price per unit: " << Medicine.price << endl
                 << "\n";
            cout << "Compositions in the medicine:" << endl;
            for (int i = 0; i < Medicine.compositionCount; i++)
            {
                cout << "Composition " << i + 1 << ": " << Medicine.compositions[i] << endl;
            }
            found = true;
        }
    }
    file.close();
    if (!found)
    {
        cout << "Medicine not found" << endl;
    }
    cin.get();
    cin.get();
    return;
}

void Medicine ::alldetails()
{
    fstream file;
    file.open("medicine.dat", ios ::binary | ios ::in);

    MedicineData Medicine;
    int choice = 1;
    file.seekg(0, ios::beg);
    while (file.read((char *)&Medicine, sizeof(MedicineData)) && choice)
    {
        cout << "Medicine Name: " << Medicine.medicine_name << endl;
        cout << "Medicine Company:" << Medicine.company << endl;
        cout << "Medicine Quantity: " << Medicine.qty << endl;
        cout << "Medicine Price per unit: " << Medicine.price << endl;
        cout << "Compositions in the medicine:" << endl;
        for (int i = 0; i < Medicine.compositionCount; i++)
        {
            cout << "Composition " << i + 1 << ": " << Medicine.compositions[i] << endl;
        }

        cout << "Press 1 to view the next medicine else press 0: " << endl;
        cin >> choice;
    }
    cin.get();
    cin.get();
    return;
}

int main()
{
    Medicine med;
    int choice;
    do
    {
        cout << "\n===== Medicine Management System =====" << endl;
        cout << "What would you like to do?" << endl;
        cout << "1. Add Medicine" << endl;
        cout << "2. Update Medicine" << endl;
        cout << "3. Delete Medicine" << endl;
        cout << "4. Show Medicines" << endl;
        cout << "5. Search Medicine Details" << endl;
        //	cout << "6. Search Compositions" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            med.inputdetails();
            break;
        }
        case 2:
        {
            med.modifydetails();
            break;
        }
        case 3:
        {
            med.deletedetails();
            break;
        }
        case 4:
        {
            med.alldetails();
            break;
        }
        case 5:
        {

            med.searchdetails();
            break;
        }
            /*case 6:
                {
                    med.comp_details();
                    break;
                }*/

        case 6:
        {
            cout << "Exiting program." << endl;
            break;
        }
        default:
        {
            cout << "Invalid choice. Please try again." << endl;
        }
        }
    } while (choice != 6);

    return 0;
}