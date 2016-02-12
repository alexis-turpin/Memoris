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
 * Factory which generates the screens.
 *
 * @file ScreenFactory.hpp
 * @brief factory to generate the game screens
 * @package factories
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_SCREEN_FACTORY
#define DEF_SCREEN_FACTORY

#include "Controller.hpp"

namespace factories {
class ScreenFactory {

public:

    static const unsigned short EXIT = 1;
    static const unsigned short MAIN_MENU_CONTROLLER_ID = 2;
    static const unsigned short NEW_GAME_CONTROLLER_ID = 3;
    static const unsigned short EDITOR_MENU_CONTROLLER_ID = 4;
    static const unsigned short EDITOR_SERIE_CONTROLLER_ID = 5;
    static const unsigned short OPEN_SERIE_CONTROLLER_ID = 6;
    static const unsigned short EDITOR_LEVEL_CONTROLLER_ID = 7;

    /**
     * @brief returns a new controller
     * pointer according to the given
     * screen id, used for screens
     * generation and screens switching.
     *
     * @param id      screen id
     *
     * @return screen controller pointer,
     * returns null if no screen match
     */
    static controllers::Controller* getScreenById(unsigned short id);
};
}

#endif
