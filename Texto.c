#define _CRT_SECURE_NO_WARNINGS

#include "Texto.h"

// ------------------------------------------------------------
extern void pushListaLivros(Lista *L, Livros *X);
extern void pushListaRequisitantes(Lista *L, Requisitantes *X);
extern void pushListaRequisicoes(Lista *L, Requisicao *X);
extern Freguesias *atualizarFreguesias(Freguesias *info, Requisitantes *infoR);
extern void mostrarFreguesiasALL(Freguesias *info);
extern void mostrarFreguesiasSingle(Freguesias *info);
// ------------------------------------------------------------
extern int idadeAtual(NodeR *P);
// ------------------------------------------------------------
extern int idadeComMaisPessoas(Lista *L);
extern const char *sobrenomeMaisUsado(Lista *L);
extern const char *areaMaisUsada(Lista *L);
extern const char *areaComMaisLivros(Lista *L);
// ------------------------------------------------------------
extern bool checkDia(int dia, int mes, int ano);
extern void limparbuffer();
// ------------------------------------------------------------
extern void hash_add_areaO(Hashtable *H, Livros *X);
extern void hash_add_requisitanteAL(Hashtable *H, Requisitantes *X);
extern void hash_add_requisitanteAP(Hashtable *H, Requisitantes *X);
extern void hash_add_requisitanteFR(Hashtable *H, Requisitantes *X);
// ------------------------------------------------------------

// Funcao que devolve o sobrenome de um requisitante
const char *pegarSobrenome(NodeR *P)
{
    int stringSize = strlen(P->infoRequisitantes->nome);
    const char *returnValue = P->infoRequisitantes->nome;
    int count = 1; // Valor que pode ser mudado para pegar qualquer parte de uma string, separado por ' '
    while (count != 0)
    {
        if (P->infoRequisitantes->nome[stringSize] == ' ')
            count--;
        stringSize--;
    }
    return returnValue += stringSize + 2;
}

// funcao para gravacao de logs para debug
void logIT(const char *logs)
{
    time_t mytime;
    mytime = time(NULL);
    struct tm hr = *localtime(&mytime);
    FILE *file = fopen("Logs.txt", "a");
    if (strcmp(logs, "Programa Iniciado") == 0)
    {
        fprintf(file, "\n\n$ %s no dia %d/%d/%d as %d:%d:%d ", logs, hr.tm_mday, hr.tm_mon + 1, hr.tm_year + 1900, hr.tm_hour, hr.tm_min, hr.tm_sec);
    }
    else
    {
        fprintf(file, "\n\n| %d/%d/%d %d:%d:%d | - %s", hr.tm_mday, hr.tm_mon + 1, hr.tm_year + 1900, hr.tm_hour, hr.tm_min, hr.tm_sec, logs);
    }
    fclose(file);
}

// Funcao que limpar o arquivo de logs se aberto no dia 1 ao dia 3
void limparLogs()
{
    time_t mytime;
    mytime = time(NULL);
    struct tm hr = *localtime(&mytime);
    if (hr.tm_mday >= 1 && hr.tm_mday <= 3)
    {
        FILE *file = fopen("Logs.txt", "w");
        fprintf(file, "\n$ Logs limpos");
        fclose(file);
    }
}

// Funcao que grava em um ficheiro todos as diferentes areas
void gravarAreas(Lista *L)
{
    if (!L)
        return;
    Node *P = L->head;
    FILE *file = fopen("Areas.txt", "w+"); // Esse arquivo ira ser apagado ao sair da aplicacao
    if (!file)
        return;
    char linha[MAX_S];
    bool areaExiste = false;
    while (P)
    {
        while (!feof(file))
        {
            fscanf(file, "%s", linha);
            if (linha != NULL)
                if (strcmp(linha, P->infoLivros->area) == 0)
                {
                    areaExiste = true;
                    break;
                }
        }
        if (areaExiste == false)
            fprintf(file, "\n%s", P->infoLivros->area);
        fseek(file, 0, SEEK_SET);
        areaExiste = false;
        P = P->next;
    }
    fclose(file);
}

// Devolve o tamanho do file areas
int sizeAreas()
{
    FILE *file = fopen("Areas.txt", "r");
    int i = 0;
    char nulo[41];
    while (!feof(file))
    {
        fgets(nulo, sizeof(nulo), file);
        i++;
    }
    fclose(file);
    return i;
}

