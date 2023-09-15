// WORDLE
// Timothy Longo

#include <iostream>
#include <iomanip> // text formatting
#include <string>
#include <vector>
#include <fstream> // to read the dictionary.txt file
#include <Windows.h> // for Sleep() function needed for welcome and winner screens
#include <ctime> // to seed the srand() function for better random order
#include <algorithm> // used to find if element is in vector


using namespace std;


// globals
string THEWORD; // variable for the randomly selected word
vector <string> DICTIONARY; // every word read from the dictionary.txt file added here
vector <string> refinedList; // this is for all the words with n number of letters
vector <string> guessesVec; // every guessed word goes here
vector <char> greenKeys; // for DisplayKeyboard function
vector <char> yellowKeys; // ^
vector <char> blackKeys; // ^
int score;
int streak;
// declared in global space so everything has access to it, makes easy


void ScoreScreen() {

	cout << setw(20) << setfill('/') << "" << endl;
	cout << "/" << setw(18) << setfill(' ') << "" << "/" << endl;
	cout << "/  " << " SCORE: " << setw(8) << score << "/" << endl;
	cout << "/  " << "STREAK: " << setw(8) << streak << "/" << endl;
	cout << "/" << setw(18) << "" << "/" << endl;
	cout << setw(20) << setfill('/') << "" << endl;

}


void DisplayKeyboard(string guessedWord = " ") { // default parameter for when it's first called with zero words guessed
	cout << endl; // just for spacing
	// make vector of all letters in the alphabet, all lowercase for simplicity
	vector <char> QwertyAlphabet;
	QwertyAlphabet.push_back('q');
	QwertyAlphabet.push_back('w');
	QwertyAlphabet.push_back('e');
	QwertyAlphabet.push_back('r');
	QwertyAlphabet.push_back('t');
	QwertyAlphabet.push_back('y');
	QwertyAlphabet.push_back('u');
	QwertyAlphabet.push_back('i');
	QwertyAlphabet.push_back('o');
	QwertyAlphabet.push_back('p');
	QwertyAlphabet.push_back('a');
	QwertyAlphabet.push_back('s');
	QwertyAlphabet.push_back('d');
	QwertyAlphabet.push_back('f');
	QwertyAlphabet.push_back('g');
	QwertyAlphabet.push_back('h');
	QwertyAlphabet.push_back('j');
	QwertyAlphabet.push_back('k');
	QwertyAlphabet.push_back('l');
	QwertyAlphabet.push_back('z');
	QwertyAlphabet.push_back('x');
	QwertyAlphabet.push_back('c');
	QwertyAlphabet.push_back('v');
	QwertyAlphabet.push_back('b');
	QwertyAlphabet.push_back('n');
	QwertyAlphabet.push_back('m');

	// for green keys
	if (guessedWord != " ") {
		// if letter in guessedWord is in THEWORD, AND at correct position
		// add letter to greenKeys
		for (int i = 0; i < guessedWord.size(); ++i) {
			size_t found = THEWORD.find(guessedWord.at(i));
			if ((found != string::npos) && (guessedWord.at(i) == THEWORD.at(i))) {
				greenKeys.push_back(guessedWord.at(i));
			}
		}
	}

	// for yellow keys
	if (guessedWord != " ") {
		// if letter of guessedWord is IN THEWORD, and NOT at correct position
		// add letter to yellowKeys
		for (int i = 0; i < guessedWord.size(); ++i) {
			size_t found = THEWORD.find(guessedWord.at(i));
			if ((found != string::npos) && (guessedWord.at(i) != THEWORD.at(i))) {
				yellowKeys.push_back(guessedWord.at(i));
			}
		}
	}
	// for black keys
	if (guessedWord != " ") {
		// if letter in guessedWord is NOT in THEWORD at all
		// add letter to blackKeys
		for (int i = 0; i < guessedWord.size(); ++i) {
			size_t found = THEWORD.find(guessedWord.at(i));
			if (found == string::npos) {
				blackKeys.push_back(guessedWord.at(i));
			}
		}
	}
	// to display the keys
	for (int i = 0; i < QwertyAlphabet.size(); ++i) {
		if (i == 10) { // for spacing
			cout << endl;
			cout << " ";
		}
		if (i == 19) {
			cout << endl;
			cout << "  ";
		}
		if (find(greenKeys.begin(), greenKeys.end(), QwertyAlphabet.at(i)) != greenKeys.end()) {
			cout << "\x1B[92m" << " " << QwertyAlphabet.at(i) << " " << "\033[0m";
		}
		else if (find(yellowKeys.begin(), yellowKeys.end(), QwertyAlphabet.at(i)) != yellowKeys.end()) {
			cout << "\x1B[33m" << " " << QwertyAlphabet.at(i) << " " << "\033[0m";
		}
		else if (find(blackKeys.begin(), blackKeys.end(), QwertyAlphabet.at(i)) != blackKeys.end()) {
			cout << "\x1B[30m" << " " << QwertyAlphabet.at(i) << " " << "\033[0m";
		}
		else { // else show white key
			cout << " " << QwertyAlphabet.at(i) << " "; // white key, original display
		}
	}
	cout << endl; // for spacing
}


