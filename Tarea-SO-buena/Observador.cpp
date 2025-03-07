#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <map>
#include <vector>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

int main()
{

    cout << "Iniciando al observador" << endl;
    cout << "Ingrese la cantidad de jugadores: ";
    int total_jugadores;
    cin >> total_jugadores;

    string fifo_jugadores[total_jugadores];
    string fifo_observer[total_jugadores];

    for (int i = 0; i < total_jugadores; i++)
    {
        string fifo_jugadores = "voto_pipe" + to_string(i);
        string fifo_observer = "respuesta_pipe" + to_string(i);

        mkfifo(fifo_jugadores.c_str(), 0666);
        mkfifo(fifo_observer.c_str(), 0666);
    }

    // crear a los jugadores usando fork
    int tiempo = rand() % 7 + 1;
    for (int i = 0; i < total_jugadores; ++i)
    {
        pid_t pid = fork();
        if (pid < 0)
        {
            cerr << "Error al hacer fork()" << endl;
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {   char tiemp[256];
            sprintf(tiemp, "%d", tiempo);
            char *args[] = {(char *)"./Jugadores", (char *)to_string(i).c_str(), (char *)to_string(total_jugadores).c_str(),tiemp ,NULL};

            execvp("./Jugadores", args);
        }
    }

    int tenedor = fork();
    if (tenedor == 0)
    {
        // conteo de votos

        int jugadores_activos = total_jugadores;
        vector<int> muertos(total_jugadores, 0);

        while (jugadores_activos > 1)
        {
            cout << "Iniciando nueva ronda con " << jugadores_activos << " jugadores." << endl;
            vector<int> votos(total_jugadores, 0);
            for (int i = 0; i < total_jugadores; i++)
            {
                if (muertos[i] == 1)
                {
                    continue;
                }
                string pipe_voto = "voto_pipe" + to_string(i);

                int fd_voto = open(pipe_voto.c_str(), O_RDONLY );
                int buffer;
                read(fd_voto, &buffer, sizeof(buffer));
                while(muertos[buffer] == 1){
                    buffer = rand() % total_jugadores;
                }
                cout << "Jugador " << i << " ha votado por el jugador " << buffer << "." << endl;
                votos[buffer]++;
            }
            int muerto = -1;
            int max_votos = 0;
            for (int i = 0; i < total_jugadores; i++)
            {
                if (votos[i] > max_votos)
                {
                    max_votos = votos[i];
                    muerto = i;
                }
            }

            for (int i = 0; i < total_jugadores; i++)
            {
                
                string pipe_respuesta = "respuesta_pipe" + to_string(i);
                int fd_respuesta = open(pipe_respuesta.c_str(), O_WRONLY | O_NONBLOCK);
                write(fd_respuesta, &muerto, sizeof(muerto));
            }
            muertos[muerto] = 1;
            jugadores_activos--;
        }
        for(int i = 0; i < total_jugadores; i++){
            if(muertos[i] == 0){
                cout << "El jugador " << i << " ha ganado." << endl;
            }
        }
        cout << "El juego ha terminado." << endl;
        exit(0);
    }
    waitpid(tenedor, NULL, 0);
    sleep(2);
    for (int i = 0; i < total_jugadores; i++)
    {

        unlink(fifo_jugadores[i].c_str());
        unlink(fifo_observer[i].c_str());
    }
    return 0;
}