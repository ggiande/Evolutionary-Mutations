#!/usr/bin/env python
# coding: utf-8
import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.animation as ani
import numpy as np
import pandas as pd     #Pandas reads files
import csv
import colorsys
import os

file_name_for_images = os.path.realpath("images")
x = []
with open("test.csv", "r" ) as f:
    a = [ [ int(dummy) for dummy in line.split() ] for line in f.readlines()] 
with open("make.csv", "r") as g:
    b = [[int(dummy) for dummy in line.split() ] for line in g.readlines()]
    num_ancestors = b[0][0]
    LX = b[0][1]
    LY  = b [0][2]
print("The number of ancestors is: " + str(num_ancestors) + " ,the LX is: " + str(LX) + " ,and the LY is: " + str(LY))

MAX = int((LX * LY)*.85) #This will act as TEND FROM NOW ON.
#MAX = int(LX * LY) #Go to 80-90% of when it is filled up.

#bg to run a command in the background and fg to return to the process.
#control + c to exit the keyboard.

#Using the file, the 2d array was initiated, then filled.
num_ancestors = max([ dummy[2] for dummy in a]) + 1
#print (num_ancestors)

p = [None for i in range(0, max([dummy[3] for dummy in a])+1)]
for j in range (0, len(a)): #Make an array that's as empty as it needs to be. 0 - max of length of what I need, including zero, not max
    g = a[j] #Grab the lines of the array
    h = g[3] #looking at the column and saving it
    p[h] = g #setting the column to the location in the new array
    #g=[x,y,label,t, motherx,smothery]

# Fleshing out the x and y values from the ordered list.
# Here is where I noticed that the past code was creating NONE values in the 2array p. I am still debugging as to why that is. I believe that it may be that none is created every time that the index is looking at the exact value where it is trying to move. For instance, 
# g = a[j] when placing in p[h] = g, if the value 2444 is j and is by chance in the correct place already, None is just placed in p.
# ## Add the 2 missing 0 values to the p array from a.
# Read in {x, y, label, t, motherx, mothery.


plt.figure(figsize = (15, 15))
#print("Note that the saving of images will be out of order.")
#q = MAX # Number of images that will be saved.
#print("This will take a while :/ ")
sim = [ [ [1.,1.,1.] for j in range(0, LX) ] for i in range (0,LY) ]
for i in range(len(a)):
    x = a[i][0]
    y = a[i][1]
    #xflipped = 50 - 1 - x      
    yflipped = LY - 1 - y #Flipping to match the style of mathematica
    
    label = a[i][2]
    time = a[i][3] #If use p, then I will be able to use time as the counter
    #print(time)

    if(time <= MAX):
        rgb = colorsys.hsv_to_rgb(label/num_ancestors, 1 ,1) #(hsv)
        sim[yflipped][x] = rgb

    if(label == -1 and time <= MAX):
        sim[yflipped][x] = [1.,1.,1.]
          
    #if(time <= q):
     #   os.chdir(file_name_for_images)
      #  print("Saving image... " + str(time) + " of " + str(q))
       # plt.imsave('test' + str(time) + '.png', sim, dpi=1000) 
        

#red =1 , 0 = blue ,-1  -white
#sim = [ [ [1.,1.,1.] for j in range(0, 50) ] for i in range (0,50) ]
    
plt.imshow(sim)
plt.waitforbuttonpress() 
#print("Done executing the program.")

# Beneficial Factors
# ### 1. Initial Conditions - Ancestors should be an entire column
# ### 2.  Change Lx
# Well Mixed
# 
# Cell Death
# ### 5. Different fitnesses/Birth Rates -- Gilespie Algorithm (what the mutations look like.)
# ### Model Antibiotics and Concentrations

# Only do lineages of the ones at the front. 
# def arbitrary - Based on a random whim.


# 1. INIT cord

# 3. diff birth rates
# 4. anitbiotic swap birth rates in right half.




