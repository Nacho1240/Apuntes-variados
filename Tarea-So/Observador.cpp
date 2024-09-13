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
#include <sys/stat.h>
#include <sys/wait.h>



#define PIPE_VOTO "/tmp/voto_pipe"       // Pipe para recibir votos
#define PIPE_RESPUESTA "/tmp/respuesta_pipe"  // Pipe para enviar respuestas

using namespace std;

void eliminar_jugador(int jugador_eliminado, int total_jugadores) {
    // Simular la función de eliminación de un jugador
    cout << "Jugador " << jugador_eliminado << " ha sido eliminado." << endl;
    execl("./Amurra_y_reclama","",NULL);
}

int contar_votos(int votos[], int total_jugadores) {
    // Contar los votos y determinar el jugador con más votos
    int max_votos = 0;
    int jugador_eliminado = -1;

    for (int i = 0; i < total_jugadores; ++i) {
        if (votos[i] > max_votos) {
            max_votos = votos[i];
            jugador_eliminado = i;
        }
    }

    return jugador_eliminado;
}

void recibir_votos(int total_jugadores, int votos[]) {
    // Abrir el pipe para leer los votos de los jugadores
    int fd_voto = open(PIPE_VOTO, O_RDONLY);
    if (fd_voto == -1) {
        cerr << "Error al abrir el pipe para recibir los votos" << endl;
        exit(EXIT_FAILURE);
    }

    // Inicializar los votos a 0
    memset(votos, 0, sizeof(int) * total_jugadores);

    char buffer[256];
    for (int i = 0; i < total_jugadores; ++i) {
        read(fd_voto, buffer, sizeof(buffer));
        int jugador_votante, voto;
        sscanf(buffer, "Jugador %d vota por Jugador %d", &jugador_votante, &voto);
        votos[voto]++;  // Incrementar el conteo de votos para el jugador votado
        cout << buffer << endl;  // Mostrar el voto recibido
    }

    close(fd_voto);
}

void enviar_respuestas(int total_jugadores, int jugador_eliminado) {
    // Abrir el pipe para enviar las respuestas a los jugadores
    int fd_respuesta = open(PIPE_RESPUESTA, O_WRONLY);
    if (fd_respuesta == -1) {
        cerr << "Error al abrir el pipe para enviar las respuestas" << endl;
        exit(EXIT_FAILURE);
    }

    char mensaje[256];
    for (int i = 0; i < total_jugadores; ++i) {
        if (i == jugador_eliminado) {
            snprintf(mensaje, sizeof(mensaje), "eliminado");
        } else {
            snprintf(mensaje, sizeof(mensaje), "continua");
        }
        write(fd_respuesta, mensaje, strlen(mensaje) + 1);  // Enviar respuesta
    }

    close(fd_respuesta);
}

int main() {
    srand(time(0));  // Inicializar generador de números aleatorios

    // Solicitar la cantidad de jugadores
    int total_jugadores;
    cout << "Ingrese la cantidad de jugadores: ";
    total_jugadores = 4;

    if (total_jugadores < 2) {
        cerr << "Debe haber al menos 2 jugadores para jugar." << endl;
        return 1;
    }

    // Crear pipes con nombre para la comunicación
    mkfifo(PIPE_VOTO, 0666);  
    mkfifo(PIPE_RESPUESTA, 0666); 

    // Crear jugadores usando fork()
    for (int i = 0; i < total_jugadores; ++i) {
        pid_t pid = fork();
        if (pid < 0) {
            cerr << "Error al hacer fork()" << endl;
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Proceso hijo: ejecutar el programa del jugador
            execl("./Jugadores", "", NULL);  // Ejecuta el archivo Jugador.cpp
            cerr << "Error al ejecutar el jugador" << endl;
            exit(EXIT_FAILURE);
        }
    }

    // Esperar a que los jugadores voten y procesar los votos
    int jugadores_activos = total_jugadores;
    int votos[total_jugadores];

    while (jugadores_activos > 1) {
        cout << "Iniciando nueva ronda con " << jugadores_activos << " jugadores." << endl;


        recibir_votos(jugadores_activos, votos);

        int jugador_eliminado = contar_votos(votos, jugadores_activos);
        eliminar_jugador(jugador_eliminado, jugadores_activos);

        enviar_respuestas(jugadores_activos, jugador_eliminado);

        jugadores_activos--;
    }

    // Esperar a que terminen todos los procesos de los jugadores
    for (int i = 0; i < total_jugadores; ++i) {
        wait(NULL);
    }

    cout << "El jugador ganador ha sido determinado." << endl;

    unlink(PIPE_VOTO);
    unlink(PIPE_RESPUESTA);

    return 0;
}