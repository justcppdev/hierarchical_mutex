#include <mutex>
#include <stdexcept>
#include <limits>

#include "hierarchical_mutex.hpp"

void hierarchical_mutex::check_for_hieararchy_violation() 
{
  if(this_thread_hierarchy_value_ <= hierarchy_value_) {
    throw std::logic_error("mutex hierarchy violated");
  }
}

void hierarchical_mutex::update_hierarchy_value()
{
  previous_hierarchy_value_ = this_thread_hierarchy_value_;
  this_thread_hierarchy_value_ = hierarchy_value_;
}
hierarchical_mutex::hierarchical_mutex(unsigned long value) :
  hierarchy_value_(value), previous_hierarchy_value_(0) 
{
}


void hierarchical_mutex::lock()
{
  check_for_hieararchy_violation();
  mutex_.lock();
  update_hierarchy_value();
}

void hierarchical_mutex::unlock()
{
  this_thread_hierarchy_value_ = previous_hierarchy_value_;
  mutex_.unlock();
}

bool hierarchical_mutex::try_lock()
{
  check_for_hieararchy_violation();
  if(!mutex_.try_lock()) {
    return false;
  }
  update_hierarchy_value();
  return true;
}

thread_local unsigned long hierarchical_mutex::this_thread_hierarchy_value_ = std::numeric_limits<unsigned long>::max();
