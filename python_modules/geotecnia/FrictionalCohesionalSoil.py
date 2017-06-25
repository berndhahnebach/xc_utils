# -*- coding: utf-8 -*-
from __future__ import division
import math
import FrictionalSoil as fs
from miscUtils import LogMessages as lmsg

'''FrictionalCohesionalSoil.py: soil with friction and cohesion soil model.

References: 

[1] Chapter 4-3 of Foundation Analysis and Design, Ed. 5 by Joseph E. Bowles.
[2] Brinch Hansen. A general formula for bearing capacity. The Danish Geotechnical Institute. Bulletin 11. Copenhagen 1961.
[3] Guía de cimentaciones en obras de carretera. Ministerio de Fomento (spain). 2002.
'''

__author__= "Luis C. Pérez Tato (LCPT)"
__copyright__= "Copyright 2016, LCPT"
__license__= "GPL"
__version__= "3.0"
__email__= "l.pereztato@gmail.com"

class FrictionalCohesionalSoil(fs.FrictionalSoil):
  '''Soil with friction and cohesion

  :ivar c:    soil cohesion
  '''
  def __init__(self,phi,c,rho= 2100.0,gammaMPhi= 1.0,gammaMc= 1.0):
    '''Constructor.

        Args:
            :c: (float) soil cohesion.
            :gammaMc: (float) partial reduction factor for soil cohesion.
    '''
    super(FrictionalCohesionalSoil,self).__init__(phi,rho)
    self.c= c
    self.gammaMc= gammaMc
    
  def getDesignC(self):
    '''Return the design value of the soil cohesion.'''
    return self.c/self.gammaMc
  def sq(self,Beff,Leff):
    '''Factor that introduces the effect of foundation shape on
       the overburden component.

       :param Beff: Width of the effective foundation area
                    (see figure 12 in page 44 of reference[2]).
       :param Leff: Length of the effective foundation area
                    (see figure 12 in page 44 of reference[2]).
    '''
    return 1.0+Beff/Leff*self.Nq()/self.Nc()

  def iq(self,deltaB,deltaL):
    '''Factor that introduces the effect of load inclination on
       the overburden component.

    :param deltaB: angle between the load and the foundation width
                   atan(HloadB/VLoad).
    :param deltaL: angle between the load and the foundation length
                   atan(HloadL/VLoad). 
    '''
    return (1.0-0.7*math.tan(deltaB))**3*(1.0-math.tan(deltaL))

  def dq(self,D,Beff):
    '''Overburden factor for foundation depth.

       :param D: foundation depth.
       :param Beff: Width of the effective foundation area
                    (see figure 12 in page 44 of reference[2]).
    '''
    k= min(D,2.0*Beff)/Beff
    return 1+2*math.tan(self.getDesignPhi())*(1-math.sin(self.getDesignPhi()))**2*math.atan(k)

  def tq(self,psi= 0.0):
    '''Factor that introduces the effect of the proximity of an slope.

       :param psi: angle of the line on wich the q load acts 
                   (see figure 4.7 in page 102 of reference [3])
                   must be determined by iterations.
    '''
    return (1-0.5*math.tan(psi))**5

  def rq(self,eta= 0.0):
    '''Factor that introduces the effect of sloped footing.

       :param eta: angle between the foundation plane with and the 
                   (see figure 4.8 in page 104 of reference [3])
                   favourable effect when eta<0.0.
    '''
    if(self.getDesignPhi()!=0):
      return math.exp(-2*eta*math.tan(self.getDesignPhi()))
    else:
      return 1.0
  
  def Nq(self):
    '''Returns the overburden multiplier for the Brinch-Hasen formula.'''
    return self.Kp()*math.exp(math.pi*math.tan(self.getDesignPhi()))

  def sc(self,Beff,Leff):
    '''Factor that introduces the effect of foundation shape on
       the cohesion component.

    :param Beff: Width of the effective foundation area
                (see figure 12 in page 44 of reference[2]).
    :param Leff: Length of the effective foundation area
                (see figure 12 in page 44 of reference[2]).
    '''
    return self.sq(Beff,Leff)

  def ic(self,deltaB,deltaL,Hload,Beff,Leff):
    '''Factor that introduces the effect of load inclination on
       the cohesion component.

    :param deltaB: angle between the load and the foundation width
                   atan(HloadB/VLoad).
    :param deltaL: angle between the load and the foundation length
                   atan(HloadL/VLoad).
    :param Hload: Horizontal load. 
    :param Beff: Width of the effective foundation area
                 (see figure 12 in page 44 of reference[2]).
    :param Leff: Length of the effective foundation area
                (see figure 12 in page 44 of reference[2]).
    '''
    if(self.getDesignPhi()!=0.0):
      iq= self.iq(deltaB,deltaL)
      return (iq*self.Nq()-1.0)/(self.Nq()-1.0)
    else: #See expresion (15) in reference [2]
      resist= Beff*Leff*self.getDesignC()
      if(Hload<=resist):
        twoAlpha= math.acos(Hload/resist)
        return 0.5+(twoAlpha+math.sin(twoAlpha))/(math.pi+2.0)
      else:
        lmsg.warning('Load (H= '+str(Hload)+') greater than soil strength R='+str(resist)+' returns 0.0')
        return 0.0

  def dc(self,D,Beff):
    '''Depth factor for cohesion.

       :param D: foundation depth.
       :param Beff: Width of the effective foundation area
                    (see figure 12 in page 44 of reference[2]).
    '''
    k= min(D,2.0*Beff)/Beff
    return 1+2*self.Nq()/self.Nc()*(1-math.sin(self.getDesignPhi()))**2*math.atan(k)
  
  def tc(self,psi= 0.0):
    '''Factor that introduces the effect of the proximity of an slope.

       :param psi: angle of the line on wich the q load acts 
                   (see figure 4.7 in page 102 of reference [3])
                   must be determined by iterations.
    '''
    if(self.getDesignPhi()!=0.0):
      return (self.tq(psi)*self.Nq()-1.0)/(self.Nq()-1.0)
    else:
      return 1-0.4*psi

  def rc(self,eta= 0.0):
    '''Factor that introduces the effect of sloped footing.

       :param eta: angle between the foundation plane with and the 
                   (see figure 4.8 in page 104 of reference [3])
                   favourable effect when eta<0.0.
    '''
    if(self.getDesignPhi()!=0.0):
      return (self.rq(eta)*self.Nq()-1.0)/(self.Nq()-1.0)
    else:
      return 1-0.4*eta

  def Nc(self):
    '''Returns the cohesion multiplier for the Brinch-Hasen formula.'''
    if(self.getDesignPhi()!=0.0):
      return (self.Nq()-1.0)*(1.0/math.tan(self.getDesignPhi()))
    else:
      return math.pi+2.0
                                                         
  def sgamma(self,Beff,Leff):
    '''Factor that introduces the effect of foundation shape on
       the self weight component.

       :param Beff: Width of the effective foundation area
                    (see figure 12 in page 44 of reference[2]).
       :param Leff: Length of the effective foundation area
                    (see figure 12 in page 44 of reference[2]).
    '''
    return 1.0-0.3*Beff/Leff

  def igamma(self,deltaB,deltaL):
    '''Factor that introduces the effect of load inclination on
       the self weight component.

    :param deltaB: angle between the load and the foundation width
                   atan(HloadB/VLoad).
    :param deltaL: angle between the load and the foundation length
                   atan(HloadL/VLoad). 
    '''
    return (1-math.tan(deltaB))**3*(1-math.tan(deltaL))

  def dgamma(self):
    '''Factor that introduces the effect of foundation depth on
       the self weight component.'''
    return 1.0

  def tgamma(self,psi= 0.0):
    '''Factor that introduces the effect of the proximity of an slope.

       :param psi: angle of the line on wich the q load acts 
                   (see figure 4.7 in page 102 of reference [3])
                   must be determined by iterations.
    '''
    return self.tq(psi)

  def rgamma(self,eta= 0.0):
    '''Factor that introduces the effect of sloped footing.

       :param eta: angle between the foundation plane with and the 
                   (see figure 4.8 in page 104 of reference [3])
                   favourable effect when eta<0.0.
    '''
    return self.rq(eta)

  def Ngamma(self,NgammaCoef= 1.5):
    '''Returns the wedge weight multiplier for the Brinch-Hasen formula.

       :param NgammaCoef: 1.5 in reference [1], 1.8 in reference 2 
                          and 2 in reference 3
    '''
    return NgammaCoef*(self.Nq()-1.0)*math.tan(self.getDesignPhi())

  def quGamma(self,D,Beff,Leff,Vload,HloadB,HloadL,NgammaCoef= 1.5,psi= 0.0,eta= 0.0):
    '''Gamma "component" of the ultimate bearing capacity pressure of the soil.

    :param D: foundation depth.
    :param Beff: Width of the effective foundation area
                 (see figure 12 in page 44 of reference[2]).
    :param Leff: Length of the effective foundation area
                 (see figure 12 in page 44 of reference[2]).
    :param Vload: Vertical load. 
    :param HloadB: Horizontal load on Beff direction. 
    :param HloadL: Horizontal load on Leff direction. 
    :param NgammaCoef: 1.5 in reference [1], 1.8 in reference 2 
                       and 2 in reference 3
    :param psi: angle of the line on wich the q load acts 
                (see figure 4.7 in page 102 of reference [3])
                must be determined by iterations.
    '''
    deltaB= math.atan(HloadB/Vload)
    deltaL= math.atan(HloadL/Vload)
    return 0.5*self.gamma()*Beff*self.Ngamma(NgammaCoef)*self.dgamma()*self.igamma(deltaB,deltaL)*self.sgamma(Beff,Leff)*self.tgamma(psi)*self.rgamma(eta)

  def quCohesion(self,D,Beff,Leff,Vload,HloadB,HloadL,psi= 0.0,eta= 0.0):
    '''Cohesion "component" of the ultimate bearing capacity pressure of the soil.

    :param D: foundation depth.
    :param Beff: Width of the effective foundation area
                 (see figure 12 in page 44 of reference[2]).
    :param Leff: Length of the effective foundation area
                 (see figure 12 in page 44 of reference[2]).
    :param Vload: Vertical load. 
    :param HloadB: Horizontal load on Beff direction. 
    :param HloadL: Horizontal load on Leff direction. 
    :param NgammaCoef: 1.5 in reference [1], 1.8 in reference 2 
                       and 2 in reference 3
    :param psi: angle of the line on wich the q load acts 
                (see figure 4.7 in page 102 of reference [3])
                must be determined by iterations.
    '''
    deltaB= math.atan(HloadB/Vload)
    deltaL= math.atan(HloadL/Vload)
    Hload= math.sqrt(HloadB**2+HloadL**2)
    return self.getDesignC()*self.Nc()*self.dc(D,Beff)*self.ic(deltaB,deltaL,Hload,Beff,Leff)*self.sc(Beff,Leff)*self.tc(psi)*self.rc(eta)

  def quQ(self,q,D,Beff,Leff,Vload,HloadB,HloadL,psi= 0.0,eta= 0.0):
    '''Overburden "component of the ultimate bearing capacity pressure of the soil.

    :param D: foundation depth.
    :param Beff: Width of the effective foundation area
                 (see figure 12 in page 44 of reference[2]).
    :param Leff: Length of the effective foundation area
                 (see figure 12 in page 44 of reference[2]).
    :param Vload: Vertical load. 
    :param HloadB: Horizontal load on Beff direction. 
    :param HloadL: Horizontal load on Leff direction. 
    :param NgammaCoef: 1.5 in reference [1], 1.8 in reference 2 
                       and 2 in reference 3
    :param psi: angle of the line on wich the q load acts 
                (see figure 4.7 in page 102 of reference [3])
                must be determined by iterations.
    '''
    deltaB= math.atan(HloadB/Vload)
    deltaL= math.atan(HloadL/Vload)
    return q*self.Nq()*self.dq(D,Beff)*self.iq(deltaB,deltaL)*self.sq(Beff,Leff)*self.tq(psi)*self.rq(eta)

  def qu(self,q,D,Beff,Leff,Vload,HloadB,HloadL,NgammaCoef= 1.5,psi= 0.0,eta= 0.0):
    '''Ultimate bearing capacity pressure of the soil.

    :param D: foundation depth.
    :param Beff: Width of the effective foundation area
                 (see figure 12 in page 44 of reference[2]).
    :param Leff: Length of the effective foundation area
                 (see figure 12 in page 44 of reference[2]).
    :param Vload: Vertical load. 
    :param HloadB: Horizontal load on Beff direction. 
    :param HloadL: Horizontal load on Leff direction. 
    :param NgammaCoef: 1.5 in reference [1], 1.8 in reference 2 
                       and 2 in reference 3
    :param psi: angle of the line on wich the q load acts 
                (see figure 4.7 in page 102 of reference [3])
                must be determined by iterations.
    '''
    deltaB= math.atan(HloadB/Vload)
    deltaL= math.atan(HloadL/Vload)
    Hload= math.sqrt(HloadB**2+HloadL**2)
    gammaComp= self.quGamma(D,Beff,Leff,Vload,HloadB,HloadL,NgammaCoef,psi,eta)
    cComp= self.quCohesion(D,Beff,Leff,Vload,HloadB,HloadL,psi,eta)
    qComp= self.quQ(q,D,Beff,Leff,Vload,HloadB,HloadL,psi,eta)
    return gammaComp+cComp+qComp
