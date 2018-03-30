#include "HEADER.h"

//Recursive function that reads through the the first path, Path, then if there is another diretory, it concatenates the current path to the new directory name, opens the directory in the next function, and reads through the next path specified.
void ReadDir(char* Path,char* Path2, bool BASE){

//DIR* pointer.
DIR* currentDir = NULL;
struct dirent* currentThing=NULL;
//dirent* pointer

//If path 2 exists, or not in BASE directory, open the directory of path2, which is another directory outside of the root directory.
if(strlen(Path2)>0||BASE==false){
currentDir= opendir(Path2);
//Check if the directory can be accessed.
if(access(Path2,R_OK)!=0){

//Free old path name if it is not NULL
if(Path!=NULL){
free(Path);
Path=NULL;
}
//Free old Path2 if it is not NULL
if(Path2!=NULL){
free(Path2);
Path2=NULL;
}

//Close the directory, finished checking if directory is openable.
closedir(currentDir);
return;
}
currentThing=NULL;
}

//If then the path 2 does not exist, then still within root directory.
else{
//Open the root directory.
currentDir= opendir(Path);
//Check if the root directory can be accessed.
if(access(Path,R_OK)!=0){

//Check if the root path name is not NULL, then erase root path name.
if(Path!=NULL){
free(Path);
Path=NULL;
}
//Check if the second path is not null(which should not happen), then free second path name in order to create a clean slate.
if(Path2!=NULL){
free(Path2);
Path2=NULL;
}
//Close the root directory when finished modifying path names.
closedir(currentDir);
return;
}
currentThing=NULL;
}

//Pointes used to store copies of Path and Path2 names.
char* i=NULL;
char* i2=NULL;

//Start of directory scanning function which searchdes for directories and files.
do{
//If the access of the directory is available, iterate through the current directory.
if(currentDir!=NULL)
currentThing=readdir(currentDir);
//If reading the directory failed, this is the end of the directory reading.
if(currentThing==NULL){
printf("\nEnd of directory reading\n");
break;
}
//If the item read from the directory is a file
if(currentThing->d_type==DT_REG){
//Have the current file name.
printf("\n %s \n",currentThing->d_name);
//If within the rot directory and found a file name
if(BASE==true){
//Free Path Name
//Check if the Path name still exists, free the path name to create just a path to the file
if(strlen(Path)>0&&Path!=NULL&&sizeof(Path)>0){
free(Path);
Path=NULL;
}

//Copy the name of the file to Path.
//To string will convert unfreeable const char array to a char* array copy that can be freed.
Path = toString(currentThing->d_name);

//Create a path stirng to append to the file name.
char* u = malloc(3*sizeof(char));
u[0]='.';
u[1]='/';
u[2]='\0';
//concatenate the path string to the file name within Path.
strcat(u,Path);
//Create path to directory (for the record).
i=toString(Path);
free(Path);
Path=NULL;
//Set path to u and delete unused ./ string.
Path=u;

//Check if the file can be accessed.
if(access(Path,R_OK)==0){
//Found an openable file
printf("\nOpenable file: %s\n",u);

//Create copies of path name file.
i2 = toString(Path);

//Insert the copy of the directory name: i2 and the path to filename: i2.
Insert(i, i2);

//free the copied directory and file path names
free(i);
i=NULL;
free(i2);
i2=NULL;
}
else{
//If cannot access the path to file, the file is unopenable.
printf("\nUnpenable file\n");
}
}
//If no longer within the root directory path.
else{
//Copy the filename into a char* array.
char* c = toString(currentThing->d_name);

//Create copy of directory path outside of root
i=toString(Path2);

//Create a char* pointer that creates: "/FileName".
char* u = NULL;
if(Path2[strlen(Path2)-1]!='/'){
u=malloc(2*sizeof(char));
u[0]='/';
u[1]='\0';
CatFile(u,&c);
}
//Concatenate a / to the path to file name outside of root in order to open a file outside of root.
strcat(Path2,c);
/////////////////// 
//If the file is found in the directory outside of root
if(access(Path2,R_OK)==0){
printf("\nReadable File... Using %s\n",Path2);
//Create a copy of the path to file.
i2 = toString(Path2);

//Insert copies of drectory and filename.
Insert(i, i2);
//free copies of irectory and filename.
free(i2);
i2=NULL;

}
else{
//Should never happen, file cannot be found after recovery
printf("\nUNABLE TO FIND FILE,ERROR\n");
break;
}
printf("\n FILE THAT IS NOT IN BASE: %s\n", Path2);
printf("NUMBER OF /:%d",countOcc("/",&Path2));

//Free the appendabe path to file copy.
free(c);
c=NULL;

free(Path2);
Path2=NULL;

//Copy the old path name and free the copy of old path name.
Path2=toString(i);
free(i);
i=NULL;
}
}


else if(currentThing->d_type==DT_DIR){
printf("\n%s\n",currentThing->d_name);
//When Hit next Dir outside of BASE
if(strcmp(currentThing->d_name,".")==0||strcmp(currentThing->d_name,"..")==0){
continue;
}

if(BASE==true){
//If within root and founr a directory, append path to directory using "/".
//Delete Path
char* s = toString(currentThing->d_name);

//Create new path to directory name.
strcat(Path2,s);
//free copy of the directory name.
free(s);
s=NULL;

printf("PATH2: %s",Path2);

//Check if the final character is not a "/", append "./" to the path to the directory within root.
if(Path2[strlen(Path2)-1]!='/'){

char* u = malloc(3*sizeof(char));
u[0]='.';
u[1]='/';
u[2]='\0';

strcat(u,Path2);
//Point to the completed path to dirctory from root.
}
//Call recursive function to read the next directory
ReadDir(toString(Path),toString(Path2),false);
}
//If not within root directory
else{
//Create copy of path to directory not in root.
i=toString(Path2);
//Copy the new directory not within root name.
char* c = toString(currentThing->d_name);


//Check if the final character is not a "/", append "./" to the path to the directory within root.
if(Path2[strlen(Path2)-1]!='/'){
char* u = malloc(2*sizeof(char));
u[0]='/';
u[1]='\0';
CatFile(u,&c);
}

//Check if the Path outside of directory is not NULL, which should always be true if found a new directory.
if(Path2!=NULL){
strcat(Path2,c);
free(c);
c=NULL;
}
else{
//Should never happen because Path2 will always be if a new directory outside of root is found.
printf("ERROR, PATH OUTSIDE OF ROOT IS LOST");
DeleteList();
exit(0);
}
printf("\n\nPATH 2: %s\n\n",Path2);
//Copies of path names to free current path names in current recursion.
//Read the directory of the next Path outside of the root directory.
ReadDir(toString(Path),toString(Path2),false);
//Return back to current path name in order to not have file conflicts where either a file is not found in the wrong directory, or a file with the same name is opened in the wrong directory.

free(Path2);
Path2=NULL;
//Copy old path name and free copy of old path name.
Path2=toString(i);
free(i);
i=NULL;
}
}
printf("\n\n");
}while(currentThing!=NULL);

//Final check, free all remaining data that has not been freed
if(i2!=NULL){
free(i2);
i2=NULL;
}
if(i!=NULL){
free(i);
i=NULL;
}

//Free all Path name copies within the recursion and base case.
if(Path!=NULL){
free(Path);
Path=NULL;
}
if(Path2!=NULL){
free(Path2);
Path2=NULL;
}

//Close directory within the recursion and base case.
closedir(currentDir);

return;
}

