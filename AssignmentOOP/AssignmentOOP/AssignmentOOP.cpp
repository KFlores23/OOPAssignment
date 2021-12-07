// AssignmentOOP.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

// the structure of the hangman platform
void PrintsMessage(string message, bool printTop = true, bool printBottom = true)
{
    if (printTop)
    {
        cout << "+---------------------------------+" << endl;  //Draws the Base of Hangman
        cout << "|";
    }
    else
    {
        cout << "|";
    }
    bool front = true;
    for (int i = message.length(); i < 33; i++)
    {
        if (front)
        {
            message = " " + message;
        }
        else
        {
            message = message + " ";
        }
        front = !front;
    }
    cout << message.c_str();

    if (printBottom)
    {
        cout << "|" << endl;
        cout << "+---------------------------------+" << endl; // Draw the base of Hangman
    }
    else
    {
        cout << "|" << endl;
    }
}

//-----------------------------------------------------------------------------------------------KYLE FLORES----------------------------------------------------------------------------------------------------------------
// This code of Boolean, has a purpose of recreating the hanged man whenever the user has chosen the incorrect letter.
void DrawsHangman(int guessCount = 0)
{
    if (guessCount >= 1)
        PrintsMessage("|", false, false); // Draws the Rope
    else
        PrintsMessage("", false, false); // Draws the Rope

    if (guessCount >= 2)
        PrintsMessage("|", false, false);// Draws the Rope
    else
        PrintsMessage("", false, false);// Draws the Rope

    if (guessCount >= 3)
        PrintsMessage("O", false, false); // Draws the head
    else
        PrintsMessage("", false, false); // Draws the neck

    if (guessCount == 4)
        PrintsMessage("/  ", false, false); // Draws the left arm

    if (guessCount == 5)
        PrintsMessage("/| ", false, false); // Draws the torso

    if (guessCount >= 6)
        PrintsMessage("/|\\", false, false); // Draws the right arm
    else
        PrintsMessage("", false, false); // Draws the torso

    if (guessCount >= 7)
        PrintsMessage("|", false, false); // Draws the torso
    else
        PrintsMessage("", false, false); // Draws the torso

    if (guessCount == 8)
        PrintsMessage("/", false, false); // Draws the left leg

    if (guessCount >= 9)
        PrintsMessage("/ \\", false, false); // Draws the right leg
    else
        PrintsMessage("", false, false); // Draws the the full figure of the stick man
}
//-----------------------------------------------------------------------------------------------KYLE FLORES----------------------------------------------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------------------------LEONIDS VASILJEVS----------------------------------------------------------------------------------------------------------

 // A new function for letters
void PrintsLetters(string input, char from, char to) // the 'from' input will be responsible for letters that ranges from (A - M)   *Alphabetical order
                                                    // and the 'to' input will be responsible for letters that ranges from (N - Z)
{
    string s; // an empty string
    for (char i = from; i <= to; i++)
    {
        if (input.find(i) == string::npos) // line of code which will contain the current character.
        {                                  // if it doesnt not contain the character and didnt find the letter in the input string
            s += i;                        // then we print it
            s += " ";
        }
        else
            s += "  ";                     // if the letter is already in the input string. this will loop through from (A-M) *Alphabetical order, then we add an empty space
    }
    PrintsMessage(s, false, false);
}
void PrintAvailableLetters(string use) // Prints the Available Letters of the chosen word
{
    PrintsMessage("Letters Left");  //Prints the messages
    PrintsLetters(use, 'a', 'm');        //Prints letters from  A-M
    PrintsLetters(use, 'n', 'z');        //Prints letters from N-Z
}
bool PrintWordAndCheckWin(string word, string guessing) // a function to check the game if the user has won
{
    bool won = true;    // a variable 'won'  and true
    string s;
    for (int i = 0; i < word.length(); i++) //for loop to loop all the characters for the word
    {
        if (guessing.find(word[i]) == string::npos) // if it does not contain the letter of the word
        {
            won = false;     // set 'won' to false, so the user will not win if they have guessed wrong
            s += "_ ";    // '_' so it does not show the appropriate letter of the word (a place holder for the character)
        }
        else
        {
            s += word[i];  // shows the letter of the word
            s += " ";
        }
    }
    PrintsMessage(s, false); // prints the message
    return won;
}
//-----------------------------------------------------------------------------------------------LEONIDS VASILJEVS----------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------DANIEL RAMSAY-----------------------------------------------------------------------------------------------------------------
string LoadsRandomWords(string path)
{      //Added the "#include <vector>"
    int lineCount = 0;
    string word;
    vector<string> v; //  vector a dynamic array || an array of strings , lines of the textual file that we have created
    ifstream reader(path); 
    if (reader.is_open())  
    {    // Added the "#include <fstream>"
        while (std::getline(reader, word)) // puts the input stream
            v.push_back(word);              // uses the push back from the vector 'v' and adds the word in the vector

        int randomLine = rand() % v.size();  // line of code randomised the line and the range

        word = v.at(randomLine);  // sets the word that will return to 'v'
        reader.close();  // closes the reader so other files or application can use our files
    }
    return word;
}
int AttemptsLeft(string word, string guessed) // a function that will indicate how many attempts the user has left
{
    int error = 0;
    for (int i = 0; i < guessed.length(); i++) // will loop throughout the guessed characters
    {
        if (word.find(guessed[i]) == string::npos) // if the actual word does not contain the current guessed character 
            error++;                               //we increment the errors, the user actually made the error by choosing the wrong letter
    }
    return error;
}
//-----------------------------------------------------------------------------------------------DANIEL RAMSAY----------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------VIVEK NEGI-----------------------------------------------------------------------------------------------------------------
int main() 
{      //Added the"#include <time.h>"
    srand(time(0)); // returns as the current time
    string guesses;
    string wordsToGuess;
    wordsToGuess = LoadsRandomWords("Words.txt"); // a funtion that will generate a random word that came from the text file "Words.txt"
    int attempts = 0;  // 
    bool win = false;
    do  //do while loop
    {
        system("cls"); // clears the screen
        PrintsMessage("HANGMAN"); // then prints the message hangman
        DrawsHangman(attempts); // print the actual hangman
        PrintAvailableLetters(guesses); // prints the available letters
        PrintsMessage("Guess the word"); // prints the message
        win = PrintWordAndCheckWin(wordsToGuess, guesses); // places the random word for the user to guess

        if (win) // if the user has won 
            break; // then the loop breaks

        char x;    // if the users has lost 
        cout << ">"; cin >> x; // Displays that the user will need to input somthing

        if (guesses.find(x) == string::npos) // if the guesses does not contain the character 'x' we will add it to the list that the user needs to guess
            guesses += x;

        attempts = AttemptsLeft(wordsToGuess, guesses); // Updates the games funtion 'AttemptsLeft' and the guesses string from line 165

    } while (attempts < 10); // user will have 10 attempts because the we have 10 characters for the Hangman

    if (win)
        PrintsMessage("YOU WON!"); // prints the message that the user has won
    else
        PrintsMessage("GAME OVER"); // prints the message whenever the user has lost the game

    system("pause"); 
    
    return 0;
}
//-----------------------------------------------------------------------------------------------VIVEK NEGI-----------------------------------------------------------------------------------------------------------------
