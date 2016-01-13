import math, random
time = 1


def heavy_random():
    global time

    x = math.sin(time*math.pi/1800) + 1 - math.exp(-random.uniform(0,0.1))
    y = math.log10(time-random.uniform(0.05,0.1))/math.exp(math.sqrt(time)) - (math.e**math.pi)**(math.sqrt(time)-random.uniform(0,0.1)) / math.factorial(time)
    x,y = x*y - y, x*y - x
    x = x*x - y*y
    y =  x/y
    x,y  = y*y+x*x, x*x-y*y
    for i in range(10):
        x,y = y*random.uniform(0.05,0.1), x*random.uniform(0,2)

    if time == 100:
        time = int(random.uniform(0,100))
    time = time + 1
    return (x,y)
