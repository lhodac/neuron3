#include "Neuron.hpp"

using namespace std;


double Neuron:: getMembranePotential() const
{
	return membranePotential_;
}
int Neuron:: getNbSpikes() const
{
	return nbSpikes_;
}
vector<double> Neuron:: getTimeSpikes() const
{
	return spikeTimes_;
}
Type Neuron:: getType() const
{
	return type_;	
}

bool Neuron:: isRefractory() const
{
	return refractory_;
}

void Neuron:: setMembranePotential(double potential)
{
	membranePotential_= potential;
}

void Neuron:: setIext(double I)
{
	I_ext_= I;
}

void Neuron:: setRefractory(bool r)
{
	refractory_= r;
}
																	
void Neuron::addTimeSpike(double time)									//To add one time at the spikeTimes table
{
	spikeTimes_.push_back(time);
}

																		//To update the simulation at each steps, it returns a boolean because we need to know if there is a spike or not
bool Neuron::update(int currentStep, double I_ext)
{
	updateBuffer();

	bool isSpiking(false);

	if (membranePotential_>= TH_POTENTIAL){
		isSpiking = true;
		addTimeSpike(currentStep*H);
		++nbSpikes_;
		setRefractory(true);
		setMembranePotential(0.0);
		}
		
	if (!refractory_){
		if (backgroundNoise_){
			std::random_device random;
			std::mt19937 gen(random());
			std::poisson_distribution<> distrib(2);//EXT_NU*H
			setMembranePotential(solveDifferentialEquation(I_ext) + buffer_[0] + distrib(gen)* J_EXCIT);
			buffer_[0]=0.0;
			}
		else {
			setMembranePotential(solveDifferentialEquation(I_ext) +buffer_[0]);
			buffer_[0]=0.0;
		}
	}
	
	if(refractory_){
		membranePotential_=0.0;
		--refractoryTime_;
		buffer_[0]=0.0;
		if (refractoryTime_ <= 0.0) { 
				refractoryTime_= REFRACTORY_TIME;
				setRefractory(false);}
		}
	//cout << membranePotential_ << endl;			
	return isSpiking;	
}
	
	
	
	//cerr << "Update Neuron" << endl;
	/*double potential(solveDifferentialEquation(I_ext)+ updateBuffer());
	bool isSpiking(false);
	
	if(getMembranePotential() >= TH_POTENTIAL and !refractory_) {
	
		isSpiking = true;
		addTimeSpike(currentStep*H);
		++nbSpikes_;
		cerr << "Nombre de spikes: " << nbSpikes_ << endl;
		setRefractory(true);
		setMembranePotential(0.0);
		
		
		cerr << getMembranePotential() << endl << "SPIKE JUST HAPPENED" <<endl;
		}
		
	else if(isRefractory()){
		setMembranePotential(0.0);
		cerr << getMembranePotential() << endl << "REFRACTORY" <<endl;
		--refractoryTime_;
			
			if (refractoryTime_ <= 0.0) { 
				refractoryTime_= REFRACTORY_TIME;
				setRefractory(false);
				}
		}
	else if(getMembranePotential()<= TH_POTENTIAL and !isRefractory()) { 
		setMembranePotential(potential); 
		} 
	
	return isSpiking;
	}*/


double Neuron:: solveDifferentialEquation(double I_ext) const
{
	return C1 * membranePotential_ + I_ext * R * C2;
}


double Neuron:: updateBuffer()
{
	for (size_t i (1); i < buffer_.size() ; ++i){
		buffer_[i-1] = buffer_[i];
		}
	
	buffer_[buffer_.size()-1] = 0.0;

	return buffer_[0];
}

void Neuron:: receive(double J)
{	

		assert(DELAY < buffer_.size());
		buffer_[DELAY]+= J;

}

Neuron:: Neuron(bool backgroundNoise,Type type)
: membranePotential_(0.0), nbSpikes_(0), refractory_(false), refractoryTime_(REFRACTORY_TIME),backgroundNoise_(backgroundNoise),type_(type)
{
	for(auto& b : buffer_){
		b= 0.0;
		}
}

Neuron:: ~Neuron()
{
	
}





