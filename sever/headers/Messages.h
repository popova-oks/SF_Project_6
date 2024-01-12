#pragma once
#include <map>
#include "ISubject.h"
#include "jsonHandler.h"

template <typename T> class Messages {
  public:
    Messages() {}
    ~Messages(){};    
    void get_messages(ISubject* chat);  
};