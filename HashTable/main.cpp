#include "myLib.h"
#include <cctype>
#include "HashTable.h"
#include <ctime>
#include <iostream>

char* ClearText (const char* file, hash_t& new_size);
void findWords (char* buf, HashTable<int>& hash_table, size_t size);

const size_t num_lists = 3001;

const char* text       = "text.txt";
const char* file_name  = "results.cvs";


int main ()
{
    std::cout << "1";
    std::clock_t start_time =  std::clock();

    hash_t size_clear = 0;
    char* words = ClearText (text, size_clear);
    HashTable<int> table (num_lists, murmur);
    table.update (words, size_clear);

    std::clock_t in_time = std::clock();
    std::cout << "In time - " << (in_time - start_time) / static_cast<double> (CLOCKS_PER_SEC) << "\n";
    for (int i = 0; i < 1000; i++)
        findWords (words, table, size_clear);


    free (words);
    std::clock_t end_time = clock();
    std::cout << "Find time time - " << (end_time - in_time) / static_cast<double> (CLOCKS_PER_SEC) << "\n";
    std::cout << "All time - " << (end_time - start_time) / static_cast<double> (CLOCKS_PER_SEC) << "\n";
}



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
            {
                clear_text[k++] = '\0';
            }
        }


        i++;
    }
    clear_text[k++] = ' ';
    new_size = k;

    return clear_text;
}

void findWords (char* buf, HashTable<int>& hash_table, size_t size)
{
    for (size_t i = 0; i < size - 1; i++)
    {
        hash_table.find (&(buf[i]));

        do
        {
            i++;
        }
        while (buf[i] != '\0');
    }
}




