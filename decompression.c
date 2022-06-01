
#include "io.h"
#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int count_tree_size(char* serializedTree){
    int counter = 0;
    for(int i = 0; serializedTree[i] != '\n'; i++){
        counter++;
    }
    return counter;
}

int separate_tree_from_words(char* serializedTree, char* treeValue, char* treeWords, int treeLen){
    int flag = 0, counter = 0, valid = 1;
    for(int i = 0; i < treeLen; i++){
        // Cuando llegamos al \n significa que comienzan los caracteres de la palabra, ademas solo hacemos esto una vez ya que el \n puede estar incluido en estos caracteres
        if(serializedTree[i] == '\n' && flag == 0){
            treeValue[counter] = '\0';
            flag = 1;
            counter = 0;
        }else{
            if(flag == 0){
                // Si estamos recorriendo el arbol y encontramos un caracter distinto a 1 o 0 entonces el arbol no es valido
                if(serializedTree[i] == '1' || serializedTree[i] == '0'){
                    treeValue[counter] = serializedTree[i];
                    counter++;
                }else{
                    valid = 0;
                }
            }else{
                treeWords[counter] = serializedTree[i];
                counter++;
            }
        }
    }
    treeWords[counter] = '\0';
    return valid;
}

Letter* fill_tree(char* treeValue, char* letters, int* counterTree, int* counterWords, int treeSize){
    // Si terminamos el array retornamos null
    if(*counterTree >= treeSize){
        return NULL;
    }
    // Si encontramos un 1 significa que el nodo actual es una hoja, entonces creamos esta hoja con la letra correspondiente y la devolvemos
    if(treeValue[*counterTree] == '1'){
        Letter* newLeaf = malloc(sizeof(Letter));
        newLeaf->letter = letters[*counterWords];
        *counterWords = *counterWords + 1;
        newLeaf->right = NULL;
        newLeaf->left = NULL;
        return newLeaf;
    }
    // Si es 0 significa que el nodo no es una hoja y recursamos a ambos lados para poder crear a sus hijos
    if(treeValue[*counterTree] == '0'){
        Letter* newNode = malloc(sizeof(Letter));
        *counterTree = *counterTree + 1; 
        newNode->left = fill_tree(treeValue, letters, counterTree, counterWords, treeSize);
        *counterTree = *counterTree + 1; 
        newNode->right = fill_tree(treeValue, letters, counterTree, counterWords, treeSize);
        return newNode;
    }
    return NULL;
}

char get_letter_decode (Letter* actualPos, int* index, char* codedTexd){
    // Si el char en la posicion actual es 0 nos movemos a la izquierda, si es 1 nos movemos a la derecha
    if ( codedTexd[*index] == '0' && actualPos -> left != NULL){
        *index = *index + 1;
        return get_letter_decode (actualPos -> left, index, codedTexd);
    }
    if ( codedTexd[*index] == '1' && actualPos -> right != NULL){
        *index = *index + 1;
        return get_letter_decode (actualPos -> right, index, codedTexd);
    }
    // Y si estamos en un a hoja devolvemos su letra
    if ( actualPos -> left == NULL && actualPos -> right == NULL){
        return actualPos->letter;
    }
    return ' ';
}

void decode_text(Letter* tree, char* codedTexd, char** decodedTexd, int *resultLen, int codedLen){
    int counter = 0;
    char letter;
    // Recorremos toda la palabra decodificada y vamos asignando las letras que encontramos en decodedTexd
    while(counter < codedLen){
        letter = get_letter_decode(tree, &counter, codedTexd);
        *resultLen = concat_letter(decodedTexd, letter, *resultLen);
    }
}



void decompress(char* fileName){
    char* compressedWord;
    char* serializedTree;
    int compressedLen, treeLen, treeSize;
    compressedWord = readfile(fileName, &compressedLen);
    
    char* treeFile = create_name(2, fileName, "tree\0");
    
    serializedTree = readfile(treeFile, &treeLen);
    treeSize = count_tree_size(serializedTree);
    char* letters = malloc(sizeof(char) * ((treeLen - treeSize) + 1));
    char* treeValue = malloc(sizeof(char) * (treeSize + 1));
    if(separate_tree_from_words(serializedTree, treeValue, letters, treeLen)){
        int counter = 0, counterTree = 0;
        Letter* tree = fill_tree(treeValue, letters, &counterTree, &counter, treeSize);
        int codedSize = 0;
        char * codedWord = explode(compressedWord, compressedLen, &codedSize);
        char* result = malloc(sizeof(char));
        int resultLen = 0;
        decode_text(tree, codedWord, &result, &resultLen, codedSize);
        char* decFile = create_name(4, treeFile, "dec\0");
        printf("%s\n", decFile);
        writefile(decFile, result, resultLen);
        free(decFile);
        free(treeFile);
        free_tree(tree);
        free(codedWord);
        free(result);
    }else{
        printf("Archivo no Valido\n");
    }
    free(compressedWord);
    free(serializedTree);
    free(letters);
    free(treeValue);
}