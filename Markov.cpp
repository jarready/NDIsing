#include "NDIsing.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <set>

void NDIsing::Markov(std::string algorithm, int steps) {
    if (algorithm == "Metropolis") {
        Metropolis(steps);
    } else if (algorithm == "Worff") {
        Worff(steps);
    } else if (algorithm == "Irre_Worff") {
        Irre_Worff(steps);
    } else {
        std::cout << "No such algorithm: " << algorithm << std::endl;
    }
}  //  end Markov

//-------------------Metropolis----------------------

double NDIsing::local_E(int pos) {
    double E = 0;
    for (int neib : mark[pos].neib_pos) {
        E += -J * mark[pos].spin * mark[neib].spin;
    }
    E += -H * mark[pos].spin;
    return E;
}  // end local_E

void NDIsing::Metropolis(int steps) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rand_pos(0, mark.size());  // random pos
    std::uniform_real_distribution<> rand_uni(0, 1);

    int pos;
    double old_locE, new_locE, pcc;
    for (int step = 0; step < steps; step++) {
        pos = rand_pos(gen);
        old_locE = local_E(pos);
        mark[pos].spin = -mark[pos].spin;  // flip
        new_locE = local_E(pos);
        pcc = std::exp(-(new_locE - old_locE) / T);
        if (rand_uni(gen) > pcc) {
            mark[pos].spin = -mark[pos].spin;
        }  // reject
    }  // end for steps loop
}  // end Metropolis


//--------------------Worff--------------------------

void NDIsing::Worff(int steps) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rand_pos(0, mark.size());  // random pos
    std::uniform_real_distribution<> rand_uni(0, 1);

    double pb = 1 - std::exp(-2 * J / T);
    int pos;
    std::set<int> C, F_old, F_new;
    for (int step = 0; step < steps; step++) {
        pos = rand_pos(gen);
        C.insert(pos);
        F_old.insert(pos);
        while (!F_old.empty()) {
            F_new.clear();
            for (int i : F_old) {
                for (int j : mark[i].neib_pos) {
                    if (mark[i].spin == mark[j].spin
                            && C.find(j) == C.end()
                            && rand_uni(gen) < pb) {
                        F_new.insert(j);
                        C.insert(j);
                    }
                }
            }
            F_old = F_new;
        }
        for (int k : C) {mark[k].spin *= -1;}
    }  // end for steps loop
}  // end Worff


void NDIsing::Irre_Worff(int steps) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rand_pos(0, mark.size());  // random pos
    std::uniform_real_distribution<> rand_uni(0, 1);

    double pb = 1 - std::exp(-2 * J / T);
    int pos;
    std::set<int> C, F_old, F_new;
    for (int step = 0; step < steps; step++) {
        pos = rand_pos(gen);
        C.insert(pos);
        F_old.insert(pos);
        while (!F_old.empty()) {
            F_new.clear();
            for (int i : F_old) {
                for (int j : mark[i].neib_pos) {
                    if (mark[i].spin == mark[j].spin
                            && C.find(j) == C.end()
                            && rand_uni(gen) < pb) {
                        F_new.insert(j);
                        C.insert(j);
                    }
                }
            }
            F_old = F_new;
        }
        for (int k : C) {mark[k].spin *= -1;}
    }  // end for steps loop
}
