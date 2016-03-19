// Copyleft[2016] Jarready
#include "NDIsing.h"
#include <iostream>
#include <ctime>
#include <string>

int main() {
    std::clock_t c_start = std::clock();
    // 2D parameters
    /*NDIsing miao(2,  // int D_set,
                 128,  // int L_set,
                 2.2,  // double T_set,
                 1,  // double J_set,
                 0  // double H_set);
                );
    */

    // 3D parameters
    NDIsing miao(2,  // int D_set,
                 128,  // int L_set,
                 2.2,  // double T_set,
                 1,  // double J_set,
                 0  // double H_set);
                );
    //std::string algorithm = "Metropolis";
    //std::string algorithm = "Worff";
    std::string algorithm = "Irre_Worff";

    /*
    miao.Metropolis(10000);
    miao.output_m_E_Ec_M_Mc(algorithm,  // std::string algorithm,
                            100,  // int equi_steps,
                            10000,  // int steps,
                            100,  // int blocks_begin,
                            1100,  // int blocks_end,
                            100,  // int d_blocks,
                            "./data/" +algorithm + "/output_m_E_Ec_M_Mc");
    */
    miao.Metropolis(10000);
    miao.output_autocorr_E_M(algorithm, // std::string algorithm,
                             100,     // int equi_steps,
                             1000,     // int steps,
                             1,      // int steps_ps,
                             100,       // int max_corr_steps,
                             "./data/" +algorithm + "/autocorr_E_M");

    /*miao.Metropolis(10000);
    miao.output_T_E_C_M_X(algorithm,  // std::string algorithm,
                          10,  // int equi_steps,
                          100,  // int ave_steps,
                          1,  // int steps_pas,
                          3,   // double T_begin,
                          6,  // double T_end,
                          0.1,  // double d_T,
                          "./data/" +algorithm + "/output_T_E_C_M_X" // std::string filename);
                         );
    */
    std::clock_t c_end = std::clock();
    std::cout << "\a\n used " << (c_end - c_start) / CLOCKS_PER_SEC << " seconds";
    return 0;
}