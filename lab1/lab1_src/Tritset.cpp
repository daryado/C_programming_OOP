#include <iostream>
#include <cmath>
#include "Tritset.h"

Tritset::Tritset()
{
    set = nullptr;
    set_b = 0;
    set_size = 0;
}


unsigned int Tritset::get_set_size() const
{
   return set_size;
}

unsigned int Tritset::get_size_b() const
{
    return set_size;
}

Tritset::Tritset(unsigned int capasity)
{
    set_b = capasity + UINT_TRIT - (capasity % UINT_TRIT);
    set_size = capasity;

    if (set_b >= 0)
    {
        set = new unsigned int[set_b / UINT_TRIT];
    }
    else
    {
        set = nullptr;
    }

    for (unsigned int i = 0; i < set_b / UINT_TRIT; ++i)
    {
        set[i] = 0;
    }
}

Tritset::Tritset(const Tritset& tritset) {
    set_size = tritset.set_size;
    set = new uint32_t[set_size]();
    set_b = tritset.set_b;
    memcpy(set, tritset.set, sizeof(unsigned int) * set_size);
}

Tritset::~Tritset()
{
    if (set != nullptr)
    {
        delete[] set;
        set_size = 0;
        set_b = 0;
    }
}


TritValue Tritset::get(unsigned int pos) const
{
    if ((set == nullptr) || (set_b < pos))
    {
        return TritValue::UNKNOWN;
    }

    unsigned int sdvig = (pos % UINT_TRIT) * 2;
    unsigned int IntTrit = (set[pos / UINT_TRIT] >> sdvig) & 0x03;
    return Int_to_Trit(IntTrit);
}

void Tritset::setValue(unsigned int position, TritValue t)
{
    unsigned int intVal = Trit_to_Int(t);

    if(t == TritValue::TRUE || t == TritValue::FALSE)
    {
        if(set == nullptr)
        {
            set_b = position + UINT_TRIT - (position % UINT_TRIT);
            set = new unsigned int [set_b / UINT_TRIT];

            for(unsigned int i = 0; i < set_b / UINT_TRIT; ++i)
            {
                set[i] = 0;
            }
        }
        else if(position > set_b)
        {
            unsigned int new_size_b = position + UINT_TRIT - (position % UINT_TRIT);

            auto * new_set = new unsigned int [new_size_b / UINT_TRIT];

            for(unsigned int i = 0; i < new_size_b / UINT_TRIT; ++i)
            {
                new_set[i] = 0;
            }

            for(unsigned int i = 0; i < set_b / UINT_TRIT; ++i)
            {
                new_set[i] = set[i];
            }

            delete [] set;

            set = new_set;
            set_b = new_size_b;
        }
    }

    unsigned int sdvig = (position % UINT_TRIT)*2;
    unsigned int mask = intVal << sdvig;
    unsigned int res = set[position/UINT_TRIT];
    res &= ~(0x03 << sdvig);
    res |= mask;
    set[position/UINT_TRIT] = res;
}

size_t Tritset::capacity() const
{
    return set_size/UINT_TRIT;
}

size_t Tritset::length() const
{
    if (set_b != 0)
    {
        for (unsigned int i = set_size - 1; i != 0; i--)//set_size
        {
            if (get(i) != TritValue::UNKNOWN)
            {
                return i + 1;
            }
        }
        return 0;
    }
    return 0;
}

size_t Tritset::cardinality(TritValue value) const
{
    size_t count = 0;
    for (unsigned int i = 0; i < Tritset::set_size; i++)
    {
        if (get(i) == value)
        {
            count++;
        }
    }
    return count;
}

Tritset::Tritset(Tritset&& tritset) noexcept
{
        set = tritset.set;
        set_size = tritset.set_size;
        set_b = tritset.set_b;

        tritset.set_size = 0;
        tritset.set_b = 0;
        tritset.set = nullptr;
}

void Tritset::shrink()
{
    unsigned int a = set_size/UINT_TRIT;
    for(unsigned int i = a - 1;; --i)
    {
        if (set[i]) {
            this->set = (unsigned int *) realloc(this->set, (i + 1) * sizeof(unsigned int));
            set_size = (i + 1)*UINT_TRIT;
            set_b -= set_b % UINT_TRIT + 1;
            set_b -= (a - i - 2) * UINT_TRIT;
            break;
        }
        if (!i) {
            this->set = (unsigned int *)realloc(this->set, (0) * sizeof(unsigned int));
            set_b = 0;
            break;
        }
    }
}

