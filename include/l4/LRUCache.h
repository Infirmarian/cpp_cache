#pragma once

#include "l4/ICache.h"

#include <list>
#include <mutex>
#include <optional>
#include <stdexcept>
#include <unordered_map>

namespace l4
{
template <typename Key, typename Value>
class LRUCache : public ICache<Key, Value>
{
private:
  std::optional<Value> _TryGet(const Key &key) const
  {
    auto it = _cache.find(key);
    if (it == _cache.end())
    {
      return std::nullopt;
    }
    _UseKey(it->second.first);
    return it->second.second;
  }
  void _UseKey(const typename std::list<Key>::iterator &iterator) const
  {
    _useHistory.splice(_useHistory.end(), _useHistory, iterator);
  }
  void _Evict()
  {
    _cache.erase(_useHistory.front());
    _useHistory.pop_front();
  }
  static std::size_t _validateCapacity(std::size_t capacity)
  {
    if (capacity == 0)
    {
      throw std::invalid_argument("Capacity must be at least 1");
    }
    return capacity;
  }

public:
  LRUCache(std::size_t capacity) : _capacity{_validateCapacity(capacity)} {}
  [[nodiscard]] std::size_t GetCapacity() const override { return _capacity; }
  void Resize(std::size_t capacity) override
  {
    _validateCapacity(capacity);
    std::scoped_lock lock{_mtx};
    if (capacity < _capacity)
    {
      while (_cache.size() > capacity)
      {
        _Evict();
      }
    }
    _capacity = capacity;
  }

  [[nodiscard]] std::size_t GetSize() const override { return _cache.size(); }

  void Set(const Key &key, const Value &value) override
  {
    std::scoped_lock lock{_mtx};
    auto it = _cache.find(key);
    if (it != _cache.end())
    {
      _UseKey(it->second.first);
      return;
    }
    if (_capacity == _cache.size())
    {
      _Evict();
    }
    _useHistory.emplace_back(key);
    _cache.emplace(key, std::make_tuple(std::prev(_useHistory.end()), value));
  }

  [[nodiscard]] std::optional<Value> TryGet(const Key &key) const override
  {
    std::scoped_lock lock{_mtx};
    return _TryGet(key);
  }

  [[nodiscard]] Value Get(const Key &key) const override
  {
    std::scoped_lock lock{_mtx};
    auto value = _TryGet(key);
    if (!value)
    {
      throw std::runtime_error("Key not found");
    }
    return *value;
  }

  [[nodiscard]] bool IsCached(const Key &key) const override
  {
    std::scoped_lock lock{_mtx};
    return _cache.find(key) != _cache.end();
  }

  void Clear() override
  {
    std::scoped_lock lock{_mtx};
    _cache.clear();
    _useHistory.clear();
  }

  bool Delete(const Key &key) override
  {
    std::scoped_lock lock{_mtx};
    auto it = _cache.find(key);
    if (it == _cache.end())
    {
      return false;
    }
    _useHistory.erase(it->second.first);
    _cache.erase(it);
    return true;
  }

private:
  std::unordered_map<Key, std::pair<typename std::list<Key>::iterator, Value>>
      _cache;
  mutable std::list<Key> _useHistory;
  mutable std::mutex _mtx;
  std::size_t _capacity;
};
} // namespace l4
