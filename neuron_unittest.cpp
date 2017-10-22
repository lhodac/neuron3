#include "neuron.hpp"
#include "gtest/include/gtest/gtest.h"
#include <iostream>
#include <cmath>



TEST (NeuronTest, membranePotential_) 
{
	Neuron neuron;
	
	//First update test
	neuron.update(0.0, 1.0);
	EXPECT_EQ(20.0*(1.0-std::exp(-0.1/20.0)),neuron.getMembranePotential());
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
