#include <catch2/catch_test_macros.hpp>
#include <l4/LRUCache.h>

TEST_CASE("LRUCache.InitialCapacity")
{
  l4::LRUCache<std::string, std::string> cache{1};
  REQUIRE(cache.GetCapacity() == 1);
}

TEST_CASE("LRUCache.BasicTest")
{
  l4::LRUCache<std::string, int> cache{1};
  cache.Set("A", 1);
  REQUIRE(cache.IsCached("A"));
  REQUIRE(cache.TryGet("A").has_value());
  REQUIRE(cache.Get("A") == 1);
  REQUIRE(cache.Delete("A"));
  REQUIRE(cache.IsCached("A") == false);
  REQUIRE_THROWS(cache.Get("A"));
}

TEST_CASE("LRUCache.Evict")
{
  l4::LRUCache<std::string, int> cache{1};
  cache.Set("A", 1);
  REQUIRE(cache.IsCached("A") == true);
  cache.Set("B", 2);
  REQUIRE(cache.IsCached("A") == false);
  REQUIRE(cache.IsCached("B") == true);
}

TEST_CASE("LRUCache.ResizeDown")
{
  l4::LRUCache<std::string, int> cache{2};
  cache.Set("A", 1);
  cache.Set("B", 2);
  REQUIRE(cache.IsCached("A") == true);
  REQUIRE(cache.IsCached("B") == true);
  cache.Resize(1);
  REQUIRE(cache.GetCapacity() == 1);
  REQUIRE(cache.IsCached("A") == false);
  REQUIRE(cache.IsCached("B") == true);
}
