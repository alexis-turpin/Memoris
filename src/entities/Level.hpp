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
 * @file Level.hpp
 * @brief level entity
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_LEVEL
#define DEF_LEVEL

#include <vector>

#include "Cell.hpp"

namespace entities {
class Level {

    static const int LEVEL_CELLS_HEIGHT = 15;
    static const int LEVEL_CELLS_WIDTH = 20;
    static const int CELL_PIXELS_DIMENSIONS = 49;
    static const int CELLS_PIXELS_SEPARATION = 1;

public:

    /**
     * @brief position setter function
     *
     * @param hPosition horizontal position
     * @param vPosition vertical position
     */
    Level(int hPosition, int vPosition);

    /**
     * @brief used to destroy the cells pointers array
     */
    ~Level();

private:

    std::vector<std::vector<Cell*>> cells;

    int horizontalPosition;
    int verticalPosition;
};
}

#endif
