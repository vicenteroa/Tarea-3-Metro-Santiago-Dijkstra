#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*Definición de constantes: */
#define numNodos 10
#define infinito 3000000


bool Visitado[numNodos];
int Costo[numNodos];
int NodoAnterior[numNodos];
int Camino[numNodos];
int Grafo[numNodos][numNodos];

void llenaGrafoConCeros()
{
    int i, j;

    for(i=0; i<numNodos; i++)
    {
        for(j=0; j< numNodos; j++)
        {
            Grafo[i][j] = 0;
        }
    }
}
void inicializaVisitados()
{
    int i;

    for(i=0; i<numNodos; i++)
    {
        Visitado[i] = false;
    }
}
/*Imprime un camino generado por Dijkstra, desde el nodo v0 al nodo vf.*/
void imprimeCaminoYCosto(int v0, int vf)
{
    int i, nodo;

    i = 0;
    Camino[i] = vf;
    i++;
    nodo = NodoAnterior[vf];
    while(nodo != v0)
    {
        Camino[i] = nodo;
        i++;
        nodo = NodoAnterior[nodo];
    }
    Camino[i] = nodo;
    if (Costo[vf] == infinito)
    {
        printf("\nNo existe camino.");
        return;
    }
    printf("\nCamino: ");
    for (; i>0; i--)
    {
        nodo = Camino[i];
        printf("%i, ", nodo);
    }
    nodo = Camino[i];
    printf("%i.", nodo);
    printf("\nCosto: %i", Costo[vf]);
}
int cantidadNodosSinVisitar()
{
    int i, cont;

    i = 0;
    cont = 0;

    for(i=0; i<numNodos; i++)
    {
        if (!Visitado[i])
        {
            cont++;
        }
    }
   return cont;
}
int nodoMinimoCostoSinVisitar()
{
    int i, nodo, minimo;
    bool esElPrimero;

    esElPrimero = true;
    i = 0;
    for(i=0; i<numNodos; i++)
    {
        if (!Visitado[i])
        {
            if (esElPrimero)
            {
                minimo = Costo[i];
                nodo = i;
                esElPrimero = false;
            }
            else
            {
                if (Costo[i] < minimo)
                {
                    minimo = Costo[i];
                    nodo = i;
                }
            }
        }
    }
    return nodo;
}
void Dijkstra(int v0)
{
    int i, j, nodoSeleccionado;

    inicializaVisitados();  //Inicialmente todos los nodos están sin visitar (arreglo "Visitados" parte con "falsos".
    Visitado[v0] = true;    //Se marca como visitado a v0
    for(i=0;i<numNodos;i++)
    {
        if (Grafo[v0][i] == 0)  //Si el nodo i no tiene un arco directo desde v0 entonces:
        {
            Costo[i] = infinito;     //El costo del nodo i es infinitoinito
        }
        else
        {
            Costo[i] = Grafo[v0][i];    //Si i tiene un arco directo el costo al nodo es el costo del arco desde v0.
        }
        NodoAnterior[i] = v0;   //El nodo anterior de todos los nodos es v0 (valor entre paréntesis)
    }
    while (cantidadNodosSinVisitar()>0)
    {
        nodoSeleccionado = nodoMinimoCostoSinVisitar(); //Escoge al nodo con menor costo y que no esté visitado.

        Visitado[nodoSeleccionado] = true;  //El nodo escogido se marca como visitado.
        for(j=0;j<numNodos;j++)
        {
            if ((Grafo[nodoSeleccionado][j] != 0) && (!Visitado[j])) //Si el nodo j es adyacente al nodo elegido, y no está visitado:
            {
                if (Costo[nodoSeleccionado] + Grafo[nodoSeleccionado][j] < Costo[j]) //Si el costo es menor a través del nodo elegido:
                {
                    Costo[j] = Costo[nodoSeleccionado] + Grafo[nodoSeleccionado][j]; //Se actualiza el costo para llegar al adyacente.
                    NodoAnterior[j] = nodoSeleccionado; //Se actualiza el nodo anterior para llegar al adyacente.

                }
            }
        }
    }
}
void leeArchivo(char nomArchivo[30])
{
    FILE *archivo;
    int valor, nodo1, nodo2, distancia;

    archivo = fopen(nomArchivo, "r");
    fscanf(archivo, "%i", &valor); //No se ocupa la variable "valor".
    llenaGrafoConCeros();
    while (fscanf(archivo, "%i", &nodo1) != EOF)
    {
        fscanf(archivo, "%i", &nodo2);
        fscanf(archivo, "%i", &distancia);
        Grafo[nodo1][nodo2] = distancia;
        Grafo[nodo2][nodo1] = distancia;
    }
    fclose(archivo);
}
int main()
{
    char nomArchivo[30];
    int v0, vf;

    printf("Ingresa el nombre del archivo: ");
    gets(nomArchivo);
    leeArchivo(nomArchivo);
    printf("Ingresa nodo desde donde quieres partir: ");
    scanf("%i", &v0);
    printf("Ingresa nodo a donde quieres llegar: ");
    scanf("%i", &vf);
    Dijkstra(v0);
    imprimeCaminoYCosto(v0, vf);
    printf("\n\n");
    return 0;
}