// Funcao que grava em um ficheiro as areas ordenadas
void ordenarAreas(Lista *L)
{
    if (!L)
        return;
    int size = sizeAreas();
    FILE *file = fopen("Areas.txt", "r");
    if (!file)
        return;

    Node *P = L->head;

    Aux *infoareas = (Aux *)malloc(size * sizeof(Aux));
    int i = 0;
    char linha[MAX_S];
    while (!feof(file))
    {
        fscanf(file, "%s", linha);
        if (linha != NULL)
            strcpy(infoareas[i].aux, linha);
        i++;
    }
    fclose(file);
    file = fopen("Livros_Ordenados.txt", "w"); // Esse arquivo ira ser apagado ao sair da aplicacao
    if (!file)
        return;
    for (i = 0; i < size; i++)
    {
        if (infoareas[i].aux != NULL)
        {
            fprintf(file, "\n-2");
            while (P)
            {
                if ((strcmp(infoareas[i].aux, P->infoLivros->area) == 0) && P->infoLivros->area != NULL)
                    fprintf(file, "\n%d", P->infoLivros->id);
                P = P->next;
            }
            P = L->head;
        }
    }
    free(infoareas);
    fclose(file);
}

// Funcao que grava em um ficheiro todas as areas desordenadas
void gravarAreasDesordenadas(Lista *L)
{
    if (!L)
        return;
    FILE *file = fopen("Todas_Areas.txt", "w"); // Esse arquivo ira ser apagado ao sair da aplicacao
    if (!file)
        return;
    Node *P = L->head;
    while (P)
    {
        fprintf(file, "\n%s", P->infoLivros->area);
        P = P->next;
    }
    fclose(file);
}

// Funcao que grava todos os sobrenomes dos requisitantes registrados
void gravarSobrenomes(Lista *L)
{
    if (!L)
        return;
    NodeR *P = L->headR;
    FILE *file = fopen("Sobrenomes.txt", "w"); // Esse arquivo ira ser apagado ao sair da aplicacao
    if (!file)
        return;
    while (P)
    {
        fprintf(file, "\n%s", pegarSobrenome(P));
        P = P->next;
    }
    fclose(file);
}

// Funcao que verifica se o id esta inserido corretamente
bool funcaoId(int num)
{
    int temp = num;
    int id = 0;
    int factor = 1;
    short int count = 0;
    while (temp)
    {
        temp = temp / 10;
        factor = factor * 10;
    }
    while (factor > 1)
    {
        factor = factor / 10;
        count++;
        id += num / factor;
        num = num % factor;
    }
    if (count != 9)
        return false;
    else if (id % 10 != 0)
        return false;
    else
        return true;
}

long int control = 100000000;
// Funcao que gera um id uncio para um requisitante
long int funcaoGerarNovoId(Lista *L)
{
    NodeR *P = L->headR;
    bool check = true;
    while (P)
    {
        do
        {
            control += 1;
            if (control > 999999999)
            {
                logIT("ERROR 20 - Nao ha ids suficientes para o programa funcionar");
                exit(0);
            }
        } while (funcaoId(control) == false);
        check = true;
        if (P->infoRequisitantes->id == control)
        {
            P = L->headR;
            check = false;
        }
        if (check == true)
            P = P->next;
    }
    return control;
}

// Funcao que faz o check list dos livros antes de entrarem no sistema
Livros *checkLivros(Livros *infolivros)
{
    if (!infolivros)
        return NULL;
    // system("cls");
    bool check = false;
    do
    {
        check = checkDia(infolivros->dataDePublicacao.dia, infolivros->dataDePublicacao.mes, infolivros->dataDePublicacao.ano);
        if (check == false)
        {
            printf("\n|| O dia do livro %d (%d/%d/%d) esta errado, digite corretamente (DD/MM/YYYY): ", infolivros->id, infolivros->dataDePublicacao.dia, infolivros->dataDePublicacao.mes, infolivros->dataDePublicacao.ano);
            scanf("%d/%d/%d", &infolivros->dataDePublicacao.dia, &infolivros->dataDePublicacao.mes, &infolivros->dataDePublicacao.ano);
        }
    } while (check == false);
    return infolivros;
}

