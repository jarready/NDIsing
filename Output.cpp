#include "NDIsing.h"
#include <iostream>
#include <fstream>
#include <string>
double NDIsing::correlate(std::vector<double> A, int j) {
    double A_ave = 0;
    double sum_dAi_dAij = 0, sum_dAi_dAi = 0;
    for (double a : A) {A_ave += a;} A_ave /= A.size();
    for (int i = 0; i < A.size() - j; i++) {
        sum_dAi_dAi += (A[i] - A_ave) * (A[i] - A_ave);
        sum_dAi_dAij += (A[i] - A_ave) * (A[i + j] - A_ave);
    }
    return sum_dAi_dAij / sum_dAi_dAi;
}  // end correlate

void NDIsing::output_autocorr_E_M(std::string algorithm,
                                  int equi_steps,
                                  int steps,
                                  int steps_ps,
                                  int max_corr_steps,
                                  std::string filename) {
    std::cout << "output_autocorr_E_M is running (" << algorithm << ")" << std::endl;
    filename += "(D=" + std::to_string(D)
                + ",L=" + std::to_string(L) + ").dat";
    std::ofstream FILE(filename);
    if (FILE.is_open()) {
        std::vector<double> E, M;
        double E_ave = 0, M_ave = 0;
        //double E_2 = 0; M_2 = 0;
        Markov(algorithm, equi_steps);
        for (int step = 0; step < steps; step++) {
            E.push_back(ave_E());
            M.push_back(ave_M());
            Markov(algorithm, steps_ps);
            std::cout << step << "/" << steps << "\r";
            std::cout.flush();
        }
        FILE << "equi_steps: " << equi_steps
             << " steps: " << steps
             << " steps_ps: " << steps_ps << "\n";
        FILE << "j Ecorr Mcoor\n";
        for (int j = 0; j < max_corr_steps; j++) {
            FILE << j << " " << correlate(E, j) << " " << correlate(M, j) << "\n";
        }
    } FILE.close();
}  // end output_autocorr


void NDIsing::output_m_E_Ec_M_Mc(std::string algorithm,
                                 int equi_steps,
                                 int steps,
                                 int blocks_begin,
                                 int blocks_end,
                                 int d_blocks,
                                 std::string filename) {
    std::cout << "output_m_E_Ec_M_Mc is running (" << algorithm << ")" << std::endl;
    filename += "(D=" + std::to_string(D)
                + ",L=" + std::to_string(L) + ").dat";
    std::ofstream FILE(filename);
    if (FILE.is_open()) {
        std::vector<double> E, M;
        double E_ave = 0, M_ave = 0;
        double Ec, Mc;
        double E_ave_i, M_ave_i;
        Markov(algorithm, equi_steps);
        for (int step = 0; step < steps; step++) {
            E.push_back(ave_E());
            E_ave += E.back();
            M.push_back(ave_M());
            M_ave += M.back();
            Markov(algorithm, 1);
            std::cout << step << "/" << steps << "\r";
            std::cout.flush();
        }
        E_ave /= steps; M_ave /= steps;

        FILE << "equi_steps:" << equi_steps
             << " steps:" << steps << "\n";
        FILE << "m E Ec M Mc\n";
        for (int m = blocks_begin; m < blocks_end; m += d_blocks) {
            Ec = 0; Mc = 0;
            for (int i = 0; i < m; i++) {
                E_ave_i = 0; M_ave_i = 0;
                int block_size = steps / m;
                for (int j = 0; j < block_size; j++) {
                    E_ave_i += E[block_size * i + j];
                    M_ave_i += M[block_size * i + j];
                }
                E_ave_i /= block_size;
                M_ave_i /= block_size;
                Ec += (E_ave_i - E_ave) * (E_ave_i - E_ave);
                Mc += (M_ave_i - M_ave) * (M_ave_i - M_ave);
            }  // end E_ave_i loop
            Ec /= m * m; Ec = std::sqrt(Ec);
            Mc /= m * m; Mc = std::sqrt(Mc);
            FILE << m << " " << E_ave << " " << Ec << " " << M_ave << " " << Mc << "\n";
        }  // end blocks loop
    } FILE.close();
}  // end output_m_E_Ec


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
            for (int step = 0; step < ave_steps; ++step) {
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
    } FILE.close();
}  // end output_T_E_C_M_X