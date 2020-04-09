#include <cstring>

typedef unsigned long long ull;

ull hash1 (const char* word, size_t mod);
ull hash2 (const char* word, size_t mod);
ull hash3 (const char* word, size_t mod);
ull hash4 (const char* word, size_t mod);
ull hash5 (const char* word, size_t mod);
ull hash6 (const char* word, size_t mod);
ull hash7 (const char* word, size_t mod);

ull hash1 (const char* word, size_t mod)
{
    return 1;
}

ull hash2 (const char* word, size_t mod)
{
    ull hash = 0;

    for (size_t i = 0; word[i] != '\0'; i++)
    {
        hash++;
    }

    return hash % mod;
}

ull hash3 (const char* word, size_t mod)
{
    ull hash = 0;

    for (size_t i = 0; word[i] != '\0'; i++)
    {
        hash += word[i];
    }

    return hash % mod;
}

ull hash4 (const char* word, size_t mod)
{
    ull sum = 0;
    ull size_ = 0;

    for (size_t i = 0; word[i] != '\0'; i++)
    {
        sum += word[i];
        size_++;
    }

    return (sum / size_) % mod;
}


ull hash5 (const char* word, size_t mod)
{
    ull sum = 0;

    int length = strlen (word);
    for (size_t i = 0; i < length; i++)
    {
        char first_bit = word[i]  >> (sizeof (char) - 1);
        sum ^=  ((word[i] << 1) + first_bit);
    }

    return sum % mod;
}

ull hash6 (const char* word, size_t mod)
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


ull hash7 (const char* word, size_t mod)
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
    /* Second reduction step to reduce sums to 8 bits */
    sum1 = (sum1 & 0xff) + (sum1 >> 8);
    sum2 = (sum2 & 0xff) + (sum2 >> 8);
    return (sum2 << 8 | sum1) % mod;
}