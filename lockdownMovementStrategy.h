#pragma once
#include "movementstrategy.h"
namespace corsim 
{

class lockdownMovementStrategy: public movementStrategy 
{

public:
    double subjectMovementSpeed() override;
};
}