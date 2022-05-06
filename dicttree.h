
#define NUMOFCHARS 27 // valid characters are: a-z and '

class dictNode{
    public:
        bool isWord; // isWord flag that keeps track if the node is the last character of a word
        dictNode *next[NUMOFCHARS]; // array of all 
        dictNode();
        dictNode(bool isWordVal);

    bool add(const char *remainingChars, const char *wordBeingInserted); // adds a word into the dictionary tree

    dictNode* findEndingNodeOfAStr(const char *remainingStr, const char *strBeingSearched); // finds the node that contains the last character of the string being searched

    void countWordsStartingFromANode(int &count); // counts the number of words within the tree that starts from a node
};
