#pragma once

#include "l4/ICache.h"

namespace l4
{
template <typename Key, typename Value>
class NoOpCache : public ICache<Key, Value>
{
public:
  void Resize(std::size_t capacity) override {}
  [[nodiscard]] std::size_t GetCapacity() const override
  {
    return std::numeric_limits<std::size_t>().max();
  }
  [[nodiscard]] std::size_t GetSize() const override { return 0; }
  void Set(const Key &key, const Value &value) override {}

  [[nodiscard]] bool TryGet(const Key &key, Value &value) const override
  {
    return false;
  }

  [[nodiscard]] Value Get(const Key &key) const override
  {
    throw std::runtime_error("Key not found");
  }
  [[nodiscard]] bool IsCached(const Key &key) const override { return false; }
  void Clear() override {}
  bool Delete(const Key &key) override { return false; }
};
} // namespace l4
