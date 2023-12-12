//Jaime Alvarez-Cienfuegos Martinez
//Jesus Abajo Magro

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <string>

using namespace std;

//definiion de la array
const int NumFichas = 28;
typedef short int tArray[NumFichas];


#pragma region Funciones
//Declaracion de funciones
int mostrarMenu(tArray& fichas1, tArray& fichas2, int& fichasCont, int& eleccion);// muestra el menú y devuelve la opción(válida) elegida.
string fichaToStr(tArray izquierda, tArray derecha, int i);// devuelve una cadena que representa la ficha : | izquierda - derecha |.
string toStr(tArray n, int i);// devuelve una cadena que contiene el número.
void generaPozo(tArray pozo1, tArray pozo2, short int maxValor);//Genera en pozo1 y pozo2 las partes izquierda y derecha de todas las piezas posibles del dominó para fichas con valores de 0 a maxValor
void desordenaPozo(tArray pozo1, tArray pozo2); // desordena el pozo


void mostrarTablero(string tablero, short int numColocadas, short int numRobadas, tArray& fichas1, tArray& fichas2, short int fichasCont);//Escribe en pantalla toda la información visible de la situación actual de la partida, incluyendo las fichas del jugador codificadas en fichas1, fichas2 y fichasCont(a esta función no le concierne el pozo, pues no se muestra)
short int sumaPuntos(tArray fichas1, tArray fichas2, int& fichasCont);//Suma los puntos acumulados en todas las fichas del jugador
void robaFicha(tArray pozo1, tArray pozo2, short int& cont, short int& fichaN1, short int& fichaN2); //Quita la última ficha del pozo (codificado en pozo1, poz2 y cont) y pone dicha ficha en fichaN1 y fichaN2
void eliminaFicha(tArray fichas1, tArray fichas2, int& fichasCont, short int fichaNum);//Quita de las fichas del jugador (representadas por ficha1, ficha2 y fichasCont) su ficha fichaNum - ésima(almacenada en las posiciones fichaNum - 1 de sendos arrays), desplazando el resto de posiciones a la izquierda para rellenar el hueco dejado por la ficha quitada


bool puedePonerIzq(string tablero, tArray fichas1, tArray fichas2, int& eleccion);// indica si se puede colocar la ficha a la izquierda de la fila.
bool puedePonerDer(string tablero, tArray fichas1, tArray fichas2, int& eleccion);// indica si se puede colocar la ficha a la derecha de la fila.
string ponerFichaIzq(string& tablero, tArray fichas1, tArray fichas2, int& fichasCont, int& eleccion);// coloca la ficha a la izquierda de la fila.
string ponerFichaDer(string& tablero, tArray fichas1, tArray fichas2, int& fichasCont, int& eleccion);// coloca la ficha a la derecha de la fila
bool puedeColocarFicha(tArray& fichas1, tArray& fichas2, short int fichasCont, string tablero, int& eleccion);//Comprueba si el jugador puede poner alguna de sus fichas en el tablero
#pragma endregion

#pragma region Funciones Globales
//declaracion de variables globales
string tablero;
short int fichaN1, fichaN2;
short int izquierda, derecha;
tArray pozo1, pozo2;
tArray fichas1, fichas2;
short int cont=6;
int numRobadas;
int numColocadas;
int i = 0;
int eleccion;
int fichasMano = 0;
int fichasCont;
int num1, num2;
#pragma endregion


#pragma region Main

int main()//funcion principal que llama al resto para que el programa se ejecute
{
tArray ficha1, ficha2;
short int maxValor = 6;//valor maximo aue toman las fichas
short int cont = 0;

generaPozo(pozo1, pozo2, maxValor);//genera el pozo con todas las fihcas con valores de 0 a 6

desordenaPozo(pozo1, pozo2);//desordena las fichas creadas

//Roba las 7 primeras fichas
robaFicha(pozo1, pozo2, cont, fichaN1, fichaN2);
fichasMano++;
robaFicha(pozo1, pozo2, cont, fichaN1, fichaN2);
fichasMano++;
robaFicha(pozo1, pozo2, cont, fichaN1, fichaN2);
fichasMano++;
robaFicha(pozo1, pozo2, cont, fichaN1, fichaN2);
fichasMano++;
robaFicha(pozo1, pozo2, cont, fichaN1, fichaN2);
fichasMano++;
robaFicha(pozo1, pozo2, cont, fichaN1, fichaN2);
fichasMano++;
robaFicha(pozo1, pozo2, cont, fichaN1, fichaN2);
fichasMano++;


//inicializacion de los contadores de robar y colocar
numRobadas = 0;
numColocadas = 0;


tablero = fichaToStr(fichas1, fichas2, i);//coloca la primera ficha del tablero que es la robada en la linea 56


while (mostrarMenu(fichas1, fichas2, fichasCont, eleccion) != 0) {//llamam al menu y comienza el juego


mostrarMenu(fichas1, fichas2, fichasCont, eleccion);

}


return 0;

}
#pragma endregion


