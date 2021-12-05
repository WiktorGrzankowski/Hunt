#ifndef _MEMBER_H
#define _MEMBER_H

#include <cstddef>
#include <type_traits>

template<typename ValueType>
concept TreasureType = requires(ValueType type) {
    { Treasure{type}} -> std::same_as<ValueType>;
};

template<typename ValueType, bool IsArmed> requires
TreasureType<SafeTreasure<ValueType>>
class Adventurer {
public:
    using strength_t = unsigned int;
    constexpr static bool isArmed = IsArmed;

    constexpr Adventurer() requires (!IsArmed) = default;

    constexpr explicit Adventurer(strength_t str) requires(IsArmed){
        strength = str;
    }

    constexpr strength_t getStrength() const requires(IsArmed){
        return strength;
    }

    constexpr ValueType pay() {
        ValueType temp = treasureGathered;
        treasureGathered = 0;
        return temp;
    }

    template<bool isTrapped>
    constexpr void loot(Treasure<ValueType, isTrapped> &&treasure) {
        if ((isTrapped && strength > 0) || !isTrapped) {
            treasureGathered += treasure.getLoot();
            if (isTrapped)
                strength /= 2;
        }
    }

private:
    ValueType treasureGathered = 0;
    strength_t strength = 0;
};

template<typename ValueType>
using Explorer = Adventurer<ValueType, false>;
using strength_t = unsigned int;

constexpr strength_t fib(size_t n) {
    strength_t f[25] = {0, 1, 1, 2, 3, 5, 8, 13, 21,
                        34, 55, 89, 144, 233, 377, 610,
                        987, 1597, 2584, 4181, 6765, 10946,
                        17711, 28657, 46368};

    return f[n];
}

using strength_t = unsigned int;

template<typename ValueType, size_t CompletedExpeditions> requires
TreasureType<SafeTreasure<ValueType>> && (CompletedExpeditions < 25)
class Veteran {
public:
    using strength_t = unsigned int;

    constexpr Veteran() = default;

    static const bool isArmed = true;

    template<bool isTrapped>
    constexpr void loot(Treasure<ValueType, isTrapped> &&treasure) {
        treasureGathered += treasure.getLoot();
    }

    constexpr ValueType pay() {
        ValueType temp = treasureGathered;
        treasureGathered = 0;
        return temp;
    }

    constexpr strength_t getStrength() const {
        return strength;
    }

private:
    ValueType treasureGathered = 0;
    size_t completedExpeditions = CompletedExpeditions;
    strength_t strength = fib(completedExpeditions);
};

#endif //_MEMBER_H
