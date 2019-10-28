/****************************************************************************
 * dictionary.h
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 45
#define CHILDREN_LENGTH 27

/**
 * Dictionary Node
 */
typedef struct node {
  bool isWord;  
  struct node *children[CHILDREN_LENGTH]; // 26 characters of the alphabet + apostrophe
} node;


/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char *dictionary);

/**
 *  Instantiates new node, allocates memory for it and returns it.
 */
node* createNewNode();

/**
 * Updates int pointer (wCharIndex) based on char (wChar).
 * e.g. 'a' -> 0; 'B' -> 1; '\`' -> 26;
 */
void updateCharIndex(int *wCharIndex, int wChar);

/**
 * Inserts new char (index: 0-26) into last node, if it isn't there already.
 */
node* insertNewChar(node *lastNode, int index);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

#endif // DICTIONARY_H
