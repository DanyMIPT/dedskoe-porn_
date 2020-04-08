#include <cstdlib>
#include <assert.h>
#include <cstring>
#include "stdio.h"

enum {
    LAST_FREE_PLACE = -440,
    NOTHING = 1,
    HEAD = -1,
    TAIL = 0,
    INCORRECT_COMMAND = -8,
    LIST_OVERFLOW = -55,
    LIST_IS_OK = 11,
    ARRAY_ERROR = 333,
    NO_POSITION = -9,
    POISON = -895622,
};

const int size = 40000;

struct list {
        char** data;
        int* next;
        int* prev;
        int head;
        int tail;
        int free;
        int size;
        int sort;
};

/*!
 * Initilisize List
 * @param list
 */
void ListInit (list * List);

/*!
 * Push the value in the end of the list
 * @param value
 * @param List
 * @return physics_number of value
 */
int PushBack (char* value, struct list * List);

/*!
 * Put the value after physics_number
 * @param physics_number after to put
 * @param value
 * @param List
 * @return physics_number of value
 */
int InsertAfter (int physics_number, char* value, struct list * List);

/*!
 * Push the value in the beginning of the list
 * @param value
 * @param List
 * @return physics_number of value
 */
int PushFront (char* value, struct list * List);

/*!
 * Put the value before physics_number
 * @param physics_number before to put
 * @param value
 * @param List
 * @return physics_number of value
 */
int InsertBefore (int physics_number, char* value, struct list * List);

/*!
 * Deletes element on physics_number
 * @param physics_number
 * @param List
 */
int Delete (int physics_number, struct list * List);


/*!
 * Paint all the list
 * @param List
 */
void Dump(struct list * List);

/*!
 * Find position in the List by value
 * @param value
 * @param List
 * @return position
 */
int FindPositionOnValue (char* value, struct list * List);

/*!
 *  Find position in the List by logical number
 * @param logical_number
 * @param List
 * @return position
 */
int FindPositionVeeryVerySlow (int logical_number, struct list * List);


void Dump(struct list * List)
{
    FILE* out = fopen ("list.dot", "w");

    fprintf (out, "digraph structs {\nrankdir=LR;\n");

    for (int i = 0; i < size; i++)
    {
        fprintf (out, "%d [shape=record,label=\"  <l%d> logic number = %d | value = %s | <p%d> prev = %d | <n%d> next = %d  \"];\n",
                 i, i, i, List->data[i], i, List->prev[i], i, List->next[i]);
    }

    for (int i = 0; i < size; i++)
    {
        fprintf (out, "%d:<l%d>", i, i);
        if (i != size - 1) fprintf (out, " -> ");
    }

    fprintf (out, ";\n");

    for (int i = 0; i < size; i++)
        fprintf (out, "%d:<n%d> -> %d:<%d>;\n", i, i, List->next[i], List->next[i]);

    fprintf (out, "\n}");

    fclose (out);

    system ("D:\\Graphiz\\bin\\dot.exe list.dot -T png -o list.png");
    system ("list.png");
}

void ListInit (list * List)
{

    List->data = (char**) calloc (size, sizeof (char*));
    List->next = (int*) calloc (size, sizeof (int));
    List->prev = (int*) calloc (size, sizeof (int));

    List->prev[0] = HEAD;
    List->data[0] = nullptr;
    List->next[0] = TAIL;

    for (int i = 1; i < size - 1; i++)
    {
        List->next[i] = i + 1;
        List->prev[i] = NOTHING;
    }

    List->prev[size - 1] = NOTHING;
    List->next[size - 1] = LAST_FREE_PLACE;

    List->head = 1;
    List->tail = 1;
    List->free = 1;
    List->size = 0;

    List->sort = 1;
}


int PushFront (char* value, struct list * List)
{
    int tmp = List->free;

    if (List->size != 1)
    {
        List->sort = 0;
    }

    List->free = List->next[List->free];

    List->data[tmp] = value;
    List->prev[tmp] = HEAD;

    if (List->size == 0)
    {
        List->next[tmp] = TAIL;
    }
    else
    {
        List->prev[List->head] = tmp;
        List->next[tmp] = List->head;
    }

    List->head = tmp;
    List->size++;

    return tmp;
}

