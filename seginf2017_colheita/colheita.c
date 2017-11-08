#include <stdio.h>            //biblioteca padrão
#include <stdlib.h>           //biblioteca padrão
#include <string.h>          //biblioteca de manipulação de strings
#include <stdbool.h>       //biblioteca que inclui o tipo bool em c (true/false)
#include <dirent.h>         //biblioteca de manipulação de pastas e arquivos
#include <sys/types.h>    //biblioteca de sistema de verificação de tipos de arquivos
#include <sys/stat.h>      //biblioteca de sistema que verifica status de um arquivo ou pasta

/*
[uso] ./colheita {formatos} {pasta busca} {arquivo de saída}
[exemplo] ./colheita .txt:.asc:.pdf teste saida.txt
[PLATAFORMA] SOMENTE LINUX
[escrito por] mazurco066 (Gabriel Ribeiro)
[email] mazurco066@gmail.com
.......
.......
[objetivo] busca de palavras chaves no sistema para geração de uma wordlist
*/

//Variáveis Globais
char resultado[10][5];		//Armazena quais foram as extensões entradas pelo usuário - limite = 10 extensões
int cont = 0;			            //Variável que armazena numerode extensões entrada pelo usuário
FILE *output;			            //Arquivo de saída do programa
char cam[200];                  //Variável que armazena junção da string do caminho do arquivo
char *formatos;                //Variável que armazena argumento das extensões
char *pasta;                     //Variável que armazena argumento do caminho raiz
char *saida;                      //Variável que armazena nome do arquivo de saída
//Variáveis Globais

int main(int argc, char *argv[]){

/*
argv[0] = programa -> exemplo colheita
argv[1] = formatos -> exemplo .txt:.text:.asc
argv[2] = pasta -> exemplo /tmp/
argv[3] = arquivo saída -> exemplo saída.txt
*/

if (argc != 4){	//ERRO: Falta ou Excesso de argumentos passados pelo usuário

	printf("[+]Erro: Parametros Insuficientes\n");
	return -1;	//Sai do programa
}

//Recebendo parametros
formatos = argv[1];	//Recupera o primeiro argumento das extensões
pasta = argv[2];		//Recupera o segundo argumento que é o caminho da pasta
saida = argv[3];		//Recupera o terceiro argumento que é o arquivo de saída do programa

//Variáveis locais
output = fopen(saida, "at");      //Abrindo arquivo de saída para armazenar a Wordlist
int i;                                        //Contador para o for para verificar extensões de arquivos encontrados

//Funções de Verificação
bool extensao(char const *nome, char ext[]);    //Verifica se a extensão do arquivo encontrado é igual a especificada retornando (true/false)
void alimenta(char *ptr);                                     //Formata a string de extensões do usuário em um formato aceitável pelo programa
void vasculhaPasta(char caminho[], int cont);      //Função recursiva que vascula pastas e subpastas encontradas
//Funções de Verificação

alimenta(argv[1]);             //Formatando os argumentos do usuário

vasculhaPasta(pasta, cont);         //Função recursiva de busca dentro da patas e suas respectivas subpastas

fclose(output);                 //Fechando o arquivo de saída do programa

printf("\n[+]Wordlist salva no arquivo \"%s\"\n", saida);   //Mensagem de Sucesso do programa

return 0;

//EOF
}

void vasculhaPasta(char caminho[], int cont){

DIR *localdir;
struct dirent *dp;
localdir = opendir(caminho);
int i;
bool extensao(char const *nome, char ext[]);

while ((dp = readdir(localdir)) != NULL){

	for (i = 0; i <= cont; i++){

		if (extensao(dp->d_name, resultado[i]) == true){

			printf("[+]ENCONTRADO ARQUIVO %s\n", dp->d_name);
			size_t len = strlen(dp->d_name);
			fprintf(output, "%s\n", strtok(dp->d_name, "."));
		}
	}
	if (dp->d_type != DT_REG && dp->d_name[0] != '.'){

		printf("[+]Entrando na Pasta \"%s\"\n", dp->d_name);
		strcpy(cam, caminho);
		strcat(cam, "/");
		strcat(cam, dp->d_name);
		vasculhaPasta(cam, cont);
	}
}

closedir(localdir);
}

bool extensao(char const *nome, char ext[]){

	size_t len = strlen(nome);
	return len > 4 && strcmp(nome + len - 4, ext) == 0;
}

void alimenta(char *ptr){

    int i = 0, j = 0;

    while (*ptr != '\0'){

        if (*ptr == ':'){
            resultado[i][j]='\0';
            i++;
            j = 0;
            cont++;
        }
        else{
            resultado[i][j] = *ptr;
            j++;
        }
        ptr++;
    }
    resultado[i][j] = '\0';
}
