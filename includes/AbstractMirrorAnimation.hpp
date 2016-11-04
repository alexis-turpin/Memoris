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
 * @file AbstractMirrorAnimation.hpp
 * @brief abstract class that manages the level mirror animations
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_ABSTRACTMIRRORANIMATION
#define MEMORIS_ABSTRACTMIRRORANIMATION

#include "LevelAnimation.hpp"

#include "Cell.hpp"

#include <queue>

namespace memoris
{
namespace animations
{

class AbstractMirrorAnimation : public LevelAnimation
{

protected:

    static constexpr sf::Uint32 ANIMATION_STEPS_INTERVAL {50};

    static constexpr unsigned short CELLS_PER_FLOOR {256};
    static constexpr unsigned short CELLS_PER_LINE {16};

    /**
     * @brief increases the transparency
     *
     * not 'const' because it modifies the animated side transparency
     */
    void increaseTransparency() & noexcept;

    /**
     * @brief increases the transparency
     *
     * not 'const' because it modifies the animated side transparency
     */
    void decreaseTransparency() & noexcept;

    /**
     * @brief set the transparency to fully transparent
     *
     * not 'const' because it modifies the animated side transparency
     */
    void setFullTransparent() & noexcept;

    /**
     * @brief set the transparency to no transparent
     *
     * not 'const' because it modifies the animated side transparency
     */
    void setNoTransparent() & noexcept;

    /**
     * @brief applies the current animated side transparency on the given cell
     *
     * @param context constant reference to the current context to use
     * @param level constant reference to a shared pointer on the level
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void applyTransparencyOnOneCell(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& index
    ) const &;

    /* these attributes are not inside an
       implementation as they are protected */

    /* TODO: check if can be deleted */
    std::queue<entities::Cell> savedCells;

private:

    static constexpr float TRANSPARENCY_INTERVAL {51.f};

    float animatedSideTransparency {255.f};
};

}
}

#endif