//Concatenation function, made to differentiate between contating a directory or concatenating a file
void CatDir(char* app, char** C){
if(C==NULL){
return;
}
if(*C==NULL){
return;
}
strcat(app,*C);

free(*C);

(*C)=NULL;

*C=app;

return;
}


//Concatenation function, made to differentiate between contating a directory or concatenating a file
void CatFile(char* app, char** C){
if(C==NULL){
return;
}
if(*C==NULL){
return;
}
strcat(app,(*C));

free(*C);

*C=NULL;

*C=app;

return;
}


//Creates copy of the string given
char* toString(char* C){
if(C==NULL){
return NULL;
}
char* v = malloc((strlen(C)+1)*sizeof(char));
bzero(v,strlen(C)+1);

int i=0;
char u = C[i];
while(u!='\0'){
v[i]=u;
i++;
u=C[i];
}

return v;
}

//Lowercases the entire string given.
void toLower(char** C){
if(C==NULL){
//Null pointer.
return;
}
int i=0;
while((*C)[i]!='\0'){
if(isalpha((*C)[i])){
(*C)[i]=tolower((*C)[i]);
}
i++;
}

return;
}

//Checks if the path to file is in the current direcory. Returns true if there is a match and false if not.
bool FileinDir(char* Path){
struct dirent* currentThing;
DIR* Directory = opendir(".");

do{
if(Directory!=NULL)
currentThing=readdir(Directory);
if(currentThing==NULL){
printf("\nDone Reading Directory\n");
break;
}
if(strcmp(currentThing->d_name,Path)==0&&currentThing->d_type==DT_REG){
printf("\n\nFOUND A MATCH!\n\n");
return true;
}
}while(currentThing!=NULL);

return false;
}

