#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;
using namespace chrono;

void EnableColor()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

// ANSI color codes
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define RESET "\033[0m"

void welcome()
{

    printf("\33\t\t\t[96m __       __   _______   __        _______   __________   _____ _____   _______\n");
    printf("\t\t\t|  |     |  | |   ____] |  |      |   ____] |   ____   | |     |     | |   ____]\n");
    printf("\t\t\t|  |  _  |  | |  |__    |  |      |  |      |  |    |  | |   _   _   | |  |__ \33[0m\n");
    printf("\t\t\t\33[94m|  |_| |_|  | |   __]   |  |      |  |      |  |    |  | |  | | | |  | |   __]\n");
    printf("\t\t\t|           | |  |____  |  |____  |  |____  |  |____|  | |  | |_| |  | |  |____\n");
    printf("\t\t\t|_____|_____| |_______] |_______] |_______] |__________| |__|     |__| |_______]\33[0m\n\n\n\n");

}
// User structure
struct User
{
    string username;
    int password;
    string bloodGroup;
    string sex;
    string maritalStatus;
    int gamePoints;
};

vector<User> users;

// Typing test questions
vector<string> easy_questions =
{
    "The sun shines brightly in the blue sky.",
    "A cat sleeps peacefully on the soft bed.",
    "I love eating fresh apples every morning.",
    "The book is on the wooden table.",
    "Birds sing sweet songs in the morning."
};

vector<string> medium_questions =
{
    "Practice makes a person perfect in every skill.",
    "A beautiful butterfly landed on the yellow flower.",
    "Technology is advancing at a very fast pace.",
    "The library is a quiet place to read and learn.",
    "She quickly typed the message on her phone."
};

vector<string> hard_questions =
{
    "The quick brown fox jumps over the lazy dog.",
    "Perseverance and determination lead to great success.",
    "An astronomer observes celestial bodies through a telescope.",
    "Intricate designs require patience and precision to create.",
    "The orchestra performed a mesmerizing symphony last night."
};

// Game structures
struct Player
{
    string name;
    int score;
};

unordered_map<string, vector<pair<string, string>>> categories =
{
    {
        "Fruits", {
            {"apple", "A red or green fruit, often found in pies"},
            {"banana", "A long yellow fruit, loved by monkeys"},
            {"cherry", "A small red fruit often used as a topping"},
            {"orange", "A citrus fruit that shares its name with a color"},
            {"strawberry", "A red fruit with tiny seeds on the outside"}
        }
    },
    {
        "Animals", {
            {"tiger", "A big cat with orange fur and black stripes"},
            {"elephant", "The largest land animal with a trunk"},
            {"giraffe", "An animal with a very long neck"},
            {"zebra", "A horse-like animal with black and white stripes"},
            {"kangaroo", "An Australian animal that jumps a lot"}
        }
    }
};

// Function declarations
void loadUsers();
void saveUsers();
int password();
bool registerUser();
int loginUser();
vector<string> generateDeck();
int getCardValue(string card);
char getCardType(string card);
string getColoredCard(string card);
bool hasType(const vector<string> &player, char type);
int playCardGame();
int playKeyPressGame();
int playTypingTest();
void updateProfile(int userIndex);
void clearScreen();
void tryAgain(string correct_sentence);
void startTypingTest(vector<string> questions);
void easyTypingTest();
void mediumTypingTest();
void hardTypingTest();
void printLargeNumber(int num);
void countdown();
int playHangman();
int playMathQuiz();
int playRockPaperScissors();
int playGuessTheNumber();
void displayLeaderboard(vector<Player> &leaderboard);
void loadLeaderboard(vector<Player> &leaderboard);
void saveLeaderboard(const vector<Player> &leaderboard);
bool isLetterPresent(char a, const string &b);
void updateHiddenWord(char a, const string &b, string &c);
void displayHangman(int a);

void loadUsers()
{
    ifstream file("users.txt");
    string username, bloodGroup, sex, maritalStatus;
    int password, gamePoints;
    while (file >> username >> password >> bloodGroup >> sex >> maritalStatus >> gamePoints)
    {
        users.push_back({username, password, bloodGroup, sex, maritalStatus, gamePoints});
    }
    file.close();
}

