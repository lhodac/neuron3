
#include "Network.hpp"


using namespace std;

int main()
{	
	Neuron first;
	Neuron second;
	
	vector<Neuron*> neurons = {&first, &second};
	Network network(neurons);
	double simtime(0.0);
	

	//Ask the user wich current and simulation time he wants
	/*cout << "Enter the number of steps: (1step is 1ms)" << endl;
	double nbSteps(0.0);
	cin >> nbSteps;
	if (nbSteps < 0.0){cout << "ERROR: steps number has to be a positive value.";}
	
	cout << "Enter a External Current: " << endl;
	double I_ext(0.0);
	cin >> I_ext;*/
	
	
	double nbSteps(400);
	double I_ext(1.01);
	
	ofstream sortie;
	sortie.open("potentiels.txt");
	
	
	while(simtime < (nbSteps*H))
	{
		network.update(simtime, I_ext);
		simtime+=H;
		
		//cout << " 1er Neuron: "<< (network.getNeuron(0)).getMembranePotential() << "			";
		sortie <<(network.getNeuron(1)).getMembranePotential() << endl;
		
	}
	 sortie.close();
	
	return 0;
	 
	 
}
