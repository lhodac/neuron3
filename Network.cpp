#include "Network.hpp"

using namespace std;

Neuron Network:: getNeuron(int n)
{
	return *(neurons_[n]);
}

void Network::reset()		//Permet de reset a tout moment le tableau de pointeurs de Neuron en libérant la mémoire
{
	if (!neurons_.empty()){
			for(auto neuron: neurons_){
				delete neuron;
				neuron = nullptr;
			}
	}
	neurons_.clear();
}

void Network:: addNeuron(Neuron neuron)
{
		neurons_.push_back(&neuron);
}


void Network::update(int currentStep,int nbSteps, double I_ext)
{	
	while(currentStep < nbSteps)
	{
		++currentStep;
		for (size_t i(0); i< neurons_.size(); ++i){
			bool spike((neurons_[i])->update(currentStep, I_ext)); //s'il y a un spike
			(neurons_[i])->update(currentStep, I_ext); //on update tout les neurones
			cout << "Pot neurone " << (i+1) << getNeuron(i).getMembranePotential()<< endl;

				if (spike){
					for (auto postNeuron : neurons_[i]->getPostNeurons()){
						postNeuron->receive(currentStep,J);		
						}	
					}
				//cout << "Temps: " << currentStep * H << " , Potentiel: " << getNeuron(i).getMembranePotential()<<endl;

			}
	}
	
	
	
	
	
	/*while(currentStep < nbSteps)
	{
		++currentStep;
		
		
		bool spike((neurons_[0])->update(currentStep, I_ext));
		
		neurons_[1]-> update(currentStep, 0);

		if(spike) {
			neurons_[1]-> receive(currentStep, J);
			}

			
		cout << currentStep * h << endl << " 1er Neuron: "<< getNeuron(0).getMembranePotential() << "			";
		cout << " 2ème Neuron: "<< getNeuron(1).getMembranePotential() << endl;
	}*/
}


Network:: Network()
{
	reset();
}
Network:: ~Network()
{
	//reset();
}
	