void saveUsers()
{
    ofstream file("users.txt");
    for (const auto& user : users)
    {
        file << user.username << " " << user.password << " " << user.bloodGroup << " "
             << user.sex << " " << user.maritalStatus << " " << user.gamePoints << endl;
    }
    file.close();
}

int password()
{
    int pass = 0;
    string passStr;
    char ch;
    cout << "Enter 4-digit password: ";
    while (true)
    {
        ch = getch();
        if (ch == 13 && passStr.length() == 4)
        {
            break;
        }
        else if (ch == 8 && !passStr.empty())
        {
            cout << "\b \b";
            passStr.pop_back();
        }
        else if (ch >= '0' && ch <= '9' && passStr.length() < 4)
        {
            cout << "*";
            passStr += ch;
        }
    }
    cout << endl;
    pass = stoi(passStr);
    return pass;
}

bool registerUser()
{
    string username, bloodGroup, sex, maritalStatus;
    int pass;

    cout << "Enter a new username: ";
    cin >> username;

    for (const auto& user : users)
    {
        if (user.username == username)
        {
            cout << "Username already exists! Try again.\n";
            return false;
        }
    }

    pass = password();
    cout << "Enter blood group: ";
    cin >> bloodGroup;
    cout << "Enter sex (Male/Female/Other): ";
    cin >> sex;
    cout << "Enter marital status (Single/Married): ";
    cin >> maritalStatus;

    users.push_back({username, pass, bloodGroup, sex, maritalStatus, 0});
    saveUsers();
    cout << "Registration successful!\n";
    return true;
}

int loginUser()
{
    string username;
    int pass;
    cout << "Enter username: ";
    cin >> username;
    pass = password();

    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i].username == username && users[i].password == pass)
        {
            cout << "Login successful!\n";
            return i;
        }
    }
    cout << "Invalid credentials!\n";
    return -1;
}

vector<string> generateDeck()
{
    vector<string> deck;
    char types[] = {'A', 'B', 'C', 'D', 'E'};
    for (char type : types)
    {
        for (int i = 1; i <= 12; i++)
        {
            deck.push_back(string(1, type) + to_string(i));
        }
    }
    random_shuffle(deck.begin(), deck.end());
    return deck;
}

int getCardValue(string card)
{
    return stoi(card.substr(1));
}

char getCardType(string card)
{
    return card[0];
}

string getColoredCard(string card)
{
    char type = getCardType(card);
    string color;
    switch (type)
    {
    case 'A':
        color = RED;
        break;
    case 'B':
        color = GREEN;
        break;
    case 'C':
        color = YELLOW;
        break;
    case 'D':
        color = BLUE;
        break;
    case 'E':
        color = MAGENTA;
        break;
    default:
        color = RESET;
        break;
    }
    return color + card + RESET;
}

bool hasType(const vector<string> &player, char type)
{
    for (const auto &card : player)
    {
        if (getCardType(card) == type)
            return true;
    }
    return false;
}

int playCardGame()
{
    srand(time(0));
    vector<string> deck = generateDeck();
    vector<string> player(deck.begin(), deck.begin() + 6);
    vector<string> ai(deck.begin() + 6, deck.begin() + 12);

    int playerPoints = 0, aiPoints = 0;

    for (int i = 0; i < 6; i++)
    {
        cout << "\nYour remaining cards: ";
        for (auto card : player)
            cout << getColoredCard(card) << " ";
        cout << "\n";

        cout << "\nRound " << i + 1 << "\n";
        cout << "AI plays: " << getColoredCard(ai[i]) << "\n";

        char aiType = getCardType(ai[i]);
        int aiValue = getCardValue(ai[i]);

        cout << "Choose a card to play";
        if (hasType(player, aiType))
            cout << " of type " << aiType;
        cout << ": ";

        string chosenCard;
        bool validChoice = false;

        while (!validChoice)
        {
            cin >> chosenCard;
            auto it = find(player.begin(), player.end(), chosenCard);

            if (it != player.end())
            {
                if (getCardType(chosenCard) == aiType || !hasType(player, aiType))
                {
                    validChoice = true;
                    if (getCardValue(chosenCard) > aiValue)
                    {
                        cout << "You win this round!\n";
                        playerPoints++;
                    }
                    else
                    {
                        cout << "AI wins this round!\n";
                        aiPoints++;
                    }
                    player.erase(it);
                }
                else
                {
                    cout << "Invalid choice. Pick a valid " << aiType << " card: ";
                }
            }
            else
            {
                cout << "Invalid choice. Choose a card from your deck: ";
            }
        }
    }

    cout << "\nGame Over!\n";
    cout << "Your Points: " << playerPoints << "\n";
    cout << "AI Points: " << aiPoints << "\n";

    if (playerPoints > aiPoints)
    {
        cout << "You Win!\n";
        return 3;
    }
    else if (playerPoints < aiPoints)
    {
        cout << "AI Wins!\n";
        return 1;
    }
    else
    {
        cout << "It's a Tie!\n";
        return 2;
    }
}

