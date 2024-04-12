/*======================================================================================================================*/
/*ICSF13 - 2023-2 - TRABALHO 2                                                                                          */
/*======================================================================================================================*/
/*Alexandre Alberto Menon. RA: 2603403                                                                                  */
/*Giovanni Mioto. RA: 2603454                                                                                           */
/*======================================================================================================================*/
#include "trabalho2.h"
#include "wavfile.h"
/*======================================================================================================================*/
/*Chamada das fun��es*/
void mudaGanho (double* dados, int n_amostras, double ganho);
int contaSaturacoes (double* dados, int n_amostras);
int hardClipping (double* dados, int n_amostras, double limite);
void limitaSinal (double* dados, int n_amostras, int n_passos);
void geraOndaQuadrada (double* dados, int n_amostras, int taxa, double freq);
/*======================================================================================================================*/

void mudaGanho (double* dados, int n_amostras, double ganho)
{
    int i;
/*======================================================================================================================*/
/*Multiplica todos os valores do vetor pelo ganho desejado*/
    for(i=0;i<n_amostras; i++)
    {
        dados[i]*=ganho;
    }
/*======================================================================================================================*/
}

int contaSaturacoes (double* dados, int n_amostras)
{
    int i, cont_saturacoes=0;
/*======================================================================================================================*/
/*Passa por todos os valores do vetor e analisa se est� acima da satura��o desejada*/
    for(i=0; i<n_amostras; i++)
    {
        if(dados[i]>1 || dados[i]<-1)
        {
            cont_saturacoes++;
        }
    }
/*======================================================================================================================*/
    return cont_saturacoes;
}

int hardClipping (double* dados, int n_amostras, double limite)
{
    int i, cont_alteracoes=0;
/*======================================================================================================================*/
/*Passa por todos os valores do vetor*/
    for(i=0; i<n_amostras; i++)
    {
/*----------------------------------------------------------------------------------------------------------------------*/
/*Substitui caso os valores sejam maiores que o limite positivo*/
        if(dados[i]>limite)
        {
            dados[i]=limite;
            cont_alteracoes++;
        }
/*----------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------*/
/*Substitui caso os valores sejam menores que o limite negativo*/
        else if(dados[i]<(limite*(-1)))
        {
            dados[i]=limite*(-1);
            cont_alteracoes++;
        }
/*----------------------------------------------------------------------------------------------------------------------*/
    }
/*======================================================================================================================*/

    return cont_alteracoes;
}

void limitaSinal (double* dados, int n_amostras, int n_passos)
{
    int i, k;
    double aux, indice_aumento;
/*======================================================================================================================*/
/*Passa por todos os valores do vetor*/
    for(i=0; i<n_amostras; i++)
    {
/*----------------------------------------------------------------------------------------------------------------------*/
/*Caso os dados sejam maiores que o limite*/
        if(dados[i]>1)
        {
/*----------------------------------------------------------------------------------------------------------------------*/
/*Calcula o �ndice de aumento por passos*/
            aux=1/dados[i];
            indice_aumento=1-aux;
            indice_aumento/=n_passos+1;
            dados[i]*=1/dados[i];
/*----------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------*/
/*Calcula as pr�ximas casas do vetor*/
            for(k=1; k<=n_passos; k++)
            {
                aux+=indice_aumento;
                dados[i+k]*=aux;
                dados[i-k]*=aux;
            }
        }
/*----------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------*/
/*Caso os dados sejam menores que o limite negativo*/
        else if(dados[i]<-1)
        {
/*----------------------------------------------------------------------------------------------------------------------*/
/*Calcula o �ndice de aumento por passos*/
            aux=1/dados[i];
            indice_aumento=1+aux;
            aux*=-1;
            indice_aumento/=n_passos+1;
            dados[i]*=-(1/dados[i]);
/*----------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------*/
/*Calcula as pr�ximas casas do vetor*/
            for(k=1; k<=n_passos; k++)
            {
                aux+=indice_aumento;
                dados[i+k]*=aux;
                dados[i-k]*=aux;
            }
/*----------------------------------------------------------------------------------------------------------------------*/
        }
    }
/*======================================================================================================================*/
}

void geraOndaQuadrada (double* dados, int n_amostras, int taxa, double freq)
{
    double meio_ciclo, inverte_sinal=1.0,  meio_ciclo_atualizado,  erro;
    int i, j;
/*======================================================================================================================*/
/*C�lculo do meio ciclo*/
    meio_ciclo=(taxa/freq)/2.0;
/*======================================================================================================================*/
/*======================================================================================================================*/
/*Caso o meio ciclo seja um inteiro*/
    if(meio_ciclo==(int)meio_ciclo)
    {
/*----------------------------------------------------------------------------------------------------------------------*/
/*Passa por todas as casas do vetor substituindo por 1 e -1 de acordo com o valor do meio ciclo*/

        for(i=0; i<n_amostras; i+=(int)meio_ciclo)
        {
            for(j=i; j<(int)meio_ciclo+i; j++)
            {
                dados[j]=inverte_sinal;
            }
            inverte_sinal*=-1.0;
        }
/*----------------------------------------------------------------------------------------------------------------------*/
    }
/*======================================================================================================================*/
/*======================================================================================================================*/
/*Caso o meio ciclo seja um n�mero n�o inteiro*/
    else
    {
        meio_ciclo_atualizado=meio_ciclo;
/*----------------------------------------------------------------------------------------------------------------------*/
/*Passa por todas as casas do vetor substituindo por 1 e -1 de acordo com o valor do meio ciclo*/
        for(i=0; i<n_amostras; i+=(int)meio_ciclo_atualizado)
        {
            for(j=i; j<i+(int)meio_ciclo_atualizado; j++)
            {
                dados[j]=inverte_sinal;
            }
            inverte_sinal*=-1.0;
/*----------------------------------------------------------------------------------------------------------------------*/
/*Calcula a taxa de erro joga ela para o pr�ximo meio ciclo*/
            erro=meio_ciclo_atualizado-(int)meio_ciclo_atualizado;
            meio_ciclo_atualizado=meio_ciclo+erro;
/*----------------------------------------------------------------------------------------------------------------------*/
        }
    }
/*----------------------------------------------------------------------------------------------------------------------*/
/*======================================================================================================================*/
}
