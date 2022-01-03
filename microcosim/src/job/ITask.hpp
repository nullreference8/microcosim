#ifndef JOB_ITASK_HPP
#define JOB_ITASK_HPP
namespace job {
  class ITask {
  public:
    virtual void Action() = 0;
    virtual bool CheckComplete() = 0;
    virtual bool CheckRunning() = 0;
  };
}
#endif
