#include "gtest/gtest.h"
#include <cmath>
#include "../../lab1_src/Tritset.h"


TEST(TritTest, Operation)
{
TritValue first = TritValue::UNKNOWN;
TritValue second = TritValue::FALSE;
TritValue third = TritValue::TRUE;

EXPECT_EQ(!first, TritValue::UNKNOWN);
EXPECT_EQ(!second, TritValue::TRUE);
EXPECT_EQ(!third, TritValue::FALSE);


EXPECT_EQ(first|second, TritValue::UNKNOWN);
EXPECT_EQ((first|third), TritValue::TRUE);
EXPECT_EQ((first&second), TritValue::FALSE);
EXPECT_EQ((first&third), TritValue::UNKNOWN);

EXPECT_EQ(Trit_to_Int(first), 0);
EXPECT_EQ(Trit_to_Int(second), 1);
EXPECT_EQ(Trit_to_Int(third), 2);

EXPECT_EQ(Int_to_Trit(0), TritValue::UNKNOWN);
EXPECT_EQ(Int_to_Trit(1), TritValue::FALSE);
EXPECT_EQ(Int_to_Trit(2), TritValue::TRUE);
}

TEST(MemoryTests, ConstructorAllocationTest)
{
    for(int i = 0; i <= 1000; ++i)
    {
        Tritset t(i);

        size_t allocLength = t.capacity();
        EXPECT_GE(allocLength, i * 2 / 8 / sizeof(unsigned int));
    }
}

TEST(MemoryTests, UnknownOutOfBound)
{
    Tritset set(1000);
    size_t allocLength = set.capacity();

    set[1000000000] = TritValue::UNKNOWN;
    EXPECT_EQ(allocLength, set.capacity());
}

TEST(MemoryTests, OutOfBoundAllocation)
{
    Tritset trits(1000);
    size_t allocLength = trits.capacity();

    trits[1000000000] = TritValue::TRUE;
    EXPECT_LT(allocLength, trits.capacity());
}

TEST(MemoryTests, tritOperationAllocation)
{
    Tritset setA(1000);
    Tritset setB(2000);

    Tritset setC = setA | setB;

    EXPECT_EQ(setB.capacity(), setC.capacity());
}

TEST(MemoryTests, ShrinkMemoryFree)
{

    Tritset set(1000);
    set[100100] = TritValue::TRUE;
    set[100100] = TritValue::UNKNOWN;

    int x = 31;

    set[x] = TritValue::FALSE;

    set.shrink();
    unsigned int y = ceil((2.0 * (x + 1)) / (8.0 * sizeof(unsigned int)));
    EXPECT_EQ(y, set.capacity());
    EXPECT_EQ(x + 1, set.get_set_size());
}

TEST(TritsetTest, OperationAND)
{
    Tritset setA(3);
    Tritset setB(3);

    setA[0] = TritValue::UNKNOWN;
    setA[1] = TritValue::UNKNOWN;
    setA[2] = TritValue::UNKNOWN;

    setB[0] = TritValue::TRUE;
    setB[1] = TritValue::FALSE;
    setB[2] = TritValue::UNKNOWN;

    Tritset setC = setA & setB;

    EXPECT_TRUE(setC[0] == TritValue::UNKNOWN);
    EXPECT_TRUE(setC[1] == TritValue::FALSE);
    EXPECT_TRUE(setC[2] == TritValue::UNKNOWN);
}

TEST(TritsetTest, OperationOr)
{
    Tritset setA(3);
    Tritset setB(3);

    setA[0] = TritValue::UNKNOWN;
    setA[1] = TritValue::UNKNOWN;
    setA[2] = TritValue::UNKNOWN;

    setB[0] = TritValue::TRUE;
    setB[1] = TritValue::FALSE;
    setB[2] = TritValue::UNKNOWN;

    Tritset setC = setA | setB;

    EXPECT_TRUE(setC[0] == TritValue::TRUE);
    EXPECT_TRUE(setC[1] == TritValue::UNKNOWN);
    EXPECT_TRUE(setC[2] == TritValue::UNKNOWN);
}