//Decreased string path to the previous path, required number of additional files or directories opened.

void PrevPath(char**C,int NextL){
int occ=0;
//int i=strlen(*C);
//printf("LENGTH: %d",i);
int j=0;

char* e = malloc(2*sizeof(char));
e[0] =(*C)[j];
e[1]='\0';
char* g=malloc(sizeof(char));
g[0]='\0';


while(e[0]!='\0'){
if(e[0]=='/'){
occ++;
}
if(occ==NextL){
//printf("\nFOUND THE LAST LINKER\n");
break;
}
strcat(g,e);
j++;
e[0]=(*C)[j];
}

free(*C);
*C=NULL;

*C=g;

free(e);
e=NULL;


return;
}

//Counts the occurrences of a given string within a given string.
int countOcc(char* n, char**C){
int j=0;
int k=0;

int count=0;
char c = (*C)[j];
while(c!='\0'){
//Increment k when the character within string matches the subsequent character within the occurrence string.
if(c==n[k]){
k++;
}
else{
k=0;
}
//K increments until reaches end of string to look for ocurrences.
if(n[k]=='\0'){
k=0;
count++;
}
j++;
c = (*C)[j];
}

return count;
}

//Insertion function takes directory name and filename.
void Insert(char* Dir, char* FileName){
//Dir and filename go hand in hand
char c = '/';
int i=0;

//Get path to only filename and no other path names involved.
char* e = strchr(FileName,c);
//int i=0;
while(countOcc("/",&e)>1){
e=strchr(e,strchr(e,c)[i]);
if(e[0]=='/'){
i=1;
}
else{
i++;
}
}
e=toString(strchr(e,c));
//Make string lowercase to compare to all other file names.

printf("\n\n\nFILE: %s FILENAME: %s\n\n\ns",e,FileName);

Occurrences** D =&O;

toLower(&e);

//Check if there is a duplicate file name within a different or same directory.
while(*D!=NULL){
char* d = (*D)->FileName;
toLower(&d);
if(strcmp(strchr(d,c),e)==0){
printf("\nDUPLICATE FILE\n");
break;
}
D=&((*D)->Next);
}

if(*D!=NULL){
//FOUND A DUPLICATE FILE
//Check if the filename to open matches the filename within the linked list.
if(strcmp((*D)->FileName,e)==0){
FILE* F = fopen(FileName,"r");
if(F==NULL){
printf("ERROR, CANNOT READ FILE");
return;
}
//Create char* apendable pointer.
char* app = malloc(2*sizeof(char));
app[0]=' ';
app[1]='\0';
//Create char* Word which will store each token.
char* Word = malloc(sizeof(char));
Word[0]='\0';
//Set size of word to 1.
int wordSize = 1;

bool isReadable = true;

//Check if the file opened ic ompletely readable, if not, boolean isReadable is false.
while(fscanf(F, "%c", &(app[0])) != EOF){
if((int)app[0]<0||(int)app[0]>126){
printf("\nError, file is not readable\n");
isReadable=false;
break;
}
}
//Close file opened.
fclose(F);
//If the file is readabe.
if(isReadable==true){

printf("\n File: %s is readable, reading...\n",FileName);
//OAttempt to open the file again, check if file cannot be opened.
F=fopen(FileName,"r");
if(F==NULL){
printf("Error, cannot open file");
return;
}

//Scan file opened and search for tokens to add to linked list of filenames, words, and number of occurrences of words.
while(fscanf(F, "%c", &(app[0])) != EOF){

printf("%c",app[0]);

//Check if the character is in the alphabet or is a number and find token pieces to append to app. 
if(isalpha(app[0])||isdigit(app[0])){
app[0]=tolower(app[0]);
//Increase capacity of Word.
Word=realloc(Word,2*sizeof(char));
Word[wordSize-1]='\0';
strcat(Word,app);
wordSize++;
//TOKENS
}
//If have not found a char, and the Word char* contains an actual token
else if(Word[0]!='\0'){
//FOUND A WORD
//char c = '/';
//Call function to increase the occurrences if the filename already exists within the linked lost, if the filename does not, then IncrOcc function will return 0 which will indicate that a new linked list pointer is to be created.
if(IncrOcc(&O,Word,e/*strrchr(strrchr(FileName,c),(strrchr(FileName,c)[1]))*/)==0){
//Found none, NEW WORD
//Go to end o linked list and then malloc size.
while(*D!=NULL){
D=&((*D)->Next);
}
//Create another entry in linked list of Occurrences.
(*D)=malloc(sizeof(Occurrences));
(*D)->Name=malloc(sizeof(char));
(*D)->Name[wordSize-1]='\0';
strcpy((*D)->Name,Word);
//Compress string to only contain filename and not the path information.
//char* d = FileName;//strrchr(strrchr(FileName,c),(strrchr(FileName,c)[1]));
(*D)->FileName=malloc(strlen(e+1)*sizeof(char));
(*D)->FileName[strlen(e)]='\0';

//Copy the filename to list filename char* pointer.
printf("\n\n\n\n FILE TO STRING: %s\n\n\n", e);
strcpy((*D)->FileName,e);
toLower(&((*D)->FileName));
//First Occurrences pointer for this filename, but not necessarily this word within all files opened.
(*D)->Occurrence=1;
(*D)->Next=NULL;

//Go to next list entry and contnue the process.
D=&((*D)->Next);
}

//Free the char* Word pointer and reset its length to 1.
free(Word);
Word=NULL;
Word = malloc(sizeof(char));
Word[0]='\0';
wordSize=1; 
}

}
}
//Case where the file does not contain all readable characters.
else{
printf("\n File: %s is not readable\n",FileName);
}

printf("\n\nEND FILE STREAM\n\n");

//Free pointers to Word tkens and append pointer
free(Word);
Word=NULL;
free(app);
app=NULL;
//Finished with file
fclose(F);
}

}

//Case where have not found the same file opened
else if(*D==NULL){
//New file found
printf("\nCREATE NEW LIST\n");
//Create a new list entry.

if(access(FileName,R_OK)==0){

printf("\nSEARCH FILENAME: %s IN DIRECTORY: %s\n",FileName,Dir);
//Try to open file.
FILE* F = fopen(FileName,"r");
if(F==NULL){
printf("ERROR, CANNOT READ FILE");
return;
}

//Create char* apendable pointer.
char* app = malloc(2*sizeof(char));
app[0]=' ';
app[1]='\0';

bool isReadable=true;

//Check if the file opened ic ompletely readable, if not, boolean isReadable is false.
while(fscanf(F, "%c", &(app[0])) != EOF){
if((int)app[0]<0||(int)app[0]>126){
printf("\nFile is not readable\n\n");
isReadable=false;
break;
}
}

//Close file opened.
fclose(F);

//Create char* Word which will store each token.
char* Word = malloc(sizeof(char));
Word[0]='\0';

//If the file is readabe.
if(isReadable==true){

printf("\n File: %s is readable, reading...\n",FileName);
//Attempt to open the file again, check if file cannot be opened.
F=fopen(FileName,"r");
if(F==NULL){
printf("ERROR, CANNOT READ FILE");
return;
}


int wordSize = 1;
//Scan file opened and search for tokens to add to linked list of filenames, words, and number of occurrences of words.
//
while(fscanf(F, "%c", &(app[0])) != EOF){


printf("%c",app[0]);

//Check if the character is in the alphabet or is a number and find token pieces to append to app. 
if(isalpha(app[0])||isdigit(app[0])){
app[0]=tolower(app[0]);
Word=realloc(Word,2*sizeof(char));
Word[wordSize-1]='\0';
strcat(Word,app);
wordSize++;
//TOKENZ
}
//If have not found a char, and the Word char* contains an actual token
else if(Word[0]!='\0'){
//Call function to increase the occurrences if the filename already exists within the linked lost, if the filename does not, then IncrOcc function will return 0 which will indicate that a new linked list pointer is to be created.
if(IncrOcc(&O,Word,e)==0){
//Found none, so found a new word, create new list entry
(*D)=malloc(sizeof(Occurrences));
(*D)->Name=malloc(sizeof(char));
(*D)->Name[wordSize-1]='\0';
strcpy((*D)->Name,Word);

//printf("\n\nSTRING PIECE: %s\n\n",e);

//printf("\n\n\n\n FILE TO STRING: %s\n\n\n", e);

(*D)->FileName=toString(e);

toLower(&((*D)->FileName));

//First Occurrences pointer for this filename, but not necessarily this word within all files opened.
(*D)->Occurrence=1;
(*D)->Next=NULL;
D=&((*D)->Next);

}

//Free the char* Word pointer and reset its length to 1.
free(Word);
Word=NULL;
Word = malloc(sizeof(char));
Word[0]='\0';
wordSize=1;
}
}

}
//Case where the file does not contain all readable characters.
else{
printf("\n File: %s is not readable\n",FileName);
}
printf("\n\nEND FILE STREAM\n\n");

//Free pointers to Word tkens and append pointer
free(Word);
Word=NULL;
free(app);
app=NULL;
//Finished with file
fclose(F);
}
//Case where there is no access to the file.
else{
printf("\nHAVE NO ACCESS TO FILE: %s\n",FileName);
}

}


printf("\nReturning with FILENAME: %s, Buffered FileName: %s\n",FileName,e);

if(e!=NULL){
free(e);
e=NULL;
}

return;
}

