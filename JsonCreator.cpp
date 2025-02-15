/* 
 * File:   JsonCreator.cpp
 * Author: ellioth
 * 
 * Created on February 17, 2016, 11:24 PM
 */

#include "JsonCreator.h"

JsonCreator::JsonCreator() {

}

JsonCreator::~JsonCreator() {
}

/**
 * metodo para crear el Json que se le enviara al cliente que tenga la pantalla
 * @param bola dato tipo puntero que es el arreglo de las bolas en el campo.
 * @param plyrs dato tipo puntero que es el arreglo que contiene a los 
 * clientes conectaDOS.
 * @param barrs dato tipo puntero que es el arreglo que contiene las barras o 
 * bloques restantes en el campo.
 * @param pBolas dato tipo entero que es la cantidad de bolas en el campo.
 * @param pPlyrs dato tipo entero que es la cantidad de jugadores en el campo.
 * @param pBarrs dato tipo entero que es el bloque que queremos decir que
 * recibio un golpe.
 * @return retorna un dato tipo string que es el Json creado.
 * {"players":{"p1":"000,000","p2":"000,000"...}, "brickH":{"id":00,"del":0}}
 */
string JsonCreator::create(Bola* bola[], Player* plyrs[], Brick* barrs, int pBolas, int pPlyrs, int pBarrs){
    string temp;
    rapidjson::StringBuffer JsonToWrite;
    rapidjson::Writer<rapidjson::StringBuffer> writer(JsonToWrite);
    writer.StartObject();
    //crea un mensaje que indica la terminacion del juego.
    if(pBolas==CERO || pBarrs==-DOS){
        temp="terminate";
        writer.String(temp.c_str());
        writer.String(temp.c_str());
        writer.EndObject();
        return JsonToWrite.GetString();
    }
    //bloque para los jugadores conectados
    writer.String(PLAYERS);
        writer.StartObject();
        string playerTempName;
        for(int i =0; i<pPlyrs; i++){
            playerTempName="p"+to_string(i);
            writer.String(playerTempName.c_str());
            string posPlayer= to_string(plyrs[i]->getPosX());
            posPlayer+=",";
            posPlayer+=to_string(plyrs[i]->getPosY());
            writer.String(posPlayer.c_str());
        }
        writer.EndObject();
    //bloque para los ladrillos que golpeamos 
    writer.String(BRICK_HIT);
        writer.StartObject();
        writer.String(ID);
        writer.String(to_string(pBarrs).c_str());
        if(barrs!=NULL){
            writer.String(BRICK_DEL);
            writer.String(to_string(barrs->getHitLft()).c_str());
        }
        writer.EndObject();
    //bloque para la pelota en el campo
    writer.String(BALL_POS);
        writer.StartObject();
        string ballTempName; 
        for(int i =0; i<pBolas; i++){
            ballTempName=POS+to_string(i);
            writer.String(ballTempName.c_str());
            string posBall= to_string(bola[i]->getPx());
            posBall+=",";
            posBall+=to_string(bola[i]->getPy());
            writer.String(posBall.c_str());
        }
        writer.EndObject();
    writer.EndObject();
    return JsonToWrite.GetString();
}

