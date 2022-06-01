#ifndef __HUFF_HELPERS_H_
#define __HUFF_HELPERS_H_
#define MAX_CHARACTERS 256

typedef struct LetterStruct{
  char letter;
  int weight;
  struct LetterStruct* right;
  struct LetterStruct* left;
} Letter;

typedef struct LetterList{
    Letter* let;
    struct LetterList* next;
} LetterList;

/*
    swap: (Letter**, int, int) -> ()
    swap intercambia de posicion dos elementos de una lista de punteros
*/
void swap(Letter** weights, int pos1, int pos2 );

/* 
    partition: (Letter**, int, int) -> ()
    partition encuentra el la posicion en la cual se particiona el array para hacer el quick sort
 */
int partition(Letter** array, int low, int high);

/* 
    quick_sort: (Letter**, int, int) -> ()
    quick_sort ordena una lista de menor a mayor
 */
void quick_sort(Letter** array, int low, int high);

/* 
    free_tree: (Letter*) -> ()
    free_tree libera la memoria reservada en un arbol binario de tipo Letter
 */
void free_tree(Letter* tree);

/* 
    concat_words: (char**, char*, int, int) -> int
    concat_words concatena dos strings y devuelve el nuevo largo
 */
int concat_words(char** final, char* newWord, int finalLen, int newWordLen);

/* 
    concat_letter: (char**, char, int) -> int
    concat_letter concatena un string y un char y devuelve el nuevo largo
 */
int concat_letter(char** final, char letter, int finalLen);

/* 
    create_name: (int, char*, char*) -> char*
    create_name concatena dos strings con la posibilidad de poder recortar un pedazo del primer string 
    que se le pase a la funcion y devueve el string concatenado
 */
char* create_name(int position, char* string, char* textToAppend);

#endif