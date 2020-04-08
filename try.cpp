#define p printf ("here");

#include "list.h"
#include "myLib.h"
#include <cctype>
#include "hash.h"
#include "HashTable.h"

char* ClearText (const char* file, ull& new_size);
void WriteResults (const char* file, list** l);
void FillHashTable (char* buf, ull buf_size, ull (*hash)(const char* , size_t));

const size_t num_lists = 3001;

const char* text       = "text.txt";
const char* file_name  = "results.cvs";


#define MurMurHash2 hash6
#define fletcher    hash7

int main ()
{
    FILE *fp = fopen(file_name, "w");
    fclose (fp);

    ull size_clear = 0;
    char* words = ClearText (text, size_clear);

    FillHashTable (words, size_clear, hash1);
    FillHashTable (words, size_clear, hash2);
    FillHashTable (words, size_clear, hash3);
    FillHashTable (words, size_clear, hash4);
    FillHashTable (words, size_clear, hash5);
    FillHashTable (words, size_clear, MurMurHash2);
    FillHashTable (words, size_clear, fletcher);


    free (words);
}

#undef MurMurHash2
#undef fletcher


void WriteResults (const char* file, list** l)
{
    FILE *fp = fopen(file, "a+");

    for (size_t i = 0; i < num_lists; i++)
    {
        fprintf (fp, "%d; ",  l[i]->size);
        DeleteList (l[i]);
    }
    free (l);

    fprintf (fp, "\n");
    fclose (fp);
}

void FillHashTable (char* buf, ull buf_size, ull (*hash)(const char* , size_t))
{
    list** List = (list**) calloc (num_lists, sizeof (list*));
    for (int i = 0; i < num_lists; i++)
        List[i] = (list*) calloc (num_lists, sizeof (list));


    for (size_t i = 0; i < num_lists; i++)
    {
        ListInit (List[i]);
    }

    for (size_t i = 0; i < buf_size; i++)
    {
        int num = hash (&buf[i], num_lists);
        PushBack (&buf[i], List[num]);

        do
        {
            i++;
        }
        while (buf[i] != '\0');
    }

    WriteResults (file_name, List);
}

char* ClearText (const char* file, ull& new_size)
{
    char* buf = BufferMaker (file);
    char* clear_text = (char*) calloc (Sizecount (file), sizeof (char));

    int i = 0;
    while (buf[i] != '\0')
    {
        if (!isalpha (buf[i]))
            buf[i] = ' ';

        i++;
    }

    i = 0;
    ull k = 0;
    while (buf[i] != '\0')
    {
        if (isalpha (buf[i]))
        {
            clear_text[k++] = buf[i];
            if (buf[i + 1] == ' ')
                clear_text[k++] = '\0';
        }


        i++;
    }
    clear_text[k++] = ' ';

    new_size = k;
    return clear_text;
}


