// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include "nage/graphics/colorcode.h"
#include "es/component.h"
#include "es/serialize.h"
#include "strlib.h"

struct Text: public es::Component
{
    static constexpr auto name = "Text";

    static std::map<std::string, sf::Font> fonts;

    std::string fontName;
    sf::Font* font{nullptr};
    sf::Text text;

    void load(const std::string& str)
    {
        std::string colorStr;
        int fontSize{16};
        es::unpack(str, fontName, fontSize, colorStr);
        if (fonts.find(fontName) == fonts.end())
            fonts[fontName].loadFromFile(fontName);
        font = &fonts[fontName];
        auto values = strlib::split(str, " ");
        values.erase(values.begin(), values.begin() + 3);
        auto textStr = strlib::join(values, " ");
        text.setString(textStr);
        text.setFont(*font);
        text.setCharacterSize(fontSize);
        text.setColor(ng::ColorCode(colorStr).toColor());
    }

    std::string save() const
    {
        return es::pack();
    }
};

#endif