void InvalidInputScreen() {
	system("CLS");
	cout << setw(30) << setfill('\\') << "" << endl;
	cout << "\\" << setfill(' ') << setw(28) << "" << "\\" << endl;
	cout << "\\" << setfill(' ') << setw(28) << "" << "\\" << endl;
	cout << "\\" << setfill(' ') << setw(8) << "" << "\x1B[31mINVALID INPUT\033[0m" << setw(7) << "" << "\\" << endl;
	cout << "\\" << setfill(' ') << setw(28) << "" << "\\" << endl;
	cout << "\\" << setfill(' ') << setw(28) << "" << "\\" << endl;
	cout << setw(30) << setfill('\\') << "" << endl;
	Sleep(1000);
}


void DifficultyScreen() {

	system("CLS");
	cout << setw(30) << setfill('/') << "" << endl;
	cout << "/" << setw(28) << setfill(' ') << "" << "/" << endl;
	cout << "/" << setw(6) << "" << "\x1B[96m" << "SELECT DIFFICULTY" << "\033[0m" << setw(5) << "" << "/" << endl;
	cout << "/" << setw(28) << setfill(' ') << "" << "/" << endl;
	cout << "/" << setw(2) << "" << "[ 1 ]  " << "\x1b[92m" << "EASIEST" << "\033[0m" << setw(12) << "" << "/" << endl;
	cout << "/" << setw(2) << "" << "[ 2 ]  " << "\x1b[33m" << "EASIER" << "\033[0m" << setw(13) << "" << "/" << endl;
	cout << "/" << setw(2) << "" << "[ 3 ]  " << "DEFAULT" << setw(12) << "" << "/" << endl;
	cout << "/" << setw(2) << "" << "[ 4 ]  " << "\x1b[91m" << "HARD" << "\033[0m" << setw(15) << "" << "/" << endl;
	cout << "/" << setw(2) << "" << "[ 5 ]  " << "\x1b[31m" << "IMPOSSIBLE" << "\033[0m" << setw(9) << "" << "/" << endl;
	cout << "/" << setw(28) << setfill(' ') << "" << "/" << endl;
	cout << setw(30) << setfill('/') << "" << endl;

}


void LevelScreen() {

	system("CLS");
	cout << setw(30) << setfill('\\') << "" << endl;
	cout << "\\" << setw(28) << setfill(' ') << "" << "\\" << endl;
	cout << "\\" << setw(8) << "" << "\x1B[96m" << "SELECT LEVEL" << "\033[0m" << setw(8) << "" << "\\" << endl;
	cout << "\\" << setw(28) << setfill(' ') << "" << "\\" << endl;
	cout << "\\" << setw(6) << "" << "[ 4 ]  4-letters" << setw(6) << "" << "\\" << endl;
	cout << "\\" << setw(6) << "" << "[ 5 ]  5-letters" << setw(6) << "" << "\\" << endl;
	cout << "\\" << setw(6) << "" << "[ 6 ]  6-letters" << setw(6) << "" << "\\" << endl;
	cout << "\\" << setw(6) << "" << "[ 7 ]  7-letters" << setw(6) << "" << "\\" << endl;
	cout << "\\" << setw(28) << setfill(' ') << "" << "\\" << endl;
	cout << setw(30) << setfill('\\') << "" << endl;

}


