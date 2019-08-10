/* Aluno: Marcos Augusto de Souza Pinto
   Matrícula = 21755102

Todos os codigos devem ser salvos na mesma página para o seu devido funcionamento*/

/*============================================================================*/


# include <stdio.h>
# include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#define ordem 1024

struct atendimento{
	char paciente [100];
	char terapeuta[100];
	char dia[20];
	char horario[30];
	char sala[20];
	char situacao[50];
    int numero;
};
typedef struct atendimento atendimento;

struct arvoreB{
    int folha; //esse nó é folha
    int numeroChaves; //quantos elementos tem esse nó
  
    atendimento chave[ordem];
    struct arvoreB *ponteiros[ordem+1]; //ponteiros
};
typedef struct arvoreB *arvoreB; //referencia

arvoreB criaArvore(void){
    arvoreB raiz;
    raiz = malloc(sizeof(*raiz));
    assert(raiz);
    raiz->folha = 1;
    raiz->numeroChaves = 0;
    return raiz;
}

void destroiArvore(arvoreB raiz){
    int contador;
    if(!raiz->folha){
        for(contador = 0; contador < raiz->numeroChaves + 1; contador++){
            destroiArvore(raiz->ponteiros[contador]);
        }
    }
    free(raiz);
}
 static int procuraChave(int n, const atendimento *a, atendimento chave){
     int lo;
     int hi;
     int mid;

     lo = -1;
     hi = n;
     
     while(lo +1 < hi){
         mid = (lo+hi)/2;
         if(a[mid].numero == chave.numero){
             return mid;
         }else if(a[mid].numero < chave.numero){
             lo = mid;
         }else{
             hi = mid;
         }
     }
     return hi;
 }

int procuraArvore(arvoreB raiz, atendimento chave){
    int pos;
    if(raiz->numeroChaves == 0){
        return 0;
    }
    pos = procuraChave(raiz->numeroChaves, raiz->chave,chave);

    if(pos < raiz->numeroChaves && raiz->chave[pos].numero == chave.numero){
        return 1;
    }else{
        return (!raiz->folha && procuraArvore(raiz->ponteiros[pos],chave));
    }
}

static arvoreB insereInterno(arvoreB raiz, atendimento chave, int *mediano, char *paciente, char *terapeuta, char *dia, char *sala, char* situacao, int numero, char* horario){
    int pos;
    int mid;
    arvoreB auxiliar;

    pos = procuraChave(raiz->numeroChaves, raiz->chave,chave);

    if(pos < raiz->numeroChaves && raiz->chave[pos].numero == chave.numero){
        return 0;
    }

    if(raiz->folha){
        memmove(&raiz->chave[pos+1], &raiz->chave[pos], sizeof(*(raiz->chave)) * (raiz->numeroChaves - pos));
        raiz->chave[pos].numero = chave.numero;
        strcpy(raiz->chave[pos].paciente,paciente);
        strcpy(raiz->chave[pos].terapeuta,terapeuta);
        strcpy(raiz->chave[pos].dia,dia);
        strcpy(raiz->chave[pos].sala,sala);
        strcpy(raiz->chave[pos].situacao,situacao);
         strcpy(raiz->chave[pos].horario,horario);
        raiz->chave[pos].numero = numero;

        raiz->numeroChaves++;
    }else{
        auxiliar = insereInterno(raiz->ponteiros[pos], chave, &mid,paciente,terapeuta,dia,sala,situacao,numero, horario);

        if(auxiliar){
            memmove(&raiz->chave[pos+1], &raiz->chave[pos], sizeof(*(raiz->chave)) * (raiz->numeroChaves - pos));
            memmove(&raiz->ponteiros[pos+2], &raiz->ponteiros[pos+1],sizeof(*(raiz->chave)) * (raiz->numeroChaves - pos));
            
            raiz->chave[pos].numero = mid;
            raiz->ponteiros[pos+1] = auxiliar;
            raiz->numeroChaves++;
        }
    }
    if(raiz->numeroChaves >= ordem){
        mid = raiz->numeroChaves/2;
        *mediano = raiz->chave[mid].numero;
        auxiliar = malloc(sizeof(*auxiliar));
        auxiliar->numeroChaves = raiz->numeroChaves - mid - 1;
        auxiliar->folha = raiz->folha;

        memmove(auxiliar->chave, &raiz->chave[mid+1], sizeof(*(raiz->chave)) * auxiliar->numeroChaves);

        if(!raiz->folha){
            memmove(auxiliar->ponteiros, &raiz->ponteiros[mid+1], sizeof(*(raiz->ponteiros)) * (auxiliar->numeroChaves +1));           
        }
        raiz->numeroChaves = mid;
        return auxiliar;
    } else{
        return 0;
    }
}

