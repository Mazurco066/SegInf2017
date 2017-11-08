#!/bin/bash
# [bruteforce.sh]
# [Uso]
# $ ./bruteforce.sh arquivozipcomsenha.zip wordlist.txt
# Senha: "senha"

# OBS - É NECESSÁRIO TER O UNZIP DISPONIVEL NO LINUX PARA QUE ESSE SHELLSCRIPT FUNCIONE

# Recebe um arquivo zip com senha
ARQUIVOZIP=

# Recebe o arquivo txt contendo as palavras chaves em um rquivo txt
WORDLIST=

# Recebe cada senha do dicionário
senhateste=

# Função de ajuda.
function show_help {
echo 'bruteforce.sh - SegInf2017'
echo '[uso] $ ./bruteforce.sh arquivozip.zip wordlist.txt'
exit 1
}

# Função que para o teste qnd se aperta as teclas "ctrl + c"
function pegarctrlc {
echo "[+] Processo abortado. Senha atual: $senhateste"
exit 1
}

# Emissor para o ctrl+c
trap pegarctrlc SIGINT

# Obtém os parâmetros.
ARQUIVOZIP="$1"	#parametro 1
WORDLIST="$2"	#parametro 2

# Flag. Tem valor 1 se a senha foi quebrada e
# 0 caso contrário.
SENHAQUEBRADA=0

# Testa os parâmetros.
[ -e "$ARQUIVOZIP" ] && [ -e "$WORDLIST" ] || show_help

# Processo de quebragem.
echo '[+] Espere. Quebrando a senha...'
while read senhateste
do
    SAIDA=$(unzip -tq -P "$senhateste" "$ARQUIVOZIP" 2>&1)
    [[ "$SAIDA" =~ 'No errors detected in compressed data of' ]] && SENHAQUEBRADA=1 && break
done < "$WORDLIST"

# Informa se a senha foi quebrada ou não.
if [ "$SENHAQUEBRADA" = '1' ]
then
    echo '[+] Senha quebrada: '$senhateste
else
    echo '[+] Senha NAO quebrada. Tente outra lista de palavras.'
fi

#Fim do Shellscript
