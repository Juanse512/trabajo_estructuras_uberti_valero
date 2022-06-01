#include "io.h"
#include "helpers.h"
#include "decompression.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void test_count_tree_size(){
    char* serializedTree = "010101\nabcd";
    int result = count_tree_size(serializedTree);
    assert(result == 6);
}

void test_separate_tree_from_words(){
    char* serializedTree = "011\nab"; 
    char* treeValue = malloc(sizeof(char) * 4);
    char* treeWords = malloc(sizeof(char) * 4);
    int treeLen = 6;
    separate_tree_from_words(serializedTree, treeValue, treeWords, treeLen);
    assert(treeValue[0] == '0' && treeValue[1] == '1' && treeValue[2] == '1'
    && treeWords[0] == 'a' && treeWords[1] == 'b');
}

void test_fill_tree(){
    char* treeValue = "011";
    char* letters = "ab";
    int counterTree = 0;
    int counterWords = 0;
    int treeSize = 3;
    Letter* result = fill_tree(treeValue, letters, &counterTree, &counterWords, treeSize);
    assert(result->left->letter == 'a' && result->right->letter == 'b');
    free_tree(result);
}

void test_get_letter_decode(){
    char* treeValue = "011";
    char* letters = "ab";
    int counterTree = 0;
    int counterWords = 0;
    int treeSize = 3;
    Letter* actualPos = fill_tree(treeValue, letters, &counterTree, &counterWords, treeSize);
    int index = 0;
    char* codedTexd = "0";
    char res = get_letter_decode(actualPos, &index, codedTexd);
    assert(res == 'a');
}

void test_decode_text(){
    char* treeValue = "011";
    char* letters = "ab";
    int counterTree = 0;
    int counterWords = 0;
    int treeSize = 3;
    Letter* tree = fill_tree(treeValue, letters, &counterTree, &counterWords, treeSize);
    
    char* codedTexd = "01";
    char* decodedTexd = malloc(sizeof(char) * 3);
    int resultLen = 0;
    int codedLen = 2;
    decode_text(tree, codedTexd, &decodedTexd, &resultLen, codedLen);
    assert(decodedTexd[0] == 'a' && decodedTexd[1] == 'b');
}


int main(){
    test_count_tree_size();
    test_separate_tree_from_words();
    test_fill_tree();
    test_get_letter_decode();
    test_decode_text();
}

