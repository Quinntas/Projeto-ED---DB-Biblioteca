#define _CRT_SECURE_NO_WARNINGS

#include "CssC.h"
#include "Essentials.h"

// ------------------------------------------------------------
extern void pausa();
// ------------------------------------------------------------
extern void mostrarCriadores();
// ------------------------------------------------------------

#ifdef OS_Windows

// Funcao que escreve uma linha animada no ecra, usada pelo menu inicial
void linhaAnimada(int q, int a)
{
  int j;
  for (j = 1; j <= q; j++)
  {
    Sleep(200);
    printf("%c", a);
  }
}

// Funcao que escreve uma linha no ecra
void linha(int q, int a)
{
  int j;
  for (j = 1; j <= q; j++)
    printf("%c", a);
}

// Funcao que determina certa cor no ecra
void cor(WORD cor)
{
  HANDLE SaidaSTD = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(SaidaSTD, cor);
}

// Funcao que determina certa posicao no terminal do ecra
void posicao(int x, int y)
{
  HANDLE SaidaSTD = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(SaidaSTD, coord);
}

// Menu principal do programa
int menuPrincipalEstilizado()
{
  system("cls");
  cor(11);
  posicao(22, 1);
  linha(1, 201);
  linha(41, 205);
  linha(1, 187);
  cor(11);
  posicao(22, 2);
  printf("\272");
  posicao(64, 2);
  printf("\272");
  cor(15);
  posicao(38, 2);
  printf("Biblioteca");
  cor(11);
  posicao(22, 3);
  linha(1, 204);
  linha(41, 205);
  linha(1, 185);
  cor(11);
  posicao(22, 4);
  printf("\272 1 \x1a Menu de manejo de Arquivos\t\t\272");
  cor(11);
  posicao(22, 5);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 6);
  printf("\272 2 \x1a Menu de Leitura de Arquivos\t\t\272");
  cor(11);
  posicao(22, 7);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 8);
  printf("\272 3 \x1a Menu de Estatisticas       \t\t\272");
  cor(11);
  posicao(22, 9);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 10);
  printf("\272 4 \x1a Menu dos Clientes          \t\t\272");
  cor(11);
  posicao(22, 11);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 12);
  printf("\272 0 \x1a Sair do Programa           \t\t\272");
  cor(11);
  posicao(22, 13);
  linha(1, 200);
  linha(41, 205), linha(1, 188);
  cor(15);
  posicao(22, 14);
  // cor(11);
  int num;
  printf("\n|| Digite uma opcao: ");
  scanf("%d", &num);
  return num;
}

// Menu de estatistica do programa
int menuEstatisticaEstilizado()
{
  system("cls");
  cor(11);
  posicao(22, 1);
  linha(1, 201);
  linha(41, 205);
  linha(1, 187);
  cor(11);
  posicao(22, 2);
  printf("\272");
  posicao(64, 2);
  printf("\272");
  cor(15);
  posicao(33, 2);
  printf("Menu de Estatisticas");
  cor(11);
  posicao(22, 3);
  linha(1, 204);
  linha(41, 205);
  linha(1, 185);
  cor(11);
  posicao(22, 4);
  printf("\272 1 \x1a Idade Maxima da Lista               \272");
  cor(11);
  posicao(22, 5);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 6);
  printf("\272 2 \x1a Idade Media da Lista                \272");
  cor(11);
  posicao(22, 7);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 8);
  printf("\272 3 \x1a Area com Mais Livros                \272");
  cor(11);
  posicao(22, 9);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 10);
  printf("\272 4 \x1a Pessoas com a Idade Maior que N     \272");
  cor(11);
  posicao(22, 11);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 12);
  printf("\272 5 \x1a Contar Numero de Nomes em uma Cidade\272");
  cor(11);
  posicao(22, 13);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 14);
  printf("\272 6 \x1a Verificar se um Leitor esta na Lista\272");
  cor(11);
  posicao(22, 15);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 16);
  printf("\272 7 \x1a Verificar se um Livro esta na Lista \272");
  cor(11);
  posicao(22, 17);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 18);
  printf("\272 8 \x1a Determinar a Idade com mais Pessoas \272");
  cor(11);
  posicao(22, 19);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 20);
  printf("\272 9 \x1a Sub-Menu de Estatisticas            \272");
  cor(11);
  posicao(22, 21);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 22);
  printf("\272 0 \x1a Voltar ao Menu Principal            \272");
  cor(11);
  posicao(22, 23);
  linha(1, 200);
  linha(41, 205), linha(1, 188);
  cor(15);
  posicao(22, 24);
  // cor(11);
  int num;
  printf("\n|| Digite uma opcao: ");
  scanf("%d", &num);
  return num;
}

