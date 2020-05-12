///*--------------------------------------------------*/
/// eic.cc:
/// Original author: Dr. Ahmed Zafar
/// Date: 2015-2018
///
///*--------------------------------------------------*/
/// Modifier: Wenliang (Bill) Li
/// Date: Feb 24 2020
/// Email: wenliang.billlee@gmail.com
///
/// Comment: Feb 24, 2020: the main function is excuted in main.cc


#include "eic.h"
#include "json/json.h"
#include "json/json-forwards.h"

using std::setw;
using std::setprecision;
using std::cout;
using std::cin;
using std::endl;
using namespace std;

//---------------------------------------------------------
// g++ -o pim pimFermi.C `root-config --cflags --glibs`
//---------------------------------------------------------

//int main() {
// 
//  eic();
//  
//  return 0;
//}

void eic() {

    Int_t target_direction, kinematics_type;
 
   	cout << "Target Direction (1->Up, 2->Down): "; cin >> target_direction; cout << endl;
   	cout << "Kinematics type (1->FF, 2->TSSA): ";  cin >> kinematics_type;  cout << endl;
   	cout << "Enter the number of events: ";        cin >> fNEvents;         cout << endl;
   	cout << "Enter the file number: ";             cin >> fNFile;           cout << endl;
 
//	eic(target_direction, kinematics_type, fNEvents);

}

/*--------------------------------------------------*/

void eic(int event_number, int target_direction, int kinematics_type, TString file_name, int fEIC_seed, TString particle) {

   	TString targetname;  
	TString charge;

   	if( target_direction == 1 ) targetname = "up";
  	if( target_direction == 2 ) targetname = "down";

	gKinematics_type = kinematics_type;
	gfile_name = file_name;

	fNFile = 1;

	fNEvents = event_number;

	fSeed = fEIC_seed;

	pim* myPim = new pim(fSeed);
  	myPim->Initilize();
 
//  	TDatime dsTime;
//  	cout << "Start Time:   " << dsTime.GetHour() << ":" << dsTime.GetMinute() << endl;

	particle = ExtractParticle(particle);
	charge = ExtractCharge(particle);

//	if (particle == "pi") {
//		Exclusive_Pion_Prodoction(*myPim);
//	} else if (particle == "omega") {
//		Exclusive_Omega_Prodoction(*myPim);
//	} else {
//		cerr << "Choice of particle is not recognized." << endl;
//		exit(0);
//	}

//    TDatime dsTime;
//  	cout << "Start Time:   " << dsTime.GetHour() << ":" << dsTime.GetMinute() << endl;
	
//	TStopwatch tTime;
//   	tTime.Start();
//
//	Exclusive_Pion_Prodoction(*myPim);
//	
//	tTime.Stop();
//   	tTime.Print();

	Reaction* r1 = new Reaction(particle);
	r1->process_reaction();
	delete r1;

}

/*--------------------------------------------------*/
/*--------------------------------------------------*/

void SetEICSeed (int seed) {
	fSeed = seed;
}




///*--------------------------------------------------*/
///*--------------------------------------------------*/
///  Some utility functions


///*--------------------------------------------------*/
/// Extracting the particle type

TString ExtractParticle(TString particle) {

	/// Make the input particle case insansitive
	particle.ToLower();

	if (particle.Contains("on")) {
		particle.ReplaceAll("on", "");
	};
	
	if (particle.Contains("plus")) {
		particle.ReplaceAll("plus", "+");
	}

	if (particle.Contains("minus")) {
		particle.ReplaceAll("minus", "-");
	}

	if (particle.Contains("zero")) {
		particle.ReplaceAll("zero", "0");
	}

	particle[0] = toupper(particle[0]);

	cout << "Particle: " << particle << endl;

	return particle;

}

///*--------------------------------------------------*/
/// Extracting the particle charge

TString ExtractCharge(TString particle) {

	TString charge;

	if (particle.Contains("+") || particle.Contains("plus")) {
		charge = "+";
	} else if (particle.Contains("-") || particle.Contains("minus")) {
		charge = "-";
	} else {
		charge = "0";
	}

	return charge;

}