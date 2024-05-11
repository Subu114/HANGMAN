#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<stdio.h>
#include<iomanip>
#include<conio.h>
using namespace std;

int done = 1;
int start = 0;
int menu_help = 1;
int customWord = 0;
string helpStatus = "[true]";
string customWordStatus = "[false]";
void centre()
{
    cout.width(46);
    cout.fill(' ');
    cout << " ";
}

class HANGMAN
{
private:
    int head_countV;
    int lhand_count, rhand_count;
    int lleg_count, rleg_count;

protected:
    bool head, body, lhand, rhand, lleg, rleg, leye, reye;

public:
    //Functions to print the HANGMAN
    HANGMAN();
    void setAttr(bool, bool, bool, bool, bool, bool, bool, bool);
    void prt_headV();
    void prt_headH();
    void prt_body();
    void prt_LHand();
    void prt_RHand();
    void prt_LLeg();
    void prt_RLeg();
};

HANGMAN :: HANGMAN()
{
    head = body = false;
    lhand = rhand = false;
    lleg = rleg = false;
    leye = reye = false;
    head_countV = 1;
    lhand_count = 2, rhand_count = 2;
    lleg_count = 1, rleg_count = 1;
}

//Setter Function to set the HANGMAN attributes
void HANGMAN :: setAttr(bool h, bool b, bool lh, bool rh, bool ll, bool rl, bool le, bool re)
{
    head = h;
    body = b;
    lhand = lh;
    rhand = rh;
    lleg = ll;
    rleg = rl;
    leye = le;
    reye = re;
}

void HANGMAN :: prt_headH()
{
    if(head)
        cout << "      -----";
}
void HANGMAN :: prt_headV()
{
    if(head)
    {
        if(head_countV == 1)
        {
            cout << "     | ";
            if(leye)
                cout << "x";
            else
                cout << " ";

            cout << " ";

            if(reye)
                cout << "x";
            else
                cout << " ";
            cout << " |";
            head_countV = 3;
        }
        else if(head_countV == 3)
        {
            cout << "     |     |";
            head_countV = 1;
        }
    }
}
void HANGMAN :: prt_LHand()
{
    if(lhand_count == 2)
    {
        cout << "      / ";
        lhand_count = 3;
        return;
    }
    if(lhand_count == 3)
    {
        cout << "     /  ";
        lhand_count = 2;
    }
}
void HANGMAN :: prt_RHand()
{
    if(rhand_count == 2)
    {
        cout << " \\";
        rhand_count = 3;
        return;
    }
    if(rhand_count == 3)
    {
        cout << "  \\";
        rhand_count = 2;
    }
}
void HANGMAN :: prt_body()
{
    if(lhand)
        prt_LHand();
    else
        cout << "        ";

    if(body)
        cout << "|";
    if(rhand)
        prt_RHand();
}
void HANGMAN :: prt_RLeg()
{
    if(rleg)
    {
        if(rleg_count == 1)
        {
            cout << " \\";
            rleg_count = 3;
            return;
        }
        if(rleg_count == 3)
        {
            cout << "   \\";
            rleg_count = 1;
            return;
        }
    }
}
void HANGMAN :: prt_LLeg()
{
    if(lleg)
    {
        if(lleg_count == 1)
        {
            cout << "       /";
            lleg_count = 3;
            if(rleg)
                prt_RLeg();
            return;
        }
        if(lleg_count == 3)
        {
            cout << "      /";
            lleg_count = 1;
            if(rleg)
                prt_RLeg();
            return;
        }
    }
}

class PLAYER
{
protected:
    int pRank;
    string name, pdifficulty, pword;
    long int score;
    int totalWords = 0;
public:
    PLAYER()
    {
        pRank = -1;
        name = "N\\A";
        score = 0;
        pdifficulty = "EASY";
        pword = " ";
    }
};

