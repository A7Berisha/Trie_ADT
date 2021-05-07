//Written by Andrew Berisha

#include <string>
#include <iostream>



//////////////////////////////////////////////////////////////////////////////////////Node Class Starts
class node {

public:
	node(unsigned int letter_, node* parent_);
	~node();

	node* return_child(unsigned int child_val);
	void set_child(node* child_p, unsigned int child_val_);

	bool return_has_children();
	void change_has_children(bool change_val_);

	void set_parent(node* parent_);
	node* return_parent();

	bool return_terminal();
	void change_terminal(bool change_val_);

	bool has_one_child();
	bool has_more_than_one_child();

	unsigned int return_letter();

private:
	node* parent{ nullptr };
	node* children[26];
	unsigned int letter{ 0 };
	bool has_children{0};
	bool terminal{ 0 };
};
////////////////////////////////////////////////////////////////////////////////////Node Class Ends




//////////////////////////////////////////////////////////////////////////////////Trie Class Starts
class trie {

public:
	trie(node* root_);
	~trie();
	node* return_root();
	unsigned int return_size();
	bool is_empty();
	bool search(std::string word_, node* parent_);
	bool insert(std::string word_,node* parent_);
	void change_empty(bool change_val_);
	void change_size(unsigned int change_val_);
	void clear(node* current_);
	bool erase(std::string word_, node* deleting_);
	node* traverse_end(std::string word_, node* parent_);
	std::string print(node* p_, std::string cumulative_);
	std::string autocomplete(std::string word_);
	void change_root(node* p_);

private:

	node* root{nullptr};
	unsigned int size{ 0 };
	bool empty{ 1 };
};
//////////////////////////////////////////////////////////////////////////////////Trie Class Ends




//////////////////////////////////////////////////////////////////////////////////Illegal_Exception Class Starts
class illegal_exception {

public:
	illegal_exception();

};
/////////////////////////////////////////////////////////////////////////////////Illegal_Exception Class Ends