int playKeyPressGame()
{
    int count = 0;
    cout << "Press any key to increase count. Counting for 5 seconds...\n";

    auto start = steady_clock::now();
    while (true)
    {
        auto now = steady_clock::now();
        double elapsed = duration<double>(now - start).count();
        if (elapsed >= 5.0) break;

        if (_kbhit())
        {
            _getch();
            count++;
            cout << "\rCount: " << count << "    ";
            cout.flush();
        }
    }

    cout << "\nTime's up! You pressed keys " << count << " times in 5 seconds.\n";
    srand(time(0));
    int randomInRange = 1 + rand() % 30;
    cout << "Random Number between 1 and 30: " << randomInRange << endl;

    if(randomInRange > count)
    {
        cout << "You win this round!\n";
        return 1;
    }
    else
    {
        cout << "You lost this round!\n";
        return 0;
    }
}

void tryAgain(string correct_sentence)
{
    string type;
    time_t start, end;
    cout << "Try again: ";
    time(&start);
    getline(cin, type);
    time(&end);

    double time_taken = difftime(end, start);
    if (type == correct_sentence)
    {
        cout << "Perfect!\n";
        cout << "Time taken: " << time_taken << " sec" << endl;
    }
    else
    {
        cout << "Still incorrect! Try again.\n";
        tryAgain(correct_sentence);
    }
}

void startTypingTest(vector<string> questions)
{
    int correct = 0;
    double total_time = 0.0;

    cin.ignore();

    for (int i = 0; i < questions.size(); i++)
    {
        string type;
        time_t start, end;

        cout << "\nQuestion " << i + 1 << ": " << questions[i] << endl;
        cout << "Type the sentence: ";

        time(&start);
        getline(cin, type);
        time(&end);

        double time_taken = difftime(end, start);
        total_time += time_taken;

        if (type == questions[i])
        {
            cout << "Perfect!\n";
            cout << "Time taken: " << time_taken << " sec" << endl;
            correct++;
        }
        else
        {
            cout << "Incorrect! ";
            tryAgain(questions[i]);
        }
    }

    cout << "\nTest Completed!" << endl;
    cout << "Accuracy: " << (correct * 100.0 / questions.size()) << "%" << endl;
    cout << "Total Time Taken: " << total_time << " seconds" << endl;
    cout << "Average Time per Question: " << total_time / questions.size() << " sec" << endl;
}

void easyTypingTest()
{
    startTypingTest(easy_questions);
}

void mediumTypingTest()
{
    startTypingTest(medium_questions);
}

void hardTypingTest()
{
    startTypingTest(hard_questions);
}

int playTypingTest()
{
    int level;
    cout << "Select difficulty level:\n";
    cout << "1. Easy\n2. Medium\n3. Hard\n";
    cout << "Enter choice: ";
    cin >> level;

    int pointsMultiplier = 1;
    switch(level)
    {
    case 1:
        easyTypingTest();
        pointsMultiplier = 1;
        break;
    case 2:
        mediumTypingTest();
        pointsMultiplier = 2;
        break;
    case 3:
        hardTypingTest();
        pointsMultiplier = 3;
        break;
    default:
        cout << "Invalid choice! Defaulting to easy.\n";
        easyTypingTest();
        pointsMultiplier = 1;
    }

    // Calculate points based on accuracy and difficulty
    int points = 5 * pointsMultiplier; // Simplified points calculation
    cout << "You earned " << points << " points!\n";
    return points;
}