class DATABASE : virtual public PLAYER
{
protected:
    string words[50];
    int wordCount = 0, customWordCount = 0;
    ofstream fileIn;
    ifstream fileOut;
public:
    DATABASE();
    void set_options();
    void read_word();
    void store_score();
    void add_score();
    void copy_files();
};
DATABASE :: DATABASE()
{
    fileOut.open("data.txt");
    if(!fileOut.good())
    {
        fileOut.close();
        fileIn.open("data.txt");
        fileIn << menu_help << endl;
        fileIn << helpStatus << endl;
        fileIn << customWord << endl;
        fileIn << customWordStatus << endl;
        fileIn.close();
    }
    else
    {
        fileOut >> menu_help;
        fileOut >> helpStatus;
        fileOut >> customWord;
        fileOut >> customWordStatus;
        fileOut.close();
    }
    fileOut.open("customwords.txt");
    if(!fileOut.good())
    {
        fileOut.close();
        fileIn.open("customwords.txt");
        fileIn.close();
    }
    else
    {
        fileOut.close();
    }
}
void DATABASE :: set_options()
{
    fileIn.open("data.txt");
    fileIn << menu_help << endl;
    fileIn << helpStatus << endl;
    fileIn << customWord << endl;
    fileIn << customWordStatus << endl;
    fileIn.close();
}

void DATABASE :: read_word()
{
    if(customWord)
        fileOut.open("customwords.txt");
    else
        fileOut.open("words.txt");
    try
    {
        string ch;
        if( !(fileOut >> ch) )
            throw 1;

        int i = 0;
        while(fileOut >> ch)
        {
            words[i] = ch;
            i++;
        }
        wordCount = customWordCount = i + 1;
    }
    catch(...)
    {
        cout << endl;
        cout.width(46);
        cout.fill(' ');
        cout << " ";
        if(customWord)
            cout << "EXCEPTION CAUGHT! Couldn't Locate any Custom word. Seems like the file is empty..!";
        else
            cout << "EXCEPTION CAUGHT! Couldn't Locate the word. Seems like the file is not present or empty..!";
        cout << endl;
        cout.width(46);
        cout.fill(' ');
        cout << " ";
        if(done == 2)
            cout << "Default word will be taken for each round.\n";
        else
            done = 2;
        wordCount = customWordCount = 1;
        words[0] = "HANGMAN";
        getch();
    }
    fileOut.close();
}
void DATABASE :: store_score()
{
    add_score();
    copy_files();
}

//Function to store the score in a temporary file as per the player SCOREs
void DATABASE :: add_score()
{
    string playerName, playerDifficulty;
    int playerRank, playerWord;
    int done = 0, j = 0;
    long int playerScore;
    ifstream rFile("highscore.txt");//Reading from highscore.txt
    ofstream wFile("tmp.txt");//Writing into tmp.txt

    try
    {
        if(!wFile.good())
            throw 1.12;
    }
    catch(double a)
    {
        cout << "\nEXCEPTION CAUGHT! Couldn't Locate the [tmp.txt] file\n..";
        cout << "Score Couldn't be saved\n";
        rFile.close();
        wFile.close();
        return;
    }

    while(rFile >> playerRank >> playerName >>playerScore >> playerDifficulty >> playerWord)
    {
        //Enter if current player score is greater than the player score from file
        if(playerScore > score || done == 1)
        {
            wFile << j + 1 << endl;
            wFile << playerName << endl;
            wFile << playerScore << endl;
            wFile << playerDifficulty << endl;
            wFile << playerWord << endl;
        }
        else
        {
            wFile << j + 1 << endl;
            wFile << name << endl;
            wFile << score << endl;
            wFile << pdifficulty << endl;
            wFile << totalWords << endl;

            wFile << j + 2 << endl;
            wFile << playerName << endl;
            wFile << playerScore << endl;
            wFile << playerDifficulty << endl;
            wFile << playerWord << endl;

            done = 1;
            j++;
        }
        j++;
    }
    //If score is to be entered at last or when high-score file is Empty
    if(done == 0)
    {
        wFile << j + 1 << endl;
        wFile << name << endl;
        wFile << score << endl;
        wFile << pdifficulty << endl;
        wFile << totalWords << endl;
    }
    rFile.close();
    wFile.close();
}

//Function to copy the content from temporary file to the original file[highscore.txt]
void DATABASE :: copy_files()
{
    ifstream rFile("tmp.txt");
    ofstream wFile("highscore.txt");

    try
    {
        if(!rFile.good())
            throw 1.12;
        if(!wFile.good())
            throw 1;
    }
    catch(int a)
    {
        cout << "\nEXPECTION CAUGHT! Couldn't Locate the [highscore.txt] file\n..";
        cout << "Score Couldn't be saved\n";
        rFile.close();
        wFile.close();
        return;
    }
    catch(double a)
    {
        cout << "\nEXPECTION CAUGHT! Couldn't Locate the [tmp.txt] file\n..";
        cout << "Score Couldn't be saved\n";
        rFile.close();
        wFile.close();
        return;
    }


    int a, e;
    string b, d;
    long int c;

    while (rFile >> a >> b >> c >> d >> e)
    {
        wFile << a << endl;
        wFile << b << endl;
        wFile << c << endl;
        wFile << d << endl;
        wFile << e << endl;
    }
    rFile.close();
    wFile.close();
}

