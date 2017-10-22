#include "neuron.hpp"

using namespace std;

//GETTERS
double Neuron:: getMembranePotential() const
{
	return membranePotential_;
}
double Neuron:: getNbSpikes() const
{
	return nbSpikes_;
}
vector<double> Neuron:: getTimeSpikes() const
{
	return spikeTimes_;
}
vector<Neuron*> Neuron:: getPostNeurons() const
{
	return postNeurons_;
}

bool Neuron:: isRefractory() const
{
	return refractory_;
}


//SETTERS
void Neuron:: setMembranePotential(double potential)
{
	membranePotential_= potential;
}
void Neuron:: setNbSpikes(double nb)
{
	nbSpikes_= nb;
}
void Neuron:: setRefractory(bool r)
{
	refractory_= r;
}

//To add one time at the spikeTimes table
void Neuron::addTimeSpike(double time)
{
	spikeTimes_.push_back(time);
}

void Neuron::addPostNeuron(Neuron n)
{
	postNeurons_.push_back(&n);
}

//To update the simulation at each steps, it returns a boolean because we need to know if there is a spike or not
bool Neuron::update(int currentStep, double I_ext)
{
	//cerr << "Update Neuron" << endl;
	double potential(solveDifferentialEquation(I_ext)+ updateBuffer());
	bool isSpiking(false);
	
	
	if(getMembranePotential() >= TH_POTENTIAL and !refractory_) {
		isSpiking = true;
		addTimeSpike(currentStep*H);
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
	else { setMembranePotential(potential); } 
	
	return isSpiking;
	

}

//To solve the equation of the potential
double Neuron:: solveDifferentialEquation(double I_ext) const
{
	return exp(-H/TAU) * getMembranePotential() + I_ext * R * (1-exp(-H/TAU));
}


double Neuron:: updateBuffer()
{
	for (size_t i (1); i < buffer_.size() ; ++i){
		buffer_[i-1] = buffer_[i];
		}
	buffer_[buffer_.size()-1] = 0.0;

	return buffer_[0];
}

void Neuron:: receive(int currentStep,double J)
{	
	cerr<<"Spike received at time " << (currentStep *H) << endl;
	

	buffer_[(currentStep+DELAY) % (buffer_.size())]+= J;
}

//Constructor: we initialise the values at 0.0 and false
Neuron:: Neuron()
: membranePotential_(0.0), nbSpikes_(0.0), refractory_(false), refractoryTime_(REFRACTORY_TIME)
{
	for(auto b : buffer_){
		buffer_[b]= 0.0;
		}
}

//Destructor: we clear the times vector
Neuron:: ~Neuron()
{
	spikeTimes_.clear();
}




