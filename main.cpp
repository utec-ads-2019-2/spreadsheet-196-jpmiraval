#include <iostream>
#include <string>

using namespace std;

class Spreadsheet{
private:
    int columnas, filas;
    string **casillas;
    int **casillas_resueltas;
    char letras[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

public:
    Spreadsheet(int x, int y): columnas(x), filas(y) {
        casillas = new string *[filas];
        casillas_resueltas = new int*[filas];
        for (int i = 0; i < filas; i++) {
            casillas[i] = new string[columnas];
        }
        for (int i = 0; i < filas; i++) {
            casillas_resueltas[i] = new int[columnas];
        }

}

    int find_valor(char x){
        int contador = 0;
        for(auto c : letras){
            if(c == x){
                return contador;
            }else{
                contador++;
            }
        }
    }

    void llenar_spreadsheet(){
        string x;
        for(int i = 0; i < filas; i++){
            for(int k = 0; k < columnas; k++){
                cin >> x;
                casillas[i][k] = x;
            }
        }
        transformar_cells(casillas);
    }

    void imprimir_spreadsheet(){
        for(int i = 0; i < filas; i++){
            for(int k = 0; k < columnas; k++){
                cout << casillas_resueltas[i][k] << " ";
            }
            cout << endl;
        }
    }

    void transformar_cells(string** casillas){
        int contador = 0;
        string component = "";
        for(int i = 0; i < filas; i++){
            for(int k = 0; k < columnas; k++){
                contador = 0;
                if(casillas[i][k][0] != '='){
                    casillas_resueltas[i][k] = stoi(casillas[i][k]);
                }else{
                    for(auto c : casillas[i][k]){
                        if(c != '=' && c !='+'){
                            component+=c;
                        }else if(c == '+'){
                            contador+=transformar_valor(component);
                            component = "";
                        }

                    }
                    contador+=transformar_valor(component);
                    casillas_resueltas[i][k] = contador;
                    casillas[i][k] = to_string(contador);
                }
            }
        }
    }

    int transformar_valor(string cadena){
        int x = 0, y;
        string component = "";
        for(auto c : cadena ){
            if(!isdigit(c))
                x+= find_valor(c);
            else{
                component = "";
                component += c;
                y = stoi(component);
            }
        }

        return(stoi(casillas[y-1][x]));
    }
};

int main(){

    int num_spreadsheets, x, y;

    cin >> num_spreadsheets;

    for(int i = 0; i < num_spreadsheets; i++){
        cin >> x;
        cin >> y;
        Spreadsheet sheet(x, y);
        sheet.llenar_spreadsheet();
        sheet.imprimir_spreadsheet();

    }

    return 0;
}