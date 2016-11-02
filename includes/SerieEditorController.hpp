/**
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
 * @file SerieEditorController.hpp
 * @package controllers
 * @brief render the serie editor
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_SERIEEDITORCONTROLLER_H_
#define MEMORIS_SERIEEDITORCONTROLLER_H_

#include "Controller.hpp"

namespace memoris
{
namespace controllers
{

class SerieEditorController : public Controller
{

public:

    /**
     * @brief constructor, just used to transfer parameter
     *
     * @param context constant reference to the current context to use
     */
    SerieEditorController(const utils::Context& context);

    /**
     * @brief render the serie editor controller
     *
     * @param context reference to the current context to use
     *
     * @return const unsigned short&
     *
     * the context reference is not constant because this is a virtual method
     * and some definitions have to modify the context attributes
     */
    virtual const unsigned short& render(utils::Context& context) & override;
};

}
}

#endif
