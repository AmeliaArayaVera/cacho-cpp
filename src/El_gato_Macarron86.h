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
    
    El_gato_Macarron86() {
        nombreEstudiante = "Amelia Rebeca Araya Vera"; 
    }
    std::string getNombreEstudiante() const{
        return nombreEstudiante;
    }

    int jugar(const std::map<std::string, Marcador> &marcadores,
              const std::vector<Actuacion> &actuacionesPosibles,
              const std::vector<int> &dados,
              const Anotacion &) override {

        // si sale casualmente una dormida, tomamos la jugada
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
        int cant_con_volteos[7] = {0};
        for(int numero = 1; numero <= 6; numero++) {
            cant_con_volteos[numero] = cant_de_cada_num[numero];
        }

        // esto calcula los dados sueltos y como seria la mano si los volteamos
        for(int i = 0; i < 5; i++) {
            int valorDado = dados[i];
            if (cant_de_cada_num[valorDado] == 1) { 
                int caraOpuesta = 7 - valorDado;
                
                cant_con_volteos[valorDado]--;
                cant_con_volteos[caraOpuesta]++;
            }
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

        std::vector<std::string> listaGrandes = {"grande", "grande2"};
        for (const auto& g : listaGrandes) {
            if (mejorOpcionLanzar != -1) break;
            if (!marcadores.at(nombre).yaAnotado(g)) {
                for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
                    if (actuacionesPosibles[i].accion == "lanzar" && maxRepetidos == 4) {
                        //esta decision solo pasa si hay 4 repetidos, cuando es mas probable sacar los 5 repetidos
                        //ya que en otros casos segun yo es más probable que salga otra jugada

                        //con lo siguiente encuentro una lanzada de dados que cumpla en este caso que sea lanzar 1 dado que no sea de los repetidos 
                        int cuantosLanzo = 0;
                        bool lanzaOtrosDadosUtiles = false;
                        for (int j : actuacionesPosibles[i].indiceDados) {
                            if (dados[j] != NumRep) cuantosLanzo++;
                            else lanzaOtrosDadosUtiles = true;
                        }
                        if (cuantosLanzo == 1 && !lanzaOtrosDadosUtiles) {
                            mejorOpcionLanzar = i;
                            break;
                        }
                    }
                    else if (maxRepetidos == 3 && cant_con_volteos[NumRep] == 4) { // esto es cuando si hay un numero que volteado es el repetido
                        int cuantosLanzo = 0;
                        bool lanzaDadosobrante = false;
                        
                        for (int j : actuacionesPosibles[i].indiceDados) {
                            // y aqui creo que conviene lanzar el que no es el numero ni el volteado, para no perder mi jugada/posible jugada
                            if (dados[j] != NumRep && (7 - dados[j] != NumRep)) {
                                cuantosLanzo++;
                                lanzaDadosobrante = true;
                            }
                        }
                        
                        if (cuantosLanzo == 1 && lanzaDadosobrante) {
                            mejorOpcionLanzar = i;
                            break;
                        }
                    } 
                }
            }
        }
        
        if (!marcadores.at(nombre).yaAnotado("poker")) {
            
            for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
                if (actuacionesPosibles[i].accion == "lanzar") {
                    
                    if (maxRepetidos == 3 && cant_con_volteos[NumRep] == 3) { //no hay volteo que sirva y hay varios repetidos de un num.
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
                    else if (maxRepetidos == 3 && cant_con_volteos[NumRep] == 4) { // esto es cuando si hay un numero que volteado es el repetido
                        int cuantosLanzo = 0;
                        bool lanzaDadosobrante = false;
                        
                        for (int j : actuacionesPosibles[i].indiceDados) {
                            // y aqui creo que conviene lanzar el que no es el numero ni el volteado, para no perder mi jugada
                            if (dados[j] != NumRep && (7 - dados[j] != NumRep)) {
                                cuantosLanzo++;
                                lanzaDadosobrante = true;
                            }
                        }
                        
                        if (cuantosLanzo == 1 && lanzaDadosobrante) {
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
                    
                    //aqui se hace 1 o 2 lanzamientos considerando si hay un dado volteado que nos sirve o no
                    if (maxRepetidos == 3 && cant_con_volteos[NumRep]== 3) {
                        int cuantosDelDuoLanza = 0;
                        bool lanzaOtrosDadosUtiles = false;

                        for (int j : actuacionesPosibles[i].indiceDados) {
                            if (dados[j] != NumRep) {
                                cuantosDelDuoLanza++;
                            } else {
                                
                                lanzaOtrosDadosUtiles = true; 
                            }
                        } 
                        
                        if (cuantosDelDuoLanza == 1 && !lanzaOtrosDadosUtiles) {
                            mejorOpcionLanzar = i;
                            break;
                        }
                    }
                    else if (maxRepetidos == 3 && cant_con_volteos[NumRep] == 4) { // esto es cuando si hay un numero que volteado es el repetido
                        int cuantosLanzo = 0;
                        bool lanzaDadosobrante = false;
                        
                        for (int j : actuacionesPosibles[i].indiceDados) {
                            // y aqui creo que conviene lanzar el que no es el numero ni el volteado, para no perder mi jugada/posible jugada
                            if (dados[j] != NumRep && (7 - dados[j] != NumRep)) {
                                cuantosLanzo++;
                                lanzaDadosobrante = true;
                            }
                        }
                        
                        if (cuantosLanzo == 1 && lanzaDadosobrante) {
                            mejorOpcionLanzar = i;
                            break;
                        }
                    }  
                    //aqui basicamente es en el caso de que haya por ej 2 2 3 3 y x numero
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
                    //aqui ya es solo cuando hay por ej 2 2 1 3 6
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
                    // en estos if me estoy tratando de deshacer de los repetidos menos 1
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
        std::vector<std::string> nombresLaterales = {"senas", "quinas", "cuadras", "trenes", "tontos", "balas"};
        //con este bloque busco lanzar los que no son los repetidos y que volteados tampoco lo son
        for (size_t k = 0; k < nombresLaterales.size(); ++k) {
            
            if (!marcadores.at(nombre).yaAnotado(nombresLaterales[k])) {
                
                int dadoObjetivo = 6 - k; 

                for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
                    if (actuacionesPosibles[i].accion == "lanzar") {
                        
                        if (maxRepetidos == 3 && NumRep == dadoObjetivo && cant_con_volteos[NumRep]==3) {
                            int cuantosLanzo = 0;
                            bool lanzaOtrosDadosUtiles = false;

                            for (int j : actuacionesPosibles[i].indiceDados) {
                                if (dados[j] != NumRep) {
                                    cuantosLanzo++;
                                } else {
                                    lanzaOtrosDadosUtiles = true; 
                                }
                            }
                        
                            if (cuantosLanzo == 2 && !lanzaOtrosDadosUtiles) {
                                mejorOpcionLanzar = i;
                                break;
                            }
                        }    
                        else if (maxRepetidos == 3 && NumRep == dadoObjetivo && cant_con_volteos[NumRep]==4) {
                            int cuantosLanzo = 0;
                            bool lanzaDadosobrante = false;
                            
                            for (int j : actuacionesPosibles[i].indiceDados) {
                                // y aqui creo que conviene lanzar el que no es el numero ni el volteado, para no perder mi jugada/posible jugada
                                if (dados[j] != NumRep && (7 - dados[j] != NumRep)) {
                                    cuantosLanzo++;
                                    lanzaDadosobrante = true;
                                }
                            }
                            
                            if (cuantosLanzo == 1 && lanzaDadosobrante) {
                                mejorOpcionLanzar = i;
                                break;
                            }
                        }
                    }
                }
        
            if (mejorOpcionLanzar != -1) {
                break;
                }
            }
        }
        //si encontro algo para lanzar dentro de algun if lo retorna
        if (mejorOpcionLanzar != -1) {
            return mejorOpcionLanzar;
        }
        
        int indiceMejorPuntaje = -1;
        //aqui llegaria si no pudo anotar algo grande como poker, full, etc,
        //Y pienso de que si no tengo la mitad o mas de los dados no conviene realmente anotar aqui
        for (size_t i = 0; i < actuacionesPosibles.size(); ++i) {
            if (actuacionesPosibles[i].accion == "anotar") {
                for (size_t k = 0; k < nombresLaterales.size(); ++k) {
                    if (actuacionesPosibles[i].anotacion.juego == nombresLaterales[k]) {
                        int puntajeMinimo = 18 - (3 * k); // k=0(senas) 18 pts min, k=1(quinas) 15, ...
                        if (actuacionesPosibles[i].anotacion.puntos >= puntajeMinimo) {
                            indiceMejorPuntaje = i;
                            break;
                        }
                    }
                }
                if (indiceMejorPuntaje != -1) break;
            }
        }
        //si llego aqui es que ninguna jugada pensada me llevo a algo que me convenia, por lo que me gustaria
        //anotar algo que me de puntos, pero no me haga perder una jugada buena
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
        //si ya no pude hacer nada y me dan la opcion de lanzar, lanzo.
        for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
            if (actuacionesPosibles[i].accion == "lanzar") {
                return i;
            }
        }


        //si llegue aqui es porque ya no tengo nada mas que hacer que tachar, y lo hacer en esta lista de prioridad
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
