#include <iostream>
#include <string>

using namespace std;

//Funktion erstellt ein zweidimensionales Array und returned den Pointer des Pointers der ersten Zeile
int** get_stat_array(){
    int i,j;
    int** stat_array = new int*[30];
    for(i=0; i<30; i++){
        stat_array[i] = new int[30];
        for(j=0; j<30; j++){
            stat_array[i][j] = rand() % 10;
        }
    }
    return stat_array;
}

//Funktion nimmt ein zweidimensionales Array und returned ein eindimensionales Array mit kopierten Werten
int* get_dyn_array(int** stat_array){
    int i,j;
    int index = 0;
    int* dyn_array = new int[30*30];
    for(i=0; i<30; i++){
        for(j=0; j<30; j++){
            dyn_array[index] = stat_array[i][j];
            index++; 
        }
    }
    return dyn_array;
}

//Print eines zweidimensionalen statischen Arrays
void print_stat_array(int** stat_array){
    for(int i=0; i<30; i++){
        for(int j=0; j<30; j++){
            cout << stat_array[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

//Print eines eindimensionalen dynamischen Arrays
void print_dyn_array(int* dyn_array){
    for(int i=0; i<30*30; i++){
        cout << dyn_array[i] << " ";
    }
    cout << "\n";
}

//Mainfunktioen
int main() 
{
    int **stat_array;   //deklarieren des statischen 2d Arrays
    int *dyn_array;     //deklarieren des dynamsichen 1d Arrays
    string user_input;      //deklarieren des User inputs
    bool stat_array_enable = false;     //definieren der Bool Variable ob ein statisches Array definiert wird
    bool dyn_array_enable = false;      //definieren der Bool Variable ob ein dynamisches Array definiert wird

    cout << "Type 'help' for more information\n";    //Erste Nachricht
    //Beginn des Konsolenprogramms durch Endlosschleife
    while(true){
        cout << ">>> ";     //Zeilenanfang des Konsolenprogramms zur Kenntlichkeit 
        cin >> user_input;  //Abfrage des Inputs

        //Fälle, jenachdem was der User eingibt, wird das Programm ihm etwas ausspucken
        //Help Funktion
        if(user_input == "help"){  
            cout << "'star' := erstellt statisches Array\n";
            cout << "'dyar' := kopiert statisches in ein dynamisches Array\n";
            cout << "'printsa' := print statisches Array\n";
            cout << "'printda' := print dynamisches Array\n";
        }

        else if(user_input == "star"){
            cout << "Statisches Array wurde erstellt\n";
            stat_array = get_stat_array();
            stat_array_enable = true;
        }

        else if(user_input == "dyar" and stat_array_enable){
            cout << "Dynamisches Array wurde erstellt und statisches Array kopiert\n";
            dyn_array = get_dyn_array(stat_array);
            dyn_array_enable = true;
        }

        //Falls es noch kein statisches Array zum kopieren gibt, wird das abgefangen
        else if(user_input == "dyar" and !stat_array_enable){
            cout << "Noch kein statisches Array erstellt\n";
        }

        else if(user_input == "printsa" and stat_array_enable){
            print_stat_array(stat_array);
        }

        else if(user_input == "printsa" and !stat_array_enable){
            cout << "Noch kein statisches Array erstellt\n";
        }

        else if(user_input == "printda" and dyn_array_enable){
            print_dyn_array(dyn_array);
        }
        else if(user_input == "printda" and !dyn_array_enable){
            cout << "Noch kein dynamisches Array erstellt\n";
        }

        //Beenden des Programms
        else if(user_input == "exit"){
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