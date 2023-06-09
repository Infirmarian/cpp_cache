#pragma once

#include "l4/ICache.h"

#include <mutex>
#include <stdexcept>
#include <unordered_map>

namespace l4
{
template <typename Key, typename Value>
class SimpleInfiniteCache : public ICache<Key, Value>
{
public:
  ~SimpleInfiniteCache() = default;
  void Resize(std::size_t capacity) override
  {
    // no-op
  }
  [[nodiscard]] std::size_t GetCapacity() const override
  {
    return std::numeric_limits<std::size_t>().max();
  }
  [[nodiscard]] std::size_t GetSize() const override
  {
    std::scoped_lock l{_mtx};
    return _cache.size();
  }
  void Set(const Key &key, const Value &value) override
  {
    std::scoped_lock l{_mtx};
    _cache.emplace(key, value);
  }

  [[nodiscard]] std::optional<Value> TryGet(const Key &key) const override
  {
    std::scoped_lock l{_mtx};
    auto it = _cache.find(key);
    if (it == _cache.end())
    {
      return std::nullopt;
    }
    return it->second;
  }

  [[nodiscard]] Value Get(const Key &key) const override
  {
    std::scoped_lock l{_mtx};
    auto it = _cache.find(key);
    if (it == _cache.end())
    {
      throw std::runtime_error("Key not found");
    }
    return it->second;
  }
  [[nodiscard]] bool IsCached(const Key &key) const override
  {
    std::scoped_lock l{_mtx};
    return _cache.find(key) != _cache.end();
  }
  void Clear() override
  {
    std::scoped_lock l{_mtx};
    _cache.clear();
  }
  bool Delete(const Key &key) override
  {
    std::scoped_lock l{_mtx};
    return _cache.erase(key);
  }

private:
  mutable std::mutex _mtx;
  std::unordered_map<Key, Value> _cache;
};
} // namespace l4