//strcmp2 is an extended version of strcmp which compares strings are returns them based on the order from least to greatest: Capital letters A->Z, lowercase letters a->z, numbers, ".", then by length.
int strcmp2(char* str1, char* str2){
if(str1==NULL||str2==NULL){
return 0;
}
char c = *str1;
char d = *str2;

int i=0;
int j=0;

//long long int pow = 10;

int HDist = 0;

bool digit=false;

while(c!='\0'&&d!='\0'){

if(isdigit(c)&&isdigit(d)){
digit=true;
}
else{
digit=false;
}

if(c=='.'&&d!='.'){
//first string should go last
return -1;
}
else if(c!='.'&&d=='.'){
//second string should go last
return 1;
}
else if(isdigit(c)&&!isdigit(d)){
//Comparing num to a char
return -1;
}
else if(!isdigit(c)&&isdigit(d)){
//Comparing num to a char
return 1;
}
if((int)c>(int)d&&!digit){
//first string should go last
//HDist--;
return -1;
}
else if ((int)c<(int)d&&!digit){
//second string should go last
//HDist++;
return 1;
}
else if(digit&&(int)c<(int)d&&strlen(str1)<strlen(str2)){
//1 vs 01

return 1;
}
else if(digit&&(int)c>(int)d&&strlen(str2)<strlen(str1)){
//01 vs 1

return -1;

}
else if(digit&&(int)c>(int)d&&strlen(str2)==strlen(str1)){
//11 vs 01

return -1;

}
else if(digit&&(int)c<(int)d&&strlen(str2)==strlen(str1)){
//01 vs 11

return 1;

}
//Equal chars
i++; c = str1[i];
j++; d = str2[j];
}

if(c=='\0'&&d!='\0'){
//end of first, d should go last
return 1;
}
else if(c!='\0'&&d=='\0'){
//end of second, c should go last
return -1;
}
//Final case. Have to be all equal chars
return HDist;
}