// Sub menu de estatistica do programa
int menuEstatistica2Estilizado()
{
  system("cls");
  cor(11);
  posicao(22, 1);
  linha(1, 201);
  linha(41, 205);
  linha(1, 187);
  cor(11);
  posicao(22, 2);
  printf("\272");
  posicao(64, 2);
  printf("\272");
  cor(15);
  posicao(31, 2);
  printf("Sub-Menu de Estatisticas");
  cor(11);
  posicao(22, 3);
  linha(1, 204);
  linha(41, 205);
  linha(1, 185);
  cor(11);
  posicao(22, 4);
  printf("\272 1 \x1a Livros mais Recentes                \272");
  cor(11);
  posicao(22, 5);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 6);
  printf("\272 2 \x1a Livro mais Requisitado              \272");
  cor(11);
  posicao(22, 7);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 8);
  printf("\272 3 \x1a Mostrar Toda a Memoria Ocupada      \272");
  cor(11);
  posicao(22, 9);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 10);
  printf("\272 4 \x1a Area mais Requisitada               \272");
  cor(11);
  posicao(22, 11);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 12);
  printf("\272 5 \x1a Requisitante com mais Livros        \272");
  cor(11);
  posicao(22, 13);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 14);
  printf("\272 6 \x1a Sobrenome mais Usado Pelos Leitores \272");
  cor(11);
  posicao(22, 15);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 16);
  printf("\272 7 \x1a Aniversarios em Datas Especiais     \272");
  cor(11);
  posicao(22, 17);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 18);
  printf("\272 0 \x1a Voltar ao Menu Principal            \272");
  cor(11);
  posicao(22, 19);
  linha(1, 200);
  linha(41, 205), linha(1, 188);
  cor(15);
  posicao(22, 20);
  // cor(11);
  int num;
  printf("\n|| Digite uma opcao: ");
  scanf("%d", &num);
  return num;
}

// Menu estilizador pro programa
int menuMostrarEstilizado()
{
  system("cls");
  cor(11);
  posicao(22, 1);
  linha(1, 201);
  linha(41, 205);
  linha(1, 187);
  cor(11);
  posicao(22, 2);
  printf("\272");
  posicao(64, 2);
  printf("\272");
  cor(15);
  posicao(33, 2);
  printf("Menu de Mostrar Dados");
  cor(11);
  posicao(22, 3);
  linha(1, 204);
  linha(41, 205);
  linha(1, 185);
  cor(11);
  posicao(22, 4);
  printf("\272 1 \x1a Mostrar Todos dos Livros (Area)     \272");
  cor(11);
  posicao(22, 5);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 6);
  printf("\272 2 \x1a Mostrar os Requisitantes com Filtro \272");
  cor(11);
  posicao(22, 7);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 8);
  printf("\272 3 \x1a Mostrar as Requisicoes de um Leitor \272");
  cor(11);
  posicao(22, 9);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 10);
  printf("\272 4 \x1a Leitores que Nunca Requisitaram Nada\272");
  cor(11);
  posicao(22, 11);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 12);
  printf("\272 5 \x1a Mostrar Requisitante por ID         \272");
  cor(11);
  posicao(22, 13);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 14);
  printf("\272 6 \x1a Mostrar Livro por ID                \272");
  cor(11);
  posicao(22, 15);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 16);
  printf("\272 7 \x1a Mostrar Todas as Freguesias         \272");
  cor(11);
  posicao(22, 17);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 18);
  printf("\272 8 \x1a Mostrar Todas as Requisicoes        \272");
  cor(11);
  posicao(22, 19);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 20);
  printf("\272 0 \x1a Voltar ao Menu Principal            \272");
  cor(11);
  posicao(22, 21);
  linha(1, 200);
  linha(41, 205), linha(1, 188);
  cor(15);
  posicao(22, 22);
  // cor(11);
  int num;
  printf("\n|| Digite uma opcao: ");
  scanf("%d", &num);
  return num;
}

