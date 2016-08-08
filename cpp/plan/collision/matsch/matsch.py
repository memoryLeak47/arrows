#!/usr/bin/python3 -B

import sys

# vars

vx1 = 1
vx2 = 10

m1 = 1
m2 = 10

fi1 = 1
fi2 = 0

# vx

vx = ((vx1 * m1) + (vx2 * m2))/(m1 + m2)

print("vx=", vx)

# fs

fs1 = (fi1)/(fi1+fi2)
fs2 = (fi2)/(fi1+fi2)

print("fs1=", fs1)
print("fs2=", fs2)

# diff

diff1 = abs(vx1-vx)
diff2 = abs(vx2-vx)

print("diff1=", diff1)
print("diff2=", diff2)

# tmp

tmp1 = diff1 * m1 * fs1
tmp2 = diff2 * m2 * fs2

# res

res1 = -tmp1/(1+tmp1)
res2 = -tmp2/(1+tmp2)

# print

print("sizeincfactor1: " + str(res1))
print("sizeincfactor2: " + str(res2))
