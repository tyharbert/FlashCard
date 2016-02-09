#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

// globals
std::vector<std::string> questions;
std::vector<std::string> answers;
std::vector<int> unanswered;
std::vector<int> missed;
int correct;

// function prototypes
void readFile(std::string);
void runPratice();
bool checkInput(int);
void printQuestion(int);
int getQuestionNum();

int main () {
    
    // seed random number generator
    srand (time(NULL));
    
    // runs the pratice loop
    runPratice();
    
    return 0;
}

// reads questions and answers
// these are separated line by line
// question followed by answer
void readFile(){
    std::ifstream f;
    std::string line, file;
    int itr = 0;
    
    // read file using user input
    do {
        std::cout << "Enter '.txt' file name:\n";
        std::getline(std::cin, file);
        f.open("../input/" + file + ".txt");
    } while(!f.is_open());
    std::cout << std::endl;

    while (std::getline(f,line)){
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        if (itr%2 == 0)
            questions.push_back(line);
        else
            answers.push_back(line);
    
        itr++;
    }
    
    if (questions.size() != answers.size())
        throw std::runtime_error("there needs to be the same number of questions and answers. (check for blank line at the end of the file)");
    
    f.close();
}

// this is an open loop going
// through each question
void runPratice(){
    
    // read the file
    readFile();
    
    // infinte loop
    while(true){
        // get question number
        int questionNum = getQuestionNum();
    
        // print the question
        printQuestion(questionNum);
    
        // check the users answer
        while(!checkInput(questionNum)) {}
    }
}

//  help (shows commands)
//  quit
//  repeat (repeats the question)
//  show (reveal the answer)
//  (type a guess)
bool checkInput(int questionNum){
    std::string input;
    
    std::getline(std::cin, input);
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    
    if (input == "quit")
        std::exit(0);
    else if (input == "help")
        std::cout << "'quit' to terminate the program\n'show' to reveal the answer\n'repeat' will repeat the question\ntake a guess at the answer\n\n";
    else if (input == "repeat")
        printQuestion(questionNum);
    else if (input == "show") {
        if (missed.empty() || (missed.back() != questionNum))
            missed.push_back(questionNum);
        std::cout << answers[questionNum] << std::endl << std::endl;
        return true;
    }
    else {
        if (answers[questionNum] == input){
            if (!missed.empty() && (missed.back() == questionNum))
                missed.pop_back();
            correct++;
            std::cout << "got it!\n\n";
            return true;
        } else {
            if (missed.empty() || (missed.back() != questionNum))
                missed.push_back(questionNum);
            std::cout << "try again.\n";
        }
    }
    
    return false;
}

// prints the question
void printQuestion(int questionNum){
    std::cout << "Correct: " << correct << " Missed: " << missed.size() << std::endl << questions[questionNum] << std::endl;
}

// gets the location of a random question that hasn't
// been answered yet. Once all have been answered it
// becomes random again.
int getQuestionNum(){    
    // add all questions back to unanswered list
    if (unanswered.empty()){
        correct = 0;
        
        if (missed.empty()){
            for (int i = 0; i < questions.size(); i++)
                unanswered.push_back(i);
            std::cout << "Starting " << unanswered.size() << " questions!\n\n";
        } else {
            for (int i = 0; i < missed.size(); i++)
                unanswered.push_back(missed[i]);
            missed.clear();
            std::cout << "Starting " << unanswered.size() << " missed questions!\n\n";
        }
    }
    
    // get one of the elements
    int i = rand()%unanswered.size();
    
    // get the elements value
    int val = unanswered[i];
    
    // remove the element
    unanswered.erase(unanswered.begin()+i);
    
    // return the value
    return val;
}