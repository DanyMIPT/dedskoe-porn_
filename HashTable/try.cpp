#include "myLib.h"
#include <cctype>
#include "HashTable.h"

char* ClearText (const char* file, hash_t& new_size);

const size_t num_lists = 3001;

const char* text       = "text.txt";
const char* file_name  = "results.cvs";


int main ()
{

    FILE *fp = fopen(file_name, "w");
    fclose (fp);

    hash_t size_clear = 0;
    char* words = ClearText (text, size_clear);


    HashTable<int> table (num_lists, nullptr);

    Hash hash_func[] =  {Hash("ret1"                , ret1),
                         Hash("size_word"           , size_word),
                         Hash("sum_ascii"           , sum_ascii),
                         Hash("sum_ascii_div_length", sum_ascii_div_length),
                         Hash("my_hash"             , my_hash),
                         Hash("murmur", murmur),
                         Hash("fletcher", fletcher)};

    for (auto& i : hash_func)
    {
        table.clear (i.hash);
        table.update (words, size_clear);
        table.dumpSize (file_name);
    }

    free (words);
}

#undef MurMurHash2
#undef fletcher

char* ClearText (const char* file, hash_t& new_size)
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
    hash_t k = 0;
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




