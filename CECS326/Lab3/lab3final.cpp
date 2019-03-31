#include <unistd.h>
#include <iostream>
#include <cstdlib>

#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(){
    // Variables: 
    long childPID; 
    string article, target, replacement; 

    // Keep the program going until the user want to exit
    while(true){
        article = "Through the five dimensions interviews and analysis diagram, our group has learned multiple advantages and disadvantages of the Kindle devices and its system. In the Individual Dimension's interview, the interviewee has been using multiple generations of Kindle for over the past 7 years. Kindle is the main device that he brings with him to work, school and even on vacations. He uses Kindle to read books and sometimes to store his documents on the device. Throughout the interview, the biggest selling point for Kindle that he mentioned is the convenience of it. The device can last for weeks on a single charge. The reader can pick up where he or she left off from the previous reading because the Kindle will always save the last  page of every book that you read. The device can hold almost all the reading materials for the user. The interviewee said that because of convenience, he is more likely to carry a Kindle with him all the time rather than a physical book. Imagine you are going to bring a couple of books with you on vacation or a trip; travel with all these weights isn't fun, which in turn, make you less likely to read. This example fits perfectly in the student's textbook problem. Specifically, an average student in high school carries several textbooks with them every week; typically, one textbook per class. Each textbook normally weighs around 3 to 6 pounds. If a student is taking 5 to 6 classes in a semester, that means 15 to 36 pounds of papers the student needs to carry to class every week. Generally, a minor effect of carrying heavy backpacks is energy deprivation, which could result in low performance in class and other activities. A more serious concern is chronic back pain or other permanent damages done to the nerves in the neck and shoulders. All the problems and concerns mentioned above can be solved by implementing Kindle in the school system";
        
        // Output original article
        cout << "Original article: " << article << endl << endl; 
        // Ask user for target string or whether the user want to exit
        cout << "Enter a target string or <!wq> to exit: ";
        cin  >> target;

        // If the user enters <!wq>, the program exits
        if (target.compare("!wq") == 0){
            cout << "Program exits..." << endl;
            exit(0);
        }
        // Ask user for a replacement string
        cout << "Enter a replacement: ";
        cin >> replacement;

        // Fork the program , child process will do replacement work 
        // while the parent will wait
        childPID = fork();

        if (childPID >0){ //If the process is parent -> wait()
            wait(0); 
        }
        else if (childPID == 0){ //If the process is child -> do replacement
            cout << "\nChild Process: pid " << getpid() << endl;
            int counter = 0; // counter to count the number of replacements
            
            // Scenario 1: Child replaces the target string that exists and exits out of the loop
            // Scenario 2: Child replaces the target string but fails, child will redo the process
            while (counter == 0){
                // print out "." to indicate the child process is working on the replacement
                cout << "." <<endl; 

                //Find the current position of the target
                size_t  current = article.find(target, 0);

                //Replace the targets with the replacement
                while ( current != string::npos){
                    article.replace( current , target.length(), replacement);
                    current= article.find(target, current+1); // Find next target
                    counter++; // keep track of number of replacements
                }
            }

            cout << "After replacement: "<< article <<endl<<endl;
            cout << "Number of replacements: " << counter <<endl<<endl;
            exit(0);
        }
    }
    exit(0);
}