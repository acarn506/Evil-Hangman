
#include "FamilySet.h"
#include <cctype>
//           [---Would like to use one late day on this assignment.---]

bool debug;    // Global variable to indicate debugging

bool PromptShowNumWords() {
    while (true) {
        cout << "Would you like to display the number of words left in the word list." << endl;
        cout << "(y/n) ";
        string response;
        cin >> response;
        if (response == "y")
            return true;
        if (response == "n")
            return false;
        cout << "Please enter y or n..." << endl;
    }
}

bool PromptYesNoMessage(string msg) {
    while (true) {
        cout << msg << "(y/n) ";
        string response;
        cin >> response;
        if (response == "y")
            return true;
        if (response == "n")
            return false;
        cout << "Please enter y or n..." << endl;
    }
}

int PromptGuesses()
{
    while (true) {
        int len;
        cout << "Please enter how many guesses: ";
        cin >> len;
        if (len > 0)
            return len;
    }
}

int PromptWordLength()
{
    int len;
    while (true) {
        cout << "\n" << "Enter a word length: ";
        cin >> len;
        if (len > 0 && len < 30 && len != 26 && len != 27) {
            return len;
        }
         cout << "\n" << "No such word length!" << endl;
    }
}
//string guess
char PromptGuess(string& guessedLetters)
{
    char guess;
    int check = 0;
    
    // Your code here...
    while (check != 1) {
        
        cout << "\n" << "Make a guess: ";
        cin >> guess;
        
        if (guessedLetters.size() > 0 || !isalpha(guess)) {
            for (int i = 0; i < guessedLetters.size(); i++) {
                if (guessedLetters[i] == guess || !isalpha(guess)) {
                    cout << "Already guessed letter or guess is not valid" << endl;
                    check = 0;
                    break;
                }
                check = 1;
            }
        }
        
        else {
            check = 1;
        }
        
    }
    
    return guess;
}

//string guess
string ChooseFamily(char guess, string guessProgress, FamilySet& set)
{
    // filter families by guess and guessProgress/guessPattern
    
    string maxFamily;
    set.filterFamilies(guess, guessProgress);
    /*
     * Use the iterator to loop through each family and
     * figure out the biggest family size.
     * Return this family
     */
    
    maxFamily = set.getNextFamily();
    
    return maxFamily;
}

bool isWin(string guessedProgress)
{
    return guessedProgress.find("*") == string::npos;
}

void PlayEvilHangman(string file)
{
    char guess;
    // Prompt user for word length and number of guesses
    int len = PromptWordLength();
    
    int guessesLeft = PromptGuesses();
    bool displayNumWords = PromptShowNumWords();
    
    // Load dictionary based on word length
    cout << "\n" << "Loading dictionary..." << endl;
    FamilySet families(file, len);
    
    string guessedLetters = "";
    string correctlyGuessed = "";    // correctly guessed positions
    string guessProgress = "";
    for (int i = 0; i < len; i++)
        guessProgress += "*";
    
    // Actual game loop...
    while (true) {
        
        // Your code here...
        cout << "\n" << "Guess Progress: " << guessProgress << endl;
        cout << "Guesses left: " << guessesLeft << endl;
        cout << "Words Guessed so far: " << guessedLetters << endl;
        
        guess = PromptGuess(guessedLetters);
        guessesLeft--;
        guessedLetters += guess;
        //choose maxFamily
        guessProgress = ChooseFamily(guess, guessProgress, families);
        
        //display running total if true
        if (displayNumWords) {
            cout << "Number of words left " << families.numWords();
        }
        
        //debug function call if true
        if (debug) {
            families.displayDebug();
        }
        
        //update masterlist
        families.setFamily(guessProgress);
        
        if (isWin(guessProgress)) {
            cout << "\n" << "Correct guess: " << guessProgress << endl;
            cout << "Wow! You won!" << endl;
            break;
        }
        
        if (guessesLeft <= 0) {
            cout << "\n" << "Wow... you are a really bad guesser..." << endl;
            cout << "The mystery word was: ";
            cout << families.getRandomWord() << endl;
            cout << "\n";
            break;
        }
    }
}

int main (int argc, char * const argv[])
{
    string file;
    /*
    cout << "Enter file: ";
    cin >> file;   */             // Can comment out this line and include the following while developing
    file = "/Users/acarn506/Desktop/Data-Structures/Hangman/Hangman/word.txt";  // Convenient to hard code while developing
    
    int option = 0;
    
    do {
        cout <<
        "\n**************************************************\n"
        "*                  CLASSIC HANGMAN               *\n"
        "*                                                *\n"
        "* (1) PLAY HANGMAN                               *\n"
        "* (2) QUIT                                       *\n"
        "**************************************************\n"
        "Enter an integer for option + ENTER: ";
        cin >> option;
        cout << "\n";
        
        switch (option) {
            case 1:
            {
                while (true) {
                    debug = PromptYesNoMessage("Turn debugging on?");
                    PlayEvilHangman(file);
                    if (!PromptYesNoMessage("Would you like to play again ?"))
                        break;
                }
                break;
            }
                
            case 2:
            {
                cout << "Okay, goodbye! " << endl;
                break;
                
            default:
                cout << "\n" << "Wrong Option! " << endl;
            }
        }
    }while(option != 2);
}


