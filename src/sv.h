#ifndef __SV_H__
#define __SV_H__


/**
 * Função que acrescenta um codigo de artigo ao ficheiro stocks
 */
void stockAppend();

/**
 * Função que procura um código no ficheiro stocks 
 * @param código de um artigo
 * @param quantidade de um artigo em stock
 */
int stocksReadQ(int code);

/**
 * Função que atualiza o ficheiro stocks.
 * @param codigo e quantidade de um produto
 */
void stocksWrite(int code, int q);

/**
 * Função que acrescenta uma venda ao ficheiro vendas.
 * @param uma venda (código, quantidade e montante)
 */
void vendasAppend(int code, int quant, float mont)

/**
 * Função que dado o código do artigo retorna o seu preço
 * @param código do artigo
 * @param preço do artigo
 */
double getPrice(int code);

#endif
