#ifndef NETWORK_H
#define NETWORK_H
#include <iostream>
#include <vector>
#include "neuron.hpp"

constexpr double J(10.0);


class Network{
	
private:

	std::vector<Neuron*> neurons_;
	bool spike_;

public:
	Neuron getNeuron(int n);
	void reset();
	void update(double simtime, double I_ext);
	Network(std::vector<Neuron*> neurons);
	~Network();
	
	
	
	
	};
#endif

