#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP
//The Game Manager will sift through designated work, stockpiles to move, and all other actions that govern units
#include <memory>
#include <list>
#include <string>
namespace game { 
  class IRequest;
  class Manager { 
  public:
    std::list<game::IRequest> Requests;
    void PrepareRequests();
  };
}
#endif