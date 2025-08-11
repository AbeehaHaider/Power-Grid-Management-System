#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct district {
    string name;
    string type;
    int num_resident;
    int power;
    bool has_power;
    int num_technician;
    string technicians[100]; // Assuming a maximum of 100 technicians per district
};

// Function to load districts from a file
void load(string fname, district districts[], int &num, int &power) {
    ifstream file(fname);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }
    
    file >> power; // Read total power supply
    file >> num;   // Read number of districts
    file.ignore(); // Ignore the newline after num
    
    for (int i = 0; i < num; ++i) {
        getline(file, districts[i].name); // Read district's name
        getline(file, districts[i].type); // Read district's type
        file >> districts[i].num_resident; // Read number of residents
        file >> districts[i].power;        // Read power consumption
        file >> districts[i].has_power;    // Read power status
        file >> districts[i].num_technician; // Read number of technicians
        file.ignore(); // Ignore newline
        
        // Read technician names
        for (int j = 0; j < districts[i].num_technician; ++j) {
            getline(file, districts[i].technicians[j]);
        }
    }
    
    file.close();
    // Sort the districts based on the number of residents in ascending order
    for (int i = 0; i < num - 1; ++i) {
        for (int j = i + 1; j < num; ++j) {
            if (districts[i].num_resident > districts[j].num_resident) {
                swap(districts[i], districts[j]);
            }
        }
    }
}

// Function to save districts to a file
void save(string fname, district districts[], int num, int power) {
    ofstream file(fname);
    if (!file) {
        cout << "Error opening file for saving!" << endl;
        return;
    }
    
    file << power << endl; // Write total power supply
    file << num << endl;   // Write number of districts
    
    for (int i = 0; i < num; ++i) {
        file << districts[i].name << endl;
        file << districts[i].type << endl;
        file << districts[i].num_resident << endl;
        file << districts[i].power << endl;
        file << districts[i].has_power << endl;
        file << districts[i].num_technician << endl;
        // Write technician names
        for (int j = 0; j < districts[i].num_technician; ++j) {
            file << districts[i].technicians[j] << endl;
        }
    }
    
    file.close();
}

// Function to print all district information
void print_all(district districts[], int num, int power) {
    cout << "The current power supply is " << power << "MW." << endl;
    
    int total_demand = 0;
    
    for (int i = 0; i < num; ++i) {
        cout << districts[i].name << endl;
        cout << "District type: " << districts[i].type << endl;
        cout << "Number of residents: " << districts[i].num_resident << endl;
        if(districts[i].has_power == true){
           cout << "Power use: " << districts[i].power << "MW" << endl;
           total_demand += districts[i].power;
        }
        else{
           cout << "Power use: 0MW" << endl;
        }
        cout << "Has power: " << districts[i].has_power << endl;
            
        if (districts[i].num_technician > 0) {
            cout << "Technicians: ";
            for (int j = 0; j < districts[i].num_technician; ++j) {
                cout << districts[i].technicians[j];
                if (j < districts[i].num_technician - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        cout << "---" << endl;
        
    }
    
    if (power < total_demand) {
        cout << "Critical Error! The current power supply of " << power << "MW is insufficient to supply " << total_demand << "MW of power demand. Please shut off one or more districts." << endl;
        cout << "---" << endl;
    }
    
    
}

// Function to assign a technician to a district
void assign_technician(string tech_name, string district_name, district districts[], int num_district) {
    for (int i = 0; i < num_district; ++i) {
        if (districts[i].name == district_name) {
            districts[i].technicians[districts[i].num_technician] = tech_name;
            districts[i].num_technician++;
            cout << "Technician assigned!" << endl;
            return;
        }
    }
    cout << "Error! The district with that name doesn't exist." << endl;
}

// Function to cut off power to a district
void cut_power(string district_name, district districts[], int num_district) {
    for (int i = 0; i < num_district; ++i) {
        if (districts[i].name == district_name) {
            districts[i].has_power = false;
            cout << "The district's power has been successfully turned off." << endl;
            return;
        }
    }
    cout << "Error! The district with that name doesn't exist." << endl;
}

// Function to restore power to a district
void restore_power(string district_name, district districts[], int num_district) {
    for (int i = 0; i < num_district; ++i) {
        if (districts[i].name == district_name) {
            districts[i].has_power = true;
            cout << "The district's power has been successfully turned back on." << endl;
            return;
        }
    }
    cout << "Error! The district with that name doesn't exist." << endl;
}

int main() {
    district districts[100]; // Assuming a maximum of 100 districts
    int num_district = 0;
    int power = 0;
    
    cout << "Please enter the name of the file to load:" << endl;
    string filename;
    cin >> filename;
    load(filename, districts, num_district, power);
    
    print_all(districts, num_district, power);
    
    while (true) {
        cout << "Main Menu" << endl;
        cout << "1- Status" << endl;
        cout << "2- Set Power Supply" << endl;
        cout << "3- Shutoff Power" << endl;
        cout << "4- Restore Power" << endl;
        cout << "5- Assign Technician" << endl;
        cout << "6- Save" << endl;
        cout << "7- Load" << endl;
        cout << "8- Exit" << endl;
        int option;
        cin >> option;
        cin.ignore(); // To handle newline characters
        
        cout<< "Please enter your choice:" << endl;
        
        if (option == 1) {
            print_all(districts, num_district, power);
        } else if (option == 2) {
            cout << "Enter the updated power supply in megawatts:" << endl;
            cin >> power;
        } else if (option == 3) {
            cout << "Enter the name of the district:" << endl;
            string district_name;
            getline(cin, district_name);
            cut_power(district_name, districts, num_district);
        } else if (option == 4) {
            cout << "Enter the name of the district:" << endl;
            string district_name;
            getline(cin, district_name);
            restore_power(district_name, districts, num_district);
        } else if (option == 5) {
            cout << "Enter the name of the technician:" << endl;
            string tech_name;
            getline(cin, tech_name);
            cout << "Enter the name of the district to assign them to:" << endl;
            string district_name;
            getline(cin, district_name);
            assign_technician(tech_name, district_name, districts, num_district);
        } else if (option == 6) {
            cout << "Enter the file name to save to: ";
            string save_file;
            cin >> save_file;
            save(save_file, districts, num_district, power);
        } else if (option == 7) {
            cout << "Enter the file name to load from: ";
            string load_file;
            cin >> load_file;
            load(load_file, districts, num_district, power);
        } else if (option == 8) {
            break;
        } else {
            cout << "Invalid option!" << endl;
        }
    }
    
    return 0;
}