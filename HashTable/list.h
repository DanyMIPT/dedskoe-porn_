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

const int size_ = 40000;

//struct list {
//        char** data;
//        int* next;
//        int* prev;
//        int head;
//        int tail;
//        int free;
//        int size;
//        int sort;
//};

template<typename TypeValue, typename HashValue>
class list
{
public:
    HashValue* hash;
    TypeValue* value;
    int* next;
    int* prev;
    int head;
    int tail;
    int free;
    int size;
    int sort;

    list ();
    ~list ();
    int PushBack (HashValue hash, TypeValue value);
    int InsertAfter (int physics_number, HashValue hash, TypeValue value);
    int PushFront (HashValue hash, TypeValue value);
    int InsertBefore (int physics_number, HashValue hash, TypeValue value);
    void Dump();
    int Delete (int physics_number);
    int FindValue (HashValue hash);
    void clear ();
};

/*!
 * Initilisize List
 */
template <typename TypeValue, typename HashValue>
list <TypeValue, HashValue>::list ()
{
    hash = new HashValue[size_];
    value = new TypeValue[size_];
    next = new int[size_];
    prev = new int[size_];

    prev[0] = HEAD;
    next[0] = TAIL;

    for (int i = 1; i < size_ - 1; i++)
    {
        next[i] = i + 1;
        prev[i] = NOTHING;
    }

    prev[size_ - 1] = NOTHING;
    next[size_ - 1] = LAST_FREE_PLACE;

    head = 1;
    tail = 1;
    free = 1;
    size = 0;

    sort = 1;
}

/*!
 * Push the value in the end of the list
 * @param value
 * @return physics_number of value
 */
template <typename TypeValue, typename HashValue>
int list <TypeValue, HashValue>::PushBack (HashValue hash_, TypeValue value_)
{
    int tmp = free;

    free = next[free];

    hash[tmp]  = hash_;
    value[tmp] = value_;
    next[tmp]  = TAIL;


    if (size != 0)
    {
        next[tail] = tmp;
        prev[tmp] = tail;
    }

    tail = tmp;
    size++;

    return tmp;
}

/*!
 * Put the value after physics_number
 * @param physics_number after to put
 * @param value
 * @return physics_number of value
 */
template <typename TypeValue, typename HashValue>
int list <TypeValue, HashValue>::InsertAfter (int physics_number, HashValue hash, TypeValue value)
{
    int tmp = 0;

    if (size == 0 )
    {
        if (physics_number != 0)
        {
            printf ("Incorrect command\n");
            return INCORRECT_COMMAND;
        }

        tmp = PushFront (value);
    }
    else
    {
        if (physics_number != tail)
        {
            sort = 0;
        }

        tmp = free;

        free = next[free];

        hash[tmp] = hash;
        value[tmp] = value;
        prev[tmp] = physics_number;
        next[physics_number] = tmp;

        if (tail == physics_number)
        {
            tail = tmp;
            next[tmp] = 0;
        }
        else
        {
            next[tmp] = next[physics_number];
            prev[next[physics_number]] = tmp;
        }

    }

    size++;

    return tmp;
}

/*!
 * Push the value in the beginning of the list
 * @param value
 * @return physics_number of value
 */
template <typename TypeValue, typename HashValue>
int list <TypeValue, HashValue>::PushFront (HashValue hash, TypeValue value)
{
    int tmp = free;

    if (size != 1)
    {
        sort = 0;
    }

    free = next[free];

    hash[tmp]  = hash;
    value[tmp] = value;
    prev[tmp]  = HEAD;

    if (size == 0)
    {
        next[tmp] = TAIL;
    }
    else
    {
        prev[head] = tmp;
        next[tmp] = head;
    }

    head = tmp;
    size++;

    return tmp;
}

/*!
 * Put the value before physics_number
 * @param physics_number before to put
 * @param value
 * @return physics_number of value
 */
template <typename TypeValue, typename HashValue>
int list <TypeValue, HashValue>::InsertBefore (int physics_number, HashValue hash, TypeValue value)
{
    hash[free]  = hash;
    value[free] = value;

    int tmp = 0;

    if (size == 0 )
    {
        if (physics_number != 0)
        {
            printf ("Incorrect command\n");
            return INCORRECT_COMMAND;
        }

        tmp = PushBack (value);
    }
    else
    {
        if (physics_number != head)
        {
            sort = 0;
        }

        tmp = free;
        free = next[free];

        if (head == physics_number)
        {
            head = tmp;
            prev[tmp] = HEAD;
        }
        else
        {
            prev[tmp] = prev[physics_number];
            next[prev[physics_number]] = tmp;
        }
        next[tmp] = physics_number;
        prev[physics_number] = tmp;
    }

    size++;

    return tmp;
}

/*!
 * Deletes element on physics_number
 * @param physics_number
 * @param List
 */
