#pragma once
#include <cstdint>
#include <iostream>
#include <cstring>
#include <unordered_map>
#include "TritValue.h"

#define UINT_TRIT (sizeof(unsigned int) * 8 / 2)

using namespace std;

class TritsetProxy;

    class Tritset {
        friend class TritsetProxy;
    private:
        unsigned int set_size;
        unsigned int* set;
        unsigned int set_b;
    public:
        Tritset();
        explicit Tritset(unsigned int capasity);
        Tritset(const Tritset& tritset);
        ~Tritset();

        unsigned int get_set_size() const;
        unsigned int get_size_b() const;

        Tritset& operator&=(Tritset& t);
        Tritset& operator|=(Tritset& t);


        Tritset operator|(const Tritset& t) const;
        Tritset operator&(const Tritset& t) const;

        bool operator==(const Tritset& trit) const;
        bool operator!=(const Tritset& trit) const;

        Tritset& operator!();

        TritsetProxy operator[](size_t i);

        Tritset& operator=(const Tritset& trit);
        Tritset& operator=(Tritset&& tritset) noexcept;

        TritValue get(unsigned int pos) const;
        void setValue(unsigned int index, TritValue value);

        size_t capacity() const;
        size_t length() const;
        size_t cardinality(TritValue value) const;

        Tritset(Tritset&& tritset) noexcept;

        void shrink();
        void trim(size_t last_index);

        struct TritHash {
            std::size_t operator()(TritValue t) const;
        };
        std::unordered_map<TritValue, size_t, Tritset::TritHash> cardinality() const;

    };

    class TritsetProxy
    {
        friend class Tritset;
    private:
        Tritset& tritset_;
        unsigned int index;

    public:
        explicit TritsetProxy(Tritset& t, unsigned int trit_index)
            : tritset_(t)
            , index(trit_index)
        {
        } 

        TritsetProxy(const TritsetProxy& trit) = default;
        TritsetProxy(TritsetProxy&& trit) = default;

        TritsetProxy& operator=(TritValue t);
        TritsetProxy& operator=(TritsetProxy &&trit) = default;

        bool operator==(const TritValue& t) const;
        bool operator!=(TritValue value);
    };

