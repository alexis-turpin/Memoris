/**
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
 * @file LevelEditorController.cpp
 * @brief render the level editor
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "LevelEditorController.hpp"

#include "controllers.hpp"
#include "fonts.hpp"
#include "dialogs.hpp"
#include "files.hpp"
#include "InputTextWidget.hpp"
#include "EditorDashboard.hpp"
#include "CellsSelector.hpp"
#include "Level.hpp"
#include "Cursor.hpp"
#include "EditingLevelManager.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "Cell.hpp"
#include "MessageForeground.hpp"
#include "InputTextForeground.hpp"
#include "SelectionListWidget.hpp"
#include "PlayingSerieManager.hpp"

#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace controllers
{

using Action = utils::EditorDashboard::Action;

constexpr const char* LevelEditorController::UNNAMED_LEVEL;
constexpr const char* LevelEditorController::SAVE_LEVEL_NAME_MESSAGE;
constexpr const char* LevelEditorController::ERASE_LEVEL_MESSAGE;

constexpr float LevelEditorController::CELLS_DEFAULT_TRANSPARENCY;

constexpr unsigned short LevelEditorController::FIRST_FLOOR_INDEX;

class LevelEditorController::Impl
{

public:

    Impl(
        const utils::Context& context,
        const Level& levelPtr,
        const bool& displayTime
    ) :
        dashboard(context),
        selector(context),
        level(levelPtr),
        cursor(context),
        displayTime(displayTime)
    {
        const auto& name = context.getEditingLevelManager().getLevelName();
        const auto& font = context.getFontsManager().getTextFont();
        const auto& colorsManager = context.getColorsManager();
        const auto& white = colorsManager.getColorWhite();

        std::string levelName = name.empty() ? UNNAMED_LEVEL : name;

        levelNameSurface.setString(levelName);
        levelNameSurface.setFont(font);
        levelNameSurface.setColor(white);
        levelNameSurface.setCharacterSize(fonts::TEXT_SIZE);
        levelNameSurface.setPosition(
            TITLES_HORIZONTAL_POSITION - 
                levelNameSurface.getLocalBounds().width,
            0.f
        );

        floorSurface.setFont(font);
        floorSurface.setColor(white);
        floorSurface.setCharacterSize(fonts::TEXT_SIZE);
        floorSurface.setString("1");
        floorSurface.setPosition(
            1240.f,
            450.f
        );

        if (displayTime)
        {
            testedTime.setColor(white);
            testedTime.setString(
                context.getPlayingSerieManager().getPlayingTimeAsString()
            );
        }
        else
        {
            testedTime.setColor(colorsManager.getColorRed());
            testedTime.setString("Not tested yet");
        }

        testedTime.setFont(font);
        testedTime.setCharacterSize(fonts::INFORMATION_SIZE);
        testedTime.setPosition(
            TITLES_HORIZONTAL_POSITION - testedTime.getLocalBounds().width,
            50.f
        );

        /* if the previous controller was the game controller, so some cells
           have been hidden during the game; this function is useless when
           the editor is loaded from the menu */
        level->showAllCells(context);

        level->setCellsTransparency(
            context,
            CELLS_DEFAULT_TRANSPARENCY,
            FIRST_FLOOR_INDEX
        );
    }

    utils::EditorDashboard dashboard;

    utils::CellsSelector selector;

    /* use a pointer here for two reasons: this is faster to copy from one
       method to another, especially after creation into controllers.cpp; we
       have no other choice that creating the Level object into controllers.cpp
       and we still want access it into the controller, so we can not use a
       simple Level reference as the original object would be destroyed */
    std::shared_ptr<entities::Level> level;

    unsigned short floor {0};

    Action currentActionId {Action::EXIT};

    widgets::Cursor cursor;

    sf::Text levelNameSurface;
    sf::Text floorSurface;
    sf::Text testedTime;

    std::unique_ptr<foregrounds::MessageForeground>
        newLevelForeground {nullptr};

    std::unique_ptr<foregrounds::InputTextForeground>
        saveLevelForeground {nullptr};

    bool newFile {false};
    bool displayTime;
};

/**
 *
 */
LevelEditorController::LevelEditorController(
    const utils::Context& context,
    const Level& level,
    const bool& displayTime
) :
    Controller(context),
    impl(
        std::make_unique<Impl>(
            context,
            level,
            displayTime
        )
    )
{
}

/**
 *
 */
LevelEditorController::~LevelEditorController() noexcept = default;

/**
 *
 */
