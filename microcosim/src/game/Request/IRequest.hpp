#ifndef GAME_IREQUEST_HPP
#define GAME_IREQUEST_HPP

namespace game {
  class IRequest {
  public:
    virtual void Execute() = 0;
    virtual bool CheckComplete() = 0;
    virtual bool CheckRunning() = 0;
  };
}
#endif