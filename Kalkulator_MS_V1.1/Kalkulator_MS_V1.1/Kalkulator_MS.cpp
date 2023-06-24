#include <iostream>
#include "Kalkulator_MS.h"
#include <vector>
#include <algorithm>
#include <cmath>


//--------------------------------------------------------Klasa Calculations---------------------------------------------------------------

//obliczanie pradu
double Calculations::current(double V, double R)
{
    return V / R;
}

//obliczanie napiecia
double Calculations::voltage(double R, double I)
{
    return I * R;
}

//obliczanie rezystancji
double Calculations::resistance(double V, double I)
{
    return  V / I;
}

//obliczanie wartosci rezystora
double Calculations::resistanceLED(double V, double I, string color)
{
    double drop{}; //sredni spadek napiecie, uzelezniony od koloru LEDa
    double IA; // prad w Amperach
    IA = I / 1000;

    if (V <= 0)
    {
        cout << "Niepoprawana wartosc napiecia zasilania" << endl;
        return 0.0;
    }

    if (color == "red")
        drop = 2.0;

    else if (color == "blue")
        drop = 3.8;

    else if (color == "yellow")
        drop = 2.2;

    else if (color == "green")
        drop = 3.0;

    else if (color == "white")
        drop = 3.3;
    else
        cout << "Niepoprawny kolor diody";
    
    if (V <= drop)
    {
        cout << "Napiecie zasilania jest za ma³e, nie moze byc mniejsze niz spadek napiecia na diodzie" << endl;
        return 0.0;
    }

    double diodeV = V - drop;
    double resistanceLed = diodeV / IA;
    return resistanceLed;

}

//Dzielnik napiecia
 vector <double> Calculations::voltageDivider(double R1, double R2, double V)
{
    vector <double> voltage;

    V1 = (R1 / (R1 + R2)) * V;
    voltage.push_back(V1);

    V2 = (R2 / (R1 + R2)) * V;
    voltage.push_back(V2);

    return voltage;
}

 //Dzielnik pradu
vector <double> Calculations::currentDivider(double R1, double R2, double I)
{
    vector <double> current;

    I1 = (R2 / (R1 + R2)) * I;
    current.push_back(I1);

    I2 = (R1 / (R1 + R2)) * I;
    current.push_back(I2);

    return current;
    
}

//metoda która sprawdza poprawnosc tego co wpisujemy przy podawaniu rezystancji
void Calculations::readResistorSecurity(const string& nameR, double& R)
{
    while (true)
    {
        cout << "Podaj wartosc rezystora " << nameR << " (Om) : ";
        if (cin >> R)
        {
            if (R > 0)
                break;
            else cout << "Rezystancja nie moze byc mniejsza badz rowna 0" << endl;
        }
        else
        {
            cout << "Niepoprawna wartosc rezystancji, sprobuj ponownie" << endl;
            cout << "" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
//uzyta 4 razy w "case4 4"


//--------------------------------------------------------Klasa Conversion---------------------------------------------------------------

//metoda do ponownego przeliczenia dla systemów liczbowych
bool Conversion::iteration()
{
    char choice;

    
        cout << "Czy chcesz przeliczyc liczbe ponownie w innym systemie? (Y,y / N,n): ";
        cout << "" << endl;
        cin >> choice;

        if (choice == 'Y' || choice == 'y')
        {
            return true;
        }
        else if (choice == 'N' || choice == 'n')
        {
            return false;
        }
        else
        {
            cout << "Niepoprawny wybor. Proszê sprobowac ponownie." << endl;
            return iteration();
        }
    
}

//Zamiana z dziesietnego(DEC) na pozosta³e
string Conversion::baseToSystem(int number, int base)
{
    string outcome;

    while (number > 0)
    {
        int remainder = number % base;
        char digit;

        if (remainder < 10)
            digit = '0' + remainder;
        else
            digit = 'A' + remainder - 10;

        outcome.insert(outcome.begin(), digit);
        number /= base;
    }

    return outcome;
}

//Zamiana z binarnego(BIN) na pozosta³e
string Conversion::binToSystem(const string& bin, int system)
{
    for (char a : bin)
        if (a != '0' && a != '1')
        {
            std::cout << "Niepoprawna liczba" << std::endl;
            std::cout << "Twoja liczba powinna byc 0-em lub 1-ynka" << std::endl;
            return "";
        }
    int dec = 0;
    int power = 0;

    // Konwersja z systemu binarnego na liczbê dziesiêtn¹
    for (int i = bin.length() - 1; i >= 0; i--)
    {
        if (bin[i] == '1')
            dec += pow(2, power);

        power++;
    }

    return baseToSystem(dec, system); 
}

//Zamiana z szesnastkowego(HEX) na pozosta³e 
string Conversion::hexToSystem(const string& hex, int system)
{
    std::string outcome;
    int dec = 0;
    int power = 0;

    for (int i = hex.length() - 1; i >= 0; i--)
    {
        int rest = 0;

        if (hex[i] >= '0' && hex[i] <= '9')
            rest = hex[i] - '0';
        else if (hex[i] >= 'A' && hex[i] <= 'F')
            rest = hex[i] - 'A' + 10;
        else if (hex[i] >= 'a' && hex[i] <= 'f')
            rest = hex[i] - 'a' + 10;
        else
        {
            std::cout << "Znaleziono nieprawidlowy znak" << std::endl;
            return ""; // W przypadku nieprawid³owego znaku, przerwij dzia³anie funkcji
        }

        dec += rest * std::pow(16, power);
        power++;
    }

    return baseToSystem(dec, system); // wykorzystuje juz napisana funkcje aby nie powtarzac kodu
}

//Zamiana z ósemkowego(OCT) na pozosta³e 
string Conversion::octToSystem(const string& oct, int system)
{
    std::string outcome;
    int dec = 0;
    int power = 0;

    for (int i = oct.length() - 1; i >= 0; i--)
    {
        int digit = oct[i] - '0';

        if (digit < 0 || digit > 7)
        {
            std::cout << "Znaleziono nieprawidlowy znak" << std::endl;
            return ""; // W przypadku nieprawid³owego znaku, przerwij dzia³anie funkcji
        }

        dec += digit * std::pow(8, power);
        power++;
    }

    return baseToSystem(dec, system); // wykorzystuje juz napisana funkcje aby nie powtarzac kodu

}
