#include "Network.hpp"


using namespace std;

int main()
{	
	Neuron neuron1;
	Neuron neuron2;
	Neuron neuron3;
	
	Network network;
	
	network.addNeuron(neuron1);
	network.addNeuron(neuron2);
	network.addNeuron(neuron3);
	
	neuron1.addPostNeuron(neuron3);
	
	
	int currentStep(0.0);
	int nbSteps(1000);
	double I_ext(1.01);
	
	//Ask the user wich current and simulation time he wants
	/*cout << "Enter the number of steps: (1step is 1ms)" << endl;
	double nbSteps(0.0);
	cin >> nbSteps;
	if (nbSteps < 0.0){cout << "ERROR: steps number has to be a positive value.";}
	
	cout << "Enter a External Current: " << endl;
	double I_ext(0.0);
	cin >> I_ext;*/
	
	ofstream sortie;
	sortie.open("potentiels.txt");
	
	network.update(currentStep, nbSteps, I_ext);

	

		//cout << " 1er Neuron: "<< (network.getNeuron(0)).getMembranePotential() << "			";
		//sortie <<(network.getNeuron(1)).getMembranePotential() << endl;
	 sortie.close();
	
	return 0;
	 
	 
}
