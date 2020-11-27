#ifndef ENRUTADORES_H
#define ENRUTADORES_H
#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>
#include <map>
#include <vector>
using namespace std;

struct Enrutador{
    string Enrutador_asociado;
    unsigned int costo;
};

bool Verificacion(map<string, vector<Enrutador>> contenedor, string E){                      //valida la existencia de un enrutador en el mapa
    for(auto elemento = begin(contenedor); elemento != end(contenedor); elemento++){
        if(E == elemento->first){
            return true;
            break;
        }
    }
    return false;
}


map<string, vector<Enrutador>> Agregar_Enrutador(map<string, vector<Enrutador>> contenedor, string E1){
    Enrutador enrutador;

    if(Verificacion(contenedor, E1) == false){
        enrutador.Enrutador_asociado = E1;
        enrutador.costo = 0;
        contenedor[E1].push_back(enrutador);
        cout << "Enrutador agregrado a la Red con exito." << endl;
    }

    else
        cout << "El nombre del enrutador ya se encuentra registrado en el sistema" << endl;
        
    cout << "--------------------------" << endl;
    return contenedor;
}

map<string, vector<Enrutador>> Agregar_ruta(map<string, vector<Enrutador>> contenedor){
    Enrutador enruador;
    string E1, E2;
    int costo_Ruta;
    
    cout << "Ingrese el enrutador de origen: " << endl;
    cin >> E1;
    cout << "Ingrese el enrutador de destino: " << endl;
    cin >> E2;
    cout << "Ingrese el costo de envio entre los dos enrutadores: " << endl;
    cin >> costo_Ruta;
    //los enrutadores deben estar en el plano
    
    bool conexion = false;
    if(E1 != E2){                                                                               //verifica que los dos enrutadores sean distintos
        if(Verificacion(contenedor, E1) == true && Verificacion(contenedor, E2)){
            for(auto elemento = begin(contenedor); elemento != end(contenedor); elemento++){
                if(elemento ->first == E1){
                    for(auto elemento2 = begin(elemento->second); elemento2 != end(elemento->second); elemento2++){
                        if(elemento2 -> Enrutador_asociado == E2){
                            conexion = true;
                            break;
                        }
                    }
                }    
            }
            if(conexion ==  false){
                enruador.Enrutador_asociado = E2;
                enruador.costo = costo_Ruta;
                contenedor[E1].push_back(enruador);
                
                enruador.Enrutador_asociado = E1;
                enruador.costo = costo_Ruta;
                contenedor[E2].push_back(enruador);
                cout << "Rutas agregadas con exito." << endl;
                
            }
            else
                cout << "los enrutadores que ingreso ya tienen conexiones" << endl;
        }
        else
            cout << "los enrutadores que ingreso no se encuentran registrados al sistema y por lo tanto no se puede hacer la conexion" << endl;
    }
    else
        cout << "los dos Enrutadores deben ser diferentes" << endl;
    
    cout << "--------------------------" << endl;
    return contenedor;
    
    
}

map<string, vector<Enrutador>> Eliminar(map<string, vector<Enrutador>> contenedor){
    string E;
    cout << "Ingrese el nombre del enrutador que desea eliminar: " << endl;
    cin >> E;
    
    if(Verificacion(contenedor, E)==true){
        for(auto elemento = begin(contenedor); elemento != end(contenedor); elemento++){
            if(elemento ->first == E){
                elemento = contenedor.erase(elemento);
                break;
            }
        }
        for(auto elemento = begin(contenedor); elemento != end(contenedor); elemento++){
            for(auto elemento2 = begin(elemento->second); elemento2 != end((elemento->second)); elemento2++){
                if((elemento2->Enrutador_asociado) == E){
                    (elemento->second).erase(elemento2);
                    break;
                }
            }
        }
        cout << "Enrutador eliminado con exito." << endl;
    }
    else
        cout << "El enrutador no se encuentra registrado en la red." << endl;
    
    cout << "--------------------------" << endl;
    return contenedor;
}

void guardar(map<string, vector<Enrutador>> vias){
    ofstream Escritura;
    Escritura.open("Red.txt");
    unsigned int lon_Vec = vias.size();
    unsigned int pos = 0;

    for(auto Enrutador = begin(vias); Enrutador != end(vias); Enrutador++){
        Escritura << Enrutador->first;
        pos++;

        for(auto caraceristicas = begin(Enrutador->second); caraceristicas != end(Enrutador->second); caraceristicas++){
            Escritura << " " << caraceristicas->Enrutador_asociado <<  " " << caraceristicas->costo;
        }
        Escritura << " .";
        if(pos<lon_Vec)
            Escritura << endl;
    }
    Escritura.close();
}


