#include <iostream>
#include <fstream>
#include<map>
#include<vector>
#include<Enrutadores.h>

using namespace std;

int main()
{
    srand(time(NULL));
    map<string, vector<Enrutador>> Plano;
    map<string, vector<Enrutador>> rutas;
    map<string, vector<Enrutador>> rutasMinimas;

    //Inicio de la simulacion
    unsigned int choice = 0;
    do{
        cout << "Bienvenido a la practica 4" << endl;
        cout << "--------------------------" << endl;
        cout << "1. Agregar un enrutador." << endl;
        cout << "2. Agregar ruta." << endl;
        cout << "3. Eliminar un enrutador." << endl;
        cout << "4. Visualizar enrutadores." << endl;
        cout << "5. Ver tabla." << endl;
        cout << "6. Ver rutas y costos" << endl;
        cout << "7. cambiar costo" << endl;
        cout << "8. Cargar una Red desde un archivo .txt" << endl;
        cout << "9. salir" << endl;
        cout << "--------------------------" << endl;
        cin >> choice;

        if(choice == 1){
            string E1;
            cout << "--------------------------" << endl;
            cout << "AGREGAR ENRUTADOR" << endl;
            cout << "ingrese el nombre del enrutador, solo puede ser una letra" << endl;
            cin >> E1;

            Plano = Agregar_Enrutador(Plano, E1);
            guardar(Plano);
        }

       else if(choice == 2){
            cout << "--------------------------" << endl;
            cout << "AGREGAR CONEXION \n" << endl;

            Plano = Agregar_ruta(Plano);
            guardar(Plano);

        }

        else if(choice == 3){
            cout << "--------------------------" << endl;
            cout << "ELIMINAR UN ENRUTADOR Y SUS RUTAS \n" << endl;

            Plano = Eliminar(Plano);
            guardar(Plano);
            
         }

        else if(choice == 4){
            cout << "--------------------------" << endl;
            cout << "VISUALIZAR ENRUTADOR \n" << endl;

            VerEnrutador(Plano);

         }

        else if(choice == 5){
            cout << "--------------------------" << endl;
            cout << "VER TABLA DE ENRUTAMIENTO \n" << endl;

            VerTablaEnrutamiento(Plano);

         }

        else if(choice == 6){
            cout << "--------------------------" << endl;
            cout << "RUTAS Y COSTOS" << endl;

//            int n = Plano.size();
//            cout << n;
            rutas = todasRutas(Plano);
            rutasMinimas = RutasValoresMinimos(Plano);
            unsigned int choice2 = 0;

            do{
                cout << "--------------------------" << endl;
                cout << "1. Para ver las rutas y costos." << endl;
                cout << "2. Para ver las rutas minimas" << endl;
                cout << "3. Para volver" << endl;
                cin >> choice2;

                if(choice2 == 1){
                    Costo_Rutas(rutas);
                }

                else if(choice2 == 2){
                    Costo_Rutas(rutasMinimas);
                }

            }while(choice2 != 3);
         }

        else if(choice == 7){
            cout << "--------------------------" << endl;
            cout << "CAMBIAR COSTO." << endl;
            Plano = cambiar_costo(Plano);

         }

        else if(choice == 8){
            cout << "--------------------------" << endl;
            cout << "CARGAR UNA RED DESDE UN ARCHIVO .TXT \n" << endl;

            Plano = Cargar();

            if(!Plano.empty())
                guardar(Plano);
            else
                cout << "Error al subir el plano de enrutadores.";
            cout << "--------------------------" << endl;


         }



    }while(choice != 9);
    return 0;
}