//Prints contents of the list.
void PrintList(char* arg1){

printf("\nPRINT LIST\n\n");
Occurrences** OCC =&O; 
while(*OCC!=NULL){
if((*OCC)!=NULL){
if((*OCC)->Name!=NULL){
printf("NAME: %s, IN FILE:%s ",(*OCC)->Name,(*OCC)->FileName);
}
}
printf("Number of Repeats: %d\n",(*OCC)->Occurrence);
OCC=&((*OCC)->Next);
}
}

//Deletes contents of the list.
void DeleteList(){

Occurrences* OCC;
Occurrences* OCC2; 

OCC = O;
while((OCC)!=NULL){
OCC2=((OCC)->Next);

if((OCC)->Name!=NULL){
free((OCC)->Name);
(OCC)->Name=NULL;
}

if((OCC)->FileName!=NULL){
free((OCC)->FileName);
(OCC)->FileName=NULL;
}

free((OCC));
(OCC)=NULL;

OCC=OCC2;
}

printf("Freed all of List");

return;
}

//Increment the occurrences of a word in a file within linked list, if the word exists, increment the occurrence. If the word does not, return 0;
int IncrOcc(Occurrences** OCC, char* Word,char* FileName){
int count=0;
//If same word is found, increment the occurrence!

toLower(&Word);
toLower(&FileName);

while(*OCC!=NULL){
if(strcmp((*OCC)->Name,Word)==0&&strcmp((*OCC)->FileName,FileName)==0){
//FOUND
(*OCC)->Occurrence++;
return (*OCC)->Occurrence;
//INCREMENTED BY ONE {WORD}
}
OCC=&((*OCC)->Next);
}
return count;
}

