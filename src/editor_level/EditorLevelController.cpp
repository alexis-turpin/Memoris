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
 * Editor of levels.
 *
 * @file EditorLevelController.cpp
 * @brief levels editor
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "EditorLevelController.hpp"

#include "../defines/Positions.hpp"
#include "../defines/Dimensions.hpp"

using namespace controllers;

const std::string EditorLevelController::EDITOR_LEVEL_BUTTON_EXIT_TEXT = "Exit";
const std::string EditorLevelController::STRING_EDITOR_LEVEL_TITLE = "Level editor";

/**
 *
 */
EditorLevelController::EditorLevelController() : Controller()
{
    titleBar.setDisplayedText(
        STRING_EDITOR_LEVEL_TITLE
    );

    buttonExit.setLabel(EDITOR_LEVEL_BUTTON_EXIT_TEXT);

    buttonExit.setLayout(
        constants::Positions::EDITOR_BUTTONS_EXIT_POSITION_X,
        constants::Positions::EDITOR_BUTTONS_POSITION_Y,
        constants::Dimensions::EDITOR_BUTTONS_WIDTH
    );
}

/**
 *
 */
unsigned char EditorLevelController::render(utils::Context* context)
{
    titleBar.display(context);
    buttonExit.display(context);

    cursor.display(context);

    while(context->getWindow()->pollEvent(event)) {
        switch(event.type) {
            case sf::Event::MouseButtonPressed: {
                switch(event.mouseButton.button) {
                    case sf::Mouse::Left: {
                        if(buttonExit.isMouseHover()) {
                            nextControllerId = factories::ScreenFactory::MAIN_MENU_CONTROLLER_ID;
                        }
                    }
                }
            }
        }
    }

    return nextControllerId;
}