//The Main GAME class
class GAME_DATA : virtual public PLAYER, public HANGMAN, public DATABASE
{
protected:
    bool gameStatus = true;
    int chances, guessed, difficulty, word_length;
    string word;
public:
    GAME_DATA(){
        gameStatus = true;
        chances = 8;
        guessed = 0;
        difficulty = 1;
        word_length = 0;
    }
    //Member functions for the game
    int  check(char wordArray[], int wordArrayCount[], int length, char input);
    void choose_difficulty();
    void credits();
    void display_game_over();
    void display_hangman_text();
    void display_HangMan();
    void display_help();
    void easy_difficulty(int [], int);
    void get_customWords();
    void game_implementation();
    void get_player_name();
    string get_word();
    void highscore();
    int isDone(int [], int);
    void main_menu();
    void medium_difficulty(int [], int);
    void menu();
    void options();
    void reset_values();
    void score_increment();
    void score_Decrement();
    void set_customWords();
    void set_menu_help();
    void set_player_difficulty_word();
    void start_game();
    void reset_all_files();
    void wrong_choice();
};

//For displaying the HANGMAN text (Game header)
void GAME_DATA :: display_hangman_text()
{
    centre();
    cout << "\t\t\t _______________________________________________________________________________________            " << endl;
    centre();
    cout << "\t\t\t| #      #   ########   #       #    ######     #       #   ########   #       #     #  |           " << endl;
    centre();
    cout << "\t\t\t| #      #   #      #   # #     #   #           # #   # #   #      #   # #     #     #  |           " << endl;
    centre();
    cout << "\t\t\t| #      #   #      #   #  #    #   #           #  # #  #   #      #   #  #    #     #  |           " << endl;
    centre();
    cout << "\t\t\t| #      #   #      #   #   #   #   #           #   #   #   #      #   #   #   #     #  |           " << endl;
    centre();
    cout << "\t\t\t| ########   ########   #    #  #   #           #       #   ########   #    #  #     #  |           " << endl;
    centre();
    cout << "\t\t\t| #      #   #      #   #     # #   #   #####   #       #   #      #   #     # #        |           " << endl;
    centre();
    cout << "\t\t\t| #      #   #      #   #      ##   #     #     #       #   #      #   #      ##    ### |           " << endl;
    centre();
    cout << "\t\t\t| #      #   #      #   #       #    ######     #       #   #      #   #       #    ### |           " << endl;
    centre();
    cout << "\t\t\t|_______________________________________________________________________________________|"            << endl << endl << endl;
}

//Displaying the main menu
void GAME_DATA :: main_menu()
{
    display_hangman_text();
    int width = 39;
    int width2 = 89;
    cout <<endl;

    centre();
    cout << "\t\t\t ";
    cout.width(88);
    cout.fill('_');
    cout.setf(ios::left);
    cout << "";
    cout << endl;

    centre();
    cout << "\t\t\t";
    cout << "|";
    cout.width(89);
    cout.fill(' ');
    cout.setf(ios::right);
    cout << "|";
    cout << endl;

    cout.setf(ios::right);
    centre();
    cout << "\t\t\t|\t\t\t\t    1. New Game    " << setw(width) << setfill(' ') << "|";
    cout << endl;

    centre();
    cout << "\t\t\t|" << setw(width2) << setfill(' ') << "|" << endl;
    centre();

    cout << "\t\t\t|\t\t\t\t    2. Scoreboard  " << setw(width) << setfill(' ') << "|";
    cout << endl;

    centre();
    cout << "\t\t\t|" << setw(width2) << setfill(' ') << "|" << endl;

    centre();
    cout << "\t\t\t|\t\t\t\t    3. Options     " << setw(width) << setfill(' ') << "|";
    cout << endl;

    centre();
    cout << "\t\t\t|" << setw(width2) << setfill(' ') << "|" << endl;

    centre();
    cout << "\t\t\t|\t\t\t\t    4. Custom Words" << setw(width) << setfill(' ') << "|";
    cout << endl;

    centre();
    cout << "\t\t\t|" << setw(width2) << setfill(' ') << "|" << endl;

    centre();
    cout << "\t\t\t|\t\t\t\t    5. Help        " << setw(width) << setfill(' ') << "|";
    cout << endl;

    centre();
    cout << "\t\t\t|" << setw(width2) << setfill(' ') << "|" << endl;

    centre();
    cout << "\t\t\t|\t\t\t\t    6. Exit        " << setw(width) << setfill(' ') << "|";
    cout << endl;

    centre();
    cout << "\t\t\t";
    cout << "|";
    cout.width(89);
    cout.fill(' ');
    cout.setf(ios::left);
    cout << "|";
    cout << endl;

    centre();
    cout << "\t\t\t|";
    cout.width(89);
    cout.fill('_');
    cout << "|";
    cout.unsetf(ios::left);
}

