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
 * @file Cell.cpp
 * @brief cell entity
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Cell.hpp"

#include "dimensions.hpp"
#include "window.hpp"
#include "Context.hpp"
#include "CellsTexturesManager.hpp"

namespace memoris
{
namespace entities
{

/**
 *
 */
Cell::Cell(
    const float& hPosition,
    const float& vPosition,
    const char& type
)
{
    /* set the given position */
    setPosition(
        hPosition,
        vPosition
    );

    /* get the texture from the cells textures manager according to the type
       of cell; set this reference as a texture for the current cell object */
    sprite.setTexture(
        textures::CellsTexturesManager::get().getTextureReferenceByCellType(
            type
        )
    );
}

/**
 *
 */
void Cell::moveOnTheRight()
{
    /* increment the horizontal position of the cell; we do
       it separately to make it clear */
    horizontalPosition++;

    /* if the cell is outside of the screen on the right side, the position
       is reset to -49 because a cell width is 49 pixel; the cell is now
       outside of the screen, on the left corner and will be displayed soon
       during the animation; we considere the cell outside of the screen on
       the right corner when the position is 1649, that means the window
       width and one cell width */
    if (horizontalPosition == memoris::window::WIDTH)
    {
        /* note that the cell pixel dimensions is forced to be signed */
        horizontalPosition = -memoris::dimensions::CELL_PIXELS_DIMENSIONS;
    }

    /* update the horizontal position */
    setPosition(
        horizontalPosition,
        verticalPosition
    );
}

/**
 *
 */
void Cell::setPosition(
    const float& hPosition,
    const float& vPosition
)
{
    /* save the given values */
    horizontalPosition = hPosition;
    verticalPosition = vPosition;

    /* set the new position of the SFML surface */
    sprite.setPosition(
        horizontalPosition,
        verticalPosition
    );
}

/**
 *
 */
void Cell::display()
{
    /* display the cell sprite */
    utils::Context::get().getSfmlWindow().draw(sprite);
}

/**
 *
 */
void Cell::hide()
{
    sprite.setTexture(
        textures::CellsTexturesManager::get().getHiddenCellTexture()
    );
}

}
}
