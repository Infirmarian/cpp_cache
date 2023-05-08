#include <catch2/catch_test_macros.hpp>
#include <l4/LRUCache.h>

TEST_CASE("LRUCache.InitialCapacity")
{
  l4::LRUCache<std::string, std::string> cache{1};
  REQUIRE(cache.GetCapacity() == 1);
}
