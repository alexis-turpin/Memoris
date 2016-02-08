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
 * @file Level.cpp
 * @brief level entity
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Level.hpp"
#include "EmptyCell.hpp"

using namespace entities;

/**
 *
 */
Level::Level(int hPosition, int vPosition)
{
    horizontalPosition = hPosition;
    verticalPosition = vPosition;

    cells.resize(LEVEL_CELLS_WIDTH);
    for (std::vector<std::vector<Cell*>>::iterator line = cells.begin();
            line != cells.end(); ++line) {

        line->resize(LEVEL_CELLS_HEIGHT);

        for (std::vector<Cell*>::iterator cell = line->begin();
                cell != line->end(); ++cell) {

            (*cell) = new EmptyCell();

            (*cell)->setPosition(
                horizontalPosition +
                static_cast<int>(std::distance(cells.begin(), line)) *
                (CELL_PIXELS_DIMENSIONS + CELLS_PIXELS_SEPARATION),
                verticalPosition +
                static_cast<int>(std::distance(line->begin(), cell)) *
                (CELL_PIXELS_DIMENSIONS + CELLS_PIXELS_SEPARATION)
            );
        }
    }
}

/**
 *
 */
Level::~Level()
{
    for (std::vector<std::vector<Cell*>>::iterator line = cells.begin();
            line != cells.end(); ++line) {
        for (std::vector<Cell*>::iterator cell = line->begin();
                cell != line->end(); ++cell) {
            delete (*cell);
        }
    }
}

/**
 *
 */
void Level::displayAllCells(utils::Context* pContext)
{
    for (std::vector<std::vector<Cell*>>::iterator line = cells.begin();
            line != cells.end(); ++line) {
        for (std::vector<Cell*>::iterator cell = line->begin();
                cell != line->end(); ++cell) {
            pContext->getWindow()->draw((*cell)->getSprite());
        }
    }
}
