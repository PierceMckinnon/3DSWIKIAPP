#ifndef TEXTBUFFS_H
#define TEXTBUFFS_H
#include "headers.h"
extern C2D_TextBuf nameBuf;
typedef struct
{
    char *name;
    char *text;
} main_struct;
typedef struct
{
    char *name;
    char *head;
    char *text;
} sub_struct;

#endif