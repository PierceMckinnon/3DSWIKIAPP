
#ifndef FOLDCREATION_H
#define FOLDCREATION_H
#include "headers.h"
typedef struct headfolders headfolders;
typedef struct folders folders;
struct headfolders
{
    char *name;
    char *text;
    float x, y;
    headfolders *next;
    headfolders *prev;
    folders *tail;
    folders *head;
    u8 count;
};
struct folders
{
    float x, y;
    folders *next;
    folders *prev;
    char *text;
    char *name;
    u32 text_size;
};
extern headfolders *kinghead;
extern headfolders *kingtail;
void addfolderhead(char *, char *);
void addfolder(char *name, char *headname, char *text);
extern u8 maincount;
#endif