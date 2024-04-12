/*============================================================================*/
/* ICSF13 - 2023-2 - TRABALHO 2                                               */
/*----------------------------------------------------------------------------*/
/* Bogdan T. Nassu                                                            */
/* Leyza E. B. Dorini                                                         */
/* Daniel F. Pigatto                                                          */
/*============================================================================*/
/** Fun��es pedidas para o 2o trabalho da disciplina Fundamentos de Programa��o
 * 1, 2o semestre de 2023, profs. Bogdan T. Nassu, Leyza E. B. Dorini e Daniel
 * F. Pigatto, Universidade Tecnol�gica Federal do Paran�. */
/*============================================================================*/

#ifndef __TRABALHO2_H
#define __TRABALHO2_H

/*============================================================================*/

void mudaGanho (double* dados, int n_amostras, double ganho);
int contaSaturacoes (double* dados, int n_amostras);
int hardClipping (double* dados, int n_amostras, double limite);
void limitaSinal (double* dados, int n_amostras, int n_passos);
void geraOndaQuadrada (double* dados, int n_amostras, int taxa, double freq);

/*============================================================================*/
#endif /* __TRABALHO2_H */