void updateProfile(int userIndex)
{
    if (userIndex == -1) return;
    int choice;
    while (true)
    {
        cout << "\n[Profile Settings]" << endl;
        cout << "1. Change Password" << endl;
        cout << "2. Update Blood Group" << endl;
        cout << "3. Update Sex" << endl;
        cout << "4. Update Marital Status" << endl;
        cout << "5. View Game Points" << endl;
        cout << "6. Exit Profile Settings" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            clearScreen();
            users[userIndex].password = password();
        }
        else if (choice == 2)
        {
            clearScreen();
            cout << "Enter new blood group: ";
            cin >> users[userIndex].bloodGroup;
        }
        else if (choice == 3)
        {
            clearScreen();
            cout << "Enter new sex (Male/Female/Other): ";
            cin >> users[userIndex].sex;
        }
        else if (choice == 4)
        {
            clearScreen();
            cout << "Enter new marital status (Single/Married): ";
            cin >> users[userIndex].maritalStatus;
        }
        else if (choice == 5)
        {
            clearScreen();
            cout << "Your total game points: " << users[userIndex].gamePoints << endl;
        }
        else if (choice == 6)
        {
            clearScreen();
            break;
        }
        else
        {
            cout << "Invalid choice! Try again.\n";
        }
        saveUsers();
        cout << "Profile updated successfully!\n";
    }
}

void clearScreen()
{
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}

void printLargeNumber(int num)
{
    clearScreen();

    // Define attractive ANSI color codes (bold + bright colors)
    const string colors[] =
    {
        "\033[1;91m",  // Bright Red
        "\033[1;92m",  // Bright Green
        "\033[1;93m",  // Bright Yellow
        "\033[1;94m",  // Bright Blue
        "\033[1;95m",  // Bright Magenta
        "\033[1;96m",  // Bright Cyan
        "\033[1;97m",  // Bright White
        "\033[1;31m",  // Bold Red
        "\033[1;32m",  // Bold Green
        "\033[1;33m",  // Bold Yellow
        "\033[1;34m",  // Bold Blue
        "\033[1;35m",  // Bold Magenta
        "\033[1;36m"   // Bold Cyan
    };

    const string reset = "\033[0m";

    // Shuffle colors for variety
    srand(time(0));
    string shuffled_colors[sizeof(colors)/sizeof(colors[0])];
    copy(begin(colors), end(colors), begin(shuffled_colors));
    random_shuffle(begin(shuffled_colors), end(shuffled_colors));

    // Print the number with different colors for each line
    if (num == 3)
    {
        cout << shuffled_colors[0] << " ***** " << reset << "\n"
             << shuffled_colors[1] << "     * " << reset << "\n"
             << shuffled_colors[2] << "  **** " << reset << "\n"
             << shuffled_colors[3] << "     * " << reset << "\n"
             << shuffled_colors[4] << " ***** " << reset << "\n";
    }
    else if (num == 2)
    {
        cout << shuffled_colors[0] << " ***** " << reset << "\n"
             << shuffled_colors[1] << "     * " << reset << "\n"
             << shuffled_colors[2] << " ***** " << reset << "\n"
             << shuffled_colors[3] << " *     " << reset << "\n"
             << shuffled_colors[4] << " ***** " << reset << "\n";
    }
    else if (num == 1)
    {
        cout << shuffled_colors[0] << "   *   " << reset << "\n"
             << shuffled_colors[1] << "  **   " << reset << "\n"
             << shuffled_colors[2] << "   *   " << reset << "\n"
             << shuffled_colors[3] << "   *   " << reset << "\n"
             << shuffled_colors[4] << " ***** " << reset << "\n";
    }

}

void countdown()
{
    for (int i = 3; i >= 1; i--)
    {
        printLargeNumber(i);
        this_thread::sleep_for(seconds(1));
        clearScreen();
    }
}

void displayHangman(int a)
{
    vector<string> h =
    {
        "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
        "  +---+\n  |   |\n      |\n      |\n      |\n      |\n========="
    };
    cout << h[a] << endl;
}

bool isLetterPresent(char a, const string &b)
{
    return b.find(a) != string::npos;
}

