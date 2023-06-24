#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cmath>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

struct Calculations //klasa dla podstawowych obliczen dla elektronika
{
	//zmienne dla metod
	double V1{};
	double V2{};
	double I1{};
	double I2{};

	double resistance(double V, double I); //obliczanie rezystancji
	double current(double V, double R); //obliczanie pradu
	double voltage(double R, double I); //obliczanie napiecia

	double resistanceLED(double V, double I, string color); //funkcja ktora oblicza wartosc rezystora dla LEDa
	vector <double> voltageDivider(double R1, double R2, double V); //dzielnik napiecia, ktory zwraca 2 wartosci
	vector <double> currentDivider(double R1, double R2, double I); //dzielnik pradu, ktory zwraca 2 wartosci
	void readResistorSecurity(const string& nameR, double& R); //kontrola tego co wpisujemy przy podawaniu rezytancji
};

class Conversion //klasa do konwersji systemów liczbowych
{
public:
	string baseToSystem(int number, int base); //Zamiana z dziesietnego(DEC) na pozostałe
	string binToSystem(const string& bin, int system);//Zamiana z binarneg0(BIN) na pozostałe
	string hexToSystem(const string& hex, int system); //Zamiana z szesnastkowego(HEX) na pozostałe
	string octToSystem(const string& oct, int system); //Zamiana z ósemkowego(OCT) na pozostałe
	bool iteration(); //funkcja do zapetlenia, dla funkcji dla systemów liczbowych

};

