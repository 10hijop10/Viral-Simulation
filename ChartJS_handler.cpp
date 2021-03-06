// Corona Simulation - basic simulation of a human transmissable virus
// Copyright (C) 2020  wbrinksma

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "ChartJS_handler.h"
#include <emscripten.h>

namespace corsim
{

ChartJSHandler::~ChartJSHandler(){}

void ChartJSHandler::communicate_numbers(int time, int infected,int immune)
{
    EM_ASM({
            var config = window.myConfig;
            var myLine = window.myLine;
            if (config.data.datasets.length > 0) 
            {
                config.data.labels.push($0);

                config.data.datasets[0].data.push($1);
                config.data.datasets[1].data.push($2);

                window.myLine.update();
                }
            },time,infected,immune);
}

}
