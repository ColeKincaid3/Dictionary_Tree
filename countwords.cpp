#include "dicttree.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string.h>

using namespace std;

int main(int argc, char **argv){

    // check for too many arguments
    if (argc < 3){
        printf("Not enough command line arguments.");
        return 0;
    }

    // check for too little arguments
    if (argc > 3){
        printf("Too many command line arguments.");
        return 0;
    }

    // checks to see if the first file provided via command line is accessable
    if (access(argv[1], F_OK) != 0){
        cout << "object file not found" << endl;
        exit(1);
    }

    // checks to see if the second file provided via command line is accessable
    if (access(argv[2], F_OK) != 0){
        cout << "symbol table file not found" << endl;
        exit(1);
    }

    // creating the root of the tree and saving its address in addrRoot variable
    dictNode root;
    dictNode* addrRoot = &root;

    // opening dictionary source file to begin inserting words into the tree
    ifstream dictStream(argv[1]);
    string currDictLine;

    // delimiters used to seperate words that are read in from the 
    const char *delimeters = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
    
    // inserting each word from dictionary source file line by line
    while(getline(dictStream, currDictLine)){
        char* addrCurrDictLine = &currDictLine[0];
        char* word = strtok(addrCurrDictLine,delimeters);
        root.add(word, word);
        word = strtok(NULL,delimeters);
    }

    // closing dictionary source file stream
    dictStream.close();

    // opening the text file that has all of the words that will be cross reference to the dictionary tree
    ifstream textFile(argv[2]);
    string currTFLine; 

    // this section has two while loops, the outer loop makes sure that it gets every line from the input file, the inner loop makes sure every word on the current line is searched and counted
    while(getline(textFile, currTFLine)){
        char* addrCurrTFLine = &currTFLine[0]; 
        char* word = strtok(addrCurrTFLine, delimeters); 
        while(word != nullptr){ 
            int tempCounter = 0;
            dictNode* temp = root.findEndingNodeOfAStr(word,word); // finds the node in the dictionary that corresponds to the current words end
            temp->countWordsStartingFromANode(tempCounter); // takes node that is returned above and counts the amount of words within the dictionary that start with the current word
            printf("%s %d\n", word, tempCounter);
            word = strtok(NULL, delimeters);
        }
    }

    // closing textfile file stream
    textFile.close();

    return 0;
}