bool t = false;
// Funcao que faz o check list dos requisitantes antes de entrarem no sistema
Requisitantes *checkRequisitantes(Requisitantes *infoRequisitantes, Freguesias *F, Lista *L, int deubgCount)
{
    if (!infoRequisitantes)
        return NULL;
    // system("cls");
    char c = 'a';
    bool check = false;
    do
    {
        check = funcaoId(infoRequisitantes->id);
        if (check == false)
        {
            if (t == false)
            {
                if (c != 't' || c != 'T')
                {
                    printf("\n|| #%d O id (%d) esta errado, deseja: ", deubgCount, infoRequisitantes->id);
                    printf("\n|| \'M\' - Introduzir Manualmente (Segindo as regras do projeto)");
                    printf("\n|| \'A\' - Introduzir Automaticamente");
                    printf("\n|| \'T\' - Introduzir Automaticamente para todos os ids errados");
                    printf("\n|| Digite aqui sua opcao (M/A): ");
                    fflush(stdin);
                    // limparbuffer();
                    scanf("%c", &c);
                    if (c == 'm' || c == 'M')
                    {
                        printf("\n|| Digite um novo: ");
                        scanf("%d", &infoRequisitantes->id);
                    }
                    else if (c == 'a' || c == 'A')
                    {
                        infoRequisitantes->id = funcaoGerarNovoId(L);
                    }
                    else
                    {
                        system("cls");
                        t = true;
                        infoRequisitantes->id = funcaoGerarNovoId(L);
                    }
                    if(t == false)
                        printf("|| Novo id: %d\n", infoRequisitantes->id);
                }
            }
            else
            {
                infoRequisitantes->id = funcaoGerarNovoId(L);
            }
        }
    } while (check == false);
    do
    {
        check = true;
        if (infoRequisitantes->infoFreguesias == NULL)
        {
            printf("\n|| A freguesia dita nao existe, por vafor insira uma nova: ");
            limparbuffer();
            fgets(infoRequisitantes->freguesia, sizeof(infoRequisitantes->freguesia), stdin);
            infoRequisitantes->infoFreguesias = atualizarFreguesias(F, infoRequisitantes);
            if (infoRequisitantes->infoFreguesias == NULL)
                check = false;
        }
    } while (check == false);
    do
    {
        check = checkDia(infoRequisitantes->idade.dia, infoRequisitantes->idade.mes, infoRequisitantes->idade.ano);
        if (check == false)
        {
            printf("\n|| A idade do requisitante %d (%d/%d/%d) esta errada, digite corretamente (DD/MM/YYYY): ", infoRequisitantes->id, infoRequisitantes->idade.dia, infoRequisitantes->idade.mes, infoRequisitantes->idade.ano);
            scanf("%d/%d/%d", &infoRequisitantes->idade.dia, &infoRequisitantes->idade.mes, &infoRequisitantes->idade.ano);
        }
    } while (check == false);
    if (infoRequisitantes->livrosRequisitados < 0 || infoRequisitantes->livrosRequisitados > MAX)
    {
        printf("\n|| Os livros requisitados (%d) do cliente %d estao errados, resetando para 0...", infoRequisitantes->livrosRequisitados, infoRequisitantes->livrosRequisitados);
        infoRequisitantes->livrosRequisitados = 0;
    }
    return infoRequisitantes;
}

// Funcao que verifica os dados das requisicoes antes do push
Requisicao *checkRequisicao(Requisicao *infoRequisicao)
{
    if (!infoRequisicao)
        return NULL;
    // system("cls");
    bool check = false;
    do
    {
        check = checkDia(infoRequisicao->inicioDaRequisicao.dia, infoRequisicao->inicioDaRequisicao.mes, infoRequisicao->inicioDaRequisicao.ano);
        if (check == false)
        {
            printf("\n|| O inicio da requisicao %d (%d/%d/%d) esta errada, digite corretamente (DD/MM/YYYY): ", infoRequisicao->idRequisicao, infoRequisicao->inicioDaRequisicao.dia, infoRequisicao->inicioDaRequisicao.mes, infoRequisicao->inicioDaRequisicao.ano);
            scanf("%d/%d/%d", &infoRequisicao->inicioDaRequisicao.dia, &infoRequisicao->inicioDaRequisicao.mes, &infoRequisicao->inicioDaRequisicao.ano);
        }
    } while (check == false);
    do
    {
        check = checkDia(infoRequisicao->fimDaRequisicao.dia, infoRequisicao->fimDaRequisicao.mes, infoRequisicao->fimDaRequisicao.ano);
        if (check == false)
        {
            printf("\n|| O fim da requisicao %d (%d/%d/%d) esta errada, digite corretamente (DD/MM/YYYY): ", infoRequisicao->idRequisicao, infoRequisicao->fimDaRequisicao.dia, infoRequisicao->fimDaRequisicao.mes, infoRequisicao->fimDaRequisicao.ano);
            scanf("%d/%d/%d", &infoRequisicao->fimDaRequisicao.dia, &infoRequisicao->fimDaRequisicao.mes, &infoRequisicao->fimDaRequisicao.ano);
        }
    } while (check == false);
    return infoRequisicao;
}

