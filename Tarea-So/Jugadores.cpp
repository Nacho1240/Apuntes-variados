#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <string.h>
#include <cstdlib>
#include <fcntl.h>



#define PIPE_voto "/tmp/voto_pipe"

#define PIPe_respuesta "/tmp/respuesta_pipe"

using namespace std;

void Silla(int jugador_id, int Cantidad_jugadores){
    cout<<"Ejecutando Test 1"<<endl;
    sleep(rand()%7+1);



int voto = -1;
while (voto == jugador_id){
    voto = rand()%Cantidad_jugadores;
}



int fd_voto = open(PIPE_voto, O_WRONLY);
    if (fd_voto == -1) {
        cout << "Error al abrir el pipe para enviar el voto" << endl;
        exit(EXIT_FAILURE);
    }


//manejo y envio de votos
char mensaje_voto[256];

    snprintf(mensaje_voto, sizeof(mensaje_voto), "Jugador %d vota por Jugador %d", jugador_id, voto);    
    write(fd_voto, mensaje_voto, strlen(mensaje_voto) + 1); 
    close(fd_voto);

//recepcion de votos del observador
 int fd_respuestas = open(PIPe_respuesta, O_RDONLY);
    cout<<"Test 2"<<endl;

    if (fd_respuestas == -1) {
        cout << "Error al abrir el pipe para recibir la respuesta" << endl;
        exit(EXIT_FAILURE);
    }

char respuesta[256];

    read(fd_respuestas, respuesta, sizeof(respuesta)); 
    cout<<"Test 3"<<endl;
    cout << "Jugador " << jugador_id << " recibió la respuesta: " << respuesta << endl;
    close(fd_respuestas);




    if (strcmp(respuesta, "eliminado") == 0) {
        cout << "Jugador " << jugador_id << " ha sido eliminado del juego." << endl;
    } else {
        cout << "Jugador " << jugador_id << " continúa en el juego." << endl;
    }
}


int main() {
    srand(time(0)); 

    
    int total_jugadores;



    cout << "Ingrese la cantidad de jugadores: ";
    cin >> total_jugadores;

    if (total_jugadores < 2) {

        cerr << "Debe haber al menos 2 jugadores para jugar." << endl;
        return 1;

    }

 
    int jugador_id = rand() % total_jugadores;

    
    Silla(jugador_id, total_jugadores);

    return 0;
}








   

