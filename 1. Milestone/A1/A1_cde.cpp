#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


using namespace std;

//Klasse des Game of Life
class GameOfLife{
    public:
        GameOfLife(int hoehe, int breite);   //Constructor
        void changeSize(int hoehe, int breite);   //Spielfeldgröße ändern
        void changeCell(int row, int column, bool state);   //Zustand ändern
        void cycle();  //Ein Durchlauf
        void printField();  //Feld anzeigen lassen
        void reset();    //Lässt alle Zellen sterben
        void importField(string fileName);
        void exportField(string fileName);

    private:
        int width;
        int height;
        char **oldField;
        char **newField;

};


//Constructor der Klasse, erstellt das Spielfeld mit angegebener Höhe,Breite oder liest aus Datei
GameOfLife::GameOfLife(int newHeight, int newWidth){
    width = newWidth;
    height = newHeight;

    //erstellen der Größe beider Arrays mittels Pointer der auf Pointer zeigt, der auf eine Zeile im Array zeigt
    oldField = new char*[height];
    for(int i = 0; i < height; i++){
        oldField[i] = new char[width];
    }
    newField = new char*[height];
    for(int i = 0; i < height; i++){
        newField[i] = new char[width];
    }

    //automatisches Befüllen beider Arrays mit Nullen/toten Zellen
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            oldField[i][j] = 'o';
            newField[i][j] = 'o';
        }
    }
}


//Änder die Aktuelle Spielfeldgröße und schneidet entweder überschüssigen Rand ab oder fügt neue Zeilen oder Spalten mit toten Zellen hinzu
void GameOfLife::changeSize(int newHeight, int newWidth){
    //Kopieren des neuen ins alte Feld
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            oldField[i][j] = newField[i][j];
        }
    }

    //Neue Größen werden übertragen auf das neue Feld
    newField = new char*[newHeight];
    for(int i = 0; i < newHeight; i++){
        newField[i] = new char[newWidth];
    }

    //Kopieren der alten Werte in das neue Array
    for(int i = 0; i < newHeight; i++){
        for(int j = 0; j < newWidth; j++){
            if(i < height and j < width){
                //Alte Felder können kopiert werden
                newField[i][j] = oldField[i][j];
            }
            else{
                //Neue Felder müssen aber neu gesetzt werden
                newField[i][j] = 'o';
            }
        }
    }

    //Größenänderung im Alten Array
    oldField = new char*[newHeight];
    for(int i = 0; i < newHeight; i++){
        oldField[i] = new char[newWidth];
    }

    height = newHeight;
    width = newWidth;
}


//wandelt das neue Feld in einen String um und gibt es in der Konsole aus
void GameOfLife::printField(){
    string outputField = "";
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            outputField = outputField + newField[i][j] + " ";
        }
        outputField = outputField + "\n";
    }
    cout << outputField;
}


//Ändert gegebenfalls den Zustand des angegebenen Zelle
void GameOfLife::changeCell(int row, int column, bool state){
    if(row < height and column < width){
        if (state){
            newField[row][column] = '*';
        }
        else{
            newField[row][column] = 'o';
        }
    }
    else{
        cout << "Angegebener Index ist zu groß.";
    }
}


//Alles neue
//Befüllt jede Zelle mit 0 und setzt das Spielfeld zurück
void GameOfLife::reset(){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            newField[i][j] = 'o';
        }
    }
}


//Importiert Spielfeld aus .txt Datei
void GameOfLife::importField(string fileName){

    //Deklarieren gebrauchter Variablen
    int newHeight, newWidth;
    int i, j;
    i = j = 0;
    string line, temp, beep;
    char tempCell;
    ifstream myFile; 
    myFile.open(fileName);
    if (!myFile){
        cout << "Unable to find file\n";
    }
    else{
        while(getline(myFile,line)){
            istringstream temp(line);   //Umwandlung um den string zu splitten

            //Erste Übergabe der Höhe
            if(i == 0){     
                temp >> newHeight;
            }

            //Danach Übergabe der Breite
            else if(i == 1){    
                temp >> newWidth;
                changeSize(newHeight, newWidth);       //Verändert der Spielfeldgröße
            }
            
            //Alle Folgeschritte sind für die Matrix des Spielfeldes   
            else{ 
                j = 0;       
                while(j < newWidth){
                    temp >> tempCell;
                    if (tempCell == '*' or tempCell == 'o'){
                        newField[i-2][j] = tempCell;
                    }
                    else{
                        newField[i-2][j] = 'o';     //Falls andere Zeichen gelesen werden, werden diese als tot gelesen
                    }
                    j++;
                }
            }
            i++;
        }
    }
    
}


