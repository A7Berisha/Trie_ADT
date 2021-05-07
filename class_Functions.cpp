//Written by Andrew Berisha

#include <iostream>
#include <string>
#include "classes.hpp"


/////////////////////////////////////////////////////////////////////////////Trie Methods Start
// 
/////////////////////////////////////Trie Constructor starts
trie::trie(node* root_) {
	root = root_;
	size = 0;
	empty = 1;
}
////////////////////////////////////Trie Constructor Ends

////////////////////////////////////Trie Destructor Starts
trie::~trie() {
	delete return_root();
	change_root(nullptr);

}
////////////////////////////////////Trie Destructor Ends



///////////////////////////////////Return Root Method Starts
node* trie::return_root() {
	return(root);
}
//////////////////////////////////Return Root Method Ends


/////////////////////////////////Return Size Method Starts
unsigned int trie::return_size() {
	return(size);
}
/////////////////////////////////Return Size Method Ends


/////////////////////////////////Is Empty Method Starts
bool trie::is_empty() {
	return(empty); //Should return 1 if empty and 0 if not empty 
}
/////////////////////////////////Is Empty Method Ends


/////////////////////////////////Search method Starts
bool trie::search(std::string word_, node* parent_) {
	//Local Variables for current node, temporary string to be passed to next call of search() and the length of the current word
	node* current{ nullptr };
	std::string new_word{};
	unsigned int length{ static_cast<unsigned int>(word_.length()) };

	//Checking if we can assign current to be the specified child of parent, if we can then we will assign it, if not then return 0 bc the word is not in the trie
	if (parent_->return_child(static_cast<unsigned int>(word_[0]) - 97) != nullptr) {
		current = parent_->return_child(static_cast<unsigned int>(word_[0]) - 97);
	}
	else {
		return(0);
	}

	//Checking if we are at a terminal node and we are at the last letter in the original word, returns 1
	if (length == 1 && current->return_terminal() == 1) {
		return(1);
	}//Checking if we are at the last letter in the original word and we are not at a terminal node, returns 0 as we are not at a terminal node
	else if (length == 1 && current->return_terminal() == 0) {
		return(0);
	}//Checking if we are at a leaf node and we are not at the last letter, returns 0 since the word is not in the trie
	else if (current->return_has_children() == 0 && length != 1) {
		return(0);
	}

	//Resizing the word to eventually reach a word length of 1 with enough recursive calls
	new_word.resize((length) - 1);
	for (unsigned int t{ 1 }; t < length; t++) {
		new_word[t - 1] = word_[t];
	}
	//Calling search recursively
	return(search(new_word, current));

}
/////////////////////////////////Search method Ends


/////////////////////////////////Insert method Starts
bool trie::insert(std::string word_, node* parent_) {
	node* current{ nullptr };
	unsigned int letter{ static_cast<unsigned int>(word_[0]) - 97 };
	std::string new_word{};

	if (parent_->return_child(letter) == nullptr) {
		current = new node(letter, parent_);
		parent_->set_child(current, letter);
		parent_->change_has_children(1);
		if (return_root() == parent_) {
			change_empty(0);
		}
	}
	else if (parent_->return_child(letter) != nullptr) {
		current = parent_->return_child(letter);
	}

	if (word_.length() == 1) {
		change_size(return_size() + 1);
		current->change_terminal(1);
		return(1);
	}


	new_word.resize((word_.length()) - 1);
	for (unsigned int t{ 1 }; t < word_.length(); t++) {
		new_word[t-1] = word_[t];
	}
	return(insert(new_word, current));
}	
/////////////////////////////////Insert Method Ends


/////////////////////////////////Change Empty Property Method Starts
void trie::change_empty(bool change_val_) {
	empty = change_val_;
}
/////////////////////////////////Change Empty Property Method Ends


/////////////////////////////////Change Size Property Method Starts
void trie::change_size(unsigned int change_val_) {
	size = change_val_;
}
/////////////////////////////////Change Size Property Method Ends


