//
// Created by malcolm on 18/01/16.
//

#include <iostream>
#include <gtest/gtest.h>
#include "Stats.h"

TEST(Stats, Initialisation){
    Stats::Stats s{};
    EXPECT_DOUBLE_EQ(0, s.getMean());
    EXPECT_EQ(0, s.numVals());
    EXPECT_EQ(0, s.getVariance());
    EXPECT_EQ(0, s.getStandardDeviation());
    EXPECT_EQ(0, s.getSkewness());
    EXPECT_EQ(0, s.getKurtosis());
}

TEST(Stats, Push){
    Stats::Stats s{};
    s.push(0.1);
    s.push(-0.1);
    EXPECT_EQ(0, s.getMean());
}

TEST(Stats, PushStats){
    std::vector<double> d1{4,7};
    std::vector<double> d2{13,16};
    std::vector<double> d3{1.,1.,1.,1.,1.,1.1,1.1,1.1,1.1,0.9,0.9,0.9,0.9,1.2,1.2,1.2,0.8,0.8,0.8};
    std::vector<double> d4{0.1,0.2,0.3,-0.2,-0.1,0.2,-0.2, 0.1, -0.1, 0.1, -0.1};
    Stats::Stats s1{}, s2{}, s3{}, s4{}, s5{}, s6{};
    for (auto item : d1) {
        s1.push(item);
    }
    s2 = Stats::Stats{s1};
    for (auto item : d2) {
        s1.push(item);
        s3.push(item);
    }
    s2.push(s3);
    EXPECT_DOUBLE_EQ(10, s2.getMean());
    EXPECT_DOUBLE_EQ(30, s2.getVariance());
    EXPECT_DOUBLE_EQ(s1.getSkewness(), s2.getSkewness());
    EXPECT_DOUBLE_EQ(s1.getKurtosis(), s2.getKurtosis());
    for (auto item : d3) {
        s4.push(item);
    }
    s5 = Stats::Stats{s4};
    for (auto item : d4) {
        s4.push(item);
        s6.push(item);
    }
    s5.push(s6);
    EXPECT_DOUBLE_EQ(s4.getMean(), s5.getMean());
    EXPECT_DOUBLE_EQ(s4.getVariance(), s5.getVariance());
    EXPECT_DOUBLE_EQ(s4.getSkewness(), s5.getSkewness());
    EXPECT_DOUBLE_EQ(s4.getKurtosis(), s5.getKurtosis());
}

TEST(Stats, Mean){
    Stats::Stats s{};
    s.push(-1.0);
    s.push(1.0);
    s.push(-1.0);
    s.push(1.0);
    ASSERT_DOUBLE_EQ(0.0,s.getMean());
    Stats::Stats t{};
    t.push(-1.0);
    t.push(1.0);
    t.push(2.0);
    t.push(3.0);
    ASSERT_DOUBLE_EQ(1.25, t.getMean());
}

TEST(Stats,Variance){
    Stats::Stats x{},y{},z{},a{},b{};
    x.push(1.0);
    ASSERT_EQ(0,x.getVariance());
    y.push(1.0);
    y.push(1.0);
    y.push(1.0);
    y.push(1.0);
    ASSERT_DOUBLE_EQ(0.0, y.getVariance());
    z.push(-1);
    z.push(-1);
    z.push(0);
    z.push(1);
    z.push(1);
    ASSERT_DOUBLE_EQ(1,z.getVariance());
    a.push(4);
    a.push(7);
    a.push(13);
    a.push(16);
    EXPECT_DOUBLE_EQ(30, a.getVariance());
    EXPECT_DOUBLE_EQ(10, a.getMean());
    b.push(10e8+4);
    b.push(10e8+7);
    b.push(10e8+13);
    b.push(10e8+16);
    EXPECT_DOUBLE_EQ(30, b.getVariance());
    EXPECT_DOUBLE_EQ(10e8+10, b.getMean());

}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}