#include <vector>
#include <iostream>
#include <forward_list>

template<
        typename K,
        typename V,
        typename Hash = std::hash<K>,
        typename KeyEqual = std::equal_to<K>
>
class HashTableWithSeparateChaining {
    using element_t = std::pair<K, V>;
    using bucket_t = std::forward_list<element_t>;
    using buckets_t = std::vector<bucket_t>;

public:
    void insert(std::pair<K, V> element)
    {
        if (load_factor() > 0.7)
            rehash();

        auto& bucket = m_buckets[bucket_index(element.first)];
        bucket.push_front(std::move(element));
        ++m_size;
    }

    void erase(K key)
    {
        auto& bucket = m_buckets[bucket_index(key)];
        if (bucket.empty())
            return;

        auto current = bucket.begin();
        auto previous = bucket.before_begin();
        while (current != end(bucket)) {
            if (current->first == key) {
                bucket.erase_after(previous);
                --m_size;
                return;
            }

            ++previous;
            ++current;
        }
    }

    [[nodiscard]] bool find(K key) const
    {
        if (buckets_count() == 0u)
            return false;

        const size_t index = bucket_index(key);
        const auto& bucket = m_buckets[index];
        auto it = std::find_if(
                begin(bucket),
                end(bucket),
                [&key](const element_t& element)
                {
                    return KeyEqual()(key, element.first);
                }
        );

        return it != end(bucket);
    }

    [[nodiscard]] float load_factor() const
    {
        if (m_buckets.empty())
            return 1.0f;

        return m_size / static_cast<float>(m_buckets.size());
    }

private:
    [[nodiscard]] size_t buckets_count() const noexcept
    {
        return m_buckets.size();
    }

    [[nodiscard]] size_t bucket_index(const K& key) const
    {
        return Hash()(key) % buckets_count();
    }

    void rehash()
    {
        buckets_t new_buckets(buckets_count() * 2u + 1u);
        for (auto& bucket: m_buckets) {
            for (auto& element: bucket) {
                const size_t hash = Hash()(element.first);
                const size_t new_bucket_index = hash % new_buckets.size();
                new_buckets[new_bucket_index].push_front(std::move(element));
            }
        }

        m_buckets.swap(new_buckets);
    }

public:
    buckets_t m_buckets;
    size_t m_size = 0u;
};

int main()
{
    HashTableWithSeparateChaining<int, std::string> hash_table;
    hash_table.insert({1, "123"});
    hash_table.insert({2, "456"});
    hash_table.insert({3, "789"});
    hash_table.insert({4, "123"});
    hash_table.insert({4, "111"});

    const bool found = hash_table.find(4);
    hash_table.erase(4);

    return EXIT_SUCCESS;
}

