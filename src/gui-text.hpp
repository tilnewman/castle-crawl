#ifndef CASTLECRAWL_GUI_TEXT_HPP_INCLUDED
#define CASTLECRAWL_GUI_TEXT_HPP_INCLUDED
//
// gui-text.hpp
//
#include "media.hpp"

#include <string>
#include <vector>

#include <SFML/Graphics/Text.hpp>

namespace castlecrawl
{
    struct Context;

    const std::vector<std::string> splitIntoWords(const std::string & text);

    const std::vector<sf::Text> typeset(
        Context & context,
        const FontSize fontSize,
        const sf::Color & color,
        const sf::FloatRect & region,
        const std::string & string);

} // namespace castlecrawl

#endif // CASTLECRAWL_GUI_TEXT_HPP_INCLUDED
