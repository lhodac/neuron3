#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <cmath>

//CONSTANTES NEURONE
constexpr double R(20);
constexpr double TAU(20);
constexpr double H(1); //1ms
constexpr double TH_POTENTIAL(20);
constexpr unsigned int DELAY(10);
//constexpr double REFRACTORY_TIME(0.001);Inutile car 1 passage dans la boucle du main correspond a ce temps.


class Neuron {
	
private:
		
	double membranePotential_;
	double nbSpikes_;
	bool refractory_;
	std::vector<double> spikeTimes_;
	std::array<double,(DELAY+1)> buffer;
	

public:
	double getMembranePotential() const;
	double getNbSpikes() const;
	std::vector<double> getTimeSpikes() const;
	bool isRefractory() const;


	
	void setMembranePotential(double potential);
	void setNbSpikes(double nb);
	void setRefractory(bool r);


	bool update(double simtime, double I_ext);
	void addTimeSpike(double time);
	double solveDifferentialEquation(double I_ext) const;
	double updateBuffer();
	void receive(double simtime,double J);

	
	Neuron();
	~Neuron();
	
	
	};




#endif
