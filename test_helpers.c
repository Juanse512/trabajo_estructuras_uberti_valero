#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helpers.h"
#include <assert.h>

void test_swap(){ 
    Letter* weights[3];
    int pos1 = 0;
    int pos2 = 2;
    Letter* let1 = malloc(sizeof(Letter));
    let1->weight = 1;
    Letter* let2 = malloc(sizeof(Letter));
    let2->weight = 2;
    Letter* let3 = malloc(sizeof(Letter));
    let3->weight = 3;
    
    weights[0] = let1;
    weights[1] = let2;
    weights[2] = let3;
    
    swap(weights, pos1, pos2);
    assert(weights[0]->weight == let3->weight && weights[2]->weight == let1->weight);
    free(let1);
    free(let2);
    free(let3);
}

void test_quick_sort(){
  Letter* weights[3];
  Letter* let1 = malloc(sizeof(Letter));
  let1->weight = 1;
  Letter* let2 = malloc(sizeof(Letter));
  let2->weight = 2;
  Letter* let3 = malloc(sizeof(Letter));
  let3->weight = 3;
  
  weights[2] = let1;
  weights[1] = let2;
  weights[0] = let3;

  quick_sort(weights, 0, 2);
  assert(weights[0]->weight == 1 && weights[1]->weight == 2 && weights[2]->weight == 3);
  free(let1);
  free(let2);
  free(let3);
}

// free_tree testeado en valgind ;D

void test_concat_words(){
    char* final = malloc(sizeof(char) * 2);
    final[0] = 'a';
    final[1] = 'b';
    char* newWord = malloc(sizeof(char));
    newWord[0] = 'c';
    int finalLen = 2;
    int newWordLen = 1;
    concat_words(&final, newWord, finalLen, newWordLen);
    assert(final[0] == 'a' && final[1] == 'b' && final[2] == 'c');
    free(final);
    free(newWord);
}

void test_concat_letter(){
    char* final = malloc(sizeof(char) * 2);
    final[0] = 'a';
    final[1] = 'b';
    char letter = 'c';
    int finalLen = 2;
    concat_letter(&final, letter, finalLen);
    assert(final[0] == 'a' && final[1] == 'b' && final[2] == 'c');
    free(final);
}
void test_create_name() {
    char* string = malloc(sizeof(char) * 3);
    string[0] = 'a';
    string[1] = 'b';
    string[2] = '\0';
    char * result = create_name(0, string, "c");
    assert(result[0] == 'a' && result[1] == 'b' && result[2] == 'c');
    free(string);
}


int main(){
    test_swap();
    test_quick_sort();
    test_concat_words();
    test_concat_letter();
    test_create_name();
    
    return 0;
}