template <typename TypeValue, typename HashValue>
int list<TypeValue, HashValue>::Delete (int physics_number)
{
    if (physics_number != head && prev[physics_number] == NOTHING)
    {
        printf ("Incorrect command\n");
        return INCORRECT_COMMAND;
    }

    if ((physics_number != head) || (physics_number != tail))
    {
        sort = 0;
    }

    if (physics_number == head)
    {
        if (size != 1)
        {
            head = next[physics_number];
            prev[next[physics_number]] = NOTHING;
        }
    }
    else
    {
        if (physics_number == tail)
        {
            if (size != 1)
            {
                tail = prev[physics_number];
                next[prev[physics_number]] = TAIL;
            }
        }
        else
        {
            prev[next[physics_number]] = prev[physics_number];
            next[prev[physics_number]] = next[physics_number];
        }
    }

    prev[physics_number] = NOTHING;
    next[physics_number] = free;

    free = physics_number;

    size--;
    return LIST_IS_OK;
}


/*!
 * Paint all the list
 * @param List
 */
template <typename TypeValue, typename HashValue>
void list<TypeValue, HashValue>::Dump()
{
    FILE* out = fopen ("list.dot", "w");

    fprintf (out, "digraph structs {\nrankdir=LR;\n");

    for (int i = 0; i < size; i++)
    {
        fprintf (out, "%d [shape=record,label=\"  <l%d> logic number = %d | value = %s | <p%d> prev = %d | <n%d> next = %d  \"];\n",
                 i, i, i, value[i], i, prev[i], i, next[i]);
    }

    for (int i = 0; i < size; i++)
    {
        fprintf (out, "%d:<l%d>", i, i);
        if (i != size - 1) fprintf (out, " -> ");
    }

    fprintf (out, ";\n");

    for (int i = 0; i < size; i++)
        fprintf (out, "%d:<n%d> -> %d:<%d>;\n", i, i, next[i], next[i]);

    fprintf (out, "\n}");

    fclose (out);

    system ("D:\\Graphiz\\bin\\dot.exe list.dot -T png -o list.png");
    system ("list.png");
}

/*!
 * Find position in the List by value
 * @param value
 * @param List
 * @return position
 */
template <typename TypeValue, typename HashValue>
int list<TypeValue, HashValue>::FindValue (HashValue hash_)
{
    int logical_number = 0;
    for (int i = head; ;)
    {
        if (size != 0 && hash_ == hash[i])
        {
            logical_number = i;
            break;
        }

        if (i == tail)
        {
            return NO_POSITION;
        }

        i = next[i];
    }

    return logical_number;
}

#define ASM
template <>
int list<int, char*>::FindValue (char* hash_)
{
    int logical_number = 0;

    for (int i = head; ;)
    {
#ifdef ASM
        __asm__ volatile (".intel_syntax noprefix\n\t"
                         "cmp %[size], 0\n\t"
                         "je not_equal\n\t"
                         "cld\n\t"
                         "loop_str:\n\t"
                         "mov al, byte [edi]\n\t"
                         "cmp al, 0\n\t"
                         "je end_str\n\t"
                         "mov al, byte [edi]\n\t"
                         "cmp al, byte [esi]\n\t"
                         "jne not_equal\n\t"
                         "inc edi\n\t"
                         "inc esi\n\t"
                         "jmp loop_str\n\t"
                         "end_str:\n\t"
                         "mov al, byte [edi]\n\t"
                         "cmp al, 0\n\t"
                         "jne not_equal\n\t"
                         "mov %[log_num], %[num]\n\t"
                         "not_equal: \n\t"
                         ".att_syntax prefix"

        : [log_num] "=r" (logical_number), [str1] "=D" (hash_), [str2] "=S" (hash[i])
        : [size] "r" (size), [num] "r" (i)
        : "al", "memory");

        if (logical_number == i)
        {
            break;
        }
#else
        if (size != 0 && strcmp (hash_, hash[i]) == 0)
        {
            logical_number = i;
            break;
        }
#endif


        if (i == tail)
        {
            return NO_POSITION;
        }

        i = next[i];
    }

    return logical_number;
}

#include <iostream>
template <typename TypeValue, typename HashValue>
list <TypeValue, HashValue>::~list ()
{
    delete [] next;
    delete [] prev;
    delete [] value;
    delete [] hash;
}

template <typename TypeValue, typename HashValue>
void list <TypeValue, HashValue>::clear ()
{
    prev[0] = HEAD;
    next[0] = TAIL;

    for (int i = 1; i < size_ - 1; i++)
    {
        next[i] = i + 1;
        prev[i] = NOTHING;
    }

    prev[size_ - 1] = NOTHING;
    next[size_ - 1] = LAST_FREE_PLACE;

    head = 1;
    tail = 1;
    free = 1;
    size = 0;

    sort = 1;
}