//Main function to print the HANGMAN
void GAME_DATA :: display_HangMan()
{
    int length = 50;
    centre();
    cout << setw(length) << " " << "   _________ "           << endl;
    centre();
    cout << setw(length) << " " <<"  |         | "           << endl;
    centre();
    cout << setw(length) << " " <<"  | ";
    prt_headH();
    cout << setw(37) << right << "SCORE   : " << score <<endl;
    centre();
    cout << setw(length) << " " <<"  | ";
    prt_headV();
    cout << endl;
    centre();
    cout << setw(length) << " " <<"  | ";
    prt_headV();
    cout << endl;
    centre();
    cout << setw(length) << " " <<"  | ";
    prt_headH();
    cout << setw(37) << right << "CHANCES : " << chances <<endl;
    centre();
    cout << setw(length) << " " <<"  | ";
    prt_body();
    cout << endl;
    centre();
    cout << setw(length) << " " <<"  | ";
    prt_body();
    cout << endl;
    centre();
    cout << setw(length) << " " <<"  | ";
    prt_LLeg();
    cout << endl;
    centre();
    cout << setw(length) << " " <<"  | ";
    prt_LLeg();
    cout << endl;
    centre();
    cout << setw(length) << " " <<"+===+          "        << endl;
    cout << left;
    if(name == "SubuWalker")
    {
        centre();
        cout << word << endl;
    }
}
void GAME_DATA :: menu()
{
    char ch;
    int i = 1;
    while(i)
    {
        system("cls");
        main_menu();
        cout << endl;
        ch = getch();
        switch(ch)
        {
        case '1' :
            get_player_name();
            setAttr(false, false, false, false, false, false, false, false);
            game_implementation();
            break;
        case '2':
            highscore();
            break;
        case '3' :
            options();
            set_options();
            break;
        case '4' :
            get_customWords();
            break;
        case '5' :
            display_help();
            break;
        case '6' :
            i = 0;
        default:
            break;
        }
    }
}

//Getting player name
void GAME_DATA :: get_player_name()
{
    if(done == 0 || menu_help == 1)
    {
        display_help();
        done = 1;
    }
    system("cls");
    display_hangman_text();
    fflush(stdin);
    cout << endl << endl;
    centre();

    cout << "Enter your Name : ";
    getline(cin, name);
    choose_difficulty();

}
//UI for selecting difficulty
void GAME_DATA :: choose_difficulty()
{
    cout << endl;
    centre();
    cout << "SELECT THE DIFFICULTY\n";
    centre();
    cout << "1. Easy (default)" << endl;
    centre();
    cout << "2. Medium" << endl;
    centre();
    cout << "3. Hard" << endl << endl;
    centre();
    char ch = getch();
    if(ch == '1')
        difficulty = 1;
    else if(ch == '2')
        difficulty = 2;
    else if(ch == '3')
        difficulty = 3;
    else
    {
        cout << "Default Difficulty will be chosen\n\n";
        getch();
    }
}
//Main game running function
void GAME_DATA :: game_implementation()
{

    while(gameStatus)
    {
        read_word();
        word = get_word();
        totalWords++;
        word_length = word.length();
        set_player_difficulty_word();
        char wordArray[word_length];
        int wordCountArray[word_length];
        for(int i = 0; i < word_length; i++)
            wordArray[i] = word[i];
        for(int i = 0; i < word_length; i++)
            wordCountArray[i] = 0;

        if(difficulty == 1)
            easy_difficulty(wordCountArray, word_length);
        else if(difficulty == 2)
            medium_difficulty(wordCountArray, word_length);

        char c;
        int choices = 0;
        while(1)
        {
            system("cls");
            display_hangman_text();
            display_HangMan();
            if(reye)
            {
                gameStatus = false;
                display_game_over();
                break;
            }
            if(isDone(wordCountArray, word_length))
                break;

            cout << endl << endl;
            centre();
            cout << "\t";
            for(int i = 0; i < word_length; i++)
            {
                if(wordCountArray[i] == 1)
                    cout << wordArray[i] << " ";
                else
                    cout << "_ ";
            }
            cout << endl << endl << endl;
            centre();
            cout << "Your Letter : ";
            cin >> c;
            c = toupper(c);
            cout << endl;

            if(!check(wordArray, wordCountArray, word_length, c))
                wrong_choice();
            cout << endl;
            choices++;
        }
    }
    store_score();
    getch();
    highscore();
    reset_values();
}

