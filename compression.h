#ifndef __HUFF_COMPRESSION_H_
#define __HUFF_COMPRESSION_H_
#include "helpers.h"

/* 
    serialize_tree: (Letter*, char*, char*, int*, int*) -> ()
    serialize_tree serializa el arbol, si el nodo en el que estoy parado es una hoja, pone un 1 en array y guarda la letra del nodo en el letterArray, si no coloca un 0
 */
void serialize_tree(Letter* tree, char* array, char* letterArray, int* counter, int* lettercounter);

/* 
    create_new_node: (Letter*, Letter*, int) -> Letter*
    create_new_node crea un nuevo nodo para un arbol binario de tipo Letter dados nodos hijos y peso 
 */
Letter* create_new_node(Letter* left, Letter* right, int weight);

/* 
    create_new_element: (Letter*, LetterList*) -> LetterList*
    create_new_element crea un nuevo elemento para una lista enlazada de tipo LetterList con un nuevo elemento y el nodo siguiente 
 */
LetterList* create_new_element(Letter* let, LetterList* next);


/* 
    insert_element: (LetterList*, LetterList*) -> LetterList*
    insert_element agrega un nuevo elemento a una lista enlazada del tipo LetterList en su posicion correspondiente segun el peso
 */
LetterList* insert_element(LetterList* list, LetterList* newElement);

/* 
    generate_tree: (LetterList*, int*) -> Letter*
    Crea un arbol del tipo Letter dada una lista de elementos del tipo LetterList guardando la altura del arbol en el puntero height
 */
Letter* generate_tree(LetterList* list, int* height);

/*  
    filter_zero_words: (Letter*, Letter*, int) -> ()
    Dada un array que contiene a todos los caracteres posibles, filtra los caracteres que aparecen al menos alguna vez en el texto y los guarda en finalWeights
 */

void filter_zero_words(Letter* finalWeights[], Letter* weights, int charAmount);

/* 
    initialize_letter_array: (Letter*) -> ()
    Inicializa una lista del tipo Letter de largo igual a MAX_CHARACTERS dejando a sus nodos en NULL 
 */
void initialize_letter_array(Letter* weights);

/* 
    set_letters_array: (Letter*, char*, int) -> int
    Guarda la cantidad de apariciones de un caracter en la propiedad weight del array de Letter weights y devuelve la cantidad de caracteres individuales en una parabra 
 */
int set_letters_array(Letter* weights, char* word, int wordlen);
 
 /*
    initialize_list: (Letter**, int) -> LetterList*
    Transforma el array de tipo Letter* a una lista enlazada del tipo LetterList para usarla en la formacion del arbol 
 */
LetterList* initialize_list(Letter** finalWeights, int charAmount);

/* 
    initialize_null: (char*, int) -> ()
    Inicializa una lista de largo igual a MAX_CHARACTERS con los nodos hijos en null y el peso en 0
 */
void initialize_null(char* array[], int len);

/* 
    generate_code: (Letter*, char, char*, int) -> int
    Dado un arbol y una letra devuelve el codigo generado por el algoritmo para esa letra
 */
int generate_code(Letter* node, char letter, char* arr, int counter);

/*
    iterate_letters: (Letter*, int, char*, int) -> char*
    Codifica un array de letras dado el arbol de huffman, su altura, la lista de codificaciones y el largo del texto
 */
char* iterate_letters(Letter* tree, int height, char* word, int wordlen);

/*
    get_letters: (char*, int, int*, int*) -> Letter*
    Dado un texto devuelve un arbol de huffman
 */
Letter* get_letters(char* word, int wordlen, int* height, int* letterCount);

/*
 * dado un archivo se encarga de llamar a las funciones necesarias para devolver el archivo codificado
 */
void compress(char* fileName);

#endif