#ifndef UPPER_PROJECT_TRITVALUE_H
#define UPPER_PROJECT_TRITVALUE_H
#include <iostream>


enum class TritValue {
    UNKNOWN = 0,
    FALSE = 1,
    TRUE = 2
};

unsigned int Trit_to_Int(TritValue a);
TritValue Int_to_Trit(unsigned int a);

TritValue operator &(TritValue trit1,TritValue trit2);
TritValue operator |(TritValue trit1,TritValue trit2);
TritValue operator !(TritValue trit1);

#endif //UPPER_PROJECT_TRITVALUE_H
