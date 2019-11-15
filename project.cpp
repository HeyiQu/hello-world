/*
	Heyi Qu

	This project is working on finding common passwords 
	which are the most similar as the password user input, and print them out.
	Also count the different characters number.
*/

#include <iostream>
using std::cout; using std::endl; using std::cin;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <string>
using std::string;

#include <fstream>
using std::ifstream;

int main()
{
	ifstream file("common_passwords.txt");	//	read common_passwords.txt file
	vector<string> com_pas;		//	declear a vector to save common passwords from the text file
	map<string, int> sim;	//	declear a map for saving the most similar passwords
	string common;		//	declear a string

	//	save every common password from the file to com_pas vector
	while (file >> common) {
		com_pas.push_back(common);	//	com_pas insert common
	}

	string password;	//	declear a string 
	cout << "Give me a password: ";		//	cout information
	cin >> password;	//	get the user input
	cout << "You provided a password of " << password << endl;	//	put user input in the message

	//	compare the password in the com_pas with user input to find out the most similar passwords
	for (auto word : com_pas) {
		int count = 0;	//	initial the count value
		//	set the shorter value between the common password's size and user input's size
		int shorter = static_cast<int>(word.size()) < static_cast<int>(password.size()) ? static_cast<int>(word.size()) : static_cast<int>(password.size());
		for (int i = 0; i < static_cast<int>(password.size()); ++i) {
			if (i == shorter) break;
			if (password[i] == word[i]) ++count;

			int a = static_cast<int>(word.size()) - count;
			int b = static_cast<int>(password.size()) - count;
			sim[word] = abs(a) > abs(b) ? abs(a) : abs(b);
		}
	}

	//	cout information
	cout << "The most similar passwords to " << password << " are:" << endl;

	map<string, int>::iterator iter = sim.begin();	//	using iterator to go over sim
	vector<string> results;		//	declear a vector for recive results

	int min_value = 1000;	//	intial minimum value of the number of different characters
	for (; iter != sim.end(); iter++) {
		if (iter->second < min_value) min_value = iter->second;		//	check if the character is less than min_value
																	//	if yes, then replace the min_value
	}

	//	redeclear the iterator
	iter = sim.begin();
	for (; iter != sim.end(); iter++) {
		if (iter->second == min_value) results.push_back(iter->first);	//	find the most similar password, insert to results
	}

	//	output the most similar common passwords based on the user input
	for (auto ele : results) {
		cout << ele << ", ";
	}

	//	output the number of different characters
	cout << endl << "All of which are " << min_value << " character(s) different." << endl;

	file.close();	//	close the file

	//end program
	return 0;
}