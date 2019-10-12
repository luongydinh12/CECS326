#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "semaphore.h"

#include <cstdlib>
#include <cstring>
#include <time.h>
#include <ctype.h>
using namespace std;

char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
const int BUFFSIZE = 1536; // 512 x 3 ??? 
enum SemVars
{
    C11,
    C12,
    C13,
    C21,
    C22,
    C23,
    C31,
    C32,
    C33,
    C41,
    C42,
    C43,
    MUTEX
};

void Pfunction(int, SEMAPHORE &);
void Vfunction(int, SEMAPHORE &);
void childProcess(int, SEMAPHORE &, char *, char *, char *, char *);
void parent_cleanup(SEMAPHORE &, int, int, int, int);
char *chooseGroup(int, char *, char *, char *, char *);
char randomCharacter();
int chooseStartIndex(int);
void swap(int, int, char *, char *);



int main()
{
    int shmid1, shmid2, shmid3, shmid4;
    char *shmBUF1, *shmBUF2, *shmBUF3, *shmBUF4;

    // Create semVars and each starts with 1
    SEMAPHORE sem(13);
    sem.V(C11);
    sem.V(C12);
    sem.V(C13);
    sem.V(C21);
    sem.V(C22);
    sem.V(C23);
    sem.V(C31);
    sem.V(C32);
    sem.V(C33);
    sem.V(C41);
    sem.V(C42);
    sem.V(C43);
    sem.V(MUTEX);

    shmid1 = shmget(IPC_PRIVATE, BUFFSIZE * sizeof(char), PERMS);
    shmBUF1 = (char *)shmat(shmid1, 0, SHM_RND);

    shmid2 = shmget(IPC_PRIVATE, BUFFSIZE * sizeof(char), PERMS);
    shmBUF2 = (char *)shmat(shmid2, 0, SHM_RND);

    shmid3 = shmget(IPC_PRIVATE, BUFFSIZE * sizeof(char), PERMS);
    shmBUF3 = (char *)shmat(shmid3, 0, SHM_RND);

    shmid4 = shmget(IPC_PRIVATE, BUFFSIZE * sizeof(char), PERMS);
    shmBUF4 = (char *)shmat(shmid4, 0, SHM_RND);

    srand(time(NULL));

    // ******* Fill shmBUF1 with random lower case letter ******* 
    for (int j = 0; j < BUFFSIZE; j++)
        shmBUF1[j] = tolower(randomCharacter());

    // *******  Fill shmBUF2, shmBUF3, shmBUF4 with random upper case letter ******* 
    for (int j = 0; j < BUFFSIZE; j++)
        shmBUF2[j] = randomCharacter();
    for (int j = 0; j < BUFFSIZE; j++)
        shmBUF3[j] = randomCharacter();
    for (int j = 0; j < BUFFSIZE; j++)
        shmBUF4[j] = randomCharacter();       

    // Input for looping condition:
    int counter = 0;
    cout << "Number of operations for each process: ";
    cin >> counter;
    cout << endl;

    // Create processes
    if (fork()) // Parent (process 1)
    {
        if (fork()) // Child 1 (process 2)
        { 
            if (fork()) // Child 2 (process 3)
            { 
                if (fork()) //Child 3 (process 4)
                { 
                    childProcess(counter, sem, shmBUF1, shmBUF2, shmBUF3, shmBUF4);
                    wait(0); // wait for Child 4
                    exit(0);
                }
                else //Child 4 (process 5)
                { 
                    childProcess(counter, sem, shmBUF1, shmBUF2, shmBUF3, shmBUF4);
                    exit(0);
                }
                childProcess(counter, sem, shmBUF1, shmBUF2, shmBUF3, shmBUF4);
                wait(0); // wait for Child 3
                exit(0);
            }
            childProcess(counter, sem, shmBUF1, shmBUF2, shmBUF3, shmBUF4);
            wait(0); // wait for Child 2
            exit(0);
        }
        childProcess(counter, sem, shmBUF1, shmBUF2, shmBUF3, shmBUF4);
        
        // ******* Print out  4 Char* to verify the swapping ******* 
        cout << "Group 1: " << endl;
        cout << shmBUF1 << endl;
        cout << "Group 2: " << endl;
        cout << shmBUF2 << endl;
        cout << "Group 3: " << endl;
        cout << shmBUF3 << endl;
        cout << "Group 4: " << endl;
        cout << shmBUF4 << endl;

        parent_cleanup(sem, shmid1, shmid2, shmid3, shmid4); // wait and clean up once done
    }



    exit(0);
} // END MAIN

