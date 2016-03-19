from mpl_toolkits.mplot3d import axes3d
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.pyplot import cm
import os, sys

def Ana_T_E_C_M_X(filename):
    T,E,C,M,X = np.loadtxt(filename,unpack=True,skiprows=1)

    fig = plt.figure()
    title ="T_E"
    plt.title(title)
    #plt.xlim(-0.2,4)
    plt.xlabel("T")
    plt.ylabel("E")
    plt.plot(T,E,"*-")
    plt.savefig(filename[:-4]+title+".png")
    plt.close()

    fig = plt.figure()
    title ="T_C"
    plt.title(title)
    #plt.xlim(-0.2,4)
    plt.xlabel("T")
    plt.ylabel("C")
    plt.plot(T,C,"*-")
    plt.savefig(filename[:-4]+title+".png")
    plt.close()

    fig = plt.figure()
    title ="T_M"
    plt.title(title)
    #plt.xlim(-0.2,4)
    plt.xlabel("T")
    plt.ylabel("M")
    plt.plot(T,M,"*-")
    plt.savefig(filename[:-4]+title+".png")
    plt.close()

    fig = plt.figure()
    title ="T_X"
    plt.title(title)
    #plt.xlim(-0.2,4)
    plt.xlabel("T")
    plt.ylabel("X")
    plt.plot(T,X,"*-")
    plt.savefig(filename[:-4]+title+".png")
    plt.close()

def Ana_m_E_Ec_M_Mc(filename):
    m,E,Ec,M,Mc = np.loadtxt(filename,unpack=True,skiprows=2)

    plt.figure()
    title = "m_Ec(E=%f)" %E[0]
    plt.title(title)
    plt.xlabel("m")
    plt.ylabel("Ec")
    plt.plot(m,Ec)
    plt.savefig(filename[:-4]+title+".png")

    plt.figure()
    title = "m_Mc(M=%f)" %M[0]
    plt.title(title)
    plt.xlabel("m")
    plt.ylabel("Mc")
    plt.plot(m,Mc)
    plt.savefig(filename[:-4]+title+".png")

def Ana_corr_E_M(filename):
    j,Ecorr,Mcorr = np.loadtxt(filename,unpack=True,skiprows=2)

    plt.figure()
    title = "j_Ecorr"
    plt.title(title)
    plt.xlabel("j")
    plt.ylabel("$\Gamma(E)$")
    plt.ylim(0,1)
    plt.plot(j,Ecorr)
    plt.savefig(filename[:-4]+title+".png")

    plt.figure()
    title = "j_Mcorr"
    plt.title(title)
    plt.xlabel("j")
    plt.ylabel("$\Gamma(M)$")
    plt.ylim(0,1)
    plt.plot(j,Mcorr)
    plt.savefig(filename[:-4]+title+".png")

def main():
    #Ana_T_E_C_M_X("./data/Metropolis/output_T_E_C_M_X(D=2,L=128).dat")
    #Ana_T_E_C_M_X("./data/Worff/output_T_E_C_M_X(D=2,L=128).dat")
    #Ana_T_E_C_M_X("./data/Irre_Worff/output_T_E_C_M_X(D=2,L=128).dat")

    #Ana_T_E_C_M_X("./data/Metropolis/output_T_E_C_M_X(D=3,L=32).dat")
    #Ana_T_E_C_M_X("./data/Worff/output_T_E_C_M_X(D=3,L=32).dat")
    #Ana_T_E_C_M_X("./data/Irre_Worff/output_T_E_C_M_X(D=3,L=32).dat")

    #Ana_m_E_Ec_M_Mc("./data/Metropolis/output_m_E_Ec_M_Mc(D=2,L=64).dat")
    #Ana_m_E_Ec_M_Mc("./data/Worff/output_m_E_Ec_M_Mc(D=2,L=64).dat")
    #Ana_m_E_Ec_M_Mc("./data/Irre_Worff/output_m_E_Ec_M_Mc(D=2,L=64).dat")

    #Ana_m_E_Ec_M_Mc("./data/Metropolis/output_m_E_Ec_M_Mc(D=3,L=32).dat")
    #Ana_m_E_Ec_M_Mc("./data/Worff/output_m_E_Ec_M_Mc(D=3,L=32).dat")
    #Ana_m_E_Ec_M_Mc("./data/Irre_Worff/output_m_E_Ec_M_Mc(D=3,L=32).dat")

    Ana_corr_E_M("./data/Metropolis/autocorr_E_M(D=3,L=32).dat")

if __name__ == "__main__":
    main()



