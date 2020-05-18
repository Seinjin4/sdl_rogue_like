#include "time_manager.h"
#include <ctime>

clock_t time_manager::time = clock();

double time_manager::delta_time = 0;

void time_manager::count_delta_time()
{
  delta_time = (double)(clock() - time) / CLOCKS_PER_SEC;
  time = clock();
}

double time_manager::get_delta_time()
{
  return delta_time;
}
