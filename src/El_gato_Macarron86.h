#ifndef EL_GATO_MACARRON86_H
#define EL_GATO_MACARRON86_H

#include "Jugador.h"

#include <map>
#include <string>
#include <vector>
class Marcador;
class El_gato_Macarron86 : public Jugador {
private:
    std::string nombreEstudiante;

public:
    
    El_gato_Macarron86(std::string nom): Jugador(nom) {
        nombreEstudiante = "Amelia Rebeca Araya Vera"; 
    }

    int jugar(const std::map<std::string, Marcador> &marcadores,
              const std::vector<Actuacion> &actuacionesPosibles,
              const std::vector<int> &dados,
              const Anotacion &resultadoPrevio) override {

        
        for (size_t i = 0; i < actuacionesPosibles.size(); ++i) {
            if (actuacionesPosibles[i].accion == "dormida") {
                return i; 
            }
        }

        for (size_t i = 0; i < actuacionesPosibles.size(); ++i) {
            const auto& act = actuacionesPosibles[i];
            if (act.accion == "anotar") {
                if (act.anotacion.juego == "grande" && act.anotacion.puntos > 0 ) {
                    return i;
                     
                }
                else if (act.anotacion.juego == "grande2"&& act.anotacion.puntos > 0) {
                    return i;
                     
                }
                else if (act.anotacion.juego == "poker"&& act.anotacion.puntos > 0) {
                    return i;
                     
                }
                else if( act.anotacion.juego == "full"&& act.anotacion.puntos > 0){
                    return i;
                    
                }
                else if (act.anotacion.juego == "escalera" && act.anotacion.puntos > 0){
                    return i;
                     
                }
            }
        }

        int cant_de_cada_num[7] = {0};
        for(int i = 0; i < 5; i++){
            cant_de_cada_num[dados[i]]++;
        }
        int NumRep = -1;
        int maxRepetidos = -1;
        int segundoNum_repetido_mismas_veces = -1;
        for(int numero = 1; numero <= 6; numero++){
            if( cant_de_cada_num[numero]> maxRepetidos){
                maxRepetidos = cant_de_cada_num[numero];
                NumRep = numero;
                segundoNum_repetido_mismas_veces = -1;
            }
            else if (cant_de_cada_num[numero]== maxRepetidos){
                segundoNum_repetido_mismas_veces = numero;
            }
        }
        int mejorOpcionLanzar = -1;

        if (!marcadores.at(nombre).yaAnotado("grande")) {
            
            for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
                if (actuacionesPosibles[i].accion == "lanzar") {
                    
                    if (maxRepetidos == 4) {
                        int cuantosLanzo = 0;
                        bool lanzaOtrosDadosUtiles = false;

                        for (int j : actuacionesPosibles[i].indiceDados) {
                            if (dados[j] != NumRep) {
                                cuantosLanzo++;
                            } else {
                                // Si intenta tirar un dado del trío, está mal
                                lanzaOtrosDadosUtiles = true; 
                            }
                        }
                       
                        if (cuantosLanzo == 1 && !lanzaOtrosDadosUtiles) {
                            mejorOpcionLanzar = i;
                            break;
                        }
                    }    
                }
            }
        }
        else if (!marcadores.at(nombre).yaAnotado("grande2")) {
            
            for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
                if (actuacionesPosibles[i].accion == "lanzar") {
                    
                    if (maxRepetidos == 4) {
                        int cuantosLanzo = 0;
                        bool lanzaOtrosDadosUtiles = false;

                        for (int j : actuacionesPosibles[i].indiceDados) {
                            if (dados[j] != NumRep) {
                                cuantosLanzo++;
                            } else {
                                // Si intenta tirar un dado del trío, está mal
                                lanzaOtrosDadosUtiles = true; 
                            }
                        }
                       
                        if (cuantosLanzo == 1 && !lanzaOtrosDadosUtiles) {
                            mejorOpcionLanzar = i;
                            break;
                        }
                    }    
                }
            }
        }
        else if (!marcadores.at(nombre).yaAnotado("poker")) {
            
            for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
                if (actuacionesPosibles[i].accion == "lanzar") {
                    
                    if (maxRepetidos == 3) {
                        int cuantosDelDuoLanza = 0;
                        bool lanzaOtrosDadosUtiles = false;

                        for (int j : actuacionesPosibles[i].indiceDados) {
                            if (dados[j] != NumRep) {
                                cuantosDelDuoLanza++;
                            } else {
                                // Si intenta tirar un dado del trío, está mal
                                lanzaOtrosDadosUtiles = true; 
                            }
                        }
                       
                        if (cuantosDelDuoLanza == 2 && !lanzaOtrosDadosUtiles) {
                            mejorOpcionLanzar = i;
                            break;
                        }
                    }    
                }
            }
        }
        else if (!marcadores.at(nombre).yaAnotado("full")) {
            
            for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
                if (actuacionesPosibles[i].accion == "lanzar") {
                    
                    // CASO 1: Tenemos un trío listo (ej: [4, 4, 4, 1, 2]). 
                    // Queremos lanzar EXACTAMENTE UNO de los dos dados que no se repiten.
                    if (maxRepetidos == 3) {
                        int cuantosDelDuoLanza = 0;
                        bool lanzaOtrosDadosUtiles = false;

                        for (int j : actuacionesPosibles[i].indiceDados) {
                            if (dados[j] != NumRep) {
                                cuantosDelDuoLanza++;
                            } else {
                                // Si intenta tirar un dado del trío, está mal
                                lanzaOtrosDadosUtiles = true; 
                            }
                        }
                        
                        // CORRECCIÓN: Para maximizar, cambiamos el '2' por '1'. 
                        // Lanzamos solo 1 dado basura, conservando el otro.
                        if (cuantosDelDuoLanza == 1 && !lanzaOtrosDadosUtiles) {
                            mejorOpcionLanzar = i;
                            break;
                        }
                    }
                    
                    // CASO 2: Tenemos doble pareja (ej: [4, 4, 2, 2, 1]).
                    // Queremos lanzar el único dado suelto (el que NO pertenece a ninguna pareja).
                    else if (maxRepetidos == 2 && segundoNum_repetido_mismas_veces != -1) {
                        int lanzaDelPrimero = 0;
                        bool lanzaOtrosDados = false;

                        for (int j : actuacionesPosibles[i].indiceDados) {
                            // CORRECCIÓN: Usamos '&&' en lugar de '||'. 
                            // Entra si el dado NO es de la pareja 1 Y TAMPOCO de la pareja 2.
                            if (dados[j] != NumRep && dados[j] != segundoNum_repetido_mismas_veces) {
                                lanzaDelPrimero++;
                            } else {
                                // Si intenta tocar cualquiera de las dos parejas, no nos sirve
                                lanzaOtrosDados = true; 
                            }
                        }

                        // Queremos lanzar exactamente ese único dado suelto
                        if (lanzaDelPrimero == 1 && !lanzaOtrosDados) {
                            mejorOpcionLanzar = i;
                            break; 
                        }
                    }
                    
                    // CASO 3: Solo tenemos una pareja (ej: [4, 4, 1, 2, 3]).
                    // Tu lógica original que ya estaba perfecta.
                    else if (maxRepetidos == 2 && segundoNum_repetido_mismas_veces == -1) {
                        int lanzaDelPrimero = 0;
                        bool lanzaOtrosDados = false;

                        for (int j : actuacionesPosibles[i].indiceDados) {
                            if (dados[j] != NumRep) {
                                lanzaDelPrimero++;
                            } else {
                                lanzaOtrosDados = true;
                            }
                        }

                        if (lanzaDelPrimero == 3 && !lanzaOtrosDados) {
                            mejorOpcionLanzar = i;
                            break; 
                        }
                    }
                    
                }
            }
        }
        else if (!marcadores.at(nombre).yaAnotado("escalera")) {
            
            for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
                if (actuacionesPosibles[i].accion == "lanzar") {
                    
                    // CASO 1: Tenemos doble pareja (ej: [2, 2, 5, 5, 1]). 
                    // Queremos lanzar UN dado del primer par y UN dado del segundo par para buscar cartas nuevas.
                    if (maxRepetidos == 2 && segundoNum_repetido_mismas_veces != -1) {
                        int lanzaDelPrimero = 0;
                        int lanzaDelSegundo = 0;
                        bool lanzaOtrosDados = false;

                        for (int j : actuacionesPosibles[i].indiceDados) {
                            if (dados[j] == NumRep) lanzaDelPrimero++;
                            else if (dados[j] == segundoNum_repetido_mismas_veces) lanzaDelSegundo++;
                            else lanzaOtrosDados = true;
                        }

                        // Si la opción lanza exactamente 1 del primero, 1 del segundo y no toca el resto
                        if (lanzaDelPrimero == 1 && lanzaDelSegundo == 1 && !lanzaOtrosDados) {
                            mejorOpcionLanzar = i;
                            break; 
                        }
                    }
                    
                    // CASO 2: Solo hay una pareja (ej: [2, 2, 3, 4, 6]).
                    // Queremos lanzar exactamente UN dado de esa pareja que se repite.
                    else if (maxRepetidos == 2 && segundoNum_repetido_mismas_veces == -1) {
                        if (actuacionesPosibles[i].indiceDados.size() == 1) {
                            int posicionDelDado = actuacionesPosibles[i].indiceDados[0];
                            if (dados[posicionDelDado] == NumRep) {
                                mejorOpcionLanzar = i;
                                break;
                            }
                        }
                    }
                    
                    // CASO 3: Tenemos un trío (ej: [2, 2, 2, 4, 5]).
                    // Queremos lanzar exactamente DOS dados de ese trío para conservar solo uno.
                    else if (maxRepetidos == 3) {
                        int cuantosDelTrioLanza = 0;
                        bool lanzaOtrosDadosUtiles = false;

                        for (int j : actuacionesPosibles[i].indiceDados) {
                            if (dados[j] == NumRep) {
                                cuantosDelTrioLanza++;
                            } else {
                                lanzaOtrosDadosUtiles = true;
                            }
                        }

                        // Si lanza exactamente 2 dados del trío y mantiene intactos los otros números útiles
                        if (cuantosDelTrioLanza == 2 && !lanzaOtrosDadosUtiles) {
                            mejorOpcionLanzar = i;
                            break;
                        }
                    }
                }
            }
        }
        if (mejorOpcionLanzar != -1) {
            return mejorOpcionLanzar;
        }
        if (mejorOpcionLanzar == -1) {
            for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
                if (actuacionesPosibles[i].accion == "lanzar") {
                    mejorOpcionLanzar = i;
                    break;
                }
            }
        }
        // 4. Estrategia de Respaldo: Si hay que anotar en los laterales o tachar
        
        int indiceMejorPuntaje = -1;

        for (size_t i = 0; i < actuacionesPosibles.size(); ++i) {
            if (actuacionesPosibles[i].accion == "anotar") {
                if(actuacionesPosibles[i].anotacion.juego == "senas"){
                    if (actuacionesPosibles[i].anotacion.puntos >= 18) {
                        indiceMejorPuntaje = i;
                        break;
                    }
                }
                else if(actuacionesPosibles[i].anotacion.juego == "quinas"){
                    if (actuacionesPosibles[i].anotacion.puntos >= 15) {
                       
                        indiceMejorPuntaje = i;
                        break;
                    }
                }
                else if(actuacionesPosibles[i].anotacion.juego == "cuadras"){
                    if (actuacionesPosibles[i].anotacion.puntos >= 12) {
                        
                        indiceMejorPuntaje = i;
                        break;
                    }
                }
                else if(actuacionesPosibles[i].anotacion.juego == "trenes"){
                    if (actuacionesPosibles[i].anotacion.puntos >= 9) {
                        
                        indiceMejorPuntaje = i;
                        break;
                    }
                }
                else if(actuacionesPosibles[i].anotacion.juego == "tontos"){
                    if (actuacionesPosibles[i].anotacion.puntos >= 6) {
                        
                        indiceMejorPuntaje = i;
                        break;
                    }
                }
                else if(actuacionesPosibles[i].anotacion.juego == "balas"){
                    if (actuacionesPosibles[i].anotacion.puntos >= 3) {
                        
                        indiceMejorPuntaje = i;
                        break;
                    }
                }
            }
        }
        if (indiceMejorPuntaje == -1){
            std::vector<std::string> prioridad = {"balas", "tontos", "trenes", "cuadras", "quinas", "senas"};
            bool encontrado = false;
            for (const std::string& jugada : prioridad) {
                for (size_t i = 0; i < actuacionesPosibles.size(); ++i) {
                    if (actuacionesPosibles[i].accion == "anotar" && 
                        actuacionesPosibles[i].anotacion.juego == jugada) {
                        
                        indiceMejorPuntaje = i;
                        encontrado = true;
                        break; 
                    }
                }
                if (encontrado) break; 
            }
        }
        
        if (indiceMejorPuntaje != -1) {
            return indiceMejorPuntaje;
        }

        for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
            if (actuacionesPosibles[i].accion == "lanzar") {
                return i;
            }
        }

        std::vector<std::string> ordenTachar = {"balas", "tontos", "trenes", "cuadras", "quinas", "senas", "escalera", "full", "poker", "grande", "grande2"};
        for (const std::string& jugadaATachar : ordenTachar) {
            if (!marcadores.at(nombre).yaAnotado(jugadaATachar)) {
                for (size_t i = 0; i < actuacionesPosibles.size(); ++i) {
                    if (actuacionesPosibles[i].accion == "tachar" && 
                        (actuacionesPosibles[i].anotacion.juego == jugadaATachar || 
                         actuacionesPosibles[i].anotacion.juego == (std::string(1, toupper(jugadaATachar[0])) + jugadaATachar.substr(1)))) {
                        return i;
                    }
                }
            }
        }
        return 0; 
    }
};

#endif 