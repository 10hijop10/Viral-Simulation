#pragma once

#include "movementstrategy.h"
#include <iostream>
namespace corsim
{

class regularMovementStrategy: public movementStrategy
{
  public:
    double subjectMovementSpeed() override;
};

}