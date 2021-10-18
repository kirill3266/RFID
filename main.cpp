#include <iostream>
#include <array>
#include <algorithm>
#include <cmath>
#include <random>
#include <cstdlib>

int main() {

    int Q = 2; //Q value; differs from 0 to 15
    int Num = 100000; //num of experiments; from 0 up to infinity

    int Nst = 1; //N start value;
    int Nfin = 40; //N stop value;
    int NStep = 1; //users step iterator

    int S = 0; //success counter
    int E = 0; //empty counter
    int C = 0; //conflict counter

    double Ps = 0; //success probability in every epoch
    double Pe = 0;//empty probability in every epoch
    double Pc = 0;//conflict probability in every epoch

    double out;
    int WindowsReaden; //

    FILE *file = fopen("..//Out.txt", "w");
    fflush(file);

    if (!file) {
        perror("File opening failure!\n");
        return 1;
    }

    int r = 0; //randomizing tags window in frame
    std::random_device generator;
    std::uniform_int_distribution<int> distribution(1, RAND_MAX);
    std::array<int, 4> a = {0, 0, 0, 0}; //4 is 2^Q param, this array stores nums of windows in frame
    for (int i = Nst; i < Nfin; i += NStep) { //increasing num of users
        out = 0;
        WindowsReaden = 0;

        for (int j = 1; j <= Num; j++) { //num of epochs
            std::fill(a.begin(), a.end(), 0);
            Ps = 0;
            Pe = 0;
            Pc = 0;

            S = 0;
            C = 0;
            E = 0;

            for (int l = 0; l < i; l++) { //generating random window for every tag
                r = distribution(generator) % (int) pow(2, Q);
                a[r]++;
            }

//            //Debugging a
//            for (int m = 0; m < pow(2,Q);m++)
//                std::cout << "A[" << m << "] is: " << a[m] << "\n";

            for (int k = 0; k < pow(2, Q); k++) {//calculating nums of tags in frame windows
                WindowsReaden++;
                if (a[k] > 1) {
                    C++;
                    break;
                } //if conflict occurs, stop calculation other windows
                if (a[k] == 1) S++;
                if (a[k] == 0) E++;
            }

//            //Debugging c,s,f
//            std::cout << "C is: " << C << " " << "S is: " << S << " " << "E is: " << E << "\n";

            Ps = (double) S / (S + E + C);
            Pe = (double) E / (S + E + C);
            Pc = (double) C / (S + E + C);

//            //Debugging Ps, Pe,Pc
//            std::cout << "Ps is: " << Ps << " " << "Pe is: " << Pe << " " << "Pc is: " << Pc << "\n";

            out += Ps;
        }
        out /= Num;
        std::cout << out << " " << i << "\n";
        fprintf(file, "%d %lf\n", i, out);
    }

    fclose(file);
    return 0;
}

