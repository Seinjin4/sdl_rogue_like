#pragma once

#include <ctime>

class time_manager
{
private:
  static clock_t time;
  static double delta_time;

  time_manager() = delete;
  ~time_manager() = delete;

public:
  static void count_delta_time();
  static double get_delta_time();

};
