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
 * @file SelectionListWidget.hpp
 * @brief used to select a text item, the widget takes the whole screen,
 * the position and dimensions are fixed
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_SELECTIONLISTWIDGET_H_
#define MEMORIS_SELECTIONLISTWIDGET_H_

#include <memory>

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
     * @param context reference to the context to use
     *
     * not 'noexcept' because it calls SFML function that are not noexcept
     */
    SelectionListWidget(utils::Context& context);

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~SelectionListWidget() noexcept;

    /**
     * @brief displays the widget
     *
     * the context is not 'const' because the current method calls some not
     * const method of Context
     *
     * not 'noexcept' because it calls some SFML method that are not noexcept
     */
    void display(utils::Context& context) const &;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif