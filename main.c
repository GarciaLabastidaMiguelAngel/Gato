/* 
 * File:   main.c
 * Author: edward hernadez santiago, perez peralta mauricio, garcia labastida miguel angel
 *
 * Created on 28 de abril de 2014, 11:50 AM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
enum bool {FALSE, TRUE};
typedef enum bool boolean;

void imprime(char m[][3]);
boolean gana(char c,char m[][3]);
void tiro_max(char c,char m[][3]);
int juega_min(char c,char m[][3]);
int minimo(char c,char m[][3]);
int posibilidades(char c,char m[][3]);
boolean pierde(char c,char m[][3]);
/*un pequeño main :D*/
int main(int argc, char** argv) {
    char m[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    int op,fila,columna,tiros;
    char c;
    tiros=0;
    do{
        printf("\nelige 1 o 2 para tu ficha de tiro\n X=>1\nO=>2\n=>");
        scanf("%d",&op);
        if(op==1)
            c='x';
        if(op==2)
            c='o';
        if(op>2 || op<1)
            printf("\nERROR: ingresa una opcion valida....\n");
    }while(op>2 || op<1);
    
    do{
        printf("\npresiona 1 para tirar primero o 2 para tirar en segundo lugar\n=>");
        scanf("%d",&op);
        if(op>2 || op<1)
            printf("\nERROR: ingresa una opcion valida....\n");
    }while(op>2 || op<1);
    if(op==1){
        ++tiros;
        printf("\ningresa la fila:");
        scanf("%d",&fila);
         printf("\ningresa la columna:");
        scanf("%d",&columna);
        m[fila-1][columna-1]=c;
    }

    do{
       if(c=='x'){
           ++tiros;
           printf("\ntiro maquina\n");
           if(!pierde(c,m)){
            tiro_max('o',m);
            if(gana('o',m))
                break ;
           }
       }
        else{
           ++tiros;
            printf("\ntiro maquina\n");
            if(!pierde(c,m)){
            tiro_max('x',m);
            if(gana('x',m))
                break ;
            }
        }
       if(tiros==9)
           break;
       imprime(m);
       ++tiros;
       do{
        printf("\ningresa la fila:");
        scanf("%d",&fila);
         printf("\ningresa la columna:");
        scanf("%d",&columna);
        if( fila>0 && fila<4 && columna>0 && columna<4 && m[fila-1][columna-1]==' ')
            break;
        else
            printf("\nverifica tus datos o que la posicion este disponible..\n");
       }while(TRUE);
        m[fila-1][columna-1]=c;
        if(gana(c,m))
            break;
        imprime(m);
        
    }while(tiros<9);
    if(gana(c,m)){
        printf("jugador GANASTE FELICIDADES..... :/ no debias ganar jejejeje");
        imprime(m);
    }
    else
        if(c=='x'){
            if(gana('o',m)){
                printf("\njugador PERDISTE!! sigue participando...\n");
                imprime(m);
            }
            else{
                printf("\nEMPATE!!!!\n");
                imprime(m);
            }
        }
        else{
            if(gana('x',m)){
                printf("\njugador PERDISTE!! sigue participando...\n");
                imprime(m);
            }
            else{
                printf("\nEMPATE!!!!\n");
                imprime(m);
            }
        }
    
    return (EXIT_SUCCESS);
}
/*este metodo valida si ya existe algun ganador*/

boolean gana(char c,char m[][3]){
    if(m[0][0]==c && m[1][0]==c && m[2][0]==c)
        return TRUE;
   if(m[0][1]==c && m[1][1]==c && m[2][1]==c)
       return TRUE;
   if(m[0][2]==c && m[1][2]==c && m[2][2]==c)
       return TRUE;
   if(m[0][0]==c && m[0][1]==c && m[0][2]==c)
       return TRUE;
   if(m[1][0]==c && m[1][1]==c && m[1][2]==c)
       return TRUE;
   if(m[2][0]==c && m[2][1]==c && m[2][2]==c)
       return TRUE;
   if(m[2][0]==c && m[1][1]==c && m[0][2]==c)
       return TRUE;
   if(m[0][0]==c && m[1][1]==c && m[2][2]==c)
       return TRUE;
    return FALSE;
}

/*
 este metodo se encarga de relizar el tiro y ver cual es la mejor opcion 
 para colocar la ficha de la makina*/
void tiro_max(char c,char m[][3]){
    int min,i,j,k,l;
    min=-10;
    k=l=0;
    char max[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    for(i=0;i<3;++i)
        for(j=0;j<3;++j)
            max[i][j]=m[i][j];
    
     for(i=0;i<3;++i)
        for(j=0;j<3;++j)
            if(max[i][j]==' ')
                 if(c=='x'){
                     max[i][j]=c;
                     if(juega_min(c,max)>min){
                         min=juega_min(c,max);
                         k=i;
                         l=j;
                     }
                     max[i][j]=' ';
                }
                else{
                     max[i][j]='o';
                     if(juega_min(c,max)>min){
                         min=juega_min(c,max);
                         k=i;
                         l=j;
                     }
                     max[i][j]=' ';
                }
    m[k][l]=c;
                
        
}
/*este metodo simula el siguiente tiro del jugador */

int juega_min(char c,char m[][3]){
    int min,i,j;
    min=10;
    char maux[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    for(i=0;i<3;++i)
        for(j=0;j<3;++j)
            maux[i][j]=m[i][j];
    
    for(i=0;i<3;++i)
        for(j=0;j<3;++j)
            if(maux[i][j]==' ')
                if(c=='x'){
                   maux[i][j]='o';
                   if(minimo(c,maux)<min)
                       min=minimo(c,maux);
                   if(gana('o',maux))
                   maux[i][j]=' ';
                }
                else{
                     maux[i][j]='x';
                   if(minimo(c,maux)<min)
                       min=minimo(c,maux);
                   maux[i][j]=' ';
                }
    return min;
    
                    
}

/*este metodo calcula el valor minimo de posibilidades que le queden al 
 usuario en el tablero dependiendo de este valor se decide donde 
 es la mejor decicion colocar la ficha*/

int minimo(char c,char m[][3]){
    if(c=='x')
        return posibilidades(c,m)-posibilidades('o',m);
    else
        return posibilidades(c,m)-posibilidades('x',m);
}
/*esta funcion lo que hace es ver las posibilidades que tiene un jugador
 las posibilidades se calculan viendo cuantas diagonales, horizxontales o verticales 
 aun tiene posibilidades de usar*/
int posibilidades(char c,char m[][3]){
   char maux[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
   int i,j,p;
   for(i=0;i<3;++i)
       for(j=0;j<3;++j)
           if(m[i][j]!=c)
               maux[i][j]=m[i][j];
   p=0;
   if(maux[0][0]==' ' && maux[1][0]==' ' && maux[2][0]==' ')
       ++p;
   if(maux[0][1]==' ' && maux[1][1]==' ' && maux[2][1]==' ')
       ++p;
   if(maux[0][2]==' ' && maux[1][2]==' ' && maux[2][2]==' ')
       ++p;
   if(maux[0][0]==' ' && maux[0][1]==' ' && maux[0][2]==' ')
       ++p;
   if(maux[1][0]==' ' && maux[1][1]==' ' && maux[1][2]==' ')
       ++p;
   if(maux[2][0]==' ' && maux[2][1]==' ' && maux[2][2]==' ')
       ++p;
   if(maux[2][0]==' ' && maux[1][1]==' ' && maux[0][2]==' ')
       ++p;
   if(maux[0][0]==' ' && maux[1][1]==' ' && maux[2][2]==' ')
       ++p;
   return p;
    
}
/*
 *la funcion(pierde) lo que trata es de identificar si con el siguiente tiro 
 * del jugador en alguna de las casillas hace que la maquina pierda de este modo 
 * la maquina se percata de que puede perder en el proximo tiro del jugador 
 * y lo bloquea en esa posicion
 * recibe como parametro el tipo de ficha del jugadro y el tablero
 * de ser verdadero el el bloqueo e impedir que pierda la maquina 
 * este metodo retorn TRUE, de lo contrario de no correr aun riesgo de perder 
 * retorna FALSE
 */
boolean pierde(char c,char m[][3]){
   int i,j;
   for(i=0;i<3;++i)
       for(j=0;j<3;++j)
           if(m[i][j]==' '){
               m[i][j]=c;
               if(gana(c,m)){
                   if(c=='x')
                       m[i][j]='o';
                   else
                       m[i][j]='x';
                   return TRUE;
               }
               m[i][j]=' ';
           }
   return FALSE;
}
/*
 
 * este metodo lo que hace es imprimir el tablero
 */
void imprime(char m[][3]){
    int i,j;
    for(i=0;i<3;++i){
        printf("\n-------\n|");
        for(j=0;j<3;++j){
            printf("%c|",m[i][j]);
        }
    }
    printf("\n-------\n");
}

