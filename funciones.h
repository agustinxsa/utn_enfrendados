#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <string>
using namespace std;


void menu();
void jugar(string jugador1,string jugador2);
int tirarDado(int CarasDados);
void rondas();
void PedirNombresJugadores();
void QuienEmpiezaRonda(string jugador1, string jugador2);

void NewFunction(int &stock, std::__1::vector<int> &dados);

#endif // FUNCIONES_H_INCLUDED
