/*============================================================================*/
/* Exemplo: Aumenta (bastante) o volume do sinal e conta satura��es. Faz hard
 * clipping com 2 n�veis diferentes. */

#include <stdlib.h>
#include "wavfile.h"

#include "trabalho2.h"

/*============================================================================*/

#define INPUT_FILE "data/sonic1.wav"
#define OUTPUT_FILE1 "data/teste2_3_clipping1a_meu.wav"
#define OUTPUT_FILE2 "data/teste2_3_clipping2a_meu.wav"

/*============================================================================*/

int main ()
{
	WavHeader header; /* Cabe�alho para as informa��es sobre o arquivo. */
	double* dados_l; /* Dados do canal esquerdo. Alocado na readWavFile. */
	double* dados_r; /* Dados do canal direito. Alocado na readWavFile, se necess�rio. */
	int n_amostras; /* N�mero de amostras nos buffers. */
	int n_saturacoes; /* N�mero de amostras com satura��o. */

    /* L� um arquivo. */
    n_amostras = readWavFile (INPUT_FILE, &header, &dados_l, &dados_r);
    if (!n_amostras)
    {
        printf ("Erro lendo %s.\n", INPUT_FILE);
        return (1);
    }

	/* Confirma que o arquivo � stereo. */
    if (!dados_r)
    {
        printf ("%s nao eh um arquivo stereo.\n", INPUT_FILE);
        return (1);
    }

    /* Conta as satura��es. */
    printf ("Antes de aumentar o volume:\n");
    n_saturacoes = contaSaturacoes (dados_l, n_amostras);
    printf ("Saturacoes esquerda: %d\n", n_saturacoes);
    n_saturacoes = contaSaturacoes (dados_r, n_amostras);
    printf ("Saturacoes direita: %d\n\n", n_saturacoes);

    /* Aumenta o volume. */
    mudaGanho (dados_l, n_amostras, 4);
    mudaGanho (dados_r, n_amostras, 4);

    /* Conta as satura��es de novo. */
    printf ("Depois de aumentar o volume:\n");
    n_saturacoes = contaSaturacoes (dados_l, n_amostras);
    printf ("Saturacoes esquerda: %d\n", n_saturacoes);
    n_saturacoes = contaSaturacoes (dados_r, n_amostras);
    printf ("Saturacoes direita: %d\n\n", n_saturacoes);

    /* Clipa em [-1,1]. */
    printf ("Limitando em [-1,1] (hard clipping):\n");
    n_saturacoes = hardClipping (dados_l, n_amostras, 1.0);
    printf ("Esquerda: %d amostras alteradas.\n", n_saturacoes);
    n_saturacoes = hardClipping (dados_r, n_amostras, 1.0);
    printf ("Direita: %d amostras alteradas.\n\n", n_saturacoes);

    /* Salva. */
    if (!writeWavFile (OUTPUT_FILE1, &header, dados_l, dados_r))
    {
        printf ("Erro salvando %s.\n", OUTPUT_FILE1);
        return (1);
    }

     /* Clipa em [-0.2,0.2]. */
    printf ("Limitando em [-0.2,0.2] (hard clipping):\n");
    n_saturacoes = hardClipping (dados_l, n_amostras, 0.2);
    printf ("Esquerda: %d amostras alteradas.\n", n_saturacoes);
    n_saturacoes = hardClipping (dados_r, n_amostras, 0.2);
    printf ("Direita: %d amostras alteradas.\n\n", n_saturacoes);

    /* Salva. */
    if (!writeWavFile (OUTPUT_FILE2, &header, dados_l, dados_r))
    {
        printf ("Erro salvando %s.\n", OUTPUT_FILE2);
        return (1);
    }

    /* Desaloca os vetores. O direito s� vai ter sido alocado se o arquivo for est�reo. */
	free (dados_l);
	if (dados_r)
        free (dados_r);

	return (0);
}

/*============================================================================*/
