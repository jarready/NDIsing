#include "NDIsing.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

NDIsing::NDIsing(int D_set,
                 int L_set,
                 double T_set,
                 double J_set,
                 double H_set) {
    D = D_set; L = L_set; T = T_set; J = J_set; H = H_set;


    mark.resize(int(std::pow(L, D)));
    for (int i = 0; i < int(std::pow(L, D)); ++i) {
        int mod_left = i;
        for (int j = 0; j < D; ++j) {
            mark[i].locate.push_back(mod_left % L);
            mod_left  = mod_left / L;

            mark[i].neib_pos.push_back((i + int(std::pow(L, j))) % mark.size());
            mark[i].neib_pos.push_back((i - int(std::pow(L, j)) + mark.size()) % mark.size());
        }
        //init locate using L base code.
        mark[i].spin = 1;
    }
    to_flip = 1;
    Nu = mark.size();
    Nd = 0;  //  set Nu and Nd for Irre_Worff
}  // end NDIsing

/*
int NDIsing::get_D() {return D;}
int NDIsing::get_L() {return L;}
double NDIsing::get_T() {return T;}
double NDIsing::get_J() {return J;}
// get private variables methods
*/

void NDIsing::set_par(double T_set, double H_set) {
    T = T_set;
    H = H_set;
}
//set_par methods


double NDIsing::ave_E() {
    double E = 0;
    for (int pos = 0; pos < mark.size(); ++pos) {
        for (int neib : mark[pos].neib_pos ) {
            E += -0.5 * J * mark[pos].spin * mark[neib].spin;
        }
        E += -H * mark[pos].spin;
    }
    E /= mark.size();  //average E
    return E;
}//end ave_E


double NDIsing::ave_M() {
    double M = 0;
    for (int pos = 0; pos < mark.size(); ++pos) {
        M += mark[pos].spin;
    }
    M /= mark.size();  // average M
    return M;
}//end ave_M







