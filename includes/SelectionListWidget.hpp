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
 * @file SelectionListWidget.hpp
 * @brief used to select a text item, the widget takes the whole screen,
 * the position and dimensions are fixed
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_SELECTIONLISTWIDGET_H_
#define MEMORIS_SELECTIONLISTWIDGET_H_

#include <memory>
#include <vector>

namespace sf
{
class Sprite;
class Text;
}

namespace memoris
{

namespace utils
{
class Context;
}

namespace widgets
{

class SelectionListWidget
{

public:

    /**
     * @brief constructor, initialize the implementation
     *
     * @param context constant reference to the context to use
     * @param horizontalPosition constant reference to the expected
     * horizontal position
     *
     * not 'noexcept' because it calls SFML function that are not noexcept
     */
    SelectionListWidget(
        const utils::Context& context,
        const float& horizontalPosition = 500.f
    );

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~SelectionListWidget() noexcept;

    /**
     * @brief displays the widget
     *
     * not 'noexcept' because it calls some SFML method that are not noexcept
     *
     * not 'const' because it calls the private method displaySelector()
     * which modifies the object
     */
    void display(const utils::Context& context) &;

    /**
     * @brief setter of the displayed items list
     *
     * @param context reference to the current context to use
     * @param list a constant reference to a vector container of std::string
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void setList(
        const utils::Context& context,
        const std::vector<std::string>& list
    ) const &;

    /**
     * @brief getter of the current pointed item string
     *
     * @return const std::string
     *
     * the returned value is a copy because even if this method returns
     * a container item, it could also return an empty string local literal
     * (""), if the cursor is currently not pointing any item
     */
    const std::string getCurrentItem() const & noexcept;

    /**
     * @brief updates the displayed items list if an arrow is clicked
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void updateList() const &;

    /**
     * @brief deletes the selected item
     *
     * not noexcept because it calls SFML methods, STL containers and iterators
     * methods that are not noexcept
     */
    void deleteSelectedItem() const &;

    /**
     * @brief add one string into the displayed list
     *
     * @param context constant reference to the current context to use
     * @param item constant reference to the string to insert
     */
    void addItem(
        const utils::Context& context,
        const std::string& item
    ) const &;

    /**
     * @brief getter of the stored values in the list
     *
     * @return const std::vector<sf::Text>&
     */
    const std::vector<sf::Text>& getTexts() const & noexcept;

    /**
     * @brief deletes all the items from the list; use std::vector<T>::clear()
     * which does not throw any exception
     */
    void deleteAllItems() const & noexcept;

private:

    static constexpr float VERTICAL_POSITION {200.f};
    static constexpr float WIDTH {600.f};
    static constexpr float HEIGHT {600.f};
    static constexpr float ITEMS_SEPARATION {50.f};

    static constexpr unsigned short ARROW_DIMENSION {64};
    static constexpr unsigned short VISIBLE_ITEMS {12};

    static constexpr short NO_SELECTION_INDEX {-1};

    /**
     * @brief move the visual selector according to the current cursor position
     *
     * @param context reference to the context object to use
     *
     * not 'const' because it modifies the position of the selector
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    void displaySelector(const utils::Context& context) &;

    /**
     * @brief selects an arrow if the mouse is hover
     * 
     * @param context constant reference to the current context
     * @param horizontalPosition horizontal position of the arrow
     * @param arrowSprite reference to the arrow sprite,
     * not constant as the color might be changed
     * @param selected reference to the selection boolean to update
     *
     * not noexcept as it calls SFML functions that are not noexcept
     */
    void selectArrowWhenMouseHover(
        const utils::Context& context,
        const unsigned short& horizontalPosition,
        sf::Sprite& arrowSprite,
        bool& selected
    ) const &;

    /**
     * @brief updates the position of all the items on the list according
     * to the user clicks on the arrow buttons
     *
     * @param movement constant reference to the movement (1 or -1)
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void updateAllItemsPosition(const float& movement) const &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