void WelcomeScreen() {
	// simple welcome screen

	char slash = '/';
	char backSlash = '\\';

	vector <char> symbolsVec;

	symbolsVec.push_back(slash);
	symbolsVec.push_back(backSlash);
	symbolsVec.push_back(slash);
	symbolsVec.push_back(backSlash);


	for (unsigned int i = 0; i < symbolsVec.size(); ++i) {
		system("CLS");
		cout << setw(30) << setfill(symbolsVec.at(i)) << "" << endl;
		cout << symbolsVec.at(i) << setfill(' ') << setw(28) << "" << symbolsVec.at(i) << endl;
		cout << symbolsVec.at(i) << setfill(' ') << setw(28) << "" << symbolsVec.at(i) << endl;
		if (i == 0) {
			cout << symbolsVec.at(i) << setfill(' ') << setw(10) << "" << "\x1B[31mWELCOME\033[0m" << setw(11) << "" << symbolsVec.at(i) << endl;
		}
		else if (i == 1) {
			cout << symbolsVec.at(i) << setfill(' ') << setw(13) << "" << "\x1B[96mTO\033[0m" << setw(13) << "" << symbolsVec.at(i) << endl;
		}
		else if (i == 2) {
			cout << symbolsVec.at(i) << setfill(' ') << setw(11) << "" << "\x1B[92mWORDLE\033[0m" << setw(11) << "" << symbolsVec.at(i) << endl;
		}
		else {
			cout << symbolsVec.at(i) << setfill(' ') << setw(11) << "" << "\x1B[96mWORDLE\033[0m" << setw(11) << "" << symbolsVec.at(i) << endl;
		}
		cout << symbolsVec.at(i) << setfill(' ') << setw(28) << "" << symbolsVec.at(i) << endl;
		cout << symbolsVec.at(i) << setfill(' ') << setw(28) << "" << symbolsVec.at(i) << endl;
		cout << setw(30) << setfill(symbolsVec.at(i)) << "" << endl;
		Sleep(1000);
	}

}


void WinnerScreen() {

	streak += 1;
	if (guessesVec.size() == 1) {
		score = score + 1000000;
	}
	else if (guessesVec.size() == 2) {
		score = score + 100;
	}
	else if (guessesVec.size() == 3) {
		score = score + 25;
	}
	else if (guessesVec.size() == 4) {
		score = score + 10;
	}
	else if (guessesVec.size() == 5) {
		score = score + 5;
	}
	else {
		score = score + 1;
	}


	// displays the winning word
	char slash = '/';
	char backSlash = '\\';
	vector <char> slashVec;
	slashVec.push_back(slash);
	slashVec.push_back(backSlash);
	slashVec.push_back(slash);
	slashVec.push_back(backSlash);
	for (int i = 0; i < slashVec.size(); ++i) {
		system("CLS");
		cout << setw(20) << setfill(slashVec.at(i)) << "" << endl;
		cout << slashVec.at(i) << setw(18) << setfill(' ') << "" << slashVec.at(i) << endl;
		cout << slashVec.at(i) << "\x1B[92m" << setw(12) << setfill(' ') << right << THEWORD << setw(6) << setfill(' ') << left << "" << "\033[0m" << slashVec.at(i) << endl;
		cout << slashVec.at(i) << setw(18) << setfill(' ') << "" << slashVec.at(i) << endl;
		cout << setw(20) << setfill(slashVec.at(i)) << "" << endl;
		Sleep(1000);
	}
}


