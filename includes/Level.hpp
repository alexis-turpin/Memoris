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
 * @file Level.hpp
 * @brief level entity, contains all the cells
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_LEVEL_H_
#define MEMORIS_LEVEL_H_

#include <memory>

#include "aliases.hpp"

#include <SFML/Config.hpp>

namespace memoris
{

namespace entities
{
class Cell;
}

namespace utils
{
class Context;
}

namespace entities
{

class Level
{

public:

    static constexpr unsigned short MIN_FLOOR {0};
    static constexpr unsigned short MAX_FLOOR {9};

    /**
     * @brief constructor that initializes a level full of wall cells
     *
     * @param context constant reference to the current context
     */
    Level(const utils::Context& context);

    /**
     * @brief constructor that initializes a level from a specific file
     *
     * @param context constant reference to the current context
     * @param fileName constant reference to a string that contains the file
     * name
     *
     * @throw std::invalid_argument the level file cannot be opened
     */
    Level(
        const utils::Context& context,
        const std::string& fileName
    );

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~Level() noexcept;

    /**
     * @brief render the level and all the cells of the given floor; this
     * method is optimized and only calculate/render/display the cells of
     * the given floor; the other cells are totally ignored
     *
     * @param context reference to the current context to use
     * @param floor the floor to render
     * @param Cell object method pointer to the cell display() method to use
     */
    void display(
        const utils::Context& context,
        const unsigned short& floor,
        void (Cell::*display)(
            const utils::Context&,
            aliases::ConstTransformUniquePtrRef
        )
    ) const;

    /**
     * @brief hides all the cells of the level, call the method (hide()) for
     * all of them except for departure cell(s)
     *
     * @param context reference to the current context to use
     */
    void hideAllCellsExceptDeparture(
        const utils::Context& context
    );

    /**
     * @brief update the transparency value of the current player color
     *
     * @param context reference to the current context
     * @param alpha the current player cell transparency value; we use a
     * sf::Uint8 value as this is the type used to set the colors of a
     * sf::Color object
     */
    void setPlayerCellTransparency(
        const utils::Context& context,
        const sf::Uint8& alpha
    );

    /**
     * @brief move the player down if possible
     *
     * @param move the value (positive or negative) to apply on the current
     * player index; defines the mouvement of the player
     * @param context reference to the current context to use
     */
    void movePlayer(
        const utils::Context& context,
        const short& movement
    );

    /**
     * @brief check if the player is allowed to perform the given movement;
     * this function is called from the game controller each time the player
     * trigger an event to move on the level
     *
     * @param move the value (positive or negative) to apply on the current
     * player index; defines the mouvement of the player; this check is
     * separated into a dedicated method for better code organisation
     * @param floor the current player floor number
     *
     * @return bool
     */
    bool allowPlayerMovement(
        const short& movement,
        const unsigned short& floor
    ) const;

    /**
     * @brief get the current player cell type; this getter is used into the
     * game controller to execute the correct current player cell event action
     *
     * @return const char&
     */
    const char& getPlayerCellType() const;

    /**
     * @brief check if the expected cell after the movement is a wall cell,
     * if yes, show the wall cell and forbid the movement; this function is
     * called by the game controller when the player is allowed to move, we
     * check if the user is currently in collision with a wall; if there is
     * a collision, the wall is shown
     *
     * @param context reference to the current context
     * @param movement the movement direction, the same as movePlayer()
     *
     * @return bool
     */
    bool detectWalls(
        const utils::Context& context,
        const short& movement
    ) const;

    /**
     * @brief updates the current player cell to an empty cell, whatever the
     * previous type; this method is called by the game controller to empty
     * a cell when the player leaves it; this method automatically forces the
     * load of a new texture for the player cell
     *
     * @param context reference to the current context
     */
    void emptyPlayerCell(
        const utils::Context& context
    );

    /**
     * @brief moves the current player to the next floor if possible,
     * returns true if the action has been executed, false if it is not
     * possible to move to the next floor
     *
     * @param context reference to the current context
     *
     * @bool true if the player moved to the next floor
     */
    bool movePlayerToNextFloor(const utils::Context& context);

    /**
     * @brief moves the current player to the previous floor if possible,
     * returns true if the action has been executed, false if it is not
     * possible to move to the previous floor
     *
     * @param context reference to the current context to use
     *
     * @bool true if the player moved to the previous floor
     */
    bool movePlayerToPreviousFloor(
        const utils::Context& context
    );

    /**
     * @brief getter of the total stars amount in the level; this is used by
     * the game controller to check when the user got all the stars of the
     * current played level
     *
     * @return const unsigned short&
     */
    const unsigned short& getStarsAmount();

    /**
     * @brief getter for the amount of playable floors; this is used to select
     * which floors have to be displayed during the watching period; this
     * amount is generated during the loading process of the level; it contains
     * the amount of floors (from the first one included) that contains at
     * least one non-empty cell
     *
     * @return const unsigned short&
     */
    const unsigned short& getPlayableFloors();

    /**
     * @brief getter for the current player floor index; we do not return
     * a reference because there is no attribute to store the player floor
     *
     * @return const unsigned short
     */
    const unsigned short getPlayerFloor();

    /**
     * @brief plays the floor transition animation; for now, the unique
     * animation renders a verical column that scroll the whole floor and
     * displays the next floor;
     *
     * @param context reference to the current context
     *
     * NOTE: this method must be called instead of 'display()' during the
     * animation
     */
    void playFloorTransitionAnimation(const utils::Context& context);