// Funcao para ler o arquivo de texto dos livros
void lerArqLivros(Lista *L, Hashtable *H)
{
    if (!L || !H)
        return;
    FILE *file = fopen("Livros.txt", "r");
    if (file == NULL)
        return;
    char linha[100];
    char *aux = NULL, *data = NULL, *auxData = NULL;
    while (fgets(linha, sizeof(linha), file))
    {
        Livros *info = (Livros *)malloc(sizeof(Livros));
        aux = strtok(linha, "\t");
        if (aux)
            info->id = atoi(aux);

        aux = strtok(NULL, "\t");
        if (aux)
            data = aux;

        aux = strtok(NULL, "\t");
        if (aux)
        {
            info->ISBN = (char *)malloc((strlen(aux) + 1) * sizeof(char));
            strcpy(info->ISBN, aux);
            info->ISBN[(strlen(aux) - 1)] = '\0';
        }

        aux = strtok(NULL, "\t");
        if (aux)
        {
            info->area = (char *)malloc((strlen(aux) + 1) * sizeof(char));
            strcpy(info->area, aux);
            info->area[(strlen(aux))] = '\0';
        }

        aux = strtok(NULL, "\t");
        if (aux)
        {
            info->titulo = (char *)malloc((strlen(aux) + 1) * sizeof(char));
            strcpy(info->titulo, aux);
            info->titulo[(strlen(aux) - 1)] = '\0';

            auxData = strtok(data, "/");
            info->dataDePublicacao.dia = atoi(auxData);
            auxData = strtok(NULL, "/");
            info->dataDePublicacao.mes = atoi(auxData);
            auxData = strtok(NULL, "/");
            info->dataDePublicacao.ano = atoi(auxData);

            info = checkLivros(info);
            pushListaLivros(L, info);
            hash_add_areaO(H, info);
        }
    }
    fclose(file);
    // system("cls");
}

// Funcao para ler o arquivo de requisitantes
void lerArqRequisitantes(Lista *L, Freguesias *infoF)
{
    if (!L)
        return;
    FILE *file = fopen("Requisitantes.txt", "r");
    if (file == NULL)
        return;
    char linha[100];
    char *aux = NULL, *data = NULL, *auxData = NULL;
    int deubgCount = 1;
    while (fgets(linha, sizeof(linha), file))
    {
        Requisitantes *info = (Requisitantes *)malloc(sizeof(Requisitantes));
        aux = strtok(linha, "\t");
        if (aux)
            info->id = atoi(aux);

        aux = strtok(NULL, "\t");
        if (aux)
            info->livrosRequisitados = atoi(aux);

        aux = strtok(NULL, "\t");
        if (aux)
            data = aux;

        aux = strtok(NULL, "\t");
        if (aux)
        {
            info->freguesia = (char *)malloc((strlen(aux) + 1) * sizeof(char));
            strcpy(info->freguesia, aux);
            // info->freguesia[(strlen(aux)-1)] = '\0';
            // printf("\n %s", info->freguesia);
        }

        aux = strtok(NULL, "\t");
        if (aux)
        {
            info->nome = (char *)malloc((strlen(aux) + 1) * sizeof(char));
            strcpy(info->nome, aux);
            info->nome[(strlen(aux) - 1)] = '\0';

            auxData = strtok(data, "/");
            info->idade.dia = atoi(auxData);
            auxData = strtok(NULL, "/");
            info->idade.mes = atoi(auxData);
            auxData = strtok(NULL, "/");
            info->idade.ano = atoi(auxData);

            info->infoFreguesias = atualizarFreguesias(infoF, info);
            info = checkRequisitantes(info, infoF, L, deubgCount);
            deubgCount++;
            pushListaRequisitantes(L, info);
        }
    }
    fclose(file);
    // system("cls");
}

