//
// Created by Saymon on 9/15/26.
//

#ifndef LAB02_2026_2_FUNCIONES_H
#define LAB02_2026_2_FUNCIONES_H

void leeDatosEImprimeReportes(const char* , const char* , const char* );
void leerMedicionesEImprimirAlertas(const char* , const char* , int& , int& , int& , int& , int& , int& , int& ,
    int& , double& , double& , double& , double& , double& , double& );
void openError(const char* );
void imprimirCabeceraAlertas(ofstream& );
void imprimeLinea(ofstream& , char );
double hallarValorMedicion(ifstream& );
bool verAlertaYactualizarEstadisticas(int , int , char , double , int& , int& , int& , int& , int& , int& , int& ,
    int& , double& , double& , double& , double& , double& , double& );
void imprimirAlerta(ofstream& , int , int , int , char , double );
void imprimirEstadisticas(const char* , int , int , int , int , int , int , int , int , double , double , double ,
    double , double , double );
void imprimeFecha(ofstream& , int );
void imprimirTipoMedicion(ofstream& , const char* , const char* , int , int , double , double , double );

#endif //LAB02_2026_2_FUNCIONES_H