//Function to select and return any random word for the game
string GAME_DATA :: get_word()
{
    srand((unsigned) time(NULL));
    unsigned int index = rand() % wordCount;
    return words[index];
}
//Setting difficulty value as per users choice
void GAME_DATA :: set_player_difficulty_word()
{
    pword = word;
    if(difficulty == 1)
        pdifficulty = "EASY";
    else if(difficulty == 2)
        pdifficulty = "MEDIUM";
    else if(difficulty == 3)
        pdifficulty = "HARD";
}
//Setting attributes for easy difficulty selected
void GAME_DATA :: easy_difficulty(int wordCountArray[], int length)
{
    int index;
    srand((unsigned) time(NULL));
    for(int i = 0; i < length / 2;)
    {
        index = rand() % length;
        if(wordCountArray[index])
            continue;
        wordCountArray[index] = 1;
        if(length <= 3)
            break;
        i++;
    }
}
//Setting attributes for medium difficulty selected
void GAME_DATA :: medium_difficulty(int wordCountArray[], int length)
{
    int index;
    srand((unsigned) time(NULL));
    for(int i = 0; i < length / 2 - 1;)
    {
        index = rand() % length;
        if(wordCountArray[index])
            continue;
        wordCountArray[index] = 1;
        if(length <= 3)
            break;
        i++;
    }
}
//Display Interface for Game Over
void GAME_DATA :: display_game_over()
{
    cout << endl;

    centre();
    cout.setf(ios::right);
    cout << setw(30) << setfill(' ') << "";
    cout << setw(30) << setfill('+') << " GAME ";
    cout << setw(30) << setfill('+') << left << " OVER! ";

    cout << endl;
    centre();
    cout << setw(30) << setfill(' ') << "";
    cout << "You've Lost !" << endl;
    centre();
    cout << setw(30) << setfill(' ') << "";
    cout << "The Word was : " << word << endl;
    centre();
    cout << setw(30) << setfill(' ') << "";
    cout << "Your Score   : " << score << endl;
}
//Function to check if the user has successfully guessed the word
int GAME_DATA :: isDone(int arr[], int n)
{
    for(int i = 0; i < n; i++)
        if(arr[i] != 1)
            return 0;
    return 1;
}
//Function to check whether the entered letter is correct or not
int GAME_DATA :: check(char wordArray[], int wordArrayCount[], int length, char input)
{
    int wcount = 0, isThere = 0, appeared = 0;

    for(int i = 0; i < length; i++)
    {
        if(input == wordArray[i] && wordArrayCount[i] == 1)
        {
            appeared++;
        }
        if(input == wordArray[i] && !wordArrayCount[i])
        {
            wordArrayCount[i] = 1;
        }
        else
            wcount++;


    }
    if(wcount == length || appeared > 1)
        return 0;
    else
    {
        guessed++;
        score_increment();
        return 1;
    }

}
void GAME_DATA :: score_increment()
{
    double multiplier = 1.00;
    if(difficulty == 2)
        multiplier = 1.25;
    else if(difficulty == 3)
        multiplier = 1.50;

    score = multiplier * (100.00 * chances / word_length) + score;
}
//Function to set the hangman attributes if the users guess is wrong
void GAME_DATA :: wrong_choice()
{
    score_Decrement();
    chances--;
    if(!head)
    {
        head = true;
        return;
    }
    if(!body)
    {
        body = true;
        return;
    }
    if(!lhand)
    {
        lhand = true;
        return;
    }
    if(!rhand)
    {
        rhand = true;
        return;
    }
    if(!lleg)
    {
        lleg = true;
        return;
    }
    if(!rleg)
    {
        rleg = true;
        return;
    }
    if(!leye)
    {
        leye = true;
        return;
    }
    if(!reye)
    {
        reye = true;
    }
}
void GAME_DATA :: score_Decrement()
{
    double multiplier = 1.00;
    if(difficulty == 2)
        multiplier = 1.25;
    else if(difficulty == 3)
        multiplier = 1.50;
    score = score - (2.50 - multiplier) * (10.00 * chances / word_length);
}