//Exportiert aktuelles Spielfeld in .txt Datei
void GameOfLife::exportField(string fileName){
    ofstream myFile(fileName);
    if (myFile.is_open()){

        //Schreiben der Feldgröße
        myFile << height << "\n";
        myFile << width << "\n";
        string outputField = "";

        //Umwandeln des Arrays in einen String, der dann in die Datei geschrieben wird
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                outputField = outputField + newField[i][j] + "";
            }
            outputField = outputField + "\n";
        }
        myFile << outputField;
        myFile.close();
    }
    else cout << "Unable to find file\n";
}


int main(){
    GameOfLife test (30, 30);   //Initialisierung des ersten Spielfelds mit 30x30 Feldern
    string userInput, command, parameter1, parameter2, parameter3, parameterCheck;      //deklarieren des User inputs
    int intParameter1, intParameter2;
    

    cout << "Type 'help' for more information\n";    //Erste Nachricht
    test.importField("beispieldatei_cellularautomaton.txt");
    test.printField();

    //Konsolenprogramm
    while(true){
        //Alle Inputvariablen werden geleert
        userInput.clear();
        command.clear();
        parameter1.clear();
        parameter2.clear();
        parameter3.clear();
        parameterCheck.clear();
        intParameter1 =-1;
        cout << ">>> ";     //Prompt des Konsolenprogramms zur Kenntlichkeit
        getline(cin, userInput);    //Abfrage des Inputs
        istringstream tempInput(userInput);
        tempInput >> command >> parameter1 >> parameter2 >> parameter3 >> parameterCheck;  //String in seine Teile zerlegen
        istringstream tempPara1(parameter1);
        tempPara1 >> intParameter1;
        istringstream tempPara2(parameter2);
        tempPara2 >> intParameter2;


        //Fälle, jenachdem was der User eingibt, wird das Programm ihm etwas ausspucken
        //Help Funktion
        if(command == "help" and parameter1 == ""){  
            cout << "'field' <Höhe> <Breite> := Ändert die Spielfeldgröße auf die neuen Werte\n";
            cout << "'cell' <Zeile> <Spalte> <Zustand> := Ändert den Zustand der angegebenen Zelle. Geben sie dabei 'dead' für tot und 'alive' für lebendig ein\n";
            cout << "'export' <Dateiname> := Exportiert das aktuelle Spielfeld in eine Datei mit angegebenen Dateinamen\n";
            cout << "'import' <Dateiname> := Importiert ein Spielfeld aus einer Datei\n";
            cout << "'cycle' := Berechnet den neuen Zustand des Spielfeldes und gibt die neue Iteration aus";
            cout << "'exit' := Beendet das Programm\n";
        }

        //Spielfeldgröße ändern
        else if(command == "field" and intParameter1 != 0 and intParameter2 != 0 and parameter3 == ""){
            test.changeSize(intParameter1, intParameter2);
            test.printField();
        }

        //Zellenstatus ändern zu lebend
        else if(command == "cell" and parameterCheck == "" and (intParameter1 != 0 or parameter1 == "0") and (intParameter2 != 0 or parameter2 == "0") and parameter3 == "alive"){
            test.changeCell(intParameter1, intParameter2, true);
            test.printField();
        }

        //Zellenstatus ändern zu tot
        else if(command == "cell" and parameterCheck == "" and (intParameter1 != 0 or parameter1 == "0") and (intParameter2 != 0 or parameter2 == "0") and parameter3 == "dead"){
            test.changeCell(intParameter1, intParameter2, false);
            test.printField();
        }

        //Datei Importieren
        else if(command == "import" and parameter2 == ""){
            test.importField(parameter1);
            test.printField();
        }

        //Datei exportieren
        else if(command == "export" and parameter2 == ""){
            test.exportField(parameter1);
        }

        //Eine Iteration des Game of Life
        else if(command == "cycle" \
and parameter1 == ""){
            //Do stuff
        }

        //Beenden des Programms
        else if(command == "exit" and parameter1 == ""){
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

