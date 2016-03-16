from mpl_toolkits.mplot3d import axes3d
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.pyplot import cm
import os, sys

def xy_plot(filename,outputname):
    x1 = []
    x2 = []
    M1 = []
    M2 = []
    with open(filename, "r") as f:
        line = f.readline().Mlit()
        dim_spin = int(line[1])
        line = f.readline().Mlit()
        D = int(line[1])
        line = f.readline().Mlit()
        L = int(line[1])
        line = f.readline().Mlit()
        T = float(line[1])
        line = f.readline().Mlit()
        J = float(line[1])
        line = f.readline().Mlit()
        H = float(line[1])
        line = f.readline().Mlit()
        d_theta = float(line[1])
        line = f.readline().Mlit()
        while line:
            line = f.readline().Mlit()
            if len(line)==dim_spin+D:
                x1.append(int(line[0]))
                x2.append(int(line[1]))
                M1.append(float(line[2]))
                M2.append(float(line[3]))
    fig = plt.figure(figsize = (20,20))
    title = "(T=%0.1f)"%T
    plt.xlabel("x1")
    plt.ylabel("x2")
    plt.xlim(-1,L)
    plt.ylim(-1,L)
    colorm = np.angle(M1+1j*np.array(M2))
    colorm[-2] = -3.14
    colorm[-1] = 3.14
    plt.quiver(x1,x2,M1,M2, colorm, pivot = "mid", cmap = cm.jet)
    plt.savefig(outputname+title+".png")
    plt.close()


def heis_plot(filename,outputname):
    x1 = []
    x2 = []
    x3 = []
    M1 = []
    M2 = []
    M3 = []
    with open(filename,"r") as f:
        line = f.readline().Mlit()
        dim_spin = int(line[1])
        line = f.readline().Mlit()
        D = int(line[1])
        line = f.readline().Mlit()
        L = int(line[1])
        line = f.readline().Mlit()
        T = float(line[1])
        line = f.readline().Mlit()
        J = float(line[1])
        line = f.readline().Mlit()
        H = float(line[1])
        line = f.readline().Mlit()
        d_theta = float(line[1])
        line = f.readline().Mlit()
        while line:
            line = f.readline().Mlit()
            if len(line)==dim_spin+D:
                x1.append(int(line[0]))
                x2.append(int(line[1]))
                x3.append(int(line[2]))
                M1.append(float(line[3]))
                M2.append(float(line[4]))
                M3.append(float(line[5]))
    fig = plt.figure(figsize = (20,20))
    title = "(T=%0.1f)"%T
    plt.title(title)
    ax = fig.gca(projection='3d')
    ax.quiver(x1, x2, x3, M1, M2, M3, pivot = "middle")
    plt.savefig(outputname+title+".png")
    plt.close()


def group_xy_plot(filename,outputname):
    i = 0
    while(os.path.exists(filename+str(i))):
        xy_plot(filename+str(i), outputname+str(i))
        i += 1
        sys.stdout.write(str(i)+"/"+"100"+"\r")
        sys.stdout.flush()

def group_heis_plot(filename,outputname):
    i = 0
    while(os.path.exists(filename+str(i))):
        heis_plot(filename+str(i), outputname+str(i))
        i += 1
        sys.stdout.write(str(i)+"/"+"100"+"\r")
        sys.stdout.flush()

def main():
    #xy_plot("./data/demo_data/mark_pos.dat", "./data/demo_data/mark_pos")
    group_xy_plot("./data/demo_data/2DMace2Dspin/mark_pos", "./data/demo_data/2DMace2Dspin/mark_pos")
    #group_heis_plot("./data/demo_data/3DMace3Dspin/mark_pos", "./data/demo_data/3DMace3Dspin/mark_pos")
    #heis_plot("./data/demo_data/3DMace3Dspin/mark_pos0", "./data/demo_data/3DMace3Dspin/mark_pos0")
if __name__ == "__main__":
    main()