void childProcess(int counter, SEMAPHORE &sem, char *shmBUF1, char *shmBUF2, char *shmBUF3, char *shmBUF4)
{
    for (int i = 0; i < counter; i++) // number of swaps for each process
    {
        srand(time(NULL)); 
        int speed_check = rand();
        while (speed_check >= 5000) // Slow down each process
        {
            speed_check = rand();
        }

        int num1 = rand() % 4 + 1; // Choose 1 random group
        int num2 = rand() % 4 + 1; // Choose 1 random group
        int num3 = rand() % 3 + 1; // Choose 1 random chunk
        int num4 = rand() % 3 + 1; // Choose 1 random chunk

        int chunk1 = stoi(std::to_string(num1) + std::to_string(num3)); // Chunk number1
        int chunk2 = stoi(std::to_string(num2) + std::to_string(num4)); // Chunk number2

        char *shA = chooseGroup(num1, shmBUF1, shmBUF2, shmBUF3, shmBUF4);
        char *shB = chooseGroup(num2, shmBUF1, shmBUF2, shmBUF3, shmBUF4);

        sem.P(MUTEX);      // Make sure both P done before other process can take over. Prevent deadlock
        Pfunction(chunk1, sem); // Lock the chunk
        Pfunction(chunk2, sem); // Lock the chunk
        sem.V(MUTEX);

        swap(num2, num4, shA, shB); // Swap 2 chunks

        Vfunction(chunk1, sem);            // Release the chunk
        Vfunction(chunk2, sem);            // Release the chunk
    }
}

void swap(int chunkA, int chunkB, char *shmBUFa, char *shmBUFb) // *******  Swap 2 chunks ******* 
{
    int indexA = chooseStartIndex(chunkA);
    int indexB = chooseStartIndex(chunkB); 
    
    char temp[512];

    int indexAtemp = indexA;
    for (int k=0;k<512; k++)
    {
        temp[k] = shmBUFa[indexAtemp];
        indexAtemp++;
    }

    int indexBtemp = indexB;
    for (int q = 0; q <512; q++){
        shmBUFa[indexA] = shmBUFb[indexBtemp];
        indexA++;
        indexBtemp++;
    }

    for (int w = 0; w <512; w++){
        shmBUFb[indexB] = temp[w];
        indexB++;
    }
} //end swap

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

char randomCharacter()
{   
    int randomIndex = rand() % 26;
    return alphabet[randomIndex];
} // Function to generate and return a random character

char *chooseGroup(int randomNumber, char *shmBUF1, char *shmBUF2, char *shmBUF3, char *shmBUF4)
{
    char *buf;
    switch (randomNumber)
    {
    case 1:
        buf = shmBUF1;
        break;
    case 2:
        buf = shmBUF2;
        break;
    case 3:
        buf = shmBUF3;
        break;
    case 4:
        buf = shmBUF4;
        break;
    } // end switch

    return (buf);
} // end chooseGroup

void Pfunction(int caseNumber, SEMAPHORE &sem)
{
    switch (caseNumber)
    {
    case 11:
        sem.P(C11);
        break;
    case 12:
        sem.P(C12);
        break;
    case 13:
        sem.P(C13);
        break;
    case 21:
        sem.P(C21);
        break;
    case 22:
        sem.P(C22);
        break;
    case 23:
        sem.P(C23);
        break;
    case 31:
        sem.P(C31);
        break;
    case 32:
        sem.P(C32);
        break;
    case 33:
        sem.P(C33);
        break;
    case 41:
        sem.P(C41);
        break;
    case 42:
        sem.P(C42);
        break;
    case 43:
        sem.P(C43);
        break;
    }
}
void Vfunction(int caseNumber, SEMAPHORE &sem)
{
    switch (caseNumber)
    {
    case 11:
        sem.V(C11);
        break;
    case 12:
        sem.V(C12);
        break;
    case 13:
        sem.V(C13);
        break;
    case 21:
        sem.V(C21);
        break;
    case 22:
        sem.V(C22);
        break;
    case 23:
        sem.V(C23);
        break;
    case 31:
        sem.V(C31);
        break;
    case 32:
        sem.V(C32);
        break;
    case 33:
        sem.V(C33);
        break;
    case 41:
        sem.V(C41);
        break;
    case 42:
        sem.V(C42);
        break;
    case 43:
        sem.V(C43);
        break;
    }
}

void parent_cleanup(SEMAPHORE &sem, int shmid1, int shmid2, int shmid3, int shmid4)
{
    int status;
    wait(0);
    shmctl(shmid1, IPC_RMID, NULL);
    shmctl(shmid2, IPC_RMID, NULL);
    shmctl(shmid3, IPC_RMID, NULL);
    shmctl(shmid4, IPC_RMID, NULL);
    sem.remove();
} // parent_cleanup
