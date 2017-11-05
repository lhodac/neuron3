#include "Network.hpp"
#include <random>

using namespace std;


void Network::reset()													//Permet de reset a tout moment le tableau de pointeurs de Neuron en libérant la mémoire
{
	if (!neurons_.empty()){
			for(auto& neuron: neurons_){
				delete neuron;
				neuron = nullptr;
			}
	}
	for(auto& ligne : neuronsRelations_) {
		for (auto& numero: ligne){
			numero=0;
			}
		neuronsRelations_.clear();
		}
}

void Network::update(int currentStep,int nbSteps, double I_ext)
{	
	ofstream sortie;
	sortie.open("NombreSpikesPerSteps.txt");
	cerr << "Update Network----------------------------------------" << endl;
	
	bool spike(false);
	
	assert(currentStep < nbSteps);
	while(currentStep < nbSteps)
		{
				
		for (int i(0);i <neurons_.size();++i){
			spike = (neurons_[i]->update(currentStep, I_ext));

				if (spike){
					
					++NbSpikesPerStep[currentStep];
					
					//if (i<50 and currentStep >500){	sortie << currentStep << '\t' << i << '\n';}
					
					for(int j(0); j< neuronsRelations_[i].size(); ++j){
						Type type;
						if (neurons_[i]->getType() == Excitatory){
							neurons_[neuronsRelations_[i][j]]->receive(J_EXCIT);
							}
						else {neurons_[neuronsRelations_[i][j]]->receive(J_INHIB);
							}
						}
					}
			}
			
		++currentStep;

		}
		
	
	sortie.close();
	
		for (int k(0); k<nbSteps ; ++k){
			cout << NbSpikesPerStep[k] << endl;
			}
}




void Network::fillNeuronsRelations()
{
	cerr << "FILL TABLEAU RELATIONS" << endl;

	std::random_device random;
	std::mt19937 gen(random());
		
	std::uniform_int_distribution<> Excit_Distrib (0,(NB_EXCIT-1));
	std::uniform_int_distribution<> Inhib_Distrib (NB_EXCIT, (NB_EXCIT + NB_INHIB)-1);
	
	array<int, TOTAL_CONNEXIONS> ligne;
	
	for (int i(0); i<NB_NEURONS ; ++i){
		neuronsRelations_.push_back(ligne);
	}
	
	
	for(auto& liste: neuronsRelations_) {

			
		for (int k(0); k< EXCIT_CONNEXIONS; ++k){						
			assert(k < EXCIT_CONNEXIONS	);
			
			int Ex_distribution(Excit_Distrib(gen));
			liste[k] = Ex_distribution;  								
			}
		
		for (int l(EXCIT_CONNEXIONS); l< (TOTAL_CONNEXIONS); ++l){	
			assert(l < TOTAL_CONNEXIONS);
			
			int In_distribution(Inhib_Distrib(gen));
			liste[l] = In_distribution;
			}
			
		/*for (auto cible: liste){										//Affichage matrice relations
			cout << cible << "   ";												
			}
		cout << endl;*/
		
		}
		
cerr <<"Fin fillRelations" << endl;
}

void Network:: CreateNeurons()
{
	for(size_t i(0); i< neurons_.size();++i){
		assert(i < neurons_.size());
		if (i<	NB_EXCIT) { neurons_[i]= new Neuron(1,Excitatory);}
		else {neurons_[i] = new Neuron(1,Inhibitory);}
		}
}

Network::Network()
{
	for (auto& n: NbSpikesPerStep){
		n=0;
	}
	
	
	CreateNeurons();
	fillNeuronsRelations();
}

Network::~Network()
{
	
	reset();

}

