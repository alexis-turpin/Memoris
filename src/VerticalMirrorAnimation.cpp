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
 * @file VerticalMirrorAnimation.cpp
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "VerticalMirrorAnimation.hpp"

#include "SoundsManager.hpp"
#include "ShapesManager.hpp"
#include "Level.hpp"

namespace memoris
{
namespace animations
{

/**
 *
 */
VerticalMirrorAnimation::VerticalMirrorAnimation(
    utils::Context& context
)
{
    context.getSoundsManager().playMirrorAnimationSound();
}

/**
 *
 */
void VerticalMirrorAnimation::playNextAnimationStep(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) &
{
    unsigned short startingLeftSideCellIndex = floor * 256,
                   startingRightSideCellIndex = startingLeftSideCellIndex + 8;

    if (animationSteps < 15 && animationSteps >= 10)
    {
        /* make the left side transparent; decrement the alpha value of all
           the side cells by 51; starts from the cell 0 of the given floor;
           go back to the next line every 8 cells */
        setLevelSideCellsTransparency(
            context,
            level,
            startingLeftSideCellIndex,
            -51.f
        );
    }
    else if (animationSteps == 15)
    {
        /* copy the right cells on the left side */
        executeMirrorMovement(
            context,
            level,
            floor
        );
    }
    else if (animationSteps >= 16 && animationSteps < 21)
    {
        /* show back the left side cells */
        setLevelSideCellsTransparency(
            context,
            level,
            startingLeftSideCellIndex,
            51.f
        );
    }
    else if (animationSteps >= 21 && animationSteps < 26)
    {
        /* switch from one side to another, so change the maximum step */
        sideMax = 16;

        /* make the cells of the right side transparent progressively, by
           step of 51 alpha value */
        setLevelSideCellsTransparency(
            context,
            level,
            startingRightSideCellIndex,
            -51.f
        );
    }
    else if (animationSteps == 26)
    {
        /* show back the right side cells */
        executeReverseMirrorMovement(
            context,
            level,
            floor
        );
    }
    else if (animationSteps >= 26 && animationSteps < 32)
    {
        /* starts at the cell 0 + floor * 256 (top side) and increase the
           transparency value by 51.f at each iteration
           */
        setLevelSideCellsTransparency(
            context,
            level,
            startingRightSideCellIndex,
            51.f
        );
    }
    else if (animationSteps == 33)
    {
        /* set the new player cell index */
        level->setPlayerCellIndex(playerCellIndexAfterAnimation);

        /* force the new player cell to be shown, no matter if this cell was
           shown or hidden */
        level->getCells()[playerCellIndexAfterAnimation]->show(context);

        finished = true;
    }

    level->display(
        context,
        floor,
        &entities::Cell::display
    );

    context.getSfmlWindow().draw(
        context.getShapesManager().getVerticalSeparator()
    );

    /* increments the animation step and update the last animation update
       time */
    incrementAnimationStep(context);
}

/**
 *
 */
void VerticalMirrorAnimation::setLevelSideCellsTransparency(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& startingCellIndex,
    const float& difference
) &
{
    unsigned short index = startingCellIndex;

    animatedSideTransparency += difference;

    while(index <= startingCellIndex + 247)
    {
        level->getCells()[index]->setCellColorTransparency(
            context,
            animatedSideTransparency
        );

        index++;

        if(index % sideMax == 0 && index != 0)
        {
            index += 8;
        }
    }
}

/**
 *
 */
void VerticalMirrorAnimation::executeMirrorMovement(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) &
{
    unsigned short index = floor * 256 + 8,
                   difference = 1,
                   end = floor * 256 + 255;

    while(index <= end)
    {
        /* the 'cells' array of the Level entity is a container of pointers;
           we really want to 'copy' the cells here, so we have to use '*' */
        savedCells.push(*(level->getCells()[index - difference]));

        if (index - difference == level->getPlayerCellIndex())
        {
            playerCellIndexAfterAnimation = index;
        }

        if (index  == level->getPlayerCellIndex())
        {
            playerCellIndexAfterAnimation = index - difference;
        }

        level->getCells()[index - difference]->setType(
            level->getCells()[index]->getType()
        );

        showOrHideCell(
            context,
            level,
            index - difference,
            level->getCells()[index]->isVisible()
        );

        index++;
        difference += 2;

        if (index % 16 == 0)
        {
            index += 8;
            difference = 1;
        }
    }
}

/**
 *
 */
void VerticalMirrorAnimation::executeReverseMirrorMovement(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) &
{
    unsigned short index = floor * 256 + 8,
                   it = 0,
                   end = floor * 256 + 255;

    while(index <= end)
    {
        level->getCells()[index]->setType(
            savedCells.front().getType()
        );

        showOrHideCell(
            context,
            level,
            index,
            savedCells.front().isVisible()
        );

        savedCells.pop();

        index++;
        it++;

        if (index % 16 == 0)
        {
            index += 8;
        }
    }
}

}
}