////////////////////////////////////Trie clear trie Method Starts
void trie::clear(node* current_) {
	
	for (unsigned int t{ 0 }; t < 26; t++) {
		if (current_->return_child(t) != nullptr) {
			clear(current_->return_child(t));
		}
	}
	
	current_->change_has_children(0);

	if (current_->return_has_children() == 0 && current_ != return_root()) {
	current_->return_parent()->set_child(nullptr, current_->return_letter());
	current_->set_parent(nullptr);
	delete current_;
	}
	else if (current_ == return_root()) {
		change_size(0);
		if (return_root()->has_one_child() == 0) {
			return_root()->change_has_children(0);
			change_size(0);
		}
	}

}
////////////////////////////////////Trie clear trie Method Ends





///////////////////////////////////Erase Method Starts
bool trie::erase(std::string word_, node* deleting_) { 

	node* current{ nullptr };
	node* temp{ nullptr };
	unsigned int letter{ static_cast<unsigned int>(word_[word_.length()]) - 97 };


	if (deleting_ == return_root() && return_root()->has_one_child() == 1 && search(word_, return_root()) == 1) {
		current = traverse_end(word_, return_root());
		if (current->has_one_child() == 1) {
			current->change_terminal(0);
			return(1);
		}
	}
	else {
		current = deleting_;
	};


	if ((current->has_one_child() == 1 || current->return_terminal() == 1  && current->return_has_children() == 1) || (current == return_root() && current->has_one_child() == 0)) {
		if (current->has_one_child() == 1) {
			return(1);
		}
		else {
			current->change_has_children(0);
			return(1);
		}
	}
	else if(current == return_root() && return_root()->has_one_child() == 1) {
		return(1);
	}
	else {
		temp = current->return_parent();
		current->return_parent()->set_child(nullptr, current->return_letter()); //Setting the parent pointer pointing to child to be nullptr
		current->set_parent(nullptr); //Setting the pointer pointing to parent to be nullptr
		delete current;
		current = nullptr;
		return(erase(word_, temp));
	}

}
///////////////////////////////////Erase Method Ends



///////////////////////////////////Traverse End Starts
node* trie::traverse_end(std::string word_, node* parent_) {
	
	if (parent_ == nullptr) {
		return(nullptr);
	}

	unsigned int current_letter{ static_cast<unsigned int>(word_[0]) - 97 };
	node* current{ parent_->return_child(current_letter) };
	std::string next_word{ "" };
	
	if (current == nullptr) {
		return(nullptr);
	}

	if (current->return_letter() == current_letter && word_.length() == 1) {
		return(current);
	}
	else if (word_.length() != 1) {
		
		next_word.resize(word_.length() - 1);
		for (unsigned int t{ 1 }; t < word_.length(); t++) {
			next_word[t - 1] = word_[t];
		}
		

		return(traverse_end(next_word, current));
	}

}
///////////////////////////////////Traverse End Ends

///////////////////////////////////Print Starts
std::string trie::print(node* p_, std::string cumulative_) {
	std::string current_cumulative{ "" }; // The cumulative that will be passed on to the recursive print calls
	std::string final{ "" };


	if (p_ != return_root()) {
		cumulative_ += static_cast<char>(p_->return_letter() + 97);
		current_cumulative = cumulative_ ;
		if (p_->return_terminal() == 1) {
			final += current_cumulative;
			final += ' ';
		}
	}

	if (p_->return_has_children() == 1) {
		for (unsigned int t{ 0 }; t < 26; t++) {

			if (p_->return_child(t) != nullptr) {
				final += print(p_->return_child(t), current_cumulative);
			}

		}
	}

	return(final);

}
///////////////////////////////////Print Starts


