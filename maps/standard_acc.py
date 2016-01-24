time = 0
vx, vy = 0 , 0
x,y = 0 , 0
acc_x, acc_y = 1, 0
noice = 1
import random,math
def standard_acc():
	global time, vx, vy, x, y, acc_x, acc_y, noice
	ax = acc_x + random.uniform(-1 * noice, noice)
	ay = acc_y
	x =  x + time * vx + time*time/2 * ax
	y =  y + time * vy + time*time/2 * ay	
	vx = vx + time * ax
	vy = vy + time * ay
	time = time + 0.1
	return (x,y,acc_x,acc_y)

