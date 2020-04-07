typedef unsigned long long ull;

ull hash1 (const char* word, size_t mod);
ull hash2 (const char* word, size_t mod);
ull hash3 (const char* word, size_t mod);
ull hash4 (const char* word, size_t mod);
ull hash5 (const char* word, size_t mod);

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
    ull size = 0;

    for (size_t i = 0; word[i] != '\0'; i++)
    {
        sum += word[i];
        size++;
    }

    return (sum / size) % mod;
}
