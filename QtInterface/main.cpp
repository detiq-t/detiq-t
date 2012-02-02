#include "Log.h"

int main ()
{
  Log::configure (true, false, 0);
  Log::critical ("ceci est un test");
  Log::info ("ceci est un test");
  Log::warning ("ma foi");
  Log::verbose ("huhu");

  return 0;
}