void InsereArvoreB(arvoreB raiz, atendimento chave,char *paciente, char *terapeuta, char *dia, char *sala, char* situacao, int numero, char* horario){

     arvoreB esquerda;
     arvoreB direita;

     int mediano;

     direita = insereInterno(raiz, chave, &mediano,paciente,terapeuta,dia,sala,situacao,numero,horario);

     if(direita){
         esquerda = malloc(sizeof(*esquerda));
         assert(esquerda);
         memmove(esquerda, raiz, sizeof(*raiz));
         
         raiz->numeroChaves = 1;
         raiz->folha = 0;
         raiz->chave[0].numero = mediano;
         raiz->ponteiros[0] = esquerda;
         raiz->ponteiros[1] = direita;
     }
}

void Menu(int *num){
		printf("\nMenu Administrador\n");
		printf("----------------------");
		printf("\n0 - Sair");
		printf("\n1 - Gerar atendimento");
		printf("\n2 - Imprimir Dados do atendimento\n");
	   scanf("%d",num);

}

void sorteia(arvoreB raiz, atendimento chave, int numero){
	int aleatorio = 0;
	int contador = 1;
	int iterador = 0;

	char paciente[50];
	char terapeuta[50];
	char dia[50];
	char horario[50];
	char situacao[50];
	char sala[10];

	FILE *arquivoTerapeutas;
	FILE *arquivoPacientes;
	FILE *arquivoDias;
	FILE *arquivoHorarios;
	FILE *arquivoSituacoes;
    FILE *arquivoSalas;
    FILE *arquivoAtendimentos;

	arquivoTerapeutas = fopen("Terapeutas.txt", "r");
	arquivoPacientes = fopen("Pacientes.txt", "r");
	arquivoDias = fopen("Dias.txt", "r");
	arquivoHorarios = fopen("Horarios.txt", "r");
	arquivoSituacoes = fopen("Situacoes.txt", "r");
	arquivoSalas = fopen("Salas.txt", "r");


while(iterador < numero){
	srand(time(NULL));
	
	aleatorio = rand()%4944+1;
	contador = 1;

	while(fgets(paciente, sizeof paciente, arquivoPacientes) != NULL){
		if(aleatorio == contador){
		 fgets(paciente, sizeof paciente, arquivoPacientes);
		 break;
		}
		++contador;

	}

	aleatorio = rand()%60+1;
	contador = 1;

	while(fgets(terapeuta, sizeof terapeuta, arquivoTerapeutas) != NULL){
		if(aleatorio == contador){
		 fgets(terapeuta, sizeof terapeuta, arquivoTerapeutas);

		 break;
		}
		++contador;
	}

	aleatorio = rand()%4+1;
	contador = 1;

	while(fgets(dia, sizeof dia, arquivoDias) != NULL){
			if(aleatorio == contador){
			 	fgets(dia, sizeof dia, arquivoDias);
		 		break;
			}
			++contador;
		}

		aleatorio = rand()%4+1;
		contador = 1;

		while(fgets(horario, sizeof horario, arquivoHorarios) != NULL){
			if(aleatorio == contador){
		 		fgets(horario, sizeof horario, arquivoHorarios);
		 		break;
			}
			++contador;
		}

		aleatorio = rand()%11+1;
		contador = 1;

		while(fgets(situacao, sizeof situacao, arquivoSituacoes) != NULL){
			if(aleatorio == contador){
		 		fgets(situacao, sizeof situacao, arquivoSituacoes);
		 		break;
			}
			++contador;
		}

	
		aleatorio = rand()%3+1;
		contador = 1;

		while(fgets(sala, sizeof sala, arquivoSalas) != NULL){
			if(aleatorio == contador){
		 		fgets(sala, sizeof sala, arquivoSalas);
		 		__fpurge(stdin);
		 		break;
			}
			++contador;
		}

	
		InsereArvoreB(raiz, chave,paciente,terapeuta,dia,sala,situacao,iterador, horario);

		iterador++;
	}

}

void imprimirAtendimento(arvoreB raiz, int j){
	printf("\n--------------------------------\n");
	printf("Atendimento %d\n",j);
	printf("paciente = %s", raiz->chave[j].paciente);
	printf("Terapeuta = %s",raiz->chave[j].terapeuta);
	printf("Horario = %s",raiz->chave[j].horario);
	printf("local = %s",raiz->chave[j].sala);
	printf("Situacao = %s",raiz->chave[j].situacao);
	printf("\n--------------------------------");
	getchar();
	getchar();
}


int main(){
    arvoreB arvore;
    atendimento i;
    int j = 0;
    arvore = criaArvore();
    assert(arvore);
    int num = 10;;
    while(num != 0){
    	Menu(&num);
    	switch(num){
    		case 1:
    			printf("Digite o numero de relatorios que deseja inserir aleatoriamente = ");
    			scanf("%d",&j);
 				sorteia(arvore,i,j);
 				printf("\nValores inseridos com sucesso!\n");
 				break;
 			case 2:
 				printf("Imprima o atendimento especifico com numero = ");
 				scanf("%d",&j);
 				imprimirAtendimento(arvore,j);
 				break;
 		}
 	}
    return 0;
}

