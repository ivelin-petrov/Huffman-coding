#ifndef _REGIMES_H_
#define _REGIMES_H_

#include <iostream>
#include <fstream>
#include "huffmantree.h"

class Regime{
  public:
    static void compressRegime();
    static void decompressRegime();
    static void visualRegime();
};

#endif