#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>



enum Erroes {
    ImageLoadFailed = -7,
    FontLoadFailed  = -6,
    MusicLoadFailed = -5,

};

class Sprite {
protected:
    std::pair<sf::Sprite*, sf::Texture*> makeSpr (const char* fileName, size_t x_lu = 0, size_t y_lu = 0, 
                                                size_t x_rd = 800, size_t y_ld = 600);
public:
    Sprite  (const char* fileName, size_t x_lu = 0, size_t y_lu = 0, size_t x_rd = 800, size_t y_ld = 600);
    ~Sprite () {delete image, sprite;}

    sf::Sprite*  sprite;
    sf::Texture* image;
};

Sprite::Sprite (const char* fileName, size_t x_lu, size_t y_lu, size_t x_rd, size_t y_ld)
{
    std::pair<sf::Sprite*, sf::Texture*> tmp = makeSpr (fileName, x_lu, y_lu, x_rd, y_ld);
    sprite = tmp.first;
    image  = tmp.second;
}

std::pair<sf::Sprite*, sf::Texture*> Sprite::makeSpr (const char* fileName, size_t x_lu, size_t y_lu, 
                                                        size_t x_rd, size_t y_rd)
{
    auto bkg = new sf::Texture;
    if (!bkg->loadFromFile(fileName))
    {
        exit (ImageLoadFailed);
    }
    bkg->setRepeated(true);

    auto back = new sf::Sprite;
    back->setTexture(*bkg);
    back->setTextureRect(sf::IntRect(x_lu, y_lu, x_rd, y_rd));

    return {back, bkg};
}

class Button: public Sprite
{
public:
    size_t width;
    size_t height;

    Button (const char* fileName, size_t x_size, size_t y_size, size_t x_lu = 0, size_t y_lu = 0);
};

Button::Button (const char* fileName, size_t x_size, size_t y_size, size_t x_lu, size_t y_lu): 
                                                                                    Sprite(fileName, 0, 0, 500, 170)
{
    sprite->move(sf::Vector2f(x_lu, y_lu));
    width  = x_size;
    y_size = y_size;
}

class ProgressBar
{
private:
    size_t x_part_size;
    size_t y_part_size;
    size_t number_of_parts;

    size_t x; 
    size_t y;

    size_t fb1;
    size_t fb2;
    size_t fb3;

    size_t ob1;
    size_t ob2;
    size_t ob3;

    size_t thick_b = 0;
    size_t thick_t = 0;

    
    std::vector<sf::RectangleShape> bars;
    sf::RectangleShape table;
    void setBar ();
    void setPercent (sf::RenderWindow& window);

    const char* cur_font;

public:
    ProgressBar (size_t x_part_size, size_t y_part_size, size_t number_of_parts, size_t x, size_t y, const char* font);
    void draw (sf::RenderWindow& window);

    void setFillBarColor    (size_t fb1_, size_t fb2_, size_t fb3_) {fb1 = fb1_; fb2 = fb2_; fb3 = fb3_;}
    void setOutLineBarColor (size_t ob1_, size_t ob2_, size_t ob3_) {ob1 = ob1_; ob2 = ob2_; ob3 = ob3_;}
    void setOutLineBarThick (size_t thick) {thick_b = thick;}

    void setFillTableColor    (size_t ft1, size_t ft2, size_t ft3) {table.setFillColor(sf::Color(ft1, ft2, ft3));}
    void setOutLineTableColor (size_t ot1, size_t ot2, size_t ot3) {table.setOutlineColor(sf::Color(ot1, ot2, ot2));}
    void setOutLineTableThick (size_t thick) {table.setOutlineThickness(thick); thick_t = thick;}
    size_t t;
};


ProgressBar::ProgressBar (size_t x_part_size, size_t y_part_size, size_t number_of_parts, size_t x, size_t y, 
const char* font):
                          x_part_size(x_part_size), y_part_size(y_part_size), number_of_parts(number_of_parts),
                          x(x), y(y),bars(number_of_parts, sf::RectangleShape(sf::Vector2f(x_part_size, y_part_size))),
                          table(sf::Vector2f(x_part_size*number_of_parts, y_part_size)), t(0), cur_font(font)
{
    table.setPosition(y, x);    
}    

void ProgressBar::setBar ()
{
    if (t != 0)
    {
        bars[t - 1].setSize(sf::Vector2f(x_part_size - thick_b*2, y_part_size-thick_b*2));
        bars[t - 1].setPosition(y + x_part_size*(t-1) - thick_b, x + thick_b);
        bars[t - 1].setFillColor(sf::Color(fb1, fb2, fb3));

        bars[t - 1].setOutlineThickness(thick_b);
        bars[t - 1].setOutlineColor(sf::Color(ob1, ob2, ob3));
    }
}

void ProgressBar::setPercent (sf::RenderWindow& window)
{
    if (t != 0)
    {
        
        sf::Text text;
        text.setPosition(10.f, 50.f);
   
        sf::Font font;
        if (!font.loadFromFile(cur_font))
        {
            exit (FontLoadFailed);
        }

        text.setFont(font);
        text.setPosition(x_part_size*number_of_parts/2, x+thick_t);
    
        text.setCharacterSize(124);
        text.setFillColor(sf::Color::Red);

        int tmp =  (t)*100/number_of_parts;
        text.setString(std::to_string(tmp) + "%");

        text.setCharacterSize(124);
        text.setFillColor(sf::Color::White);

        window.draw(text);
    }
}

void ProgressBar::draw (sf::RenderWindow& window)
{
    window.draw(table);
    setBar ();
    
    for (size_t i = 0; i < t; i++)
    {
        window.draw(bars[i]);
    }
    
    setPercent (window);

    t++;
    
}
