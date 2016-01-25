time = 0
time_step = 0.1
vx, vy = 0 , 0
x,y = 0 , 0
acc_x, acc_y = 1, 0
noice = 1
import random,math
def standard_acc():
	global time, vx, vy, x, y, acc_x, acc_y, noice
	ax = acc_x + random.uniform(-1 * noice, noice)
	ay = acc_y
	x =  x + time_step * vx + time_step*time_step/2 * ax
	y =  y + time_step * vy + time_step*time_step/2 * ay	
	vx = vx + time_step * ax
	vy = vy + time_step * ay
	time = time + time_step
	return (x,y,acc_x,acc_y)