// Funcao que atualiza a estrutura de requisicoes para requisitantes
Requisitantes *atualizaRequisicoesR(Lista *L, Requisicao *X)
{
    NodeR *P = L->headR;
    while (P)
    {
        if (X->codR == P->infoRequisitantes->id)
            return P->infoRequisitantes;
        P = P->next;
    }
    return NULL;
}

// Funcao que atualiza a estrutura de requisicoes para livros
Livros *atualizaRequisicoesL(Lista *L, Requisicao *X)
{
    Node *P = L->head;
    while (P)
    {
        if (X->codR == P->infoLivros->id)
            return P->infoLivros;
        P = P->next;
    }
    return NULL;
}

// Funcao para ler o arquivo de requisicoes
void lerArqRequisicoes(Lista *L)
{
    if (!L)
        return;
    FILE *file = fopen("Requisicoes.txt", "r");
    if (file == NULL)
        return;
    char linha[100];
    char *aux = NULL, *data = NULL, *auxData = NULL, *data2 = NULL;
    while (fgets(linha, sizeof(linha), file))
    {
        Requisicao *info = (Requisicao *)malloc(sizeof(Requisicao));
        aux = strtok(linha, "\t");
        if (aux)
            data = aux;

        aux = strtok(NULL, "\t");
        if (aux)
            data2 = aux;

        aux = strtok(NULL, "\t");
        if (aux)
            info->idRequisicao = atoi(aux);

        aux = strtok(NULL, "\t");
        if (aux)
            info->codL = atoi(aux);

        aux = strtok(NULL, "\t");
        if (aux)
        {
            info->codR = atoi(aux);
            auxData = strtok(data, "/");
            info->inicioDaRequisicao.dia = atoi(auxData);
            auxData = strtok(NULL, "/");
            info->inicioDaRequisicao.mes = atoi(auxData);
            auxData = strtok(NULL, "/");
            info->inicioDaRequisicao.ano = atoi(auxData);

            auxData = strtok(data2, "/");
            info->fimDaRequisicao.dia = atoi(auxData);
            auxData = strtok(NULL, "/");
            info->fimDaRequisicao.mes = atoi(auxData);
            auxData = strtok(NULL, "/");
            info->fimDaRequisicao.ano = atoi(auxData);

            info->livros = atualizaRequisicoesL(L, info);
            info->requisitante = atualizaRequisicoesR(L, info);

            info = checkRequisicao(info);
            pushListaRequisicoes(L, info);
        }
    }
    fclose(file);
    // system("cls");
}

// Funcao que devolve o tamanho do ficheiro freguesias
int tamFreg()
{
    FILE *file = fopen("Freguesia.txt", "r");
    if (!file)
    {
        logIT("File de freguesias nao foi executado");
        return 0;
    }
    int size = 0;
    fscanf(file, "%d", &size);
    fclose(file);
    return size;
}

int sizeFREG;

// Funcao que le os arquivos de freguesias
void lerArqFreguesias(Freguesias *info)
{
    FILE *file = fopen("Freguesia.txt", "r");
    char linha[1000], *aux;
    fgets(linha, sizeof(linha), file);
    while (fgets(linha, sizeof(linha), file))
    {
        aux = strtok(linha, "\t");
        if (aux)
        {
            info->idFreguesia = (char *)malloc(sizeof(char) * (strlen(aux) + 1));
            strcpy(info->idFreguesia, aux);
        }
        aux = strtok(NULL, "\t");
        if (aux)
        {
            info->freguesia = (char *)malloc(sizeof(char) * (strlen(aux) + 1));
            strcpy(info->freguesia, aux);
        }
        aux = strtok(NULL, "\t");
        if (aux)
        {
            info->idDistrito = (char *)malloc(sizeof(char) * 3);
            info->idDistrito[0] = aux[2];
            info->idDistrito[1] = aux[3];
            info->idDistrito[2] = '\0';
        }
        aux = strtok(NULL, "\t");
        if (aux)
        {
            info->distrito = (char *)malloc(sizeof(char) * (strlen(aux) + 1));
            strcpy(info->distrito, aux);
        }
        aux = strtok(NULL, "\t");
        if (aux)
        {
            info->idConcelho = (char *)malloc(sizeof(char) * 3);
            info->idConcelho[0] = aux[2];
            info->idConcelho[1] = aux[3];
            info->idConcelho[2] = '\0';
        }
        aux = strtok(NULL, "\t");
        if (aux)
        {
            info->concelho = (char *)malloc(sizeof(char) * (strlen(aux) + 1));
            strcpy(info->concelho, aux);
        }
        aux = strtok(NULL, "\t");
        if (aux)
        {
            info->idCidade = (char *)malloc(sizeof(char) * 3);
            strcpy(info->idCidade, aux);
        }
        aux = strtok(NULL, "\t");
        if (aux)
        {
            info->cidade = (char *)malloc(sizeof(char) * (strlen(aux) + 1));
            strcpy(info->cidade, aux);
            info->cidade[(strlen(aux) - 1)] = '\0';
        }
        // printf("\n%s %s | %s %s | %s %s | %s %s", info->idFreguesia, info->freguesia, info->idDistrito, info->distrito, info->idConcelho, info->concelho, info->idCidade, info->cidade);
        info++;
    }
    fclose(file);
}

