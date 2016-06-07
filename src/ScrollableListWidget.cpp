/*
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
 * @file ScrollableListWidget.cpp
 * @brief scrollable list
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "ScrollableListWidget.hpp"
#include "Fonts.hpp"
#include "Colors.hpp"

using namespace widgets;

/**
 *
 */
ScrollableListWidget::ScrollableListWidget()
{
    font.loadFromFile(constants::Fonts::getTextFontPath());

    colorSltr.r = constants::Colors::COLOR_RED_RED;
    colorSltr.g = constants::Colors::COLOR_RED_GREEN;
    colorSltr.b = constants::Colors::COLOR_RED_BLUE;
    colorSltr.a = constants::Colors::COLOR_ALPHA_FULL;

    colorWhite.r = constants::Colors::COLOR_WHITE_RED;
    colorWhite.g = constants::Colors::COLOR_WHITE_GREEN;
    colorWhite.b = constants::Colors::COLOR_WHITE_BLUE;
    colorWhite.a = constants::Colors::COLOR_ALPHA_FULL;

    sltrPstn = 0;
}

/**
 *
 */
void ScrollableListWidget::display(utils::Context* ctx)
{
    /* iterate like that as we copy the reference in the for loop */
    uint8_t it = 0;

    for (sf::Text& txt : txtItems)
    {
        /* TODO: temporary solution to do not diplay the text
         * that overflows. Should be scrollable */
        if (it >= ITEMS_AMNT)
            continue;

        ctx->getWindow()->draw(txt);
        it++;
    }
}

/**
 *
 */
void ScrollableListWidget::initFromStrArr(const std::vector<std::string>& arr)
{
    uint8_t it = 0;

    /* TODO: use short as it is declared inside the
     * Fonts class, but should be changed... */
    const short size = constants::Fonts::SIZE_ITEM_FONT;

    for(std::string str : arr)
    {
        sf::Text txt;

        txt.setFont(font);
        txt.setString(str);
        txt.setCharacterSize(size);
        txt.setColor(colorWhite);
        txt.setPosition(
            SLTR_HRTL_PSTN,
            SLTR_VRTL_PSTN + SLTR_VRTL_SPRT * it
        );

        txtItems.push_back(txt);
        it++;
    }
}

/**
 *
 */
void ScrollableListWidget::updtSltrPstn()
{
    sltrPstn = ((sltrPstn > ITEMS_AMNT - 1) ? 0 : sltrPstn);

    for (sf::Text& item : txtItems)
    {
        item.setColor(colorWhite);
    }

    txtItems[sltrPstn].setColor(colorSltr);
}

/**
 *
 */
void ScrollableListWidget::incSltrPstn()
{
    sltrPstn++;
}

/**
 *
 */
void ScrollableListWidget::decSltrPstn()
{
    sltrPstn--;
}