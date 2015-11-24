#include <stdio.h>
#include <stdlib.h>

char matriz[27][27] =  {' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char men_cif[41] = {'m','e','d','i','o','f','l','o','j','e','r','a','e','s','c','r','i','b','i','r'};
char men_des[41] = {'h','m','j','m','b','j','c','s','e','m','x','e','r','w','t','v','d','j','o','v'};

void LlenarMatriz()
{
    int f, c, cont;
    
    for (f = 1 ; f < 27 ; f++)
    {
        for (c = 0 ; c < 27 ; c++)
        {
            // Condicion principal para llenar la matriz
            if( (f > 1) && (c == 0) )
            {
                matriz[f][c] = matriz[f - 1][c + 2]; //Asignacion es para llenar las casillas de todas las filas, correspondientes a la columna "0" (e.g: [0,0], [1,0], [2,0]...)
            }
            else
            {
                if ( (f > 1) || ((f == 1) && (c == 0)) ) //Condicion para que la primera fila no se llene dos veces innecesariamente, y para que matriz[1][0] no quede vacia.
                    matriz[f][c] = matriz[f - 1][c + 1];
            }
            
            // Casos Especiales (arreglan datos especificos de la matriz):
            if ( (f == 1) && (c != 0) ) // Condicion para llenar la primera fila
            {
                matriz[f][c] = matriz[f - 1][c];
            }
            
            if ( (f > 1) && (c == 26) ) // Condicion para llenar la ultima casilla de cada fila (cuando la variable "f" sea mayor a 2)
            {
                matriz[f][c] = matriz[f - 1][c - 25]; // e.g: matriz[2][26] = matriz[1][1]
            }
        }
    }   
}

void SMatriz(int fil, int col)
{
    printf(" %c", matriz[fil][col]);
    
    if (col < 26)
    {
        SMatriz(fil, col + 1);
    }
    else
    {
        printf("\n");
        if (fil < 26)
            SMatriz(fil + 1, col = 0);
    }
}

int Leer(char clave[], int *cif, int *LargoC)
{
    int f, digi, n;
    char cod;

    printf("Desea cifrar (1) o descifrar (2)? \n");
    scanf("%d", cif);
    printf("\n");
    
    printf("Introduzca la clave, concluyendo con el numero '0' (maximo 40 digitos): \n");
    
    for (f = 0 ; f < *LargoC ; f++)
    {
        scanf(" %c", &cod);
        
        if (cod != 48) //Condicion que define la clave, y la variable que contiene su longitud numerica (LargoC)
            clave[f] = cod;
        else
            *LargoC = f;
    }
    
    printf("\n");
    
    printf("Desea digitar el mensaje? (1 = Si - 2 = No): \n");
    scanf("%d", &digi);
    printf("\n");
    
    if ( (*cif == 1) && (digi == 1) )
        printf("Introduzca el mensaje a cifrar, concluyendo con el numero '0': \n"); 
    else
    {
        if (digi == 1)
            printf("introduzca el mensaje a descifrar, concluyendo con el numero '0': \n");
    }
    
    return digi;
}

void Digitar(char EntradaM[], int cif, int digi, int *LargoM)
{
    int f;
    char m;

     if (digi == 1)
    {    
        for (f = 0 ; f < *LargoM ; f++)
        {
            scanf(" %c", &m);
        
            if (m != 48) //Condicion que define el Mensaje de Entrada, y la variable que contiene su longitud numerica (LargoM)
                EntradaM[f] = m;
            else
                *LargoM = f;
        } 
    }
} 

void NoDigitar(char EntradaM[], int cif, int digi, int *LargoM)
{
    int f;
    
    *LargoM = 20;

    if ( (cif == 1) && (digi == 2) )
    {
        for (f = 0 ; f < *LargoM ; f++)
        {
            EntradaM[f] = men_cif[f];
        }
    }
    else
    {
        for (f = 0 ; f < *LargoM ; f++)
        {
            EntradaM[f] = men_des[f];
        }
    }
}

void Cifrado(char clave[], char EntradaM[], char SalidaM[], int LargoM, int LargoC)
{
    int f, c, code = 0, msg = 0;
    char n;
    
    for (f = 0 ; f < 27 ; f++)
    {
        for (c = 0 ; c < 27 ; c++)
        {
            if (matriz[0][c] == clave[code]) // Busca la columna que contenga la letra actual de la clave (en la fila 0)
            {
                n = c; // Guarda el numero de columna en la variable "n"
            }
            
            if (matriz[f][0] == EntradaM[msg]) // Busca la fila que contenga la letra actual del mensaje a encriptar (en la columna 0)
            {
                SalidaM[msg] = matriz[f][n]; /* Guarda el valor que se encuentra en la fila actual, y en el numero de columna guardado anteriormente en la variable "n", 
                                                en el arreglo que contiene el mensaje cifrado */
                                                
                code++; //Se pasa a la siguiente letra de la clave especificada
                msg++; //Se pasa a la siguiente casilla del arreglo cifrado (SalidaM)
                
                // Tanto "f" como "c" se declaran en "0" para realizar el barrido a traves de la matriz nuevamente
                f = 0;
                c = 0;
                
                if (code >= LargoC) //Si se llega a la ultima letra de la clave, se reinicia el contador (variable "code") a "0", iniciando nuevamente desde la primera letra de la clave
                    code = 0;
            }
            
            if (msg == LargoM) //Si se supera el contador que especifica la longitud numerica del mensaje (LargoM), se modifican los valores de la variable "f" y "c" a 27, concluyendo ambos ciclos "for"
            {
                f = 27;
                c = 27;
            }
        }
    }
}

void Descifrado(char clave[], char EntradaM[], char SalidaM[], int LargoM, int LargoC)
{
    int f, c, code = 0, msg = 0;
    
    for (f = 0 ; f < 27 ; f++)
    {
        for (c = 0 ; c < 27 ; c++)
        {
            if (matriz[f][0] != clave[code]) //Se busca la primera letra de la clave en la fila de la matriz (columna 0)
            {
                f++; //Si no se encuentra en la fila actual, se aumenta la variable "f" un valor
                c = 0;
            } 
            else
            {
                if (matriz[f][c] == EntradaM[msg]) //Una vez que la condicion anterior haya sido cumplida, se barrera la fila actual (por columna), hasta conseguir la letra actual del mensaje a descifrar
                {
                    SalidaM[msg] = matriz[0][c]; //Guarda el valor de la fila "0", y la columna actual, en el arreglo que contiene el mensaje descifrado
                    
                    code++; //Se pasa a la siguiente letra de la clave especificada
                    msg++; //Se pasa a la siguiente casilla del arreglo cifrado (SalidaM)
                    
                    // Tanto "f" como "c" se declaran en "0" para realizar el barrido a traves de la matriz nuevamente
                    f = 0;     
                    c = 0;
                    
                    if (code >= LargoC) //Si se llega a la ultima letra de la clave, se reinicia el contador (variable "code") a "0", iniciando nuevamente desde la primera letra de la clave
                        code = 0;
                }
            } 
            
            if (msg == LargoM) //Si se supera el contador que especifica la longitud numerica del mensaje (LargoM), se modifican los valores de la variable "f" y "c" a 27, concluyendo ambos ciclos "for"
            {
                f = 27;
                c = 27;
            } 
        }
    }
}

void Salida(char EntradaM[], char SalidaM[], int cif, int LargoM)
{
    int f;
    if (cif == 1)
    {
        printf("El mensaje a cifrar, era: \n");
        printf("%s \n \n", EntradaM);
            
        printf("El mensaje cifrado, es: \n");
        printf("%s \n \n", SalidaM);
    }
    else
    {
        printf("El mensaje a descifrar, era: \n");
        printf("%s \n \n", EntradaM);
            
        printf("El mensaje descifrado, es: \n");
        printf("%s \n \n", SalidaM);
    }
}

main() //la clave para no digitar es "vigenere"
{
    int cif, digi, LargoC = 40, LargoM = 40, fil = 0, col = 0;
    char clave[41] = {}, EntradaM[41] ={}, SalidaM[41] = {};

    printf("Tabla Vigenere: \n \n");
    
    LlenarMatriz();
    SMatriz(fil,col);
    
    printf("\n \n");
    
    digi=Leer(clave, &cif, &LargoC);
    
    if (digi == 1)
        Digitar(EntradaM, cif, digi, &LargoM);
    else
        NoDigitar(EntradaM, cif, digi, &LargoM);
    
    if (cif == 1)
        Cifrado(clave, EntradaM, SalidaM, LargoM, LargoC);
    else
        Descifrado(clave, EntradaM, SalidaM, LargoM, LargoC);
    
    printf("\n");
    
    Salida(EntradaM, SalidaM, cif, LargoM);
        
    system("pause");
}
