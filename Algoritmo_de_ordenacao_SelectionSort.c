#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


typedef struct ListaAlunos {
   
    int matricula;
    char nome[100];
    int ano_ingresso;
    int periodo_ingresso;
    char campus[100];
    char curso[100];
    char modalidade[100];
    char forma_ingresso[100];

}ListaAlunos;

ListaAlunos dados[1024];

int qtd;

void imprimir(int ContLinhas);

int selectionSort(ListaAlunos vec[], int TAM);

void troca(ListaAlunos *a, ListaAlunos *b);
void arquivos_processado(int ContCampos, char *value, int i);



int main(void) {
    char buf[1024];
    char chave[1024];

    setlocale (LC_ALL, "Portuguese");
    int ContLinhas = 0;
    int ContCampos = 0;
    int in_aspas_duplas = 0;
    int chave_pos = 0;
    int i = 0;
	
	
	printf("_______________________________________________________________________  \n \n");
    printf("               {Estutura de Dados II } \n \n");
    printf("                ****Alexandre Oliveira****  \n \n");
    printf("                             \n \n");
    printf("______________________________________________________________________  \n \n");
    printf("     Relação dos alunos ingressantes identificando sua matricula,:  \n \n");
    printf("  nome, curso, campus ou polo, modalidade de ensino, forma de ingresso,  \n \n");    
    printf("   ano e periodo de ingresso e cota de ingresso (a partir de 2016)   \n");
   
    FILE *fp = fopen("alunos-ingressantes-na-graduacao-pda-2017-2018.csv", "r");

    if (!fp) {
        printf("Nao Foi Possivel Abrir o Arquivo\n");
        return 0;
    }

    while (fgets(buf, 1024, fp)) {
        ContLinhas++;

        if (ContLinhas == 1) {
            continue;
        }

        ContCampos = 0;
        i = 0;
        do {
            chave[chave_pos++] = buf[i];

            if (!in_aspas_duplas && (buf[i] == ';' || buf[i] == '\n')) {
                chave[chave_pos - 1] = 0;
                chave_pos = 0;
                arquivos_processado(ContCampos++, chave, ContLinhas-2);
            }

            if (buf[i] == '"' && buf[i + 1] != '"') {
                chave_pos--;
                in_aspas_duplas = !in_aspas_duplas;
            }

            if (buf[i] == '"' && buf[i + 1] == '"')
                i++;

        } while (buf[++i]);

        printf("\n");
    }
	
	printf("************************************************************\n\n");
    printf("***** Vetor Desordenado: *****\n\n");
    printf("************************************************************\n\n");
	imprimir(ContLinhas);
    printf("\n\n");

	
	selectionSort(dados,ContLinhas-1);

	printf("************************************************************\n\n");
	printf("***** Vetor Ordenado No Metodo SelectionSort: *****\n\n");
	printf("*****   Ordenação pelo número da matricula:  *****\n\n");
    printf("*************************************************************\n\n");
  
	imprimir(ContLinhas);
    printf("\n\n");

    fclose(fp);

    //free(fp);


    return 0;
}

void arquivos_processado(int ContCampos, char *value, int i) {

   if (ContCampos == 0) {
        dados[i].matricula = atoi(value);
    }
    if (ContCampos == 1) {
         strcpy(dados[i].nome,value);
    }
    if (ContCampos == 2) {
     	dados[i].ano_ingresso = atoi(value);
	}
	if (ContCampos == 3) { 	
    	dados[i].periodo_ingresso = atoi(value);
	}
    if (ContCampos == 4) {
     	strcpy(dados[i].campus,value);
	}
	if (ContCampos == 5) { 
		strcpy(dados[i].curso,value);
	}
	if (ContCampos == 6) {
		strcpy(dados[i].modalidade,value);
	}
	if (ContCampos == 7) {
		strcpy(dados[i].forma_ingresso,value);
	}
}

void imprimir(int ContLinhas){
    int i;
    for(i = 0; i <= ContLinhas-2; i++){
        printf("Numero da matricula:\t %d\n",dados[i].matricula);//int
        printf("Nome do Aluno:\t\t %s\n",dados[i].nome);//char
        printf("Ano de ingresso:\t %d\n",dados[i].ano_ingresso);//int
        printf("Periodo\t\t\t %d\n",dados[i].periodo_ingresso);//int
        printf("Campus:\t\t\t %s\n",dados[i].campus);//char
        printf("Curso:\t\t\t %s\n",dados[i].curso);//char
        printf("Modalidade:\t\t %s\n",dados[i].modalidade);//char
        printf("Forma de ingresso:\t %s\n",dados[i].forma_ingresso);//char
         
        
		
		
		printf("\n");
    }
}



void troca(ListaAlunos *a, ListaAlunos *b) {
	ListaAlunos tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}


int selectionSort(ListaAlunos vec[], int TAM){
	int i, j, min, qtd=0;
	for (i = 0; i < (TAM-1); i++)
	{
		min = i;
		for (j = (i+1); j < TAM; j++) {
			if(vec[j].matricula < vec[min].matricula) {
				min = j;
			}
			qtd++;
		}
		if (i != min) {
			troca(&vec[i], &vec[min]);
		}
	}
	return(qtd);
}






