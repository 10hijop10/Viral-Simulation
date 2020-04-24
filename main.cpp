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

#include "simulation.h"
#include <iostream>
#include <random>
#include <math.h>
#include "html_canvas.h"
#include "ChartJS_handler.h"
#include "movementstrategy.h"
#include "lockdownMovementStrategy.h"
#include "regularMovementStrategy.h"
#include <emscripten.h>
#include <emscripten/bind.h>

//Constants to control the simulation
const int SUBJECT_COUNT = 200;
const int SIM_WIDTH = 800;
const int SIM_HEIGHT = 500;
const int SUBJECT_RADIUS = 2;

static corsim::Simulation s(SIM_WIDTH,SIM_HEIGHT,std::make_unique<corsim::HTMLCanvas>(30,150,SIM_WIDTH,SIM_HEIGHT),
        std::make_unique<corsim::ChartJSHandler>());

int main() {
    //Code to randomly generate certain numbers, which is done by using certain distributions
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist_w(1.0, SIM_WIDTH);
    std::uniform_real_distribution<double> dist_h(1.0, SIM_HEIGHT);
    std::uniform_real_distribution<double> dist_dx(-1.0, 1.0);
    std::uniform_real_distribution<double> dist_dy(-1.0, 1.0);

    for (int i = 0; i<SUBJECT_COUNT; ++i)
    {
        double x = dist_w(mt); //Randomly generate x position
        double y = dist_h(mt); //Randomly generate y position
        
        corsim::Subject su(x,y,SUBJECT_RADIUS,false);

        su.set_dx(dist_dx(mt));
        su.set_dy(dist_dy(mt));
        su.set_strategy(new corsim::regularMovementStrategy); 

        if(i == SUBJECT_COUNT-1)
        {
            su.infect();
        }

        s.add_subject(std::move(su));
    }  

    s.run();
}

void regularMovement()
{
    std::vector<corsim::Subject>& subjects = s.getSubjects();
    for (corsim::Subject& subject : subjects)
    {
        subject.set_strategy(new corsim::regularMovementStrategy);   
    }
}

void lockDownMovement()
{
    std::vector<corsim::Subject>& subjects = s.getSubjects();
    double size = subjects.size() * 0.75;
    for (int i = 0; i < size; i++)
    {
        subjects.at(i).set_strategy(new corsim::lockdownMovementStrategy);   
    }
}

EMSCRIPTEN_BINDINGS(my_module) 
{      
    emscripten::function("regularMovement", &regularMovement);
    emscripten::function("lockDownMovement", &lockDownMovement);
}