void updateHiddenWord(char a, const string &b, string &c)
{
    for (int i = 0; i < b.size(); i++) if (b[i] == a) c[i] = a;
}
int playHangman()
{
    srand(time(0));
    int totalScore = 0;
    auto it = categories.begin();
    advance(it, rand() % categories.size());
    string category = it->first;
    const vector<pair<string, string>> &words = it->second;

    int randomIndex = rand() % words.size();
    string word = words[randomIndex].first;
    string hint = words[randomIndex].second;
    string hiddenWord(word.length(), '_');
    int attempts = 5, score = 100;
    map<char, int> guessedLetters;

    cout << "\n===============================" << endl;
    cout << "        HANGMAN GAME" << endl;
    cout << "===============================\n" << endl;
    cout << "Category: " << category << endl;
    cout << "Hint: " << hint << endl;
    cout << "Welcome to Hangman! Guess the word." << endl;

    while (attempts > 0)
    {
        cout << "\nAttempts remaining: " << attempts << " | Score: " << score << endl;
        displayHangman(attempts);
        cout << "Hidden word: " << hiddenWord << endl;
        cout << "Enter your guess: ";

        string input;
        cin >> input;

        if (input.length() != 1 || !isalpha(input[0]))
        {
            cout << "Invalid input! Enter a single letter." << endl;
            continue;
        }

        char guess = tolower(input[0]);

        if (guessedLetters[guess] >= 3)
        {
            cout << "You have exhausted 3 attempts for this letter! Try another one." << endl;
            continue;
        }

        guessedLetters[guess]++;

        if (isLetterPresent(guess, word))
        {
            updateHiddenWord(guess, word, hiddenWord);
            if (hiddenWord == word)
            {
                cout << "\nCongratulations! You guessed the word correctly: " << word << endl;
                totalScore += score;
                break;
            }
        }
        else
        {
            cout << "Incorrect guess!" << endl;
            attempts--;
            score = max(0, score - 10);
        }

        if (attempts == 0)
        {
            displayHangman(attempts);
            cout << "\nGame over! The word was: " << word << endl;
            break;
        }
    }

    cout << "Total Score: " << totalScore << endl;
    return totalScore;
}

int generateMathProblem(int difficulty)
{
    int num1, num2, answer, userAnswer;
    char operators[] = {'+', '-', '*', '/'};
    char op = operators[rand() % 4];

    if (difficulty == 1)
    {
        num1 = rand() % 10 + 1;
        num2 = rand() % 10 + 1;
    }
    else if (difficulty == 2)
    {
        num1 = rand() % 50 + 1;
        num2 = rand() % 50 + 1;
    }
    else
    {
        num1 = rand() % 100 + 1;
        num2 = rand() % 100 + 1;
    }

    if (op == '/' && num2 == 0) num2 = 1;

    switch (op)
    {
    case '+':
        answer = num1 + num2;
        break;
    case '-':
        answer = num1 - num2;
        break;
    case '*':
        answer = num1 * num2;
        break;
    case '/':
        answer = num1 / num2;
        break;
    }

    cout << "Solve: " << num1 << " " << op << " " << num2 << " = ";
    cin >> userAnswer;

    if (userAnswer == answer)
    {
        return 10 * difficulty;
    }
    else
    {
        cout << "Wrong! Correct answer: " << answer << endl;
        return 0;
    }
}

int playMathQuiz()
{
    vector<Player> leaderboard;
    string playerName;
    int difficulty;
    char playAgain;

    loadLeaderboard(leaderboard);

    cout << "==================================\n";
    cout << "     WELCOME TO THE MATH GAME!    \n";
    cout << "==================================\n";
    cout << "Solve as many problems as you can in 30 seconds!\n";

    cout << "Enter your name: ";
    cin >> playerName;

    do
    {
        cout << "Choose difficulty (1-Easy, 2-Medium, 3-Hard): ";
        cin >> difficulty;

        if (cin.fail() || difficulty < 1 || difficulty > 3)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter 1, 2, or 3.\n";
        }
    }
    while (difficulty < 1 || difficulty > 3);

    int score = 0;
    time_t startTime = time(0);
    while (time(0) - startTime < 30)
    {
        score += generateMathProblem(difficulty);
        cout << "Time left: " << 30 - (time(0) - startTime) << " seconds\n";
    }

    cout << "\nTime's up! Your score: " << score << " points\n";
    leaderboard.push_back({playerName, score});
    saveLeaderboard(leaderboard);
    displayLeaderboard(leaderboard);
    return score;
}

