import numpy as np
import pylab as pl

data = np.loadtxt('1e.txt')


#plot lambda as x axis and mix log model values as y axis

pl.plot(data[:,0],data[:,1],'ro')
pl.xlabel('lambda')
pl.ylabel('Mix model likelihood')

pl.show()