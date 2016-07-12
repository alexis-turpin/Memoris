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
 * @file NewGameController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "NewGameController.hpp"

#include "fonts.hpp"
#include "controllers.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"

namespace memoris
{
namespace controllers
{

/**
 *
 */
NewGameController::NewGameController() :
    Controller()
{
    /* initialize the new game screen title; this title is horizontally
       centered and vertically in the top area of the screen */
    title.setFont(memoris::fonts::FontsManager::get().getTitleFont());
    title.setString("New game");
    title.setCharacterSize(memoris::fonts::SUB_TITLE_SIZE);
    title.setColor(memoris::colors::ColorsManager::get().getColorLightBlue());
    title.setPosition(
        620,
        200
    );

    /* initialize the new game label indicating the input text widget should
       contains the new game name; this text is located under the new game
       screen title and before the input text widget */
    explanation.setFont(memoris::fonts::FontsManager::get().getTextFont());
    explanation.setString("Your name :");
    explanation.setCharacterSize(memoris::fonts::TEXT_SIZE);
    explanation.setColor(memoris::colors::ColorsManager::get().getColorWhite());
    explanation.setPosition(
        645,
        380
    );

    /* set the position and the pixels width of the input text widget; the
       widget is just under the explanation label and is horizontaly centered;
       the width of the widget is 600 pixels long */
    inputTextGameName.setLayout(
        500,
        450,
        600
    );

    /* the input text widget can contains 15 characters maximum; with this
       amount, we can create a lot of different names and we are sure that
       the text won't overflow the widget width */
    inputTextGameName.setMaximumCharacters(15);
}


/**
 *
 */
unsigned short NewGameController::render()
{
    /* display the title and the explanation labels */
    utils::Context::get().getSfmlWindow().draw(title);
    utils::Context::get().getSfmlWindow().draw(explanation);

    /* render the input text widget */
    inputTextGameName.display();

    /* render the opening/closing animation if necessary, get the next
       controller id at the end of the closing animation if the expected
       controller id has been modified */
    nextControllerId = animateScreenTransition();

    /* new game controller events loop; update the text displayed inside the
       input text widget; go back to the main menu if the Escape key is
       pressed; directly go to the series menu if the Enter key is pressed */
    while(utils::Context::get().getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            /* go back to the main menu if the Escape key is pressed */
            case sf::Keyboard::Escape:
            {
                expectedControllerId =
                    MAIN_MENU_CONTROLLER_ID;

                break;
            }
            /* go to the serie main menu controller if the Enter key is
               pressed */
            /* TODO: #497 should not be allowed if the input text widget is
               empty */
            /* TODO: #498 should not be allowed if the name already exists */
            case sf::Keyboard::Return:
            {
                expectedControllerId =
                    SERIE_MAIN_MENU_CONTROLLER_ID;

                break;
            }
            /* if any other key is pressed, the event object reference is
               sent to the input text widget; the widget will check if the
               key is a letter and displays it */
            default:
            {
                inputTextGameName.update(&event);

                break;
            }
            }
        }
        default:
        {
            /* empty default block for coding style requirements */
            break;
        }
        }
    }

    return nextControllerId;
}

}
}
