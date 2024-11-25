#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

char currentUnit;

// Temperature convertion functions
double celsiusToFahrenheit(double celsius)
{
    return (celsius * 9 / 5) + 32;
}

double fahrenheitToCelsius(double fahrenheit)
{
    return (fahrenheit - 32) * 5 / 9;
}

double celsiusToKelvin(double celsius)
{
    return celsius + 273.15;
}

double kelvinToCelsius(double kelvin)
{
    return kelvin - 273.15;
}

// Global converter function
double globalConverter(double temperature, const char unitIn, const char unitOut){
    if(unitIn == unitOut)
    {
        return temperature;
    }
    
    if (unitIn == 'C'){
        if (unitOut == 'F')
        {
            return celsiusToFahrenheit(temperature);
        } else {
            return celsiusToKelvin(temperature);
        }
    } else if (unitIn == 'F') {
        if(unitOut == 'C') {
            return fahrenheitToCelsius(fahrenheitToCelsius(temperature));
        } else {
            return celsiusToKelvin(temperature);
        }
    } else {
        if (unitIn == 'C'){
            return kelvinToCelsius(temperature);
        } else {
            return celsiusToKelvin(kelvinToCelsius(temperature));
        }
    }
    return temperature; // Fallback
}

// unit validifier
char isValidUnit(string prompt){
    char unit;
    while(true){
        cout << prompt << endl;
        cin >> unit;
        if(unit == 'C' || unit == 'F' || unit == 'K')
        {
            return unit;
        }
        cout << "\nInvalid unit! Enter enter C for Celsius, F for Fahrenheit, and K for Kelvin\n" << endl;
    }
}

// gets temperature full name based on initials
string getTemperatureUnit(char initial)
{
    if (initial == 'C'){
        return "Celsius";
    }
    if (initial == 'F'){
        return "Fahrenheit";
    }
    if (initial == 'K'){
        return "Kelvin";
    }
    return "Unknown unit";
}

// Validates temperature is above absolute zero
bool isValidTemp(double temp, char unit)
{
    if (unit == 'C' || unit == 'K')
    {
        return temp >= -273.15;
    } else if (unit == 'F'){
        return fahrenheitToCelsius(temp) >= -273.15;
    }
    return false;
}

//format user's input
void getUserInput(double& temp, char& unitIn, char& unitOut)
{
    do{
        cout << "what is the inital temperature (number): " << endl;
        cin >> temp;
        unitIn = isValidUnit("Enter an input unit (enter C for Celsius, F for Fahrenheit, and K for Kelvin):\n");
        
        if (!isValidTemp(temp, unitIn)) {
            cout << "Invalid temperature! Please enter a temperature above absolute zero";
            cout << endl;
        }
    } while(!isValidTemp(temp, unitIn));
    unitOut = isValidUnit("Enter an output unit (enter C for Celsius, F for Fahrenheit, and K for Kelvin):\n");
    cout << endl;
}

// generates random temperature based off of users desired range
double generateRandomTemperature(char unit, double lowerLimit, double upperLimit){
    double temp;
    srand(static_cast<unsigned>(time(0)));
    
    do{
        // generates random number in within range
        temp = static_cast<double>(rand()) / RAND_MAX * (upperLimit - lowerLimit) + lowerLimit;
        
        // checks if the generated temperature is valid based on units
        if(!isValidTemp(temp, unit))
        {
            cout << "Generate temperature " << fixed << setprecision(2) << temp << " is invalid for " << unit << ". Please enter valid limits." << endl;
            
            cout << "Enter a new lower limit:" << endl;
            cin >> lowerLimit;
            
            cout << "Enter a new upper limit:" << endl;
            cin >> upperLimit;
            
            // ensure upper limit isn't greater then lower limit
            if(upperLimit <= lowerLimit)
            {
                cout << "Upper limit must be greater than lower limit." << endl;
                continue;
            }
        }
        
    }while(!isValidTemp(temp, unit)); // repeat until user properly generates temperature
    
    return temp;
}

//adds current temperature to list and auto converts based on current list unit
void addToList(double tempList[], int & currentSize, int listSize, double temp, char currentUnit, char listUnit){
    if (temp == -9999){
        cout << "There is currently no temperature to be added to the list."  << endl;
    } else if(currentSize < listSize){
        char confirm;
        cout << "The current unit of the list is " << getTemperatureUnit(currentUnit) << endl;
        cout << "Do you want to add " << temp << " " << getTemperatureUnit(currentUnit) << " (Y for Yes and N for no)" << endl;
        cin >> confirm;
        
        switch(confirm){
            case 'Y':
                if (currentUnit == listUnit){
                    tempList[currentSize] = temp;
                    currentSize++;
                    cout << temp << " " << currentUnit << " has been added to the list." << endl;
                } else {
                    double convertedUnit = globalConverter(temp, currentUnit, listUnit);
                    tempList[currentSize] = convertedUnit;
                    currentSize++;
                    cout << "Temperature entered, " << temp << " " << getTemperatureUnit(currentUnit) << " has been converted to " << convertedUnit << " " << listUnit << endl;
                }
                break;
            case 'N':
                cout << "Temperature not added" << endl;
                break;
            default:
                cout << "invalid input, add temperature aborted" << endl;
                break;
        }
        
        
    } else {
        cout << "List is full, Cannot add more temperatures" << endl;
    }
}

