/*bibliotecas*/
#include <stdlib.h>
#include <stdio.h>
#include "lab10.h"


typedef struct {
    int instrumento;
    int nota;
    int intensidade;
    int instanteInicial;
    int duracao;
} TpSom;


/*codigo do programa*/
int main()
{
  /*vetor de eventos*/
  TpSom *vetorEventos,*vetorAuxiliar,aux;
  /*vetor de saidaVec*/
  TpEvento *saidaVec;
  /*vetor de entrada*/
  int entrada[5];
  /*variaveis auxiliares*/
  int i,j,flag,sizeEventos,instante,valido;
  valido =0;
  /* inicialmente nao sabemos quantal sera o tamanho da musica e quantos eventos
  alocamos inicialmente um ponteiro que sera realocado ao longo do
  programa*/
  sizeEventos = 0;
  flag=0;
  /*realiza as proximas leituras ate o fim do programa*/
  while (flag!=5)
  {
    flag=0;
    for(i=0; i<5; i++)
    {
      scanf("%d", &entrada[i]);
    }

    for(i=0 ;i<5;i++)
    {
      if(entrada[i]==0)
        flag++;
      /*se houver algum numero negativo nao executa o programa*/
      if(entrada[i]<0 ||(i<3 && entrada[i]>128))
        valido++;
    }
    /*se flag != 5 temos que a entrada nao foi "vazia" */
    i=0;
    if(flag!=5)
    {
      /*realoca o vetor com tamanho+1*/
      vetorEventos = (TpSom *) realloc(vetorEventos,sizeof(TpSom)
                                                        * (sizeEventos + 1));
      vetorEventos[sizeEventos].instrumento = entrada[i++];
      vetorEventos[sizeEventos].nota = entrada[i++];
      vetorEventos[sizeEventos].intensidade = entrada[i++];
      vetorEventos[sizeEventos].instanteInicial = entrada[i++];
      vetorEventos[sizeEventos].duracao = entrada[i++];
      sizeEventos++;
    }
  }
  /*ao terminar a leitura temos o tamanho do vetorEventos sendo assim conseguimos facilmente ordenar por instanteInicial*/
  saidaVec = malloc(sizeof(TpEvento)*sizeEventos*2);
  vetorAuxiliar = malloc(sizeof(TpSom)*sizeEventos*2);
  i=0;
  instante=0;
  while(i<sizeEventos*2 && valido ==0)
  {
    for(j=0;j<sizeEventos;j++)
    {
      /*procura o final da nota  igual ao da interacao atual*/
      if ((vetorEventos[j].instanteInicial==instante||vetorEventos[j].duracao+
        vetorEventos[j].instanteInicial==instante)&& vetorEventos[j].duracao!=0)
      {
        if(vetorEventos[j].intensidade != 0)
        {
          vetorAuxiliar[i].instrumento = vetorEventos[j].instrumento;
          vetorAuxiliar[i].nota = vetorEventos[j].nota;
          vetorAuxiliar[i].intensidade = vetorEventos[j].intensidade;
          vetorAuxiliar[i].instanteInicial = vetorEventos[j].instanteInicial;
          /*marca a intensidade como 0*/
          vetorEventos[j].intensidade=0;
        }
        else
        {
          vetorAuxiliar[i].instrumento = vetorEventos[j].instrumento;
          vetorAuxiliar[i].nota = vetorEventos[j].nota;
          vetorAuxiliar[i].intensidade = vetorEventos[j].intensidade;
          vetorAuxiliar[i].instanteInicial= vetorEventos[j].duracao+
                                              vetorEventos[j].instanteInicial;
          /*marca a duracao como 0*/
          vetorEventos[j].duracao=0;
          vetorAuxiliar[i].duracao=0;
        }
        /*soma 1 no indice do vetor de vetorAuxiliar*/
        i++;
        j=0;
      }
    }
    /*procura o proximo instante*/
    instante++;
  }


  /*realiza a ordenacao dos eventos simultaneos
  Entre eventos simultâneos na música, eventos com número de instrumento menor,
   devem estar em posições anteriores no vetor.
  Entre eventos simultâneos no mesmo instrumento, eventos com número de
  nota menor devem estar em posições anteriores no vetor.*/
  if(valido==0)
  {
    for(i=0;i<sizeEventos*2;i++)
    {
      for(j=i+1;j<sizeEventos*2;j++)
      {
        if(vetorAuxiliar[i].instanteInicial > vetorAuxiliar[j].instanteInicial)
        {
          aux.instrumento = vetorAuxiliar[i].instrumento;
          aux.nota = vetorAuxiliar[i].nota;
          aux.intensidade = vetorAuxiliar[i].intensidade;
          aux.instanteInicial = vetorAuxiliar[i].instanteInicial;
          aux.duracao = vetorAuxiliar[i].duracao;
          vetorAuxiliar[i].instrumento = vetorAuxiliar[j].instrumento;
          vetorAuxiliar[i].nota = vetorAuxiliar[j].nota;
          vetorAuxiliar[i].intensidade = vetorAuxiliar[j].intensidade;
          vetorAuxiliar[i].instanteInicial = vetorAuxiliar[j].instanteInicial;
          vetorAuxiliar[i].duracao = vetorAuxiliar[j].duracao;
          vetorAuxiliar[j].instrumento = aux.instrumento;
          vetorAuxiliar[j].nota = aux.nota;
          vetorAuxiliar[j].intensidade = aux.intensidade;
          vetorAuxiliar[j].instanteInicial = aux.instanteInicial;
          vetorAuxiliar[j].duracao = aux.duracao;
          i=0;
          j=0;
        }
      }
    }
    for(i=0;i<sizeEventos*2;i++)
    {
      for(j=i+1;j<sizeEventos*2;j++)
      {

        /*um instanteInicial que possui 2 eventos*/
        if(vetorAuxiliar[i].instanteInicial == vetorAuxiliar[j].instanteInicial)
        {
          /*se neste instanteInicial a posicao menor possuir um
          instrumento maior, troca*/
          if(vetorAuxiliar[i].instrumento > vetorAuxiliar[j].instrumento)
          {
            aux.instrumento = vetorAuxiliar[i].instrumento;
            aux.nota = vetorAuxiliar[i].nota;
            aux.intensidade = vetorAuxiliar[i].intensidade;
            aux.duracao = vetorAuxiliar[i].duracao;
            vetorAuxiliar[i].instrumento = vetorAuxiliar[j].instrumento;
            vetorAuxiliar[i].nota = vetorAuxiliar[j].nota;
            vetorAuxiliar[i].intensidade = vetorAuxiliar[j].intensidade;
            vetorAuxiliar[i].duracao = vetorAuxiliar[j].duracao;
            vetorAuxiliar[j].instrumento = aux.instrumento;
            vetorAuxiliar[j].nota = aux.nota;
            vetorAuxiliar[j].intensidade = aux.intensidade;
            vetorAuxiliar[j].duracao = aux.duracao;

          }
          /*se neste instanteInicial a posicao menor possuir um mesmo
          instrumento com nota maior, troca*/
          else if(vetorAuxiliar[i].instrumento == vetorAuxiliar[j].instrumento
            && vetorAuxiliar[i].nota > vetorAuxiliar[j].nota)
            {
              aux.instrumento = vetorAuxiliar[i].instrumento;
              aux.nota = vetorAuxiliar[i].nota;
              aux.intensidade = vetorAuxiliar[i].intensidade;
              aux.duracao = vetorAuxiliar[i].duracao;
              vetorAuxiliar[i].instrumento = vetorAuxiliar[j].instrumento;
              vetorAuxiliar[i].nota = vetorAuxiliar[j].nota;
              vetorAuxiliar[i].intensidade = vetorAuxiliar[j].intensidade;
              vetorAuxiliar[i].duracao = vetorAuxiliar[j].duracao;
              vetorAuxiliar[j].instrumento = aux.instrumento;
              vetorAuxiliar[j].nota = aux.nota;
              vetorAuxiliar[j].intensidade = aux.intensidade;
              vetorAuxiliar[j].duracao = aux.duracao;

            }
            else if(vetorAuxiliar[i].instrumento == vetorAuxiliar[j].instrumento
              && vetorAuxiliar[i].nota == vetorAuxiliar[j].nota
              && vetorAuxiliar[i].intensidade > vetorAuxiliar[j].intensidade)
              {
                aux.instrumento = vetorAuxiliar[i].instrumento;
                aux.nota = vetorAuxiliar[i].nota;
                aux.intensidade = vetorAuxiliar[i].intensidade;
                aux.duracao = vetorAuxiliar[i].duracao;
                vetorAuxiliar[i].instrumento = vetorAuxiliar[j].instrumento;
                vetorAuxiliar[i].nota = vetorAuxiliar[j].nota;
                vetorAuxiliar[i].intensidade = vetorAuxiliar[j].intensidade;
                vetorAuxiliar[i].duracao = vetorAuxiliar[j].duracao;
                vetorAuxiliar[j].instrumento = aux.instrumento;
                vetorAuxiliar[j].nota = aux.nota;
                vetorAuxiliar[j].intensidade = aux.intensidade;
                vetorAuxiliar[j].duracao = aux.duracao;
              }
              else if(vetorAuxiliar[i].instrumento == vetorAuxiliar[j].instrumento
                && vetorAuxiliar[i].nota == vetorAuxiliar[j].nota
                && vetorAuxiliar[i].duracao > vetorAuxiliar[j].duracao)
                {
                  aux.instrumento = vetorAuxiliar[i].instrumento;
                  aux.nota = vetorAuxiliar[i].nota;
                  aux.intensidade = vetorAuxiliar[i].intensidade;
                  aux.duracao = vetorAuxiliar[i].duracao;
                  vetorAuxiliar[i].instrumento = vetorAuxiliar[j].instrumento;
                  vetorAuxiliar[i].nota = vetorAuxiliar[j].nota;
                  vetorAuxiliar[i].intensidade = vetorAuxiliar[j].intensidade;
                  vetorAuxiliar[i].duracao = vetorAuxiliar[j].duracao;
                  vetorAuxiliar[j].instrumento = aux.instrumento;
                  vetorAuxiliar[j].nota = aux.nota;
                  vetorAuxiliar[j].intensidade = aux.intensidade;
                  vetorAuxiliar[j].duracao = aux.duracao;
                }
              }
            }
          }
          /*copia para o vetor de saida*/
          for(i=0;i<sizeEventos*2;i++)
          {
            saidaVec[i].instrumento=vetorAuxiliar[i].instrumento;
            saidaVec[i].nota=vetorAuxiliar[i].nota;
            saidaVec[i].intensidade=vetorAuxiliar[i].intensidade;
            saidaVec[i].instante=vetorAuxiliar[i].instanteInicial;
          }

  }
  if(valido==0)
  {
    /*chamamos a funcao de saidaVec*/
    saida(0, sizeEventos*2, saidaVec);

  }
  else
    saida(0,0,saidaVec);
  /*libera a memoria */
  free(vetorEventos);
  free(vetorAuxiliar);
  free(saidaVec);
  /*termina o programa*/
  return 0;
}
