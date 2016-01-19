//
// Created by malcolm on 26/11/15.
//

#ifndef STATS_STATS_H
#define STATS_STATS_H

#include<cmath>

namespace Stats {

    class Stats {
        long long n;
        double M1, M2, M3, M4;
    public:
        Stats();

        void push(double val);

        void push(const Stats &);

        double getMean() const;

        double getVariance() const;

        double getStandardDeviation() const;

        double getSkewness() const;

        double getKurtosis() const;

        long long numVals() const;
    };
};

#endif //STATS_STATS_H
