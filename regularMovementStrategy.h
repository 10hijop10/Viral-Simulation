#pragma once

#include "movementStrategy.h"
namespace corsim
{

class regularMovementStrategy: public movementStrategy
{
  public:
    double subjectMovementSpeed() override;
};

}