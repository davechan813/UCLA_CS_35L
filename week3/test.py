#!/usr/bin/python
import random, sys, locale
from optparse import OptionParser

parser = OptionParser()
options, args = parser.parse_args(sys.argv[1:])  

file1 = args[0]
file2 = args[1]


lines1 = []
if file1 != '-':
	with open(file1) as f1:
		lines1 = f1.readlines()
else:	
	for line in sys.stdin:
		lines1.append(line)
lines1 = [x.strip() for x in lines1] 

lines2 = []
if file2 != '-':
	with open(file2) as f2:
		lines2 = f2.readlines()
		lines2 = [x.strip() for x in lines2] 
else:
	for line2 in sys.stdin:
		lines2.append(line2)
lines2 = [x.strip() for x in lines2] 			


def isSorted():
	for i in range(0, len(lines1) - 1):
		if lines1[i] > lines1[i+1]:
			print lines1[i] + " > " + lines1[i + 1]
			return False

	return True



print lines1
print lines2