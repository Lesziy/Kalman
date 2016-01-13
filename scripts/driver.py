#!/bin/python
# -*- coding: UTF-8 -*-
import sys, os, time, math
#import numpy as np
import matplotlib
matplotlib.use('WXAgg') 
import matplotlib.pyplot as plt

fname = ''
ok = 1

# Dodaje główny folder projektu do path, przez co możemy importować mapy.
sys.path.insert(1, os.path.join(sys.path[0], '..'))

try:
    fname = sys.argv[1]
    exec('from maps.' + fname + ' import ' + fname)
except:
    print('Import: ' + 'from maps.' + fname + ' import ' + fname + ' failed!')
    sys.exit(1)

plt.axis([0,1,0,1])
plt.ion()
plt.show()
time = 0

while ok:
    time = time + 1
    clr = math.fabs(math.sin(time*math.pi/12))
    #time.sleep(0.05)
    plt.pause(10 ** -15)
    ret = eval(fname + '()')
    print(ret)
    plt.scatter(ret[1], ret[0],c=[clr, clr, clr])
    plt.draw()
