#pragma once

#include <l4/ICache.h>

#include <mutex>
#include <stdexcept>
#include <unordered_map>

namespace l4
{
template <typename Key, typename Value>
class LRUCache : public ICache<Key, Value>
{
public:
  LRUCache(std::size_t capacity) : _capacity(capacity) {}
  [[nodiscard]] std::size_t GetCapacity() const override { return _capacity; }
  void Resize(std::size_t capacity) override
  {
    if (capacity < _capacity)
    {
      // todo: shrink to fit
    }
    _capacity = capacity;
  }
  [[nodiscard]] std::size_t GetSize() const override { return _cache.size(); }

  void Set(const Key &key, const Value &value) override
  {
    // todo: implement
  }
  [[nodiscared]] bool TryGet(const Key &key, Value &value) const override
  {
    // todo: implement
    return false;
  }
  [[nodiscard]] Value Get(const Key &key) const override
  {
    // todo: implement
    throw std::runtime_error("Not implemented");
  }
  [[nodiscard]] bool IsCached(const Key &key) const override
  {
    // todo: implement
    return false;
  }
  void Clear() override
  {
    // todo: implement
  }
  bool Delete(const Key &key) override
  {
    // todo: implement
    return false;
  }

private:
  std::unordered_map<Key, Value> _cache;
  mutable std::mutex _mtx;
  std::size_t _capacity;
};
} // namespace l4
