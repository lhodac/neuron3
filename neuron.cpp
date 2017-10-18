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

//To update the simulation at each steps, it returns a boolean because we need to know if there is a spike or not
bool Neuron:: update(double simtime, double I_ext)
{
	//cerr << "Update Neuron" << endl;
	double potential(solveDifferentialEquation(I_ext)+ updateBuffer());
	setMembranePotential(potential);
	//cout<< "Potentiel:	"<< getMembranePotential() << endl;
	if(isRefractory()){
		setMembranePotential(0.0);
		setRefractory(false);
		cerr << getMembranePotential() << endl << "REFRACTORY" <<endl;
		}
	else if(getMembranePotential() > TH_POTENTIAL) {
		addTimeSpike(simtime);
		setRefractory(true);
		cerr << getMembranePotential() << endl << "SPIKE JUST HAPPENED" <<endl;
		return true;
		}
		
	return false;
		
		
}

//To solve the equation of the potential
double Neuron:: solveDifferentialEquation(double I_ext) const
{
	return exp(-H/TAU) * getMembranePotential() + I_ext * R * (1-exp(-H/TAU));
}


double Neuron:: updateBuffer()
{
	//cerr<<"UPDATE BUFFER" <<endl;

	for (size_t i (1); i < buffer.size() ; ++i){
		buffer[i-1] = buffer[i];
	}
	buffer[buffer.size()-1] = 0.0;

	return buffer[0];
}

void Neuron:: receive(double simtime,double J)
{	
	cerr<<"Spike received" <<endl;
	
	int time(simtime);
	buffer[time % (buffer.size())]+= J;
}

//Constructor: we initialise the values at 0.0 and false
Neuron:: Neuron()
: membranePotential_(0.0), nbSpikes_(0.0), refractory_(false)
{
	for(auto b : buffer){
		buffer[b]= 0.0;
		}
}

//Destructor: we clear the times vector
Neuron:: ~Neuron()
{
	spikeTimes_.clear();
}




