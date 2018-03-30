#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>

//Linked list stores names of files, names of occurrences, and number of occurences of the names in the file.
typedef struct Occurrences_{
char* Name;
int Occurrence;
char* FileName;
struct Occurrences_* Next;
} Occurrences;

//Visited list stores the name of the file visited already.
typedef struct Visited_{

char* Name;

struct Visited_*Next;

}
Visited;

//Insert Directory, fileName, after filename is read.
void Insert(char* Dir, char* FileName);
//Prints the contents of the occurrence list.
void PrintList();
//Puts file information .
void PUT(FILE*F,int type, char* Name,int count);
//Deletes contents of the list.
void DeleteList();
//
//void PrevPath(char** C,int Next);
//Concaatenates a directory path to current path.
void CatDir(char* app,char** C);
//Concatenates a file path to current path.
void CatFile(char* app,char**C);
//Puts all required information into the XML encoded file.
void PutFile( FILE* F);
//Reads all directories to be opened by path name and indexes all files within those directories.
void ReadDir(char* P,char* P2,bool BASE);
//Converts char* argument to a copy of the string.
char* toString( char* C);
//Converts string to lower case.
void toLower(char** C);
//
//bool FileinDir(char* path);
//Count the occurrence(s) of a string within a string.
int countOcc(char* N, char** C);
//Increments the number of occurrences of a token if it is found within the file, otherwise returns 0 to indicate no occurrences are found.
int IncrOcc(Occurrences** OCC, char* W,char* F);
//
//Adds the filename to visited list.
void AddToVisited(Visited**V, char* entry);
//Checks if the file is already visited, returns true if so and false if not.
bool isVisited(Visited** V,char* entry);
//Frees all visited nodes in visited list.
void freeVisited(Visited**V);
//Checks every sub group of tokens in linked list and shuffles them so that they are in the correct order.
void AddAllOcc(Occurrences**O, char* entry);
//String compare 2.0, order of evaluation from highest to lowest: Uppercase letters, lowercase letters, numbers, dot, length of shortest string.
int strcmp2(char*s1, char*s2);
#define strcmp(X,Y) strcmp2((X),(Y))

//Merge sort function for list of filenames and names of occurrences.
Occurrences * MSort(Occurrences** top);
 ////Sorts pieces of the list and returns pointer to the sortedl list.
Occurrences * MG(Occurrences* O, Occurrences* P);
////Gets the middle or closest to middle node.
Occurrences * GM (Occurrences** H);
////

//Initialize the occurrences list.
Occurrences * O =NULL;

#endif
