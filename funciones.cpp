#include "funciones.h"
#include <cstdlib>
#include "rlutil.h"
#include <ctime>
#include <string>
#include <vector>

using namespace std;

void menu()
{
    int opcion;
    do
    {
        cout << "\n=== MENU PRINCIPAL ===\n";
        cout << "1. JUGAR\n";
        cout << "2. ESTADISTICAS\n";
        cout << "3. CREDITOS\n";
        cout << "0. SALIR\n";
        cout << "\nElige una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            PedirNombresJugadores();
            break;
        case 2:
            // todo
            cout << "Estadisticas no implementadas aun\n";
            break;
        case 3:
            // todo
            cout << "Creditos no implementados aun\n";
            break;
        case 0:
            cout << "Gracias por jugar. ¡Hasta pronto!\n";
            break;
        default:
            cout << "Opcion no valida. Intenta de nuevo.\n";
        }
    } while (opcion != 0);
}

int tirarDado(int CarasDados)
{
    return rand() % CarasDados + 1;
}

void PedirNombresJugadores()
{
    string jugador1;
    string jugador2;

    rlutil::cls();
    rlutil::locate(30, 12);
    cout << "Ingrese su nombre jugador/a 1: ";
    cin >> jugador1;
    rlutil::cls();
    rlutil::locate(30, 12);
    cout << "Ingrese su nombre jugador/a 2: ";
    cin >> jugador2;
    rlutil::cls();
    QuienEmpiezaRonda(jugador1, jugador2);
    system("pause");
}

void QuienEmpiezaRonda(string jugador1, string jugador2)
{
    int dado1;
    int dado2;
    string ganador;

    rlutil::locate(30, 2);
    cout << jugador1 << " tira su dado.. " << endl;
    dado1 = tirarDado(6);
    rlutil::locate(30, 3);
    cout << "El dado de " << jugador1 << " es: " << dado1 << endl;
    rlutil::locate(30, 4);
    cout << jugador2 << " tira su dado.. " << endl;
    dado2 = tirarDado(6);
    rlutil::locate(30, 5);
    cout << "El dado de " << jugador2 << " es: " << dado2 << endl;

    while (dado1 == dado2)
    {
        rlutil::cls(); // Limpia pantalla para evitar textos superpuestos
        rlutil::locate(30, 6);
        cout << "Empate. Vuelven a tirar los dados.\n";

        dado1 = tirarDado(6);
        dado2 = tirarDado(6);

        rlutil::locate(30, 7);
        cout << jugador1 << " saco: " << dado1 << endl;
        rlutil::locate(30, 8);
        cout << jugador2 << " saco: " << dado2 << endl;

        system("pause"); // Pausa para que el usuario vea el resultado de la nueva tirada
    }

    if (dado1 > dado2)
    {
        rlutil::locate(30, 7);
        cout << " Empieza: " << jugador1 << endl;
        ganador = jugador1;
        jugar(jugador1, jugador2);
    }
    else
    {
        rlutil::locate(30, 7);
        cout << " Empieza: " << jugador2 << endl;
        ganador = jugador2;
        jugar(jugador2, jugador1);
    }
    system("pause");
}