#pragma region Mostrar Tablero
void mostrarTablero(string tablero, short int numColocadas, short int numRobadas, tArray& fichas1, tArray& fichas2, short int fichasCont)
{


cout << "-------------------" << endl;
cout << "|     TABLERO     |" << endl;
cout << "-------------------" << endl;
cout << tablero << endl;//muestra las fichas del tablero
//se muestran los contadores de robadas y colocadas
cout << "Fichas colocadas:" << numColocadas << endl;
cout << "Fichas Robadas:" << numRobadas << endl;
cout << "Fichas del jugador: ";//enseña la mano del jugador



for (int i = 0; i <= cont; i++) {
//este bucle enseña todas las fichas de la mano del jugador

cout << i + 1 << "." << fichaToStr(fichas1, fichas2, i) << " ";

}




cout << endl;
}
#pragma endregion


#pragma region Mostrar Menu
int mostrarMenu(tArray& fichas1, tArray& fichas2, int& fichasCont, int& eleccion)
{
int opcion = -1;



while ((opcion < 0) || (opcion > 4))
{
system("cls"); //esta es la funcion que actualiza la pantalla.

mostrarTablero(tablero, numColocadas, numRobadas, fichas1, fichas2, fichasCont);//Escribe en pantalla toda la información visible de la situación actual de la partida, incluyendo las fichas del jugador codificadas en fichas1, fichas2 y fichasCont(a esta función no le concierne el pozo, pues no se muestra)

cout << "-------------------------" << endl;
cout << "|   MENU DE OPCIONES    |" << endl;
cout << "-------------------------" << endl;
cout << "1-Poner Ficha por la izquierda" << endl;
cout << "2-Poner Ficha por la derecha" << endl;
cout << "3-Robar ficha" << endl;
cout << "0-Salir" << endl;
cout << "Elija opcion: ";
cin >> opcion;

if ((opcion < 0) || (opcion > 4))
{
cout << "Opcion no valida" << endl;//se enseña cuando no se puede realizar la accion deseada y nos devuelve al menu

}


if (opcion == 0) {

cout << "Salir." << endl;//cierra el programa y termina la partida

exit(0);

}
}
switch (opcion) {


case 1://caso para poner una ficha a la izquierda
{
if (puedeColocarFicha(fichas1, fichas2, fichasCont, tablero, eleccion) == 1) {


tablero = ponerFichaIzq(tablero, fichas1, fichas2, fichasCont, eleccion);//coloca la ficha a la izquierda


}

else {


cout << "No se puede poner ficha por la izquierda.\n" << endl;//se enseña cuando no se puede realizar la accion deseada y nos devuelve al menu
system("pause");
}

}
break;





case 2://caso para poner una ficha a la derecha
{
if (puedeColocarFicha(fichas1, fichas2, fichasCont, tablero, eleccion) == 1) {

tablero = ponerFichaDer(tablero, fichas1, fichas2, fichasCont, eleccion);//coloca la ficha a la derecha



}

else {


cout << "No se puede poner ficha por la derecha.\n" << endl;//se enseña cuando no se puede realizar la accion deseada y nos devuelve al menu
system("pause");
}

}
break;




case 3:
{


if (numRobadas < 27 ) {

robaFicha(pozo1, pozo2, cont, fichaN1, fichaN2);//roba la siguiente ficha del pozo

numRobadas++;//aumenta el contador de robadas ya que se ha robado un a ficha

fichasMano++;
}

else {

cout << endl;

cout << "No quedan fichas" << endl;

system("pause");

return opcion;

}

if (fichasMano < 7) {

robaFicha(pozo1, pozo2, cont, fichaN1, fichaN2);//roba la siguiente ficha del pozo

numRobadas++;//aumenta el contador de robadas ya que se ha robado un a ficha

fichasMano++;


}

else {

sumaPuntos(fichas1, fichas2, fichasCont);


exit(0);


}




}
break;


}


return opcion;
}
#pragma endregion


#pragma region Ficha to String
string fichaToStr(tArray izquierda, tArray derecha, int i)
{
int num1 = izquierda[i];
int num2 = derecha[i];

return "|" + to_string(num1) + "-" + to_string(num2) + "|";//genera las fichas con su correspondiente formato

i++;
}
#pragma endregion


#pragma region To String
string toStr(tArray n, int i)
{

int num = n[i];

return to_string(num);//transforma un numero en un string
}
#pragma endregion


#pragma region Robar Ficha
void robaFicha(tArray pozo1, tArray pozo2, short int& cont, short int& fichaN1, short int& fichaN2)
{
//al estar ya desordenado el pozo, esta funcion elige la primera ficha
//y va recorriendo el pozo el pozo sacando finalmente todas las fichas

fichas1[cont] = pozo1[cont];
fichas2[cont] = pozo2[cont];
fichaN1 = fichas1[cont];
fichaN2 = fichas2[cont];
cont++;


//correrPosicion(pozo1, pozo2, cont);//vacia el espacio usado por numero en los pozos

}
#pragma endregion


