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
constexpr double H(0.01); //1ms
constexpr double TH_POTENTIAL(20);
constexpr unsigned int DELAY(10);
constexpr double REFRACTORY_TIME(0.02);

class Neuron {
	
private:
		
	double membranePotential_;
	double nbSpikes_;
	bool refractory_;
	double refractoryTime_;
	std::vector<double> spikeTimes_;
	std::array<double,(DELAY+1)> buffer_;
	std:: vector<Neuron*> postNeurons_;
	

public:
	double getMembranePotential() const;
	double getNbSpikes() const;
	std::vector<double> getTimeSpikes() const;
	std::vector<Neuron*> getPostNeurons() const;
	bool isRefractory() const;


	
	void setMembranePotential(double potential);
	void setNbSpikes(double nb);
	void setRefractory(bool r);


	bool update(int currentStep, double I_ext);
	void addTimeSpike(double time);
	void addPostNeuron(Neuron n);
	double solveDifferentialEquation(double I_ext) const;
	double updateBuffer();
	void receive(int currentStep,double J);

	
	Neuron();
	~Neuron();
	
	
	};




#endif