// Menu de manejo do programa
int menuManejoEstilizado()
{
  system("cls");
  cor(11);
  posicao(22, 1);
  linha(1, 201);
  linha(41, 205);
  linha(1, 187);
  cor(11);
  posicao(22, 2);
  printf("\272");
  posicao(64, 2);
  printf("\272");
  cor(15);
  posicao(33, 2);
  printf("Menu de Manejo de Dados");
  cor(11);
  posicao(22, 3);
  linha(1, 204);
  linha(41, 205);
  linha(1, 185);
  cor(11);
  posicao(22, 4);
  printf("\272 1 \x1a Forcar Leitura de Dados             \272");
  cor(11);
  posicao(22, 5);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 6);
  printf("\272 2 \x1a Forcar Gravacao de Dados            \272");
  cor(11);
  posicao(22, 7);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 8);
  printf("\272 3 \x1a Adcionar um Livro a Lista           \272");
  cor(11);
  posicao(22, 9);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 10);
  printf("\272 4 \x1a Adicionar um Requisitante a Lista   \272");
  cor(11);
  posicao(22, 11);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 12);
  printf("\272 5 \x1a Efetuar a Requisicao de um Livro    \272");
  cor(11);
  posicao(22, 13);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 14);
  printf("\272 6 \x1a Efetuar a Devolucao um Livro        \272");
  cor(11);
  posicao(22, 15);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 16);
  printf("\272 7 \x1a Modificar Dados nas Estruturas      \272");
  cor(11);
  posicao(22, 17);
  linha(1, 204);
  linha(41, 205), linha(1, 185);
  cor(11);
  posicao(22, 18);
  printf("\272 0 \x1a Voltar ao Menu Principal            \272");
  cor(11);
  posicao(22, 19);
  linha(1, 200);
  linha(41, 205), linha(1, 188);
  cor(15);
  posicao(22, 20);
  // cor(11);
  int num;
  printf("\n|| Digite uma opcao: ");
  scanf("%d", &num);
  return num;
}

// Mensagem do programa, ela possui um _sleep por isso demora um pouco a carregar
void mensagem()
{
  system("cls");
  cor(11);
  posicao(20, 1);
  linha(1, 201);
  linha(41, 205);
  linha(1, 187);
  posicao(20, 2);
  printf("\272");
  posicao(62, 2);
  printf("\272");
  posicao(20, 3);
  linha(1, 200);
  linha(41, 205);
  linha(1, 188);
  cor(10);
  posicao(26, 2);
  printf("BEM VINDO -> CARREGANDO PROGRAMA");
  cor(11);
  posicao(21, 2);
  linhaAnimada(41, 219);
  cor(10);
  posicao(21, 2);
  printf("         CONCLUIDO - APERTE ENTER        ");
  getch();
  cor(1 | 2 | 4);
}

void mesagem2()
{
  system("cls");
  cor(11);
  posicao(20, 1);
  linha(1, 201);
  linha(41, 205);
  linha(1, 187);
  posicao(20, 2);
  printf("\272");
  posicao(62, 2);
  printf("\272");
  posicao(20, 3);
  linha(1, 200);
  linha(41, 205);
  linha(1, 188);
  cor(10);
  posicao(26, 2); // a
  printf("TXT");
  getch();
  ;
}

void mensagem3()
{
  system("cls");
  cor(11);
  posicao(20, 1);
  linha(1, 201);
  linha(41, 205);
  linha(1, 187);
  posicao(20, 2);
  printf("\272");
  posicao(62, 2);
  printf("\272");
  posicao(20, 3);
  linha(1, 200);
  linha(41, 205);
  linha(1, 188);
  cor(10);
  posicao(24, 2);
  printf("TXT");
  getch();
  ;
}

void mensagem4()
{
  system("cls");
  cor(11);
  posicao(20, 1);
  linha(1, 201);
  linha(41, 205);
  linha(1, 187);
  posicao(20, 2);
  printf("\272");
  posicao(62, 2);
  printf("\272");
  posicao(20, 3);
  linha(1, 200);
  linha(41, 205);
  linha(1, 188);
  cor(10);
  posicao(30, 2);
  printf("TXT");
  getch();
  ;
}

#else

// Tela Inicial do progrma
void mensagem()
{
  system("cls");
  printf("\n||||||||||||||||||||||||||||||||||||||||||||||\n");
  printf("||||||||||||||||||||||||||||||||||||||||||||||\n");
  printf("|||||||||||||||||BEM VINDO||||||||||||||||||||\n");
  printf("||||||||||||||||||||||||||||||||||||||||||||||\n");
  printf("||||||||||||||||||||||||||||||||||||||||||||||\n\n");
  printf("|| Todos os dados foram lidos com sucesso");
  printf("|| Criadores do programa --")
  mostrarCriadores()
  pausa();
}