    /**
     * @brief setter for the animation boolean
     *
     * @param animate true if the animation must be rendered; the animation
     * can be displayed using the method playFloorTransitionAnimation()
     */
    void setAnimateFloorTransition(const bool& animate);

    /**
     * @brief getter for the animation boolean
     *
     * @return const bool&
     */
    const bool& getAnimateFloorTransition();

    /**
     * @brief getter for the minutes amount loaded from the level file
     *
     * @return const unsigned short&
     */
    const unsigned short& getMinutes() const;

    /**
     * @brief getter for the seconds amount loaded from the level file
     *
     * @return const unsigned short&
     */
    const unsigned short& getSeconds() const;

    /**
     * @brief getter of the player cell index
     *
     * @return const unsigned short&
     */
    const unsigned short& getPlayerCellIndex() const;

    /**
     * @brief setter of the player cell index
     *
     * @param index the value to set for the player cell index
     */
    void setPlayerCellIndex(const unsigned short& index);

    /**
     * @brief set the transparency of all the cells of the given floor
     *
     * @param context shared pointer to the context to use
     * @param transparency the value of SFML transparency
     * @param floor the concerned floor index
     */
    void setCellsTransparency(
        const utils::Context& context,
        const float& transparency,
        const unsigned short& floor
    ) &;

    /**
     * @brief getter of the cells container; returns a reference to the
     * container; we return a constant reference to the container; in that
     * case, the elements of the container cannot be modified (that means
     * each pointer into the container cannot be replaced by another one)
     * but the objects pointed by those pointers can be modified
     *
     * @return const std::vector<std::unique_ptr<Cell>>&
     */
    const std::vector<std::unique_ptr<Cell>>& getCells() const & noexcept;

    /**
     * @brief dynamically create a SFML transform object pointed by the
     * 'transform' pointer, member of this class
     */
    void createTransform();

    /**
     * @brief dynamically delete the SFML transform object pointed by the
     * 'transform' pointer, member of this class
     */
    void deleteTransform();

    /**
     * @brief rotate all the cells with the given amount of degrees; the
     * center of the rotation is the level floor center
     *
     * @param degrees amount of degrees for the rotation
     *
     * NOTE: the function createTransform() has to be called AFTER the
     * dynamic creation of a SFML transform object (createTransform()).
     */
    void rotateAllCells(const short& degrees);

    /**
     * @brief check if the mouse is hover a cell on the current floor of the
     * the level and replace it with the given type; returns a boolean that
     * indicates if the level has been modified or not
     *
     * @param context current context
     * @param floor the current level floor displayed
     * @param type the type to apply on the 'mouse hover cell'
     *
     * @return const bool
     *
     * does not return a reference to a bool because the returned boolean is
     * a local variable of the method
     */
    const bool updateSelectedCellType(
        const utils::Context& context,
        const unsigned short& floor,
        const char& type
    );

    /**
     * @brief refresh all the cells and reset them to wall cells
     *
     * @param context reference to the current context to use
     *
     * @throws std::terminate something wrong happened in the for_each
     * algorithm (functions that are called there may throw exceptions as
     * they are not declared noexcept)
     * @throws std::bad_alloc for_each algorithm failed to allocate memory
     *
     * not 'const' because it modifies the cells inside the cells container
     *
     * not 'noexcept' because it could throw exceptions; those exceptions are
     * never caught and the program just stops if it happens
     */
    void refresh(const utils::Context& context) &;

    /**
     * @brief getter of the player cell horizontal position
     *
     * @return const float&
     */
    const float& getPlayerCellHorizontalPosition() const & noexcept;

    /**
     * @brief getter of the player cell vertical position
     *
     * @return const float&
     */
    const float& getPlayerCellVerticalPosition() const & noexcept;

    /**
     * @brief show all the cells (this is used by the level editor, just
     * after a level has been tested; in fact, the level object is the same,
     * so some cells have been hidden during the game)
     *
     * @param context constant reference to the current context to use
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void showAllCells(const utils::Context& context) const &;

    /**
     * @brief checks if the level has exactly one departure and one arrival;
     * this method is used to check if the level can be tested in the
     * level editor
     *
     * @return const bool
     *
     * the returned value is directly created into the method
     */
    const bool hasOneDepartureAndOneArrival() const & noexcept;

    /**
     * @brief set the player on the departure cell if it exists; counts the
     * total amount of stars on the level; this method is used by the game
     * controller in order to initialize a level that is edited
     */
    void initializeEditedLevel() const & noexcept;

    /**
     * @brief creates and returns an array of characters representing the level
     *
     * @return const std::vector<char>
     *
     * the returned value is directly created into the method, so the function
     * does not return a reference
     */
    const std::vector<char> getCharactersList() const & noexcept;

    /**
     * @brief update the cells of the level according to a given list
     * of characters
     *
     * @param characters array of characters
     */
    void setCellsFromCharactersList(const std::vector<char>& characters)
        const &;

private:

    static constexpr unsigned short CELLS_PER_FLOOR {256};
    static constexpr unsigned short CELLS_PER_LINE {16};
    static constexpr unsigned short CELLS_PER_LEVEL {2560};

    /**
     * @brief called by the constructor to update the cursor position during
     * the level creation
     */
    void updateCursors() const & noexcept;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
