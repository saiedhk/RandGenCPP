/**********************************************************************
   Project: C++ Class for Pseudo-Random Generation

   Language: C++ 2007	   
   Author: Saied H. Khayat
   Date:   Oct 2014
   URL: https://github.com/saiedhk/RandGenCPP
   
   Copyright Notice: Free use of this library is permitted under the
   guidelines and in accordance with the MIT License (MIT).
   http://opensource.org/licenses/MIT

**********************************************************************/

// Functions for RandGen class

#include <iostream>
using namespace std;

#include "shk_randgen.h"
namespace shk
{

//------------------------------------------------------
RandGen::RandGen(void)
{
    // default fixed seed array is set to digits of Pi (arbitrarily)
    state[0]  = 3141592653589793238ULL;
    state[1]  = 4626433832795028841ULL;
    state[2]  = 9716939937510582097ULL;
    state[3]  = 4944592307816406286ULL;
    state[4]  = 2089986280348253421ULL;
    state[5]  = 1706798214808651328ULL;
    state[6]  = 2306647093844609550ULL;
    state[7]  = 5822317253594081284ULL;
    state[8]  = 8111745028410270193ULL;
    state[9]  = 8521105559644622948ULL;
    state[10] = 9549303819644288109ULL;
    state[11] = 7566593344612847564ULL;
    state[12] = 8233786783165271201ULL;
    state[13] = 9091456485669234603ULL;
    state[14] = 4861045432664821339ULL;
    state[15] = 3607260249141273724ULL;
    p = 0;
}

//------------------------------------------------------
RandGen::RandGen(uint64 seed)
{
    p = 0;
    x = seed;
    assert(seed>0);
    // expand input seed into 16 state words
    for (int i=0; i<STATE_LEN; i++)
        state[i] = xorshift64star();
}

//------------------------------------------------------
RandGen::RandGen(uint64 seed[], int seedlength)
{
    if (!((seedlength > 0) && (seedlength < STATE_LEN)))
    {
        cerr << "fatal: RandGen(): bad parameters to construct RandGen!\n";
        exit(1);
    }
    bool flag = false;
    for (int i=0; i<seedlength; i++)
    {
        state[i] = seed[i];
        if (seed[i]) flag = true;
    }
    if (!flag) { cerr << "fatal: RandGen(): all seed words are zero!\n"; exit(1); }
}

//------------------------------------------------------
uint64 RandGen::rand_uint64(void)
{
    /*
    This function is the core of RandGen.
    Each time it is called, it returns a different 64-bit random unsigned integer.
    It was written by S. Vigna (vigna@acm.org) based on Marsaglia's xorshift*
    generators.
    */
	uint64 s0 = state[p];
	uint64 s1 = state[ p = (p + 1) & 15 ];
	s1 ^= s1 << 31; // a
	s1 ^= s1 >> 11; // b
	s0 ^= s0 >> 30; // c
	return ( state[p] = s0 ^ s1 ) * 1181783497276652981ULL;
}

//------------------------------------------------------
double RandGen::normal(void)
{
    // Box-Muller method
    const double PI = (4.0 * atan(1.0));
    double u1 = rand_double();
    double u2 = rand_double();
    if (u1 <= 0.0) u1 = DBL_MIN;
    return ( sqrt(-2*log(u1)) * cos(2*PI*u2) );
}

//------------------------------------------------------
double RandGen::normal(double sigma, double mu)
{
    // Box-Muller method
    const double PI = (4.0 * atan(1.0));
    double u1 = rand_double();
    double u2 = rand_double();
    if (u1 <= 0.0) u1 = DBL_MIN;
    return ( ( sqrt(-2*log(u1)) * cos(2*PI*u2) ) * sigma  + mu);
}

//------------------------------------------------------
double RandGen::exponential(double lambda)
{
    assert(lambda>0.0);
    double u = rand_double();
    if (u<=0.0) u = DBL_MIN;
    return ((-1/lambda) * log (u));
}

//------------------------------------------------------
double RandGen::weibull(double a, double lambda)
{
    double u = rand_double();
    if (u<=0.0) u = DBL_MIN;
    if (u>=1.0) u = 1.0 - DBL_MIN;
    u = -log(u);
    return ((1/lambda) * exp((1/a) * log(u)) );
}

//------------------------------------------------------
double RandGen::erlang(int n, double lambda)
{
    /* An Erlang random variable is sum of n exponential
       variables all having the same parameter lambda. */
    assert(lambda>0.0);
    assert(n>1);
    double u, x = 1.0;
    for (int i=0; i<n; i++)
    {
        u = rand_double();
        if (u<=0.0) u = DBL_MIN;
        x *= u;
    }
    return ((-1/lambda) * log(x));
}

//------------------------------------------------------
int RandGen::geometric(double p)
{
    assert((p>0.) && (p<1.));
    double u = rand_double();
    if (u<=0.0) u = DBL_MIN;
    return (int) (log(u) / log(1-p));
}

//------------------------------------------------------
int RandGen::binomial(int n, double p)
{
    assert((p>=0.) && (p<=1.));
    assert(n>=1);
    int sum = 0;
    for (int i=0; i<n; i++)
        sum += ((rand_double() < p) ? 1 : 0);
    return sum;
}

//------------------------------------------------------
int RandGen::negativebinomial(int n, double p)
{
    assert((p>0.) && (p<1.));
    assert(n>=1);
    int sum = 0;
    for (int i=0; i<n; i++)
        sum += geometric(p);
    return sum;
}

//------------------------------------------------------
int RandGen::poisson(double lambda)
{
    /* A random variable X has a Poisson distribution with parameter lambda if X is
       the number of events in a time interval of length 1, provided the inter-event
       times are independent and exponentially distributed with parameter lambda. */
    assert(lambda>0.0);
    int i = -1;
    double a = 1.0;
    double b = exp(-lambda);

    do {
        double u = rand_double();
        if (u<=0.0) u = DBL_MIN;
            a *= u;
            i++;
    } while (a >= b);

    return i;
}

} // namespace shk
