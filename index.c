#include "FUNC.c"

int main(int argc, char** argv){

if(argc<2||strlen(argv[1])==0||strlen(argv[2])==0){
printf("Not Enough Arguments");
return -1;
}

//Try to open a file as a directory, if it is a directory, skip if statement to other case
//If it is a file, U is NULL and open the file in current directory for the inverted index
DIR* U = opendir(argv[2]);


if(access(argv[2],R_OK)==0&&U==NULL){
//Create XML IN . DIR
printf("ACCEESSED");
//Insert one file
char* FileName=malloc(3*sizeof(char));
FileName[0]='.';
FileName[1]='/';
FileName[2]='\0';
strcat(FileName,argv[2]);
//Create path to file name.
printf("FILE: %s",FileName);
Insert(FileName,FileName);
free(FileName);
FileName=NULL;
//Sort list of filenames and occurrences using merge sort.
O=MSort(&O);
//Print contents of sorted names and files.
PrintList(argv[1]);

char c = 'y';
//If the file to create can be accessed in root directory.
if(access(argv[1],R_OK)==0){
//Prompt the user if they want to overwrite the file.
printf("\nAre you sure you want to delete this file? Enter y for yes, anything else for no.\n");
scanf("%c",&c);
}
//If the user agrees, delete the file and rewrite XML format over the file.
if(c=='y'){

FILE* F = fopen(argv[1],"w+");
PutFile(F);
//Free file pointer.
if(F!=NULL){
fclose(F);
F=NULL;
}

}
//Delete contents of list.
//
DeleteList();
return 0;
}
else if(access(argv[2],R_OK)!=0){
//If there is no directory or file to open.
printf("\nNo file or directory to open.\n");
DeleteList();
return 0;
}
//If directory successfully opened, not a file, and close the directory.
closedir(U);
//Create paths to use on current directory, directory within directory, and files.
char* c = malloc(3*sizeof(char));
c[0]='.';
c[1]='/';
c[2]='\0';
//Create path to directory.
strcat(c,argv[2]);

char* P = malloc(2*sizeof(char));
P[0]='.';
P[1]='\0';

//Read the directory specified
ReadDir(P,c,false);
//Sort list of filenames and names lexicographically by name.
O=MSort(&O);
//Print contents of list.
PrintList(argv[1]);

//printf("\n FINALE \n");
char d = 'y';
//Check if the file to create already exists and promt the user if it does.
if(access(argv[1],R_OK)==0){
printf("\nAre you sure you want to delete this file? Enter y for yes, anything else for no.\n");
scanf("%c",&d);
}
//If the user agrees, or the file does not exist, then create new file and write XML format on list items into file.
if(d=='y'){
FILE* F = fopen(argv[1],"w+");
if(F==NULL){
printf("\nERROR, CANNOT OPEN FILE!\n");
DeleteList();
return 0;
}
//Function puts the necassary XML format into file.
PutFile(F);
//Close the file after it's opened.
if(F!=NULL){
fclose(F);
F=NULL;
}
}
//Delete contents of the list.
DeleteList();
return 0;
}
