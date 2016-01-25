time = 0
time_step = 0.1
vx, vy = 5 , 0
x,y = 0 , 0
acc_x, acc_y = 0, 0
noice = 1
radius = 10
v_static = 5
import random,math
def circle_acc():
	global time, vx, vy, x, y, acc_x, acc_y, noice, radius
	V = math.sqrt(vx**2 + vy**2)
	A = (vx**2 + vy**2)/radius
	print vx, vy, acc_x, acc_y, x, y
	if vy == 0:
		acc_x = 0
		acc_y = A
		if vx < 0:
			acc_y = -1 * acc_y
	else:
		tn_alpha = vx/vy
		acc_x = A / math.sqrt(tn_alpha**2 + 1)
		if vy > 0:
			acc_x = -1 * acc_x
		acc_y = -tn_alpha * acc_x
	if (vy > 0) and (V > v_static + 0.5 or V < v_static - 0.5):
		dV = V - v_static
		dvy = dV**2 / math.sqrt((vx/vy)**2 + 1)
		if vy < 0:
			dvy = -dvy
		dvx = vx/vy * dvy
		acc_x = acc_x -dvx*time_step;
		acc_y = acc_y - dvy*time_step;
	print vx, vy, acc_x, acc_y, x, y	
	ax = acc_x + random.uniform(-1 * noice, noice)
	ay = acc_y + random.uniform(-1 * noice, noice)
	x =  x + time_step * vx + time_step*time_step/2 * ax
	y =  y + time_step * vy + time_step*time_step/2 * ay	
	vx = vx + time_step * ax
	vy = vy + time_step * ay
	time = time + time_step
	return (x,y,acc_x,acc_y)