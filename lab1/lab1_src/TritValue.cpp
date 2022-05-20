#include "TritValue.h"

TritValue Int_to_Trit(unsigned int a)
{

    switch (a)
    {
        case 0:
            return TritValue::UNKNOWN;
        case 1:
            return TritValue::FALSE;
        case 2:
            return TritValue::TRUE;
        default:
            return TritValue::UNKNOWN;
    }
}

unsigned int Trit_to_Int(TritValue a)
{
    if (a == TritValue::TRUE)
    {
        return 2;
    }
    if (a == TritValue::UNKNOWN)
    {
        return 0;
    }
    if (a == TritValue::FALSE)
    {
        return 1;
    }
    return 0;
}


TritValue operator &(TritValue trit1,TritValue trit2)
{
    if( (trit1 == TritValue::FALSE) || (trit2 == TritValue::FALSE))
    {
        return TritValue::FALSE;
    }
    else if((trit1 == TritValue:: UNKNOWN) || (trit2 == TritValue::UNKNOWN))
    {
        return TritValue::UNKNOWN;
    }
    else
    {
        return TritValue::TRUE;
    }
}

TritValue operator |(TritValue trit1,TritValue trit2)
{
    if( (trit1 == TritValue::TRUE) || (trit2 == TritValue::TRUE))
    {
        return TritValue::TRUE;
    }
    else if((trit1 == TritValue:: UNKNOWN) || (trit2 == TritValue::UNKNOWN))
    {
        return TritValue::UNKNOWN;
    }
    else
    {
        return TritValue::FALSE;
    }
}

TritValue operator !(TritValue trit1)
{
    TritValue trit2;
    switch(trit1)
    {
        case TritValue::UNKNOWN:
            trit2 = TritValue::UNKNOWN;
            break;
        case TritValue::TRUE:
            trit2 = TritValue::FALSE;
            break;
        case TritValue::FALSE:
            trit2 = TritValue::TRUE;
            break;
    }

    return trit2;
}