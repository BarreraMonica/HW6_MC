from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import matplotlib.pyplot as plt
import numpy as np
import sys
import os

file = "salida.dat"

n_time =500
puntosx = 41
puntosy = 41
data = np.loadtxt(file)

for i in range(0,n_time):
    u=data[2*i*puntosx:(2*i+1)*puntosx][:]
    v=data[(2*i+1)*puntosx:(2*i+2)*puntosx][:]

    x = np.linspace(0.0,2.0,puntosx)
    y = np.linspace(0.0,2.0,puntosy)
    
    img=plt.figure(figsize = (11,7), dpi=100)
    ax=img.gca(projection='3d')

    X,Y = np.meshgrid(x,y)
    wire1 = ax.plot_wireframe(X,Y,u)
    wire2 = ax.plot_wireframe(X,Y,v)
    
    plt.savefig('img%s.png'%(i), format = 'png')
    plt.close()

#Funcion de ImageMagick
os.system('convert -delay 0.0001 -loop 0 $(ls -v img*.png) burgers.gif')
#Remover las imagenes despues de generar el gif
os.system('rm -r img*.png')
