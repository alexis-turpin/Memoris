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

namespace memoris
{
namespace controllers
{
class OfficialSeriesSelectorController : public Controller
{
public:

    OfficialSeriesSelectorController(utils::Context& context);

    /**
     * @brief rendering method
     *
     * @param context current context
     *
     * @return uint8_t id of the next screen
     */
    uint8_t render(utils::Context& context);

private:

    /**
     * @brief create the items
     */
    void createItems(utils::Context& context);

    static const std::string OFF_SER_TITLE;
    static const std::string TEMPORARY_DEFAULT_SERIE;

    static const float_t OFF_SER_TITLE_HRTL_PSTN;
    static const float_t OFF_SER_TITLE_VRTL_PSTN;

    sf::Color colorTitle;

    sf::Text offSerTitle;

    widgets::ScrollableListWidget scrlList;

    std::vector<std::string> levels;
};
}
}

#endif
