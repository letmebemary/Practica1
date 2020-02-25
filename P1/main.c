/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include <stdio.h>
#include <string.h>

#include "types.h"
#include <string.h>

#define CODE_LENGTH 2

#ifdef STATIC_LIST
#include "static_list.h"
#endif
#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef TEST_LIST
#include "list/list.h"
#endif



void processCommand(char command_number[CODE_LENGTH+1], char command, char param[NAME_LENGTH_LIMIT+1], tList* list) {
    tItemL item1;
    tPosL pos;


    switch(command) {
        case 'N': {
            strcpy(item1.partyName, param);
            item1.numVotes = 0;
            insertItem(item1,LNULL, &list);
            printf("%s %c: party %s\n", command_number, command, item1.partyName);
            printf("* New: party %s\n", item1.partyName);
            break;
        }

        case 'S': {
            int param_int;
            sscanf(param,"%d", &param_int);
            printf("%s %c: totalvoters %d\n", command_number, command, param_int);

            item1 = getItem(first(*list), *list);
            printf("Party %s numvotes %d (%.2f%)\n", item1.partyName, item1.numVotes,(item1.numVotes/param_int)*100);
            while(next(pos,*list) == LNULL){
                pos = next(pos,*list);
                item1 = getItem(pos, *list);
                printf("Party %s numvotes %d (%.2f%)\n", item1.partyName, item1.numVotes,(item1.numVotes/param_int)*100);
            }
            printf("Null votes xx\n");
            break;
        }

        case 'V': {
            printf("Read: %s %c %s.\n", command_number, command, param);
            break;
        }

        default: {
            break;
        }
    }
    printf("********************\n");
}

void readTasks(char *filename, tList* list) {
    FILE *df;
    char command_number[CODE_LENGTH+1], command, param[NAME_LENGTH_LIMIT+1];

    df = fopen(filename,"r");
    if (df != NULL) {
        while (!feof(df)) {
            char format[16];
            sprintf(format, "%%%is %%c %%%is", CODE_LENGTH, NAME_LENGTH_LIMIT);
            fscanf(df,format, command_number, &command, param);
            processCommand(command_number, command, param, &list);
        }
        fclose(df);
    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {


    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    tList list;
    createEmptyList(&list);

    readTasks(file_name, &list);


    return 0;
}