void Tritset::trim(size_t lastIndex)
{
    if (set_b <= lastIndex)
    {
        return;
    }
    else
    {
        if (lastIndex % UINT_TRIT == 0)
        {
            for (unsigned int i = lastIndex / UINT_TRIT + 1; i < set_b / UINT_TRIT; i++)
            {
                set[i] = 0;
            }
        }
        else
        {
            for (unsigned int i = lastIndex / UINT_TRIT + 1; i < set_b / UINT_TRIT; i++)
            {
                set[i] = 0;
            }
            set[lastIndex / UINT_TRIT] = (set[lastIndex / UINT_TRIT] >> ((UINT_TRIT - lastIndex % UINT_TRIT - 1) * 2));
            set[lastIndex / UINT_TRIT] = set[lastIndex / UINT_TRIT] << ((UINT_TRIT - lastIndex % UINT_TRIT - 1) * 2);
        }
    }
}

TritsetProxy Tritset::operator[](size_t i)
{
    TritsetProxy T(*this, i);
    T = get(i);
    return T;
}

TritsetProxy& TritsetProxy::operator=(TritValue t)
{
      if (t != TritValue::UNKNOWN && index >= tritset_.set_size){
          tritset_.set = (unsigned int *)realloc(tritset_.set, ceil(2.0*(index + 1.0)/ 8.0 * sizeof(unsigned int)));
          tritset_.set_size = index + 1;
          tritset_.setValue(index, t);
      }else if (index < tritset_.set_size)
          tritset_.setValue(index, t);

    return *this;
}

bool TritsetProxy::operator==(const TritValue &t) const
{
    if(index >= tritset_.set_size)
        return TritValue::UNKNOWN == t;
    else
        return t == tritset_.get(index);
}

bool TritsetProxy::operator!=(TritValue value)
{
    return !(operator==(value));
}

Tritset& Tritset::operator=(const Tritset& trit)
{

    if (this != &trit) {
        set_b = trit.set_b;
        auto* new_set = new unsigned int[set_b / UINT_TRIT];
        memcpy(new_set, trit.set, (set_b / UINT_TRIT) * sizeof(unsigned int));

        set = new_set;
    }

    return *this;
}

Tritset& Tritset::operator=(Tritset&& tritset) noexcept {
    if (&tritset != this) {
        delete[] set;
        set = tritset.set;
        set_size = tritset.set_size;
        set_b = tritset.set_b;

        tritset.set_size = 0;
        tritset.set_b = 0;
        tritset.set = nullptr;
    }
    return *this;
}

Tritset& Tritset::operator&=(Tritset& t) {
    *this = *this & t;
    return *this;
}

Tritset& Tritset::operator|=(Tritset& t) {
    *this = *this | t;
    return *this;
}

Tritset& Tritset::operator!()
{
    for (unsigned int i = 0; i < set_b; i++)
    {
        if ((*this)[i] == TritValue::TRUE)
            (*this)[i] = TritValue::FALSE;
        else if ((*this)[i] == TritValue::FALSE)
            (*this)[i] = TritValue::TRUE;
    }
    return *this;
}

bool Tritset::operator==(const Tritset& trit) const
{
    if (this->length() != trit.length())
    {
        return false;
    }
    else
    {
        for (unsigned int i = 0; i < (this->set_b) / UINT_TRIT;i++)
        {
            if (this->set[i] != trit.set[i])
            {
                return false;
            }
        }
    }
    return true;
}

bool Tritset::operator!=(const Tritset& trit) const
{
    return false;
}

Tritset Tritset::operator|(const Tritset& t) const {

    unsigned int size = t.get_set_size() > this->get_set_size() ? t.get_set_size() : this->get_set_size();
    Tritset tmp(size);
    for(unsigned int i = 0; i < size; i++)
    {
        tmp.setValue(i, get(i) | t.get(i));
    }
    return tmp;
}

Tritset Tritset:: operator&(Tritset const & t) const{

    unsigned int size = t.get_set_size() > this->get_set_size() ? t.get_set_size() : this->get_set_size();
    Tritset tmp(size);
    for(unsigned int i = 0; i < size; i++)
    {
        tmp.setValue(i, get(i) & t.get(i));
    }
    return tmp;
}

std::size_t Tritset::TritHash::operator()(TritValue t) const { return std::hash<int>()((int)t); }

std::unordered_map<TritValue, size_t, Tritset::TritHash> Tritset::cardinality() const
{
    std::unordered_map<TritValue, size_t, Tritset::TritHash> umap;
    umap = { {TritValue::UNKNOWN,cardinality(TritValue::UNKNOWN)},
                                 {TritValue::TRUE, cardinality(TritValue::TRUE)},
                                 {TritValue::FALSE, cardinality(TritValue::FALSE)} };
    return umap;
}
