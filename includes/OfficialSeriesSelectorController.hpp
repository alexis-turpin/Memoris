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
 * Official series selector menu
 *
 * @file OfficialSeriesSelectorController.hpp
 * @brief official series menu
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_OFFICIAL_SERIES_SELECTOR_MENU
#define DEF_OFFICIAL_SERIES_SELECTOR_MENU

#include "Controller.hpp"
#include "ScrollableListWidget.hpp"

namespace controllers
{
class OfficialSeriesSelectorController : public Controller
{
public:

    OfficialSeriesSelectorController();

    /**
     * @brief rendering method
     *
     * @param ctx current context
     *
     * @return uint8_t id of the next screen
     */
    uint8_t render(utils::Context* ctx);

private:

    /**
     * @brief create the items
     */
    void createItems();

    static const std::string OFF_SER_TITLE;
    static const std::string TEMPORARY_DEFAULT_SERIE;
    static const std::string ARR_DOWN_IMG_PATH;

    static const float_t OFF_SER_TITLE_HRTL_PSTN;
    static const float_t OFF_SER_TITLE_VRTL_PSTN;
    static const float_t ARR_DOWN_HRTL_PSTN;
    static const float_t ARR_DOWN_VRTL_PSTN;

    sf::Color colorTitle;

    sf::Font fontTitle;

    sf::Text offSerTitle;

    sf::Texture arrDownTxt;

    sf::Sprite arrDownSprt;

    widgets::ScrollableListWidget scrlList;
};
}

#endif