//Function to display Highscore
void GAME_DATA :: highscore()
{
    system("cls");
    display_hangman_text();

    centre();
    cout << setw(45) << setfill(' ') << "";
    cout << " ___________________________ " << endl;
    centre();
    cout << setw(45) << setfill(' ') << "";
    cout << "|        SCOREBOARD         |" << endl;
    centre();
    cout << setw(45) << setfill(' ') << "";
    cout << "|___________________________|" << endl;
    centre();
    cout << endl ;

    centre();
    cout.width(118);
    cout.fill('-');
    cout << "";

    cout << endl;
    centre();
    cout.width(5);
    cout.fill(' ');
    cout.setf(ios::left);
    cout << "";
    cout.width(10);
    cout.fill(' ');
    cout.setf(ios::left);
    cout << "RANK";
    cout.width(25);
    cout.fill(' ');
    cout << "NAME";
    cout.width(25);
    cout.fill(' ');
    cout << "SCORE";
    cout.width(25);
    cout.fill(' ');
    cout << "DIFFICULTY";
    cout.width(25);
    cout.fill(' ');
    cout << "WORD COUNT";
    cout << endl;
    centre();

    for(int i = 0; i < 118; i++)
        cout << "-";

    ifstream rFile("highscore.txt");
    try
    {
        if(rFile.eof())
            throw 1;
    }
    catch(int a)
    {
        cout << "\nEXPECTION CAUGHT! High Score file Empty\n..";
        cout << "Score Couldn't be loaded\n";
        rFile.close();
        return;
    }
    int a, e;
    string b, d;
    long int c;
    while(rFile >> a >> b >> c >> d >> e)
    {
        cout << endl;
        centre();

        cout.width(5);
        cout.fill(' ');
        cout << " ";

        cout.width(10);
        cout.fill(' ');
        cout << a;

        cout.width(25);
        cout.fill(' ');
        cout << b;

        cout.width(25);
        cout.fill(' ');
        cout << c;

        cout.width(25);
        cout.fill(' ');
        cout << d;

        cout.width(25);
        cout.fill(' ');
        cout << e;
    }
    cout << endl;
    centre();
    for(int i = 0; i < 118; i++)
        cout << "-";

    cout << endl;
    centre();
    cout << "Press R to RESET the HighScores....!";
    char ch = getch();
    if(ch == 'R' || ch == 'r')
    {
        cout << endl;
        centre();
        cout << "Press R again to confirm!";
        ch = getch();
        if(ch == 'R' || ch == 'r');
            reset_all_files();
    }
}

