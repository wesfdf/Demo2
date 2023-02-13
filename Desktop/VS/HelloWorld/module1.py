
import numpy as np
import matplotlib.pyplot as plt

lattice = np.loadtxt("lattice.txt")

plt.scatter(lattice[:, 0], lattice[:, 1], c=lattice[:,2])
#plt.scatter(lattice[:, 2], lattice[:, 3], c=lattice[:,2])
plt.xlabel("1st coordinate")
plt.ylabel("2nd coordinate")
plt.show()
#plt.scatter(lattice[:, 0], lattice[:, 1], c=lattice[:,2])
plt.scatter(lattice[:, 2], lattice[:, 3], c=lattice[:,0])
plt.xlabel("1st coordinate")
plt.ylabel("2nd coordinate")
plt.show()
