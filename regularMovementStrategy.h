#pragma once
#include "movementstrategy.h"
namespace corsim
{

class regularMovementStrategy: public movementStrategy
{
  public:
    double subjectMovementSpeed() override;
};

}