#include "list.h"


template <typename TypeValue>
class HashTable
{
private:
    list<TypeValue, char*>* List;

    size_t num_lists;
    ull (*hash)(const char* , size_t);
    static char* ClearText (const char* file, ull& new_size);
public:
    void insert (char* word, TypeValue value = 0);
    int find  (char* word);
    void erase  (char* word);
    void clear ();

    void update (char* buf, ull size_clear);
    void update_hash (ull (*hash_)(const char* , size_t)) {hash = hash_;};

    void dumpSize (const char* file);
    HashTable (const char* text, int size_lists, ull (*hash)(const char* , size_t));
    HashTable (char* buf, ull size_clear, ull size_lists, ull (*hash)(const char* , size_t));
    ~HashTable ();

    TypeValue& operator[](char* word);
};


template <typename TypeValue>
HashTable<TypeValue>::HashTable (const char* text, int size_lists, ull (* hash) (const char*, size_t)):num_lists(size_lists), hash(hash)
{
    List = nullptr;

    List = new list<TypeValue, char*>[num_lists];


    ull size_clear = 0;
    char* words = ClearText (text, size_clear);


    for (size_t i = 0; i < size_clear - 1; i++)
    {
        insert (&words[i]);

        do
        {
            i++;
        }
        while (words[i] != '\0');
    }

    free (words);
}

template <typename TypeValue>
char* HashTable<TypeValue>::ClearText (const char* file, ull& new_size)
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
    free (buf);
    return clear_text;
}

template <typename TypeValue>
HashTable<TypeValue>::~HashTable ()
{
    delete List;
}

template <typename TypeValue>
void HashTable<TypeValue>::dumpSize (const char* file)
{
    FILE *fp = fopen(file, "a+");

    for (size_t i = 0; i < num_lists; i++)
    {
        fprintf (fp, "%d; ",  List[i].size);
    }

    fprintf (fp, "\n");
    fclose (fp);
}

template <typename TypeValue>
void HashTable<TypeValue>::insert (char* word, TypeValue value)
{
    if (find (word) == NO_POSITION)
    {
        int num = hash (word, num_lists);
        List[num].PushBack (word, value);
    }

}

template <typename TypeValue>
int HashTable<TypeValue>::find (char* word)
{
    int num = hash (word, num_lists);

    int log_num = List[num].FindValue (word);
    if (log_num == NO_POSITION)
        return NO_POSITION;
    else
        return log_num;
}

template <typename TypeValue>
void HashTable<TypeValue>::erase (char* word)
{
    int log_num = find (word);

    if (log_num == NO_POSITION)
        return;

    int num = hash (word, num_lists);

    List[num].Delete (log_num);
}

template <typename TypeValue>
TypeValue& HashTable<TypeValue>::operator[] (char* word)
{
    int num = hash (word, num_lists);

    int phys_num = find (word);
    if (phys_num == NO_POSITION)
    {
        return List[num].value[ (List[num].PushBack (word))];
    }
    else
    {
        return List[num].value[phys_num];
    }
}

template <typename TypeValue>
HashTable <TypeValue>::HashTable (char* buf, ull size_clear, ull size_lists,  ull (* hash) (const char*, size_t)):num_lists(size_lists), hash(hash)
{
    List = nullptr;
    List = new list<TypeValue, char*>[num_lists];

    for (size_t i = 0; i < size_clear - 1; i++)
    {
        insert (&buf[i]);

        do
        {
            i++;
        }
        while (buf[i] != '\0');
    }
}

template <typename TypeValue>
void HashTable <TypeValue>::clear ()
{
    for (size_t i = 0; i < num_lists; i++)
    {
        List[i].clear ();
    }
}

template <typename TypeValue>
void HashTable <TypeValue>::update (char* buf, ull size_clear)
{
    for (size_t i = 0; i < size_clear - 1; i++)
    {
        insert (&buf[i]);

        do
        {
            i++;
        }
        while (buf[i] != '\0');
    }
}

