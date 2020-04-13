#include <cstring>




hash_t ret1 (const char* word, size_t mod);
hash_t size_word (const char* word, size_t mod);
hash_t sum_ascii (const char* word, size_t mod);
hash_t sum_ascii_div_length (const char* word, size_t mod);
hash_t my_hash (const char* word, size_t mod);
hash_t murmur (const char* word, size_t mod);
hash_t fletcher (const char* word, size_t mod);

hash_t ret1 (const char* word, size_t mod)
{
    return 1;
}

hash_t size_word (const char* word, size_t mod)
{
    hash_t hash = 0;

    for (size_t i = 0; word[i] != '\0'; i++)
    {
        hash++;
    }

    return hash % mod;
}

hash_t sum_ascii (const char* word, size_t mod)
{
    hash_t hash = 0;

    for (size_t i = 0; word[i] != '\0'; i++)
    {
        hash += word[i];
    }

    return hash % mod;
}

hash_t sum_ascii_div_length (const char* word, size_t mod)
{
    hash_t sum = 0;
    hash_t size_ = 0;

    for (size_t i = 0; word[i] != '\0'; i++)
    {
        sum += word[i];
        size_++;
    }

    return (sum / size_) % mod;
}


hash_t my_hash (const char* word, size_t mod)
{
    hash_t sum = 0;

    int length = strlen (word);
    for (size_t i = 0; i < length; i++)
    {
        char first_bit = word[i]  >> (sizeof (char) - 1);  //msb / lsb (least bit)
        sum ^=  ((word[i] << 1) | first_bit);
    }

    return sum % mod;
}

hash_t murmur (const char* word, size_t mod)
{
    size_t len = strlen (word);
    const unsigned int m = 0x5bd1e995;
    const unsigned int seed = 0;
    const int r = 24;

    unsigned int h = seed ^ len;

    const unsigned char * data = (const unsigned char *)word;
    unsigned int k;

    while (len >= 4)
    {
        k  = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len)
    {
        case 3:
            h ^= data[2] << 16;
        case 2:
            h ^= data[1] << 8;
        case 1:
            h ^= data[0];
            h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h % mod;
}


hash_t fletcher (const char* word, size_t mod)
{
    size_t bytes = strlen (word);
    int sum1 = 0xff, sum2 = 0xff;

    while (bytes) {
        size_t tlen = bytes > 20 ? 20 : bytes;
        bytes -= tlen;
        do {
            sum2 += sum1 += *word++;
        } while (--tlen);
        sum1 = (sum1 & 0xff) + (sum1 >> 8);
        sum2 = (sum2 & 0xff) + (sum2 >> 8);
    }

    sum1 = (sum1 & 0xff) + (sum1 >> 8);
    sum2 = (sum2 & 0xff) + (sum2 >> 8);
    return (sum2 << 8 | sum1) % mod;
}