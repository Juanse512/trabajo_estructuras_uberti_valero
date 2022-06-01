#include <stdlib.h>
#include <stdio.h>
#include "compression.h"
#include "decompression.h"
int main(int argc, char *argv[]){
    if (argc > 2 && *argv[1] == 'C') {
        compress(argv[2]);
    }else{
        if(argc > 1 && *argv[1] == 'D'){ //verificar que el archivo contiene un arbol, sino el programa retorna seg_fault
            decompress(argv[2]);
        }
    }
    return 0;
}
