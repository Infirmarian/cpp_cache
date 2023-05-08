#include "Version.h"
#include <cache/SimpleInfiniteCache.h>
#include <iostream>

int main()
{
  l4::SimpleInfiniteCache<std::string, double> cache{};
  cache.Set("Hello", 1);
  assert(cache.GetSize() == 1);
  assert(cache.IsCached("Hello"));
  assert(cache.Get("Hello") == 1);
  cache.Clear();
  assert(cache.GetSize() == 0);
  std::cout << "Capacity: " << cache.GetCapacity() << std::endl;
  std::cout << "All tests passed" << std::endl;
}