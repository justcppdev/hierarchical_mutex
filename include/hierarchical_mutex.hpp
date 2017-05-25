#include <mutex>

class hierarchical_mutex
{
  std::mutex mutex_;
  unsigned long const hierarchy_value_;
  unsigned long previous_hierarchy_value_;
  static thread_local unsigned long this_thread_hierarchy_value_;

  void check_for_hieararchy_violation();
  void update_hierarchy_value();
public:
  explicit hierarchical_mutex(unsigned long value);
  void lock();
  void unlock();
  bool try_lock();
};
