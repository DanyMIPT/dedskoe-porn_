#include <iostream>
#include <fstream>
#include <unistd.h>
#include "menu.h"


std::string readFile(const char* fileName);
void crack (std::string& file);
void CRACK ();
void ShowStart ();
void ProgressBarDraw (sf::RenderWindow& window);
void SetBarSettings (ProgressBar& bar);
void EndWindow (sf::RenderWindow& window);

typedef unsigned int ui;

const int JE  = 116; ////74h
const int JNE = 117; ////75h

const char* fileIn   = "PASS.COM";
const char* fileOut  = "PASS1_CRACK.COM";

const char* background_image1 = "matrix.png";
const char* background_image2 = "bar.png";
const char* background_image3 = "bkg3.png";
const char* button_image      = "button.png";
const char* font              = "font.ttf";
const char* sound             = "sound.wav";

const ui width  = 1920;
const ui height = 1080; 

const ui but_width  = 500;
const ui but_height = 170; 

int main ()
{
    ShowStart ();
    
    return 0;
}


void EndWindow (sf::RenderWindow& window)
{
    Sprite back (background_image3, 0, 0, width, height);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent (event))
        {
            if (event.type == sf::Event::Closed)
                window.close ();
        }

        window.clear (sf::Color::Black);

        window.draw (*back.sprite);
        

        window.display();
        sleep (5);
        break;
    }
}



void ProgressBarDraw (sf::RenderWindow& window)
{
    Sprite back (background_image2, 0, 0, width, height);

    ProgressBar bar(85, 200, 20, 500, 110, font);
    SetBarSettings (bar);

    sf::Music music;
    if (!music.openFromFile(sound))
    {
        exit (MusicLoadFailed);
    }
    music.play();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent (event))
        {
            if (event.type == sf::Event::Closed)
                window.close ();
        }

        window.clear (sf::Color::Black);

        window.draw (*back.sprite);
        if (bar.t <= 20)
        {
            bar.draw (window);

        }
        else
        {
            break;
        }
        
        window.display();
        sleep (1);
    }
}

void SetBarSettings (ProgressBar& bar)
{
    bar.setFillTableColor (173, 173, 173);
    bar.setOutLineTableThick (10);
    bar.setOutLineTableColor (122, 122, 122);

    bar.setFillBarColor (113, 113, 113);
    bar.setOutLineBarThick (4);
    bar.setOutLineBarColor (173, 173, 173);
}

void ShowStart ()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Crack");

    Sprite back (background_image1, 0, 0, width, height);
    Button button (button_image, but_width, but_height, width/2 - but_width/2, 670);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent (event))
        {
            if (event.type == sf::Event::Closed)
                window.close ();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                size_t mousePosX = (sf::Mouse::getPosition(window).x);
                size_t mousePosY = (sf::Mouse::getPosition(window).y);

                if ((mousePosX >= 710 && mousePosX <= 1210) &&  
                    (mousePosY >= 670                      && mousePosY <= 840))
                {
                    ProgressBarDraw (window);
                    CRACK ();
                    EndWindow (window);
                    window.close ();
                } 
            }
        }
        window.clear (sf::Color::Black);

        window.draw (*back.sprite);
        window.draw (*button.sprite);

        window.display();
    }
}

void CRACK ()
{
    std::string file = readFile (fileIn);
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

std::string readFile(const char* fileName)
{
    std::ifstream file(fileName, std::ios::binary);
    std::string str;

    file.seekg(0, std::ios_base::end);
    std::ifstream::pos_type len = file.tellg();
    file.seekg(0);
    str.resize(len);
    file.read((char*)str.data(), len);

    file.close ();
    return str;
}
