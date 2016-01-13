#!/bin/python
time = 1
import random,math

def r(t):
    return 1/4 + (math.exp(-t/123))/4

def circle2():
    global time
    time = time + 1    
    arg = time*math.pi/48
    x,y = 0.5 + math.sin(arg)*r(time), 0.5 + math.cos(arg)*r(time)
    
    return (x,y) 
    

    
 