// Menu principal do progrma
int menuPrincipalEstilizado()
{
  int mani;
  system("cls");
  printf("\n|| Escola sua opcao:                           ");
  printf("\n|| 1 - Menu de manejo de arquivos              ");
  printf("\n|| 2 - Menu de leitura de dados                ");
  printf("\n|| 3 - Menu de estatisticas                    ");
  printf("\n|| 4 - Menu para clientes                      ");
  printf("\n|| Escolha sua opcao (0 para sair do progrma): ");
  scanf("%i", &mani);
  return mani;
}

// Menu principal do manejo de itens
int menuManejoEstilizado()
{
  int mani;
  system("cls");
  printf("\n|| Escola sua opcao:                                             ");
  printf("\n|| 1 - Forcar leitura arquivo dos ficheiros                      ");
  printf("\n|| 2 - Forcar gravacao dos arquivos                              ");
  printf("\n|| --------------------------------------------------------------");
  printf("\n|| 3 - Adcionar um novo livro a lista");
  printf("\n|| 4 - Adcionar um novo requisitante a lista");
  printf("\n|| 5 - Efetuar uma requisicao de um livro por parte de uma pessoa");
  printf("\n|| 6 - Devolver um livro que anteriormente estava requisitado    ");
  printf("\n|| 7 - Modificar dados nas estruturas                            ");
  printf("\n|| Escolha sua opcao (0 para voltar): ");
  scanf("%i", &mani);
  return mani;
}

// Menu para mostrar informacoes da lista
int menuMostrarEstilizado()
{
  int mani;
  system("cls");
  printf("\n|| Escola sua opcao:                                            ");
  printf("\n|| 1 - Mostrar todos os livros (organizados por area)           ");
  printf("\n|| 2 - Mostrar os Requisitantes com Filtro                      ");
  printf("\n|| 3 - Mostrar as requisicoes de um dado requisitante           ");
  printf("\n|| 4 - Mostrar uma lista das pessoas que nunca requisitaram nada");
  printf("\n|| 5 - Mostrar requisitante por id                              ");
  printf("\n|| 6 - Mostrar livro por id                                     ");
  printf("\n|| 7 - Mostrar todas as freguesias                              ");
  printf("\n|| 8 - Mostrar todas as requisicoes                             ");
  printf("\n|| Escolha sua opcao (0 para voltar): ");
  scanf("%i", &mani);
  return mani;
}

// Menu para mostrar estatisticas da lista
int menuEstatisticaEstilizado()
{
  int mani;
  system("cls");
  printf("\n|| Escola sua opcao:                                                                ");
  printf("\n|| 1 - Determinar a idade maxima de todas as pessoas                                ");
  printf("\n|| 2 - Determinar a media das idades de todas as pessoas                            ");
  printf("\n|| 3 - Determinar qual a area com mais livros                                       ");
  printf("\n|| 4 - Contar o numero de pessoas cuja idade e superior a um dado valor             ");
  printf("\n|| 5 - Contar o numero de pessoas de uma dada cidade, que no nome contem outro, nome");
  printf("\n|| 6 - Verificar se uma pessoa existe na lista, dando o nome                        ");
  printf("\n|| 7 - Verificar se um dado livro existe (dado o ISBN)                              ");
  printf("\n|| 8 - Determinar qual a idade com mais requisitantes                               ");
  printf("\n|| 9 - Ir para o sub-menu                                                           ");
  printf("\n|| Escolha sua opcao (0 para voltar): ");
  scanf("%i", &mani);
  return mani;
}

// Sub - Menu para mostrar estatisticas da lista
int menuEstatistica2Estilizado()
{
  int mani;
  system("cls");
  printf("\n|| Escola sua opcao:                                                    ");
  printf("\n|| 1 - Determinar qual(ais) os livros mais recentes                     ");
  printf("\n|| 2 - Determinar qual o livro mais requisitado                         ");
  printf("\n|| 3 - Determinar a memoria ocupada por toda a Estrutura de Dados       ");
  printf("\n|| 4 - Determinar qual area mais requisitada                            ");
  printf("\n|| 5 - Listar o requisitante que no momento tem mais livros requisitados");
  printf("\n|| 6 - Determinar qual o sobrenome mais usado pelos requisitantes       ");
  printf("\n|| 7 - Mostrar aniversarios em datas especiais                          ");
  printf("\n|| Escolha sua opcao (0 para voltar ao menu principal): ");
  scanf("%i", &mani);
  return mani;
}

#endif
