/*
--------------------------------
TAREA N°2 : APLICACION DE GRAFOS
NOMBRES: VICENTE ROA & BENJAMIN QUEZADA
FECHA :  20 - 10 - 2022
RUT :  21.287.775-1 - 21.158.853-5
---------------------------------
INFO: Construir un programa en C que lea desde el archivo entregado las estaciones
del metro y las conexiones entre estas y muestre un menú que permita elegir los distintos casos.
---------------------------------
*/

/*IMPORTAMOS LA LIBRERIRA*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Definición de constantes
#define numNodos 126
#define infinito 3000000

//  Variable Global
char estaciones[numNodos][40];
bool Visitado[numNodos];
float Costo[numNodos];
int NodoAnterior[numNodos];
int Camino[numNodos];
int Grafo[numNodos][numNodos];

void GrafoConCeros()
{
    /*ESTA FUNCION LO QUE HARA SERA RELLENAR UNA MATRIZ CON 0*/
    int i, j;

    for(i=0; i<numNodos; i++)
    {
        for(j=0; j< numNodos; j++)
        {
            Grafo[i][j] = 0; //LLENA LOS GRAFOS CON 0 EN FILA Y COLUMNA
        }
    }
}
/* CODIGO FUENTE METRO */

int ObtieneNumero(char nomEstacion[40]) //Funcion ObtieneNumero de la matriz
{
    int i;
    for(i=0;i<126;i++)
    {
        if ( strcmp(estaciones[i],nomEstacion) == 0 ) //Compara los 2 string
        /* estaciones[2] se refiere a toda la fila si se pone estaciones[?][?] se refiere a una fila y columna especifica*/
        {
            return i; //Si se cumple la condicion se retorna la variable
        }
    }

}

void inicializaVisitados()
{
    /*USAMOS ESTA FUNCION PARA QUE LOS VISITADOS PARTAN DE FALSO
    LO QUE EN FUNCIONES COMO DIJKSTRA YA CAMBIARAN SU SENTIDOA VERDADERO
    */
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
    char est;

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
        printf("\nNo existe camino."); // EN CASO DE QUE SEA INIFINITO IMPRIMIRA NO EXISTE CAMINO
        return;
    }

    printf("\nCamino: ");
    for (; i>0; i--)
    {
    nodo = Camino[i];
    printf("%s ,", estaciones[nodo]); //IMPRIMIMOS LAS ESTACIONES ADJUNTANDO LOS NUMEROS DEL CAMINO
    }
    nodo = Camino[i];
    printf("%s.", estaciones[nodo]); 
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



void distanciaTotal()
{
    /*CREAMOS LAS VARIABLES*/
    char estacion_origen[100],estacion_destino[100];
    int distancia_1 , distancia_2;
    float distancia_final;

    printf("Estacion Origen: ");
    gets(estacion_origen);
    printf("Estacion Destino: ");
    gets(estacion_destino);


    /*SE 0BTIENE EL NUMERO DE LAS ESTACIONES INGRESADAS*/
        /* PARA PODER ASI LLEVAR A CABO DIJKSTRA*/
    distancia_1 = ObtieneNumero(estacion_origen);  
    distancia_2 = ObtieneNumero(estacion_destino); 
    Dijkstra(distancia_1); // Le pasamos como V0 (Punto Inicial) la distancia ingresada correspondiente a origen

    distancia_final = Costo[distancia_2]/1000.0; //Dividimos Costo en 1000.0 para que muestra los numeros los decimales
    printf("%.2f km.",(distancia_final));

}

void caminoCorto()
{
    /*CREAMOS LAS VARIABLES*/
    int estacion_elegida , estacion_elegida2;
    char estacion_origen[100],estacion_destino[100];

    printf("Estacion Origen: ");
    gets(estacion_origen);
    printf("Estacion Destino: ");
    gets(estacion_destino);

    estacion_elegida = ObtieneNumero(estacion_origen); //Obtenemos el  numero del origen
    estacion_elegida2 = ObtieneNumero(estacion_destino);//Obtenemos el numero del destino
    Dijkstra(estacion_elegida); //Le pasamos V0 la estacion del origen
    imprimeCaminoYCosto(estacion_elegida,estacion_elegida2); /*Usamos esta funcion ya que imprime el recorrido
    correcto de las estaciones que tiene que pasar el usuario*/


}

