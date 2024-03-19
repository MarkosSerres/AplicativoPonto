#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define VALOR 50

int i;
int Menu, Menu2;
char opcao[2];
int c;
int sair = 0;
int janeiro, fevereiro, marco, abril, maio, junho, julho, agosto, setembro, outubro, novembro, dezembro;
int mes;

struct FUNCIONARIO {
    int DIAS;
    char Nome[100];
    float Horas;
    float SalarioHora;
    int CodigoFuncionario;
    char Cargo[100];
};

typedef struct FUNCIONARIO Funcionario;
Funcionario lista[50];

void comeco() {
    for (i = 0; i < VALOR; i++) {
        lista[i].CodigoFuncionario = 0;
    }
}

int encontrarPosicao(Funcionario lista[], int tamanho, int codigoProcurado) {
    for (i = 0; i < tamanho; i++) {
        if (lista[i].CodigoFuncionario == codigoProcurado) {
            return i;
        }
    }
    return -1;
}

int ConsultaPosicaoLivre() {
    int I;
    for (I = 0; I < VALOR; I++) {
        if (lista[I].CodigoFuncionario == 0)
            return I;
    }
    return -1;
}

void GravarFuncionarioEmArquivo(FILE *arquivo, int posicao) {
    fprintf(arquivo, "Nome: %s\n", lista[posicao].Nome);
    fprintf(arquivo, "Codigo do funcionario: %d\n", lista[posicao].CodigoFuncionario);
    fprintf(arquivo, "Cargo do funcionario: %s\n", lista[posicao].Cargo);
    fprintf(arquivo, "Valor da hora trabalhada do funcionario: %.2f\n\n", lista[posicao].SalarioHora);
}

