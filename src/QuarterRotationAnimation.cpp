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
 * @file QuarterRotationAnimation.cpp
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "QuarterRotationAnimation.hpp"

#include "Context.hpp"
#include "SoundsManager.hpp"
#include "Level.hpp"
#include "Cell.hpp"
#include "ColorsManager.hpp"

namespace memoris
{
namespace animations
{

constexpr unsigned short LevelAnimation::TOP_SIDE_LAST_CELL_INDEX;
constexpr unsigned short LevelAnimation::CELLS_PER_LINE;

constexpr sf::Uint32 QuarterRotationAnimation::ANIMATION_STEPS_INTERVAL;

constexpr unsigned short QuarterRotationAnimation::HALF_CELLS_PER_LINE;
constexpr unsigned short QuarterRotationAnimation::ANIMATION_STEPS;

class QuarterRotationAnimation::Impl
{

public:

    /* store one quarter of the cells floor that has to be saved when the
       quarters rotation is applied; we could use a std::queue to automatically
       free the space when the cells are written back on the floor, but the
       container is directly deleted by the animation destructor when the
       animation is finished */
    std::vector<entities::Cell> temporaryCells;

    unsigned short translationSteps {0};
};

/**
 *
 */
QuarterRotationAnimation::QuarterRotationAnimation() noexcept :
    impl(std::make_unique<Impl>())
{
}

/**
 *
 */
QuarterRotationAnimation::~QuarterRotationAnimation() noexcept = default;

/**
 *
 */
void QuarterRotationAnimation::renderAnimation(
    const utils::Context& context,
    const Level& level,
    const unsigned short& floor
) &
{
    if (
        context.getClockMillisecondsTime() -
        lastAnimationUpdateTime < ANIMATION_STEPS_INTERVAL
    )
    {
        level->display(
            context,
            floor,
            &entities::Cell::display
        );

        return;
    }

    if (animationSteps == 0)
    {
        context.getSoundsManager().playFloorMovementAnimationSound();
    }

    moveAllQuarters(
        context,
        level,
        floor
    );

    impl->translationSteps++;

    if (impl->translationSteps == ANIMATION_STEPS)
    {
        updateCells(
            context,
            level,
            floor
        );

        finished = true;
    }

    level->display(
        context,
        floor,
        &entities::Cell::display
    );

    incrementAnimationStep(context);
}

/**
 *
 */
void QuarterRotationAnimation::moveAllQuarters(
    const utils::Context& context,
    const Level& level,
    const unsigned short& floor
) const &
{
    using MovementDirection = entities::Cell::MovementDirection;

    const unsigned short firstIndex = CELLS_PER_FLOOR * floor;
    const unsigned short lastIndex = firstIndex + CELLS_PER_FLOOR;
    const unsigned short topSideLastIndex =
        firstIndex + TOP_SIDE_LAST_CELL_INDEX;

    for (
        unsigned short index = firstIndex;
        index < lastIndex;
        index++
    )
    {
        const unsigned short horizontalSide = index % CELLS_PER_LINE;
        MovementDirection direction {MovementDirection::LEFT};

        if (
            horizontalSide < HALF_CELLS_PER_LINE and
            index < topSideLastIndex
        )
        {
            direction = MovementDirection::DOWN;
            level->getCells()[index]->moveInDirection(direction);
        }
        else if (
            horizontalSide >= HALF_CELLS_PER_LINE and
            index >= topSideLastIndex
        )
        {
            direction = MovementDirection::UP;
            level->getCells()[index]->moveInDirection(direction);
        }
        else if (
            horizontalSide < HALF_CELLS_PER_LINE and
            index >= topSideLastIndex
        )
        {
            direction = MovementDirection::RIGHT;
            level->getCells()[index]->moveInDirection(direction);
        }
        else if (
            horizontalSide >= HALF_CELLS_PER_LINE and
            index < topSideLastIndex
        )
        {
            level->getCells()[index]->moveInDirection(direction);
        }
    }
}

/**
 *
 */
void QuarterRotationAnimation::updateCells(
    const utils::Context& context,
    const Level& level,
    const unsigned short& floor
) & noexcept
{
    const unsigned short firstIndex = floor * CELLS_PER_FLOOR;
    const unsigned short topSideLastIndex =
        firstIndex + TOP_SIDE_LAST_CELL_INDEX;

    for (
        unsigned short index = firstIndex;
        index < topSideLastIndex;
        index++
    )
    {
        const unsigned short horizontalSide = index % CELLS_PER_LINE;

        if (horizontalSide >= HALF_CELLS_PER_LINE)
        {
            invertCells(
                context,
                level,
                index,
                -HALF_CELLS_PER_LINE,
                floor
            );
        }
    }

    const unsigned short floorLastIndex = firstIndex + CELLS_PER_FLOOR;

    for (
        unsigned short index = topSideLastIndex;
        index < floorLastIndex;
        index++
    )
    {
        const unsigned short horizontalSide = index % CELLS_PER_LINE;

        if (horizontalSide >= HALF_CELLS_PER_LINE)
        {
            invertCells(
                context,
                level,
                index,
                -TOP_SIDE_LAST_CELL_INDEX,
                floor
            );
        }
    }

    for (
        unsigned short index = topSideLastIndex;
        index < floorLastIndex;
        index++
    )
    {
        const unsigned short horizontalSide = index % CELLS_PER_LINE;

        if (horizontalSide < HALF_CELLS_PER_LINE)
        {
            invertCells(
                context,
                level,
                index,
                HALF_CELLS_PER_LINE,
                floor
            );
        }
    }

    unsigned short index = floor * CELLS_PER_FLOOR;

    for (const entities::Cell& cell : impl->temporaryCells)
    {
        const unsigned short newIndex = index + TOP_SIDE_LAST_CELL_INDEX;

        level->getCells()[index]->resetPosition();

        level->getCells()[newIndex]->setType(
            cell.getType()
        );

        level->getCells()[newIndex]->setIsVisible(
            cell.isVisible()
        );

        if (index == level->getPlayerCellIndex())
        {
            updatedPlayerIndex = newIndex;
        }

        showOrHideCell(
            context,
            level,
            newIndex,
            cell.isVisible()
        );

        index++;

        if (index % CELLS_PER_LINE >= HALF_CELLS_PER_LINE)
        {
            index += HALF_CELLS_PER_LINE;
        }
    }

    movePlayer(
        context,
        level
    );
}

/**
 *
 */
void QuarterRotationAnimation::invertCells(
    const utils::Context& context,
    const Level& level,
    const unsigned short& index,
    const unsigned short& modification,
    const unsigned short& floor
) & noexcept
{
    const unsigned short newIndex = index + modification;

    /* TODO: this pointer declaration is bad regarding to C++14 specifications;
       the problem is that level->getCells() is an array of unique pointers
       that we cannot copy, and we do not want move the ownership either; as
       we do not want do multiple calls like level->getCells()[newIndex] in the
       body of this function, we just store the pointer this way; a solution
       should be find for this */
    entities::Cell* sourceCell = level->getCells().at(index).get();
    entities::Cell* destinationCell = level->getCells().at(newIndex).get();

    /* if the destination quarter is the top left one,
       save the old cells of this quarter */
    if (
        newIndex < floor * CELLS_PER_FLOOR + TOP_SIDE_LAST_CELL_INDEX and
        newIndex % CELLS_PER_LINE < HALF_CELLS_PER_LINE
    )
    {
        impl->temporaryCells.push_back(*destinationCell);
    }

    if (index == level->getPlayerCellIndex())
    {
        updatedPlayerIndex = newIndex;
    }

    destinationCell->setType(sourceCell->getType());
    destinationCell->setIsVisible(sourceCell->isVisible());

    sourceCell->resetPosition();

    showOrHideCell(
        context,
        level,
        newIndex,
        sourceCell->isVisible()
    );
}

}
}
