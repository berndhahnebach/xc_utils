# -*- coding: utf-8 -*-

import xc_base
import loadCombinations

coefs_psi_EHE= loadCombinations.PsiCoeffsDict()

coefs_psi_EHE.insert("permanente",loadCombinations.PsiCoeffs(1,1,1))
coefs_psi_EHE.insert("nieve",loadCombinations.PsiCoeffs(0.6,0.2,0.0))
coefs_psi_EHE.insert("viento",loadCombinations.PsiCoeffs(0.6,0.5,0.0))
coefs_psi_EHE.insert("term",loadCombinations.PsiCoeffs(0.6,0.5,0.0))
coefs_psi_EHE.insert("sismo",loadCombinations.PsiCoeffs(0,0,0))
coefs_psi_EHE.insert("azotea_solo_conserv",loadCombinations.PsiCoeffs(0.7,0.5,0.3))
coefs_psi_EHE.insert("vivienda",loadCombinations.PsiCoeffs(0.7,0.5,0.3))
coefs_psi_EHE.insert("dormitorios_hotel",loadCombinations.PsiCoeffs(0.7,0.5,0.3))
coefs_psi_EHE.insert("pasillos_escaleras_hotel",loadCombinations.PsiCoeffs(0.7,0.7,0.6))
coefs_psi_EHE.insert("salones_hotel",loadCombinations.PsiCoeffs(0.7,0.7,0.6))
coefs_psi_EHE.insert("aulas_escuela",loadCombinations.PsiCoeffs(0.7,0.7,0.6))
coefs_psi_EHE.insert("pasillos_escaleras_escuela",loadCombinations.PsiCoeffs(0.7,0.7,0.6))
#Coeficientes de ponderación para acciones permanentes, control de ejecución normal.
gammaf_permanentes_EHE_ctr_normal= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1.35,1,1),loadCombinations.GammaFELS(1,1))

#Coeficientes de ponderación para acciones permanentes de valor no constante, control de ejecución normal.
gammaf_permanentes_nc_EHE_ctr_normal= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1.5,1,1),loadCombinations.GammaFELS(1,1))
#Coeficientes de ponderación para acciones variables, control de ejecución normal.
gammaf_variables_EHE_ctr_normal= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1.5,0,1),loadCombinations.GammaFELS(0,1))
#Coeficientes de ponderación para acciones sísmicas, control de ejecución normal.
gammaf_sismicas_EHE_ctr_normal= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1,1,1),loadCombinations.GammaFELS(0,0))
#Coeficientes de ponderación para acciones accidentales, control de ejecución normal.
gammaf_accidentales_EHE_ctr_normal= loadCombinations.GammaF(loadCombinations.GammaFELU(0,0,1,1),loadCombinations.GammaFELS(0,0))
#Coeficientes de ponderación para acciones permanentes, control de ejecución intenso.
gammaf_permanentes_EHE_ctr_intenso= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1.35,1,1),loadCombinations.GammaFELS(1,1))

#Coeficientes de ponderación para acciones permanentes de valor no constante, control de ejecución intenso.
gammaf_permanentes_nc_EHE_ctr_intenso= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1.5,1,1),loadCombinations.GammaFELS(1,1))
#Coeficientes de ponderación para acciones variables, control de ejecución intenso.
gammaf_variables_EHE_ctr_intenso= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1.5,0,1),loadCombinations.GammaFELS(0,1))
#Coeficientes de ponderación para acciones sísmicas, control de ejecución intenso.
gammaf_sismicas_EHE_ctr_intenso= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1,1,1),loadCombinations.GammaFELS(0,0))
#Coeficientes de ponderación para acciones accidentales, control de ejecución intenso.
gammaf_accidentales_EHE_ctr_intenso= loadCombinations.GammaF(loadCombinations.GammaFELU(0,0,1,1),loadCombinations.GammaFELS(0,0))

intenseControlCombGenerator= loadCombinations.LoadCombGenerator()
pond= intenseControlCombGenerator.defPonderacion("EHEIntenso",coefs_psi_EHE)
pond.permanentActions.gammaF= gammaf_permanentes_EHE_ctr_intenso
pond.variableActions.gammaF= gammaf_variables_EHE_ctr_intenso
pond.accidentalActions.gammaF= gammaf_accidentales_EHE_ctr_intenso
pond.seismicActions.gammaF= gammaf_sismicas_EHE_ctr_intenso