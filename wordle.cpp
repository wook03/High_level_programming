#include <iostream>
#include <cstdlib>
#include <ctime>

#include "std_lib_facilities.h"
using namespace std;

void menu();
void read_word();
void play_game();
string compare_word(string answer, string input_str);

int main(){
    menu();
}

void menu(){
    // 화면을 지우는 기능 구현

    // 화면 출력
    cout << "<<< WORDLE >>> " << endl;
    cout << "1. Dictionary " << endl;
    cout << "2. Game " << endl;
    cout << "3. Exit \n" << endl;
    
    
    int menu_number, dictionary_number, game_number;

    while(true){
        cout << "Choose an option (1-3): ";
        cin >> menu_number;
        switch (menu_number)
        {
        case 1:
            // dictionary menu
			main_menu:
            cout <<"\n[ DICTIONARY ]" << endl;
            cout << "1. Print " << endl;
            cout << "2. Return \n" << endl;
            
            while(true){
                cout << "Choose an option (1-2): ";
                cin >> dictionary_number;
                switch (dictionary_number)
                {
                case 1:
                    read_word();
					goto main_menu;
                case 2:
                    cout << endl;
                    menu();
                    return;
                default:
                    break;
                }
            }
        case 2:
            // game menu
			game:
            cout <<"\n[ Game ]" << endl;
            cout << "1. Play " << endl;
            cout << "2. Return \n" << endl;
            
            while(true){
                cout << "Choose an option (1-2): ";
                cin >> game_number;
                switch (game_number)
                {
                case 1:
					play_game();
					goto game;
                case 2:
                    cout << endl;
                    menu();
                    return;
                default:
                    break;
                }
            }
        case 3:
            // exit menu
            cout << endl <<"Good bye!!!"<<endl;
            return;
        default:
            break;
        }

    }
}

void read_word(){
    string filename="words.txt";
    ifstream ist {filename};
    
	if (!ist) error("can't open input file", filename);
    
	vector<string> dictionary;
	string word;
	while(ist >> word){
		dictionary.push_back(word);
	}
	int dictionary_size = dictionary.size();
	sort(dictionary.rbegin(), dictionary.rend());
	while (!dictionary.empty())
	{
		word=dictionary.back();
		dictionary.pop_back();
		cout << word <<endl;
	}
    cout << "\nA total words = " <<dictionary_size << " words are available." << endl;
	return;

}

void play_game(){
    string filename="words.txt";
    ifstream ist {filename};
    
	if (!ist) error("can't open input file", filename);
    
	vector<string> dictionary;
	string word;
	while(ist >> word){
		dictionary.push_back(word);
	}
	int dictionary_size = dictionary.size();

	int idx = randint(dictionary_size-1);
	string answer = dictionary[idx];
	
    bool result_flag = false;
    cout << "\nA new 5-letter word has been chosen radomly from the dictionary.\n\n";

    for (int i = 1 ; i <= 6 ; i++ ){
        cout << "["<<i<<"/6] Guess the word: ";
        string guess_word;
        cin  >> guess_word;

        string result  = compare_word(answer,guess_word);
        if (result == "*****"){
            result_flag = true;
            break;
        }
        cout << "==> " << result <<" \n\n";
    }

    if (result_flag == true){
        cout << "Congratulation!!! Your guess is correct.";
    }
    else cout << "Oops!!! Your lost all your chances. The correct answer is \""<< answer <<"\".";
	getchar();
	cin.ignore();
}

string compare_word(string answer, string input_str)
{
    string result;
    char check_char;
    string::size_type state_word;
	for ( int i = 0; i < input_str.size(); i++){
        check_char = input_str[i];
        state_word = answer.find(check_char);
        
        if (state_word == string::npos){
            result += "@";
        }
        else{
            if (answer[i]==check_char){
                result += "*";
            }
            else{
                result += "#";
            }
        }

    }

	return result;
    
}