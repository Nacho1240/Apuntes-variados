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

using namespace std;

void eliminar_jugador(int jugador_eliminado, int total_jugadores)
{
    // Simular la función de eliminación de un jugador
    cout << "Jugador " << jugador_eliminado << " ha sido eliminado." << endl;
    execl("./Amurra_y_reclama", "", NULL);
}

int contar_votos(int votos[], int total_jugadores)
{
    // Contar los votos y determinar el jugador con más votos
    int max_votos = 0;
    int jugador_eliminado = -1;

    for (int i = 0; i < total_jugadores; ++i)
    {
        if (votos[i] > max_votos)
        {
            max_votos = votos[i];
            jugador_eliminado = i;
        }
    }

    return jugador_eliminado;
}

void recibir_votos(int total_jugadores, void *votos, string PIPE_VOTO, int numero_jugador)
{
    cout<<"VOTO : "<<PIPE_VOTO<<endl;
    int *casted_votos_p = (int *)votos;
    int arr[total_jugadores];
    for (int i = 0; i < total_jugadores; i++)
    {
        casted_votos_p[i] = arr[i];
    }

    // Abrir el pipe para leer los votos de los jugadores

    int fd_voto = open(PIPE_VOTO.c_str(), O_RDONLY | O_NONBLOCK);
    if (fd_voto == -1)
    {
        cerr << "Error al abrir el pipe para recibir los votos" << endl;
        exit(EXIT_FAILURE);
    }

    
    int buffer;
    
    
        sleep(4);
        read(fd_voto, &buffer, sizeof(buffer));
        printf("BUFFER : %d\n", buffer);
        arr[buffer]++;            // Incrementar el conteo de votos para el jugador votado
        cout << buffer << endl; // Mostrar el voto recibido
    

    close(fd_voto);
}

void enviar_respuestas(int total_jugadores, int jugador_eliminado)
{

    for (int i = 0; i < total_jugadores; i++)
    {
        string PIPE_RESPUESTA = "respuesta_pipe" + to_string(i);

        int fd_respuesta = open(PIPE_RESPUESTA.c_str(), O_WRONLY | O_NONBLOCK);
        if (fd_respuesta == -1)
        {
            cerr << "Error al abrir el pipe para enviar las respuestas" << endl;
            exit(EXIT_FAILURE);
        }
        char mensaje[256];
        for (int i = 0; i < total_jugadores; ++i)
        {
            if (i == jugador_eliminado)
            {
                snprintf(mensaje, sizeof(mensaje), "eliminado");
            }
            else
            {
                snprintf(mensaje, sizeof(mensaje), "continua");
            }
            write(fd_respuesta, mensaje, strlen(mensaje) + 1); // Enviar respuesta
        }
    }

    // Abrir el pipe para enviar las respuestas a los jugadores


}

int main()
{

    string fifo_jugadores[4];
    string fifo_observer[4];

    for (int i = 0; i < 4; i++)
    {
        fifo_jugadores[i] = "voto_pipe" + to_string(i);
        fifo_observer[i] = "respuesta_pipe" + to_string(i);
    }

    srand(time(0)); // Inicializar generador de números aleatorios

    // Solicitar la cantidad de jugadores
    int total_jugadores;
    cout << "Ingrese la cantidad de jugadores: ";
    total_jugadores = 4;

    if (total_jugadores < 2)
    {
        cerr << "Debe haber al menos 2 jugadores para jugar." << endl;
        return 1;
    }

    for (int i = 0; i < 4; i++)
    {
        mkfifo(fifo_jugadores[i].c_str(), 0666);
        mkfifo(fifo_observer[i].c_str(), 0666);
    }

    // Crear jugadores usando fork()
    for (int i = 0; i < total_jugadores; ++i)
    {
        pid_t pid = fork();
        if (pid < 0)
        {
            cerr << "Error al hacer fork()" << endl;
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Proceso hijo: ejecutar el programa del jugador
            execl("./Jugadores", "./Jugadores", to_string(i).c_str(), to_string(total_jugadores).c_str(), NULL);
            cerr << "Error al ejecutar el jugador" << endl;
            exit(EXIT_FAILURE);
        }
    }

    // Esperar a que los jugadores voten y procesar los votos
    int jugadores_activos = total_jugadores;
    int votos[total_jugadores];

    while (jugadores_activos > 1)
    {
        cout << "Iniciando nueva ronda con " << jugadores_activos << " jugadores." << endl;
        for (int i = 0; i < total_jugadores; i++)
        {
            printf("VOTO : %s\n", fifo_jugadores[i].c_str());
            recibir_votos(jugadores_activos, votos, fifo_jugadores[i], i);
        }

        int jugador_eliminado = contar_votos(votos, jugadores_activos);

        eliminar_jugador(jugador_eliminado, jugadores_activos);

        enviar_respuestas(jugadores_activos, jugador_eliminado);

        jugadores_activos--;
    }

    // Esperar a que terminen todos los procesos de los jugadores
    for (int i = 0; i < total_jugadores; ++i)
    {
        wait(NULL);
    }

    cout << "El jugador ganador ha sido determinado." << endl;

    for (int i = 0; i < total_jugadores; i++)
    {
        unlink(fifo_jugadores[i].c_str());
        unlink(fifo_observer[i].c_str());
    }

    return 0;
}