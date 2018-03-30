For my stringsorter.c program, first I created struct List which contains parameters entry, which is the node's word, entrySize, which is the size of the word, and struct List * next, which points to the next node in the list.

I used the function ReadDataS, which reads data from argument1 of argv[] in main and stores each valid word or letter into each free entry of a node in the list.

After storing all of the words and/or characters into the entries of the linked list, I implement MSort which groups all the nodes up by twos and if there is a odd node out, it is placed in the next group. The groups of two's become groups of fours which are compared, then they become groups of eights and so on ultil they return to the size of the original group. Once this is completed, all of the entries are sorted within O(mlogn) time, n is the amount of entries and m is the length of each entry. 

Then I implement PrintList, which takes argument Root node, which points to the first node in the linked list. Print list prints out all entries that are not NULL.
 
I also created boolean function isLetter, which takes a character argument and returns true if the character is an alphabetical letter, and false if the character is not. Another boolean function, isCap, takes a character argument and returns true if the character is a capital letter, and false if the character is not.

The final function that I implemented was called freeList, and it takes argument List*R, which is the first node of the list. I iterate through the list and free each previous list using a while loop, then I finally free the list which points to the final node. 
