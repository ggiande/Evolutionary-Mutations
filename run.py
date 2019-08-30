#!/usr/bin/env python
# coding: utf-8
Z = 100
for i in range(100, 6000, Z):	#Skips iteration by 100 until 6000. 60 times.
	print(i)
	print(" ")
	for k in range(2,10):
		print("K: " + str(k))
		print("I: " + str(i))

