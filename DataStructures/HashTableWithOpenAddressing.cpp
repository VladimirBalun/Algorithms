#include <vector>
#include <iostream>

namespace details {

    struct Probing
    {
        explicit Probing(size_t index) noexcept:
            m_index(index) {}

    protected:
        size_t m_index;
    };

    struct LinearProbing : Probing
    {
        using Probing::Probing;
        size_t operator ()() noexcept
        {
            return ++m_index;
        }
    };

    struct QuadraticProbing : Probing
    {
        using Probing::Probing;
        size_t operator ()() noexcept
        {
            const size_t index = m_index + (m_multiplier * m_multiplier);
            ++m_multiplier;
            return index;
        }

    private:
        size_t m_multiplier = 1;
    };

    template<size_t PRIME = 7>
    struct DoubleHashingProbing : Probing
    {
        explicit DoubleHashingProbing(size_t index) noexcept:
            Probing(index), m_double_index(PRIME - (index % PRIME)) {}

        size_t operator ()() noexcept
        {
            ++m_offset;
            const size_t index = m_index + m_offset * m_double_index;
            return index;
        }

    private:
        size_t m_offset = 0;
        size_t m_double_index = 0;
    };
}

template<
    typename K,
    typename V,
    typename Hash = std::hash<K>,
    typename KeyEqual = std::equal_to<K>,
    typename Probing = details::DoubleHashingProbing<7>
>
class HashTableWithOpenAddressing {
public:
    struct bucket {
        static constexpr std::uint8_t ABSENT = 0u;
        static constexpr std::uint8_t PRESENT = 1u;
        static constexpr std::uint8_t REMOVED = 2u;

        std::pair<K, V> element;
        std::uint8_t status = ABSENT;
    };

    using buckets_t = std::vector<bucket>;

public:
    void insert(std::pair<K, V> element)
    {
        if (load_factor() > 0.7f)
            rehash();

        size_t index = 0;
        std::uint8_t status = bucket::PRESENT;
        while (status == bucket::PRESENT) {
            index = find_empty_element_index(element.first, m_buckets);
            status = m_buckets[index].status;
            if (status == bucket::PRESENT)
                rehash();
        }

        m_buckets[index].element = std::move(element);
        m_buckets[index].status = bucket::PRESENT;
        ++m_size;
    }

    void erase(const K& key)
    {
        const size_t index = find_element_index(key);
        if (m_buckets[index].status == bucket::PRESENT && KeyEqual()(key, m_buckets[index].element.first)) {
            m_buckets[index].element.first.~K();
            m_buckets[index].element.second.~V();
            m_buckets[index].status = bucket::REMOVED;
            --m_size;
        }
    }

    [[nodiscard]] bool find(const K& key) const
    {
        const size_t index = find_element_index(key);
        return KeyEqual()(key, m_buckets[index].element.first);
    }

    [[nodiscard]] float load_factor() const
    {
        if (m_buckets.empty())
            return 1.0f;

        return m_size / static_cast<float>(m_buckets.size());
    }

private:
    [[nodiscard]] size_t bucket_index(const K& key) const
    {
        return Hash()(key) % m_buckets.size();
    }

    [[nodiscard]] size_t find_element_index(const K& key) const
    {
        size_t index = bucket_index(key);
        size_t initiated_index = index;
        Probing probing(initiated_index);
        while (m_buckets[index].status != bucket::ABSENT) {
            if (m_buckets[index].status == bucket::PRESENT == KeyEqual()(key, m_buckets[index].element.first))
                break;

            index = probing() % m_buckets.size();
            if (index == initiated_index)
                break;
        }

        return index;
    }

    [[nodiscard]] size_t find_empty_element_index(const K& key, const buckets_t& buckets) const
    {
        size_t index = bucket_index(key);
        size_t initiated_index = index;
        Probing probing(key);
        while (buckets[index].status == bucket::PRESENT) {
            index = probing() % buckets.size();
            if (index == initiated_index)
                break;
        }

        return index;
    }

    void rehash()
    {
        buckets_t new_buckets(m_buckets.size() * 2 + 1);
        for (auto& bucket: m_buckets) {
            if (bucket.status == bucket::PRESENT) {
                const auto& key = bucket.element.first;
                const size_t index = find_empty_element_index(key, new_buckets);
                assert(new_buckets[index].status != bucket::PRESENT);
                new_buckets[index].element = std::move(bucket.element);
                new_buckets[index].status = bucket::PRESENT;
            }
        }

        m_buckets.swap(new_buckets);
    }

private:
    buckets_t m_buckets;
    size_t m_size = 0;
};

int main()
{
    HashTableWithOpenAddressing<int, std::string> hash_table;
    return EXIT_SUCCESS;
}
