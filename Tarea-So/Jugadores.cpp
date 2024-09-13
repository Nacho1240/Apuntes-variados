#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <iostream>
#include <string.h>

#define PIPE_VOTO "/tmp/voto_pipe"
#define PIPE_RESPUESTA "/tmp/respuesta_pipe"

using namespace std;

void Silla(int jugador_id, int total_jugadores) {
    cout << "Jugador " << jugador_id << " está moviéndose." << endl;
    sleep(rand() % 7 + 1);  // Simula el tiempo de la música

    // Generar un voto aleatorio por otro jugador (evitar auto-voto)
    int voto = -1;
    while (voto == jugador_id) {
        voto = rand() % total_jugadores;
    }

    // Enviar el voto al observador a través del pipe
    int fd_voto = open(PIPE_VOTO, O_WRONLY);
    if (fd_voto == -1) {
        cout << "Error al abrir el pipe para enviar el voto" << endl;
        exit(EXIT_FAILURE);
    }

    // Enviar el voto
    char mensaje_voto[256];
    snprintf(mensaje_voto, sizeof(mensaje_voto), "Jugador %d vota por Jugador %d", jugador_id, voto);
    write(fd_voto, mensaje_voto, strlen(mensaje_voto) + 1);
    close(fd_voto);

    // Recibir la respuesta del observador
    int fd_respuesta = open(PIPE_RESPUESTA, O_RDONLY);
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
