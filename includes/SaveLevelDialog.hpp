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
 * @file SaveLevelDialog.hpp
 * @brief dialog that is displayed when the 'save' button is pressed down
 * into the level editor
 * @package popups
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_SAVELEVELDIALOG_H_
#define MEMORIS_SAVELEVELDIALOG_H_

#include "Dialog.hpp"

namespace memoris
{

namespace widgets
{
class InputTextWidget;
}

namespace popups
{

class SaveLevelDialog : public Dialog
{

public:

    /**
     * @brief constructor, does nothing for now, only pass the variables to
     * the parent constructor
     *
     * @param context reference to the current context
     */
    SaveLevelDialog(
        utils::Context& context
    );

    /**
     * @brief default constructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~SaveLevelDialog() noexcept;

    /**
     * @brief render the dialog window
     *
     * @param context reference to the current context to use
     */
    void render(utils::Context& context) & override;

    /**
     * @brief getter of the input text widget, used in the level editor,
     * returns a reference of the widget
     *
     * @return widgets::InputTextWidget&
     */
    widgets::InputTextWidget& getInputTextWidget() &;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