int playRockPaperScissors()
{
    clearScreen();
    cout << "===================================\n";
    cout << "WELCOME TO ROCK PAPER SCISSORS GAME\n";
    cout << "===================================\n";
    cout << "GAME RULES:\n!~~You Just Enter Your Choice Between(1,2,3)~~!\n\t\t\t&\n  !~~Computer Choice Random Between(1,2,3)~~!\n\n";

    int playerScore = 0, computerScore = 0, draws = 0;
    char playAgain;

    do
    {
        cout << "1. Rock\n2. Paper\n3. Scissors\n4. Quit\n";
        cout << "Enter your choice: ";
        int playerChoice;
        cin >> playerChoice;
        clearScreen();

        if (playerChoice == 4)
        {
            cout << "Score - You: " << playerScore << " | Computer: " << computerScore << " | Draws: " << draws << endl << endl;
            if (playerScore > computerScore)
            {
                cout << "Congratulations! You Are The Winner...!!" << endl;
            }
            else if (playerScore < computerScore)
            {
                cout << "Better Luck Next Time. Computer Is The Winner...!!" << endl;
            }
            else
            {
                cout << "The Game Was Drawn...Thanks For Playing!" << endl;
            }
            break;
        }

        if (playerChoice < 1 || playerChoice > 3)
        {
            cout << "Invalid choice! Try again.\n";
            continue;
        }

        int computerChoice = rand() % 3 + 1;

        auto getChoiceName = [](int choice)
        {
            if (choice == 1) return "Rock";
            if (choice == 2) return "Paper";
            return "Scissors";
        };

        cout << "You chose: " << getChoiceName(playerChoice) << endl;
        cout << "Computer chose: " << getChoiceName(computerChoice) << endl;

        if (playerChoice == computerChoice)
        {
            cout << "It's a draw!\n";
            draws++;
        }
        else if ((playerChoice == 1 && computerChoice == 3) ||
                 (playerChoice == 2 && computerChoice == 1) ||
                 (playerChoice == 3 && computerChoice == 2))
        {
            cout << "You win!\n";
            playerScore++;
        }
        else
        {
            cout << "Computer wins!\n";
            computerScore++;
        }

        cout << "Score - You: " << playerScore << " | Computer: " << computerScore << " | Draws: " << draws << endl << endl;

        cout << "Play again? (y/n): ";
        cin >> playAgain;
    }
    while (playAgain == 'y' || playAgain == 'Y');
    return playerScore;
}

int playGuessTheNumber()
{
    int difficulty;
    char playAgain;

    do
    {
        clearScreen();
        cout << "Welcome to 'Guess the Number' Game!\n\n";
        cout << "Select difficulty level:\n";
        cout << "1. Easy (1-100, 10 attempts)\n";
        cout << "2. Medium (1-500, 7 attempts)\n";
        cout << "3. Hard (1-1000, 5 attempts)\n\n";
        cout << "Enter your choice (1/2/3): ";
        cin >> difficulty;
        cout << endl;

        int range, maxAttempts;
        switch (difficulty)
        {
        case 1:
            range = 100;
            maxAttempts = 10;
            break;
        case 2:
            range = 500;
            maxAttempts = 7;
            break;
        case 3:
            range = 1000;
            maxAttempts = 5;
            break;
        default:
            cout << "Invalid choice! Exiting game.\n";
        }

        countdown();

        srand(time(0));
        int secretNumber = rand() % range + 1;
        int guess, attempts = 0;
        bool won = false;

        cout << "Guess the number between 1 and " << range << "!\n\n";

        while (attempts < maxAttempts)
        {
            cout << "Attempt " << attempts + 1 << " of " << maxAttempts << ": ";
            cin >> guess;

            if (guess < 1 || guess > range)
            {
                cout << "Invalid input! Enter 1-" << range << ".\n";
                continue;
            }

            attempts++;

            if (guess == secretNumber)
            {
                won = true;
                break;
            }
            else
            {
                int difference = abs(secretNumber - guess);
                int closenessThreshold = min(10, range / 10);

                if (difference <= closenessThreshold)
                {
                    cout << "Very close! ";
                }
                else
                {
                    cout << "Far away! ";
                }

                if (guess < secretNumber)
                {
                    cout << "Too low!\n";
                }
                else
                {
                    cout << "Too high!\n";
                }
            }
        }

        clearScreen();
        if (won)
        {
            int score = (maxAttempts - attempts + 1) * 10 * difficulty;
            cout << "Congratulations! Correct guess!\n";
            cout << "Your score: " << score << "\n";
            return score;
            // Update leaderboard
            vector<int> leaderboard;
            ifstream inFile("leaderboard.txt");
            if (inFile.is_open())
            {
                int score;
                while (inFile >> score) leaderboard.push_back(score);
                inFile.close();
            }

            leaderboard.push_back(score);
            sort(leaderboard.begin(), leaderboard.end(), greater<int>());

            ofstream outFile("leaderboard.txt");
            if (outFile.is_open())
            {
                cout << "\n===== Leaderboard =====\n";
                int count = 0;
                for (int s : leaderboard)
                {
                    cout << s << endl;
                    outFile << s << "\n";
                    if (++count == 5) break;
                }
                outFile.close();
            }
        }
        else
        {
            cout << "Game over! The number was " << secretNumber << ".\n";
            cout << "Better luck next time!\n";
        }

        cout << "Play again? (y/n): ";
        cin >> playAgain;
    }
    while (playAgain == 'y' || playAgain == 'Y');

}

