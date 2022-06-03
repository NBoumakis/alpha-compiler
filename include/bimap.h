#ifndef __BIMAP_H
#define __BIMAP_H

#include <map>

template <typename V>
class bimap {
private:
    std::map<unsigned long, V> straight;
    std::map<V, unsigned long> reverse;
    unsigned long max_key = 0;

public:
    // Default constructor
    bimap() = default;

    // Copy constructor
    bimap(const bimap &) = default;

    /// Move constructor.
    bimap(bimap &&) = default;

    // Copy assignment operator.
    bimap &operator=(const bimap &) = default;

    // Move assignment operator.
    bimap &operator=(bimap &&) = default;

    bool empty() const noexcept {
        assert(straight.size() == reverse.size());
        return straight.empty();
    }

    ///  Returns the size of the %map.
    auto size() const noexcept { return straight.size(); }

    ///  Returns the maximum size of the %map.
    auto max_size() const noexcept {
        return std::min(straight.max_size(), -1UL);
    }

    unsigned long insert(V value) {
        auto inserted = reverse.find(value);

        if (inserted != reverse.end()) {
            return inserted->second;
        } else {
            if (max_key + 1 == 0)
                throw(max_key);

            straight.insert({max_key, value});
            reverse.insert({value, max_key});

            return max_key++;
        }
    }

    const V find(unsigned long key) const {
        return straight.at(key);
    }

    unsigned long find_reverse(V value) const {
        return reverse.at(value);
    }

    auto get_straight() {
        return this->straight;
    }

    auto get_reverse() {
        return this->reverse;
    }
};

#endif /* __BIMAP_H */