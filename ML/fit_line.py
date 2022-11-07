# Linear solver
from cmath import sqrt
from tkinter import RIGHT

def my_linfit(x,y):
    x_mean = x.mean()
    y_mean = y.mean()
    b_osoittaja = (((x - x_mean) * (y - y_mean)).sum())
    b_nimittaja = ((x - x_mean)**2).sum()

    b = (b_osoittaja / b_nimittaja)
    a = y_mean - (b * x_mean)

    return a, b

def on_click(event):
    if event.button is MouseButton.LEFT:
        x_crd = event.xdata
        y_crd = event.ydata
        if x_crd != -30 and y_crd != -30:
            x_list.append(x_crd)
            y_list.append(y_crd)
            with plt.ion():
                plt.plot(x_crd, y_crd, 'kx')

    elif event.button is MouseButton.RIGHT:
        x = np.array(x_list)
        y = np.array(y_list)
        a , b = my_linfit(x, y)
        # Plotting the regression line
        with plt.ion():
            plt.plot(x, x*b + a)
            
        


# Main
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.backend_bases import MouseButton
x_list = []
y_list = []

# activate data collecting from mouse clicks
plt.connect('button_press_event', on_click)

#Initialize axis and the coordinate system
plt.axis([0,30,0,30])
plt.show()