void LoserScreen() {

	score = 0;
	streak = 0;

	char slash = '/';
	char backSlash = '\\';
	vector <char> slashVec;
	slashVec.push_back(slash);
	slashVec.push_back(backSlash);
	slashVec.push_back(slash);
	slashVec.push_back(backSlash);
	slashVec.push_back(slash);
	slashVec.push_back(backSlash);

	for (int i = 0; i < slashVec.size(); ++i) {
		system("CLS");
		cout << setw(20) << setfill(slashVec.at(i)) << "" << endl;
		cout << slashVec.at(i) << setw(18) << setfill(' ') << "" << slashVec.at(i) << endl;
		if (i == 0) {
			cout << slashVec.at(i) << "\x1B[31m" << setw(12) << setfill(' ') << right << "GAME" << setw(6) << setfill(' ') << left << "" << "\033[0m" << slashVec.at(i) << endl;
		}
		else if (i == 1) {
			cout << slashVec.at(i) << "\x1B[31m" << setw(12) << setfill(' ') << right << "OVER" << setw(6) << setfill(' ') << left << "" << "\033[0m" << slashVec.at(i) << endl;
		}
		else if (i == 2) {
			cout << slashVec.at(i) << "\x1B[31m" << setw(14) << setfill(' ') << right << "WORD WAS" << setw(4) << setfill(' ') << left << "" << "\033[0m" << slashVec.at(i) << endl;
		}
		else {
			cout << slashVec.at(i) << "\x1B[31m" << setw(12) << setfill(' ') << right << THEWORD << setw(6) << setfill(' ') << left << "" << "\033[0m" << slashVec.at(i) << endl;
		}
		cout << slashVec.at(i) << setw(18) << setfill(' ') << "" << slashVec.at(i) << endl;
		cout << setw(20) << setfill(slashVec.at(i)) << "" << endl;
		Sleep(1000);
	}
}


void ShowBoxes(int num) {

	system("CLS");
	cout << endl;

	int outer_i = 0;
	// outer_i is to allow the functionaly of displaying vector index 0, then index 1, then index 2, so on and so forth
	// for every time it's called after a new entry is made


	if (guessesVec.size() != 0) { // this line avoids the error produced when searching for index 0 of a blank vector
		for (int i = 0; i < guessesVec.size(); ++i) {
			cout << string(5 * THEWORD.size(), '_') << endl;
			for (int i = 0; i < THEWORD.size(); ++i) {
				// initially checks the char in THEWORD
				size_t found = THEWORD.find(guessesVec.at(outer_i).at(i));
				if (guessesVec.at(outer_i).at(i) == THEWORD.at(i)) {
					// if you got a letter correct
					cout << "\x1B[92m [\033[0m" << guessesVec.at(outer_i).at(i) << "\x1B[92m] \033[0m";
				}
				else if ((found != string::npos) && !(guessesVec.at(outer_i).at(i) == THEWORD.at(i))) {
					// if the letter is in THEWORD, wrong position
					cout << "\x1B[33m (\033[0m" << guessesVec.at(outer_i).at(i) << "\x1B[33m) \033[0m";
				}
				else {
					// this is the default display for incorrect
					cout << "| " << guessesVec.at(outer_i).at(i) << " |";
				}
			}
			cout << endl;
			if (guessesVec.at(outer_i) == THEWORD) {
				cout << endl << "\x1B[92m    WINNER -- ROUND COMPLETE\033[0m\t\t" << endl;
				Sleep(2000);
				WinnerScreen();
				ScoreScreen();
			}
			outer_i += 1;

		}
		outer_i -= 1; // decrement outer_i AFTER the 'for' loop, since the very last increment is never made use of
	}

	for (int i = 0; i < num - guessesVec.size() + 1; ++i) { // + 1 for 6 rows if 5 was selected for easier difficulty
		if (guessesVec.size() != 0) {
			if (guessesVec.at(outer_i) == THEWORD) {
				break;
			}
		}
		cout << string(5 * THEWORD.size(), '_') << endl; // num here needs to be letter length
		for (int i = 0; i < THEWORD.size(); ++i) {
			cout << "|   |";
		}
		cout << endl;
	}

}


void MakeList(int number) {

	for (int i = 0; i < DICTIONARY.size(); ++i) { // iterate through every word of the dictionary vector
		if (DICTIONARY.at(i).size() == number) { // if the size of the word is equal to the number entered to play with
			refinedList.push_back(DICTIONARY.at(i)); // add that word to this new list of 'n' lettered words
		}
	}

	// assign THEWORD
	// from random index of newly refined list of words

	int randomIndexNumber = (rand() % refinedList.size()); // random number from 0 to the size of refined list of n lettered words
	THEWORD = refinedList.at(randomIndexNumber); // assigns the word to that random index of the list

}


