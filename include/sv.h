#ifndef __SV_H__
#define __SV_H__

/**
 * Função que procura um código no ficheiro stocks 
 * @param código de um artigo
 * @returns quantidade de um artigo em stock
 */
int stocksReadQ(int code);

/**
 * Função que atualiza o ficheiro stocks.
 * @param codigo de um produto
 * @param quantidade existente do artigo em stock
 * @returns quantidade do artigo em questão
 */
int stocksWrite(int code, int q);

/**
 * Função que calcula o montante de uma venda dado o code e a quantidade
 * @param codigo de um artigo 
 * @param quantidade existente do artigo em stock
 * @returns montante de uma venda
 */
float calculaMont(int code, int quant);

/**
 * Função que acrescenta uma venda ao ficheiro vendas.
 * @param uma venda (código, quantidade e montante)
 */
void vendasAppend(int code, int quant, float mont);

/**
 * Função que dado o código do artigo retorna o seu preço
 * @param código do artigo
 * @returns preço do artigo
 */
float getPrice(int code);

/**
 * Função que realiza uma venda/restock
 * @param codigo do artigo
 * @param quantidade existente do artigo em stock
 * @returns quantidade existente do artigo em stock atualizada
 */
int makeVenda(int code, int quant);

/**
 * Handler do Ctr-C para terminar o processo e fazer unlink do pipe pedidos
 * @param sinal
 */
void terminar(int signum);

#endif
