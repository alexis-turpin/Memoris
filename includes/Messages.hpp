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
 * Messages.
 *
 * @file Messages.hpp
 * @brief message names list sent through the context
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_MESSAGES
#define DEF_MESSAGES

#include <string>

namespace constants
{
class Messages
{
public:

    static const std::string SELECTED_LEVEL_MESSAGE;
    static const std::string OPEN_SERIE_MESSAGE;
    static const std::string PREVIOUS_CONTROLLER_MESSAGE;
};
}

#endif