// PROJETO - TESTE DE AVIÕES

//================= DEFINES ==================================================== 
#include "defines.h"
#include "manipulaTela.h"
#include "manipulaArquivo.h"
#include "estruturas.h"
#include "menu.h"
#include "funcoesAux.h"

#include "dadosAviao.h"
#include "aviao.h"
#include "dadosPista.h"
#include "pista.h"
#include "dadosTeste.h"
#include "teste.h"


//================= PROTÓTIPOS DAS FUNÇÕES =====================================
void encaminharOpcoes(int opcao1, int opcao2);                                  
int escrevaLimitado(int margemReal, int margemInicial, int altura, int minimo,  
                    int tamanho, int limite, char * string, int inicio);

void apresentaInfo(Aviao *dadoAviao, Pista *dadoPista, Teste *dadoTeste, char *msg);

int lerOpcao(int coluna, int linha);
int strStr(char *string, char *texto);

int main(void)
{
//Declarações
    COORD szConsole;
    int opcao1, opcao2;                                                 
//Instruções                                         
    system("title TESTE DE AVIÕES");                                     
	   szConsole.X = 80;  // Altura Janela
	   szConsole.Y = 30 ; // Largura Janela
	   redimencionarConsole(szConsole);
       //setlocale(LC_ALL, "Portuguese");
    arquivosNecessarios();
    do
    {
        menuPrincipal(&opcao1, &opcao2);
        if(opcao1 == 4)
            return 0;
        encaminharOpcoes(opcao1, opcao2);
        //clrscr();
        system("cls");
    }while(opcao1 != 4);
    
  getch();
  return 0;
}
//------------------------------------------------------------------------------
//Objetivo  : Recebe opções do usuário e redireciona para as funções corretas para o devido tratamento.
//Parâmetros: Opcao 1 e 2.
//Retorno   : Nenhum.
void encaminharOpcoes(int opcao1, int opcao2)
{
     int associar = (5 * (opcao1 - 1)) + opcao2;
     switch(associar)
     {
         case 1://Cadastrar Avião
              cadastrarAviao();
              break;      
         case 2://Listar Avião
              listarAviao(NULL, 0, 0);
              break;
         case 3://Consultar Avião
              centralPesquisaAviao(0);
              break;
         case 4://Alterar Avião
              centralPesquisaAviao(2);
              break;
         case 5://Excluir Avião
              centralPesquisaAviao(1);
              break; 
              
         case 6://Cadastrar Pista
             cadastraPista();
             break;
         case 7://Listar Pista
             listarPista(NULL, 0, 0);
             break;
         case 8://Consultar Pista
              centralPesquisaPista(0);
              break;
         case 9://Alterar Pista
              centralPesquisaPista(2);
              break;
         case 10://Excluir Pista
              centralPesquisaPista(1);
              break;
              
         case 11://Cadastrar Teste
              cadastraTeste();
              break;
         case 12://Listar Teste
              listarTeste(NULL, 0 , 0);
              break;              
         case 13://Consultar Teste
              centralPesquisaTeste(0);
              break;
         case 14://Alterar Teste
              centralPesquisaTeste(2);
              break;
         case 15://Excluir Teste
              centralPesquisaTeste(1);
              break;     
         default :
             gotoxy(26,13);
             textcolor(LIGHTRED);
             printf("Opcao ainda nao implementada.");
             textcolor(WHITE);
             getch();
     }   
}
//------------------------------------------------------------------------------
//Objetivo  : Possibilita uma digitação de string limitada a uma caixa.
//Parâmetros: Coordenada X (margem), coordenada Y(altura), tamanho mínimo e máximo da linha, tamanho da string,
//            String a ser usada, e, em caso de alteração de dados, o inicio do cursor.
//Retorno   : 0 - se a escrita foi cancelada.
int escrevaLimitado(int margemReal, int margemInicial, int altura, int minimo, 
                    int tamanho, int limite, char * string, int inicio)
{
     int cont, linha = 0;
     char *backup;
     if(!(backup = (char*) calloc (strlen(string) + 1, sizeof(char))))
         return 0;
     strcpy(backup, string);
     do
     {
         cont = 0;
         gotoxy(margemInicial + 1, altura + linha);
         do
         {
               switch(inicio ? 0 : (string[cont + (linha * tamanho)] = getch()))
               {
                   case 8:
                        if(!cont)
                        {
                            if(linha) 
                            {
                                cont = tamanho - 1;
                                linha--;
                                gotoxy( margemReal + cont + 2, altura + linha);
                                printf("\x8 \x8");
                            }
                        }
                        else
                        {
                            printf("\x8 \x8");
                            cont--;
                        }
                        break;
                   case 13: case 9:
                        if(cont + (linha * tamanho) >= minimo)
                        {
                            string[cont + (linha * tamanho)] = '\0';
                            free(backup);
                            return 1;
                        }
                        break;
                   case 27:
                         strcpy(string, backup);
                         free(backup);
                         return 0;
                   default:
                         if((cont + (linha * tamanho)) < limite)
                         {
                            if(inicio)
                            {
                                 inicio--;
                                 cont++;
                            }
                            else
                            {
                                if(string[cont + (linha * tamanho)] == 32)
                                {
                                    if(cont + (linha * tamanho))
                                    {                                                                
                                        putc(string[cont + (linha * tamanho)], stdout);
                                        cont++;
                                    }
                                }
                                else
                                {
                                        putc(string[cont + (linha * tamanho)], stdout);
                                        cont++;
                                }
                                margemInicial = margemReal;
                            }
                         }
                         break;
               }
         }while(cont < tamanho);
            linha++;
     }while(1);
}
//Objetivo  :  Apresentar os dados de aviões, móveis ou teste já cadastrados.
//Parâmetros:  Ponteiro da struct de aviões, móveis ou teste e mensagem
//               a ser exibida.
//Retorno   :  Nenhum.
void apresentaInfo(Aviao *dadoAviao, Pista *dadoPista, Teste *dadoTeste, char *msg)
{
// Instruções
     limpaArea(2, 5, 78, 20);
     textbackground(BLACK);
     textcolor(LIGHTGRAY);
     fazBorda(76, 15, 2, 6, 1);
     imprimeMsg("----------------------------------------------------------------------------", 3, 8, WHITE, BLACK);
     if(dadoAviao)
     {
         imprimeMsg(msg, 22, 7, YELLOW, BLACK);         
         imprimeMsg("Modelo: ", 3, 9, WHITE, BLACK);
         imprimeMsg(dadoAviao->modelo, 11, 9, YELLOW, BLACK);  //TAM+3  = X _
         imprimeMsg("Capacidade: ", 3, 10, WHITE, BLACK);
         textcolor(YELLOW);
		 printf("%d",dadoAviao->capacidade);
   		 imprimeMsg("Codigo (ID): ", 3, 11, WHITE, BLACK);
         imprimeMsg(dadoAviao->codigoAviao, 16, 11, YELLOW, BLACK);
		 imprimeMsg("Cliente: " , 3, 12, WHITE, BLACK);
         imprimeMsg(dadoAviao->cliente.nome, 12, 12, YELLOW, BLACK);  //Obs: imprimeMsg so apresenta String.
         imprimeMsg("Pais: ", 3, 13, WHITE, BLACK);
         imprimeMsg(dadoAviao->cliente.pais, 9, 13, YELLOW, BLACK);
     }
     else if(dadoPista)
     {
         imprimeMsg(msg, 22, 7, YELLOW, BLACK);
         imprimeMsg("Endereco: ", 3, 9, WHITE, BLACK);
         imprimeMsg(dadoPista->endereco, 13, 9, YELLOW, BLACK);
  		 imprimeMsg("Codigo Pista: ", 3, 10, WHITE, BLACK);
         textcolor(YELLOW);
		 printf("%d", dadoPista->codigoPista);
         imprimeMsg("Codigo Aviao: ", 3, 11, WHITE, BLACK);
         imprimeMsg(dadoPista->codigoAviao, 17, 11, YELLOW, BLACK);
         imprimeMsg("UF: ", 3, 12, WHITE, BLACK);
         imprimeMsg(dadoPista->UF, 7, 12, YELLOW, BLACK);
		 imprimeMsg("Cirtuito (Km): ", 3, 13, WHITE, BLACK);
         textcolor(YELLOW);
		 printf("%6.2f",dadoPista->circuito);
		 imprimeMsg("Velodade (Km/H): ", 3, 14, WHITE, BLACK);
         textcolor(YELLOW);
		 printf("%d", dadoPista->velocidade);     
     }

     else if (dadoTeste)
     {
         imprimeMsg(msg, 22, 7, YELLOW, BLACK);
         imprimeMsg("Codigo Aviao: ", 3, 9, WHITE, BLACK);
         imprimeMsg(dadoTeste->codigoAviao, 17, 9, YELLOW, BLACK);
         imprimeMsg("Codigo Pista: ", 3, 10, WHITE, BLACK);
         textcolor(YELLOW);
         printf("%d", dadoTeste->codigoPista);
         imprimeMsg("Velocidade MAX: ", 3, 11, WHITE, BLACK);
         textcolor(YELLOW);
         printf("%d", dadoTeste->velocidadeMax);
         imprimeMsg("Data de cadastro: ", 3, 12, WHITE, BLACK);
         textcolor(YELLOW);
         printf("%02d/%02d/%04d", dadoTeste->dia, dadoTeste->mes, dadoTeste->ano);
         imprimeMsg("Hora de cadastro: ", 3, 13, WHITE, BLACK);
         textcolor(YELLOW);
         printf("%02d:%02d", dadoTeste->hora, dadoTeste->minuto);
     }
}
//------------------------------------------------------------------------------
//Objetivo  : Ler opcao de sim ou nao.
//Parâmetros: Coordenadas de escrita da opcao.
//Retorno   : 1 para sim e 0 para não.
int lerOpcao(int coluna, int linha)
{
// Declarações
    char temp[2];
    int invalido;
// Instruções
    do
    {
         if(!escrevaLimitado(coluna - 1, coluna - 1, linha, 1, 2, 1, temp, 0))
               return 0;
         temp[0] = toupper(temp[0]);
         invalido = 0;
         if((temp[0] == 'S') || (temp[0] == 'N'))
              return (temp[0] == 'S')? 1 : 0;
         else
         {
              printf("\x8 \x8");
              invalido = 1;
         }
    }while(invalido);
}
//------------------------------------------------------------------------------
//Objetivo  : Procurar ocorrência de uma string na outra ignorando diferença entre maiúsculas e minúsculas.
//Parâmetros: String e texto a ser pesquisado.
//Retorno   : 0 em caso de não encontrar e 1 caso encontre.
int strStr(char *string, char *texto)
{
// Declarações
    char *tempString, *tempTexto;
// Instruções
    if(!(tempString = (char *) calloc(strlen(string) + 1, sizeof(char))) ||
       !(tempTexto = (char *) calloc(strlen(texto) + 1, sizeof(char))))
    {
                   printf("Falta de memória!");
                   getch();
                   return 0;
    }
    strcpy(tempString, string);
    strcpy(tempTexto, texto);
    minusculo(tempString);
    minusculo(tempTexto);
    if(strstr(tempString, tempTexto))
    {
        free(tempString);
        free(tempTexto);
        return 1;
    }
    else
    {
        free(tempString);
        free(tempTexto);
        return 0;
    }
}
//------------------------------------------------------------------------------
//Objetivo  : Verificar se o número selecionado é válido.
//Parâmetros: Número máximo de registros e número do resgistro escolhido.
//Retorno   : 0 - cancelamento ou 1 - bem sucedido.
int numEscolhido(int max, int *num)
{
// Declarações
     char temp[5];
// Instruções
     do
     {
          if(!(escrevaLimitado(73, 73, 24, 1, 4, 3, temp, 0)))
          {
              textbackground(BLACK);
              //free(temp);
              return 0;
          }
          *num = atoi(temp);
          if((*num < 1) || (*num > max))
			  limpaArea(74, 24, 3 ,1);
     }while((*num < 1) || (*num > max));
     return 1;
}
