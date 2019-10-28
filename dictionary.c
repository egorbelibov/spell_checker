/****************************************************************************
 * dictionary.c
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include "dictionary.h"

/**
 * Global Variable(s)
 */
node *rootNode;
unsigned int wordCount = 0;


/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionaryName) {

  FILE *dictionaryFile = fopen(dictionaryName, "r");  
  if (dictionaryFile == NULL) {
    printf("Couldn't open: %s", dictionaryName);
    return false;
  }
 
  int wChar;
  int wCharIndex = 0;
  wordCount = 0;

  rootNode = createNewNode();
  node *lastNode = rootNode;

  while((wChar = fgetc(dictionaryFile)) != EOF) { 
    if (wChar != '\n') {
      updateCharIndex(&wCharIndex, wChar); 
      lastNode = insertNewChar(lastNode, wCharIndex);
    } else {
      lastNode->isWord = true;
      lastNode = rootNode;
      wordCount++;
    }
  }

  return true;

}

/**
 * Instantiates new node, allocates memory for it and returns it.
 */
node* createNewNode() {

  node *newNode = malloc(sizeof(node));
  if (newNode == NULL) {
    printf("Failed to allocate memory for --> newNode");
    return NULL;
  }

  newNode->isWord = false;
  for (int i = 0; i < CHILDREN_LENGTH; i++)
    newNode->children[i] = NULL;

  return newNode; 

}

/**
 * Updates int pointer (wCharIndex) based on char (wChar).
 * e.g. 'a' -> 0; 'B' -> 1; '\`' -> 26;
 */
void updateCharIndex(int *wCharIndex, int wChar) {

  if (isalpha(wChar)) {
    if (islower(wChar))
      *wCharIndex = wChar - 'a';
    else
      *wCharIndex = wChar - 'A';
  } else {
    if (wChar == '\'')
      *wCharIndex = 26; 
  }

}

/**
 * Inserts new char (index: 0-26) into last node, if it isn't there already.
 */
node* insertNewChar(node *lastNode, int index) {

  if (lastNode->children[index] == NULL)  {
    //printf("%c -> (CREATING NEW NODE)\n", index + 'a');
    lastNode->children[index] = createNewNode();
    if (lastNode->children[index] == NULL) {
      printf("Failed to allocate memory for -->lastNode->children[%i]<--", index);
      return NULL;
    }
    return lastNode->children[index];
  } else {
    //printf("%c -> (NODE EXISTS)\n", index + 'a');
    return lastNode->children[index];
  }

}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void) {

  return wordCount; 

}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word) {

  if (strlen(word) <= 0) {
    return false;
  }
  
  int wCharIndex = 0;
  node *currentNode = rootNode;
  while (*word) {
    updateCharIndex(&wCharIndex, *word); 
    currentNode = currentNode->children[wCharIndex];

    if (currentNode == NULL)
      return false;

    word++;
  }

  return currentNode->isWord;

}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void) {

  bool freeAll(node *nodeForCleanup);
  return freeAll(rootNode);

}

/**
 * Recursivelly frees node and it's children 
 */
bool freeAll(node *nodeForCleanup) {

  if (nodeForCleanup == NULL)  
    return true; 

  for (int i = 0; i < CHILDREN_LENGTH; i++) {
    if (nodeForCleanup->children[i])     
      freeAll(nodeForCleanup->children[i]);
  }

  free(nodeForCleanup);
  return true;

}
