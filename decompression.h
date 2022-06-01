#ifndef __HUFF_DECOMPRESSION_H_
#define __HUFF_DECOMPRESSION_H_
#include "helpers.h"

/* 
    count_tree_size: (char *) -> int
    Cuenta el tamaño del arbol a partir del string que contiene al arbol serializado y las letras
 */

int count_tree_size(char* serializedTree);

/* 
    separate_tree_from_words: (char *, char*, char*, int) -> int
    Esta funcion separa el codigo del arbol serializado de las letras que contiene el arbol del archivo de entrada
 */

int separate_tree_from_words(char* serializedTree, char* treeValue, char* treeWords, int treeLen);

/* 
    fill_tree: (char *, char*, int*, int*, int) -> Letter*
    Crea el arbol a partir del codigo serializado y rellena las hojas con el array de las letras que contiene
 */

Letter* fill_tree(char* treeValue, char* letters, int* counterTree, int* counterWords, int treeSize);

/* 
    get_letter_decode: (Letter*, int*, char*) -> char
    Devuelve la primera letra que encuentra recorriendo el arbol con el codigo del arbol serializado
 */
char get_letter_decode (Letter* actualPos, int* index, char* codedTexd);

/* 
    decode_text: (Letter*, char*, char**, int*, int) -> ()
    Decodifica el codigo y lo guarda en decodedText
 */
void decode_text(Letter* tree, char* codedTexd, char** decodedTexd, int *resultLen, int codedLen);

/* 
 * esta funcion coordina todas las anteriores
 */
void decompress(char* fileName);

#endif