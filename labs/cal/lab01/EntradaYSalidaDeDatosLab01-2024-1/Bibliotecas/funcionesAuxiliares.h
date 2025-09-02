//
// Created by sn on 9/2/25.
//

#ifndef ENTRADAYSALIDADEDATOSLAB01_2024_1_FUNCIONESAUXILIARES_H
#define ENTRADAYSALIDADEDATOSLAB01_2024_1_FUNCIONESAUXILIARES_H

void leeDatosEImprimeReporte(void);
void imprimirEncabezadoReporte(void);
void imprimeLinea(char c);
void imprimeDatosYActualizaContadores(int fecha, int duracion, double tarifa, char especialidad, bool hayMed,
double montoMed, double &total, double &totalGastosMed, double &dermaGastosMed, int &cantPac, int &cantPacMed,
                int &cantPacDerma, int &cantPacPed, int &cantPacCardFecha, int &cantPacNoMedGasto);
void imprimeResumenFinal(double total, double promMed, double promMedDerma, double porcNoMed, double porcPed,
            int cantPacCardFecha, double porcPacNoMedGasto);

#endif //ENTRADAYSALIDADEDATOSLAB01_2024_1_FUNCIONESAUXILIARES_H