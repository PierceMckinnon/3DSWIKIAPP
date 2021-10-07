
#include "foldcreation.h"
#include "headers.h"
#include "setup.h"

headfolders *kinghead = NULL;
headfolders *kingtail = NULL;
u8 maincount = 0;

/*!
 * @param       name        Name to be displayed on the button.
 * @param       headname    Name of the head node you want the button 
 *                          to be connected to on click.
 * @param       text        Text displayed on-click.                  
*/
void addfolder(char *name, char *headname, char *text)
{
    headfolders *temp = kinghead;
    while (strcmp(headname, temp->name) != 0)
    {
        temp = temp->next;
        if (temp == NULL)
        {
            return;
        }
    }
    (temp->count)++;

    folders *new = (folders *)malloc(sizeof(folders));
    if (new == NULL)
    {
        sceneExit();
    }
    if (temp->head == NULL)
    {
        temp->head = new;
    }
    else
    {
        temp->tail->next = new;
    }
    new->prev = temp->tail;
    temp->tail = new;
    new->name = name;
    new->next = NULL;
    new->text = text;
    new->text_size = strlen(text);
}

void addfolderhead(char *name, char *description)
{
    headfolders *new = (headfolders *)malloc(sizeof(headfolders));

    if (new == NULL)
    {
        sceneExit();
    }
    if (kinghead == NULL)
    {
        kinghead = new;
    }
    else
    {
        kingtail->next = new;
    }
    new->prev = kingtail;
    new->text = description;
    new->name = name;
    new->next = NULL;
    new->head = NULL;
    new->tail = NULL;
    kingtail = new;
    maincount++;
}
