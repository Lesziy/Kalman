time = 0
time_step = 0.1
vx, vy = 2 , 0
x,y = 0 , 0
acc_x, acc_y = 0, 0
noice = 2

maxX = 40
Vx1 = 2
Vx2 = -30
acc = 20

import random,math
def saw_signal_acc_v1():
	global time, vx, vy, x, y, acc_x, acc_y

	if x > maxX:  
		acc_x = -acc
	elif x < 0:
		acc_x = acc
		
	if acc_x < 0 and vx < Vx2:
		acc_x = 0
	elif acc_x > 0 and vx > Vx1:
		acc_x = 0;
		
	ax = acc_x + random.uniform(-1 * noice, noice)
	ay = acc_y
	x =  x + time_step * vx + time_step*time_step/2 * ax
	y =  y + time_step * vy + time_step*time_step/2 * ay	
	vx = vx + time_step * ax
	vy = vy + time_step * ay
	time = time + time_step
	print x, y, vx, vy
	
	return (x,y,0,0)