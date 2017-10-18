#include "Network.hpp"

using namespace std;

Neuron Network:: getNeuron(int n)
{
	return *(neurons_[n]);
}

void Network::reset()	//Permet de reset a tout moment le tableau de pointeurs de Neuron en libérant la mémoire
{
	/*for(auto neuron: neurons_){
		delete neuron;
		neuron = nullptr;
	} */
	neurons_.clear();

}

void Network::update(double simtime, double I_ext)
{	
	/*for (size_t i(0); i<neurons_.size(); ++i){

		(neurons_[i])->update(simtime, I_ext); //on update tout les neurones

		bool spike((neurons_[i])->update(simtime, I_ext)); //s'il y a un spike


		if (spike){
			
			for (size_t j(1); j< neurons_.size(); ++j){
			(neurons_[i+j])->receive(simtime, DELAY,J);			
			}
		}*/
		
		
		
		bool spike((neurons_[0])->update(simtime, I_ext));
		
		neurons_[1]-> update(simtime, 0);

		if(spike) {
			neurons_[1]-> receive(simtime, J);
			}

			
		cout << simtime << endl << " 1er Neuron: "<< getNeuron(0).getMembranePotential() << "			";
		cout << " 2ème Neuron: "<< getNeuron(1).getMembranePotential() << endl;
}


Network:: Network(vector<Neuron*> neurons)
{
	neurons_ = neurons;
}
Network:: ~Network()
{
	reset();
}
	
