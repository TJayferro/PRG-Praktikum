#include <iostream>
#include <string>


using namespace std;


class GameOfLife{
    public:
        GameOfLife(int hoehe, int breite, int datei);   //Constructor
        void changeSize(int hoehe, int breite);   //Spielfeldgröße ändern
        void changeCell(int row, int column, bool state);   //Zustand ändern
        void cycle();  //Ein Durchlauf
        void printField();  //Feld anzeigen lassen

    private:
        int width;
        int height;
        char **oldField;
        char **newField;

};


//Constructor der Klasse, erstellt das Spielfeld mit angegebener Höhe,Breite oder liest aus Datei
GameOfLife::GameOfLife(int newHeight, int newWidth, int datei){
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
            oldField[i][j] = '0';
            newField[i][j] = '0';
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
                newField[i][j] = 0;
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
            newField[row][column] = '0';
        }
    }
    else{
        cout << "Angegebener Index ist zu groß.";
    }
}


int main(){
    cout << "test\n";
    GameOfLife test (30, 30, 0);
    test.printField();
    test.changeSize(10, 10);
    test.changeCell(0, 0, true);
    test.printField();
    
    return 0;
}
