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
 * @file InputTextWidget.hpp
 * @brief the input text widget is a text line where the user can type text
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_INPUTTEXTWIDGET_H_
#define MEMORIS_INPUTTEXTWIDGET_H_

#include "Widget.hpp"

#include <string>

namespace memoris
{
namespace widgets
{

class InputTextWidget : public Widget
{

public:

    /**
     * @brief constructor, initialize the whole widget with the correct size,
     * at the correct given position; set the maximum character variable;
     *
     * @param hPosition horizontal position
     * @param vPosition vertical position
     * @param lineWidth the width of the input text widget
     * @param maxCharacters the maximum amount of characters allowed
     */
    InputTextWidget(
        const float& hPosition,
        const float& vPosition,
        const float& lineWidth,
        const size_t& maxCharacters
    );

    /**
     * @brief set the displayed text; this function is used to force the
     * content of the input text widget; this function is used by the
     * level editor to edit the name of the current edited level
     *
     * @param inputTextData reference of a string to display into the input
     * text widget
     */
    void setDisplayedText(const sf::String& inputTextData);

    /**
     * @brief render the widget and its content
     */
    void display();

    /**
     * @brief update the displayed text according to the user input
     *
     * @param event constant reference to the SFML events manager
     */
    void update(const sf::Event& event);

    /**
     * @brief return the current displayed text; return a copy of the string
     * for manipulation in calling object
     *
     * @return sf::String
     *
     * NOTE: the string we return is not an attribute of the widget class
     * but directly the string contained inside the SFML text object; this
     * avoid duplication of identical data
     */
    sf::String getText() const;

    /**
     * @brief returns a boolean indicating if the input text widget content
     * is empty or not; used into the new game controller to save the new
     * game only if the name is not empty
     *
     * @return bool
     */
    bool isEmpty() const;

private:

    /**
     * @brief return a copy of the letter selected by the user on the keyboard;
     * this function uses the SFML events manager
     *
     * @param event constant reference to the SFML events manager
     *
     * @return sf::String
     */
    sf::String getInputLetter(const sf::Event& event);

    /* the last time of the input text widget cursor flashing animation
       update; we use SFML sf::Int32 data type as the SFML clock object
       uses this data type to handle time features */
    sf::Int32 cursorLastFlashAnimation;

    /* the maximum amount of characters allowed into the input text widget; we
       use a size_t because we compare sizes during the rendering of the widget
       between the actual sf::String size and the maximum size; SFML uses
       size_t to return the size of a SFML string */
    size_t maximumCharacters;

    /* boolean that specifies if the input text line cursor must be displayed
       or not; in fact, the animation of the input text line widget is to
       display the cursor during a very short time and then hide it; the cursor
       is also hidden during a very short time and displayed again */
    bool displayCursor;

    /* the pixels width of the input text widget; this value must be set by
       the developer in the calling object */
    float width;

    /* the SFML surface of the displayed text inside the input text widget */
    sf::Text displayedText;

    /* the four following SFML rectangles shapes are the borders of the input
       text widget */
    sf::RectangleShape boxTop;
    sf::RectangleShape boxBottom;
    sf::RectangleShape boxLeft;
    sf::RectangleShape boxRight;

    /* the cursor SFML rectangle shape is the flashing surface that moves on
       the right when one character is added and moved on the left when one
       character is deleted */
    sf::RectangleShape cursor;
};

}
}

#endif
