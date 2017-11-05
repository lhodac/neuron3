#ifndef CONSTANTS_H
#define CONSTANTS_H


constexpr int currentStep(0);
constexpr int nbSteps(1000);
constexpr double I_EXT(0.0);
 
constexpr double R(20);													///<Resistance membrane
constexpr double C(1);													///<Capacité membrane
constexpr double H(0.1);												///<Pas de temps (par step) = 0.0001s = 0.1ms
constexpr double TH_POTENTIAL(20);										///<"THRESHOLD POTENTIAL" Seuil de potentiel au dessus duquel on observe un pic
constexpr double DELAY(15);												///<Delai de transmission d'un signal à un autre neuron
constexpr double REFRACTORY_TIME(2);									///<Durée de temps sans activité après un pic --> 2 steps = 0.2ms
constexpr double J_EXCIT(0.1);											///<Courant que les neurons excitateurs transmettent
constexpr double J_INHIB(-0.5);											///<Courant que les neurons inhibiteurs transmettent
constexpr double E(0.1);												///<Rapport entre neurons excit et inhib
constexpr unsigned int NB_EXCIT(10000);									///<Nombre de neurones excitateurs
constexpr unsigned int ETA(2);

const unsigned int BUFFER_SIZE(DELAY+1);
const unsigned int NB_INHIB(0.25*NB_EXCIT);								///<Nombre de neurones inhibiteurs
const unsigned int NB_NEURONS(NB_EXCIT + NB_INHIB);						///<Nombre total de neurones
const unsigned int EXCIT_CONNEXIONS(E*NB_EXCIT);						///<Nombre de connexions excitatrices
const unsigned int INHIB_CONNEXIONS(E*NB_INHIB);						///<Nombre de connexions inhibitrice
const unsigned int TOTAL_CONNEXIONS(EXCIT_CONNEXIONS+INHIB_CONNEXIONS);	///<Nombre total de connexions

const double TAU(R*C);													///<Rapport capacité et résistance
const double C1 (exp(-H/TAU));											///<Constante pour la résolution de l'équa. diff.
const double C2 (1-C1);													///<Constante pour la résolution de l'équa. diff.
const double TH_NU(TH_POTENTIAL/(EXCIT_CONNEXIONS * J_EXCIT * TAU));	///<NuThreshold
const double EXT_NU(ETA * TH_NU);										///<Frequency factor for the background noise (poisson generator)

#endif