const unsigned short& LevelEditorController::render(
    const utils::Context& context
) &
{
    // std::unique_ptr<Level>&
    auto& level = impl->level;

    // std::unique_ptr<NewLevelForeground>&
    auto& newLevelForeground = impl->newLevelForeground;
    auto& saveLevelForeground = impl->saveLevelForeground;

    auto& levelNameSurface = impl->levelNameSurface;

    auto& newFile = impl->newFile;

    if (newLevelForeground != nullptr)
    {
        newLevelForeground->render(context);
    }
    else if (saveLevelForeground != nullptr)
    {
        saveLevelForeground->render(context);
    }
    else
    {
        impl->dashboard.display(context);
        impl->selector.display(context);

        level->display(
            context,
            impl->floor,
            &entities::Cell::displayWithMouseHover
        );

        context.getSfmlWindow().draw(levelNameSurface);
        context.getSfmlWindow().draw(impl->floorSurface);
        context.getSfmlWindow().draw(impl->testedTime);

        impl->cursor.render(context);
    }

    nextControllerId = animateScreenTransition(context);

    while(context.getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                if (newLevelForeground != nullptr)
                {
                    newLevelForeground.reset();
                }
                else if (saveLevelForeground != nullptr)
                {
                    saveLevelForeground.reset();
                }

                break;
            }
            case sf::Keyboard::Return:
            {
                if (newLevelForeground != nullptr)
                {
                    level->refresh(context);

                    newLevelForeground.reset();

                    changeLevelName(
                        context,
                        UNNAMED_LEVEL
                    );

                    newFile = false;
                }

                else if (saveLevelForeground != nullptr)
                {
                    // const std::string&
                    const auto& levelName =
                        saveLevelForeground->getInputTextWidget().getText()
                            .toAnsiString();

                    if (levelName.empty())
                    {
                        break;
                    }

                    saveLevelFile(
                        levelName,
                        level->getCells()
                    );

                    changeLevelName(
                        context,
                        levelName
                    );

                    saveLevelForeground.reset();
                }
            }
            default:
            {
                if (saveLevelForeground != nullptr)
                {
                    saveLevelForeground->getInputTextWidget().update(event);
                }
            }
            }

            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            /* the mouse is not used if a foreground is displayed */
            if (newLevelForeground != nullptr)
            {
                break;
            }

            const auto displayedName =
                levelNameSurface.getString().toAnsiString();

            const auto& levelManager = context.getEditingLevelManager();

            switch(impl->dashboard.getActionIdBySelectedButton())
            {
            case Action::NEW:
            {
                impl->newLevelForeground =
                    std::make_unique<foregrounds::MessageForeground>(
                        context,
                        ERASE_LEVEL_MESSAGE
                    );

                break;
            }
            case Action::EXIT:
            {
                levelManager.setLevelName("");
                levelManager.setLevel(nullptr);

                levelManager.refreshLevel();

                expectedControllerId = EDITOR_MENU_CONTROLLER_ID;

                break;
            }
            case Action::SAVE:
            {
                if (not impl->displayTime)
                {
                    break;
                }

                std::string levelName =
                    context.getEditingLevelManager().getLevelName();

                if (displayedName != UNNAMED_LEVEL)
                {
                    const bool updatedLevel = displayedName.back() == '*';

                    /* if the level is not saved yet,
                       a star is displayed after the name */
                    if ((not levelName.empty() and updatedLevel) or newFile)
                    {
                        saveLevelFile(
                            levelName,
                            level->getCells()
                        );

                        /* remove the asterisk at the end
                           of the displayed level name */
                        levelNameSurface.setString(levelName);

                        updateLevelNameSurfacePosition();
                    }

                    break;
                }

                saveLevelForeground =
                    std::make_unique<foregrounds::InputTextForeground>(
                        context,
                        SAVE_LEVEL_NAME_MESSAGE
                    );

                newFile = true;

                impl->currentActionId = Action::SAVE;

                break;
            }
            case Action::UP:
            {
                if (impl->floor != entities::Level::MAX_FLOOR)
                {
                    impl->floor++;

                    impl->floorSurface.setString(
                        std::to_string(
                            impl->floor + 1
                        )
                    );
                }

                break;
            }
            case Action::DOWN:
            {
                if (impl->floor != entities::Level::MIN_FLOOR)
                {
                    impl->floor--;

                    impl->floorSurface.setString(
                        std::to_string(
                            impl->floor + 1
                        )
                    );
                }

                break;
            }
            case Action::PLAY:
            {
                if (not level->hasOneDepartureAndOneArrival())
                {
                    break;
                }

                level->initializeEditedLevel();

                expectedControllerId = GAME_CONTROLLER_ID;

                auto& level = impl->level;
                levelManager.setLevel(level);
                levelManager.setCellsBackup(
                    level->getCharactersList()
                );

                context.getPlayingSerieManager().reinitialize();

                break;
            }
            default:
            {
            }
            }

            impl->selector.selectCell(context);

            if(
                level->updateSelectedCellType(
                    context,
                    impl->floor,
                    impl->selector.getSelectedCellType()
                ) and
                displayedName.back() != '*' and
                displayedName != UNNAMED_LEVEL
            )
            {
                levelNameSurface.setString(
                    levelNameSurface.getString() + "*"
                );

                updateLevelNameSurfacePosition();
            }
        }
        default:
        {
        }
        }
    }

    return nextControllerId;
}

/**
 *
 */
void LevelEditorController::updateLevelNameSurfacePosition() const &
{
    impl->levelNameSurface.setPosition(
        1200.f - impl->levelNameSurface.getLocalBounds().width,
        0.f
    );
}

/**
 *
 */
void LevelEditorController::saveLevelFile(
    const std::string& name,
    aliases::ConstUniquePtrCellsContainerRef cells
) const &
{
    std::ofstream file;
    utils::applyFailbitAndBadbitExceptions(file);

    file.open(
        "data/levels/personals/" + name + ".level",
        std::fstream::out
    );

    std::string cellsStr;

    cellsStr += std::to_string(impl->level->getMinutes()) + '\n';
    cellsStr += std::to_string(impl->level->getSeconds()) + '\n';

    for (
        std::vector<std::unique_ptr<entities::Cell>>::const_iterator iterator =
            cells.cbegin();
        iterator != cells.cend();
        iterator++
    )
    {
        cellsStr += (*iterator)->getType();
    }

    file << cellsStr;
}

/**
 *
 */
void LevelEditorController::changeLevelName(
    const utils::Context& context,
    const std::string& levelName
) const &
{
    impl->levelNameSurface.setString(levelName);

    context.getEditingLevelManager().setLevelName(
        levelName
    );

    updateLevelNameSurfacePosition();
}

}
}