#pragma region Eliminar Ficha
void eliminaFicha(tArray fichas1, tArray fichas2, short int& fichasCont, short int fichaNum, int& eleccion)
{
int pos = 0;
//la pos es la ficha que elegimos para colocar en le tablero
pos = 1;

}
#pragma endregion


#pragma region Puede Izquierda
bool puedeColocarFicha(tArray& fichas1, tArray& fichas2, short int fichasCont, string tablero, int& eleccion)
{

//esta funcion comprueba si la ficha elegida se puede colocar ala izquierda del tablero

string fichaNI;

fichaNI = tablero[1];

return(fichaNI == toStr(fichas1, eleccion) || fichaNI == toStr(fichas2, eleccion));



//esta funcion comprueba si la ficha elegida se puede colocar a la derecha del tablero

string fichaND;

fichaND = tablero[tablero.length() - 2];

return(fichaND == toStr(fichas1, eleccion) || fichaND == toStr(fichas2, eleccion));

}
#pragma endregion


#pragma region Poner Izquierda
string ponerFichaIzq(string& tablero, tArray fichas1, tArray fichas2, int& fichasCont, int& eleccion)
{
//esta funcion despues de comprobar si se puede poner una ficha  a la izquierda, la coloca
//rotando la ficha en le caso de que sea necesario
int i = 0;
string fichaNI;
fichaNI = tablero[1];

if (fichaNI == toStr(fichas2, eleccion)) {//coloca la ficha como en la mano

tablero = fichaToStr(fichas1, fichas2, i) + tablero;
numColocadas++;
robaFicha(pozo1, pozo2, cont, fichaN1, fichaN2);

}

if (fichaNI == toStr(fichas1, eleccion)) {//rota las posiciones de la ficha de la amno a colocar

tablero = fichaToStr(fichas2, fichas1, i) + tablero;
numColocadas++;
robaFicha(pozo1, pozo2, cont, fichaN1, fichaN2);



}
cont--;
return tablero;
}
#pragma endregion


#pragma region Poner Derecha
string ponerFichaDer(string& tablero, tArray fichas1, tArray fichas2, int& fichasCont, int& eleccion)
{
//esta funcion despues de comprobar si se puede poner una ficha  a la derecha, la coloca
//rotando la ficha en le caso de que sea necesario
int i = 0;
string fichaND;
fichaND = tablero[tablero.length() - 2];

if (fichaND == toStr(fichas1, eleccion)) {//coloca la ficha como en la mano

tablero = tablero + fichaToStr(fichas1, fichas2, i);
numColocadas++;
robaFicha(pozo1, pozo2, cont, fichaN1, fichaN2);

}

if (fichaND == toStr(fichas2, eleccion)) {//rota las posiciones de la ficha de la amno a colocar

tablero = tablero + fichaToStr(fichas2, fichas1, i);
numColocadas++;
robaFicha(pozo1, pozo2, cont, fichaN1, fichaN2);


}
cont--;
return tablero;
}
#pragma endregion


#pragma region Generar Pozo
void generaPozo(tArray pozo1, tArray pozo2, short int maxValor)
{
//esta funcion genera el pozo de fichas con sus dos partes izquierda y derecha

short int indice = 0;

for (short int izquierda = 0; izquierda <= maxValor; izquierda++) {//esta aperte genere las partes izquierdas


for (short int derecha = izquierda; derecha <= maxValor; derecha++) {//y esta le hace corresponder a las izquierdas las propias a la derecha

pozo1[indice] = izquierda;
pozo2[indice] = derecha;
indice++;
}

}




}
#pragma endregion


#pragma region Desordenar Pozo
void desordenaPozo(tArray pozo1, tArray pozo2) {//funcion dada en la hoja de la practica que hace que las posiciones del pozo sean aleatorias
int idx, i;
short int tmp1, tmp2;
for (int i = NumFichas - 1; i >= 0; i--) {
idx = rand() % (i + 1);
if (i != idx) {
tmp1 = pozo1[i];
tmp2 = pozo2[i];
pozo1[i] = pozo1[idx];
pozo2[i] = pozo2[idx];
pozo1[idx] = tmp1;
pozo2[idx] = tmp2;
}
}
}
#pragma endregion


short int sumaPuntos(tArray fichas1, tArray fichas2, int& fichasCont) {

cout << endl;

int puntos;


puntos = fichas1[cont] + fichas2[cont];

cout << "Tus puntos son:" << puntos << endl;


return 0;
}




	void correrPosicion(tArray izquierda, tArray derecha, short int contador)
	{

		for (int i = contador - 1; i < contador - 1; i++) {
			izquierda[i] = izquierda[i + 1];
			derecha[i] = derecha[i + 1];
		}
		contador--;


	}


//en eliminar fiicha
	//correrPosicion(fichas1, fichas2, fichasCont);

