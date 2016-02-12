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
 * @file ScreenFactory.hpp
 * @package factories
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "ScreenFactory.hpp"

#include "../main_menu/MainMenuController.hpp"
#include "../new_game/NewGameController.hpp"
#include "../editor_menu/EditorMenuController.hpp"
#include "../editor_serie/EditorSerieController.hpp"
#include "../open_serie/OpenSerieController.hpp"
#include "../editor_level/EditorLevelController.hpp"

using namespace factories;

const unsigned short ScreenFactory::EXIT = 1;
const unsigned short ScreenFactory::MAIN_MENU_CONTROLLER_ID = 2;
const unsigned short ScreenFactory::NEW_GAME_CONTROLLER_ID = 3;
const unsigned short ScreenFactory::EDITOR_MENU_CONTROLLER_ID = 4;
const unsigned short ScreenFactory::EDITOR_SERIE_CONTROLLER_ID = 5;
const unsigned short ScreenFactory::OPEN_SERIE_CONTROLLER_ID = 6;
const unsigned short ScreenFactory::EDITOR_LEVEL_CONTROLLER_ID = 7;

/**
 *
 */
controllers::Controller* ScreenFactory::getScreenById(
    unsigned short id
)
{
    switch(id) {
        case MAIN_MENU_CONTROLLER_ID:
            return new controllers::MainMenuController;
        case NEW_GAME_CONTROLLER_ID:
            return new controllers::NewGameController;
        case EDITOR_MENU_CONTROLLER_ID:
            return new controllers::EditorMenuController;
        case EDITOR_SERIE_CONTROLLER_ID:
            return new controllers::EditorSerieController;
        case OPEN_SERIE_CONTROLLER_ID:
            return new controllers::OpenSerieController;
        case EDITOR_LEVEL_CONTROLLER_ID:
            return new controllers::EditorLevelController;
        default:
            return NULL;
    }
}
