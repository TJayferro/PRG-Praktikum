#include <iostream>
#include <string>

using namespace std;



class MyFirstClass{
    public:
        MyFirstClass();
        void getStaticArray();
        void getDynamicArray();
        void printStaticArray();
        void printDynamicArray();
    private:
        int staticArray[30][30];
        int* dynamicArray = new int[30*30]; 
        bool dynamicArrayEnable;
        bool staticArrayEnable;
};

//Constructor
MyFirstClass::MyFirstClass(){
    dynamicArrayEnable = false;
    staticArrayEnable = false;
}

//Verteilt zufällige Zahlen auf das statische Array
void MyFirstClass::getStaticArray(){
    int i,j;
    for(i=0; i<30; i++){
        for(j=0; j<30; j++){
            staticArray[i][j] = rand() % 10;
        }
    }
    staticArrayEnable = true;
}

//Kopiert wenn möglich alle Werte des statischen in ein dynamisches Array
void MyFirstClass::getDynamicArray(){
    if(staticArrayEnable){
        int i,j;
        int index = 0;
        for(i=0; i<30; i++){
            for(j=0; j<30; j++){
                dynamicArray[index] = staticArray[i][j];
                index++; 
            }
        }
        dynamicArrayEnable = true;
    }
    else{
        cout << "Noch kein statisches Array erstellt\n";
    }
}

//Printausgabe des statischen Arrays
void MyFirstClass::printStaticArray(){
    if(staticArrayEnable){
        for(int i=0; i<30; i++){
            for(int j=0; j<30; j++){
                cout << staticArray[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    else{
        cout << "Noch kein statisches Array erstellt\n";
    }
}

//Printausgabe des dynamischen Arrays
void MyFirstClass::printDynamicArray(){
    if(dynamicArrayEnable){
        for(int i=0; i<30*30; i++){
            cout << dynamicArray[i] << " ";
        }
        cout << "\n";
    }
    else{
        cout << "Noch kein dynamisches Array erstell\n";
    }
}



//Mainfunktioen
int main() 
{
    
    string userInput;      //deklarieren des User inputs
    MyFirstClass test;      //Initialisierung des Klassenelements

    cout << "Type 'help' for more information\n";    //Erste Nachricht
    //Beginn des Konsolenprogramms durch Endlosschleife
    while(true){
        userInput.clear();
        cout << ">>> ";     //Prompt des Konsolenprogramms zur Kenntlichkeit
        cin >> userInput;  //Abfrage des Inputs

        //Fälle, jenachdem was der User eingibt, wird das Programm ihm etwas ausspucken
        //Help Funktion
        if(userInput == "help"){  
            cout << "'star' := Erstellt ein statisches Array\n";
            cout << "'dyar' := Kopiert das statische in ein dynamisches Array\n";
            cout << "'printsa' := Printausgabe des statischen Array\n";
            cout << "'printda' := Printausgabe des dynamischen Array\n";
            cout << "'exit' := Beendet das Programm";
        }

        else if(userInput == "star"){
            cout << "Statisches Array wurde erstellt\n";
            test.getStaticArray();
        }

        else if(userInput == "dyar"){
            cout << "Dynamisches Array wurde erstellt und statisches Array kopiert\n";
            test.getDynamicArray();
        }


        else if(userInput == "printsa"){
            test.printStaticArray();
        }

        
        else if(userInput == "printda"){
            test.printDynamicArray();
        }

        //Beenden des Programms
        else if(userInput == "exit"){
            cout << "Exiting program\n";
            break; 
        }

        //Alle anderen Befehle werden abgefangen
        else{
            cout << "Befehl ungültig\n";
            cout << "Type 'help' for more information\n";
        }

    }

    return 0;
} 