void GAME_DATA :: reset_all_files()
{
    ofstream f;
    f.open("data.txt");
    f.close();
    f.open("tmp.txt");
    f.close();
    f.open("highscore.txt");
    f.close();
}
void GAME_DATA :: options()
{
    char ch;
    do
    {
        system("cls");
        display_hangman_text();
        cout << endl << endl;
        centre();
        cout << "\t\t\t";
        cout << "OPTIONS" << endl << endl;
        centre();
        cout << "\t\t\t";
        cout << "1. Display Help at Each round " << helpStatus << endl << endl;
        centre();
        cout << "\t\t\t";
        cout << "2. Custom words " << customWordStatus << endl << endl ;
        centre();
        cout << "\t\t\t";
        cout << "Press the option number to toggle it!...";
        cout << endl;
        centre();
        cout << "\t\t\t";
        cout << "Press any other key to go back!...";
        ch = getch();
        switch(ch)
        {
        case '1' :
            set_menu_help();
            break;
        case '2' :
            set_customWords();
            break;
        default :
            return;
            break;
        }
    }
    while(1);
}
void GAME_DATA :: set_menu_help()
{
    if(!menu_help)
    {
        menu_help = 1;
        helpStatus = "[true]";
        return;
    }
    menu_help = 0;
    helpStatus = "[false]";

}
void GAME_DATA :: set_customWords()
{
    if(!customWord)
    {
        customWord = 1;
        customWordStatus = "[true]";
        return;
    }
    customWord = 0;
    customWordStatus = "[false]";

}
void GAME_DATA :: get_customWords()
{
    bool ending = false;
    string str;
    fstream file, tmpFile;

    system("cls");

    display_hangman_text();
    cout << endl;

    centre();
    centre();
    cout << "_______CUSTOM WORDS_______" << endl;
    file.open("customwords.txt", ios::in);

    if( !(file >> str) )
    {
        cout << endl;
        centre();
        centre();
        cout << "No Custom words found!";
        cout << endl;
        centre();
        centre();
        cout << "Press Y to enter the custom words...!" << endl;
        centre(); centre();
        cout << "Press any key to return back to the Main Menu...!";
        char ch = getch();
        file.close();
        if(!(ch == 'Y' || ch == 'y'))
            return;
        file.open("customwords.txt", ios::app);
    }
    else
    {
        do
        {
            centre();
            centre();
            cout << str;
            cout << endl;
        }while(file >> str);
        file.close();
        cout << endl;
        centre();
        cout << "\t\t\t\t\t";
        cout << "Press Y to return back to Main Menu..!";
        cout << endl << endl;
        centre();
        cout << "\t\t\t\t\t";
        cout << "Press R to reset the Custom Words File..!";
        cout << endl << endl;
        centre();
        cout << "\t\t\t\t\t";
        cout << "Press any other key, to append the Custom Words..!";
        char ch = getch();
        if(ch == 'Y' || ch == 'y')
            return;

        if(ch == 'R' || ch == 'r')
        {
            cout << endl;
            centre();
            cout << "\t\t\t\t\t";
            cout << "Press R again to confirm!";
            ch = getch();
            if(ch == 'R' || ch == 'r')
            {
                cout << endl;
                centre();
                centre();
                cout << "FILE SUCCESSFULLY RESET\n";
                file.open("customwords.txt", ios::out);
                customWordCount = 0;
            }
            else
                file.open("customwords.txt", ios::app);
        }
        else
            file.open("customwords.txt", ios::app);
    }
    system("cls");
    display_hangman_text();
    int length = customWordCount;
    cout << endl;
    centre();
    cout << "\t\t\t\t\t";
    cout << "Enter the Custom Words one by one [Enter $[on new a line] to exit]" << endl;
    while(1)
    {
        centre();
        cout << "\t\t\t\t\t";
        cin >> str;
        if(str == "$")
            break;

        transform(str.begin(), str.end(), str.begin(), ::toupper);
        file << str << endl;
        length++;
    }
    file.close();
    customWordCount = length;
}

//Function to display help from the file [help.txt]
void GAME_DATA :: display_help()
{
    system("cls");
    display_hangman_text();
    cout << endl;
    ifstream file("help.txt");
    string str;
    while(getline(file, str))
    {
        centre();
        cout << "\t\t\t";
        cout << str << endl;
    }
    centre();
    cout << "\t\t\t";
    cout << "Press Any key to continue...";
    file.close();
    getch();
}

//For resetting values after each game
void GAME_DATA :: reset_values()
{
    gameStatus = true;
    score = 0;
    chances = 8;
    guessed = 0;
    difficulty = 1;
    wordCount = 0;
    customWordCount = 0;
    totalWords = 0;
}
void GAME_DATA :: credits()
{
    system("cls");
    display_hangman_text();
    cout << endl;
    centre();
    cout << "\t\t\t";
    cout << "By Subodh Salgaonkar";
    cout << endl;
    centre();
    cout << "\t\t\t";
    cout << "21CO63\n";
    centre();
    cout << "\t\t\t";
    cout << "S.E. COMPUTER";
    getch();
}
int main()
{
    GAME_DATA obj;
    obj.menu();
//    obj.credits();
    return 0;
}
