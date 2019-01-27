#include <iostream>

using namespace std;
struct lab1
{   
    int n = 2700;
    char *ch =  new char[20]; 
    int *in = new int [20];
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
    n = 2*recursive(n);
    return n;
}
