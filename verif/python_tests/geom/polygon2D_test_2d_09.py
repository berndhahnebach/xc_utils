# -*- coding: utf-8 -*-
import xc_base
import geom
pol1=geom.Poligono2d()
pol2=geom.Poligono2d()
pol3=geom.Poligono2d()

pList= geom.polygon_2D_list()
pList.append(pol1)
pList.append(pol2)
pList.append(pol3)

# for p in pList:
#   print p.getArea()

ratio= len(pList)-3

import os
fname= os.path.basename(__file__)
if(abs(ratio)<1e-10):
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."