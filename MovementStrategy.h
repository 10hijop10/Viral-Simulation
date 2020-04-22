#pragma once

namespace corsim
{

class movementStrategy
{
  public:
	  virtual ~movementStrategy() = default;
	  movementStrategy() = default;
    virtual double subjectMovementSpeed() = 0; //pure virtual
};
}