// Example program
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h> /* time */
char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
const int BUFFSIZE = 1536;

char randomCharacter()
{

    int randomIndex = rand() % 26;
    return alphabet[randomIndex];
} // Function to generate and return a random character
int chooseStartIndex(int chunk){
    if(chunk == 1){
        return 0;
    }else if (chunk == 2){
        return 512;
    }else if (chunk == 3){
        return 1024;
    }
    return 0;
}

void swap(int chunkA, int chunkB, char *shmBUFa, char *shmBUFb) // *******  Swap 2 chunks *******
{
    int indexA = chooseStartIndex(chunkA);
    int indexB = chooseStartIndex(chunkB);

    char temp[512];

    int indexAtemp = indexA;
    for (int k = 0; k < 512; k++)
    {
        temp[k] = shmBUFa[indexAtemp];
        indexAtemp++;
    }

    int indexBtemp = indexB;
    for (int q = 0; q < 512; q++)
    {
        shmBUFa[indexA] = shmBUFb[indexBtemp];
        indexA++;
        indexBtemp++;
    }

    for (int w = 0; w < 512; w++)
    {
        shmBUFb[indexB] = temp[w];
        indexB++;
    }
    
} //end swap



int main()
{

    /*
    srand(time(NULL));
    int num1 = rand() % 4 + 1;
    int num2 = rand() % 4 + 1;
    int num3 = rand() % 3 + 1;
    int num4 = rand() % 3 + 1;

    std::cout << num1 << std::endl;
    std::cout << num2 << std::endl;
    std::cout << num3 << std::endl;
    std::cout << num4 << std::endl;

    int caseNumber = stoi(std::to_string(num1) + std::to_string(num3));
    int caseNumber2 = stoi(std::to_string(num2) + std::to_string(num4));
    std::cout << caseNumber << std::endl;
    switch (caseNumber)
    {
    case 11:
        std::cout << "Case 11 ";
        break;
    case 12:
        std::cout << "Case 12 ";
        break;
    case 13:
        std::cout << "Case 13 ";
        break;
    case 21:
        std::cout << "Case 21 ";
        break;
    case 22:
        std::cout << "Case 22 ";
        break;
    case 23:
        std::cout << "Case 23 ";
        break;
    case 31:
        std::cout << "Case 31 ";
        break;
    case 32:
        std::cout << "Case 32 ";
        break;
    case 33:
        std::cout << "Case 33 ";
        break;
    case 41:
        std::cout << "Case 41 ";
        break;

    case 42:
        std::cout << "Case 42 ";
        break;
    case 43:
        std::cout << "Case 43 ";
        break;
    }*/
    srand(time(NULL));
    char *shmBUF1 = new char[BUFFSIZE];
    char *shmBUF2 = new char[BUFFSIZE];
    char *shmBUF3 = new char[BUFFSIZE];
    char *shmBUF4 = new char[BUFFSIZE];

    // ******* Fill shmBUF1 with random lower case letter *******
    for (int j = 0; j < BUFFSIZE; j++)
    {
        shmBUF1[j] = tolower(randomCharacter());
    }

    // *******  Fill shmBUF2, shmBUF3, shmBUF4 with random upper case letter *******
    for (int j = 0; j < BUFFSIZE; j++)
        shmBUF2[j] = randomCharacter();
    for (int j = 0; j < BUFFSIZE; j++)
        shmBUF3[j] = randomCharacter();
    for (int j = 0; j < BUFFSIZE; j++)
        shmBUF4[j] = randomCharacter();


    
    std::cout << shmBUF1 << std::endl;
    std::cout << "___________________" << std::endl;
    std::cout << shmBUF2 << std::endl;
    std::cout << "___________________" << std::endl;

    std::cout << "SWAP STARTED" << std::endl;
    swap(2, 1, shmBUF1, shmBUF2);
    std::cout << "SWAP ENDED" << std::endl;

    std::cout << "___________________" << std::endl;
    std::cout << shmBUF1 << std::endl;
    std::cout << "___________________" << std::endl;
    std::cout << shmBUF2 << std::endl;


    std::cout << "SWAP STARTED" << std::endl;
    swap(2, 1, shmBUF1, shmBUF2);
    std::cout << "SWAP ENDED" << std::endl;

    std::cout << "___________________" << std::endl;
    std::cout << shmBUF1 << std::endl;
    std::cout << "___________________" << std::endl;
    std::cout << shmBUF2 << std::endl;
}