//Creates the XML formatted inverted index of all files opened, their words, and the count.
void PutFile(FILE*F){
//JUST A FILE

//Used to indicate if a name has been found and printed out with their respected file(s) and occurrences.
Visited * Vis =NULL;

int i=0;
//If the file is already visited, V is true, if not, V is false
bool V = false;
//Used as a helper variable to then call AddAllOcc.
bool Fix=false;

//Initialize list pointer to first node in list.
Occurrences** U = &O;
//Put into file the first two strings.
//<?xml version= "1.0" encoding="UTF-8"?>
PUT(F,1,NULL,0);
//<fileIndex>
PUT(F,2,NULL,0);

//Will be used to compare name to all list items with the same name. 
char* ALL;
//Used to go back to the origin and find the next name.
Occurrences** Back = &O;
//Loop through the list, keeping a pointer back to the next node.
while(*U!=NULL){
ALL = (*U)->Name;
Back=&((*U)->Next);

//If the number of visited nodes exceeds 0, check if the current name is visited.
//If the current name is not visited, set V to false, else set V to true and Fix to false.
if(i>0){
if(isVisited(&Vis,(*U)->Name)==false){
V=false;
}
else{
V=true;
Fix=false;
}
}

//If V is false, then found a new name to print the files the name exists in andthe occurrences of the name in the files.
if(V==false){
if(Fix==false){
//Helps print out the correct sorted order of files with the same name from the linked list, basically shuffles the contents of the list such that the next foun
//d file will be in the correct order.
AddAllOcc(U,(*U)->Name);
}
//Put the information about <name> into the file.

PUT(F,4,NULL,0);
PUT(F,6,(*U)->Name,(*U)->Occurrence);
}
//Continue putting the information about the files which contain the same name into the file in sorted order.
while((*U)!=NULL){

if(strcmp((*U)->Name,ALL)==0&&isVisited(&Vis,(*U)->Name)==false){

//Put <word text = ""> into file.
PUT(F,7,(*U)->Name,(*U)->Occurrence);
PUT(F,6,(*U)->FileName,(*U)->Occurrence);
//Put <file name=""> into file.
PUT(F,8,(*U)->FileName,(*U)->Occurrence);
PUT(F,9,(*U)->Name,(*U)->Occurrence);
//Put </file> into file.
}
U=&((*U)->Next);
}
//If the file was not visited, put </word> into the file.
if(V==false){
//Put </word> into file.
PUT(F,5,NULL,0);
}
//Append the visited name to the visited list.
AddToVisited(&Vis,ALL);
printf("\n\nVISITED COPIED: %s\n\n",ALL);
//Increment number of visited names.
i++;
//Go back to the next node of old U.
U=Back;
}
//Put </fileIndex> string into file.
PUT(F,3,NULL,0);
//Free visited list.
freeVisited(&Vis);

return;
}
//PUTS all information about XML encoding into file FILE* F.
void PUT(FILE*F, int type, char* Name, int count){
char* g = "<?xml version= \"1.0\" encoding=\"UTF-8\"?>";
char* f = "<fileIndex>";
char* h = "</fileIndex>";
char* k = "<word text =\"";
char* j = "</word>";
char* l = "<file name = \"";
char* m = "<";
char* n = "</file>";
char c = ' ';
c=g[0];
int i=0;

//PUT into file "<?xml version= \"1.0\" encoding=\"UTF-8\"?>".
if(type==1){
c=g[0];
i=0;
while(c!='\0'){
fputc(c,F);
i++;
c=g[i];
}
fputc('\n',F);
}
//Put into file "<fileIndex>".
else if(type==2){
c=f[0];
i=0;
while(c!='\0'){
fputc(c,F);
i++;
c=f[i];
}
}
//Put into file "</fileIndex>".
else if(type==3){
c=h[0];
i=0;
fputc('\n',F);
while(c!='\0'){
fputc(c,F);
i++;
c=h[i];
}
fputc('\n',F);
}
//Put into file "<word text =\"".
else if(type==4){
c=k[0];
i=0;

fputc('\n',F);

fputc('\t',F);

while(c!='\0'){
fputc(c,F);
i++;
c=k[i];
}
/*
 "<word text =\"";
char* j = "</word>";
char* l = "<file name = \"";
char* m = "<";
char* n = "</file>"
*/

}
//Put into file "</word>".
else if(type==5){
c=j[0];
i=0;
fputc('\n',F);
fputc('\t',F);

while(c!='\0'){
fputc(c,F);
i++;
c=j[i];
}
}
//Put into file the name of the token.
else if(type==6){
char c ='/';
char* e = strrchr(Name,(int)c);
if(e==NULL){
e=Name;
//printf("\nCompressed: %s\n",e);
}
c=e[0];
i=0;
//fputc('\"',F);
while(c!='\0'){
if(c!='/')
fputc(c,F);
i++;
//c=strrchr(strrchr(Name,(int)c),(strrchr(Name,(int)c)[1]))[i];
c=e[i];
}

fputc('\"',F);
fputc('>',F);

//free(e);
//e=NULL;
}
//Put into file "<file name = \"".
else if(type==7){
c=l[0];
i=0;

fputc('\n',F);
fputc('\t',F);
fputc('\t',F);

while(c!='\0'){
fputc(c,F);
i++;
c=l[i];
}
//fprintf(F,"%d",count);



}
//Put into file >count of occurrences<.
else if(type==8){
c=m[0];
i=0;

fprintf(F,"%d",count);

}
//Put into file </fileIndex>.
else if(type==9){
c=n[0];
i=0;

while(c!='\0'){
fputc(c,F);
i++;
c=n[i];
}
}
//
return;
}


