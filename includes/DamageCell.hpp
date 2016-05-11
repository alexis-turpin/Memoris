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
 * @file DamageCell.hpp
 * @brief damage cell entity
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_DAMAGE_CELL
#define DEF_DAMAGE_CELL

#include "Cell.hpp"

#include <string>

namespace entities
{
class DamageCell : public Cell
{

    static const std::string DAMAGE_CELL_PICTURE_PATH;

public:

    DamageCell();

    /**
     * @brief definition of the action to
     * perform when the cell is triggered
     *
     * @param pGameContext pointer to the current game context
     */
    void performAction(utils::GameContext* pGameContext);
};
}

#endif