// Funcao que chama todos os ler arquivos
void lerArqLocais(Lista *L, Hashtable *H, Freguesias *F)
{
    if (!L || !H || !F)
        return;
    lerArqLivros(L, H);
    lerArqRequisitantes(L, F);
    lerArqRequisicoes(L);
}

// Funcao que le os arquivos das freguesias, distritos, cidades e concelhos
void lerArqFDCC(Freguesias *info)
{
    if (!info)
        return;
    lerArqFreguesias(info);
}

// Funcao que grava todos os arquivos em um ficheiro txt
void gravarTXT(Lista *L, Freguesias *F)
{
    FILE *fileLivros = fopen("!Livros Gravados.txt", "w");
    Node *P = L->head;
    while (P)
    {
        fprintf(fileLivros, "%d\t%s\t%d/%d/%d\t%s\t%s\n", P->infoLivros->id, P->infoLivros->ISBN, P->infoLivros->dataDePublicacao.dia, P->infoLivros->dataDePublicacao.mes, P->infoLivros->dataDePublicacao.ano, P->infoLivros->area, P->infoLivros->titulo);
        P = P->next;
    }
    fclose(fileLivros);

    FILE *fileRequisitantes = fopen("!Requisitantes Gravados.txt", "w");
    NodeR *P2 = L->headR;
    while (P2)
    {
        fprintf(fileRequisitantes, "%d\t%d/%d/%d\t%s\t%s\t%d\n", P2->infoRequisitantes->id, P2->infoRequisitantes->idade.dia, P2->infoRequisitantes->idade.mes, P2->infoRequisitantes->idade.ano, P2->infoRequisitantes->freguesia, P2->infoRequisitantes->nome, P2->infoRequisitantes->livrosRequisitados);
        P2 = P2->next;
    }
    fclose(fileRequisitantes);

    FILE *fileRequisicoes = fopen("!Requisicoes Gravadas.txt", "w");
    NodeRC *P3 = L->headRC;
    while (P3)
    {
        fprintf(fileRequisicoes, "%d/%d/%d\t%d/%d/%d\t%d\t%d\t%d\n", P3->infoRequisicoes->inicioDaRequisicao.dia, P3->infoRequisicoes->inicioDaRequisicao.mes, P3->infoRequisicoes->inicioDaRequisicao.ano, P3->infoRequisicoes->fimDaRequisicao.dia, P3->infoRequisicoes->fimDaRequisicao.mes, P3->infoRequisicoes->fimDaRequisicao.ano, P3->infoRequisicoes->idRequisicao, P3->infoRequisicoes->codL, P3->infoRequisicoes->codR);
        P3 = P3->next;
    }
    fclose(fileRequisicoes);

    FILE *fileFreguesias = fopen("!Freguesias Gravadas.txt", "w");
    while (F)
    {
        fprintf(fileFreguesias, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", F->idFreguesia, F->freguesia, F->idDistrito, F->distrito, F->idConcelho, F->concelho, F->idCidade, F->cidade);
        F++;
    }
    fclose(fileFreguesias);
}

// Funcao que grava todos os arquivos em um ficheiro csv
void gravarCSV(Lista *L, Freguesias *F)
{
    FILE *fileLivros = fopen("!Livros Gravados.csv", "w");
    fprintf(fileLivros, "Id do Livro;ISBN;Data de Publicacao;Area;Titulo\n");
    Node *P = L->head;
    while(P)
    {
        fprintf(fileLivros, "%d;%s;%d-%d-%d;%s;%s\n", P->infoLivros->id, P->infoLivros->ISBN, P->infoLivros->dataDePublicacao.dia, P->infoLivros->dataDePublicacao.mes, P->infoLivros->dataDePublicacao.ano, P->infoLivros->area, P->infoLivros->titulo);
        P = P->next;
    }
    fclose(fileLivros);

    FILE *fileRequisitantes = fopen("!Requisitantes Gravados.csv", "w");
    fprintf(fileRequisitantes, "Id do Requisitante;Data de Nascimento;Freguesia;Nome do Requisitante;Quantidade de Livros Requisitados\n");
    NodeR *P2 = L->headR;
    while (P2)
    {
        fprintf(fileRequisitantes, "%d;%d-%d-%d;%s;%s;%d\n", P2->infoRequisitantes->id, P2->infoRequisitantes->idade.dia, P2->infoRequisitantes->idade.mes, P2->infoRequisitantes->idade.ano, P2->infoRequisitantes->freguesia, P2->infoRequisitantes->nome, P2->infoRequisitantes->livrosRequisitados);
        P2 = P2->next;
    }
    fclose(fileRequisitantes);

    FILE *fileRequisicoes = fopen("!Requisicoes Gravadas.csv", "w");
    fprintf(fileRequisicoes, "Data do Inicio da Requisicao;Data do Fim da Requisicao;Id da Requisicao;Codigo do Livro;Codigo do Requisitante\n");
    NodeRC *P3 = L->headRC;
    while (P3)
    {
        fprintf(fileRequisicoes, "%d-%d-%d;%d-%d-%d;%d;%d;%d\n", P3->infoRequisicoes->inicioDaRequisicao.dia, P3->infoRequisicoes->inicioDaRequisicao.mes, P3->infoRequisicoes->inicioDaRequisicao.ano, P3->infoRequisicoes->fimDaRequisicao.dia, P3->infoRequisicoes->fimDaRequisicao.mes, P3->infoRequisicoes->fimDaRequisicao.ano, P3->infoRequisicoes->idRequisicao, P3->infoRequisicoes->codL, P3->infoRequisicoes->codR);
        P3 = P3->next;
    }
    fclose(fileRequisicoes);

    FILE *fileFreguesias = fopen("!Freguesias Gravadas.csv", "w");
    fprintf(fileFreguesias, "Id da Freguesia;Freguesia;Id do Distrito;Distrito;Id do Concelho;Concelho;Id da Cidade;Cidade\n");
    while (F)
    {
        fprintf(fileFreguesias, "%s;%s;%s;%s;%s;%s;%s;%s\n", F->idFreguesia, F->freguesia, F->idDistrito, F->distrito, F->idConcelho, F->concelho, F->idCidade, F->cidade);
        F++;
    }
    fclose(fileFreguesias);
}

// Funcao que guarda em ficheiros .txt/.xls os requisitantes e os livros
void gravarArquivos(Lista *L, Freguesias *F)
{
    if (!L)
        return;
    int mani = 0;
    do
    {
        system("cls");
        printf("\n|| Escolha sua opcao:");
        printf("\n|| 1 - Gravar todos os dados em .txt");
        printf("\n|| 2 - Gravar todos os dados em .csv");
        printf("\n|| Digite sua opcao (0 para voltar ao menu): ");
        scanf("%d", &mani);
        switch (mani)
        {
        case 1:
            gravarTXT(L, F);
            printf("\n|| Dados gravados com sucesso\n");
            pausa();
            break;
        case 2:
            gravarCSV(L, F);
            printf("\n|| Dados gravados com sucesso\n");
            pausa();
            break;
        }
    } while (mani != 0);
}

// Funcao para destruir arquivos auxiliares
void freeFiles()
{
    system("del Areas.txt");
    system("del Sobrenomes.txt");
    system("del Idades.txt");
    system("del Livros_Ordenados.txt");
    system("del Todas_Areas.txt");
    system("del Funcoes_pre_Carregadas.txt");
}
