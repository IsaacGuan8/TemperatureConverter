// Standard C++ libraries
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cmath>

using namespace std;

char currentUnit;

// Constants for absolute zero for different temperatures units
const double ABSOLUTE_ZERO_C = -273.15;
const double ABSOLUTE_ZERO_F = -459.67;
const double ABSOLUTE_ZERO_K = 0.0;

// Function converts from celsius to Fahrenheit
double celsiusToFahrenheit(double celsius)
{
    return (celsius * static_cast<double>(9) / 5) + 32;
}

// Functions converts from fahrenheit to celsius
double fahrenheitToCelsius(double fahrenheit)
{
    return (fahrenheit - 32) * static_cast<double>(5) / 9;
}

// Functions converts from celsius to kelvin
double celsiusToKelvin(double celsius)
{
    return celsius + 273.15;
}

// Functions converts from kelvin to fahrenheit
double kelvinToCelsius(double kelvin)
{
    return kelvin - 273.15;
}

// Function converts temperature based on the units in and desired unit output
double convertTemperatureBasedOnUnits(double temperature, const char unitIn, const char unitOut){
    if(unitIn == unitOut){
        return temperature;
    }
    
    if(unitIn == 'C'){
        return (unitOut == 'F') ? celsiusToFahrenheit(temperature) : celsiusToKelvin(temperature);
    }
    if(unitIn == 'F'){
        return (unitOut == 'C') ? fahrenheitToCelsius(temperature) : celsiusToKelvin(fahrenheitToCelsius(temperature));
    }
    if (unitIn == 'C'){
       return (unitOut == 'C') ? kelvinToCelsius(temperature) : celsiusToFahrenheit(kelvinToCelsius(temperature));
    }
    return temperature; // Fallback
}

// Function validates temperature unit to ensure initals are used outside of ones representing temperatures
char isValidUnit(string prompt){
    char unit;
    while(true){
        cout << prompt << endl;
        cin >> unit;
        if(unit == 'C' || unit == 'F' || unit == 'K'||unit == 'c' || unit == 'f' || unit == 'k')
        {
            return unit;
        }
        cout << "Invalid unit! Enter enter C for Celsius, F for Fahrenheit, and K for Kelvin" << endl;
    }
}

// Functions gets temperatures full name from initial
string getTemperatureUnit(char initial)
{
    if (initial == 'C' || initial == 'c'){
        return "Celsius";
    }
    if (initial == 'F' || initial == 'f'){
        return "Fahrenheit";
    }
    if (initial == 'K' || initial == 'k'){
        return "Kelvin";
    }
    return "Unknown unit";
}

// Function validates temperature is above absolute zero
bool isValidTemp(double temperature, char unit){
    if(unit == 'C' || unit =='c') return temperature >= ABSOLUTE_ZERO_C;
    if(unit == 'F' || unit =='f') return temperature >= ABSOLUTE_ZERO_F;
    if(unit == 'K' || unit =='k') return temperature >= ABSOLUTE_ZERO_K;
    return false; // Invalid unit
}

// Function formats user's input
void getUserInput(double& temp, char& unitIn, char& unitOut)
{
    do{
        cout << "what is the inital temperature (number): " << endl;
        cin >> temp;
        unitIn = isValidUnit("Enter an input unit (enter C for Celsius, F for Fahrenheit, and K for Kelvin):");
        
        if(!isValidTemp(temp, unitIn)){
            cout << "Invalid temperature! Please enter a temperature above absolute zero";
            cin >> temp;
            cout << endl;
        }
    }while(!isValidTemp(temp, unitIn));
    unitOut = isValidUnit("Enter an output unit (enter C for Celsius, F for Fahrenheit, and K for Kelvin):");
    cout << endl;
}

// Function generates random temperature based off of users desired range
double generateRandomTemperature(double lower, double upper){
    return lower + static_cast<double>(rand()) / RAND_MAX * (upper - lower);
}

