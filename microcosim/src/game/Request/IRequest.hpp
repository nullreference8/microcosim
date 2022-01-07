#ifndef GAME_IREQUEST_HPP
#define GAME_IREQUEST_HPP

namespace game {
  class IRequest {
  public:
    virtual void QueueJob() = 0;
  };
}
#endif