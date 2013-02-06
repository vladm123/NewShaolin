/*
    Copyright 2009, 2010 Sebastian Codrin Ditu, Vlad Manea

        This file is part of newshaolin.

        newshaolin is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation, either version 3 of the License, or
        (at your option) any later version.

        newshaolin is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with newshaolin.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "intermain.h"

// functia care creeaza aplicatia
int main(int argc, char *argv[])
{
    // pornesc aplicatia qt
    myapp = new QApplication(argc, argv);

    // setez stilul
    InterMain::instance()->setstyle("background-color:#fff; background-image:url(images/shaolin.jpg); background-repeat:no-repeat;", 0);

    // pune pe ecran interfata
    InterMain::instance()->show();

    // predau controlul aplicatiei qt create
    return myapp->exec();
}
