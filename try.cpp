#define p printf ("here");


#include "myLib.h"
#include <cctype>
#include "hash.h"
#include "HashTable.h"

char* ClearText (const char* file, ull& new_size);

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


    HashTable <int> table (words, size_clear, num_lists, hash1);
    table.dumpSize (file_name);

    ull (*hash[6])(const char* , size_t) = {hash2, hash3, hash4, hash5, hash6, hash7};

    for (auto & i : hash)
    {
        table.clear ();
        table.update_hash (i);
        table.update (words, size_clear);
        table.dumpSize (file_name);
    }

    free (words);
}

#undef MurMurHash2
#undef fletcher

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




