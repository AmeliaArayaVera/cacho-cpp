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
              const Anotacion &) override {

        // si sale casualmente una dormida, la tomamos
        for (size_t i = 0; i < actuacionesPosibles.size(); ++i) {
            if (actuacionesPosibles[i].accion == "dormida") {
                return i; 
            }
        }
        //lo mismo aqui, pero con uno orden de prioridad por puntaje escogemos nuestra anotación 
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
        // aqui usare la cantidad de cada numero de dado para analizar que tirar según jugada posible en el momento 
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
        // con lo anterior analice si hay 1 numero repetido x veces, o si hay 2 numeros (en este caso si es que estos 2 se repiten 2 veces, ya que si fuera 3 rep y 2 rep ya es una jugada (al menos antes de anotar))
        int mejorOpcionLanzar = -1;
        //en estos bloques tomaremos decisiones de que hacer con las tiradas si tengo alguna anotación x disponible 
        //y estas decisiones dependen de que tantos repetidos hay en mi mano, y eso filtra si vale la pena o no la jugada
        if (!marcadores.at(nombre).yaAnotado("grande")) {
            
            for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
                if (actuacionesPosibles[i].accion == "lanzar") {
                    //esto solo pasa si hay 4 repetidos, cuando es mas probable sacar los 5 repetidos
                    //ya que en otros casos segun yo es más probable que salga otra jugada

                    //con lo siguiente encuentro una lanzada de dados que cumpla en este caso que sea lanzar 1 dado que no sea de los repetidos 
                    if (maxRepetidos == 4) {
                        int cuantosLanzo = 0;
                        bool lanzaOtrosDadosUtiles = false;

                        for (int j : actuacionesPosibles[i].indiceDados) {
                            if (dados[j] != NumRep) {
                                cuantosLanzo++;
                            } else {
                                
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
            //este es exactamente igual al anterior 
            for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
                if (actuacionesPosibles[i].accion == "lanzar") {
                    
                    if (maxRepetidos == 4) {
                        int cuantosLanzo = 0;
                        bool lanzaOtrosDadosUtiles = false;

                        for (int j : actuacionesPosibles[i].indiceDados) {
                            if (dados[j] != NumRep) {
                                cuantosLanzo++;
                            } else {
                                
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
                        
                        if (cuantosDelDuoLanza == 1 && !lanzaOtrosDadosUtiles) {
                            mejorOpcionLanzar = i;
                            break;
                        }
                    }
                    
                    else if (maxRepetidos == 2 && segundoNum_repetido_mismas_veces != -1) {
                        int lanzaDelPrimero = 0;
                        bool lanzaOtrosDados = false;

                        for (int j : actuacionesPosibles[i].indiceDados) {
                            
                            if (dados[j] != NumRep && dados[j] != segundoNum_repetido_mismas_veces) {
                                lanzaDelPrimero++;
                            } else {
                                
                                lanzaOtrosDados = true; 
                            }
                        }
                        if (lanzaDelPrimero == 1 && !lanzaOtrosDados) {
                            mejorOpcionLanzar = i;
                            break; 
                        }
                    }
            
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
            
                    if (maxRepetidos == 2 && segundoNum_repetido_mismas_veces != -1) {
                        int lanzaDelPrimero = 0;
                        int lanzaDelSegundo = 0;
                        bool lanzaOtrosDados = false;

                        for (int j : actuacionesPosibles[i].indiceDados) {
                            if (dados[j] == NumRep) lanzaDelPrimero++;
                            else if (dados[j] == segundoNum_repetido_mismas_veces) lanzaDelSegundo++;
                            else lanzaOtrosDados = true;
                        }

                        if (lanzaDelPrimero == 1 && lanzaDelSegundo == 1 && !lanzaOtrosDados) {
                            mejorOpcionLanzar = i;
                            break; 
                        }
                    }
                    else if (maxRepetidos == 2 && segundoNum_repetido_mismas_veces == -1) {
                        if (actuacionesPosibles[i].indiceDados.size() == 1) {
                            int posicionDelDado = actuacionesPosibles[i].indiceDados[0];
                            if (dados[posicionDelDado] == NumRep) {
                                mejorOpcionLanzar = i;
                                break;
                            }
                        }
                    }
                    
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
                        if (cuantosDelTrioLanza == 2 && !lanzaOtrosDadosUtiles) {
                            mejorOpcionLanzar = i;
                            break;
                        }
                    }
                }
            }
        }
        else if (!marcadores.at(nombre).yaAnotado("senas")) {
            
            for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
                if (actuacionesPosibles[i].accion == "lanzar") {
                    
                    if (maxRepetidos == 3 && NumRep == 6) {
                        int cuantosLanzo = 0;
                        bool lanzaOtrosDadosUtiles = false;

                        for (int j : actuacionesPosibles[i].indiceDados) {
                            if (dados[j] != NumRep ) {
                                cuantosLanzo++;
                            } else {
                                
                                lanzaOtrosDadosUtiles = true; 
                            }
                        }
                       
                        if (cuantosLanzo == 2 &&!lanzaOtrosDadosUtiles) {
                            mejorOpcionLanzar = i;
                            break;
                        }
                    }    
                }
            }
        }
        else if (!marcadores.at(nombre).yaAnotado("quinas")) {
            
            for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
                if (actuacionesPosibles[i].accion == "lanzar") {
                    
                    if (maxRepetidos == 3 && NumRep == 5) {
                        int cuantosLanzo = 0;
                        bool lanzaOtrosDadosUtiles = false;

                        for (int j : actuacionesPosibles[i].indiceDados) {
                            if (dados[j] != NumRep ) {
                                cuantosLanzo++;
                            } else {
                                
                                lanzaOtrosDadosUtiles = true; 
                            }
                        }
                       
                        if (cuantosLanzo == 2 &&!lanzaOtrosDadosUtiles) {
                            mejorOpcionLanzar = i;
                            break;
                        }
                    }    
                }
            }
        }
        else if (!marcadores.at(nombre).yaAnotado("cuadras")) {
            
            for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
                if (actuacionesPosibles[i].accion == "lanzar") {
                    
                    if (maxRepetidos == 3 && NumRep == 4) {
                        int cuantosLanzo = 0;
                        bool lanzaOtrosDadosUtiles = false;

                        for (int j : actuacionesPosibles[i].indiceDados) {
                            if (dados[j] != NumRep ) {
                                cuantosLanzo++;
                            } else {
                                // Si intenta tirar un dado del trío, está mal
                                lanzaOtrosDadosUtiles = true; 
                            }
                        }
                       
                        if (cuantosLanzo == 2 &&!lanzaOtrosDadosUtiles) {
                            mejorOpcionLanzar = i;
                            break;
                        }
                    }    
                }
            }
        }
        else if (!marcadores.at(nombre).yaAnotado("trenes")) {
            
            for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
                if (actuacionesPosibles[i].accion == "lanzar") {
                    
                    if (maxRepetidos == 3 && NumRep == 3) {
                        int cuantosLanzo = 0;
                        bool lanzaOtrosDadosUtiles = false;

                        for (int j : actuacionesPosibles[i].indiceDados) {
                            if (dados[j] != NumRep ) {
                                cuantosLanzo++;
                            } else {
                                
                                lanzaOtrosDadosUtiles = true; 
                            }
                        }
                       
                        if (cuantosLanzo == 2 &&!lanzaOtrosDadosUtiles) {
                            mejorOpcionLanzar = i;
                            break;
                        }
                    }    
                }
            }
        }
        else if (!marcadores.at(nombre).yaAnotado("tontos")) {
            
            for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
                if (actuacionesPosibles[i].accion == "lanzar") {
                    
                    if (maxRepetidos == 3 && NumRep == 2) {
                        int cuantosLanzo = 0;
                        bool lanzaOtrosDadosUtiles = false;

                        for (int j : actuacionesPosibles[i].indiceDados) {
                            if (dados[j] != NumRep ) {
                                cuantosLanzo++;
                            } else {
                                
                                lanzaOtrosDadosUtiles = true; 
                            }
                        }
                       
                        if (cuantosLanzo == 2 &&!lanzaOtrosDadosUtiles) {
                            mejorOpcionLanzar = i;
                            break;
                        }
                    }    
                }
            }
        }
        else if (!marcadores.at(nombre).yaAnotado("balas")) {
            
            for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
                if (actuacionesPosibles[i].accion == "lanzar") {
                    
                    if (maxRepetidos == 3 && NumRep == 1) {
                        int cuantosLanzo = 0;
                        bool lanzaOtrosDadosUtiles = false;

                        for (int j : actuacionesPosibles[i].indiceDados) {
                            if (dados[j] != NumRep ) {
                                cuantosLanzo++;
                            } else {
                                
                                lanzaOtrosDadosUtiles = true; 
                            }
                        }
                       
                        if (cuantosLanzo == 2 &&!lanzaOtrosDadosUtiles) {
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
            std::vector<std::string> prioridad = {"balas", "tontos", "trenes", "cuadras", "quinas", "senas", "escalera", "full", "poker", "grande", "grande2"};
            bool encontrado = false;
            for (const std::string& jugada : prioridad) {
                for (size_t i = 0; i < actuacionesPosibles.size(); ++i) {
                    if (actuacionesPosibles[i].accion == "anotar" && 
                        actuacionesPosibles[i].anotacion.juego == jugada && actuacionesPosibles[i].anotacion.puntos > 0) {
                        
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
                        (actuacionesPosibles[i].anotacion.juego == jugadaATachar )) {
                        return i;
                    }
                }
            }
        }
        return 0; 
    }
};

#endif 
