#!/usr/bin/python3 -B

import sys

class Error: pass
E=Error()

def die(msg):
	print("ERROR: " + msg)
	sys.exit(1)
