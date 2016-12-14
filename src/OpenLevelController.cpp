/*
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
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
 * @file OpenLevelController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "OpenLevelController.hpp"

#include "Context.hpp"
#include "fonts.hpp"
#include "controllers.hpp"
#include "SelectionListWidget.hpp"
#include "DirectoryReader.hpp"
#include "Cursor.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "EditingLevelManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace controllers
{

class OpenLevelController::Impl
{

public:

    Impl(const utils::Context& context) :
        list(context),
        cursor(context)
    {
        title.setFont(context.getFontsManager().getTitleFont());
        title.setString("Open level");
        title.setCharacterSize(memoris::fonts::SUB_TITLE_SIZE);
        title.setColor(context.getColorsManager().getColorLightBlue());
        title.setPosition(
            TITLE_HORIZONTAL_POSITION,
            TITLE_VERTICAL_POSITION
        );

        list.setList(
            context,
            utils::getFilesFromDirectory("data/levels/personals")
        );
    }

    sf::Text title;

    widgets::SelectionListWidget list;

    widgets::Cursor cursor;
};

/**
 *
 */
OpenLevelController::OpenLevelController(const utils::Context& context) :
    Controller(context),
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
OpenLevelController::~OpenLevelController() noexcept = default;

/**
 *
 */
const unsigned short& OpenLevelController::render(
    const utils::Context& context
) &
{
    window.draw(impl->title);

    impl->list.display(context);

    impl->cursor.render(context);

    nextControllerId = animateScreenTransition(context);

    while(window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Escape:
            {

                /* TODO: force the selected level to empty in order to reset
                   the whole level content; this behavior should be changed,
                   we should get back the previously edited level */
                context.getEditingLevelManager().setLevelName("");

                expectedControllerId = LEVEL_EDITOR_CONTROLLER_ID;

                break;
            }
            default:
            {
            }
            }
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            std::string levelName = impl->list.getCurrentItem();

            if (!levelName.empty())
            {
                context.getEditingLevelManager().setLevelName(
                    "personals/" + levelName
                );

                expectedControllerId = LEVEL_EDITOR_CONTROLLER_ID;
            }

            break;
        }
        default:
        {
        }
        }
        break;
    }

    return nextControllerId;
}

}
}