void turnoJugador(string nombre, int &stock, int &puntos, int &dadosUsados, int &objetivo)
{
    vector<int> dados(stock);
    vector<bool> dadosQuemados(stock, false);
    dadosUsados = 0;

    // Tirar dados objetivo
    int dado1 = tirarDado(12);
    int dado2 = tirarDado(12);
    objetivo = dado1 + dado2;

    cout << "\nTurno de: " << nombre << endl;
    cout << "Dado objetivo: " << dado1 << " + " << dado2 << " = " << objetivo << endl;

    // Tira dados del jugador segun el stock que fue recorrido por un for.
    for (int i = 0; i < stock; i++)
    {
        dados[i] = tirarDado(6);
    }

    // Aca mostramos los dados como nos sugirio el profe. basicamente se dividio en dos bucles para en una linea
    // mostrar los indices y abajo los valores.
    cout << "Tus dados:\n";
    for (int i = 0; i < stock; i++)
    {
        cout << "| " << i + 1 << " ";
    }
    cout << "|\n";
    cout << endl;
    
    for (int i = 0; i < stock; i++)
    {
        cout << "| " << dados[i] << " ";
    }
    cout << "|\n";
    cout << endl;

    // Selección de dados por indice
    int suma = 0;
    int cantidadUsados = 0;

    while (suma < objetivo)
    {
        cout << "Elegí el número de dado a usar (0 para rendirte): ";
        int eleccion;
        cin >> eleccion;

        if (eleccion < 0 || eleccion > stock)
        {
            cout << "Elección inválida. Intenta nuevamente." << endl;
            continue;
        }

        if (eleccion == 0)
        {
            cout << "Te rendiste.\n";
            break;
        }

        // Aca comprobamos el vector pa verificar si el dado ya fue usado, si ese dado se uso abajo nosotros vamos a
        // setear la posicion con el valor true. por defecto en la primera tirada todos los valores van a estar en false
        //[false, false, false, false, false, false] <-- estado del vector.
        if (dadosQuemados[eleccion - 1])
        {
            cout << "Este dado ya fue usado. Seleccione otro." << endl;
            continue;
        }

        suma += dados[eleccion - 1];
        // Aca se pisa el valor de false por un true segun la eleccion del jugador
        //[false, false, true, false, false, false] << suponiendo que eligio el dado 3. entonces en la prox vuelta del
        // while va a dar true el if y va a mostra msj y hace continue.... otra vuelta del ciclo
        dadosQuemados[eleccion - 1] = true;
        cout << "Elegiste el dado [" << eleccion << "] con valor " << dados[eleccion - 1] << endl;

        cantidadUsados++;

        if (stock == 0)
        {
            cout << "¡Felicitaciones Utilizaste todos tus dados Ganaste automaticamente! y sumaste 10.000 puntos" << endl;
            cout << "¡Tu puntaje es ! [" << puntos + 10000 << "] " << endl;
        }

        if (suma == objetivo)
        {
            cout << "¡Objetivo alcanzado con " << cantidadUsados << " dados!\n";
            // calcular puntos, transferir dados, etc.
            int puntosGanados = cantidadUsados * suma;
            puntos += puntosGanados;
            dadosUsados += cantidadUsados;

            cout << "¡Objetivo alcanzado! Ganaste " << puntosGanados << " puntos." << endl;
            break;
        }
        if (suma > objetivo)
        {
            cout << "Te pasaste del objetivo. Fin del turno.\n";
            // aca loo hice
            stock = stock + 1;
            break;
        }
    }
}

void imprimirDados(int dados[], int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        cout << dados[i] << " ";
    }
    cout << endl;
}

void jugar(string jugador1, string jugador2)
{
    const int rondas = 3;

    int stockJ1 = 6;
    int stockJ2 = 6;
    int puntosJ1 = 0;
    int puntosJ2 = 0;

    for (int ronda = 1; ronda <= rondas; ronda++)
    {
        cout << "\n======= RONDA " << ronda << " =======\n";

        // Turno Jugador 1
        int usadosJ1 = 0;
        int objetivoJ1 = 0;
        turnoJugador(jugador1, stockJ1, puntosJ1, usadosJ1, objetivoJ1);

        // chequeo de dados usados - suma o resta de los mismos.
        if (usadosJ1 > 0)
        {
            stockJ1 -= usadosJ1;
            stockJ2 += usadosJ1;
            cout << jugador1 << " pasa " << usadosJ1 << " dado(s) a " << jugador2 << ".\n";
        }
        // mostramos los puntajes en ronda
        cout << "\nPuntajes:\n";
        cout << jugador1 << ": " << puntosJ1 << " puntos | Dados: " << stockJ1 << endl;
        cout << jugador2 << ": " << puntosJ2 << " puntos | Dados: " << stockJ2 << endl;
        system("pause");

        // Turno Jugador 2
        int usadosJ2 = 0;
        int objetivoJ2 = 0;
        turnoJugador(jugador2, stockJ2, puntosJ2, usadosJ2, objetivoJ2);
        // chequeo de dados usados - suma o resta de los mismos.
        if (usadosJ2 > 0)
        {
            stockJ2 -= usadosJ2;
            stockJ1 += usadosJ2;
            cout << jugador2 << " pasa " << usadosJ2 << " dado(s) a " << jugador1 << ".\n";
        }
        // mostramos los puntajes en ronda
        cout << "\nPuntajes:\n";
        cout << jugador1 << ": " << puntosJ1 << " puntos | Dados: " << stockJ1 << endl;
        cout << jugador2 << ": " << puntosJ2 << " puntos | Dados: " << stockJ2 << endl;
        system("pause");
    }

    // Resultado final
    cout << "\n======= JUEGO TERMINADO =======\n";
    cout << jugador1 << ": " << puntosJ1 << " puntos\n";
    cout << jugador2 << ": " << puntosJ2 << " puntos\n";

    if (puntosJ1 > puntosJ2)
        cout << "Ganador: " << jugador1 << " 🎉\n";
    else if (puntosJ2 > puntosJ1)
        cout << "Ganador: " << jugador2 << " 🎉\n";
    else
        cout << "¡Empate!\n";
}
