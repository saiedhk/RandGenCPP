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

// Sample usage program for RandGen class.

#include <iostream>
#include "shk_randgen.h"

using namespace std;
using namespace shk;

const int N=1000;

RandGen randgen(37134);  // construct a RandGen with an arbitrary seed

int main()
{
    for (int i=0; i<N; i++)
    {
        cout << randgen.normal(1.,0.) << endl;
        //cout << randgen.erlang(5,1.);
        //cout << randgen.exponential(1.);
        //cout << randgen.geometric(0.34);
        //cout << randgen.poisson(5.0);
    }

    return 0;
}












