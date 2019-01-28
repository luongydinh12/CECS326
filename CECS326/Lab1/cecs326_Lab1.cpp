
// Dinh Luong
// cecs326_Lab1.cpp
// Description:


#include <iostream>

using namespace std;
char alphabet[26] = { 'A' , 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

struct myArray
{   
    char *ch[20]; 
    int *in[20];
};


int main() {

    return 0;
}

void menu(){
    cout << "Main Menu: \n";
    cout << "(1) Access a pointer \n";
    cout << "(2) List deallocated memory (index) \n";
    cout << "(3) Deallocate all memory\n";
    cout << "(4) Exit program\n";

}
void submenu(){
    cout << "Sub Menu: \n";
}

int recursive(int n) {
    if (n == 0)
        return 2700;
    else
        return 2*recursive(n-1);
    return n;
} //  Recursive Function: f(0)=2700 & f(n+1)=2*f(n), Generate indexes of integer array

char randomCharacter(){
    int randomIndex = rand()%26;
    return alphabet[randomIndex] ;
} // Function to generate and return a random character
