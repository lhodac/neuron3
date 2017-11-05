#include "Network.hpp"
#include "Constants.hpp"

using namespace std;

int main()
{	

	Network network;
	
	///<Ask the user wich current and simulation time he wants, not activated because user is the programmer for now
	
	/*cout << "Enter the number of steps: (1step is 1ms)" << endl;
	double nbSteps(0.0);
	cin >> nbSteps;
	if (nbSteps < 0.0){cout << "ERROR: steps number has to be a positive value.";}
	
	cout << "Enter a External Current: " << endl;
	double I_ext(0.0);
	cin >> I_ext;*/


	network.update(currentStep, nbSteps, 0.0);

	
	return 0;
	 
	 
}

