# RandGenCPP
A Pseudo-random Number Generator Class in C++

This class implements a pseudo-random number generator (PRNG), and a number of
class member functions providing useful probability distribuions. The core PRNG 
algorithm adopted here is xorshift1024*. 

This algorithm is described here: http://xorshift.di.unimi.it/

xorshift1024* uses an internal state which is 1024 bits and has a maximal period
of (2 ^ 1024 - 1). It is a fast and high-quality PRNG, which passes the BigCrush 
test in U01 test suite. It is studied and evaluated in this paper:   

Sebastiano Vigna, "An experimental exploration of Marsaglia's xorshift generators, 
scrambled" (2014). arXiv:1402.6246.

A RandGen object is seeded once only when a 'RandGen' it is constructed. If multiple
'RandGen' objects are instantiated in a program, they can have a different seed and 
hence can produce a different pseudo-random number stream.

This class provides the following set of member functions:

bool rand_bool(void);

int uniform_int(int a, int b);

double rand_double(void);

double uniform_double(double a, double b);

double exponential(double lambda);

int bernoulli(double p);

double normal(void);

double normal(double mu, double sigma);

double weibull(double a, double lambda);

double erlang(int n, double lambda);

int geometric(double p);

int binomial(int n, double p);

int negativebinomial(int n, double p);

int poisson(double lambda);