map<string, vector<Enrutador>> Cargar(){
    string Archivolec, clave, valor;
    cout << "Ingrese el nombre del archivo desde el cual desea cargar los enrutadores: " << endl;
    cin >> Archivolec;
    Enrutador enrutador;
    map<string, vector<Enrutador>> contenedor;

    ifstream Lectura;
    Lectura.open(Archivolec+".txt");

    if(!Lectura.is_open()){
        cout << "archivo no encontrado.";
        exit(1);
    }

    while(!Lectura.eof()){
        Lectura >> clave;
        Lectura >> valor;

        while(valor != "."){
          enrutador.Enrutador_asociado = valor;
          Lectura >> enrutador.costo;
          Lectura >> valor;

          contenedor[clave].push_back(enrutador);

        }
        enrutador = {};
    }
    Lectura.close();
    cout << "--------------------------" << endl;
    return contenedor;
}

void VerEnrutador(map<string, vector<Enrutador>> contenedor){
    string E;
    cout << "Ingrese el nombre del enrutador que desea ver: ";
    cin >> E;

    for(auto elemento = begin(contenedor); elemento != end(contenedor); elemento++){
        if(elemento->first == E){
            cout << "El enrutador: " << E << " tiene conexiones con: " << endl;
            for(auto conexion = begin(elemento ->second); conexion != end(elemento ->second); conexion++){
                cout << conexion->Enrutador_asociado << " Con costo de: " << conexion->costo << endl;
            }
        }
    }
    cout << "--------------------------" << endl;

}

void VerTablaEnrutamiento(map<string, vector<Enrutador>> contenedor){
    if(!contenedor.empty()){
        for(auto elemento = begin(contenedor); elemento != end(contenedor); elemento++){
            cout << "--------------------------" << endl;
            cout << "El enrutador: " << elemento->first << " tiene conexiones con: " << endl;
            for(auto conexion = begin(elemento ->second); conexion != end(elemento ->second); conexion++){
                cout << conexion->Enrutador_asociado << " Con costo de: " << conexion->costo << endl;
            }
        }
        cout << "--------------------------" << endl;

    }
    else{
        cout << "La red no tiene enrutadores registrados, registre o cargue una red para poder ver la tabla de enrutamiento." << endl;
        cout << "--------------------------" << endl;
    }

}

map<string, vector<Enrutador>> cambiar_Elemento(map<string, vector<Enrutador>> contenedor, string Enrutador1, string Enrutador2, int costo_Enrutador, Enrutador enrutador){
    for(auto elemento = begin(contenedor); elemento != end(contenedor); elemento++){
        if(elemento->first == Enrutador1){
            for(auto valor = begin(elemento->second); valor != end(elemento->second); valor++){
                if(valor->Enrutador_asociado == Enrutador2){
                    (elemento->second).erase(valor);
                    enrutador.Enrutador_asociado = Enrutador2;
                    enrutador.costo = costo_Enrutador;
                    contenedor[Enrutador1].push_back(enrutador);
                    break;
                }
            }
            break;
        }
    }
    return contenedor;
}

