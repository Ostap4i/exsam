#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

// Змінні для гри
const int MAX_TRIES = 6;
vector<string> words;

// Зчитує слова з файлу
void loadWords() {
    ifstream file("words.txt");
    if (!file.is_open()) {
        cerr << "Could not open word file." << endl;
        exit(1);
    }

    string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();
}

// Вибирає випадкове слово зі списку
string selectRandomWord() {
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

// Перевіряє, чи була введена буква вже
bool alreadyGuessed(const string& guessedLetters, char letter) {
    return guessedLetters.find(letter) != string::npos;
}

// Очищає екран
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}



int main()
{
    srand(time(0));
    loadWords();

    string secretWord = selectRandomWord();
    string guessedWord(secretWord.length(), '_');
    string guessedLetters = "";
    int attempts = 0;
    time_t startTime = time(nullptr);

    while (true) {
        clearScreen();
        cout << "Guess the word: " << guessedWord << endl;
        cout << "Attempts " << attempts << "/" << MAX_TRIES << endl;
        cout << "Letters entered " << guessedLetters << endl;

        if (secretWord == guessedWord) {
            cout << "You won! Word: " << secretWord << endl;
            break;
        }
        else if (attempts == MAX_TRIES) {
            cout << "You lost! The word was: " << secretWord << endl;
            break;
        }

        cout << "Ener the voard ";
        char letter;
        cin >> letter;

        if (alreadyGuessed(guessedLetters, letter)) {
            cout << "You have already typed that letter." << endl;
            continue;
        }

        guessedLetters += letter;

        if (secretWord.find(letter) != string::npos) {
            for (int i = 0; i < secretWord.length(); i++) {
                if (secretWord[i] == letter) {
                    guessedWord[i] = letter;
                }
            }
        }
        else {
            attempts++;
        }
    }

    time_t endTime = time(nullptr);
    int gameTime = endTime - startTime;

    cout << "Game Statistics:" << endl;
    cout << "Amount of time: " << gameTime << " sek" << endl;
    cout << "Number of attempts:" << attempts << endl;
    cout << "Searched word: " << secretWord << endl;
    cout << "Player Letters: " << guessedLetters << endl;

    return 0;
}

