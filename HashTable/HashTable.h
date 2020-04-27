
typedef unsigned long long hash_t;


typedef hash_t (*hash_func)(const char* , size_t);

struct Hash
{
    const char* name;
    hash_func hash;

    Hash (const char* name, hash_func func):
            name(name),
            hash(func) {};
};

#include "hash.h"
#include "list.h"

template <typename TypeValue>
class HashTable
{
private:
    list<TypeValue, char*>** List;

    size_t num_lists;
    hash_func hash;
    static char* ClearText (const char* file, hash_t& new_size);
    int find_  (char* word);
public:
    void insert (char* word, TypeValue value = 0);

    TypeValue& find  (char* word);
    void erase  (char* word);
    void clear (hash_func hash_ = nullptr);

    void update (char* buf, hash_t size_clear);
    void set_hash (hash_func hash_) {hash = hash_;};

    void dumpSize (const char* file);
    HashTable (hash_t size_lists,  hash_func hash);
    HashTable (const char* text, int size_lists, hash_t (*hash)(const char* , size_t));
    HashTable (char* buf, hash_t size_clear, hash_t size_lists, hash_t (*hash)(const char* , size_t));
    ~HashTable ();

    TypeValue& operator[](char* word);
};


template <typename TypeValue>
HashTable<TypeValue>::HashTable (const char* text, int size_lists, hash_func hash):
    num_lists(size_lists),
    hash(hash),
    List(nullptr)
{
    List = new list<TypeValue, char*>*[num_lists];

    for (size_t i = 0; i < num_lists; i++)
        List[i] = new list<TypeValue, char*>;


    hash_t size_clear = 0;
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
char* HashTable<TypeValue>::ClearText (const char* file, hash_t& new_size)
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
    free (buf);
    return clear_text;
}

template <typename TypeValue>
HashTable<TypeValue>::~HashTable ()
{
    for (int i = 0; i < num_lists; i++)
        delete List[i];

    delete List;
}

template <typename TypeValue>
void HashTable<TypeValue>::dumpSize (const char* file)
{
    FILE *fp = fopen(file, "a+");

    for (size_t i = 0; i < num_lists; i++)
    {
        fprintf (fp, "%d; ",  List[i]->size);
    }

    fprintf (fp, "\n");
    fclose (fp);
}

template <typename TypeValue>
void HashTable<TypeValue>::insert (char* word, TypeValue value)
{
    if (find_ (word) == NO_POSITION)
    {
        int num = hash (word, num_lists);
        List[num]->PushBack (word, value);
    }

}

template <typename TypeValue>
int HashTable<TypeValue>::find_ (char* word)
{
    int num = hash (word, num_lists);

    int log_num = List[num]->FindValue (word);
    if (log_num == NO_POSITION)
        return NO_POSITION;
    else
        return log_num;
}

template <typename TypeValue>
TypeValue& HashTable<TypeValue>::find (char* word)
{
    int num = hash (word, num_lists);

    int log_num = List[num]->FindValue (word);
    if (log_num != NO_POSITION)
        return List[num]->value[log_num];
}

template <typename TypeValue>
void HashTable<TypeValue>::erase (char* word)
{
    int log_num = find_ (word);

    if (log_num == NO_POSITION)
        return;

    int num = hash (word, num_lists);

    List[num].Delete (log_num);
}

template <typename TypeValue>
TypeValue& HashTable<TypeValue>::operator[] (char* word)
{
    int num = hash (word, num_lists);

    int phys_num = find_ (word);
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
HashTable <TypeValue>::HashTable (char* buf, hash_t size_clear, hash_t size_lists,  hash_func hash):
    num_lists(size_lists),
    hash(hash),
    List(nullptr)
{
    List = new list<TypeValue, char*>*[num_lists];

    for (size_t i = 0; i < num_lists; i++)
        List[i] = new list<TypeValue, char*>;

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
void HashTable <TypeValue>::clear (hash_func hash_)
{
    for (size_t i = 0; i < num_lists; i++)
    {
        List[i]->clear ();
    }

    if (hash_ != nullptr)
    {
        set_hash (hash_);
    }
}

template <typename TypeValue>
void HashTable <TypeValue>::update (char* buf, hash_t size_clear)
{
    for (size_t i = 0; i < size_clear - 1; i++)
    {
        insert (&buf[i], i);

        do
        {
            i++;
        }
        while (buf[i] != '\0');
    }
}

template <typename TypeValue>
HashTable <TypeValue>::HashTable (hash_t size_lists,  hash_func hash):
    num_lists(size_lists),
    hash(hash),
    List(nullptr)
{
    List = new list<TypeValue, char*>*[num_lists];

    for (size_t i = 0; i < num_lists; i++)
        List[i] = new list<TypeValue, char*>;
}

