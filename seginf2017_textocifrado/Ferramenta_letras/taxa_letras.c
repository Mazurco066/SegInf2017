#include <stdio.h>
#include <stdlib.h>
#define esc 27

int sair = 0;
int pos = 1;
float taxaerro;
char opcoes [2][24] = {"Pesquisar Caracter", "Sair"};
char cifrado[] = "lrvmnir bpr sumvbwvr jx bpr lmiwv yjeryrkbi jx qmbm wi bpr xjvni mkd ymibrut jx irhx wi bpr riirkvr jx ymbinlmtmipw utn qmumbr dj w ipmhh but bj rhnvwdmbr bpr yjeryrkbi jx bpr qmbm mvvjudwko bj yt wkbrusurbmbwjk lmird jk xjubt trmui jx ibndt wb wi kjb mk rmit bmiq bj rashmwk rmvp yjeryrkb mkd wbi iwokwxwvmkvr mkd ijyr ynib urymwk nkrashmwkrd bj ower m vjyshrbr rashmkmbwjk jkr cjnhd pmer bj lr fnmhwxwrd mkd wkiswurd bj invp mk rabrkb bpmb pr vjnhd urmvp bpr ibmbr jx rkhwopbrkrd ywkd vmsmlhr jx urvjokwgwko ijnkdhrii ijnkd mkd ipmsrhrii ipmsr w dj kjb drry ytirhx bpr xwkmh mnbpjuwbt lnb yt rasruwrkvr cwbp qmbm pmi hrxb kj djnlb bpmb bpr xjhhjcwko wi bpr sujsru msshwvmbwjk mkd wkbrusurbmbwjk w jxxru yt bprjuwri wk bpr pjsr bpmb bpr riirkvr jx jqwkmcmk qmumbr cwhh urymwk wkbmvb";
char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";
float taxas[] = {0.0817, 0.0150, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, 0.0609, 0.697, 0.0015, 0.0077, 0.0403, 0.241, 0.0675, 0.0751, 0.0193, 0.0010, 0.0599, 0.0633, 0.0906, 0.0276, 0.0098, 0.0236, 0.0015, 0.0197, 0.0007};


int strcountc(char *s, char ch){

    char *ptr;
    int count = 0;
    int i;

    ptr = s;

    while(*ptr != '\0'){

        if (*ptr==ch){

           count++;
        }
        ptr++;
    }

    return count;
}

float percent(int tamanho, int tem){

    return ((float)tem / tamanho);
}

int main(){

    //printf("Entre com uma taxa de variacao para as frequencias -> \n");
    //scanf("%f", &taxaerro);

    inicios();

    do{
        menu_principal();
    }while (sair != 1);

    return 0;
}

void enter(int posicao){    //menu ao pressionar a tecla enter / decisão

    if (posicao == 1){

        char procura;
        fflush(stdin);
        printf("\n Digite um caracter para pesquisar no texto -> ");
        scanf("%c", &procura);

        printf("\n O caracter %c aparece %d vezes no texto\n", procura, strcountc(cifrado, procura));
        printf(" O Percentual da letra %c no texto eh de: %.4f\n\n ", procura, percent(strlen(cifrado), strcountc(cifrado, procura)));

        system("pause");
        printf("\n\n ");
    }
    else if(posicao == 2){

            sair = 1;
    }


}

void inicios(){ //possibilidades do menu

    int i;

    system("cls");

    for (i = 1; i <=4; i++){

            if (pos == i){
                printf("-> %s \n", &opcoes[i - 1]);
            }
            else{
                printf("   %s \n", &opcoes[i - 1]);
            }

    }
}

void menu_principal(){  //captura de teclas

    int ch;
    ch=getch();
    if (ch== esc){  //esc
        sair = 1;
    }
    else if (ch==13){   // enter
        enter(pos);
    }
    if (ch==72){    //acima
        pos--;
        if (pos < 1){
            pos = 2;
        }
    }
    else if (ch==80){   //abaixo
        pos++;
        if(pos > 2){
            pos = 1;
        }
    }

    //impressão
    inicios();
}
