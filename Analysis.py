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
def main():
    Ana_T_E_C_M_X("./data/Metropolis/output_T_E_C_M_X(D=2,L=128).dat")
    #Ana_T_E_C_M_X("./data/Worff/output_T_E_C_M_X(D=2,L=64).dat")

if __name__ == "__main__":
    main()



