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
 * @file Controller.hpp
 * @brief parent class for all controllers
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_CONTROLLER_H_
#define MEMORIS_CONTROLLER_H_

#include "Context.hpp"

namespace memoris
{
namespace controllers
{
class Controller
{
public:

    /**
     * NOTE: the constructor, destructor and render functions are public
     * as they are called from the program main algorithm (main.cpp)
     */

    /**
     * @brief constructor, initialize variables and load in memory the
     * transition surface (used for screens transition animation)
     */
    Controller();

    /**
     * @brief destructor, does nothing, only used to respect the rule saying
     * that if a child object is pointed by a parent pointer, deleting the
     * pointer should also correctly call the child destructor; the destructor
     * of the parent must be virtual
     */
    virtual ~Controller();

    /**
     * @brief pure virtual function to render the current screen, must be
     * defined into each controller; contains all the elements to render,
     * animations and events to manage; returns the id of the next controller
     * to load and to display (returns 0 if no controller has to be loaded
     * and only the current controller must be displayed)
     *
     * @return unsigned short
     */
    virtual unsigned short render() = 0;

protected:

    /**
     * @brief render the controller switching animation (the animation that
     * is rendered when one screen is closed and a new one is opened, also
     * rendered when the first screen is opened and when the last screen is
     * closed); starts to animate when the expectedControllerId protected
     * value is updated inside the current controller (usually when a menu
     * item is selected, an event occured or a button is pressed); the function
     * returns 0 as long as no animation is rendering or when the animation is
     * rendering; the function returns the expectedControllerId when the
     * animtation (opening or closing) is terminated; this id can be stored
     * in the nextControllerId and the screen can be switched.
     *
     * @return unsigned short
     *
     * NOTE: must be called inside the render method of a controller,
     * because the screen is still rendered even when the controllers switching
     * animation is displayed; the screen switching process is not handled
     * by this function
     */
    unsigned short animateScreenTransition();


    /* the controller SFML event manager; there is no need to declare a SFML
       event manager inside each controller, this is done here */
    sf::Event event;

    /* must be returned by the render method in every controller; contains the
       id of the next controller to load; contains 0 if no new controller has
       to be rendered and if there is no controller switch at the moment */
    unsigned short nextControllerId;

    /* must be changed inside the render method of the current rendered
       controller when a new controller has to be rendered; usually, this
       expected controller id is verified inside the animation method; if it
       is not equal to 0, the closing animation is started; at the end of the
       animation, the next controller id becomes equal to the expected
       controller id and the controllers can be switched; contains 0 if no new
       controller has to be rendered and if there is no controller switch at
       the moment */
    unsigned short expectedControllerId;

    /* this boolean is true if the opening animation is currently rendering and
       is false if the opening animation is not rendering; this boolean is true
       everytime a new controller is opened, while the opening animation is not
       finished, then it becomes false */
    bool openingScreen;

private:

    /* NOTE: we use SFML 32 bits long integers to save the
       last updated time of each animation; we use this
       data type as it is the one used by SFML clock */

    /* save the last time the screen transition surface transparency animation
       has been updated */
    sf::Int32 lastScreenTransitionTime;

    /* the current step of the screen switch animation from 0 to 5; this value
       is incremented or decremented every second quarter during the animation
       to detect when the animation is finished; used for both opening and
       closing */
    sf::Uint8 transitionTime;

    /* the color of the background for the screen
       transition animation; declared here because
       this color is animated and continually updated */
    sf::Color transitionSurfaceColor;

    /* the screen transition surface is a black rectangle covering the whole
       window; the transparency (alpha) value of this color is updated during
       the animation to create a smooth opening/closing effect */
    sf::RectangleShape transitionSurface;
};
}
}

#endif