// Function adds current temperature to list and auto converts based on current list unit
void addToList(double tempList[], int & currentSize, int& listSize, double temp, char currentUnit, char listUnit){
    if(temp == -9999){
        cout << "There is currently no temperature to be added to the list."  << endl;
    }else if(currentSize < listSize){
        char confirm;
        cout << "The current unit of the list is " << getTemperatureUnit(currentUnit) << endl;
        cout << "Do you want to add " << temp << " " << getTemperatureUnit(currentUnit) << " (Y for Yes and N for no)" << endl;
        cin >> confirm;
        
        switch(confirm){
            case 'Y':
                if(currentUnit == listUnit){
                    tempList[currentSize] = temp;
                    currentSize++; // Increment size to keep index current when diplaying temperatures
                    cout << temp << " " << getTemperatureUnit(currentUnit) << " has been added to the list." << endl;
                }else{
                    double convertedUnit = convertTemperatureBasedOnUnits(temp, currentUnit, listUnit);
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
    }else{
        cout << "List is full, Cannot add more temperatures" << endl;
    }
}

// Functions returns average of the temperatures in list
double listAverage(double tempList[], int size){
    if(size == 0){
        cout << "There are no temperatures stored in the list currently" << endl;
        return 0;
    }else{
        double avg = 0;
        for(int i = 0; i < size; i ++){
            avg = avg + tempList[i];
        }
        return avg/size;
    }
}

// Function displays all temperatures in list
void printTemperatures(double tempList[], int size, char unit){
    if(size == 0){
        cout << endl;
        cout << "There are no temperatures stored in the list currently" << endl;
        cout << endl;
        return;
    }else{
        cout << setw(10) << "Index" << setw(20) << "Temperature" << setw(15) << "Unit" << endl;
        for(int i = 0; i < size; i++){
            cout << setw(10) << i + 1 << setw(20) << tempList[i] << setw(15)<< getTemperatureUnit(unit) << endl;
        }
    }
}

// Function that converts the list of temperature to another unit (Celsius, Fahrenheit, or Kelvin"
void convertTemperatureList(double tempList[], int size, char currentUnit, char targetUnit){
    for(int i = 0; i < size; ++i){
        tempList[i] = convertTemperatureBasedOnUnits(tempList[i], currentUnit, targetUnit);
    }

    cout << "All temperatures have been converted to " << getTemperatureUnit(targetUnit) << "." << endl;
}

// Functions changes the temperature units of list to desired unit
void changeListTemperature(double tempList[], int size, char &currentUnit, char newUnit){
    if(currentUnit == newUnit){
            cout << "The list is already in " << getTemperatureUnit(currentUnit) << ". No changes made.\n";
            return;
        }
    
    char confirmation;
    while(true){
        cout << "Are you sure you want to change the unit to " << getTemperatureUnit(newUnit) << "? (Y/N):" << endl;
        cin >> confirmation;
        if(confirmation == 'Y' || confirmation == 'y'){
            convertTemperatureList(tempList, size, currentUnit, newUnit);
            currentUnit = newUnit;
            cout << "The list unit has been updated to " << getTemperatureUnit(newUnit) << endl;
            break;
        }else if(confirmation == 'N' || confirmation == 'n'){
            cout << "Unit change aborted" << endl;
            break;
        }else{
            cout << "Invalid input. Please enter Y or N.\n";
        }
    }
}

// Function returns the current temperatures lists unit
string getCurrentListUnit(char listUnit){
    return getTemperatureUnit(listUnit);
}

// Function to clear the current list by setting all temperatures slots to 0
void clearTemperatureList(double tempList[], int &currentSize){
    for(int i = 0; i < currentSize; ++i) {
        tempList[i] = std::nan(""); // Assign Not-a-Number to each element
    }
    currentSize = 0; // Reset current size to 0
    cout << "All temperatures have been cleared from the list.\n";
}

int main(){
    srand(static_cast<unsigned>(time(0)));
    bool quit = false;
    int choice = 0;
    double temperature = 0;
    
    char unitIn;
    char unitOut;
    
    char listUnit = 'C'; // Default starting unit for the list
    double currentTemperature = -9999; //
    double temperatureStorage[100];
    
    int currentSize = 0;
    int listSize = sizeof(temperatureStorage) / sizeof(temperatureStorage[0]);
    
    // Brief introduction and intructions
    cout << "Hello, welcome to Temperature Converter Plus!" << endl;
    cout << "Type the number representing each of the operation to get started\n" << endl;
    
    do{
        // Display menu
        cout << "(1) Any temperature to any temperature" << endl;
        cout << "(2) Generate a random temperature" << endl;
        cout << "(3) Add current temperature to list (auto converts to current unit and can add up to 100 temperatures)" << endl;
        cout << "(4) Change unit of list" << endl;
        cout << "(5) List average" << endl;
        cout << "(6) Display list of current temperatures" << endl;
        cout << "(7) Get current temperature list's unit" << endl;
        cout << "(8) Clear temperature list of all values" << endl;
        cout << "(9) Quit\n" << endl;
        cout << "Enter your selection:" << endl;
        
        // Validate integer input
        while(!(cin >> choice)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
            cout << "Invalid input! Please enter an integer: " << endl;
        }
        
        switch(choice)
        {
            case 1:
            {
                getUserInput(temperature, unitIn, unitOut);
                double convertedTemp = convertTemperatureBasedOnUnits(temperature, unitIn, unitOut);
                cout << temperature << " " << getTemperatureUnit(unitIn) << " is " << convertedTemp << " " << getTemperatureUnit(unitOut) << endl;
                
                // Update current temperature and unit
                currentTemperature = convertedTemp;
                currentUnit = unitOut;
                break;
            }
                
            case 2:
            {
                char unit;
                double lowerLimit;
                double upperLimit;
                
                unit = isValidUnit("Enter the temperature unit (enter C for Celsius, F for Fahrenheit, and K for Kelvin)");
                // Makes sure upper and lower limit are logical (lower limit is smaller than upper limit)
                do{
                    cout << "Enter lower limit for temperature:" << endl;
                    cin >> lowerLimit;
                    cout << "Enter upper limit for temperature:" << endl;
                    cin >> upperLimit;
                    if(lowerLimit >= upperLimit){
                        cout << "Lower bound must be less than upper bound. Try again." << endl;
                    }
                }while (lowerLimit >= upperLimit);
                
                double randomTemp = generateRandomTemperature(lowerLimit, upperLimit);
                cout << "Your random temperature is " << fixed << setprecision(2) << randomTemp << " " << getTemperatureUnit(unit) << endl;
                
                // Update current temperature and unit
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
                cout << "what should the new list unit be? (enter C for Celsius, F for Fahrenheit, and K for Kelvin)" << endl;
                cin >> newUnit;
                
                while(newUnit == currentUnit){
                    cout << "Please ask for a unit different from the current unit of " << getTemperatureUnit(currentUnit) << endl;
                    cin >> newUnit;
                }
                
                changeListTemperature(temperatureStorage, listSize, currentUnit, newUnit);
                listUnit = newUnit;
                break;
            }
                
            case 5:
            {
                if(currentSize == 0){
                    cout << "No Temperatures in list to calculate" << endl;
                }else{
                    double average = listAverage(temperatureStorage, currentSize);
                    cout << "The current average temperature of the the list is " << average << " " << getTemperatureUnit(currentUnit) << endl;
                }
                break;
            }
                
            case 6:
                printTemperatures(temperatureStorage, currentSize, currentUnit);
                break;

            case 7:
                cout << "The current list unit is " << getCurrentListUnit(listUnit) << "." << endl;
                break;
                
            case 8:
            {
                char confirmation;
                while(true){
                    cout << "Are you sure you want to clear all temperatures from list?(Y for yes, N for No)" << endl;
                    cin >> confirmation;
                    
                    if(confirmation == 'Y' || confirmation == 'y'){
                        clearTemperatureList(temperatureStorage, currentSize);
                        cout << "Temperature list cleared" << endl;
                        break;
                    }else if(confirmation == 'N' || confirmation == 'n'){
                        cout << "Clear list aborted" << endl;
                        break;
                    }else{
                        cout << "Please choose a valid choice(Y for yes, N for No)" << endl;
                    }
                }
                break;
            }
                
            case 9:
                cout << "Thank you for using this calculator have a nice day!" << endl;
                quit = true;
                break;
                
            default:
                cout << "invalid option please select a number in the menu" << endl;

        }
    }while(quit != true);
    return 0;
}
