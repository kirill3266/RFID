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

Gnuplot::Gnuplot() {
#ifdef WIN32
    gnuplotpipe = _popen(GNUPLOT_NAME, "w");
    fprintf(gnuplotpipe, "cd '%s'\n", DIR);
#else
    gnuplotpipe  = popen(GNUPLOT_NAME, "w");
#endif

    if (!gnuplotpipe) {
        std::cerr << ("Gnuplot not found !");
    }
}

Gnuplot::~Gnuplot() {
    fprintf(gnuplotpipe, "exit\n");

#ifdef WIN32
    _pclose(gnuplotpipe);
#else
    pclose(gnuplotpipe);
#endif
}

void Gnuplot::operator()(const std::string &command) {
    fprintf(gnuplotpipe, "%s\n", command.c_str());
    fflush(gnuplotpipe); //without fflush nothing will draw
};

#endif