///////////////////////////////////Autocomplete Starts
std::string trie::autocomplete(std::string word_) {
	
	node* prefix{ nullptr };
	std::string returnee{ "" };

	prefix = traverse_end(word_, return_root());
	
	if (prefix->return_terminal() == 1) {
		returnee += word_;
		returnee += ' ';
	}
	word_.pop_back();
	returnee = print(prefix, word_);

	returnee.pop_back();
	

	return(returnee);
}
///////////////////////////////////Autocomplete Ends

//Change Root Starts
void trie::change_root(node* p_) {
	root = p_;
}
//Change Root Ends

///////////////////////////////////////////////////////////////////////////Trie Methods End





//////////////////////////////////////////////////////////////////////////Node Methods Start


/////////////////////////////////Node Constructor Starts
node::node(unsigned int letter_, node* parent_){
	letter = letter_;
	parent = parent_;
	has_children = 0;
	terminal = 0;
	for (unsigned int t{ 0 }; t < 26; t++) {
		children[t] = nullptr;
	}
}
/////////////////////////////////Node Constructor Ends


/////////////////////////////////Return a pointer to a specified child Starts
node* node::return_child(unsigned int child_val) {
	return(children[child_val]);
}
/////////////////////////////////Return a pointer to a specified child Starts


/////////////////////////////////Has children (bool function) Starts
bool node::return_has_children() {
	return(has_children);
}
/////////////////////////////////Has children (bool function) Ends

/////////////////////////////////Set Parent Node Pointer Method Starts
void node::set_parent(node* parent_) {
	parent = parent_;
}
/////////////////////////////////Set Parent Node Pointer Method Ends


/////////////////////////////////Set Child Node Pointer Method Starts
void node::set_child(node* child_p, unsigned int child_val_) {
	children[child_val_] = child_p;
}
/////////////////////////////////Set Child Node Pointer Method Ends


/////////////////////////////////Set has_children Method (bool property) Starts
void node::change_has_children(bool change_val_) {
	has_children = change_val_;
}
/////////////////////////////////Set has_children Method (bool property) Ends


/////////////////////////////////Return Parent Node Starts
node* node::return_parent() {
	return(parent);
}
/////////////////////////////////Return Parent Node Ends


/////////////////////////////////Return terminal Starts
bool node::return_terminal() {
	return(terminal);
}
/////////////////////////////////Return Terminal Ends


/////////////////////////////////Change Terminal Starts
void node::change_terminal(bool change_val_) {
	terminal = change_val_;
}
/////////////////////////////////Change Terminal Ends


/////////////////////////////////Return node letter Starts
unsigned int node::return_letter() {
	return(letter);
}
/////////////////////////////////Return node letter Ends


/////////////////////////////////Has one child node Starts
bool node::has_one_child() {
	
	unsigned int counter{ 0 };

	for (unsigned int t{ 0 }; t < 26; t++) {
		if (return_child(t) != nullptr) {
			counter++;
		}
	}

	if (counter >= 1) {
		return(1);
	}
	else {
		return(0);
	}

}
/////////////////////////////////Has one child node Ends


/////////////////////////////////Has more than one child node Starts
bool node::has_more_than_one_child() {
	unsigned int counter{ 0 };

	for (unsigned int t{ 0 }; t < 26; t++) {
		if (return_child(t) != nullptr) {
			counter++;
		}
	}

	if (counter > 1) {
		return(1);
	}
	else {
		return(0);
	}
}
/////////////////////////////////Has more than one child node ends


//Node Constructor Starts
node::~node() {

	for (unsigned int t{ 0 }; t < 26; t++) {
		delete return_child(t);
		set_child(nullptr, t);
	}
	set_parent(nullptr);
}


//Node Constructor Ends


/////////////////////////////////////////////////////////////////////////Node Methods End


//////////////////////////////////////////////////////////////////////Illegal Exception Methods Start
illegal_exception::illegal_exception() {

};

//////////////////////////////////////////////////////////////////////Illegal Exception Methods Start