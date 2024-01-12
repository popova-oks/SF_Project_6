#pragma once
#include "IObserver.h"
#include "nlohmann/json.hpp"
#include <map>


template <typename T> class Messages {
  public:
    Messages() {};
    ~Messages();    
    nlohmann::json send_message(const nlohmann::json &json);
};