from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

file = "trayectoria_E_alpha.dat"

puntos=100
data = np.loadtxt(file)
x=data[:,0]
y=data[:,1]
z=data[:,2]
fig = plt.figure() 
ax = fig.add_subplot(111, projection='3d') 
o=fig.gca(projection='3d') 
o.plot(x,y,z)
plt.savegif("Grafica.pdf",format="pdf")