void cortaTramo()
{
    char estacion_origen[100] , estacion_destino[100];
    char conexion_cortada1[100] , conexion_cortada2[100];
    char *est_cortada1 , *est_cortada2 , *est_cortada3 , *est_cortada4;
    int est_conexion1 , est_conexion2 , est_conexion3 , est_conexion4;
    int num_origen , num_destino;
    /*-----------------------*/
    printf("Estacion Origen:");
    gets(estacion_origen);
    printf("Estacion Destino:");
    gets(estacion_destino);
    /*------------------------*/
    printf("Conexion Cortada 1: ");
    gets(conexion_cortada1);
    printf("Conexion Cortada 2: ");
    gets(conexion_cortada2);
    /*--------SEPARACION CORTADA 1-------------*/
    est_cortada1 = strtok(conexion_cortada1,",");
    est_cortada2 = strtok(NULL , ",");
    /*-------SEPARACI0N CORTADA 2-------------*/
    est_cortada3 = strtok(conexion_cortada2,",");
    est_cortada4 = strtok(NULL,",");
    /*----------------------------------------*/
    /* OBTENEMOS EL NUMERO DE CADA ESTACION*/
    num_origen = ObtieneNumero(estacion_origen);
    num_destino = ObtieneNumero(estacion_destino);
    est_conexion1 = ObtieneNumero(est_cortada1);
    est_conexion2 = ObtieneNumero(est_cortada2);
    est_conexion3 =  ObtieneNumero(est_cortada3);
    est_conexion4 = ObtieneNumero(est_cortada4);
    /*----------------------------------------*/
    //Corta la estaciones de la conexion 1 y 2
    Grafo[est_conexion1][est_conexion2] = 0;
    Grafo[est_conexion2][est_conexion1] = 0;
    //Corta la estaciones de la conexion 3 y 4
    Grafo[est_conexion3][est_conexion4] = 0;
    Grafo[est_conexion4][est_conexion3] = 0;
    /*----------------------------------------*/
    Dijkstra(num_origen);
    imprimeCaminoYCosto(num_origen,num_destino);

}

void menu()
{
    int usuario;

    printf("Seleccione opcion:\n");
    printf("1)Distancia entre estaciones\n");
    printf("2)Ruta entre estaciones\n");
    printf("3)Tramo alternativo en caso de corte\n");
    printf("4)Salir\n\n");
    printf(">> ");
    scanf("%i",&usuario);
    printf("\n");
    fflush(stdin); // LIMPIA LO HAY EN EL BUFFER (YA QUE SE ALMAECENA UN ENTER EN EL SCANF)

    /* SE CREAN LAS CONDICIONALES CADA OPCION LLEVA LA FUNCION CORRESPONDIENTE*/

    if (usuario ==1 )
    {
        distanciaTotal();
    }
    if ( usuario == 2 )
    {
        caminoCorto();
    }
    if (usuario ==3)
    {
        cortaTramo();
    }
    if (usuario == 4)
    {
        exit(1);
    }

}
void leeArchivo()
{
    //VARIABLES
    FILE*archivo;
    int numNodo, i, nodo1,nodo2,distancia;
    char linea[100] , largo;
    char *estacion1 , *estacion2 , *strDistancia;

    GrafoConCeros();
    archivo = fopen("metro.txt","r");
    if (archivo == NULL)
    {
        printf("No se puede abrir.");
        exit(1);
    }
    fscanf(archivo,"%i\n", &numNodo);
    for (i=0;i<126;i++)
    {
        fgets(linea,100,archivo);
        largo = strlen(linea);
        linea[largo - 1] = '\0'; //ELIMINA EL ENTER DEL ARCHIVO
        strcpy(estaciones[i],linea); // COPIA LO DE LA LINEA EN ESTACIONES
    }
    //printf("\n%i",ObtieneNumero("Tobalaba"));
    while (fgets(linea, 400, archivo) != 0)     //Se lee cada línea en la condición del while. Cuando se ha llegado al final del archivo, la función "fgets"
    //retorna 0.
    {
        estacion1 = strtok(linea, ",");     //corta el primer string antes de la primera ","
        estacion2 = strtok(NULL, ",");      //corta el segundo string entre las dos ","
        strDistancia = strtok(NULL, ",");   //corta el tercer string luego de la última ","
        distancia = atoi(strDistancia);     //la función "atoi" transforma el string que tiene la distancia a un número entero.
        nodo1 = ObtieneNumero(estacion1);   //se obtiene el número de la estación1 a partir de su nombre.
        nodo2 = ObtieneNumero(estacion2);   //se obtiene el número de la estación2 a partir de su nombre.
        Grafo[nodo1][nodo2] = distancia;    //llena el grafo con los arcos de las estaciones conectadas.
        Grafo[nodo2][nodo1] = distancia;    //llena el grafo simétricamente.
    }

    fclose(archivo);
}

int main()
{
    leeArchivo(); //LLAMAMOS A LEEARCHIVO()
    menu(); //CREAMOS UNA FUNCION MENU
    return 0;
}