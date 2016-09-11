/**
 * Memoris
 * Copyright (C) 2015  Jean LELIEVRE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file FontsManager.cpp
 * @brief loads the fonts objects from the files and provides getters to them
 * @package fonts
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "FontsManager.hpp"

namespace memoris
{
namespace fonts
{

/**
 *
 */
FontsManager::FontsManager()
{
    loadFontFromFile(titleFont, "res/fonts/crystal_regular.ttf");
    loadFontFromFile(textFont, "res/fonts/hi.otf");
}

/**
 *
 */
const sf::Font& FontsManager::getTitleFont() const noexcept
{
    return titleFont;
}

/**
 *
 */
const sf::Font& FontsManager::getTextFont() const noexcept
{
    return textFont;
}

/**
 *
 */
void FontsManager::loadFontFromFile(
    sf::Font& font,
    const std::string& path
)
{
    if(!font.loadFromFile(path))
    {
        throw std::invalid_argument("Cannot load font " + path);
    }
}

}
}
