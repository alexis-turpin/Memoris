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
#include "Dimensions.hpp"
#include "Colors.hpp"

using namespace entities;

/**
 *
 */
Cell::Cell()
{
    initializeCommonAttributes();
}

/**
 *
 */
Cell::Cell(const Cell& cell)
{
    initializeCommonAttributes();

    setPicturePath(cell.getPicturePath());

    setPosition(
        cell.getHorizontalPosition(),
        cell.getVerticalPosition()
    );

    setLevelAddresses(cell.getAddress());

    setStringRepresentation(cell.getStringRepresentation());
}

/**
 *
 */
Cell::Cell(std::string fileValue) : stringRepresentation(fileValue)
{
    initializeCommonAttributes();
}

/**
 *
 */
Cell::~Cell()
{
}

/**
 *
 */
void Cell::performAction()
{
}

/**
 *
 */
void Cell::setPosition(
    float hPosition,
    float vPosition
)
{
    horizontalPosition = hPosition;
    verticalPosition = vPosition;

    sprite.setPosition(
        horizontalPosition,
        verticalPosition
    );

    hiddenCellPtr.setSpritePosition(
        horizontalPosition,
        verticalPosition
    );

    topSelectionBar.setPosition(
        horizontalPosition,
        verticalPosition
    );

    bottomSelectionBar.setPosition(
        horizontalPosition,
        verticalPosition +
        constants::Dimensions::CELL_PIXELS_DIMENSIONS -
        constants::Dimensions::SELECTED_CELLS_BORDER_WIDTH
    );

    leftSelectionBar.setPosition(
        horizontalPosition,
        verticalPosition
    );

    rightSelectionBar.setPosition(
        horizontalPosition +
        constants::Dimensions::CELL_PIXELS_DIMENSIONS -
        constants::Dimensions::SELECTED_CELLS_BORDER_WIDTH,
        verticalPosition
    );
}

/**
 *
 */
void Cell::setPicturePath(std::string path)
{
    texture.loadFromFile(path);
    sprite.setTexture(texture, true);

    picturePath = path;
}

/**
 *
 */
std::string Cell::getPicturePath() const
{
    return picturePath;
}

/**
 *
 */
void Cell::display(utils::Context* pContext)
{
    sf::Sprite sprToDspl;

    if (getIsHidden())
    {
        sprToDspl = hiddenCellPtr.getSprite();
    }
    else
    {
        sprToDspl = sprite;
    }

    if (isMouseHover() && isCursorSensitive)
    {
        sprToDspl.setColor(transparentWhiteColor);
    }
    else
    {
        sprToDspl.setColor(whiteColor);
    }

    pContext->getWindow()->draw(sprToDspl);

    if (isSelected)
    {
        pContext->getWindow()->draw(topSelectionBar);
        pContext->getWindow()->draw(bottomSelectionBar);
        pContext->getWindow()->draw(leftSelectionBar);
        pContext->getWindow()->draw(rightSelectionBar);
    }
}

/**
 *
 */
bool Cell::isMouseHover() const
{
    if (
        sf::Mouse::getPosition().x > horizontalPosition &&
        sf::Mouse::getPosition().x < horizontalPosition + constants::Dimensions::CELL_PIXELS_DIMENSIONS &&
        sf::Mouse::getPosition().y > verticalPosition &&
        sf::Mouse::getPosition().y < verticalPosition + constants::Dimensions::CELL_PIXELS_DIMENSIONS
    )
    {
        return true;
    }

    return false;
}

/**
 *
 */
void Cell::setSelected(bool selected)
{
    isSelected = selected;
}

/**
 *
 */
float Cell::getHorizontalPosition() const
{
    return horizontalPosition;
}

/**
 *
 */
float Cell::getVerticalPosition() const
{
    return verticalPosition;
}

/**
 *
 */
void Cell::setLevelAddresses(const uint16_t& cellAddress)
{
    address = cellAddress;
}

/**
 *
 */
uint16_t Cell::getAddress() const
{
    return address;
}

/**
 *
 */
bool Cell::getIsSelected() const
{
    return isSelected;
}

/**
 *
 */
void Cell::setHidden(const bool& hidden)
{
    isHidden = hidden;
}

/**
 *
 */
bool Cell::getIsHidden() const
{
    return isHidden;
}

/**
 *
 */
void Cell::setCursorSensitivity(const bool& sensitivity)
{
    isCursorSensitive = sensitivity;
}

/**
 *
 */
void Cell::initializeCommonAttributes()
{
    isSelected = false;
    isHidden = false;
    isCursorSensitive = true;

    horizontalPosition = 0;
    verticalPosition = 0;
    address = 0;

    transparentWhiteColor.r = constants::Colors::COLOR_WHITE_RED;
    transparentWhiteColor.g = constants::Colors::COLOR_WHITE_GREEN;
    transparentWhiteColor.b = constants::Colors::COLOR_WHITE_BLUE;
    transparentWhiteColor.a = constants::Colors::COLOR_ALPHA_PARTIAL;

    whiteColor.r = constants::Colors::COLOR_WHITE_RED;
    whiteColor.g = constants::Colors::COLOR_WHITE_GREEN;
    whiteColor.b = constants::Colors::COLOR_WHITE_BLUE;
    whiteColor.a = constants::Colors::COLOR_ALPHA_FULL;

    selectorColor.r = constants::Colors::COLOR_RED_RED;
    selectorColor.g = constants::Colors::COLOR_RED_GREEN;
    selectorColor.b = constants::Colors::COLOR_RED_BLUE;
    selectorColor.a = constants::Colors::COLOR_ALPHA_FULL;

    topSelectionBar.setSize(
        sf::Vector2f(
            constants::Dimensions::CELL_PIXELS_DIMENSIONS,
            constants::Dimensions::SELECTED_CELLS_BORDER_WIDTH
        )
    );

    bottomSelectionBar.setSize(
        sf::Vector2f(
            constants::Dimensions::CELL_PIXELS_DIMENSIONS,
            constants::Dimensions::SELECTED_CELLS_BORDER_WIDTH
        )
    );

    leftSelectionBar.setSize(
        sf::Vector2f(
            constants::Dimensions::SELECTED_CELLS_BORDER_WIDTH,
            constants::Dimensions::CELL_PIXELS_DIMENSIONS
        )
    );

    rightSelectionBar.setSize(
        sf::Vector2f(
            constants::Dimensions::SELECTED_CELLS_BORDER_WIDTH,
            constants::Dimensions::CELL_PIXELS_DIMENSIONS
        )
    );

    topSelectionBar.setFillColor(selectorColor);
    bottomSelectionBar.setFillColor(selectorColor);
    leftSelectionBar.setFillColor(selectorColor);
    rightSelectionBar.setFillColor(selectorColor);
}

/**
 *
 */
void Cell::setStringRepresentation(const std::string& representation)
{
    stringRepresentation = representation;
}

/**
 *
 */
std::string Cell::getStringRepresentation() const
{
    return stringRepresentation;
}
