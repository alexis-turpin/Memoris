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
 * @file Game.cpp
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Game.hpp"

#include "files.hpp"

#include <string>

namespace memoris
{
namespace entities
{

constexpr char Game::GAMES_FILES_DIRECTORY[];
constexpr char Game::GAMES_FILES_EXTENSION[];

/**
 *
 */
Game::Game() :
    impl(std::make_unique<Impl>())
{
}

/**
 *
 */
void Game::loadGameFromFile(const std::string& gameName) const & noexcept
{
    impl->gameName = gameName;
}

/**
 *
 */
void Game::deleteGameFile() const &
{
    std::string filePath =
        GAMES_FILES_DIRECTORY + impl->gameName + GAMES_FILES_EXTENSION;

    /* TODO: #931 check if the file deletion succeeds */
    std::remove(filePath.c_str());
}

/**
 *
 */
void Game::createFile() const &
{
    std::ofstream file;
    utils::applyFailbitAndBadbitExceptions(file);

    file.open(
        GAMES_FILES_DIRECTORY + impl->gameName + GAMES_FILES_EXTENSION,
        std::fstream::out
    );

    /* std::ofstream is automatically closed at the end of the context */
}

/**
 *
 */
const std::string& Game::getName() const & noexcept
{
    return impl->gameName;
}

}
}
