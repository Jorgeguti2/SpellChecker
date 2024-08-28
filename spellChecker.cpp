#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
using namespace std;

int main(int argc, char* argv[]){

	// Tests to make sure the correct arguments are passed in	
	if (argc < 3)
	{
		cout << "Please include input dictionary and input words file in param list.\n";
		cout << "Example:\n";
		cout << "     % spellChecker dictionary.txt words.txt\n";
		exit(EXIT_SUCCESS);
	}

	// Initializes word variable and vector for the words
	string word;
	vector<string> words;

	// Reads in the words.txt file into the vector
	ifstream fin;
	fin.open(argv[2]);
	while(fin >> word){
		words.push_back(word);
	}
	
	// Gets rid of all the special characters in words.txt except the ' and -
	regex punct("([^a-zA-Z0-9\'-])");
	for(int i=0; i<words.size(); i++)
	{
		words[i] = regex_replace(words[i], punct, "");
	}
	
	// Lowercases all letters in words.txt
	for(int i=0; i<words.size(); i++){
		transform(words[i].begin(), words[i].end(), words[i].begin(), ::tolower);
	}

	// intializes a set for dictionary with all lowercased
	set<string> dictionary;
	ifstream fin2;
	fin2.open(argv[1]);
	while(fin2 >> word){
		word[0] = tolower(word[0]);
		dictionary.insert(word);
	}

	// Initializes a map for the words that are not in the dictionary
	map<string, int> misspelled;

	// Checks which words are mispelled and adds them to the map, also keeping track of how many words are mispelled
	for(int i=0; i<words.size(); i++){
		// Checks to see how many apostrophes the word contains
		int count = 0;
		string test = words[i];
		for(int i = 0; i<test.size(); i++){
			if(ispunct(test[i]) and test[i] != '-'){
				count += 1;
			}
		}

		// Checks to see if the word is in the dictionary, if it starts with a letter, and if it has 0 or 1 apostrophe
		// If it is not in the dictionary, but fulfills the second two conditions, then it is added to misspelled map
		// Otherwise, nothing is done
		if(dictionary.find(words[i]) == dictionary.end() and (std::any_of(begin(words[i]), begin(words[i])+1, ::isalpha) and (std::any_of(end(words[i])-1, end(words[i]), ::isalpha)) and count < 2)) {
    			misspelled[words[i]] += 1;
		}
	}

	cout << "Words Misspelled: " << misspelled.size() << endl;

	for(auto itr = misspelled.begin(); itr!=misspelled.end(); itr++)
	{
		cout << itr->first << "\t- " <<itr->second << endl;;
 	} 

	return 0;

}

