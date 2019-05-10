#ifndef __AG_H__
#define __AG_H__

/**
 * Função que agrega um ficheiro de vendas
 * @param nome do ultimo ficheiro agregado
 */
void agregar(char* filename);

/**
 * Função que escreve os dados agregados para um novo ficheiro
 * @param nome do ultimo ficheiro agregado
 */
void wrToFile(char* oldfile);

#endif