int InsertAfter (int physics_number, char* value, struct list * List)
{
    int tmp = 0;

    if (List->size == 0 )
    {
        if (physics_number != 0)
        {
            printf ("Incorrect command\n");
            return INCORRECT_COMMAND;
        }

        tmp = PushFront (value, List);
    }
    else
    {
        if (physics_number != List->tail)
        {
            List->sort = 0;
        }

        tmp = List->free;

        List->free = List->next[List->free];

        List->data[tmp] = value;
        List->prev[tmp] = physics_number;
        List->next[physics_number] = tmp;

        if (List->tail == physics_number)
        {
            List->tail = tmp;
            List->next[tmp] = 0;
        }
        else
        {
            List->next[tmp] = List->next[physics_number];
            List->prev[List->next[physics_number]] = tmp;
        }

    }

    List->size++;

    return tmp;
}


int PushBack (char* value, struct list * List)
{
    int tmp = List->free;

    List->free = List->next[List->free];

    List->data[tmp] = value;
    List->next[tmp] = TAIL;


    if (List->size != 0)
    {
        List->next[List->tail] = tmp;
        List->prev[tmp] = List->tail;
    }

    List->tail = tmp;
    List->size++;

    return tmp;
}

// DRY

int InsertBefore (int physics_number, char* value, struct list * List)
{
    List->data[List->free] = value;

    int tmp = 0;

    if (List->size == 0 )
    {
        if (physics_number != 0)
        {
            printf ("Incorrect command\n");
            return INCORRECT_COMMAND;
        }

        tmp = PushBack (value, List);
    }
    else
    {
        if (physics_number != List->head)
        {
            List->sort = 0;
        }

        tmp = List->free;
        List->free = List->next[List->free];

        if (List->head == physics_number)
        {
            List->head = tmp;
            List->prev[tmp] = HEAD;
        }
        else
        {
            List->prev[tmp] = List->prev[physics_number];
            List->next[List->prev[physics_number]] = tmp;
        }
        List->next[tmp] = physics_number;
        List->prev[physics_number] = tmp;
    }

    List->size++;

    return tmp;
}

int Delete (int physics_number, struct list * List)
{

    if (physics_number != List->head && List->prev[physics_number] == NOTHING)
    {
        printf ("Incorrect command\n");
        return INCORRECT_COMMAND;
    }

    if ((physics_number != List->head) || (physics_number != List->tail))
    {
        List->sort = 0;
    }

    if (physics_number == List->head)
    {
        if (List->size != 1)
        {
            List->head = List->next[physics_number];
            List->prev[List->next[physics_number]] = NOTHING;
        }
    }
    else
    {
        if (physics_number == List->tail)
        {
            if (List->size != 1)
            {
                List->tail = List->prev[physics_number];
                List->next[List->prev[physics_number]] = TAIL;
            }
        }
        else
        {
            List->prev[List->next[physics_number]] = List->prev[physics_number];
            List->next[List->prev[physics_number]] = List->next[physics_number];
        }
    }

    List->data[physics_number] = nullptr;
    List->prev[physics_number] = NOTHING;
    List->next[physics_number] = List->free;

    List->free = physics_number;

    List->size--;
    return LIST_IS_OK;
}

int FindValue (char* value, struct list * List)
{
    int logical_number = 0;
    for (int i = List->head; ;)
    {

        if (i == List->tail)
        {
            return NO_POSITION;
        }

        if (strcmp (value, List->data[i]) == 0)
        {
            logical_number = i;
            break;
        }

        i = List->next[i];
    }

    return logical_number;
}

int FindPositionVeeryVerySlow (int logical_number, struct list * List)
{
    if ((List->prev[logical_number] == NOTHING) && (logical_number != List->head))   return NO_POSITION;

    if (List->sort == 1)        return logical_number;

    int position = 1;

    while (List->prev[logical_number] != HEAD)
    {
        position++;
        logical_number = List->prev[logical_number];
    }
    return position;
}

void DeleteList (struct list * List)
{
    free (List->next);
    free (List->prev);
    free (List->data);

    List->head = POISON;
    List->size = POISON;
    List->tail = POISON;
    List->sort = POISON;
    List->free = POISON;

    free (List);
}