map<string, vector<Enrutador>> cambiar_costo(map<string, vector<Enrutador>> contenedor){
    Enrutador enrutador;
    string E1, E2;
    int costo_Enrutadores;

    cout << "Ingrese el nombre del enrutador de origen: " << endl;
    cin >> E1;
    cout << "Ingrese el nombre del enrutador de destino: " << endl;
    cin >> E2;

    if(E1 != E2){
        if(Verificacion(contenedor, E1)== true && Verificacion(contenedor, E2)== true){
            cout << "Ingrese el costo entre los Enrutadores (mayor que 0): " << endl;
            cin >> costo_Enrutadores;
            if(costo_Enrutadores>0){
                contenedor = cambiar_Elemento(contenedor, E1, E2, costo_Enrutadores, enrutador);
                contenedor = cambiar_Elemento(contenedor, E2, E1, costo_Enrutadores, enrutador);
            }
            else
                cout << "El costo entre los Enrutadores tiene que ser mayor que 0:" << endl;
        }
        else
            cout << "Los enrutadores no se encuentran registrados en la red." << endl;
    }
    else
        cout << "La ruta entre estos dos enrutadores es 0 y no se puede cambiar." << endl;

    cout << "--------------------------" << endl;
    return contenedor;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//RUTAS, RUTAS MINIMAS Y COSTOS

bool coincidenciaString(string posible_Ruta, string nodo){
    for(unsigned int posicion = 0; posicion<posible_Ruta.size(); ++posicion){
        if(nodo[0]== posible_Ruta.at(posicion)){
            return true;
        }
    }
    return false;
}

vector<Enrutador> completar_caminos(map<string, vector<Enrutador>> contenedor, vector<Enrutador> caminos, unsigned int tam1, unsigned int tam2, string Enrutador_Actual, Enrutador conexion){
    string AuxRuta, Ruta;
    unsigned int AuxCosto, Costo;

    for(unsigned int i= tam1; i<tam2; ++i){
        Ruta = (caminos.at(i)).Enrutador_asociado;
        Costo = caminos.at(i).costo;

        for(auto elemento = begin(contenedor); elemento != end(contenedor); elemento++){

            if(Enrutador_Actual != elemento->first && &(Ruta.at(Ruta.size()-1))==elemento->first){
                for(auto elemento2 = begin(elemento->second); elemento2 !=end(elemento->second); elemento2++){
                    if(coincidenciaString(Ruta, elemento2->Enrutador_asociado)==false){
                        AuxRuta = Ruta;
                        AuxRuta += elemento2->Enrutador_asociado;
                        AuxCosto = Costo;
                        AuxCosto += elemento2->costo;

                        conexion.Enrutador_asociado = AuxRuta;
                        conexion.costo = AuxCosto;
                        caminos.push_back(conexion);
                    }
                }
            }
        }
    }
    return caminos;
}

map<string, vector<Enrutador>> todasRutas(map<string, vector<Enrutador>> contenedor){
    map<string, vector<Enrutador>> R;
    vector<Enrutador> Caminos;
    Enrutador conexion;
    string Aux;
    unsigned int tam1, tam2;

    for(auto elemento = begin(contenedor); elemento != end(contenedor); elemento++){
        tam1 = 0;

        for(auto valor = begin(elemento->second); valor != end(elemento->second); valor++){
            Aux = elemento->first;
            if(elemento->first != valor->Enrutador_asociado)
                Aux += valor->Enrutador_asociado;

            conexion.Enrutador_asociado = Aux;
            conexion.costo =(valor->costo);
            Caminos.push_back(conexion);
        }
        tam2 = Caminos.size();
        do{
            Caminos = completar_caminos(contenedor, Caminos, tam1, tam2, elemento ->first, conexion);
            tam1 = tam2;
            tam2 = Caminos.size();
        }while(tam1 != tam2);

        for(unsigned int n=0; n<Caminos.size(); ++n)
            R[elemento->first].push_back(Caminos.at(n));

        Caminos ={};
    }
    return R;
}

void Costo_Rutas(map<string,vector<Enrutador>> contenedor){
    string E;
    cout << "Ingrese el nombre del enrutador que desea ver: ";
    cin >> E;

    for(auto elemento = begin(contenedor); elemento != end(contenedor); elemento++){
        if(elemento->first == E){
            cout << "El enrutador: " << E << " tiene una ruta hacia: " << endl;
            for(auto camino = begin(elemento ->second); camino != end(elemento ->second); camino++){
                cout << camino->Enrutador_asociado << " Con costo de: " << camino->costo << endl;
            }
        }
    }
    cout << "--------------------------" << endl;

}

map<string,vector<Enrutador>> RutasValoresMinimos(map<string,vector<Enrutador>> posiblesvias){
    #define INFINITO 999999999
    map<string, vector<Enrutador>> trayecto_minimo;
    vector<Enrutador> caminos_minimos;
    Enrutador camino;
    unsigned int minimo = INFINITO;
    string ruta_minimo;

    for(auto elemento = begin(posiblesvias); elemento != end(posiblesvias); elemento++){
        for(auto ultimo_elemento = begin(posiblesvias); ultimo_elemento != end(posiblesvias); ultimo_elemento++){
            caminos_minimos ={};
            for(auto valor = begin(elemento->second); valor != end(elemento->second); valor++){
                if((ultimo_elemento->first).at(0)==(valor->Enrutador_asociado).at((valor->Enrutador_asociado).size()-1) && minimo>(valor->costo)){
                    ruta_minimo = valor->Enrutador_asociado;
                    minimo = valor->costo;
                }
            }
            if(minimo != INFINITO){
                camino.Enrutador_asociado = ruta_minimo;
                camino.costo = minimo;
                caminos_minimos.push_back(camino);
                trayecto_minimo[elemento->first].push_back(caminos_minimos.at(0));
            }
            minimo = INFINITO;
        }
    }
    return trayecto_minimo;
}



#endif // ENRUTADORES_H