//averages the temperatures in list
double listAverage(double tempList[], int size){
    if (size == 0){
        cout << "There are no temperatures stored in the list currently" << endl;
        return 0;
    } else {
        double avg = 0;
        for(int i = 0; i <= size; i ++){
            avg = avg + tempList[i];
        }
        return avg/size;
    }
}

//print all temperatures in list
void printTemperatures(double tempList[], int size, char unit){
    if (size == 0){
        cout << endl;
        cout << "There are no temperatures stored in the list currently" << endl;
        cout << endl;
        return;
    } else {
        for(int i = 0; i <= size; i++){
            cout << " Temperature is: " << i + 1 << tempList[i] << " " << getTemperatureUnit(unit) << endl;
        }
    }
}

// changes the temperature units of list to desired unit
void changeListTemperature(char &currentUnit, char newUnit){

    while (currentUnit == newUnit){
        cout << "Redudant Conversion, Please choose a unit that is not "<< getTemperatureUnit(currentUnit) << " " << endl;
        cout << "Please enter a new unit that is not " << getTemperatureUnit(currentUnit) << " (C for Celsius, F for Fahrenheit, K for Kelvin)" <<endl;
        cin >> newUnit;
        cout << endl;
    }
    
    char confirmation;
    while(true){
        
        cout << "The current unit is " << getTemperatureUnit(currentUnit) << endl;
        cout << "Are you sure You want to change the unit? (Y for Yes, N for No)" << endl;
        cin >> confirmation;
        
        if(confirmation == 'Y' || confirmation == 'y'){
            currentUnit = newUnit;
            cout << "The new temperature list unit is " << getTemperatureUnit(newUnit) << endl;
            cout << endl;
            break;
        } else if (confirmation == 'N' || confirmation == 'n'){
            cout << "Unit is unchange, operation aborted" << endl;
            cout << endl;
            break;
        } else {
            cout << "Invalid input, please enter Y for yes N for no" << endl;
            cout << endl;
        }
    }
}


int main(){
    bool quit = false;
    int choice = 0;
    double temperature = 0;
    
    char unitIn;
    char unitOut;
    
    char listUnit = 'C';
    double currentTemperature = -9999;
    double temperatureStorage[100];
    
    int currentSize = 0;
    int listSize = sizeof(temperatureStorage) / sizeof(temperatureStorage[0]);
    
    // brief introduction and intructions
    cout << "Hello, welcome to Temperature Converter Plus!" << endl;
    cout << "Type the number representing each of the operation to get started\n" << endl;
    
    do{
        // display menu
        cout << "(1) any temperature to any temperature" << endl;
        cout << "(2) generate a random temperature" << endl;
        cout << "(3) add current temperature to list (auto converts to current unit and can add up to 100 temperatures)" << endl;
        cout << "(4) change unit of list" << endl;
        cout << "(5) list average" << endl;
        cout << "(6) display list of current temperatures" << endl;
        cout << "(7) Quit\n" << endl;
        cout << "Enter your selection:" << endl;
        cin >> choice;
        
        switch(choice)
        {
            case 1:
            {
                getUserInput(temperature, unitIn, unitOut);
                double convertedTemp = globalConverter(temperature, unitIn, unitOut);
                cout << temperature << " " << getTemperatureUnit(unitIn) << " is " << convertedTemp << " " << getTemperatureUnit(unitOut) << endl;
                
                currentTemperature = convertedTemp;
                currentUnit = unitOut;
                break;
            }
            case 2:
            {
                char unit;
                double lowerLimit;
                double upperUnit;
                
                unit = isValidUnit("Enter the temperature unit (enter C for Celsius, F for Fahrenheit, and K for Kelvin)");
                cout << endl;
                cout << "Enter lower limit for temperature:" << endl;
                cin >> lowerLimit;
                cout << "Enter upper limit for temperature:" << endl;
                cin >> upperUnit;
                
                double randomTemp = generateRandomTemperature(unit, lowerLimit, upperUnit);
                cout << endl;
                cout << "Your random temperature is " << fixed << setprecision(2) << randomTemp << " " << getTemperatureUnit(unit) << endl;
                currentTemperature = randomTemp;
                currentUnit = unit;
                
                break;
            }
                
            case 3:
                addToList(temperatureStorage, currentSize, listSize, currentTemperature, currentUnit, listUnit);
                break;
                
            case 4:
            {
                char newUnit;
                cout << "what should the new list unit be?" << endl;
                cin >> newUnit;
                changeListTemperature(listUnit, newUnit);
                listUnit = newUnit;
                break;
            }
            case 5:
            {
                double average = listAverage(temperatureStorage, currentSize);
                cout << "The current average of the the list is " << average << " " << getTemperatureUnit(currentUnit) << endl;
                break;
            }
            case 6:
                printTemperatures(temperatureStorage, currentSize, currentUnit);
                break;

            case 7:
                cout << "Thank you for using this calculator have a nice day!" << endl;
                quit = true;
                break;
                
            default:
                cout << "invalid option please select a number in the menu" << endl;

        }
    }while(quit != true);
    
    return 0;
}