TEST(TritsetTest, OperationNot)
{
    Tritset setA(3);

    setA[0] = TritValue::TRUE;
    setA[1] = TritValue::FALSE;
    setA[2] = TritValue::UNKNOWN;

    Tritset setC = !setA;

    EXPECT_TRUE(setC[0] == TritValue::FALSE);
    EXPECT_TRUE(setC[1] == TritValue::TRUE);
    EXPECT_TRUE(setC[2] == TritValue::UNKNOWN);
}

TEST(TritsetTest,Constructor)
{
Tritset t(10);
unsigned int length = t.get_size_b();
EXPECT_TRUE(length >= 10);
}

TEST (TritsetTest,Cardinality){
    Tritset t(5);
    t[0] = TritValue::TRUE;
    t[1] = TritValue::UNKNOWN;
    t[2] = TritValue::FALSE;
    t[3] = TritValue::UNKNOWN;
    t[4] = TritValue::FALSE;
EXPECT_EQ(t.cardinality(TritValue::TRUE),1);
EXPECT_EQ(t.cardinality(TritValue::UNKNOWN), 2);
EXPECT_EQ(t.cardinality(TritValue::FALSE), 2);
}

TEST (TritsetTest,CardinalityMap){
    Tritset t(6);
    t[0] = TritValue::TRUE;
    t[1] = TritValue::UNKNOWN;
    t[2] = TritValue::FALSE;
    t[3] = TritValue::UNKNOWN;
    t[4] = TritValue::FALSE;
    t[5] = TritValue::FALSE;

    auto a = t.cardinality();

    EXPECT_EQ(a[TritValue::TRUE],1);
    EXPECT_EQ(a[TritValue::UNKNOWN], 2);
    EXPECT_EQ(a[TritValue::FALSE], 3);
}

TEST (TritsetTest,Trim){
    Tritset t(6);
    t[0] = TritValue::TRUE;
    t[1] = TritValue::UNKNOWN;
    t[2] = TritValue::FALSE;
    t[3] = TritValue::UNKNOWN;
    t[4] = TritValue::FALSE;
    t[5] = TritValue::FALSE;

    t.trim(2);

    EXPECT_TRUE(t[2] == TritValue::UNKNOWN && t[3] == TritValue::UNKNOWN && t[4] == TritValue::UNKNOWN && t[5] == TritValue::UNKNOWN );
}

TEST(OtherFunctionsTests, LenTest)
{
    Tritset t(6);
    t[0] = TritValue::TRUE;
    t[1] = TritValue::UNKNOWN;
    t[2] = TritValue::FALSE;
    t[3] = TritValue::UNKNOWN;
    t[4] = TritValue::FALSE;
    t[5] = TritValue::UNKNOWN;

    EXPECT_EQ(t.length(), 5);
}

TEST(OtherFunctionsTests, get_and_SetValue)
{
Tritset t(9);
t[0] = TritValue::FALSE;
t[1] = TritValue::FALSE;
t[2] = TritValue::UNKNOWN;
t[3] = TritValue::UNKNOWN;
t[4] = TritValue::TRUE;
t[5] = TritValue::TRUE;
t[6] = TritValue::FALSE;
t[7] = TritValue::TRUE;
t[8] = TritValue::TRUE;
t.setValue(6, TritValue::TRUE);
 EXPECT_EQ(t[6] , TritValue::TRUE);
 EXPECT_EQ(t.get(3) , TritValue::UNKNOWN);
}

TEST(OtherFunctionsTests, EqTest) {
    Tritset t1;
    t1[0] = TritValue::UNKNOWN;
    t1[1] = TritValue::FALSE;
    t1[2] = TritValue::TRUE;
    Tritset t2;
    t2[0] = TritValue::UNKNOWN;
    t2[1] = TritValue::FALSE;
    t2[2] = TritValue::TRUE;
    EXPECT_TRUE(t1 == t2);
}

