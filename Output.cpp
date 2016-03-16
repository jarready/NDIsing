#include "NDIsing.h"

#include <iostream>
#include <fstream>
#include <string>

void NDIsing::output_T_E_C_M_X(std::string algorithm,
                               int equi_steps,
                               int ave_steps,
                               int steps_pas,
                               double T_begin,
                               double T_end,
                               double d_T,
                               std::string filename) {
    std::cout << "output_T_E_C_M_X is running (" << algorithm << ")" << std::endl;
    filename += "(D=" + std::to_string(D) + ",L=" + std::to_string(L) + ").dat";
    std::ofstream FILE(filename);
    if (FILE.is_open()) {
        FILE << "T E C M X\n";
        for (double t = T_begin; t < T_end; t += d_T) {
            set_par(t, H);
            Markov(algorithm, equi_steps);
            double buff_E = 0, E = 0, E2 = 0, C = 0,
                   buff_M = 0, M = 0, M2 = 0, X = 0;
            //get ready!~
            for (int step = 0; step < ave_steps; ++step)
            {
                Markov(algorithm, steps_pas);
                buff_E = ave_E();
                E += buff_E;
                E2 += buff_E * buff_E;
                buff_M = ave_M();
                M += buff_M;
                M2 += buff_M * buff_M;
            }//end ave for loop
            E /= ave_steps; E2 /= ave_steps; C = (E2 - E * E) / (T * T);
            M /= ave_steps; M2 /= ave_steps; X = (M2 - M * M) / T;

            FILE << t << " " << E << " " << C << " " << M << " " << X << "\n";
            std::cout << T_begin << " / " << t << " / " << T_end << "\r";
            std::cout.flush();
        }//end h for loop
    }
    FILE.close();
}  // end output_T_E_C_M_X

