#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    to_do_list                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/15 18:16:12 by otlacerd          #+#    #+#              #
#    Updated: 2026/04/18 03:55:23 by olacerda         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

Project start time: 13/04/2026 (Gustavo "14")

Finish time: 12/05/2026 ~~ 15/05/2026


1-Precisa parsear os elementos de config? (O avaliador pode alterar?) confirmar

<!-- 0. Setup base ------------------------------------------------------------------

Ler argumento .cub
Validar extensão .cub
Abrir ficheiro (error se falhar)

1. Leitura do ficheiro ---------------------------------------------------------

Ler linha a linha (read / get_next_line)
Guardar tudo (array de strings) -->

2. Separação de secções --------------------------------------------------------

Ignorar linhas vazias iniciais
Identificar:
config (texturas + cores)
mapa (última parte do ficheiro)
Garantir: mapa é último bloco

3. Parsing dos identificadores (config)
Para cada linha não-vazia antes do mapa:

Identificar tipo:
NO, SO, WE, EA
F, C
Extrair conteúdo

4. Validação dos identificadores -----------------------------------------------

Cada identificador aparece exatamente 1 vez
Nenhum identificador inválido
Ordem livre (não assumir ordem)

5. Parsing das texturas --------------------------------------------------------
Para cada NO SO WE EA:

Extrair path
Remover espaços extras
Validar:
path não vazio
ficheiro existe (open)

6. Parsing das cores -----------------------------------------------------------
Para F e C:

Extrair string R,G,B
Split por ,
Validar:
exatamente 3 valores
cada valor ∈ [0,255]
apenas números

7. Detecção do início do mapa --------------------------------------------------

Primeira linha que:
contém apenas 01NSEW
A partir daí → tudo é mapa

8. Parsing do mapa (raw) -------------------------------------------------------

Guardar linhas como estão (incluindo espaços)
Não trimar espaços internos

9. Normalização do mapa --------------------------------------------------------

Encontrar largura máxima
Padding com espaços (' ') nas linhas menores

10. Validação de caracteres ----------------------------------------------------

Apenas:
0 1 N S E W ' '
Error se outro char

11. Player ------------------------------------------------------------------
-----
Encontrar N/S/E/W
Validar:
existe exatamente 1
Guardar:
posição (x,y)
dire

12. Mapa fechado ---------------------------------------------------------------

Para cada 0 ou player:
não pode tocar:
borda
espaço ' '
Estratégia: 
flood fill ou
check vizinhos (4 direções)

estrategia pra verificar "fechado por 1"
--> verificar por 'linha' depois por 'coluna'. Se o "começo" e o "fim" é '1'.

13. Consistência geral ---------------------------------------------------------

Todos os elementos obrigatórios existem:
4 texturas
2 cores
mapa válido
Nenhuma linha extra inválida antes do mapa

14. Gestão de erros ------------------------------------------------------------

Qualquer erro:
Error\n
mensagem clara
Sem leaks

15. Estruturas finais ----------------------------------------------------------

Struct config:
paths texturas
cores
Struct mapa:
grid normalizado
player pos + direção

16. Cleanup --------------------------------------------------------------------

Free de tudo
Fechar fd

17. Lembrar de Criar a "Regra bonus" no Makefile