/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node structure
struct TrieNode
{
    struct TrieNode *children[26];
    int count;
};

// Trie structure
struct Trie
{
    struct TrieNode *root;
};

// Function to create a new TrieNode
struct TrieNode *createTrieNode()
{
    struct TrieNode *newNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (newNode)
    {
        newNode->count = 0;
        for (int i = 0; i < 26; i++)
        {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    if (pTrie == NULL || word == NULL)
        return;

    struct TrieNode *current = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';
        if (current->children[index] == NULL)
            current->children[index] = createTrieNode();

        current = current->children[index];
    }

    current->count++;
}

// Helper function to recursively deallocate the trie nodes
void deallocateTrieHelper(struct TrieNode *node)
{
    if (node == NULL)
        return;

    for (int i = 0; i < 26; i++)
    {
        if (node->children[i] != NULL)
            deallocateTrieHelper(node->children[i]);
    }

    free(node);
}

// Deallocates the trie structure
void deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
        return;

    deallocateTrieHelper(pTrie->root);
    free(pTrie);
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *newTrie = (struct Trie *)malloc(sizeof(struct Trie));
    if (newTrie)
    {
        newTrie->root = createTrieNode();
    }
    return newTrie;
}

// Function to search for a word in the Trie and return the number of occurrences
int numberOfOccurrences(struct Trie *pTrie, char *word)
{
    if (pTrie == NULL || word == NULL)
        return 0;

    struct TrieNode *current = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';
        if (current->children[index] == NULL)
            return 0;

        current = current->children[index];
    }

    return current->count;
}

// Function to read words from a file and populate the array pInWords
// Returns the number of words read from the file
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening the file: %s\n", filename);
        return 0;
    }

    int numWords = 0;
    char word[256];

    while (fgets(word, sizeof(word), file) != NULL)
    {
        word[strcspn(word, "\n")] = '\0'; // Remove newline character if present
        pInWords[numWords] = strdup(word); // Copy the word to the array
        numWords++;
    }

    fclose(file);
    return numWords;
}

int main(void)
{
    char *inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }

    // Test words to check their occurrences
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }

    // Deallocate the Trie and free the memory
    deallocateTrie(pTrie);
    if (pTrie != NULL)
    {
        printf("There is an error in this program\n");
    }

    // Free the memory for each word in inWords array
    for (int i = 0; i < numWords; i++)
    {
        free(inWords[i]);
    }

    return 0;
}
