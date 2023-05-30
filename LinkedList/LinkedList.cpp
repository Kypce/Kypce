/** LINKED LIST INFORMATION
 * Space Complexity: O(1) as no extra space is required for any operation
 * Time Complexity . . .
 *      Insert: O(N) (though this linked list always inserta at the head so it is always O(1))
 *      Delete: O(N)
 *      Access: O(N)
 *      Search: O(N)
 * 
 * This is only a forwardly linked list (no back links)
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Contains information on person's social security number, birth date (YYYYMMDD), first name, last name, and zip code
struct person {
    int ssn, bdate;
    string fname, lname;
    int zip;

    person(int s, int bd, string fn, string ln, int z) {
        ssn = s;
        bdate = bd;
        fname = fn;
        lname = ln;
        zip = z;
    }

    // Generic print function to print raw data of "person"
    void printPerson() {
        cout << ssn << " " << bdate << " " << fname << " " << lname << " " << zip << "\n";
    }

    // Detailed print function that gives labels with the data of the "person"
    void printPersonDetailed() {
        cout << "SSN: " << ssn << "\nBirth Date: " << bdate << "\nFirst Name: " << fname << "\nLast Name: " << lname 
            << "\nZip Code: " << zip << "\n";
    }
};

class List {
    protected:
        // The node containing the pointer to the next node and the data object
        struct node {
            person *data;
            node *next;

            node(person *d, node *n) {
                data = d;
                next = n;
            }
        };

        node *first;

    public:
        List() {
            first = NULL;
        }

        // Adds new node to the front of the linked list
        void addNode(person *p) {
            // The current first node is set to the new nodes next data
                // Before: first -> null
                // After: first -> old first -> null
            first = new node(p, first);
        }

        // Finds any person with given name (either first or last name)
        void findByName(string name) {
            node *ptr = first;

            while(ptr != NULL) {
                if(name == ptr->data->fname || name == ptr->data->lname) {
                    ptr->data->printPersonDetailed();
                    printf("\n");
                }
                ptr = ptr->next;
            }
        }

        void findByName(string fname, string lname) {
            node *ptr = first;

            while(ptr != NULL) {
                if(fname == ptr->data->fname) {
                    if(lname == ptr->data->lname) {
                        ptr->data->printPersonDetailed();
                        printf("\n");
                    }
                }
                ptr = ptr->next;
            }
        }

        // Finds any person with given zip code
        void findByZip(int zp) {
            node *ptr = first;

            while(ptr != NULL) {
                if(zp == ptr->data->zip) {
                    ptr->data->printPersonDetailed();
                    printf("\n");
                }
                ptr = ptr->next;
            }
        }

        // Finds oldest person in list
        void findOldest() {
            node *ptr = first;
            node *old = first;

            while(ptr != NULL) {
                if(ptr->data->bdate < old->data->bdate)
                    old = ptr;
                ptr = ptr->next;
            }

            old->data->printPersonDetailed();
            printf("\n");
        }

        // Runs through entire linked list printing all nodes' data
        void printAll() {
            node *ptr = first;

            while(ptr != NULL) {
                ptr->data->printPerson();
                ptr = ptr->next;
            }
        }

        void deletePerson(string fname, string lname) {
            node *ptr = first;
            node *prev;
            int s;
            
            // Prints all people with given first name and last name
            findByName(fname, lname);

            printf("Please type the SSN value for the person you would like to delete: ");
            cin >> s;

            while(ptr != NULL) {
                if(s == ptr->data->ssn) {
                    // Deletion if node is the head of the list
                    if(ptr == first) {
                        first = ptr->next;
                        delete(ptr);
                    // Deletion if node is at the end of the list
                    } else if(ptr->next == NULL) {
                        prev->next = NULL;
                        delete(ptr);
                    // Deletion if node is in the middle of the list
                    } else {
                        prev->next = ptr->next;
                        delete(ptr);
                    }

                    break;
                }

                prev = ptr;
                ptr = ptr->next;
            }

            printf("\n");
        }
};

// Takes an input file and will read and input contents into linked list
void readToList(string file, List &L) {
    ifstream fin;
    string line;
    fin.open(file);

    if(fin.fail()) {
        printf("Error opening file \"%s\"", file);
        exit(1);
    }

    while(!fin.eof()) {
        int tmp_ssn, tmp_bdate;
        string tmp_fname, tmp_lname;
        int tmp_zip;

        if(fin.fail())
            break;

        fin >> tmp_ssn >> tmp_bdate >> tmp_fname >> tmp_lname >> tmp_zip;

        person *p = new person(tmp_ssn, tmp_bdate, tmp_fname, tmp_lname, tmp_zip);

        //p->printPerson();

        L.addNode(p);
    }
}

int main() {
    List LL;
    string fileName = "People.txt";
    
    int choice = -1;
    int numInput;
    char charInput;
    string stringInput;
    string stringInput2;

    int tmp_ssn, tmp_bdate;
    string tmp_fname, tmp_lname;
    int tmp_zip;
    person *tmp;

    readToList(fileName, LL);

    printf("Welcome to this interactive employee finder service\n\n");

    while(choice != 0) {
        printf("Please type the number value of one of the following commands . . .\n");
        printf("1: Find by name\n");
        printf("2: Find by zip code\n");
        printf("3: Find the oldest\n");
        printf("4: Print all\n");
        printf("5: Add a user\n");
        printf("6: Delete user\n");
        printf("0: Exit\n");

        cin >> choice;

        switch(choice) {
            // Search by name
            case 1:
                printf("You will be prompted for a first name and then a last name.\n");
                printf("If you only know one of the two names, please only type for first name. . .\n");
                
                printf("Enter first name: ");
                cin >> stringInput;

                printf("If you only have one name to give, please type the following: ZZZZZ\n");
                printf("Enter last name: ");
                cin >> stringInput2;

                if(stringInput2 == "ZZZZZ") {
                    cout << "\nSearching for all people with name containing \"" << stringInput << "\". . .\n\n";
                    LL.findByName(stringInput);
                } else {
                    cout << "\nSearching for all people with name \"" << stringInput << " " << stringInput2 << "\". . .\n\n";
                    LL.findByName(stringInput, stringInput2);
                }

                break;

            // Search by zip code
            case 2:
                cin >> numInput;
                cout << "\nSearching for all people with zip code \"" << numInput << "\". . .\n\n";

                LL.findByZip(numInput);

                break;

            // Find the oldest
            case 3:
                cout << "\nFinding the oldest person in the linked list. . .\n\n";

                LL.findOldest();

                break;

            // Print all persons
            case 4:
                LL.printAll();

                break;

            // Adding a person
            case 5:
                printf("Please type the person's 9 digit SSN number: ");
                cin >> tmp_ssn;
                printf("Please type the person's birth date (format = YYYYMMDD): ");
                cin >> tmp_bdate;
                printf("Please type the person's first name: ");
                cin >> tmp_fname;
                printf("Please type the person's last name: ");
                cin >> tmp_lname;
                printf("Please type the person's 5 digit zip code: ");
                cin >> tmp_zip;

                tmp = new person(tmp_ssn, tmp_bdate, tmp_fname, tmp_lname, tmp_zip);
                LL.addNode(tmp);

                printf("\n");
                break;

            // Deletes given person
            case 6:
                printf("To delete, please enter the person's first name and last name when prompted. . .\n");
                printf("First Name: ");
                cin >> stringInput;

                printf("Last Name: ");
                cin >> stringInput2;

                cout << "\nAre you sure you want to delete the person \"" << stringInput << " " << stringInput2 << "\"?\n";
                printf("Type Y for yes or N for no\n");
                cin >> charInput;

                if(charInput == 'Y') {
                    cout << "Attempting to delete \"" << stringInput << " " << stringInput2 << "\". . .\n\n";
                    LL.deletePerson(stringInput, stringInput2);
                } else
                    cout << "Action aborted\n";

                break;

            // Exit
            case 0:
                printf("Thank you for using this service :D\n");
                break;
            
            default:
                printf("Invalid entry given, please try again!\n");
                break;
        }
    }

    return 0;
}
