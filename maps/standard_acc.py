time = 1
vx, vy = 0 , 0
x,y = 0 , 0
acc_x, acc_y = 0.1, 0.1
noice = 0.1
import random,math
def standard_acc():
	global time, vx, vy, x, y, acc_x, acc_y
	ax = acc_x + random.uniform(0, 0.04)
	ay = acc_y + random.uniform(0, 0.04)
	x =  x + time * vx + time*time/2 * ax
	y =  y + time * vy + time*time/2 * ay	
	x = vx + time * ax
	vy = vy + time * ay
	time = time + 1
	return (x,y,ax,ay)
	
print standard_acc();
