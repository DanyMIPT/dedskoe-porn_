#include "list.h"
#include "myLib.h"
#include "ctype.h"
#include "hash.h"

#define p printf ("here");
char* ClearText (const char* file);
list** FillHashTable (char* words, ull (*hash)(const char* , size_t));

const size_t num_lists = 3001;

const char* text       = "text.txt";

int main ()
{

    char* words = ClearText (text);
    list** List = FillHashTable (words, hash1);


    
    for (int i = 0; i < num_lists; i++)
    {
        //DeleteList (List[i]);
    }
}

list** FillHashTable (char* buf, ull (*hash)(const char* , size_t))
{
    auto List = new list*[num_lists];
    printf ("%p", List);

    for (size_t i = 0; i < num_lists; i++)
    {
        ListInit (List[i]);
    }

    //char* word = buf;
    //for (int i = 0; buf[i]; i++)
    {
        //if (buf[i] == '\0' || buf[i] == ' ')
        {
            //continue;
        }
        //else
        {

            //if (i > 0 && (buf[i-1] == '\0' || buf[i-1] == ' '))
            {
                //word = buf;
                //continue;
            }

            //if ((buf[i + 1] == '\0' && i > 0 && isalpha(buf[i-1])) || buf[i + 1] == ' ')
            {
                //buf[i + 1] = '\0';
                //PushBack (word, List[hash(word, num_lists)]);
            }
                

        }       
    }
    

    return List;
}

char* ClearText (const char* file)
{
    char* buf = BufferMaker (file);
    
    int i = 0;
    while (buf[i] != '\0')
    {
        if (!isalpha (buf[i]))
            buf[i] = ' ';

        i++;
    }

    return buf;
}


