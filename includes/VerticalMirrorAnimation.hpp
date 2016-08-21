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
 * @file VerticalMirrorAnimation.hpp
 * @brief plays the vertical mirror animation
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "AbstractMirrorAnimation.hpp"

namespace memoris
{
namespace animations
{

class VerticalMirrorAnimation : public AbstractMirrorAnimation
{

public:

    /**
     * @brief constructor, initializes the separator
     *
     * @param context shared pointer to the context to use
     */
    VerticalMirrorAnimation(
        const std::shared_ptr<utils::Context>& context
    );

    /**
     * @brief renders the animation
     *
     * @param context shared pointer to the current context to use
     * @param level shared pointer to the level to use
     * @param floor the current floor to display in the animation
     */
    void playNextAnimationStep(
        const std::shared_ptr<utils::Context>& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) override;

private:

    /**
     * @brief used for the animation of the grid; this function updates the
     * transparency value of 160 cells starting at the given index; the
     * modification to apply is specified by the 'difference' parameter
     *
     * @param context shared pointer to the current context to use
     * @param level shared pointer to the level to use
     * @param floor the current floor to display in the animation
     * @param difference the color transparency update to apply on the
     * transparency value of the cells textures
     * @param ... specific parameter for the vertical mirror only (check
     * interface documentation for details)
     */
    void setLevelSideCellsTransparency(
        const std::shared_ptr<utils::Context>& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& startingCellIndex,
        const float difference,
        ...
    ) override;

    /**
     * @brief replace the left side cells by the right side cells
     *
     * @param context shared pointer to the current context to use
     * @param level shared pointer to the level to use
     * @param floor the current floor to display in the animation
     */
    void executeMirrorMovement(
        const std::shared_ptr<utils::Context>& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) override;

    /**
     * @brief replace the right side cells by the left side cells
     *
     * @param context shared pointer to the current context to use
     * @param level shared pointer to the level to use
     * @param floor the current floor to display in the animation
     */
    void executeReverseMirrorMovement(
        const std::shared_ptr<utils::Context>& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) override;
};

}
}