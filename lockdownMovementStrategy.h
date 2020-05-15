#pragma once
#include "movementStrategy.h"

namespace corsim 
{

class lockdownMovementStrategy: public movementStrategy 
{

public:
    double subjectMovementSpeed() override;
};
}