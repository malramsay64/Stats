//
// Created by malcolm on 26/11/15.
//

#include "Stats.h"

namespace Stats {

    Stats::Stats() {
        M1 = M2 = M3 = M4 = 0.0;
        n = 0;
    }

    void Stats::push(double val) {
        double delta, delta_n, delta_n2, term1;
        long long n1 = n;
        n++;
        delta = val - M1;
        delta_n = delta / n;
        delta_n2 = delta_n * delta_n;
        term1 = delta * delta_n * n1;
        M1 += delta_n;
        M4 += term1 * delta_n2 * (n * n - 3 * n + 3) + 6 * delta_n2 * M2 - 4 * delta_n * M3;
        M3 += term1 * delta_n * (n - 2) - 3 * delta_n * M2;
        M2 += term1;
    }

    /* Combine two Stats objects together
     * Uses algorithm from Timothy Terriberry
     * http://people.xiph.org/~tterribe/notes/homs.html
     *
     * A generalisation of this same algorithm is used to
     * compute the online statistics.
     */
    void Stats::push(const Stats &s) {
        long nx = s.n+n, na = n, nb = s.n;
        double delta = s.M1 - M1;
        double delta_n = delta/nx;
        double delta_n2 = delta_n * delta_n;
        M1 += delta_n * nb;
        M4 += s.M4 + delta_n*delta_n2*delta*na*nb*(na*na-na*nb+nb*nb)\
                + 6*delta_n2*(na*na*s.M2 + nb*nb*M2)\
                + 4*delta_n*(na*s.M3-nb*M3);
        M3 += s.M3 + delta_n2*delta*na*nb*(na-nb)\
                + 3*delta_n*(na*s.M2 - nb*M2);
        M2 += s.M2 + delta*delta_n*na*nb;
        n += s.n;
    }

    double Stats::getMean() const {
        return M1;
    }

    double Stats::getVariance() const {
        if (n > 1){
            return M2 / (n - 1);
        }
        return 0;
    }

    double Stats::getStandardDeviation() const {
        return sqrt(getVariance());
    }

    double Stats::getSkewness() const {
        if (n > 2){
            return sqrt(double(n)) * M3 / pow(M2, 1.5);
        }
        return 0;
    }

    double Stats::getKurtosis() const {
        if (n > 2) {
            return double(n) * M4 / (M2 * M2) - 3.0;
        }
    }

    long long Stats::numVals() const{
        return n;
    }


}
