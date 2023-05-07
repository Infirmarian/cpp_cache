#pragma once
namespace l4
{
    template <typename Key, typename Value>
    class ICache
    {
    public:
        virtual ~ICache() = default;

        [[nodiscard]] virtual std::size_t GetCapacity() const = 0;
        virtual void Resize(std::size_t capacity) = 0;
        [[nodiscard]] virtual std::size_t GetSize() const = 0;

        virtual void Set(const Key &key, const Value &value) = 0;
        [[nodiscared]] virtual bool TryGet(const Key& key, Value& value) const = 0;
        [[nodiscard]] virtual Value Get(const Key &key) const = 0;
        [[nodiscard]] virtual bool IsCached(const Key &key) const = 0;
        virtual void Clear() = 0;
        virtual bool Delete(const Key &key) = 0;
    };
} // namespace l4
