#ifndef _GNUPLOT_H_
#define _GNUPLOT_H_

#include <cstdio>
#include <string>
#include <iostream>

#define GNUPLOT_NAME "gnuplot -persist"
#define DIR "YOUR_DIR"

class Gnuplot {
public:
    Gnuplot();

    ~Gnuplot();

    void operator()(const std::string &command); // send commant to gnuplot

protected:
    FILE *gnuplotpipe;
};


#endif