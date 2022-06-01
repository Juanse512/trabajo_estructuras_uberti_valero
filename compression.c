
#include "io.h"
#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void serialize_tree(Letter* tree, char* array, char* letterArray, int* counter, int* lettercounter){
    if(!tree->left && !tree->right){
        array[*counter] = '1';
        letterArray[*lettercounter] = tree->letter;
        *counter = *counter + 1;
        *lettercounter = *lettercounter + 1;
    }else{
        array[*counter] = '0';
        *counter = *counter + 1;
        serialize_tree(tree->left, array, letterArray, counter, lettercounter);
        serialize_tree(tree->right, array, letterArray, counter, lettercounter);
    }
}

Letter* create_new_node(Letter* left, Letter* right, int weight){
    Letter* newNode = malloc(sizeof(Letter));
    newNode->left = left;
    newNode->right = right;
    newNode->weight = weight;
    return newNode;
}

LetterList* create_new_element(Letter* let, LetterList* next){
    LetterList* newElement = malloc(sizeof(LetterList));
    newElement->let = let;
    newElement->next = next;
    return newElement;
}


LetterList* insert_element(LetterList* list, LetterList* newElement){
    //  Si el elemento a ingresar es menor al primer elemento de la lista asigno como primer elemento al newElement
    //  y como siguiente de este elemento al viejo primer elemento de la lista
    if(list->let->weight > newElement->let->weight){
        newElement->next = list;
        list = newElement;
    }else{
        LetterList* current = list;
        int flag = 1;
        while(current && flag){
            //  Si el siguiente elemento es NULL significa que el newElement es mayor a todos los de la lista, por lo tanto lo ponemos al final
            if(current->next == NULL){
                current->next = newElement;
                flag = 0;
            }else{
                //  Revisamos si el peso del nuevo elemento es mayor al siguiente del actual, en caso verdadero ponemos el elemento entre el elemento actual y el siguiente
                if(current->next->let->weight > newElement->let->weight){
                    newElement->next = current->next;
                    current->next = newElement;
                    flag = 0;
                }
            }
            current = current->next;
        }
    }
    return list;
}

Letter* generate_tree(LetterList* list, int* height){
    Letter* tree = NULL;
    if(list){
        LetterList* current = list;
        LetterList* next = list->next;
        while(current && next){
            // Creamos un nuevo nodo con los 2 primeros elementos de la lista actual y el peso de la suma de ambos,
            // que son los menores, luego lo asignamos a un elemento de la lista y lo insertamos en la posicion correspondiente a su peso
            Letter* newNode = create_new_node(current->let, next->let, current->let->weight + next->let->weight);
            LetterList* newElement = create_new_element(newNode, NULL);
            LetterList* newCurrent = next->next;
            *height = *height + 1;
            if(newCurrent){
                newCurrent = insert_element(newCurrent, newElement);
            }else{
                //  Si solo queda un elemento en la lista este va a ser el nuevo elemento actual
                newCurrent = newElement; 
            }
            free(current);
            free(next); 
            current = newCurrent;
            next = current->next;
        }
        // Una vez que termine saco el elemento Letter del ultimo elemento de la lista enlazada, este contiene todo el arbol
        tree = current->let;
        free(current);
    }
    return tree;
}

void filter_zero_words(Letter* finalWeights[], Letter* weights, int charAmount){
    int counter = 0;
    for(int i = 0; i < MAX_CHARACTERS; i++){
        if(weights[i].weight != 0){
            finalWeights[counter] = malloc(sizeof(Letter));
            finalWeights[counter]->letter = weights[i].letter;
            finalWeights[counter]->weight = weights[i].weight;
            finalWeights[counter]->left = NULL;
            finalWeights[counter]->right = NULL;
            counter++; 
        }
    }
    return;
}

void initialize_letter_array(Letter* weights){
    for(int i = 0; i < MAX_CHARACTERS; i++){
            weights[i].weight = 0;
            weights[i].right = NULL;
            weights[i].left = NULL;
    }
}

int set_letters_array(Letter* weights, char* word, int wordlen){
    int charAmount = 0;
    for(int i = 0; i < wordlen; i++){
        // Le asignamos la letra y le sumamos uno al elemento Letter de la posicion del char
        weights[(unsigned char)word[i]].letter = word[i];
        if(weights[(unsigned char)word[i]].weight == 0){
            charAmount++;
        }
        weights[(unsigned char)word[i]].weight++;
    }
    return charAmount;
}

LetterList* initialize_list(Letter** finalWeights, int charAmount){
    LetterList* list = malloc(sizeof(LetterList));
    list->let = finalWeights[0];
    list->next = NULL;
    LetterList * current = list;
    // Iteramos sobre la lista y vamos creando nuevos LetterList y asignandole la Letter correspondiente
    for(int i = 1; i < charAmount; i++){
        LetterList * next = malloc(sizeof(LetterList));
        next->let = finalWeights[i];
        next->next = NULL;
        current->next = next;
        current = next; 
    }
    // Si solo hay una letra en el texto le asigno un nodo anterior para poder ejecutar el algoritmo correctamente
    if(list->next == NULL){
        LetterList* first = malloc(sizeof(LetterList));
        first->let = create_new_node(NULL, NULL, 0);
        first->let->letter = list->let->letter;
        first->next = list;
        list = first;
    }
    return list;
}

