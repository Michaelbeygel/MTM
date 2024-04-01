#include <stdlib.h>
#include "AsciiArtTool.h"

RLEList asciiArtRead(FILE* in_stream){
    if(in_stream == NULL){
        return NULL;
    }

    RLEList list = RLEListCreate();

    if(list == NULL){
        return NULL;
    }

    char current_char;

    current_char = fgetc(in_stream);

    while (current_char != EOF) {
        RLEListResult result = RLEListAppend(list, current_char);
        if (result != RLE_LIST_SUCCESS) {
            RLEListDestroy(list);
            return NULL;
        }
        current_char = fgetc(in_stream);
    }

    return list;
}


// Function to write ASCII art from RLE list to a file stream
RLEListResult asciiArtPrint(RLEList list, FILE* out_stream) {
    // Check if a NULL pointer was sent as one of the parameters
    if (list == NULL || out_stream == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    int charLen = RLEListSize(list);

    for(int i =0; i<charLen; i++){
        RLEListResult result;
        char letter = RLEListGet(list, i, &result);
        if(result != RLE_LIST_SUCCESS){
            return result;
        }
        fprintf(out_stream, "%c", letter);
    }                       
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE* out_stream){
// Check if a NULL pointer was sent as one of the parameters
    if (list == NULL || out_stream == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    // Export the RLE list to a string
    RLEListResult result;
    char* output = RLEListExportToString(list, &result);
    if (result != RLE_LIST_SUCCESS) {
        return result;
    }


    char letter = output[0];
    int index = 0;

    while(letter != '\0'){
        fprintf(out_stream, "%c", letter);
        index++;
        letter = output[index];
    }
    free(output);
    return RLE_LIST_SUCCESS;
}


