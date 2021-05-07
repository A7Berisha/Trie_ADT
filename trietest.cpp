//Written by Andrew Berisha

#include <iostream>
#include <string>
#include "classes.hpp"

int main();
bool check_illegal(std::string word);

int main() {
	///////////////////////////////Variables Start
	std::string input{};
	bool go{ 1 };
	node* root(new node(99, nullptr)); //Root node made
	trie tree(root); //Trie Data Structure made
	///////////////////////////////Variables End

	while (go == 1) {
		input = "";
		go = 1;
		std::getline(std::cin, input);

		///////////////Insert command
		if (input[0] == 'i') {

			std::string word{};
			bool result{0};
			bool run{ 1 };

			//Copying the word from input to a string variable
			for (unsigned int t{ 2 }; input[t] != '\0'; t++) {
				word += input[t];
			}
			
			//Checking if there are any illegal characters or if the word is length = 0
			if (check_illegal(word) == 1) {
				try {
					throw illegal_exception();
				}
				catch(illegal_exception e){
					std::cout << "illegal argument" << std::endl;
					run = 0;
				}
			}

			if (run == 1) {
				result = tree.search(word, tree.return_root());

				//Searching for the word in the trie, if it is in the trie then we print 'failure'
				if (result == 1) {
					std::cout << "failure" << std::endl;
				} //If the word is not in the trie, then we can insert it and print 'success'
				else if (result == 0) {
					tree.insert(word, tree.return_root());
					std::cout << "success" << std::endl;
				}
			
			}


		}

		//////////////Search command
		else if (input[0] == 's' && input[1] != 'i') {
		
			std::string word{};
			unsigned int result{ 0 };
			bool run{ 1 };

			//Copying the word from input to a string variable
			for (unsigned int t{ 2 }; input[t] != '\0'; t++) {
				word += input[t];
			}

			//Checking if there are any illegal characters or if the word is length = 0
			if (check_illegal(word) == 1) {
				try {
					throw illegal_exception();
				}
				catch (illegal_exception e) {
					std::cout << "illegal argument" << std::endl;
					run = 0;
				}
			}

			if (run == 1) {
				result = tree.search(word, tree.return_root());

				if (result == 1) {
					std::cout << "found " << word << std::endl;
				}
				else if (result == 0) {
					std::cout << "not found" << std::endl;
				}
			}

		}


		//////////////Size command
		else if (input[0] == 's' && input[1] == 'i') {
			std::cout << "number of words is " <<tree.return_size() << std::endl;
		}

		//Empty command
		else if (input[0] == 'e' && input[1] == 'm') {
			
			if (tree.return_size() > 0) {
				std::cout << "empty 0" << std::endl;
			}
			else if (tree.return_size() == 0) {
			std::cout << "empty 1" << std::endl;
			}

		}

		//Exit command
		else if (input[0] == 'e' && input[1] == 'x') {
			go = 0;
		}


		//Erase Command
		else if (input[0] == 'e' && input[1] == ' ') {
			
			std::string word{};
			bool result{ 0 };
			bool run{ 1 };

			//Copying the word from input to a string variable
			for (unsigned int t{ 2 }; input[t] != '\0'; t++) {
				word += input[t];
			}

			//Checking if there are any illegal characters or if the word is length = 0
			if (check_illegal(word) == 1) {
				try {
					throw illegal_exception();
				}
				catch (illegal_exception e) {
					std::cout << "illegal argument" << std::endl;
					run = 0;
				}
			}

			if (run == 1) {
			
				result = tree.search(word, tree.return_root());

				if (result == 0 || tree.is_empty() == 1) {
					std::cout << "failure" << std::endl;
				}
				else if (result == 1) {
					tree.erase(word, tree.return_root());
					result = tree.search(word, tree.return_root());
					if (result == 0) {
						tree.change_size(tree.return_size() - 1);
						std::cout << "success" << std::endl;
					}
					else {
						std::cout << "failure" << std::endl;
					}
				}
			}
		}

		//Print Command
		else if (input[0] == 'p' && input[1] == 'r') {
		
			std::string printee{ "" };

			if (tree.return_size() > 0) {
				printee = tree.print(tree.return_root(), printee);
				printee.pop_back();
				std::cout << printee << std::endl;
			}
		}

		//Clear Command
		else if (input[0] == 'c') {
		
			if (tree.return_size() == 0) {
				std::cout << "success" << std::endl;
			}
			else if (tree.return_size() > 0) {
				tree.clear(tree.return_root());
				std::cout << "success" << std::endl;
			}

		}


		//Autocomplete Command
		else if (input[0] == 'a') {

			std::string prefix{ "\0" };
			unsigned int start_prefix{ 0 };
			std::string result{ "" };

			for (unsigned int t{ 0 }; input[t] != ' '; t++) {
				start_prefix = t;
			}


			start_prefix += 2;


			for (unsigned int t{ start_prefix }; input[t] != '*'; t++) {
				prefix += input[t];
			}


			if (prefix == "" && tree.return_size() > 0) {
				result = tree.print(tree.return_root(), "");
				result.pop_back();
				std::cout << result << std::endl;
			}
			else if (prefix != "" && tree.return_size() > 0) {
			
				if (tree.traverse_end(prefix, tree.return_root()) != nullptr) {
					std::cout << tree.autocomplete(prefix) << std::endl;
				}

			}

		}
	
	}

	tree.clear(root);
	delete root;
	root = nullptr;
	tree.change_root(nullptr);
	return 0;
}




//////////////////////////////////////////////Check for illegal arguement function starts
bool check_illegal(std::string word) {
	if (word == "" || word.length() == 0) {
		return(1); //Returns 1 if there is an illegal arguement
	}

	//Checking if the word has any illegal characters
	for (unsigned int t{ 0 }; t < word.length(); t++) {
		if (static_cast<unsigned int>(word[t]) < 97 || static_cast<unsigned int>(word[t]) > 122) {
			return(1);
		}
	}
	return(0);
}
//////////////////////////////////////////////Check for illegal arguement function Ends
