#pragma once
#include <map>
#include <string>

class IObserver {
  public:
    virtual ~IObserver(){};
    virtual bool update(const int event) = 0;
};