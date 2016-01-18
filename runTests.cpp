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
}

TEST(StatsClass, Mean){
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

TEST(StatsClass,Variance){
    Stats::Stats x,y,z;
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
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}