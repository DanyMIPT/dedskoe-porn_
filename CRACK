#include <iostream>
#include <fstream>

std::string readFile();
void crack (std::string& file);

typedef unsigned int ui;

const int JE  = 116; ////74h
const int JNE = 117; ////75h

const char* fileIn = "PASS1.COM";
const char* fileOut  = "PASS1_CRACK.COM";

int main ()
{
    std::string file = readFile ();
    for (auto i:file)
        std::cout << static_cast<ui> (i) << " ";
    crack (file);

    std::ofstream out(fileOut);
    out << file;
    out.close ();
}

void crack (std::string& file)
{
    for (char& i : file)
    {
        if (static_cast<ui> (i) != JE)
        {
            continue;
        }
        else
        {
            i = JNE;
            break;
        }
    }
}

std::string readFile()
{
    std::ifstream file(fileIn, std::ios::binary);
    std::string str;

    file.seekg(0, std::ios_base::end);
    std::ifstream::pos_type len = file.tellg();
    file.seekg(0);
    str.resize(len);
    file.read((char*)str.data(), len);

    file.close ();
    return str;
}
