
#include "io.h"
#include "helpers.h"
#include "compression.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
void test_serialize_tree(){
    Letter* tree = malloc(sizeof(Letter));
    Letter* child1 = malloc(sizeof(Letter));
    Letter* child2 = malloc(sizeof(Letter));
    child1->right = NULL;
    child1->left = NULL;
    child1->letter = 'a';
    child2->right = NULL;
    child2->letter = 'b';
    child2->left = NULL;
    tree->left = child1;
    tree->right = child2;
    char* array = malloc(sizeof(char) * 4);
    char* letterArray = malloc(sizeof(char) * 3);
    int counter = 0;
    int lettercounter = 0;
    serialize_tree(tree, array, letterArray, &counter, &lettercounter);
    assert(array[0] == '0' && array[1] == '1' && array[2] == '1' && letterArray[0] == 'a' && letterArray[1] == 'b');

}

void test_create_new_node(){
    Letter* left = NULL;
    Letter* right = NULL;
    int weight = 3;
    Letter* node = create_new_node( left, right, weight);
    assert(node->weight == 3 && node->left == NULL && node->left == NULL);
    free(node);
}

void test_create_new_element(){
  Letter* left = NULL;
  Letter* right = NULL;
  int weight = 3;
  Letter* let = create_new_node( left, right, weight);
  LetterList* element = create_new_element(let, NULL);
  assert(element->let == let && element->next == NULL);
}

void test_insert_element(){
    Letter* let1 = create_new_node( NULL, NULL, 1);
    Letter* let2 = create_new_node( NULL, NULL, 3);
    Letter* letNew = create_new_node( NULL, NULL, 2);
    LetterList* element2 = create_new_element(let2, NULL);
    LetterList* element1 = create_new_element(let1, element2);
    LetterList* elementNew = create_new_element(letNew, NULL);
    insert_element(element1, elementNew);
    assert(element1->next->let == letNew);
    free(let1);
    free(let2);
    free(letNew);
    free(element1);
    free(element2);
    free(elementNew);
}
void test_generate_tree(){
    Letter* let1 = create_new_node( NULL, NULL, 1);
    Letter* let2 = create_new_node( NULL, NULL, 2);
    LetterList* element2 = create_new_element(let2, NULL);
    LetterList* element1 = create_new_element(let1, element2);
    int height = 0;
    Letter* result = generate_tree(element1, &height);
    assert(result->left->weight == 1 && result->right->weight == 2 && result->weight == 3 && height == 1);
}

void test_filter_zero_words(){
    Letter* weights = malloc(sizeof(Letter) * 3);
    Letter* finalWeights[3];
    weights[0].weight = 1;
    weights[1].weight = 0;
    weights[2].weight = 2;
    filter_zero_words(finalWeights, weights, 3);
    assert(finalWeights[0]->weight == 1 && finalWeights[1]->weight == 2);
    free(finalWeights[0]);
    free(finalWeights[1]);
    free(weights);
}

void test_initialize_letter_array(){
    Letter* weights = malloc(sizeof(Letter)*3);
    initialize_letter_array(weights);
    assert(weights[0].weight == 0 && weights[1].weight == 0 && weights[2].weight == 0);
    assert(weights[0].right == NULL && weights[1].right == NULL && weights[2].right == NULL);
    assert(weights[0].left == NULL && weights[1].left == NULL && weights[2].left == NULL);
}

void test_set_letters_array(){
    Letter* weights = malloc(sizeof(Letter) * MAX_CHARACTERS);
    char* word = malloc(sizeof(char) * 2);
    word[0] = 'a';
    word[1] = 'b';
    set_letters_array(weights, word, 2);
    assert(weights['a'].weight == 1 && weights['b'].weight == 1);
    free(weights);
    free(word);
}

void test_initialize_list(){
    Letter* weights = malloc(sizeof(Letter) * 4);
    Letter* finalWeights[4];
    weights[0].weight = 1;
    weights[1].weight = 0;
    weights[2].weight = 2;
    filter_zero_words(finalWeights, weights, 3);
    LetterList* result = initialize_list(finalWeights, 2);
    assert(result->let == finalWeights[0] && result->next->let == finalWeights[1]);
    free(result->next);
    free(result);
    free(weights);
}

void test_initialize_null(){
    char* array[3];
    int len = 3;
    initialize_null(array, len);
    assert(array[0] == NULL && array[1] == NULL && array[2] == NULL);
    // free(array);
}
void test_iterate_letters(){
    Letter* tree = malloc(sizeof(Letter));
    Letter* child1 = malloc(sizeof(Letter));
    Letter* child2 = malloc(sizeof(Letter));
    child1->right = NULL;
    child1->left = NULL;
    child1->letter = 'a';
    child2->right = NULL;
    child2->letter = 'b';
    child2->left = NULL;
    tree->left = child1;
    tree->right = child2;
    char* word = malloc(sizeof(char) * 3);
    word[0] = 'a';
    word[1] = 'b';
    char* result = iterate_letters(tree, 1, word, 2);
    assert(result[0] == '0' && result[1] == '1');
}
void test_get_letters(){
    char* word = malloc(sizeof(char) * 3);
    word[0] = 'a';
    word[1] = 'b'; 
    int height = 0;
    int letterCount = 0;
    Letter* result = get_letters(word, 2, &height, &letterCount);
    assert(result->left->letter == 'a' && result->right->letter == 'b' && height == 1 && letterCount == 2);
}

void test_count_nodes(){
    Letter* tree = malloc(sizeof(Letter));
    Letter* child1 = malloc(sizeof(Letter));
    Letter* child2 = malloc(sizeof(Letter));
    child1->right = NULL;
    child1->left = NULL;
    child2->right = NULL;
    child2->left = NULL;
    tree->left = child1;
    tree->right = child2;
    int result = count_nodes(tree);
    assert(result == 3);
}

void test_generate_code(){
    Letter* node = malloc(sizeof(Letter)); 
    node -> left = malloc(sizeof(Letter));
    node -> right = malloc(sizeof(Letter));
    node -> left -> right = NULL;
    node -> left -> left = NULL;
    node -> right -> right = NULL;
    node -> right -> left = NULL;
    node -> left -> letter = 'A';
    node -> right -> letter = 'B';
    char* arr = malloc(sizeof(char)*3);
    generate_code(node, 'A', arr, 0);
    assert(arr[0] =='0' );
}

int main(){
    test_serialize_tree();
    test_create_new_node();
    test_create_new_element();
    test_insert_element();
    test_generate_tree();
    test_filter_zero_words();
    test_initialize_letter_array();
    test_set_letters_array();
    test_initialize_list();
    test_initialize_null();
    test_iterate_letters();
    test_get_letters();
    test_count_nodes();
    test_generate_code();
}