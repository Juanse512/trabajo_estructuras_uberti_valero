#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helpers.h"


void swap(Letter** weights, int pos1, int pos2 ){ 
    Letter* auxLetter;
    auxLetter = weights[pos1];
    weights[pos1] = weights[pos2];
    weights[pos2] = auxLetter;
}

int partition(Letter** array, int low, int high) {
  Letter* pivot = array[high];
  int i = (low - 1);
  for (int j = low; j < high; j++) {
    if (array[j]->weight <= pivot->weight) {
      i++;
      swap(array, i, j);
    }
  }
  swap(array, i + 1, high);
  return (i + 1);
}

void quick_sort(Letter** array, int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);
    quick_sort(array, low, pi - 1);
    quick_sort(array, pi + 1, high);
  }
}

void free_tree(Letter* tree){
    if(tree){
        free_tree(tree->left);
        free_tree(tree->right);
        free(tree);
        tree = NULL;
    }
}

int concat_words(char** final, char* newWord, int finalLen, int newWordLen){
    int newSize = finalLen + newWordLen;
    int counter = 0;
    *final = realloc(*final, (sizeof(char) * (newSize + 1)));
    char* finalArray = *final;
    for(int i = finalLen; i < newSize; i++){
        finalArray[i] = newWord[counter];
        counter++;
    }
    return newSize;
}

int concat_letter(char** final, char letter, int finalLen){
    int newSize = finalLen + 1;
    *final = realloc(*final, (sizeof(char) * (newSize + 1)));
    char* finalArray = *final;
    finalArray[newSize - 1] = letter;
    return newSize;
}

char* create_name(int position, char* string, char* textToAppend) {
    if (position != 0) string[strlen(string) - position] = '\0';
    int stringSize = strlen(string);
    int textSize = strlen(textToAppend) + 1;
    char* outputFile = malloc(sizeof(char) * (stringSize + textSize));
    strcpy(outputFile, string);
    strcat(outputFile, textToAppend);

    return outputFile;
}

