// Dinh Luong
// cecs326_Lab1.cpp
// Description: This program demonstrates allocation and deallocation of memory 
// Visual Studio Code 

#include <iostream>

using namespace std;

char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char randomCharacter(){
    int randomIndex = rand()%26;
    return alphabet[randomIndex];
} // Function to generate and return a random character

int recursive(int n) {
    if (n == 0)
        return 2700;
    else
        return (2*recursive(n-1));
} //  Recursive Function: f(0)=2700 & f(n+1)=2*f(n)

struct myArray
{   
    char *charPtr[20];  // array of 20 pointers to char
    int intArray[20]; // integer array with 20 elements
}; // Single Struct 

void initializeStruct (struct myArray &array){
    for (int i=0; i<20; i++)
        array.intArray[i] = recursive(i); 
    
    for (int i=0; i<20; i++){
        array.charPtr[i] = new char[array.intArray[i]];
        for (int j=0; j<array.intArray[i]; j++)
            array.charPtr[i][j] = randomCharacter();
    }
} // Initialize data for Struct 

void menu(){
    cout << endl;
    cout << "-- Main Menu --\n";
    cout << "(1) Access a pointer \n";
    cout << "(2) List deallocated memory (index) \n";
    cout << "(3) Deallocate all memory\n";
    cout << "(4) Exit program\n";
} // Main Menu

void subMenu(){
    cout << endl;
    cout << "-- Sub Menu --\n";
    cout << "(1) Print the first 10 char's in the chosen array \n";
    cout << "(2) Delete all the char's associated with this pointer \n";
    cout << "(3) Return to Main Menu \n";
} // Sub Menu for option 1

int main() {
    myArray array; // Create struct 
    initializeStruct(array); // Initialize struct
    menu();
    int choice = 0; // variable to store user's choice for navigate through the Menu
    cin >> choice;
    int index = 0; //variable to store user's choice of index
    while (choice !=4){
        switch(choice){
            case 1: {
                cout << "Index of the array you want to manipulate is: ";
                cin >> index;
                subMenu();
                int subChoice = 0;
                cin >> subChoice;
                while (subChoice !=3 ){
                    switch(subChoice){
                        case 1:{
                            if(array.charPtr[index] != NULL){
                                for (int i=0; i <10; i++)
                                    cout << array.charPtr[index][i] << "  "; 
                            } // If memory exists, print character(s)
                            else{
                                cout << "The index does not exist. Program will re-allocate memory and re-initialize chars \n";
                                array.charPtr[index] = new char [array.intArray[index]];
                                for (int i=0; i < array.intArray[index]; i++)
                                    array.charPtr[index][i]= randomCharacter();
                            } // If memory has been deleted, reallocate and reinitialize
                            break;} // End of case 1.1
                        case 2: {
                            delete array.charPtr[index];
                            array.charPtr[index] = NULL;
                            cout << "Delete Successfully!";
                            break;} // End of case 1.2
                    }
                    subMenu();
                    cin >> subChoice;
                }
                break;}// End of case 1

            case 2: {
                cout << "Index(es) of deallocated memory is/are: \n";
                int flag = 0;
                for (int i=0; i<20; i++){
                    if(array.charPtr[i] == NULL){
                        cout << i << " ";
                        flag = 1;
                    }
                }
                if (flag == 0)
                    cout << "None";
                break; }// Print out index(es) of deallocated memory // End of case 2

            case 3:{
                for (int i=0; i <20; i++){
                    delete array.charPtr[i];
                    array.charPtr[i] = NULL;
                }
                break;} // Deallocate all memory and set all point to NULL // End of case 3
        }
        menu();
        cin >> choice;        
    }
    //ON EXIT: deallocate all memory (even though the OS will automatically do it)
    for (int i=0; i <20; i++){
        delete array.charPtr[i];
        array.charPtr[i] = NULL;
    }
    return 0;
}