//Recursive Merge Sort.
Occurrences* MSort(Occurrences** T){
//next
if(*T==NULL||(*T)->Next==NULL){
return (*T);
}
//Set Middle node which is the end of the first half of the separated lists.
Occurrences* M;// = malloc(sizeof(Occurrences));
M=GM(T);
//Second half of the separated lists is always set to the next node of middle.
Occurrences* SH;// = malloc(sizeof(Occurrences));
SH=M->Next; 
//Set M->next to NULL in order to end the first half of the lists, Second half of the lists already has a NULL at the end.
M->Next=NULL;
//Implement merge function which takes multiple halves of the list using the head and then the second half. First the nodes are separated until there are pairs and either 1 extra node or not, then these pairs are compared first, then they are connected and compared until the entire list is connected and the list is then sorted.

//DeleteList();
return MG(MSort(T),MSort(&SH));
//return NULL;
}

//Merge 
Occurrences* MG(Occurrences* O, Occurrences* P){
//Initialize nodes which point to the same address.

Occurrences * D = malloc(sizeof(Occurrences));
Occurrences * C;// = malloc(sizeof(Occurrences));
C=D;
//While Havent reached end of first and second half
while(O!=NULL&&P!=NULL){
//If the node entry of the first piece is equivalent or of less weight that the node entry of the second piece, set the next node of C to the first node. If the size of both pieces of the list are 1, then C would be NULL.
//Sort filenames in greatest to least importance order.
//Check if filenames contain same names, then sort by that name
if(strcmp((O)->FileName,(P)->FileName)<=0/*&&strcmp(O->Name,P->Name)<=0*//*strcmp((O)->FileName,(P)->FileName)<=0*/){

if(strcmp((O)->Name,(P)->Name)<=0){
//Within same name group, compare filenames
//Filename comparison within same name group
(C)->Next = P;
Occurrences* P1=P->Next;
P=P1;

}
else{
//Filename comparison within same name group
(C)->Next=O;
Occurrences* O1=O->Next;
O=O1;

}

}

//If node entry is of greater weight than the entry it is compared to, set C to the node that the first node is compared to. again, if the size of each piece is 1, C will be NULL.

else{ 
//If the filenames are not same, sort by name by default.
//Not same sort file names.

if(strcmp((O)->Name,(P)->Name)<=0){
//Filenames comparisons, filenames will go together
(C)->Next = P;

Occurrences* P1=P->Next;
 
P=P1;


}
else{
//If not similar/same filenames, go ahead.
(C)->Next=O;

Occurrences* O1=O->Next;

O=O1;

}


}
Occurrences* C1=C->Next;

if(C->Name==NULL||C->FileName==NULL){
free(C);
C=NULL;
}

C=C1;
}

//If the first node is NULL, then set the next node of C to P, otherwise, set the next node of C to O.
//Example case1:  
//		O->entry= "H"
//		P->entry= "h"
//		C->next->entry="h"
//		C->next->next->entry="H"
//		D->next->entry="H"
//
(C)->Next=(O==NULL) ? P:O;

//printf("\n\nCurrent is: %s\n\n",C->entry);
//Return the greater part of the block
return (D)->Next;
}