void displayLeaderboard(vector<Player> &leaderboard)
{
    cout << "\n=== LEADERBOARD ===\n";
    sort(leaderboard.begin(), leaderboard.end(), [](Player a, Player b)
    {
        return a.score > b.score;
    });

    for (size_t i = 0; i < leaderboard.size(); i++)
    {
        cout << i + 1 << ". " << leaderboard[i].name << " - " << leaderboard[i].score << " points\n";
    }
    cout << "===================\n";
}

void loadLeaderboard(vector<Player> &leaderboard)
{
    ifstream file("leaderboard.txt");
    string name;
    int score;
    while (file >> name >> score)
    {
        leaderboard.push_back({name, score});
    }
    file.close();
}

void saveLeaderboard(const vector<Player> &leaderboard)
{
    ofstream file("leaderboard.txt");
    for (const auto &player : leaderboard)
    {
        file << player.name << " " << player.score << endl;
    }
    file.close();
}

int main()
{
    EnableColor();
    loadUsers();
    int choice, userIndex = -1;
    welcome();

    // Login/Register loop
    while (true)
    {
        cout << "1. Register\n2. Login\n3. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 1)
        {
            clearScreen();
            countdown();
            registerUser();
        }
        else if (choice == 2)
        {
            clearScreen();
            countdown();
            userIndex = loginUser();
            if (userIndex != -1) break;
        }
        else if (choice == 3)
        {
            clearScreen();
            return 0;
        }
        else
        {
            clearScreen();
            cout << "Invalid choice! Try again.\n";
        }
    }

    while (true)  // Main game menu
    {
        cout << "\n1. Play Card Game\n2. Play Key Press Game\n3. Play Typing Test\n";
        cout << "4. Play Hangman\n5. Play Math Quiz\n6. Play Rock Paper Scissors\n";
        cout << "7. Play Guess The Number\n8. Profile Settings\n9. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            clearScreen();
            countdown();
            int points = playCardGame();
            users[userIndex].gamePoints += points;
            saveUsers();
        }
        else if (choice == 2)
        {
            clearScreen();
            countdown();
            int points = playKeyPressGame();
            users[userIndex].gamePoints += points;
            saveUsers();
        }
        else if (choice == 3)
        {
            clearScreen();
            countdown();
            int points = playTypingTest();
            users[userIndex].gamePoints += points;
            saveUsers();
        }
        else if (choice == 4)
        {
            clearScreen();
            countdown();
            int points=playHangman();
            users[userIndex].gamePoints += points;
            saveUsers();
        }
        else if (choice == 5)
        {
            clearScreen();
            countdown();
            int points= playMathQuiz();
            users[userIndex].gamePoints += points;
            saveUsers();
        }
        else if (choice == 6)
        {
            clearScreen();
            countdown();
            int points=playRockPaperScissors();
            users[userIndex].gamePoints += points;
            saveUsers();
        }
        else if (choice == 7)
        {
            clearScreen();
            countdown();
            int points=playGuessTheNumber();
            users[userIndex].gamePoints += points;
            saveUsers();
        }
        else if (choice == 8)
        {
            clearScreen();
            updateProfile(userIndex);
        }
        else if (choice == 9)
        {
            clearScreen();
            cout << "Logging out...\n";
            break;
        }
        else
        {
            clearScreen();
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
