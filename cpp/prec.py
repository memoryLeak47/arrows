#!/usr/bin/python3 -B

import sys
import glob
import string

sys.path.append(sys.path[0] + "/pybase")
from std import *
from walk import *
from main import *

assert(len(sys.argv) == 2)
dir = sys.argv[1].strip("/") + "/"

files = Files()
# add code here

# 
files.writeback()
