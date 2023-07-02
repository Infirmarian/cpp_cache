#include "l4/LRUCache.h"

#include <catch2/catch_test_macros.hpp>

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

TEST_CASE("LRUCache.Clear")
{
  l4::LRUCache<std::string, int> cache{2};
  cache.Set("A", 1);
  cache.Set("B", 2);
  REQUIRE(cache.IsCached("A") == true);
  REQUIRE(cache.IsCached("B") == true);
  cache.Clear();
  REQUIRE(cache.IsCached("A") == false);
  REQUIRE(cache.IsCached("B") == false);
}

TEST_CASE("LRUCache.Capacity3Push5")
{
  l4::LRUCache<std::string, int> cache{3};
  cache.Set("A", 1);
  cache.Set("B", 2);
  cache.Set("C", 3);
  cache.Set("D", 4);
  cache.Set("E", 5);
  REQUIRE(cache.IsCached("A") == false);
  REQUIRE(cache.IsCached("B") == false);
  REQUIRE(cache.IsCached("C") == true);
  REQUIRE(cache.IsCached("D") == true);
  REQUIRE(cache.IsCached("E") == true);
}

TEST_CASE("LRUCache.IntKeyTest")
{
  l4::LRUCache<int, int> cache{3};
  cache.Set(1, 1);
  cache.Set(2, 2);
  cache.Set(3, 3);
  REQUIRE(cache.IsCached(1) == true);
  REQUIRE(cache.IsCached(2) == true);
  REQUIRE(cache.IsCached(3) == true);
}

TEST_CASE("LRUCache.LastAccessedIsRecentlyUsed")
{
  l4::LRUCache<std::string, int> cache{3};
  cache.Set("A", 1);
  cache.Set("B", 2);
  cache.Set("C", 3);
  REQUIRE_NOTHROW(cache.Get("A"));
  cache.Set("D", 4);
  REQUIRE(cache.IsCached("A") == true);
  REQUIRE(cache.IsCached("B") == false);
  REQUIRE(cache.IsCached("C") == true);
  REQUIRE(cache.IsCached("D") == true);
}

// Additional, more complex tests
TEST_CASE("LRUCache.ResizeUp")
{
  l4::LRUCache<std::string, int> cache{1};
  cache.Set("A", 1);
  REQUIRE(cache.IsCached("A") == true);
  cache.Resize(2);
  REQUIRE(cache.GetCapacity() == 2);
  REQUIRE(cache.IsCached("A") == true);
  cache.Set("B", 2);
  REQUIRE(cache.IsCached("A") == true);
  REQUIRE(cache.IsCached("B") == true);
}
