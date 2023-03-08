//
// Created by lunam on 3/1/2023.
//
#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <cmath>
#include "mathlib.h"

#define ERR_MARGIN 0.00001

class MathlibTest : public ::testing::Test {
protected:
    TExpressionParser parser{};
};

TEST_F(MathlibTest, Test1) {
    EXPECT_EQ(parser.ParseExpressionToFloat("8 + 10"),   18.0);
}
TEST_F(MathlibTest, Test2) {
    EXPECT_EQ(parser.ParseExpressionToFloat("(98 - 37)"),   61.0);
}
TEST_F(MathlibTest, Test3) {
    EXPECT_EQ(parser.ParseExpressionToFloat("-63"),   -63.0);
}
TEST_F(MathlibTest, Test4) {
    EXPECT_EQ(parser.ParseExpressionToFloat("2 ^ 9"),   512.0);
}
TEST_F(MathlibTest, Test5) {
    EXPECT_EQ(parser.ParseExpressionToFloat("10 + 65"),   75.0);
}
TEST_F(MathlibTest, Test6) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("sqrt(93)"),   9.64365, ERR_MARGIN);
}
TEST_F(MathlibTest, Test7) {
    EXPECT_EQ(parser.ParseExpressionToFloat("49 + 59"),   108.0);
}
TEST_F(MathlibTest, Test8) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("(86 / 76)"),   1.13158, ERR_MARGIN);
}
TEST_F(MathlibTest, Test9) {
    EXPECT_EQ(parser.ParseExpressionToFloat("86 - 60"),   26.0);
}
TEST_F(MathlibTest, Test10) {
    EXPECT_EQ(parser.ParseExpressionToFloat("(71 * 21)"),   1491.0);
}
TEST_F(MathlibTest, Test11) {
    EXPECT_EQ(parser.ParseExpressionToFloat("(65 + 99)"),   164.0);
}
TEST_F(MathlibTest, Test12) {
    EXPECT_EQ(parser.ParseExpressionToFloat("10 + 65 + 86 - 60"),   101.0);
}
TEST_F(MathlibTest, Test13) {
    EXPECT_EQ(parser.ParseExpressionToFloat("77 * 44"),   3388.0);
}
TEST_F(MathlibTest, Test14) {
    EXPECT_EQ(parser.ParseExpressionToFloat("(86 - 60 * 68)"),   -3994.0);
}
TEST_F(MathlibTest, Test15) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("sqrt(66)"),   8.12404, ERR_MARGIN);
}
TEST_F(MathlibTest, Test16) {
    EXPECT_EQ(parser.ParseExpressionToFloat("40 * 49"),   1960.0);
}
TEST_F(MathlibTest, Test17) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("20 / sqrt(66)"),   2.46183, ERR_MARGIN);
}
TEST_F(MathlibTest, Test18) {
    EXPECT_EQ(parser.ParseExpressionToFloat("38 - 34"),   4.0);
}
TEST_F(MathlibTest, Test19) {
    EXPECT_EQ(parser.ParseExpressionToFloat("93 * 8"),   744.0);
}
TEST_F(MathlibTest, Test20) {
    EXPECT_EQ(parser.ParseExpressionToFloat("93 + 80"),   173.0);
}
TEST_F(MathlibTest, Test21) {
    EXPECT_EQ(parser.ParseExpressionToFloat("40 * 49 - 4"),   1956.0);
}
TEST_F(MathlibTest, Test22) {
    EXPECT_EQ(parser.ParseExpressionToFloat("-98"),   -98.0);
}
TEST_F(MathlibTest, Test23) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("-63 / 66"),   -0.95455, ERR_MARGIN);
}
TEST_F(MathlibTest, Test24) {
    EXPECT_EQ(parser.ParseExpressionToFloat("28 + 31"),   59.0);
}
TEST_F(MathlibTest, Test25) {
    EXPECT_EQ(parser.ParseExpressionToFloat("46 * 88"),   4048.0);
}
TEST_F(MathlibTest, Test26) {
    EXPECT_EQ(parser.ParseExpressionToFloat("10 + 65 + 86 - 60 + 42"),   143.0);
}
TEST_F(MathlibTest, Test27) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("41 / 49 + 59"),   59.83673, ERR_MARGIN);
}
TEST_F(MathlibTest, Test28) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("34 / 78"),   0.43590, ERR_MARGIN);
}
TEST_F(MathlibTest, Test29) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("(86 - 60 * 68) / 81"),   -49.30864, ERR_MARGIN);
}
TEST_F(MathlibTest, Test30) {
    EXPECT_EQ(parser.ParseExpressionToFloat("63 + 44"),   107.0);
}
TEST_F(MathlibTest, Test31) {
    EXPECT_EQ(parser.ParseExpressionToFloat("91 / 40 * 49 - 4"),   107.475);
}
TEST_F(MathlibTest, Test32) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("sqrt(27)"),   5.19615, ERR_MARGIN);
}
TEST_F(MathlibTest, Test33) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("(86 - 60 * 68) ^ 26"),   4.3312133186580905e+93);
}
TEST_F(MathlibTest, Test34) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("63 / 99"),   0.63636, ERR_MARGIN);
}
TEST_F(MathlibTest, Test35) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("(93 + 80 ^ 63 + 44)"),   7.8463771692333514e+119);
}
TEST_F(MathlibTest, Test36) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("9 / 81"),   0.11111, ERR_MARGIN);
}
TEST_F(MathlibTest, Test37) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("63 / 99 / 85"),   0.00749, ERR_MARGIN);
}
TEST_F(MathlibTest, Test38) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("29 / 37"),   0.78378, ERR_MARGIN);
}
TEST_F(MathlibTest, Test39) {
    EXPECT_EQ(parser.ParseExpressionToFloat("1 + 74"),   75.0);
}
TEST_F(MathlibTest, Test40) {
    EXPECT_EQ(parser.ParseExpressionToFloat("30 - 99"),   -69.0);
}
TEST_F(MathlibTest, Test41) {
    EXPECT_EQ(parser.ParseExpressionToFloat("26 * 16"),   416.0);
}
TEST_F(MathlibTest, Test42) {
    EXPECT_EQ(parser.ParseExpressionToFloat("26 * 16 - 34"),   382.0);
}
TEST_F(MathlibTest, Test43) {
    EXPECT_EQ(parser.ParseExpressionToFloat("-(98 - 37)"), -61.0);
}
TEST_F(MathlibTest, Test44) {
    EXPECT_EQ(parser.ParseExpressionToFloat("(69 - 23)"),   46.0);
}
TEST_F(MathlibTest, Test45) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("(22 ^ 39)"),   2.2619580800770516e+52);
}
TEST_F(MathlibTest, Test46) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("9 / (65 + 99)"),   0.05488, ERR_MARGIN);
}
TEST_F(MathlibTest, Test47) {
    EXPECT_EQ(parser.ParseExpressionToFloat("10 + 3"),   13.0);
}
TEST_F(MathlibTest, Test48) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("28 + 31 ^ 78"),   2.1193960426038701e+116);
}
TEST_F(MathlibTest, Test49) {
    EXPECT_EQ(parser.ParseExpressionToFloat("31 * 10 + 65 + 86 - 60 + 42"),   443.0);
}
TEST_F(MathlibTest, Test50) {
    EXPECT_EQ(parser.ParseExpressionToFloat("1 + 74 - 25"),   50.0);
}
TEST_F(MathlibTest, Test51) {
    EXPECT_EQ(parser.ParseExpressionToFloat("47 * 41"),  1927);
}
TEST_F(MathlibTest, Test52) {
    EXPECT_EQ(parser.ParseExpressionToFloat("(29 - 8)"),  21);
}
TEST_F(MathlibTest, Test53) {
    EXPECT_EQ(parser.ParseExpressionToFloat("1 + 10"),  11);
}
TEST_F(MathlibTest, Test54) {
    EXPECT_EQ(parser.ParseExpressionToFloat("-17"),  -17);
}
TEST_F(MathlibTest, Test55) {
    EXPECT_EQ(parser.ParseExpressionToFloat("19 * 1 + 10"),  29);
}
TEST_F(MathlibTest, Test56) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("16 / 40"),  0.4);
}
TEST_F(MathlibTest, Test57) {
    EXPECT_EQ(parser.ParseExpressionToFloat("(7 + 11)"),  18);
}
TEST_F(MathlibTest, Test58) {
    EXPECT_EQ(parser.ParseExpressionToFloat("22 + 29"),  51);
}
TEST_F(MathlibTest, Test59) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("(12 ^ -17)"),  4.507324411032949e-19);
}
TEST_F(MathlibTest, Test60) {
    EXPECT_EQ(parser.ParseExpressionToFloat("37 * 0"),  0);
}
TEST_F(MathlibTest, Test61) {
    EXPECT_EQ(parser.ParseExpressionToFloat("(47 * 41 - 9)"),  1918);
}
TEST_F(MathlibTest, Test62) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("sqrt(48)"),  6.928203230275509, ERR_MARGIN);
}
TEST_F(MathlibTest, Test63) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("2 ^ 36"),  68719476736);
}
TEST_F(MathlibTest, Test64) {
    EXPECT_EQ(parser.ParseExpressionToFloat("sqrt(9)"),  3.0);
}
TEST_F(MathlibTest, Test65) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("sqrt(sqrt(9))"),  1.7320508075688772);
}
TEST_F(MathlibTest, Test66) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("sqrt(45)"),  6.708203932499369, ERR_MARGIN);
}
TEST_F(MathlibTest, Test67) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("sqrt(12)"),  3.4641016151377544, ERR_MARGIN);
}
TEST_F(MathlibTest, Test68) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("32 ^ sqrt(12)"),  163678.8145263561, ERR_MARGIN);
}
TEST_F(MathlibTest, Test69) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("sqrt(1)"),  1.0);
}
TEST_F(MathlibTest, Test70) {
    EXPECT_EQ(parser.ParseExpressionToFloat("-22 + 29"),  7);
}
TEST_F(MathlibTest, Test71) {
    EXPECT_TRUE(std::isnan(parser.ParseExpressionToFloat("-32 ^ sqrt(12)"))); //-163678.8145263561); ???
}
TEST_F(MathlibTest, Test72) {
    EXPECT_EQ(parser.ParseExpressionToFloat("49 - (7 + 11)"),  31);
}
TEST_F(MathlibTest, Test73) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("6 / sqrt(12)"),  1.7320508075688774, ERR_MARGIN);
}
TEST_F(MathlibTest, Test74) {
    EXPECT_EQ(parser.ParseExpressionToFloat("19 * 6"),  114);
}
TEST_F(MathlibTest, Test75) {
    EXPECT_NEAR(parser.ParseExpressionToFloat("9 ^ sqrt(12)"),  2021.1242746401729, ERR_MARGIN);
}
TEST_F(MathlibTest, Test76) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("((47 * 41 - 9) / (47 * 41 - 9))"),  1.0);
}
TEST_F(MathlibTest, Test77) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("sqrt(sqrt(9)) / 17"),  0.10188534162169866);
}
TEST_F(MathlibTest, Test78) {
    EXPECT_EQ(parser.ParseExpressionToFloat("(40 * 0)"),  0);
}
TEST_F(MathlibTest, Test79) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("(26 ^ 30)"),  2.8131989012847462e+42);//2813198901284745919258621029615971520741376);
}
TEST_F(MathlibTest, Test80) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("-6 / sqrt(12)"),  -1.7320508075688774);
}
TEST_F(MathlibTest, Test81) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("sqrt(12) - 44"),  -40.53589838486224);
}
TEST_F(MathlibTest, Test82) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("(26 ^ 30) + ((47 * 41 - 9) / (47 * 41 - 9))"),  2.813198901284746e+42);
}
TEST_F(MathlibTest, Test83) {
    EXPECT_EQ(parser.ParseExpressionToFloat("-(7 + 11)"),  -18);
}
TEST_F(MathlibTest, Test84) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("38 + sqrt(1)"),  39.0);
}
TEST_F(MathlibTest, Test85) {
    EXPECT_EQ(parser.ParseExpressionToFloat("-2"),  -2);
}
TEST_F(MathlibTest, Test86) {
    EXPECT_EQ(parser.ParseExpressionToFloat("-35"),  -35);
}
TEST_F(MathlibTest, Test87) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("sqrt(1) ^ 38 + sqrt(1)"),  2.0);
}
TEST_F(MathlibTest, Test88) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("(sqrt(sqrt(9)) / 17 / 47 * 41)"),  0.08887870226573713);
}
TEST_F(MathlibTest, Test89) {
    EXPECT_EQ(parser.ParseExpressionToFloat("(20 - 49 - (7 + 11))"),  -47);
}
TEST_F(MathlibTest, Test90) {
    EXPECT_EQ(parser.ParseExpressionToFloat("(40 * 30)"),  1200);
}
TEST_F(MathlibTest, Test91) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("16 / 37"),  0.43243243243243246);
}
TEST_F(MathlibTest, Test92) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("sqrt(sqrt(9)) / 17 ^ sqrt(12) - 44"),  -43.99990534130094);
}
TEST_F(MathlibTest, Test93) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("-38 + sqrt(1)"),  -37.0);
}
TEST_F(MathlibTest, Test94) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("(12 ^ -17) - sqrt(48)"),  -6.928203230275509);
}
TEST_F(MathlibTest, Test95) {
    EXPECT_EQ(parser.ParseExpressionToFloat("10 * 4"),  40);
}
TEST_F(MathlibTest, Test96) {
    EXPECT_EQ(parser.ParseExpressionToFloat("26 * (7 + 11)"),  468);
}
TEST_F(MathlibTest, Test97) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("19 / 35"),  0.5428571428571428);
}
TEST_F(MathlibTest, Test98) {
    EXPECT_EQ(parser.ParseExpressionToFloat("1 + 10 - 8"),  3);
}
TEST_F(MathlibTest, Test99) {
    EXPECT_DOUBLE_EQ(parser.ParseExpressionToFloat("13 + (12 ^ -17) - sqrt(48)"),  6.071796769724491);
}
TEST_F(MathlibTest, Test100) {
    EXPECT_EQ(parser.ParseExpressionToFloat("26 + 26"),  52);
}