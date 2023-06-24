//
//Projekt Miłosz-a Sokoł-a  24.06.2023r.
// KALKULATOR DLA ELEKTRONIKÓW
//
//Projekt zawiera 4 pliki, 3 z kodem odpowiedno:
// 1. plik main(Main_Kalkulator_V1.cpp)
// 2. plik h(Kalkulator_MS.h)
// 3. plik (Kalkulator_MS.cpp)
// oraz dokumentacja w pliku tekstowym


#include <iostream>
#include "Kalkulator_MS.h"
#include <vector>
#include <string>
#include <limits>
#include <cmath>

int main()
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "-------------------KALKULATOR DLA ELEKTRONIKOW--------------------" << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << "" << endl;

    int choice{};  //zmienna do wyboru dla głownych funkcji kalkulatora

    while (choice != 6)
    {

        cout << "-------------------WYBIERZ FUNKCJE KALKULATORA:-------------------" << endl;
        cout << "" << endl;
        cout << "1. Przeliczanie systemow liczbowych" << endl;
        cout << "2. Obliczanie podstawowych wartosci pradu, napiecia i rezystancji" << endl;
        cout << "3. Obliczanie wartosci rezystora dla LED" << endl;
        cout << "4. Dzielnik napiecia oraz pradu" << endl;
        cout << "5. Wyjscie z kalkulatora" << endl;

        cin >> choice; 
        
        //case 1------------------------------------------------------------------------------------------------
        string sysChoice; //zmienna dzieki której mozemy wybrac w jakim systemie wpisujemy liczbe
        string system;  //system liczbowy
        string digit;  //liczba podana przez uzytkownika do konwersji
        int digitDEC{}; //liczba podana przez uzytkownika do konwersji dla systemu dziesietnego
        string wynik; //wynik obliczen


        // case 2------------------------------------------------------------------------------------------------
        int calcChoice{};  //zmienna dzieki której mozemy wybrac co chcemy policzyc
        double wynikC{};  //zapis wyniku

        //zmienne dla pradu, rezystancji i napiecia
        double I{};
        double R{};
        double V{};

        //case3------------------------------------------------------------------------------------------------
        int ledChoice{};  //wybor koloru diody
        double ledResistance{};  //zmienna dla wyniku obliczonej rezystancji

        //case4------------------------------------------------------------------------------------------------
        int divChoice{};  //wybór dzielnika

        //zmienne dla pradu, napiecia oraz resytancji
        double R1{};
        double R2{};
        double V1{};
        double I1{};
        vector <double> voltages; //wektor obliczonych spadków napiec na rezystorach
        vector <double> currents; //wektor obliczonych pradów jakie popłyna przez konketny rezystor

        //obiekty------------------------------------------------------------------------------------------------
        Conversion conv; //obiekt dla przeliczenia dla systemów liczbowych
        Calculations calc; //obiekt dla obliczen dla case2
        Calculations led;  //obiekt dla obliczania wartosci rezystora do LEDów
        Calculations volt;  //obiekt dla dzielnika napiec
        Calculations curr;  //obiekt dla dzielnika prądów
        Calculations readResistor;  //obiekt dla metody sprawdzajacej dla rezytsorów


        switch (choice)
        {
        case 1: 
            cout << "Wybrales przeliczanie systemow liczbowych" << endl;
            cout << "-----------------------------------------" << endl;
            cout << "Wybierz system w ktorym wpiszesz liczbe: " << endl;
            cout << "(wpisz nazwe systemu z nawiasu np 'HEX' lub 'BIN')" << endl;
            cout << "" << endl;
            cout << "1. Szesnastkowy(HEX)" << endl << "2. Dziesietny(DEC)" <<
                endl << "3. Osemkowy(OCT)" << endl << "4. Binarny(BIN)" << endl;
            cin >> sysChoice;

            if (sysChoice == "HEX") //zamiana z HEX na pzoostałe
            {
                while (true)
                {

                    cout << "Na jaki system chcesz zamienic?" << endl;
                    cout << "1. Dziesietny(DEC)" << endl << "2. Osemkowy(OCT)" << endl << "3. Binarny(BIN)" << endl;

                    cin >> system;

                    cout << "Podaj liczbe w zapisie szesnastkowym (mozesz uzywac duzych jak i maLych liter np. A5C3 = a5c3" << endl;
                    cout << "Twoja liczba: ";
                    cin >> digit;


                    if (system == "DEC")  // na DEC
                    {
                        wynik = conv.hexToSystem(digit, 10);
                        cout << "Twoja liczba w zapisie dziesietnym to: " + wynik << endl;
                        cout << "" << endl;
                    }
                    else if (system == "OCT")  //na OCT
                    {
                        wynik = conv.hexToSystem(digit, 8);
                        cout << "Twoja liczba w zapisie osemkowym to: " + wynik << endl;
                        cout << "" << endl;
                    }
                    else if (system == "BIN")  //na BIN
                    {
                        wynik = conv.hexToSystem(digit, 2);
                        cout << "Twoja liczba w zapisie binarnym to: " + wynik << endl;
                        cout << "" << endl;
                    }
                    else if (system == "HEX")  // dla ciekawych na HEX
                    {
                        cout << "Nie ma sensu zamieniac liczby z tego samego systemu na ten sam, ale prosze bardzo:" << endl;
                        cout << "Twoja liczba w zapisie dziesietnym to: " + wynik << endl;
                        cout << "" << endl;
                    }
                    else
                    {
                        cout << "Podano nieprawidlowy wybor" << endl;
                        cout << "" << endl;
                        continue;
                    }

                    if (!conv.iteration())  // metoda do powtórzenia wyboru
                        break;
                }



            }
            else if (sysChoice == "DEC")  // zamiana z dziesietnego na pozostałe
            {
                while (true)
                {
                    cout << "Na jaki system chcesz zamienic?" << endl;
                    cout << "1. Szesnastkowy(HEX)" << endl << "2. Osemkowy(OCT)" << endl << "3. Binarny(BIN)" << endl;
                    cin >> system;

                    cout << "Podaj liczbe w zapisie dziesietnym:" << endl;
                    cout << "Twoja liczba: ";
                    cin >> digitDEC;

                    if (system == "HEX")  //na HEX
                    {
                        wynik = conv.baseToSystem(digitDEC, 16);
                        cout << "Twoja liczba w zapisie szesnastkowym to: " + wynik << endl;
                        cout << "" << endl;
                    }
                    else if (system == "OCT")  //na OCT
                    {
                        wynik = conv.baseToSystem(digitDEC, 8);
                        cout << "Twoja liczba w zapisie osemkowym to: " + wynik << endl;
                        cout << "" << endl;
                    }
                    else if (system == "BIN")  //na BIN
                    {
                        wynik = conv.baseToSystem(digitDEC, 2);
                        cout << "Twoja liczba w zapisie binarnym to: " + wynik << endl;
                        cout << "" << endl;
                    }
                    else if (system == "DEC")  //na DEC dla ciekawych
                    {
                        cout << "Nie ma sensu zamieniac liczby z tego samego systemu na ten sam, ale prosze bardzo:" << endl;
                        cout << "Twoja liczba w zapisie dziesietnym to: " + digitDEC;
                    }
                    else
                        cout << "Podano nieprawidłowy wybór" << endl;

                    if (!conv.iteration())  // metoda do powtórzenia wyboru
                        break;

                }


            }
            else if (sysChoice == "OCT")  //zamiana z ósemkowego na pozostałe
            {
                while (true)
                {
                    cout << "Na jaki system chcesz zamienic?" << endl;
                    cout << "1. Szesnastkowy(HEX)" << endl << "2. Dziesietny(DEC)" << endl << "3. Binarny(BIN)" << endl;

                    cin >> system;

                    cout << "Podaj liczbe w zapisie Osemkowym" << endl;
                    cout << "Twoja liczba: ";
                    cin >> digit;


                    if (system == "HEX")  //na HEX
                    {
                        wynik = conv.octToSystem(digit, 16);
                        cout << "Twoja liczba w zapisie szesnastkowym to: " + wynik << endl;
                        cout << "" << endl;
                    }
                    else if (system == "DEC")  //na DEC
                    {
                        wynik = conv.octToSystem(digit, 10);
                        cout << "Twoja liczba w zapisie dziesietnymm to: " + wynik << endl;
                        cout << "" << endl;
                    }
                    else if (system == "BIN")  //na BIN
                    {
                        wynik = conv.octToSystem(digit, 2);
                        cout << "Twoja liczba w zapisie binarnym to: " + wynik << endl;
                        cout << "" << endl;
                    }
                    else if (system == "OCT")  //na OCT dla ciekawych
                    {
                        cout << "Nie ma sensu zamieniac liczby z tego samego systemu na ten sam, ale prosze bardzo:" << endl;
                        cout << "Twoja liczba w zapisie ósemkowymto: " + wynik << endl;
                        cout << "" << endl;
                    }
                    else
                        cout << "Podano nieprawidLowy wybór" << endl;
                }

                if (!conv.iteration())  // metoda do powtórzenia wyboru
                    break;


            }
            else if (sysChoice == "BIN") // zamiana z binarnego na pozostałe
            {
                while (true)
                {
                    cout << "Na jaki system chcesz zamienic?" << endl;
                    cout << "1. Szesnastkowy(HEX)" << endl << "2. Dziesietny(DEC)" << endl << "3. Osemkowy(OCT)" << endl;

                    cin >> system;

                    cout << "Podaj liczbe w zapisie binarnym (pamietaj tylko 0 i 1)" << endl;
                    cout << "Twoja liczba: ";
                    cin >> digit;


                    if (system == "DEC")  // na DEC
                    {
                        wynik = conv.binToSystem(digit, 10);
                        cout << "Twoja liczba w zapisie dziesietnym to: " + wynik << endl;
                        cout << "" << endl;
                    }
                    else if (system == "OCT")  //na OCT
                    {
                        wynik = conv.binToSystem(digit, 8);
                        cout << "Twoja liczba w zapisie Osemkowym to: " + wynik << endl;
                        cout << "" << endl;
                    }
                    else if (system == "HEX")  // na HEX
                    {
                        wynik = conv.binToSystem(digit, 16);
                        cout << "Twoja liczba w zapisie szesnastkowym to: " + wynik << endl;
                        cout << "" << endl;
                    }
                    else if (system == "BIN")  // na BIN dla ciekawych
                    {
                        cout << "Nie ma sensu zamieniac liczby z tego samego systemu na ten sam, ale prosze bardzo:" << endl;
                        cout << "Twoja liczba w zapisie binarnym to: " + wynik << endl;
                        cout << "" << endl;
                    }
                    else
                        cout << "Podano nieprawidlowy wybor" << endl;

                    if (!conv.iteration())  // metoda do powtórzenia wyboru
                        break;

                }

            }
            else
                cout << "Podano nieprawidlowy wybor, sprobuj jeszcze raz" << endl;
            break;

        case 2: 
            cout << "Wybrales obliczanie podstawowych wartosci pradu, napiecia i rezystancji" << endl;
            cout << "----------------------------------------------------------------------" << endl;
            cout << "Wybierz wartosc ktora chesz policzyc: " << endl;
            cout << "1. Napiecie" << endl << "2. Prad" << endl << "3. Rezystancje" << endl;
            cin >> calcChoice;

            if (calcChoice == 1)  //Obliczanie napiecia
            {
                // kod pobierajacy dane oraz sprawdzajacy czy wpisane wartosci sa liczba, powtarza sie w dalszych czesciach kodu 
                while (true)
                {
                    cout << "Podaj wartosc pradu oraz rezystancji:" << endl;
                    if (cout << "Prad(A): "; cin >> I)
                    {
                        if (I > 0)
                            break;
                        else cout << "Prad nie moze byc rowny badz mniejszy od 0" << endl;
                    }
                    else
                    {
                        cout << "Niepoprawna wartosc pradu, sprobuj ponownie" << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }

                while (true)
                {
                    //cout << "Podaj wartosc pradu oraz rezystancji:" << endl;
                    if (cout << "Rezystancja(Om): "; cin >> R)
                    {
                        if (R > 0)
                            break;
                        else cout << "Rezystancja nie moze byc rowna badz mniejsza od 0" << endl;
                    }
                    else
                    {
                        cout << "Niepoprawna wartosc rezystancji, sprobuj ponownie" << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }

                //cout << "Podaj wartosc pradu oraz rezystancji:" << endl;
                //cout << "Prad(A): "; cin >> I;
                //cout << "Rezystancja(Om): "; cin >> R;

                wynikC = calc.voltage(R, I);  //metoda z klasy Calculations
                cout << "Wartosc napiecia wynosi: " << wynikC << " V" << endl;
                cout << "" << endl;
            }
            else if (calcChoice == 2)  //obliczanie pradu
            {
                while (true)
                {
                    cout << "Podaj wartosc napiecia oraz rezsytancji:" << endl;
                    if (cout << "Napiecie(V): "; cin >> V)
                    {
                        if (V > 0)
                            break;
                        else cout << "Napiecie nie moze byc rowne badz mniejsze od 0" << endl;
                    }
                    else
                    {
                        cout << "Niepoprawna wartosc napiecia, sprobuj ponownie" << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }

                while (true)
                {
                    if (cout << "Rezystancja(Om): "; cin >> R)
                    {
                        if (R > 0)
                            break;
                        else cout << "Rezystancja nie moze byc rowna badz mniejsza od 0" << endl;
                    }
                    else
                    {
                        cout << "Niepoprawna wartosc rezystancji, sprobuj ponownie" << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }

                wynikC = calc.current(V, R);  //metoda z klasy Calculations
                cout << "Wartosc pradu wynosi: " << wynikC << " A" << endl;
                cout << "" << endl;

            }
            else if (calcChoice == 3)  //obliczanie rezystancji
            {
                //cout << "Prad(A): "; cin >> I;
                //cout << "Napiecie(V): "; cin >> V;

                while (true)
                {
                    cout << "Podaj wartosc pradu oraz napiecia:" << endl;
                    if (cout << "Prad(A): "; cin >> I)
                    {
                        if (I > 0)
                            break;
                        else cout << "Prad nie moze byc rowny badz mniejszy od 0" << endl;
                    }
                    else
                    {
                        cout << "Niepoprawna wartosc pradu, sprobuj ponownie" << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }

                while (true)
                {
                    if (cout << "Napiecie(V): "; cin >> V)
                    {
                        if (V > 0)
                            break;
                        else cout << "Niepoprawna wartosc napiecia, sprobuj ponownie" << endl;
                    }
                    else
                    {
                        cout << "Niepoprawna wartosc napiecia, sprobuj ponownie" << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }

                wynikC = calc.resistance(V, I);  //metoda z klasy Calculations
                cout << "Wartosc rezystancji wynosi: " << wynikC << " Om" << endl;
                cout << "" << endl;
            }
            else
            {
                cout << "Podano nieprawidlowy wybor, sprobuj jeszcze raz" << endl;
                cout << "" << endl;
            }

            break;

        case 3:
            cout << "Wybrales obliczanie wartosci rezystora dla LED" << endl;
            cout << "----------------------------UWAGA-------------------------------------" << endl;
            cout << "Aby obliczyc wartosc rezystora podaj napiecie przylozone," << endl;
            cout << "oraz prad ktory poplynie przez diode (nie powinien przekroczyc 30mA)" << endl;
            cout << "Wybierz rowniez kolor diody:" << endl;
            cout << "----------------------------------------------------------------------" << endl;

            // kod pobierajacy dane oraz sprawdzajacy czy wpisane wartosci sa liczba
            while (true)
            {
                cout << "Podaj napiecie(w Voltach): ";
                if (cin >> V)
                {
                    if (V > 0)
                        break;
                    else cout << "Napiecie nie moze byc ujemne badz rowne 0" << endl;
                }
                else
                {
                    cout << "Niepoprawna wartosc napiecia, sprobuj ponownie" << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }

            while (true)
            {
                cout << "Podaj prad, ktory poplynie przez diode(w miliamperach): ";
                if (cin >> I)
                {
                    if (I > 0)
                        break;
                    else
                        cout << "Prad nie moze byc ujemny badz rowny 0" << endl;
                }
                else
                {
                    cout << "Niepoprawna wartosc pradu. Sprobuj ponownie." << std::endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                }
            }

            //wybor koloru diody, rózne kolory maja rózne spadki napiecia
            cout << "" << endl;
            cout << "Wybierz kolor diody:" << endl;
            cout << "1. Czerwony" << endl << "2. Niebieski" << endl << "3. Zolty" << endl
                << "4. Zielony" << endl << "5. Bialy" << endl;
            cin >> ledChoice;

            //obliczanie wartoaci rezystora w zaleznosci od wybranego koloru
            if (ledChoice == 1)
            {
                ledResistance = led.resistanceLED(V, I, "red");//metoda z klasy calculations
                cout << "----[ R ]----------->|------" << endl;
                cout << "   rezystor        LED" << endl;
                cout << "" << endl;
                cout << "Wartosc opornika (R) przy napieciu zasilania: " << V <<
                    " [V], " << endl << "oraz maksymalnym pradzie: " << I << "[mA]," << endl << "dla LEDa o kolorze czerwonym wynosi: " << ledResistance << " Om" << endl;
                cout << "" << endl;
                cout << "" << endl;
            }
            else if (ledChoice == 2)
            {
                ledResistance = led.resistanceLED(V, I, "blue");
                cout << "----[ R ]----------->|------" << endl;
                cout << "   rezystor        LED" << endl;
                cout << "" << endl;
                cout << "Wartosc opornika przy napieciu zasilania: " << V <<
                    " [V], " << endl << "oraz maksymalnym pradzie: " << I << "[mA]," << endl << "dla LEDa o kolorze niebieskim wynosi: " << ledResistance << " Om" << endl;
                cout << "" << endl;
                cout << "" << endl;
            }
            else if (ledChoice == 3)
            {
                ledResistance = led.resistanceLED(V, I, "yellow");
                cout << "----[ R ]----------->|------" << endl;
                cout << "   rezystor        LED" << endl;
                cout << "" << endl;
                cout << "Wartosc opornika przy napieciu zasilania: " << V <<
                    " [V], " << endl << "oraz maksymalnym pradzie: " << I << "[mA]," << endl << "dla LEDa o kolorze zoltym wynosi: " << ledResistance << " Om" << endl;
                cout << "" << endl;
                cout << "" << endl;
            }
            else if (ledChoice == 4)
            {
                ledResistance = led.resistanceLED(V, I, "green");
                cout << "----[ R ]----------->|------" << endl;
                cout << "   rezystor        LED" << endl;
                cout << "" << endl;
                cout << "Wartosc opornika przy napieciu zasilania: " << V <<
                    " [V], " << endl << "oraz maksymalnym pradzie: " << I << "[mA]," << endl << "dla LEDa o kolorze zielonym wynosi: " << ledResistance << " Om" << endl;
                cout << "" << endl;
                cout << "" << endl;
            }
            else if (ledChoice == 5)
            {
                ledResistance = led.resistanceLED(V, I, "white");
                cout << "----[ R ]----------->|------" << endl;
                cout << "   rezystor        LED" << endl;
                cout << "" << endl;
                cout << "Wartosc opornika przy napieciu zasilania: " << V <<
                    " [V], " << endl << "oraz maksymalnym pradzie: " << I << "[mA]," << endl << "dla LEDa o kolorze bialym wynosi: " << ledResistance << " Om" << endl;
                cout << "" << endl;
                cout << "" << endl;
            }
            else
            {
                cout << "Podano nieprawidlowy wybor, sprobuj jeszcze raz" << endl;
                cout << "" << endl;
            }
            break;

        case 4:
            cout << "Wybrales opcje dzielnika napiecia oraz pradu" << endl;
            cout << "--------------------------------------------" << endl;
            cout << "Wybierz, ktory dzielnik chcesz wykorzystac:" << endl;
            cout << "" << endl;
            cout << "1. Dzielnik napiecia" << endl;
            cout << "2. Dzielnik pradu" << endl;
            cout << "" << endl;
            cin >> divChoice;

            // kod pobierajacy dane oraz sprawdzajacy czy wpisane wartosci sa liczba

            if (divChoice == 1)  //dzielnik napiecia
            {
                while (true)
                {
                    cout << "Podaj napiecie zasilania dla rezystorow(w woltach): " << endl;
                    if (cout << "Twoje napiecie: "; cin >> V1)
                    {
                        if (V1 > 0)
                            break;
                        else cout << "Napiecie nie moze byc ujemne badz rowne 0" << endl;

                    }
                    else
                    {
                        cout << "Niepoprawna wartosc napiecia, sprobuj ponownie" << endl;
                        cout << "" << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }

                }

                readResistor.readResistorSecurity("R1", R1);  //metoda z klsy Calculations, 
                readResistor.readResistorSecurity("R2", R2);  //sprawdzajaca poprawnosc tego co wpisujemy przy podawaniu rezystancji

                voltages = volt.voltageDivider(R1, R2, V1);  //metoda z klasy Calculations
                cout << "" << endl;
                cout << "Przy napieciu zasilania: " << V1 << "V" << endl;
                cout << "Napiecie na rezystorze R1 wynosi: " << voltages[0] << " V" << endl;
                cout << "Napiecie na rezystorze R2 wynosi: " << voltages[1] << " V" << endl;

                cout << "" << endl;
                cout << "" << endl;

            }
            else if (divChoice == 2) 
            {
                // kod pobierajacy dane oraz sprawdzajacy czy wpisane wartosci sa liczba

                while (true)// dzielnik pradu
                {
                    cout << "Podaj prad calkowity jaki poplynie przez dzielnik (w Amperach): " << endl;
                    if (cout << "Prad: "; cin >> I1)
                    {
                        if (I1 > 0)
                            break;
                        else  cout << "Prad nie moze byc równy badz mniejszy od 0" << endl;
                    }
                    else
                    {
                        cout << "Niepoprawna wartosc pradu, sprobuj ponownie" << endl;
                        cout << "" << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }

                }

                readResistor.readResistorSecurity("R1", R1);  //metoda z klsy Calculations
                readResistor.readResistorSecurity("R2", R2);  //sprawdzajaca poprawnosc tego co wpisujemy przy podawaniu rezystancji

                currents = curr.currentDivider(R1, R2, I1);  //metoda z klasy Calculations
                cout << "" << endl;
                cout << "Przy pradzie calkowitym: " << I1 << "A" << endl;
                cout << "Prad na rezystorze R1 wynosi: " << currents[0] << " A" << endl;
                cout << "Prad na rezystorze R2 wynosi: " << currents[1] << " A" << endl;

                cout << "" << endl;
                cout << "" << endl;
            }
            else
                cout << "Podano nieprawidlowy wybor, sprobuj jeszcze raz" << endl;
            cout << "" << endl;
            cout << "" << endl;


            break;

        case 5:
            //wyłaczenie kalkulatora
            cout << "Wyjscie z programu" << endl;
            return 0;

            //informacja o złym wyborze dla głownego MENU
        default:
            cout << "Niepoprawny wybor, sprobuj ponownie" << endl;
            cout << "" << endl;
            break;

        }
    }

}