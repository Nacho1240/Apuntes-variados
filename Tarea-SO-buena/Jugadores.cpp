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

int main(int argc, char *argv[])
{
    int tiempo = atoi(argv[3]);
        sleep(tiempo);

    string pipe_voto = "voto_pipe" + to_string(atoi(argv[1]));
    string pipe_respuesta = "respuesta_pipe" + to_string(atoi(argv[1]));

    int jugador_id = atoi(argv[1]);
    int total_jugadores = atoi(argv[2]);
        srand(time(NULL)+jugador_id);

    int fd_voto = open(pipe_voto.c_str(), O_WRONLY);

    cout << "Jugador " << jugador_id << " ha tomado asiento." << endl;

    int voto = rand() % total_jugadores;
    write(fd_voto, &voto, sizeof(voto));

    int Loser;
    int fd_respuesta = open(pipe_respuesta.c_str(), O_RDONLY);

    read(fd_respuesta, &Loser, sizeof(Loser));
    if (Loser == jugador_id)
    {
        cout << "Jugador " << jugador_id << " ha sido eliminado." << endl;
        execl("./Amurrar", "", NULL);
    }
    else
    {
        cout << "Jugador " << jugador_id << " ha pasado a la siguiente ronda." << endl;
        execvp("./Jugadores", argv);
    }

    return 0;
}