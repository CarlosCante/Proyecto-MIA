#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void Split(char Linea[], char delimitador[], char *Destino[])
{
    char *spl;
    int i = 0;

    spl = strtok(Linea,delimitador);

    while(spl != NULL)
    {
        Destino[i] = spl;
        spl = strtok(NULL,delimitador);
        i++;
    }
}

void ConvertirMayusculas(char cadena[])
{
    int i=0;

    for (i=0;cadena[i]!='\0';++i)

    {
        if(cadena[i]>='a' && cadena[i]<='z')

        {
            cadena[i] = cadena[i]- 32;
        }

    }
}

void MKDISK(char *tam, char *dimencion, char *ruta[])
{
    FILE *F;

    F = fopen(ruta,"w+b");
    int t = atoi(tam);
    printf("\n");
    printf("%s",tam);

    if(strcmp(dimencion,"k") == 0)
    {
        t = t * 1024;
    }

    if(strcmp(dimencion,"m") == 0)
    {
        t = t * 1024 * 1024;
    }

    char c[1] = "\0";

    for (int i = 0; i < t; i++)
    {
        fwrite(&c, sizeof c, 1, F);
    }
    fflush(F);
    fclose(F);
}

void CrearDisco(char *tam, char *dimencion, char *ruta)
{
    char *Tama[2];
    char *Dim[2];
    char *path[2];
    char path2[31];

    Split(tam,"=",Tama);
    Split(dimencion,"=",Dim);
    Split(ruta,"=",path);

    strcpy(path2,path[1]);
    printf(path2);

    CrearDirectorio(path2);

    MKDISK(Tama[1],Dim[1],path[1]);

}

void CrearDirectorio(char *ruta2)
{
    char *spl;
    int i = 0;
    char Destino[500] = "\0";
    int agregar = 1;

    char *ruta = ruta2;

    spl = strtok(ruta,"/");

    while(spl != NULL)
    {
        for(int j = 0 ; j < strlen(spl) ; j++)
        {
            if(spl[j] == '.')
            {
                agregar = 0;
            }
        }

        if(agregar == 1)
        {

            strcat(Destino,"/");
            strcat(Destino,spl);
            mkdir(Destino,0700);
        }

        agregar = 1;

        spl = strtok(NULL,"/");
    }

}


int main()
{


    char Comando[]="mkdisk -size=100 -unit=k -path=/home/carlos/hola/abc/disk.dsk";
    char *cadenas[10];

    printf("Ingrese un comando: ");
    //fgets(Comando, 100, stdin);

    Split(Comando," ",cadenas);

    ConvertirMayusculas(cadenas[0]);

    //*****************************************MKDISK***************************************

    if(strcmp(cadenas[0],"MKDISK") == 0)
    {
        CrearDisco(cadenas[1],cadenas[2],cadenas[3]);
    }


    return 0;
}

