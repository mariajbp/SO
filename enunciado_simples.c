<enunciado>

<ARTIGOS>
	/*

		Este ficheiro segue uma ordem de construcao, em que cada linha contem:

		<index> <index_posicao para o ficheiro STRINGS> <preco>

		index			-> numero sequencia que permite obter a linha do artigo [000 000 a 999999]
		index_posicao		-> posicao referencia do inicio da string no ficheiro STRINGS [000 000 a 999999]
		preco			-> preco do artigo [000.00 a 999.99]

	*/

<STRINGS>
/*

	?

*/

<STOCKS>
	/*

		Este ficheiro segue uma ordem de construcao, em que cada linha contem:

		<index> <quantidade>

		index			-> numero sequencia que permite obter a linha do artigo [000 000 a 999999]
		quantidade		-> quantidade em stock do produto [000 000 a 999999]

	*/

<VENDAS>
/*

	Este ficheiro segue uma ordem de construcao, em que cada linha contem:

	<index> <quantidade> <montante>

	index			-> numero sequencia que permite obter a linha do artigo [000 000 a 999999]
	quantidade		-> quantidade comprada do produto [000 000 a 999999]
	montante		-> preco * quantidade comprada do produto [000 000 000.00 a 999999999.99]

*/

<Manutencao_Artigos>
	/*

	Este programa devera permitir:
		T1: inserir novos artigos (especificando o nome e preço de venda)
		T2: alterar atributos de um dado artigo (nome ou preço)

	Cada artigo tem um código numerico, atribuido na criação como o proximo de uma sequencia (index)
	Acesso a um aritigo no ficheiro ARTIGOS:
		T3: usar o codigo como indice, as entradas devem ter tamanho fixo
	O atributo nome no ficheiro de artigos deve conter uma referencia para onde se encontra no ficheiro STRINGS

	O programa recebe todo o seu input pelo stdin:
		i <nome> <preco>      --> insere novo artigo, mostra o index
		n <code> <new name>   --> altera o nome do artigo
		p <code> <new price>  --> altera o preco do artigo

		... <-- o que sao estes ... ?

	*/

<Servidor_Vendas>

	/*

	Este programa devera permitir:
		T1: controlar o stock
		T2: receber pedidos de vendas
		T3: registar as vendas efetuadas

	A quantidade em stock de cada artigo devera ser mantida num ficheiro STOCKS
	Cada venda devera ser registada, por apendice num ficheiro VENDAS, contendo:
		<code> <quantidade> <montante_venda>        <-- code é o indice do artigo ou o indice da venda?
	O servidor de vendas deve correr o agregador a pedido, fazendo com que este receba:
		<intervalo_ a ser agregado, desda ultima agregacao>
		-> o resultado vai ser escrito num ficheiro cujo nome reflete o momento de solicitacao
			<2019.03.24.T.14:23:56>

	*/

<Cliente_Vendas>

	/*

	Este programa devera permitir:
		T: interagir com o servidor de vendas solicitando-lhe
			T1: o retorno da quantidade em stock e o preco de um artigo (atraves do indice)
		T: operacao que escolha uma acao baseada numa quantidade
			T2: se a quantidade for negativa efetua uma venda
			T3: se a quantidade for positiva efetua uma entrada em stock

	O sistema devera permitir a execucao concorrente de varios clientes de venda.

	O programa recebe todo o seu input pelo stdin:
		<code> 				--> mostra no stdout stock e preco
		<code> <quantidade> --> atualiza o stock e mostra o no stdout

	*/

<Agregador>

	/*

	Este programa devera permitir:
		T: funcionar como filtro
			T1: receber pelo stdin entradas no formato de ficheiro de VENDAS ate EOF
			T2: produzir para o stdout os dados agregados de cada artigo com vendas efetuadas

	Os dados agregados de um artigo devem conter:
		<code> <quantidade_total> <montante_total> <-- manter o formato do ficheiro VENDAS

	*/