//Get middle node
Occurrences* GM(Occurrences** H){
if(*H==NULL){return *H;}
//Initialize a node which is located at the current head that goes to next node each iteration..
//Initialize node to head that goes to next next node each iteration.
//By the time the F node reaches end of list, S node will always be in the middle or appropriate location of the list in order to merge sort to work.
Occurrences** S;// = malloc(sizeof(Occurrences));
Occurrences** F;// = malloc(sizeof(Occurrences));
S=F=H;
//Iterate through list.
while((*F)->Next!=NULL&&(*F)->Next->Next!=NULL){
S=&((*S)->Next);
F=&((*F)->Next->Next);
}
//Return the Node which arrived at the middle.
return *S;
}

//Check within visited list if the file name is already visited, if so, return true, else return false.
bool isVisited(Visited**V,char* entry){
if(V==NULL){
return false;
}
while(*V!=NULL){
if(strcmp(entry,(*V)->Name)==0){
return true;
}
V=&((*V)->Next);
}
return false;
}

//Append another file name entry to the visited list.
void AddToVisited(Visited**V,char* entry){
if(V==NULL){
return;
}
while(*V!=NULL){
V=&((*V)->Next);
}
(*V)=malloc(sizeof(Visited));
(*V)->Name=malloc((strlen(entry)+1)*sizeof(char));
bzero((*V)->Name,strlen(entry)+1);
strcpy((*V)->Name,entry);
(*V)->Next=NULL;
return;
}

//Free all nodes within visited list.
void freeVisited(Visited**V){
if(V==NULL){
return;
}
Visited** V1;
while((*V)!=NULL){
V1=&((*V)->Next);
free((*V)->Name);
(*V)->Name=NULL;
free(*V);
*V=NULL;
V=V1;
}
return;
}


void AddAllOcc(Occurrences**O, char* entry){
//If names match, sort them out
if(O==NULL){
return;
}
if((*O)->Next!=NULL){
if(strcmp((*O)->Next->Name,entry)!=0){
return;
}
}

Occurrences** O2=NULL;

printf("\nReshuffle: %s\n",entry);

bool found = false;

while(*O!=NULL){
//Find group(s) of same names
O2=O;
while(*O2!=NULL){
if(strcmp((*O2)->Name,entry)==0){
found=true;
//Sort by highest occurrence first
if((*O)->Occurrence<(*O2)->Occurrence){
char* F = toString((*O2)->FileName);
int temp = (*O2)->Occurrence;
//Switch filenames and occurrences if the previous node occurrence is less than the current node occurrence.
char* F2 = toString((*O)->FileName);

free((*O)->FileName);
(*O)->FileName=NULL;

free((*O2)->FileName);
(*O2)->FileName=NULL;

(*O)->FileName=F;
(*O2)->FileName=F2;
(*O2)->Occurrence=(*O)->Occurrence;
(*O)->Occurrence=temp;
}
else if(strcmp((*O)->FileName,(*O2)->FileName)<=0&&(*O)->Occurrence==(*O2)->Occurrence){
//Switch filenames and occurrences if the previous filename is equivalent or greater than the current filename and the occurences are equal.

int temp = (*O2)->Occurrence;

char* F2 = toString((*O)->FileName);


free((*O)->FileName);
(*O)->FileName=NULL;
(*O)->FileName=toString((*O2)->FileName);

free((*O2)->FileName);
(*O2)->FileName=NULL;
(*O2)->FileName=F2;

(*O2)->Occurrence=(*O)->Occurrence;
(*O)->Occurrence=temp;

}
}
else{
if(found&&strcmp((*O)->Name,entry)!=0){
//Exit function, there are no other names to be searched for
return;
}
else{
//If not found and/or entry is still equal.
break;
}
}
O2=&((*O2)->Next);
}
O=&((*O)->Next);
}

return;
}
//Finished sorting each sub group of files within file names.