void ReadDictionary() {

	ifstream reader; // declares reading variable of ifstream
	reader.open("C:\\Users\\Timmy\\Documents\\DICTIONARY.txt"); // opens file
	string word; // declares variable to store word, to add to vector

	if (reader.is_open()) {
		while (!reader.eof() && !reader.fail()) {
			reader >> word;
			DICTIONARY.push_back(word); // word added one-by-one to vector
		}
	}
	reader.close();

	// now we effectively transferred the .txt to a vector named DICTIONARY which is global
}


void Menu() {
	guessesVec.clear(); // clears for multipule rounds played
	refinedList.clear();
	greenKeys.clear();
	yellowKeys.clear();
	blackKeys.clear();


	// call difficulty screen first
	DifficultyScreen();
	int difficultyInput;
	cin >> difficultyInput;
	while (cin.fail() || difficultyInput < 1 || difficultyInput > 5) {
		cin.clear();
		cin.ignore(1000, '\n');
		InvalidInputScreen();
		DifficultyScreen();
		cin >> difficultyInput;
	}

	LevelScreen();
	int levelInput;
	cin >> levelInput;
	while (cin.fail() || levelInput < 4 || levelInput > 7) {
		cin.clear();
		cin.ignore(1000, '\n');
		InvalidInputScreen();
		LevelScreen();
		cin >> levelInput;
	}

	// difficulty decision branching
	int number;
	number = levelInput;

	if (difficultyInput == 1) {
		number = number + 2;
	}
	else if (difficultyInput == 2) {
		number = number + 1;
	}
	// if difficultyInput == 3 nothing needs to be done, 3 is DEFAULT
	else if (difficultyInput == 4) {
		number = number - 1;
	}
	else if (difficultyInput == 5) {
		number = number - 2;
	}

	MakeList(levelInput); // makes a list of (number) letterd words
	ShowBoxes(number); // displays the starting blank screen for the game
	// cout << THEWORD << endl; // for testing purposes
	DisplayKeyboard(); // shows white keyboard


	for (int i = 0; i < number + 1; ++i) { // for number of guesses, default for example is 6 guesses for 5 lettered word
		string guessedWord;
		cout << endl << ". . . Guess a word :" << endl;
		cin >> guessedWord;
		while (guessedWord.size() != THEWORD.size()) { // validates guessed word is in fact a 'n' lettered entry
			InvalidInputScreen();
			cin.ignore(10000, '\n'); // this is necessary to ignore all the characters after the first one that is checked
			ShowBoxes(number);
			DisplayKeyboard();
			cout << endl << ". . . Guess a word :" << endl;
			cin >> guessedWord;
		}
		
		// assigning the guessed word to all lower case
		for (int i = 0; i < guessedWord.size(); ++i) {
			guessedWord.at(i) = tolower(guessedWord.at(i));
		}

		// simple logic NOT to display keyboard after winning
		if (guessedWord != THEWORD) {
			guessesVec.push_back(guessedWord);
			ShowBoxes(number);
			DisplayKeyboard(guessedWord);
		}
		else {
			guessesVec.push_back(guessedWord);
			ShowBoxes(number);
		}

		if ((guessedWord != THEWORD) && (i == number)) { // if the last guessed word is incorrect, and 'i' is on the last iteration (after the last attempt)
			LoserScreen();
			ScoreScreen();
			cout << endl << "  Play again? Enter any key to contine. . ." << endl;
			cout << "    Enter 'q' to quit" << endl;
			string userIn;
			cin >> userIn;
			if (userIn.at(0) == 'q') {
				exit(0);
			}
			else {
				break;
			}
		}
		else if (guessedWord == THEWORD) { // if guessed correctly, first ShowBoxes calls WinnerScreen, then this is executed
			cout << endl << "  Play again? Enter any key to contine. . ." << endl;
			cout << "    Enter 'q' to quit" << endl;
			string userIn;
			cin >> userIn;
			if (userIn.at(0) == 'q') {
				exit(0);
			}
			else {
				break;
			}
		}
	}
}


int main() {

	srand(time(0));  // seeding the random function with the current time to simulate a better random order
	ReadDictionary(); // populates the vector from the .txt dictionary file
	WelcomeScreen();

	while (true) {
		Menu();
	}

	return 0;
}