void CadastrarFuncionario() {
    FILE *arquivo = fopen("funcionarios.txt", "a"); // "a" para abrir ou criar o arquivo para escrita no final

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    while (1) {
        int POSICAO = ConsultaPosicaoLivre();
        if (POSICAO == -1) {
            printf("Limite de funcionarios atingido.\n");
            break;
        }

        printf("Insira os dados do funcionario '%d':\n", POSICAO + 1);

        printf("Nome do funcionario:\n");
        scanf(" %99[^\n]", lista[POSICAO].Nome);

        int nome_valido = 1;
        size_t len = strlen(lista[POSICAO].Nome);
        for (size_t i = 0; i < len; i++) {
            if (!isalpha(lista[POSICAO].Nome[i]) && !isspace(lista[POSICAO].Nome[i])) {
                nome_valido = 0;
                break;
            }
        }

        if (!nome_valido) {
            printf("Entrada invalida. Por favor, insira um nome valido.\n");
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        printf("Codigo do funcionario:\n");

        while (1) {
            if (scanf("%d", &lista[POSICAO].CodigoFuncionario) == 1) {
                break;
            } else {
                printf("Entrada invalida. Por favor, digite um numero.\n");

                while ((c = getchar()) != '\n' && c != EOF);
            }
        }

        while ((c = getchar()) != '\n' && c != EOF);

        printf("Cargo do funcionario:\n");
        scanf(" %99[^\n]", lista[POSICAO].Cargo);

        printf("Valor da hora trabalhada:\n");

        while (1) {
            if (scanf("%f", &lista[POSICAO].SalarioHora) == 1) {
                break;
            } else {
                printf("Entrada invalida. Por favor, digite um numero.\n");

                while ((c = getchar()) != '\n' && c != EOF);
            }
        }

        GravarFuncionarioEmArquivo(arquivo, POSICAO);

        printf("Cadastrar mais um funcionario? (S/N)\n");
        scanf(" %1s", opcao);

        if (opcao[0] == 'N') {
            break;
        }
    }
    fclose(arquivo);
}



int ListarFuncionarios() {
    do {
        printf("Menu:\n");
        printf("1 - Exibir funcionario especifico.\n");
        printf("2 - Listar todos os funcionarios.\n");
        printf("0 - Voltar ao Menu Principal\n");
        scanf("%d", &Menu2);

        switch (Menu2) {
            case 0:
                //fclose(arquivo);
                return 0;
                break;

            case 1:
                printf("Digite o codigo do funcionario a ser exibido:\n");
                int indice = 0;
                scanf("%d", &indice);

                int tamanho = VALOR;
                int posicao = encontrarPosicao(lista, tamanho, indice);

                if (posicao != -1) {
                    printf("Funcionario %d:\n", indice);
                    //fprintf(arquivo, "Funcionario %d:\n", indice);
                    printf("Nome: %s\n", lista[posicao].Nome);
                    //fprintf(arquivo, "Nome: %s\n", lista[posicao].Nome);
                    printf("Codigo do funcionario: %d\n", lista[posicao].CodigoFuncionario);
                    //fprintf(arquivo, "Codigo do funcionario: %d\n", lista[posicao].CodigoFuncionario);
                    printf("Cargo do funcionario: %s\n", lista[posicao].Cargo);
                    //fprintf(arquivo, "Cargo do funcionario: %s\n", lista[posicao].Cargo);
                    printf("Valor da hora trabalhada do funcionario: %.2f\n", lista[posicao].SalarioHora);
                    //fprintf(arquivo, "Valor da hora trabalhada do funcionario: %.2f\n\n", lista[posicao].SalarioHora);

                    //fclose(arquivo);
                } else {
                    printf("Codigo invalido ou funcionario nao encontrado.\n");
                }
                char voltarMenuPrincipal2[2];
                do {
                    printf("Deseja voltar ao segundo menu? (S/N): ");
                    scanf("%2s", voltarMenuPrincipal2);
                } while (voltarMenuPrincipal2[0] != 'S' && voltarMenuPrincipal2[0] != 'N');

                if (voltarMenuPrincipal2[0] == 'S') {
                    break;
                } else {
                    return 0;
                }
                break;

            case 2:
                for (i = 0; i < VALOR; i++) {

                    if (lista[i].CodigoFuncionario != 0) {
                        printf("Funcionario: %d\n", i + 1);
                        //fprintf(arquivo, "Funcionario %d:\n", i + 1);
                        printf("Nome: %s\n", lista[i].Nome);
                        //fprintf(arquivo, "Nome: %s\n", lista[i].Nome);
                        printf("Codigo do funcionario: %d\n", lista[i].CodigoFuncionario);
                        //fprintf(arquivo, "Codigo do funcionario: %d\n", lista[i].CodigoFuncionario);
                        printf("Cargo do funcionario: %s\n", lista[i].Cargo);
                        //fprintf(arquivo, "Cargo do funcionario: %s\n", lista[i].Cargo);
                        printf("Valor da hora trabalhada do funcionario: %.2f\n", lista[i].SalarioHora);
                        //fprintf(arquivo, "Valor da hora trabalhada do funcionario: %.2f\n\n", lista[i].SalarioHora);
                    }
                }

                char voltarMenuPrincipal[2];
                do {
                    printf("Deseja voltar ao segundo menu? (S/N): ");
                    scanf("%2s", voltarMenuPrincipal);
                } while (voltarMenuPrincipal[0] != 'S' && voltarMenuPrincipal[0] != 'N');

                if (voltarMenuPrincipal[0] == 'S') {
                    break;
                    //fclose(arquivo);
                } else {
                    return 0;
                }
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }

        printf("Aperte qualquer tecla para continuar.\n");
        getch();
        system("cls");

    } while (1);
    //fclose(arquivo);

    return 0;
}

void AlterarInfo() {
    int indice = 0;
    printf("Codigo do funcionario a ser alterado:\n");

    while (1) {
        if (scanf("%d", &indice) == 1) {
            break;
        } else {
            printf("Entrada invalida. Por favor, digite um numero.\n");

            while ((c = getchar()) != '\n' && c != EOF);
        }
    }

    int tamanho = VALOR;
    int posicao = encontrarPosicao(lista, tamanho, indice);

    if (posicao == -1) {
        printf("Codigo do funcionario nao encontrado.\n");
        return;
    }

    printf("Dados atuais:\n");
    printf("Funcionario %d:\n", indice);
    printf("Nome: %s\n", lista[posicao].Nome);
    printf("Codigo do funcionario: %d\n", lista[posicao].CodigoFuncionario);
    printf("Cargo do funcionario: %s\n", lista[posicao].Cargo);
    printf("Valor da hora trabalhada do funcionario: %.2f\n", lista[posicao].SalarioHora);

    printf("Cadastrar novos dados:\n");

    printf("Nome do funcionario:\n");
    scanf(" %99[^\n]", lista[posicao].Nome);

    int nome_valido = 1;
    size_t len = strlen(lista[posicao].Nome);
    for (size_t i = 0; i < len; i++) {
        if (!isalpha(lista[posicao].Nome[i]) && !isspace(lista[posicao].Nome[i])) {
            nome_valido = 0;
            break;
        }
    }

    if (!nome_valido) {
        printf("Entrada invalida. Por favor, insira um nome valido.\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    printf("Cargo do funcionario:\n");
    scanf(" %99[^\n]", lista[posicao].Cargo);

    printf("Valor da hora trabalhada:\n");

    while (1) {
        if (scanf("%f", &lista[posicao].SalarioHora) == 1) {
            break;
        } else {
            printf("Entrada invalida. Por favor, digite um numero.\n");

            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}




void excluirFuncionario() {
    int indice;
    char opcaoEF;
    printf("Codigo do funcionario que deseja excluir:");
    scanf("%d", &indice);
    printf("Deseja realmente excluir o funcionario %d?(S/N)", indice);
    scanf(" %c", &opcaoEF);

    int tamanho = VALOR;
    int posicao = encontrarPosicao(lista, tamanho, indice);

    if (opcaoEF == 'S' && posicao != -1) {
        memset(&lista[posicao], 0, sizeof(Funcionario));
        printf("Funcionario %d excluido com sucesso.\n", indice);
    } else {
        printf("Funcionario %d nao encontrado ou a exclusao foi cancelada.\n", indice);
    }
}

int Calendario(int mes) {
    int soma = 0;
    int diasNoMes;
    int i;

    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            diasNoMes = 31;
            break;
        case 4: case 6: case 9: case 11:
            diasNoMes = 30;
            break;
        case 2:
            diasNoMes = 28;
            break;
        default:
            printf("Mes invalido.\n");
            return 0;
    }

    for (i = 0; i < diasNoMes; i++) {
        int horasTrabalhadas = 0;

        while (1) {
            printf("Horas trabalhadas no dia %d: ", i + 1);
            if (scanf("%d", &horasTrabalhadas) == 1 && horasTrabalhadas >= 0) {
                break;
            } else {
                printf("Entrada invalida. Por favor, insira um valor numerico positivo.\n");
                while (getchar() != '\n');
            }
        }

        lista[i].DIAS = horasTrabalhadas;
        soma += horasTrabalhadas;
    }

    return soma;
}

int InserirHoras() {
    int indice = 0;
    printf("Inserir as horas trabalhadas.\n");

    while (1) {
        printf("Digite o codigo do funcionario (somente numeros): ");
        if (scanf("%d", &indice) == 1) {
            int tamanho = VALOR;
            int posicao = encontrarPosicao(lista, tamanho, indice);
            if (posicao != -1) {
                break;
            } else {
                printf("Funcionario nao encontrado. Por favor, insira um codigo valido.\n");
            }
        } else {
            printf("Entrada invalida. Por favor, insira um codigo valido.\n");
            while (getchar() != '\n');
        }
    }

        printf("Digite o numero do mes a ser cadastrado (1 a 12): ");
    while (scanf("%d", &mes) != 1 || mes < 1 || mes > 12) {
        printf("Entrada invalida. Por favor, insira um numero de mes valido.\n");
        while (getchar() != '\n');
        printf("Digite o numero do mes a ser cadastrado (1 a 12): ");
    }

    int tamanho = VALOR;
    int posicao = encontrarPosicao(lista, tamanho, indice);

    switch (mes) {
        case 1:
            janeiro = Calendario(mes);
            lista[posicao].DIAS = janeiro;
            break;
        case 2:
            fevereiro = Calendario(mes);
            lista[posicao].DIAS = fevereiro;
            break;
        case 3:
            marco = Calendario(mes);
            lista[posicao].DIAS = marco;
            break;
        case 4:
            abril = Calendario(mes);
            lista[posicao].DIAS = abril;
            break;
        case 5:
            maio = Calendario(mes);
            lista[posicao].DIAS = maio;
            break;
        case 6:
            junho = Calendario(mes);
            lista[posicao].DIAS = junho;
            break;
        case 7:
            julho = Calendario(mes);
            lista[posicao].DIAS = julho;
            break;
        case 8:
            agosto = Calendario(mes);
            lista[posicao].DIAS = agosto;
            break;
        case 9:
            setembro = Calendario(mes);
            lista[posicao].DIAS = setembro;
            break;
        case 10:
            outubro = Calendario(mes);
            lista[posicao].DIAS = outubro;
            break;
        case 11:
            novembro = Calendario(mes);
            lista[posicao].DIAS = novembro;
            break;
        case 12:
            dezembro = Calendario(mes);
            lista[posicao].DIAS = dezembro;
            break;
        default:
            printf("Mes invalido.\n");
            break;
    }
    return 0;
}

void CalcularSalario() {
    int SALARIO;
    int indice = 0;
    int mes = 0;
    printf("Consultar o salario de qual funcionario?\n");
    scanf("%d", &indice);
    printf("Numero do mes a ser consultado: ");
    scanf("%d", &mes);

    int tamanho = VALOR;
    int posicao = encontrarPosicao(lista, tamanho, indice);

    if (posicao != -1) {
        switch (mes) {
            case 1:
                SALARIO = janeiro * lista[posicao].SalarioHora;
                break;
            case 2:
                SALARIO = fevereiro * lista[posicao].SalarioHora;
                break;
            case 3:
                SALARIO = marco * lista[posicao].SalarioHora;
                break;
            case 4:
                SALARIO = abril * lista[posicao].SalarioHora;
                break;
            case 5:
                SALARIO = maio * lista[posicao].SalarioHora;
                break;
            case 6:
                SALARIO = junho * lista[posicao].SalarioHora;
                break;
            case 7:
                SALARIO = julho * lista[posicao].SalarioHora;
                break;
            case 8:
                SALARIO = agosto * lista[posicao].SalarioHora;
                break;
            case 9:
                SALARIO = setembro * lista[posicao].SalarioHora;
                break;
            case 10:
                SALARIO = outubro * lista[posicao].SalarioHora;
                break;
            case 11:
                SALARIO = novembro * lista[posicao].SalarioHora;
                break;
            case 12:
                SALARIO = dezembro * lista[posicao].SalarioHora;
                break;
            default:
                printf("Mes invalido.\n");
                break;
        }
        FILE *arquivo = fopen("salarios.txt", "a");

        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }

        fprintf(arquivo, "Funcionario %d, Mes %d: Salario Total = %dR$\n", indice, mes, SALARIO);
        fclose(arquivo);

        printf("Salario Total: %dR$\n", SALARIO);
    }
    else {
        printf("Funcionario nao encontrado.\n");
    }
}

int main() {
    comeco();
    do {
        printf("Aplicativo de Ponto.\n");
        printf("Empresa: Ficticia Ltda\n");
        printf("\nMENU:\n");
        printf("1 - Cadastrar funcionario\n");
        printf("2 - Listar funcionarios cadastrados\n");
        printf("3 - Alterar informacao sobre funcionario\n");
        printf("4 - Excluir funcionario\n");
        printf("5 - Inserir horas trabalhadas\n");
        printf("6 - Calcular o salario mensal\n");
        printf("0 - Sair\n");
        scanf("%d", &Menu);

        while ((c = getchar()) != '\n' && c != EOF);

        switch (Menu) {
            case 1:
                CadastrarFuncionario();
                break;

            case 2:
                ListarFuncionarios();
                break;

            case 3:
                AlterarInfo();
                break;

            case 4:
                excluirFuncionario();
                break;

            case 5:
                InserirHoras();
                break;

            case 6:
                CalcularSalario();
                break;

            case 0:
                printf("Saindo do programa.\n");
                sair = 1;
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }
        printf("Aperte qualquer tecla para continuar.\n");
        getch();
        system("cls");

    } while (!sair);

    return 0;
}
