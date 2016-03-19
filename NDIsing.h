#ifndef NDIsing_H
#define NDIsing_H

#include <iostream>
#include <string>
#include <vector>
#include <random>

class NDIsing {
// N dimensional NDIsing model
// H = -\sum{J \sigma_i \simga_j}
private:
    int D;  // space dimension
    int L;  // space size
    struct point {
        int spin;
        std::vector<int> locate;  // location in space description
        std::vector<int> neib_pos;  // neighbors' position storage
    };
    std::vector<point> mark;

    double T;  // for Temperature;
    double J;  // for J
    double H;  // for Megnetic field

    int to_flip;  // for Irre_Worff, branch mark
    int Nu, Nd;   // Number of spin up and down

public:
    NDIsing(int D_set,
            int L_set,
            double T_set,
            double J_set,
            double H_set);

    void set_par(double T_set, double H_set);  // reset parameters method

//---------------variable------------------
    double local_E(int pos);
    double ave_E();
    double ave_M();

//--------------Makov----------------------
    void Metropolis(int steps);
    //moving with metropolis method;

    void Worff(int steps);
    // moving with traditional worff method;

    void Irre_Worff(int steps);
    // irreversible worff algorithm

    void Markov(std::string algorithm, int steps);
    // using selected algorithm to move

//---------------tools----------------

    double correlate(std::vector<double> A, int j);

//---------------Write2file---------------
    void output_autocorr_E_M(std::string algorithm,
                             int equi_steps,
                             int steps,
                             int steps_ps,
                             int max_corr_steps,
                             std::string filename);

    void output_m_E_Ec_M_Mc(std::string algorithm,
                            int equi_steps,
                            int steps,
                            int blocks_begin,
                            int blocks_end,
                            int d_blocks,
                            std::string filename);

    void output_T_E_C_M_X(std::string algorithm,
                          int equi_steps,
                          int ave_steps,
                          int steps_pas,
                          double T_begin,
                          double T_end,
                          double d_T,
                          std::string filename);
}; // class NDIsing

#endif