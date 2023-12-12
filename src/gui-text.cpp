// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// gui-text.cpp
//
#include "gui-text.hpp"

#include "context.hpp"
#include "sfml-util.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

namespace castlecrawl
{

    const std::vector<std::string> splitIntoWords(const std::string & text)
    {
        std::vector<std::string> words;

        std::istringstream iss{ text };

        std::copy(
            std::istream_iterator<std::string>(iss),
            std::istream_iterator<std::string>(),
            std::back_inserter(words));

        return words;
    }

    const std::vector<sf::Text> typeset(
        Context & context,
        const FontSize fontSize,
        const sf::Color & color,
        const sf::FloatRect & region,
        const std::string & string)
    {
        const FontExtent fontExtent{ context.media.fontExtent(fontSize) };
        const std::vector<std::string> words{ splitIntoWords(string) };

        std::vector<sf::Text> lineTexts;
        lineTexts.reserve(words.size() / 4); // found by experiment to be a good upper bound

        sf::Vector2f pos{ util::position(region) };
        std::string lineStr;
        sf::Text lineText = context.media.makeText(fontSize, "", color);
        lineText.setPosition(pos);
        for (auto wordIter = std::begin(words); wordIter != std::end(words); ++wordIter)
        {
            if ("<paragraph>" == *wordIter)
            {
                lineTexts.push_back(lineText);
                pos.y += fontExtent.letter_size.y;
                pos.y += fontExtent.letter_size.y;
                lineStr.clear();
                lineText.setString(lineStr);
                util::setOriginToPosition(lineText);
                lineText.setPosition(pos);
                continue;
            }

            const std::string tempStr{ lineStr + " " + *wordIter };

            sf::Text tempText{ lineText };
            tempText.setString(tempStr);
            util::setOriginToPosition(tempText);
            tempText.setPosition(pos);

            if (util::right(tempText) < util::right(region))
            {
                lineText = tempText;
                lineStr = tempStr;
            }
            else
            {
                lineTexts.push_back(lineText);

                pos.y += fontExtent.letter_size.y;
                lineStr = *wordIter;
                lineText.setString(lineStr);
                util::setOriginToPosition(lineText);
                lineText.setPosition(pos);
            }
        }

        lineTexts.push_back(lineText);

        return lineTexts;
    }

} // namespace castlecrawl
