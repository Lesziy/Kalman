time = 0
time_step = 0.1
vx, vy = 0 , 0
x,y = 10 , 0
acc_x, acc_y = 0, 0
noice = 2
radius = 5
v_static = 5
x_max = 500
y_max = 500
import random,math

class Move:
	Left = 1
	Right = 2
	Stright = 3

status = Move.Stright
phase_time = 1
max_phase_time = 4

def robo_acc():
	global time, vx, vy, x, y, acc_x, acc_y, noice, radius, status, phase_time, max_phase_time
	acc_x = 0
	acc_y = 0
	if phase_time <= 0:
		status = random.randint(1, 3)
		phase_time = random.uniform(max_phase_time/2, max_phase_time)
		#print status

	if status != Move.Stright:
		turn()
	#turn()
	hamowanie()
	
	ax = acc_x + random.uniform(-1 * noice, noice)
	ay = acc_y + random.uniform(-1 * noice, noice)
	x =  x + time_step * vx + time_step*time_step/2 * ax
	y =  y + time_step * vy + time_step*time_step/2 * ay	
	vx = vx + time_step * ax
	vy = vy + time_step * ay
	

	odbicie()
	time = time + time_step
	phase_time = phase_time - time_step
	#print x, y
	return (x,y,acc_x,acc_y)
	
def odbicie():
	global x, y, x_max, y_max, vx, vy
	if (x < -x_max):
		x = -x_max
		if(vx <= 0):
			vx = -vx
	elif (x > x_max):
		vx = -vx
		if(vx >= 0):
			x = x_max
			
	if (y < -x_max):
		y = -x_max
		if(vy <= 0):
			vy = -vy
	elif (y > y_max):
		vy = -vy
		if(vy >= 0):
			y = y_max
	
def hamowanie():

	global  vx, vy, acc_x, acc_y, v_static, time_step
	V = math.sqrt(vx**2 + vy**2)
	if (V > v_static + 0.5):
		dV = V - v_static
		if ( vy != 0 ):
			dvy = dV**2 / math.sqrt((vx/vy)**2 + 1)
			if vy < 0:
				dvy = -dvy
			dvx = vx/vy * dvy
		else:
			if vx < 0:
				dvx = -dV
			else:
				dvx = dV
			
		acc_x = acc_x - dvx/time_step;
		acc_y = acc_y - dvy/time_step;
			
def turn( ):
	global time, vx, vy, x, y, acc_x, acc_y, noice, radius
	#print vx, vy, acc_x, acc_y
	A = (vx**2 + vy**2)/radius
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
	if status == Move.Right :
		acc_x = -acc_x
		acc_y = -acc_y

#for i in range(0,20):
	#robo_acc()