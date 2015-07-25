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
 * Button widget
 *
 * @file ButtonWidget.hpp
 * @brief button widget
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_BUTTON_WIDGET
#define DEF_BUTTON_WIDGET

#include <SFML/Graphics.hpp>

#include "../utils/Context.hpp"

#include "../defines/Colors.hpp"
#include "../defines/Fonts.hpp"

namespace widgets {
class ButtonWidget {

    static constexpr unsigned int BUTTON_FIXED_HEIGHT = 60;
    static constexpr unsigned int SIZE_BUTTON_TEXT_FONT = 40;

public:

    /**
     * Constructor
     *
     * @param buttonHorizontalPosition  button horizontal position
     * @param buttonVerticalPosition    button vertical position
     * @param buttonWidth               button fixed width
     * @param textLabel                 text of the button
     */
    ButtonWidget(
        unsigned int buttonHorizontalPosition,
        unsigned int buttonVerticalPosition,
        unsigned int buttonWidth,
        std::string textLabel = ""
    );
    ~ButtonWidget();

    /**
     * @brief setter for text content
     *
     * @param text         content to set
     */
    void setText(std::string text);

    /**
     * @brief displays the button and manage
     * button colors according to the current
     * cursor position on screen
     *
     * @param context       current context pointer
     */
    void display(utils::Context* context);

    /**
     * Returns true if the mouse is
     * currently hover the button
     *
     * @return bool
     */
    bool isMouseHover() const;


private:

    std::string text;

    sf::Font fontButton;

    sf::Color textColor;
    sf::Color backgroundColor;
    sf::Color textMouseHoverColor;
    sf::Color backgroundMouseHoverColor;

    sf::Text buttonText;

    sf::RectangleShape background;

    unsigned int horizontalPosition;
    unsigned int verticalPosition;
    unsigned int width;
};
}

#endif