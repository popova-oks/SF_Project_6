#pragma once
#include "jsonHandler.h"

class ISubject {
  public:
    virtual ~ISubject(){};
    virtual nlohmann::json update(nlohmann::json &json) = 0;
};
