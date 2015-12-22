#!/bin/python
time = 1
import random,math
def circle():
    global time
    time = time + 1    
    arg = time*math.pi/48
    x,y = 0.5 + math.sin(arg)/4, 0.5 + math.cos(arg)/4
    
    return (x,y) 
    

    
 
