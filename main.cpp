#include <array>
#include <algorithm>
#include <cmath>
#include <random>
#include <cstdlib>
#include "gnuplot.h"


int main() {
    Gnuplot plot;

    int Q = 2; //Q value; differs from 0 to 15
    int Num = 10e4; //num of experiments; from 0 up to infinity

    int Nst = 0; //N start value;
    int Nfin = 40; //N stop value;
    int NStep = 1; //users step iterator

    int S = 0; //success counter
    int E = 0; //empty counter
    int C = 0; //conflict counter

    //probabilities in every epoch
    double Ps = 0;
    double Pe = 0;
    double Pc = 0;

    //end average probabilities
    double AvS;
    double AvE;
    double AvC;

    FILE *file = fopen("..//Out.txt", "w");
    fflush(file);

    if (!file) {
        perror("File opening failure!\n");
        return 1;
    }

    int r = 0; //randomizing tags window in frame
    std::random_device generator;
    std::uniform_int_distribution<int> distribution(0, RAND_MAX);
    //4 is 2^Q param, this array stores nums of windows in frame, need's to change after changing Q
    std::array<int, 4> a = {0, 0, 0, 0};
    for (int i = Nst; i < Nfin; i += NStep) {
        AvS = 0;
        AvE = 0;
        AvC = 0;
        for (int j = 1; j <= Num; j++) {
            std::fill(a.begin(), a.end(), 0);
            Ps = 0;
            Pe = 0;
            Pc = 0;

            S = 0;
            C = 0;
            E = 0;
            //generating random window for every tag
            for (int l = 0; l < i; l++) {
                r = distribution(generator) % (int) pow(2, Q);
                a[r]++;
            }

            //calculating nums of tags in frame windows
            for (int k = 0; k < pow(2, Q); k++) {
                if (a[k] > 1)C++;
                if (a[k] == 1) S++;
                if (a[k] == 0) E++;
            }

            Ps = (double) S / (S + C + E);
            Pe = (double) E / (S + E + C);
            Pc = (double) C / (S + E + C);

            AvS += Ps;
            AvE += Pe;
            AvC += Pc;
        }
        AvS /= Num;
        AvE /= Num;
        AvC /= Num;
        std::cout << i << " " << Q << " " << AvS << " " << AvE << " " << AvC << Q << "\n";
        fprintf(file, "%d %d %lf %lf %lf\n", i, Q, AvS, AvE, AvC);
    }


    plot("set title \"RFID\" font \"Times, 20\"");
    plot("set xrange [0:40]");
    plot("set yrange [0:1]");
    plot("set grid");
//for N;
    plot("set xlabel \"N\"");
    plot("set ylabel \"P\"");
    plot("set key title \"Q = 2\""); //replace Q here
    plot("plot \"Out.txt\" using 1:3 with lines title \"Pr_{success}\" lw 3 lc \"green\", \"Out.txt\" using 1:4 with lines title \"Pr_{conflict}\" lw 3 lc \"red\", \"Out.txt\" using 1:5 with lines title \"Pr_{empty}\" lw 3lc \"blue\"");
////for Q; Needs to add the way to Out file
//    plot("set xlabel \"Q\"");
//    plot("set ylabel \"P\"");
//    plot("set key title \"N = \""); //replace N here
//    plot("plot \"Out.txt\" using 2:3 with lines title \"Pr_{success}\" lw 3 lc \"green\", \"Out.txt\" using 2:4 with lines title \"Pr_{conflict}\" lw 3 lc \"red\", \"Out.txt\" using 2:5 with lines title \"Pr_{empty}\" lw 3 lc \"blue\"");

    fclose(file);
    return 0;
}