void initialize_null(char* array[], int len){
    for(int i = 0; i < len; i++){
        array[i] = NULL;
    }
}

int generate_code(Letter* node, char letter, char* arr, int counter){
    // Si estamos en una hoja y la letra es la adecuada devolvemos 1, si no -1
    if(!node->left && !node->right){
        if(node->letter == letter) return counter; else return -1;
    }
    // counterLeft y counterRight iteran a la izquierda y derecha respectivamente, una de ellas va a ser distinta a -1 ya que la letra
    // va a estar en alguna de sus ramas, le asignamos 0 o 1 al array en el contador actual dependiendo de la direccion de la recursion
    int counterLeft = generate_code(node->left, letter, arr, counter + 1);
    if(counterLeft != -1){
        arr[counter] = '0';
        return counterLeft;
    }
    int counterRight = generate_code(node->right, letter, arr, counter + 1);
    if(counterRight != -1){
        arr[counter] = '1';
        return counterRight;
    }
    return -1;
}


char* iterate_letters(Letter* tree, int height, char* word, int wordlen){
    char* coded = malloc(sizeof(char));
    int size = 0;
    char* DP[MAX_CHARACTERS];
    int sizeDP[MAX_CHARACTERS];
    initialize_null(DP, MAX_CHARACTERS);
    
    for(int i = 0; i < wordlen; i++){
        // Si no hay nada asignado en DP en la posicion dada por el char de la letra, llamamos a generate_code para que nos genere el codigo de la letra 
        // y guardarlo en esa posicion para evitar calcularla luego
        if(DP[(unsigned char)word[i]] == NULL){
            DP[(unsigned char)word[i]] = malloc(sizeof(char) * (height));
            int size = generate_code(tree, (unsigned char)word[i], DP[(unsigned char)word[i]], 0);
            sizeDP[(unsigned char)word[i]] = size;
        }
        
        size = concat_words(&coded, DP[(unsigned char)word[i]], size, sizeDP[(unsigned char)word[i]]);
    }
    // Liberamos la memoria de DP
    for(int i = 0; i < wordlen; i++){
        if(DP[(unsigned char)word[i]] != NULL){
            free(DP[(unsigned char)word[i]]);
            DP[(unsigned char)word[i]] = NULL;
        }
    }
    coded[size] = '\0';

    return coded;
}

Letter* get_letters(char* word, int wordlen, int* height, int* letterCount){
    Letter* weights;
    weights = malloc(sizeof(Letter) * MAX_CHARACTERS);
    
    initialize_letter_array(weights);
    
    int charAmount = set_letters_array(weights, word, wordlen);
    
    Letter* finalWeights[charAmount + 1];
    filter_zero_words(finalWeights, weights, charAmount);
    
    free(weights);

    quick_sort(finalWeights, 0, charAmount - 1);
    
    LetterList* initialElement = initialize_list(finalWeights, charAmount);
    
    Letter* tree = generate_tree(initialElement, height);
    
    *letterCount = charAmount;
    
    return tree;
}

int count_nodes(Letter* tree){
    if(tree == NULL) return 0;
    return 1 + count_nodes(tree->left) + count_nodes(tree->right); 
}

void compress(char* fileName){
    
    char* word;
    char* result;
    int wordLen, height = 0, treeNodes, counter = 0, letterCount = 0, lettercounter = 0;
    Letter* tree;

    char* outputFile = create_name(0, fileName, ".hf\0" );
    char* outputTreeFile = create_name(0, fileName, ".tree\0" );

    word = readfile(fileName, &wordLen);
    tree = get_letters(word, wordLen, &height, &letterCount);
    result = iterate_letters(tree, height, word, wordLen);
    treeNodes = count_nodes(tree);

    char* letters = malloc(sizeof(char) * (letterCount + 1));
    char* treeSerialized = malloc(sizeof(char) * (treeNodes + 1));
    
    serialize_tree(tree, treeSerialized, letters, &counter, &lettercounter);
    treeSerialized[counter] = '\n';
    
    concat_words(&treeSerialized, letters, (counter + 1), (letterCount + 1));
    
    int newLen = 0;
    char * implodedTree = implode(result, strlen(result), &newLen);
    
    writefile(outputFile, implodedTree, newLen);
    writefile(outputTreeFile, treeSerialized, (counter + letterCount + 1));
    printf("FILES CREATED\n");
    free(letters);
    free(treeSerialized);
    free(implodedTree);
    free_tree(tree);
    free(result);
    free(outputTreeFile);
    free(outputFile);
    free(word);
}
