#!/usr/bin/env python

import sys

class Body:
	def __init__(self, pos, size, speed):
		self.positionX, self.positionY = pos
		self.sizeX, self.sizeY = size
		self.speedX, self.speedY = speed

	def getIt(self, body):
		minCT = max(	((body.positionX - body.sizeX/float(2)) - (self.positionX + self.sizeX/float(2)))/float(self.speedX),
				((body.positionY - body.sizeY/float(2)) - (self.positionY + self.sizeY/float(2)))/float(self.speedY))

		maxCT = min(	((body.positionX + body.sizeX/float(2)) - (self.positionX - self.sizeX/float(2)))/float(self.speedX),
				((body.positionY + body.sizeY/float(2)) - (self.positionY - self.sizeY/float(2)))/float(self.speedY))
		if minCT > maxCT:
			print("NOPE")
			sys.exit()
		return minCT

body1 = Body((2, 2), (1, 1), (1, 1))
body2 = Body((4, 4), (1, 1), (0, 0))
print(body1.getIt(body2))
