# -*- coding: utf-8 -*-

import xc_base
import geom
pos1= geom.Pos3d(1,2,3);

xPt= pos1.x
yPt= pos1.y
zPt= pos1.z

#print("pos1.x= ",pos1.x," pos1.y= ",pos1.y," pos1.z= ",pos1.z)

import os
fname= os.path.basename(__file__)
if(xPt==1. and yPt==2. and zPt==3.):
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."
