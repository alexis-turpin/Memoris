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

#include <cstdarg>

namespace memoris
{
namespace animations
{

/**
 *
 */
VerticalMirrorAnimation::VerticalMirrorAnimation(
    const std::shared_ptr<utils::Context>& context
)
{
    /* initialize the separator surface positions, sizes and color */
    separator.setPosition(798.f, 98.f);
    separator.setFillColor(context->getColorsManager().getColorRed());
    separator.setSize(sf::Vector2f(4.f, 800.f));

    /* plays the mirror animation sound */
    context->getSoundsManager().getMirrorAnimationSound().play();
}

/**
 *
 */
void VerticalMirrorAnimation::playNextAnimationStep(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    unsigned short
    startingLeftSideCellIndex = floor * 320,
    startingRightSideCellIndex = startingLeftSideCellIndex + 10;

    if (animationSteps < 15 && animationSteps >= 10)
    {
        /* make the left side transparent; decrement the alpha value of all
           the side cells by 51; starts from the cell 0 of the given floor;
           go back to the next line every 10 cells */
        setLevelSideCellsTransparency(
            context,
            level,
            startingLeftSideCellIndex,
            -TRANSPARENCY_UPDATE_AMOUNT,
            10
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
            TRANSPARENCY_UPDATE_AMOUNT,
            10
        );
    }
    else if (animationSteps >= 21 && animationSteps < 26)
    {
        /* make the cells of the right side transparent progressively, by
           step of 51 alpha value */
        setLevelSideCellsTransparency(
            context,
            level,
            startingRightSideCellIndex,
            -TRANSPARENCY_UPDATE_AMOUNT,
            20
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
        /* starts at the cell 0 + floor * 320 (top side) and increase the
           transparency value by TRANSPARENCY_UPDATE_AMOUNT at each iteration
           */
        setLevelSideCellsTransparency(
            context,
            level,
            startingRightSideCellIndex,
            TRANSPARENCY_UPDATE_AMOUNT,
            20
        );
    }
    else if (animationSteps == 33)
    {
        /* set the new player cell index */
        level->setPlayerCellIndex(playerCellIndexAfterAnimation);

        /* force the new player cell to be shown, no matter if this cell was
           shown or hidden */
        level->cells[playerCellIndexAfterAnimation]->show(context);

        finished = true;
    }

    /* displays the level and the animation separator */
    displayLevelAndSeparator(
        context,
        level,
        floor
    );

    /* increments the animation step and update the last animation update
       time */
    incrementAnimationStep(context);
}

/**
 *
 */
void VerticalMirrorAnimation::setLevelSideCellsTransparency(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& startingCellIndex,
    const float difference,
    ...
)
{
    /* declare a va_list variable used to find the variadic function
       parameters */
    va_list params;

    /* specify from which parameter address the variadic list starts, in our
       case, right after the 'difference' paramater */
    va_start(params, difference);

    /* use 'int' because va_arg does not work with unsigned short */
    int sideMax = va_arg(params, int);

    /* we could use unsigned short here, but as we are mandatory to use 'int',
       we use it everywhere in the function */
    int index = startingCellIndex;

    animatedSideTransparency += difference;

    while(index <= startingCellIndex + 309)
    {
        level->cells[index]->setCellColorTransparency(
            context,
            animatedSideTransparency
        );

        index++;

        if(index % sideMax == 0 && index != 0)
        {
            index += 10;
        }
    }
}

/**
 *
 */
void VerticalMirrorAnimation::executeMirrorMovement(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    unsigned short
    index = floor * 320 + 10,
    difference = 1,
    end = floor * 320 + 319;

    while(index <= end)
    {
        /* the 'cells' array of the Level entity is a container of pointers;
           we really want to 'copy' the cells here, so we have to use '*' */
        savedCells.push(*(level->cells[index - difference]));

        if (index - difference == level->getPlayerCellIndex())
        {
            playerCellIndexAfterAnimation = index;
        }

        if (index  == level->getPlayerCellIndex())
        {
            playerCellIndexAfterAnimation = index - difference;
        }

        level->cells[index - difference]->setType(
            level->cells[index]->getType()
        );

        showOrHideCell(
            context,
            level,
            index - difference,
            level->cells[index]->isVisible()
        );

        index++;
        difference += 2;

        if (index % 20 == 0)
        {
            index += 10;
            difference = 1;
        }
    }
}

/**
 *
 */
void VerticalMirrorAnimation::executeReverseMirrorMovement(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    unsigned short
    index = floor * 320 + 10,
    it = 0,
    end = floor * 320 + 319;

    while(index <= end)
    {
        level->cells[index]->setType(
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

        if (index % 20 == 0)
        {
            index += 10;
        }
    }
}

}
}