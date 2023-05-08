#include <cache/SimpleInfiniteCache.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("SimpleCache.Set")
{
  l4::SimpleInfiniteCache<std::string, std::string> cache;
  cache.Set("Hello", "World");
  REQUIRE(cache.IsCached("Hello"));
  REQUIRE(cache.GetSize() == 1);
  REQUIRE(cache.Get("Hello") == "World");
}

TEST_CASE("SimpleCache.Resize")
{
  l4::SimpleInfiniteCache<int, int> cache;
  auto capacity = cache.GetCapacity();
  cache.Resize(1);
  REQUIRE(cache.GetCapacity() == capacity);
}