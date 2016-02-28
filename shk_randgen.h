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

#include <float.h>
#include <math.h>

// Asserts are disabled by default. To enable, comment the following line:
#define NDEBUG
#include <assert.h> 

#ifndef SHK_RANDGEN_H
#define SHK_RANDGEN_H
namespace shk 
{

typedef unsigned long long int uint64;   // 64-bit unsigned integer
typedef unsigned long int uint32;        // 32-bit unsigned integer
typedef long long int int64;             // 64-bit signed integer
typedef long int int32;                  // 32-bit signed integer


/**
   This class defines RandGen, a pseudo-random number generator (PRNG).
   Refer to README.md file for details.
*/
class RandGen
{

    public:

        //---------------------------
        // constructors
        //---------------------------

        /**
           Contructs a RandGen object using a hard-coded default seed
           @param seed
        */
        RandGen(void);

        /**
           Contructs a RandGen object using a single seed word
           @param seed, 64-bit unsigned integer
        */
        RandGen(uint64 seed);

        /**
           Contructs a RandGen object using an array of seed words
           @param seed, an array of 64-bit unsigned integers
           @param seedlength, lenght of seed array
        */
        RandGen(uint64 seed[], int seedlength);

        //---------------------------
        // generators
        //---------------------------

        /**
           Returns a random unsigned integer in [0,(2^64)-1].
        */
        uint64 rand_uint64(void);


        /**
           Returns a random unsigned integer in [0,(2^63)-1].
        */
        int64 rand_int63(void);


        /**
           Returns a random signed 64-bit integer
        */
        int64 rand_int64(void);


        /**
           Returns a random unsigned 32-bit integer
        */
        uint32 rand_uint32(void);


        /**
           Returns a random signed 32-bit integer
        */
        int32 rand_int32(void);


        /**
           Returns a random double number in [0,1]
        */
        double rand_double(void);


        /**
           Returns a uniformly-distributed random boolean variable {false,true}
        */
        bool rand_bool(void);


        /**
           Returns a uniformly-distributed random integer in [a,b]
        */
        int uniform_int(int a, int b);


        /**
           Returns a uniformly-distributed random double number in [a,b]
        */
        double uniform_double(double a, double b);


        /* Returns an exponentially-distributed double variable with mean = 1/lambda */
        double exponential(double lambda);


        /* Returns a Bernoulli-distributed variable in {0,1} (1 with probability p, 0 with probability 1-p) */
        int bernoulli(double p);


        /* Returns a Standard Normally-distributed number with mean = 0 and stdev = 1 */
        double normal(void);


        /* Returns a Normally-distributed number with mean = mu and stdev = sigma */
        double normal(double mu, double sigma);


        /* Returns a Weibull-distributed number with parameters a and lambda */
        double weibull(double a, double lambda);


        /* Returns an Erlang-distributed number with parameters n and lambda */
        double erlang(int n, double lambda);


        /* Returns an geometric-distributed integer with parameter p (probability of success) */
        int geometric(double p);


        /* Returns an binomial-distributed integer with parameter p (probability of success)
        and n (number of trials) */
        int binomial(int n, double p);


        /* Returns an negative binomial-distributed integer with parameter p (probability of success)
        and n (number of trials) */
        int negativebinomial(int n, double p);


        /* Returns an poisson-distributed integer with mean lambda */
        int poisson(double lambda);

    private:

        static const int STATE_LEN = 16; // hard coded constant (DO NOT CHANGE)
        uint64 state[STATE_LEN]; // 1024-bit internal state
        int p;
        uint64 x;
        uint64 xorshift64star(void)  // function used to expand an input seed
        {
            x ^= (x >> 12);
            x ^= (x << 25);
            x ^= (x >> 27);
            return x * 2685821657736338717ULL;
        }
};



inline int64   RandGen::rand_int64(void)  { return (int64) rand_uint64(); }
inline int64   RandGen::rand_int63(void)  { return (int64)(rand_uint64() >> 1); }
inline uint32  RandGen::rand_uint32(void) { return (uint32) rand_uint64(); }
inline int32   RandGen::rand_int32(void)  { return (int32) rand_uint64(); }
inline bool    RandGen::rand_bool(void)   { return (rand_uint64() & 1ULL) ? true : false; }
inline double  RandGen::rand_double(void) { return (rand_uint64() >> 11) * (1.0/9007199254740991.0); }

inline int RandGen::uniform_int(int a, int b)
{
    assert(a<b);
    return (( rand_int32() % (b - a + 1)) + a );
}


inline double RandGen::uniform_double(double a, double b)
{
    assert(a<b);
    return ((b - a) * rand_double() + a );
}


inline int RandGen::bernoulli(double p)
{
    assert((p>=0.) && (p<=1.));
    return ((rand_double() < p) ? 1 : 0);
}

} // namespace shk

#endif // SHK_RANDGEN_H
