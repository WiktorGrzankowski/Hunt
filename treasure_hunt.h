#ifndef _TREASURE_HUNT_H
#define _TREASURE_HUNT_H

#include "treasure.h"
#include "member.h"
#include <concepts>
#include <utility>

template<typename T>
concept MemberType = requires(T member) {
    typename T::strength_t;

    { []() constexpr { return T::isArmed; }() } -> std::convertible_to<bool>;

    { member.pay() } -> std::integral;

    member.loot(std::declval<Treasure<decltype(member.pay()), true>>());
    member.loot(std::declval<Treasure<decltype(member.pay()), false>>());
};

template<typename T>
concept EncounterSide = TreasureType<T> || MemberType<T>;

template<EncounterSide sideA, EncounterSide sideB>
using Encounter = std::pair<sideA &, sideB &>;

// Treasure vs member.
template<TreasureType A, MemberType B>
constexpr void run(Encounter<A, B> encounter) {
    (encounter.second).loot(std::move((encounter.first)));
}

// Member vs treasure.
template<MemberType A, TreasureType B>
constexpr void run(Encounter<A, B> encounter) {
    (encounter.first).loot(std::move((encounter).second));
}

// Armed member vs armed member.
template<MemberType A, MemberType B>
requires A::isArmed && B::isArmed
constexpr void run(Encounter<A, B> encounter) {
    auto[sideA, sideB] = encounter;

    if (sideA.getStrength() > sideB.getStrength())
        sideA.loot(SafeTreasure<decltype(sideB.pay())>(sideB.pay()));
    else if (sideA.getStrength() < sideB.getStrength())
        sideB.loot(SafeTreasure<decltype(sideA.pay())>(sideA.pay()));
}

// Armed member vs unarmed member.
template<MemberType A, MemberType B>
requires A::isArmed && (!B::isArmed)
constexpr void run(Encounter<A, B> encounter) {
    auto[sideA, sideB] = encounter;
    sideA.loot(SafeTreasure<decltype(sideB.pay())>(sideB.pay()));
}

// Unarmed member vs armed member.
template<MemberType A, MemberType B>
requires (!A::isArmed) && B::isArmed
constexpr void run(Encounter<A, B> encounter) {
    auto[sideA, sideB] = encounter;
    sideB.loot(SafeTreasure<decltype(sideA.pay())>(sideA.pay()));
}

// Unarmed member vs unarmed member.
template<MemberType A, MemberType B>
requires (!A::isArmed) && (!B::isArmed)
constexpr void run(Encounter<A, B>) {}


constexpr void expedition() {}

template<typename Encounter, typename ... Encounters>
constexpr void expedition(Encounter enc, Encounters... encs) {
    run(enc);
    expedition(encs...);
}


#endif //_TREASURE_HUNT_H
