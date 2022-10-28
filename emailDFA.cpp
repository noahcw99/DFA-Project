#include <iostream>
#include <string>
using namespace std;

//Coded by Noah Welsh
//UCID: XXXXXX
//
//Comments available throughout to easily follow
//
//
//Program to build DFA that tests for a valid email
//Valid Emails are defined as:
//          ((Γ*)Δ(Γ*)*) Ø ((Γ*)Δ(Γ*)*) ('o' || 'c') ('r' || 'o') ('g' || 'm')
//
//Where Γ is any letter from 'a-z' or number from '0-9', Δ is '.', Ø is '@',
//          * notates infinite of that thing can be used,
//          || notates an option between multiple things
//
//Images for visual representation DFA attatched on github
//
//Examples of valid emails:
//          foo.bar99@fun.com, this5.will4.work3.even2@like1.this0.org, 
//          555555555555this@too9999999999999999.com
//
//Examples of invalid emails:
//          this..wont@work.org, sad@toomany..com, needs.org.or.com@end.ze, 
//          missing.symbol.com, invalid^symbol@here.com



int main() {
    cout << "Project 1 for CS341\nSemester: Spring 2022"
         << "\nWritten by: Noah Welsh \nInstructor: Marvin Nakayama, marvin@njit.edu\n\n"
         << "This program builds a deterministic finite automaton (DFA) "
         << "that tests for valid email addresses.\n"
         << "\"Valid\" email addresses are defined in the comments at the top of code.\n\n";
         
    cout << "Do you want to enter a(nother) string? y/n: ";
    string continueString = "y";
    cin >> continueString; //first read for y, n, or invalid user input
    while (continueString == "y") { //while loop continues reading strings as long as y is entered
        string dfaString; //reset string each loop, ask for new one, and initialize
        cout << "Enter a string over Σ: ";
        cin >> dfaString;
        cout << "String Entered: " << dfaString << endl;
        cout << "\nProcessing DFA:\n";

        int index = 0;
        enum allStates { q0, q1, q2, q3, q4, q5, q6, q7, q8, q9 } dfaState = q0; //all DFA states, q9 is trap state
        while (index < dfaString.length()) { //loop until end of string is reached
            if(index == 0) //starting state is always q0
                cout << "Starting State: q" << dfaState << endl;
            switch(dfaState) { //switch case for each char being read in
                case q0: //start state, check for letters
                    if(isalpha(dfaString[index]) || isdigit(dfaString[index]))
                        dfaState = q1;
                    else
                        dfaState = q9; //if checks are not met always set state to trap state
                    break;
                case q1: //check for letters, ., and @
                    if(isalpha(dfaString[index]) || isdigit(dfaString[index]))
                        dfaState = q1;
                    else if(dfaString[index] == '.')
                        dfaState = q2;
                    else if(dfaString[index] == '@')
                        dfaState = q3;
                    else
                        dfaState = q9;
                    break;
                case q2: //check for letters to move back to q1
                    if(isalpha(dfaString[index]) || isdigit(dfaString[index]))
                        dfaState = q1;
                    else
                        dfaState = q9;
                    break;
                case q3: //check for @ to continue (there should only be 1 @ for accepted strings)
                    if(isalpha(dfaString[index]) || isdigit(dfaString[index]))
                        dfaState = q4;
                    else
                        dfaState = q9;
                    break;
                case q4: //loop state if letter, continue if .
                    if(isalpha(dfaString[index]) || isdigit(dfaString[index]))
                        dfaState = q4;
                    else if (dfaString[index] == '.')
                        dfaState = q5;
                    else
                        dfaState = q9;
                    break;
                case q5: //continue if o, else go back to q4
                    if(isalpha(dfaString[index]) && (dfaString[index] == 'o' || dfaString[index] == 'c'))
                        dfaState = q6;
                    else if(isalpha(dfaString[index]) && (dfaString[index] != 'o' || dfaString[index] != 'c'))
                        dfaState = q4;
                    else
                        dfaState = q9;
                    break;
                case q6: //continue if r, else go back to q4 if another letter or q5 if .
                    if(isalpha(dfaString[index]) && (dfaString[index] == 'r' || dfaString[index] == 'o'))
                        dfaState = q7;
                    else if(isalpha(dfaString[index]) && (dfaString[index] != 'r' || dfaString[index] != 'o'))
                        dfaState = q4;
                    else if(dfaString[index] == '.')
                        dfaState = q5;
                    else
                        dfaState = q9;
                    break;
                case q7: //continue if g, else go back to q4 if another letter or q5 if .
                    if(isalpha(dfaString[index]) && (dfaString[index] == 'g' || dfaString[index] == 'm'))
                        dfaState = q8;
                    else if(isalpha(dfaString[index]) && (dfaString[index] != 'g' || dfaString[index] != 'm'))
                        dfaState = q4;
                    else if(dfaString[index] == '.')
                        dfaState = q5;
                    else
                        dfaState = q9;
                    break;
                case q8: //accepting state, loop back to q4 if another letter or q5 if .
                    if(isalpha(dfaString[index]) || isdigit(dfaString[index]))
                        dfaState = q4;
                    else if(dfaString[index] == '.')
                        dfaState = q5;
                    else
                        dfaState = q9;
                    break;
                case q9: //trap state, no checks were hit and string is stuck once here
                    dfaState = q9;
                    break;
            }
            //print char and states each iteration
            if(index == 0)
                cout << "Char: " << dfaString[index] << "\nState: q" << dfaState << endl;
            else if(index == dfaString.length()-1 && index != 0)
                cout << "Char: " << dfaString[index] << "\nFinal State: q" << dfaState << endl;
            else if(index != 0)
                cout << "Char: " << dfaString[index] << "\nState: q" << dfaState << endl;

            index++; //increment index
        }
        if(dfaState == q8) //q8 is accepting state
            cout << "The string was accepted!" << endl;
        else
            cout << "The string was rejected!" << endl;

        cout << "\nDo you want to enter a(nother) string? y/n: "; //check to run another string or not
        cin >> continueString;
    }


    if(continueString == "n") { //terminate program if n is entered
        cout << "Program Terminated";
        return 0;
    } else if(continueString != "n" && continueString != "y") { //if neither y or n is entered, invalid answer
        cout << "Invalid Answer - Program Terminated";
        return 0;
    }

    return 0;
}