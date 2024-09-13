#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <iostream>
#include <string.h>



using namespace std;

void Silla(int jugador_id, int total_jugadores) {

    cout << "Jugador " << jugador_id << " ha tomado asiento." << endl;
    sleep(2);
    string PIPE_VOTO = "voto_pipe" + to_string(jugador_id);
    string PIPE_RESPUESTA = "respuesta_pipe" + to_string(jugador_id);
    



    cout << "Jugador " << jugador_id << " está moviéndose." << endl;
    sleep(rand() % 7 + 1);  // Simula el tiempo de la música








    // Generar un voto aleatorio por otro jugador (evitar auto-voto)
  

       int voto = rand() % total_jugadores ;
   
    cout << "Jugador " << jugador_id << " ha votado por el jugador " << voto << "." << endl;

    // Enviar el voto al observador a través del pipe
    int fd_voto = open(PIPE_VOTO.c_str(), O_WRONLY | O_NONBLOCK);
    if (fd_voto == -1) {
        cout << "Error al abrir el pipe para enviar el voto" << endl;
        exit(EXIT_FAILURE);
    }

    // Enviar el voto
    write(fd_voto, &voto, sizeof(voto));
    close(fd_voto);

    // Recibir la respuesta del observador
    int fd_respuesta = open(PIPE_RESPUESTA.c_str(), O_RDONLY | O_NONBLOCK);
    if (fd_respuesta == -1) {
        cout << "Error al abrir el pipe para recibir la respuesta" << endl;
        exit(EXIT_FAILURE);
    }

    char respuesta[256];
    read(fd_respuesta, respuesta, sizeof(respuesta));
    cout << "Jugador " << jugador_id << " recibió la respuesta: " << respuesta << endl;
    close(fd_respuesta);

    // Evaluar si fue eliminado o no
    if (strcmp(respuesta, "eliminado") == 0) {
        cout << "Jugador " << jugador_id << " ha sido eliminado del juego." << endl;
    } else {
        cout << "Jugador " << jugador_id << " continúa en el juego." << endl;
    }
}

int main(int argc, char* argv[]) {
    srand(time(0));

    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <jugador_id> <total_jugadores>" << endl;
        return 1;
    }

    int jugador_id = atoi(argv[1]);       // ID del jugador proporcionado por el observador
    int total_jugadores = atoi(argv[2]);  // Total de jugadores proporcionado por el observador

    // Iniciar el juego para este jugador
    Silla(jugador_id, total_jugadores);

    return 0;
}
