# Trie_ADT
An implementation of a trie abstract data structure which can be used to store sequences of characters along with other functionality.

Commands:

i w - This command inserts a word into the trie, with 'w' being the word parameter (i.e. "i another" inserts the word "another" into the trie)

e w - This command erases a word from the trie with 'w' being the word parameter (i.e. "i another" would be removed from the trie if it was in the trie)

s w - This command searches for a word in the trie with 'w' being the word parameter (i.e. "s another" would search for the word "another")

print - This command prints all the words in the trie in alphabetical order.

autocomplete p - This command prints a list of all the words with the given prefix, with 'p' being the prefix parameter. (i.e. "autocomplete th" this would then list all the words in the trie that start with "th")

empty - This command checks if the trie is empty.

clear - This command erases all the words from the trie.

size - This command gives the number of words in the trie.

exit - This command is the last command that should be run to end the program.
