#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "bibliotecaPrototipos.h" 
#define ENTER      13
#define BACK_SPACE 8
#define CARACTER_EOL   0x0A
   
/**********************************************************************************************
 Função     : strUpper
 Objetivo   : Converte uma string para maiuscula
 Parâmetros : str - endereço de memória da string a ser convertida para maiuscul
 Retorno   :  void
***********************************************************************************************/
void strUpper(char * str)
{
int i;
  for (i=0;i<strlen(str);i++)
  {
      str[i] = (char) toupper(str[i]);
  }        
}        

/**********************************************************************************************
 Função     : leStringTeclado
 Objetivo   : lê uma string do teclado
 Parâmetros : nenhum
 Retorno   :  endereço de memória onde está a string lida
***********************************************************************************************/
char * leStringTeclado(void)
{
char *texto=NULL, *textoAux=NULL, carac;    
int nroCarac=0,qtdeAlocada=0;

// tipos de teclas tratadas


// tamanho do bloco de memória a alocar
#ifndef TAM_BLOCO
#define  TAM_BLOCO  100
#endif

   do
   {
       carac = (char) getch(); // nao mostra caractere por causa dos caracteres especiais
       
       if(carac != ENTER)
       {
         if(carac > 0) // verifica se nao e caractere de controle (teclas especiais)
                       // del, setas de controle (esquerda, direita, baixo, cima)
         {
           // tratamento do back_space
           if(carac == BACK_SPACE)
           {
               if(nroCarac == 0)
                  printf(" ");
               else
               {   
                  printf("%c%c%c",BACK_SPACE,' ',BACK_SPACE);// retira o caractere e posiciona o
                                                          // cursor um caractere para trás
                  nroCarac--;
               }       
           }
           else
           {
             // verifica se existe necessidade de alocar memória  
             if(nroCarac == qtdeAlocada)
             {  
               // realocação da memória  
               textoAux = (char *)realloc(texto,(qtdeAlocada + TAM_BLOCO +1)*sizeof(char));
               if(textoAux != NULL)
               {
                 // atualização da qtdeAlocada e o ponteiro de texto  
                 qtdeAlocada += TAM_BLOCO;  
                 texto = textoAux;
               }      
               else
               {
                   printf(" Erro na realocacao de memoria na leitura do texto do teclado \n");
                   getch();
                   break;
               }        
             }      
             // guarda o caractere e apresenta na tela
             texto[nroCarac] = carac;
             nroCarac++;
             printf("%c",carac);//mostra caractere lido            
           }        
         }
         else
         {
             // le o segundo caractere de controle das teclas especiais desprezando-o
             getch();
         }   
       } 
       else
       {
          printf("\n"); // apos o enter muda de linha
       }                      
   }while(carac != ENTER);
   // verifica se não houve erro de alocação de memória
   if(textoAux == NULL)
   {
       // libera memória que estiver sido alocada anteriormente
       if(texto != NULL)
         free(texto);
       texto = NULL;
   }            
   else
   {
       // coloca o terminador de string
       texto[nroCarac] = '\0';
       // realoca o espaco necessario eliminando os excessos
       textoAux = (char *)realloc(texto,(strlen(texto)+1)*sizeof(char));
       if(textoAux != NULL)
       {
           texto = textoAux;
       }
       else
       {
           printf(" Erro na realocacao final de memoria na leitura do texto do teclado \n");
           getch();
           // libera memória que estiver sido alocada anteriormente
           if(texto != NULL)
              free(texto);
           texto = NULL ;  
       }          
   }
   // retorna o endereço de memória onde está o texto lido    
   return texto;
}


/**********************************************************************************************
 Função     : leStringArquivo
 Objetivo   : lê uma string de um arquivo
 Parâmetros : arq        - endereço de memória onde se encontra a estrutura FILE 
                           do arquivo a ser lido
              terminador - terminador da string gravada no arquivo que não será colocada na string
 Retorno   :  endereço de memória onde está a string lida do arquivo
***********************************************************************************************/

char * leStringArquivo(FILE *arq, char terminador)
{
char *texto=NULL, *textoAux=NULL, carac;    
int nroCarac=0,qtdeAlocada=0;
#ifndef TAM_BLOCO
#define  TAM_BLOCO  100
#endif
   while(!feof(arq))
   {
       carac = fgetc(arq);

       if(carac == ENTER)
          continue;
//       printf(" caractere lido (%c - %d)\n",carac,carac);
//       getch();
       // verifica se foi lido o terminador da string
       if(carac == terminador || carac == CARACTER_EOL)
          break;
                    
       if(!feof(arq))
       {
         // verifica se existe necessidade de alocar memória  
         if(nroCarac == qtdeAlocada)
         {  
            // realocação da memória  
            textoAux = (char *)realloc(texto,(qtdeAlocada+TAM_BLOCO+1)*sizeof(char));
            if(textoAux != NULL)
            {
             // atualização da qtdeAlocada e o ponteiro de texto  
             qtdeAlocada += TAM_BLOCO;
             texto = textoAux;
            }
            else
            {
                printf(" Erro de realocacao de memoria na leitura do texto do arquivo \n");
                getch();
                break;
            }         
          }      
          // guarda o caractere lido
          texto[nroCarac] = carac;
          nroCarac++;
       }                       
   }
   // verifica se não houve erro de alocação de memória
   if(textoAux == NULL)
   {
       // libera memória que estiver sido alocada anteriormente
       if(texto != NULL)
         free(texto);
       texto = NULL;
   }            
   else
   {
       // coloca o  terminador de string
       texto[nroCarac] = '\0';
       // realoca o espaco necessario eliminando os excessos
       textoAux = (char *)realloc(texto,(strlen(texto)+1)*sizeof(char));
       if(textoAux != NULL)
       {
           texto = textoAux;
       }
       else
       {
           printf(" Erro na realocacao final de memoria na leitura do texto do arquivo \n");
           getch();
           // libera memória que estiver sido alocada anteriormente
           if(texto != NULL)
              free(texto);
           texto = NULL ;  
       }          
   }    
   // retorna o endereço de memória onde está o texto lido    
   return texto;
}
/***********************************************************
*  Nome      : validaData                                  *  
*  Descricao : Efetua a validação de uma data a partir das *
*             informações do dia mes e ano (com seculo)    *
*  Parâmetros:                                             *
*             dia, mes e ano                               *
*  Retorno   :                                             * 
*            1 - data valida                               * 
*            0 - data invalida                             *
************************************************************/ 
int validaData(int dia, int mes, int ano)
{
int retorno=1;    
    if(ano<0 || mes<1 || mes >12 || dia >31)
       return 0;          
    switch(mes)
    {
       case 4:
       case 6:
       case 9:
       case 11:
            if(dia > 30)
               retorno =0;
            break;
       case 2:
            printf(" %d\n",(ano%4 == 0 && ano %100 !=0) ||(ano % 400 == 0));
            if((ano%4 == 0 && ano %100 !=0) ||(ano % 400 == 0))
            {
               if(dia >29)
                  retorno = 0;
            }      
            else
            {
               if(dia >28)
                  retorno =0;                                      
            }
            break;      
    }      
    return retorno;
}

/***********************************************************
*  Nome      : validaDataRestrita                          *  
*  Descricao : Efetua a validação de uma data a partir das *
*             informações do dia mes e ano (com seculo)    *
*             na faixa de 01/01/1970 até 31/12/2037        * 
*  Parâmetros:                                             *
*             dia, mes e ano                               *
*  Retorno   :                                             * 
*            1 - data valida                               * 
*            0 - data invalida                             *
************************************************************/ 
int validaDataRestrita(int dia, int mes, int ano)
{
struct tm time_check;

#ifdef XX
// campos da estrutura tm 
struct tm {
  int tm_sec;   /* Seconds */
  int tm_min;   /* Minutes */
  int tm_hour;  /* Hour (0--23) */
  int tm_mday;  /* Day of month (1--31) */
  int tm_mon;   /* Month (0--11) */
  int tm_year;  /* Year (calendar year minus 1900) */
  int tm_wday;  /* Weekday (0--6; Sunday = 0) */
  int tm_yday;  /* Day of year (0--365) */
  int tm_isdst; /* 0 if daylight savings time is not in effect) */
};    
#endif
    
    if(ano < 1970 || ano >2037)
       return 0;
       
    /* carrega a data para a estrutura time_check do tipo tm */
    time_check.tm_year = ano - 1900;
    time_check.tm_mon  = mes - 1;
    time_check.tm_mday = dia;
    time_check.tm_hour = 0;
    time_check.tm_min  = 0;
    time_check.tm_sec  = 1;
    time_check.tm_isdst = -1;

    /*  chama  mktime para criar uma data validando-a */
    if (mktime(&time_check) == -1)
    {
       return 0; // data invalida
    }
    // verifica se data criada é igual a data de entrada 
    else if ((time_check.tm_year != ano - 1900) ||
             (time_check.tm_mon  != mes - 1) ||
             (time_check.tm_mday != dia))
    {
         return 0; // data invalida
    }
    else        
    {
       return 1; // data valida
    }  
}

/***********************************************************
*  Nome      : obtemDataHoraAtual                          *  
*  Descricao : Obtem a data e hora atual do sistema        *
*  Parâmetros:                                             *
*             dia, mes,ano, hora, minutos, segundos        *
*  Retorno   : Nenhum                                      * 
************************************************************/ 
void obtemDataHoraAtual(int *dia, int * mes, int *ano, int *hora, 
                        int *minutos, int *segundos)
{
   time_t t;
   struct tm *dataAtual;
   t = time(NULL);
   dataAtual = localtime(&t);
   
   *dia      = dataAtual->tm_mday;
   *mes      = dataAtual->tm_mon+1;
   *ano      = 1900+dataAtual->tm_year;
   *hora     = dataAtual->tm_hour;
   *minutos  = dataAtual->tm_min;
   *segundos = dataAtual->tm_sec;
}
/**************************************************************
*  Nome      : tiraBrEsq                                      *  
*  Descricao : Tira todos os brancos a esquerda de uma string *
*  Parâmetros:                                                *
*             string                                          *
*  Retorno   : Nenhum                                         * 
**************************************************************/ 
void tiraBrEsq(char *str)
{
char *pStr;    
   pStr = str;
   while(*pStr == ' ' && *pStr != '\0')
      pStr++;
   strcpy(str,pStr);   
}    

/**************************************************************
*  Nome      : tiraBrDir                                      *  
*  Descricao : Tira todos os brancos a direita  de uma string *
*  Parâmetros:                                                *
*             string                                          *
*  Retorno   : Nenhum                                         * 
**************************************************************/ 
void tiraBrDir(char *str)
{
char *pStr; 
   if(*str == '\0')
      return;   
   pStr = str+strlen(str)-1;
   while(*pStr == ' ')
      pStr--;
   *(pStr+1) = '\0';
}

/**************************************************************
*  Nome      : menuVertical                                   *  
*  Descricao : Apresenta um menu vertical e retorna a opcao   *
*              selecionada                                    * 
*  Parâmetros: n - Numero de itens                            *
*              imenu - Descrição dos itens                    *
*              c1 - cor do texto do menu                      *
*              c2 - cor da marca do item selecionado          *
*              linha - linha inicial para instalação do menu  *
*              coluna - coluna inicial para instalação do menu*
*              ini - número da opção inicial do menu a ser    *
*                        selecionada                          *
*              moldura - indicador se deve desenhar o menu    *
*                 dentro de uma moldura                       *
*              corFundoAtual - cor do fundo a ser restituida a*
*                 tela com a retirada do menu                 *      
*              corLetra - cor da letra a ser restituida a     *
*                 tela com a retirada do menu                 *      
*  Retorno   : número do item do menu selecionado             * 
**************************************************************/ 
int menuVertical(int n,char *imenu[],int c1,int c2,int linha,int coluna,int ini,
                int moldura,int corFundoAtual, int corLetraAtual)
{
		int tecla;	// Recebe a tecla pressionada
		int sel_b;	// Selecao de backup do menu
		int sel;
		int i;  		
		int val;		// 1 = tecla valida encontrada
						// 0 = tecla valida nao encontrada
        int tamMaiorTexto;
         

        // verifica se desenha com moldura e menu comeca na linha 1
        if(linha ==1 && moldura)
           linha++;
        // verifica se desenha com moldura e menu comeca na coluna 1
        if(coluna== 1 && moldura)
           coluna++;
            
		textcolor(c1);	// Atributo da cor das letras
		if(ini < 1)
		    ini=1;
		else if(ini>n)
           ini=n;
               
		sel=ini-1; 	// Primeiro item selecionado
		for (i=0;i<=n-1;i++)
			{
			    
				if (i==ini-1) textbackground(c2); // Escreve itens do menu
				else textbackground(corFundoAtual);           // e seleciona o item inicial
				gotoxy(coluna,linha+i);                    // setado no argumento passado
				printf(imenu[i]);
				if(i==0)
				  tamMaiorTexto = strlen(imenu[i]);
				else if(strlen(imenu[i]) > tamMaiorTexto)
				  tamMaiorTexto = strlen(imenu[i]);
                
			}
			// desenha a moldura
			if(moldura)
			{
			    desenhaMoldura(linha-1,coluna-1,linha+n,coluna+tamMaiorTexto+2,
                     corFundoAtual, corLetraAtual);
			}    
		do
			{
				do
					{
//						do
//							{
//							} while (!kbhit());

						tecla=toupper(getch()); 

						// Verificar pelas teclas validas pressionadas
						if (tecla==72||tecla==75||tecla==65) val=1;
						else 	if (tecla==77||tecla==80||tecla==90) val=1;
								else 	if (tecla==27||tecla==13) val=1;
										else val=0;

					} while (!val);
				sel_b=sel; // Backup do item atual antes de modifica-lo
				if (tecla==72||tecla==75||tecla==65) sel--; // Sobe
				if (tecla==80||tecla==77||tecla==90) sel++; // Desce
				if (tecla==27) sel_b=-1; 		  // Sai com ESC
				if (sel<=-1) sel=n-1; // Se for menor vai para o ultmo item
				if (sel>=n) sel=0; // Se for maior vai para o primeiro item
				textcolor(c1);
				if (tecla!=13&&tecla!=27)
					{
						// Desseleciona o antigo item do menu...
						gotoxy(coluna,sel_b+linha); textbackground(corFundoAtual); printf(imenu[sel_b]);
						// Seleciona o novo item do menu...
						gotoxy(coluna,sel+linha); textbackground(c2); printf(imenu[sel]);
						// Descarrega o buffer do teclado...
						fflush(stdin);
					}
					
			} while (tecla!=13&&tecla!=27);

   
        if(moldura)
           	limpaJanela(linha-2,coluna-1,linha+n,coluna+tamMaiorTexto+2,corFundoAtual);
        else
           	limpaJanela(linha,coluna,linha+n,coluna+tamMaiorTexto,corFundoAtual);
   
		return(sel_b+1); 	// Retorna item selecionado + 1 (nao retorna 0)
}
/**************************************************************
*  Nome      : desenhaMoldura                                 *  
*  Descricao : Desenha uma moldura na tela                    *
*  Parâmetros: linhaInicial - linha inicial da moldura        *
*              colunaInicial - coluna inicial da moldura      *
*              linhaFinal   - linha final da moldura          *
*              colunaFinal - coluna final da moldura          *
*              corFundoAtual - cor do fundo atual             *
*              corLetra  - cor do fundo atual                 *
*  Retorno   : nenhum                                         * 
**************************************************************/ 

void desenhaMoldura(int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal,
          int corFundoAtual, int corLetraAtual)
{
    int i=0,qtdeLinhas,qtdeColunas;
    
    qtdeLinhas  = linhaFinal - linhaInicial ;
    qtdeColunas = colunaFinal - colunaInicial ;
    textbackground(7);
    textcolor(8);
    // faz a borda superior
    gotoxy(colunaInicial,linhaInicial);
    for(i=0;i<=qtdeColunas;i++)
    {
        printf("\xCD");
    }

    // faz a borda inferior
    gotoxy(colunaInicial,linhaInicial+qtdeLinhas);
    for(i=0;i<=qtdeColunas;i++)
    {
        printf("\xCD");
    }

    // faz a lateral esquerda    
    for(i=0;i<=qtdeLinhas;i++)
    {
        gotoxy(colunaInicial,linhaInicial+i);
        printf("\xBA");
    }
    // faz a lateral direita
    for(i=0;i<=qtdeLinhas;i++)
    {
        gotoxy(colunaInicial+qtdeColunas,linhaInicial+i);
        printf("\xBA");
    }

    // fecha os cantos da moldura
    gotoxy(colunaInicial,linhaInicial);
    printf("\xC9");
    gotoxy(colunaInicial+qtdeColunas,linhaInicial);
    printf("\xBB");
    gotoxy(colunaInicial,linhaInicial+qtdeLinhas);
    printf("\xC8");
    gotoxy(colunaInicial+qtdeColunas,linhaInicial+qtdeLinhas);
    printf("\xBC");
    retornaCor(corFundoAtual, corLetraAtual);
}

/**************************************************************
*  Nome      : limpaJanela                                    *  
*  Descricao : limpa uma janela da tela                       *
*  Parâmetros: linhaInicial - linha inicial da janela         *
*              colunaInicial - coluna inicial da janela       *
*              linhaFinal   - linha final da janela           *
*              colunaFinal - coluna final da janela           *
*              corFundo - cor do fundo da janela a ser limpa  *
*  Retorno   : nenhum                                         * 
**************************************************************/ 
void limpaJanela(int linhaInicial,int colunaInicial,int linhaFinal, 
                     int colFinal,int corFundo)
{
int coluna=0,linha=0;

    for(coluna=colFinal;coluna>=colunaInicial;coluna--)
    {
        for(linha=linhaFinal;linha>=linhaInicial;linha--)        
        {
            textbackground(corFundo);
            gotoxy(coluna,linha);
            printf(" ");

        }
    }


}
/**************************************************************
*  Nome      : retornaCor                                     *  
*  Descricao : retorna a cor de fundo e de texto              *
*  Parâmetros: corFundo - cor de fundo                        *
*              corTexto - cor do texto                        *
*  Retorno   : nenhum                                         * 
**************************************************************/ 
void      retornaCor(int corFundo,int corTexto)
{
    textbackground(corFundo);
    textcolor(corTexto);
}    

/**************************************************************
*  Nome      : validaCPF                                      *  
*  Descricao : Valida um CPF                                  *
*  Parâmetros: endereço inicial da string cpf                 *
*  Retorno   : 1 - cpf válido, 0 - cpf inválido               * 
**************************************************************/ 
int validaCPF (char *cpf)
	{
       // cpfs inválidos        
       char *cpfInval[] = {"11111111111",
                         "22222222222",
                         "33333333333",
                         "44444444444",
                         "55555555555",
                         "66666666666",
                         "77777777777",
                         "88888888888",
                         "99999999999"}; 
		
		int cont,retorno =1,aux2,dig[11],soma=0,digVeri[2];
		
		if(strlen(cpf) != 11)
		   return 0;
		 
         // verifica se cpf so contem nros iguais  
	     for(cont=0;cont<9;cont++)
         {
               if(strcmp(cpfInval[cont],cpf)==0)
               {
                  retorno =0;
                  break;
               }
         } 
         
         if(retorno ==0)
            return retorno;
          
         // transforma os caracteres do cpf em números     
         for(cont=0;cont<strlen(cpf);cont++)
         {
                dig[cont] = cpf[cont] - '0';
         }
         
         // obtem o primeiro digito verificador
         aux2=10;
         for(cont=0;cont<9;cont++,aux2--)
         {
            soma+= dig[cont] * aux2;
         }
         digVeri[0]=soma % 11;
         digVeri[0]= digVeri[0]<2 ? 0 : 11-digVeri[0];
         
         // obtem o segundo digito verificador
         soma=0;
         aux2=11;
         for(cont=0;cont<10;cont++,aux2--)
         {
               if(cont==9)
                  soma+= digVeri[0] * aux2;
               else
                  soma+= dig[cont] * aux2;
         }
         digVeri[1]=soma % 11;
         digVeri[1]= digVeri[1]<2 ? 0 : 11-digVeri[1];
         if(digVeri[0]!=dig[9] || digVeri[1]!=dig[10])
         {
               retorno =0;               
         }
         return retorno;
}
/**************************************************************
*  Nome      : formataCPF                                     *  
*  Descricao : Formata um CPF                                 *
*  Parâmetros: endereço inicial da string cpf                 *
*  Retorno   : endereço de memória onde comeca a string       * 
*               com CPF formatado ou NULL                     *
**************************************************************/ 
char * formataCPF (char *cpf)
{
static char cpfFormatado[15];
   if(validaCPF(cpf) == 0)
      return NULL;
   else
   {
        sprintf(cpfFormatado,"%3.3s.%3.3s.%3.3s-%2.2s",
            cpf,cpf+3,cpf+6,cpf+9);
        return cpfFormatado;    
   }   
    
}

/***********************************************************
*  Nome      : obtemDiaSemana                              *  
*  Descricao : Obtem o dia da semana de uma data           *
*             informações do dia mes e ano (com seculo)    *
*             na faixa de 01/01/1970 até 31/12/2037        * 
*  Parâmetros:                                             *
*             dia, mes e ano                               *
*  Retorno   :                                             * 
*             0.. 6 - domingo, segunda...... sabado        * 
*            -1 - data invalida                             *
************************************************************/ 
int obtemDiaSemana(int dia, int mes, int ano)
{
struct tm time_check;
    if(ano < 1970 || ano >2037)
       return -1;
       
    /* carrega a data para a estrutura time_check do tipo tm */
    time_check.tm_year = ano - 1900;
    time_check.tm_mon  = mes - 1;
    time_check.tm_mday = dia;
    time_check.tm_hour = 0;
    time_check.tm_min  = 0;
    time_check.tm_sec  = 1;
    time_check.tm_isdst = -1;

    /*  chama  mktime para criar uma data validando-a */
    if (mktime(&time_check) == -1)
    {
       return -1; // data invalida
    }
    // verifica se data criada é igual a data de entrada 
    else if ((time_check.tm_year != ano - 1900) ||
             (time_check.tm_mon  != mes - 1) ||
             (time_check.tm_mday != dia))
    {
         return -1; // data invalida
    }
    else        
    {
       return time_check.tm_wday; // dia da semana
    }  
}
/***********************************************************
*  Nome      : valida ISBN                                 *  
*  Descricao : Valida se um ISBN é válido ou não           *
*  Parâmetros:                                             *
*             ISBN                                         *
*  Retorno   : 1 - valido ou 0 - invalido                  * 
************************************************************/ 
int validaISBN( char * isbn)
{
int retorno = 1,somaValores,mult,digitoVerificador,digitoCalculado,i,j=0;
char *isbnAux;

   //aloca memória
   if((isbnAux = (char *) malloc(sizeof(char) * (strlen(isbn)+1))) == NULL)
       return 0;
       
   // tira - do isbn   
   for(i=0;i<strlen(isbn);i++)
   {
      if(isbn[i] != '-')
      {
         isbnAux[j] = isbn[i];        
         j++;
      }                         
   }   
   isbnAux[j] = '\0';
   tiraBrEsq(isbnAux);
   tiraBrDir(isbnAux); 
   // verifica tamanho do isbn
   if(strlen(isbnAux)!= 13 && strlen(isbnAux)!= 10)
   {            
      retorno = 0;
   }   
   else
   {
       
       // verifica se no ISBN só tem digitos a menos do digito verificador
       // que poderá ser X (equivale a 10)
       for(i=0;i<strlen(isbnAux)-1;i++)
       {
          if(!isdigit(isbnAux[i]))  
          {
             retorno =0;        
             break;                   
          }             
       }                 
       if(retorno)
       {          
           // verifica digito verificado
           if(!isdigit(isbnAux[strlen(isbnAux)-1])&& toupper(isbnAux[strlen(isbnAux)-1]) != 'X')          
           {
                 retorno =0;                
           }
           
           if(retorno)
           {
               if(toupper(isbnAux[strlen(isbnAux)-1])!= 'X')
                  digitoVerificador = isbnAux[strlen(isbnAux)-1]- '0';
               else
               {
                  // no ISBN 13 ==> digito = X corresponde a 0
                  // no ISBN 10 ==> digito = X corresponde 1                      
                  digitoVerificador = strlen(isbnAux) == 10 ? 0:1;   
               }   
             
               // calcula o digito verificador
               // ISBN com 10 digitos
               if(strlen(isbnAux) == 10)
               {
                    somaValores =0;
                    mult=10;
                    for(i=0;i<strlen(isbnAux)-1;i++)
                    {
                         somaValores +=((*(isbn+i)) - '0')*mult;
                         mult--;
                    }
                    digitoCalculado = somaValores % 11 != 0 ? (11- somaValores % 11): 0;
               }
               else
               {  
                   // ISBN de 13 digitos                 
                   somaValores =0;
                   mult = 1;
                   for(i=0;i<strlen(isbnAux)-1;i++)
                   {
                     somaValores += mult * (isbnAux[i] - '0');
                     mult = mult == 1? 3:1;               
                   }
                   
                   digitoCalculado = somaValores % 10 != 0 ? (10- somaValores % 10): 0;
               }    
               printf(" Digito verficados %d calculado %d\n",digitoVerificador, digitoCalculado);
                   
               if(digitoVerificador != digitoCalculado)
               {                              
                       retorno =0;                 
               
               }    
            }     
       }     
   }    
   free(isbnAux);
   return retorno;
   
}
/***********************************************************
*  Nome      : novaFgets                                   *  
*  Descricao : Le uma string usando a fgets e tira o \n    *
*  Parâmetros: endereço da string                          *
*              tamanho máximo                              * 
*  Retorno   :  NULL ou endereço da string                 * 
************************************************************/ 
char * novaFgets(char *texto, int tamanho)
{
char *retorno;
   // limpa o buffer de teclado 
   fflush(stdin);      
   if((retorno = fgets(texto,tamanho,stdin)) != NULL)
   {
        if(texto[strlen(texto)-1] == '\n')
          texto[strlen(texto)-1] = '\0';                             
   }
   // limpa o buffer de teclado para eliminar caracteres que foram fornecidos além do tamnho especificado
   fflush(stdin);      
   
   return retorno;  
}
/***********************************************************
*  Nome      : adicionaDiasData                            *  
*  Descricao : Adiciona uma quantidade de dias a uma data  *
*  Parâmetros:                                             *
*             dia, mes, ano e qtde de dias                 *
*  Retorno   :                                             * 
*            1 - ok                                        * 
*            0 - erro                                      *
************************************************************/ 
int adicionaDiasData(int *dia, int *mes, int *ano,int qtdeDias)
{
struct tm time_check;

    
    if(*ano < 1970 || *ano >2037)
       return 0;
       
    /* carrega a data para a estrutura time_check do tipo tm */
    time_check.tm_year = *ano - 1900;
    time_check.tm_mon  = *mes - 1;
    time_check.tm_mday = *dia+qtdeDias;
    time_check.tm_hour = 0;
    time_check.tm_min  = 0;
    time_check.tm_sec  = 1;
    time_check.tm_isdst = -1;

    /*  chama  mktime para criar uma data validando-a */
    if (mktime(&time_check) == -1)
    {
       return 0; // data invalida
    }
    // verifica se data criada é igual a data de entrada 
    else 
    {
       *ano = time_check.tm_year +1900;
       *mes = time_check.tm_mon + 1;
       *dia = time_check.tm_mday;
       return 1; // data valida
    }  
}
/***********************************************************
*  Nome      : strIstr                                     *  
*  Descricao : compara duas strings ignorando case         *
*  Parâmetros:                                             *
*             duas strings                                 *
*  Retorno   :                                             * 
*            endereço foi encontrada a string ou NULL      * 
************************************************************/
char * strIstr(char *str1, char *str2)
{
char*pStr1,*pStr2;
char *retorno=NULL;
   pStr1 = (char*) malloc(sizeof(char) * (strlen(str1)+1));
   if(pStr1 != NULL)
   {
        strcpy(pStr1,str1);
        strUpper(pStr1);
        pStr2 = (char*) malloc(sizeof(char) * (strlen(str2)+1));
        if(pStr2 != NULL)
        {
           strcpy(pStr2,str2);
           strUpper(pStr2);
           retorno = strstr(pStr1,pStr2);
           free(pStr1);
           free(pStr2);
        }  
        else
        {
            free(pStr1);
        }     
   }  
   return retorno;  
} 

/**************************************************************
*  Nome      : validaCNPJ                                     *  
*  Descricao : Valida um CNPJ                                 *
*  Parâmetros: endereço inicial da string com o cnpj          *
*  Retorno   : 1 - cnpj válido, 0 - cnpj inválido             * 
**************************************************************/ 
int validaCNPJ (char *cnpj)
{
int j,Soma=0,i,existeErro=0;
char digito[2];
char mult[13]={"543298765432"};
int Digito = 0;
 
	if(strlen(cnpj) != 14)
		   return 0;

    // verifica se so existem números
    existeErro =0;
    for(i=0;i<strlen(cnpj);i++)
    {
         if(!isdigit(cnpj[i]))
         {
             existeErro =1;                
         }                                             
    }
    		   
    if(existeErro)
       return 0;
    
    printf(" Cnpj(%s)\n",cnpj);
    getch();
       
    for (j = 1; j < 3; j++)
    {
        Soma =0;
        for (i = 0; i < 12; i++)
        {
          Soma += (cnpj[i]-'0') * (mult[i]-'0');
        }
           
        if (j == 2)
        {
            Soma += (2 * Digito);
        }
 
        Digito = ((Soma * 10) % 11);
 
        if (Digito == 10)
        {
            Digito = 0;
        }
 
        digito[j-1] = Digito + '0';
        
        strcpy(mult,"654329876543");
    }
  
   
    return !strncmp(digito,&cnpj[12],2);
}
/****************************************************************
*  Nome      : excluiRegArq                                     *  
*  Descricao : Excluir um registro de um arquivo                *
*  Parâmetros: endereço inicial da string com o nome do arquivo *
*              tamanho de cada registro do arquivo(fixo)        *
*              número do registro a excluir                     *
*              endereço de memória onde será armazenado o erro  *   
*  Retorno   : mensagem de erro                                 * 
*****************************************************************/ 
char * excluiRegArq(char *nomeArq, int tamReg, int regExcluir,int *existeErro)
{
FILE *arq, *arqTemp;
int cont=0;
char *dados;
static char mensagem[100];

      mensagem[0] = '\0'; 
      *existeErro =0;
      if((arq = fopen(nomeArq,"rb"))== NULL)
      {
           sprintf(mensagem," Erro ao abrir arquivo  para exclusao");    
           *existeErro  = 1;
      }
      else
      {       
        if((arqTemp = fopen("arqTemp.txt","wb")) ==NULL)
        {
           fclose(arq);
           sprintf(mensagem," Erro ao criar arquivo para exclusao");    
           *existeErro  = 2; 
        }
        else
        {
          if((dados = (char*)malloc(sizeof(char)*tamReg)) == NULL)
          {
             sprintf(mensagem," Erro ao alocar memoria para exclusao");            
             *existeErro  = 3;
          }
          else
          {
              while(!feof(arq))
              {
                if(fread(dados,tamReg,1,arq)==1)
                {
                    cont++;
                    if(cont != regExcluir)
                    {
                      if(fwrite(dados,tamReg,1,arqTemp)!=1)
                      {
                         sprintf(mensagem,"Erro ao gravar dados para copia ");
                         *existeErro = 4;
                      }
                    } 
                }
                else
                {
                  if(!feof(arq))
                  {
                     sprintf(mensagem,"Erro ao ler dados para copia");
                     *existeErro = 5;
                  }   
                }  
              }
              free(dados);
          }
          if(fclose(arq) != 0)
          {
                sprintf(mensagem,"Erro ao fechar arquivo para exclusao");
                *existeErro = 6;
          }      
          if(fclose(arqTemp) != 0)
          {
                sprintf(mensagem,"Erro ao fechar arquivo temporario exclusao");
                *existeErro = 7;
          }      
        }
      }
      
      if(!*existeErro)
      {
          if(remove(nomeArq) != 0)
          {
             sprintf(mensagem,"Erro ao remover aquivo original");
             *existeErro = 8;
          }   
          else
          {   
            if(rename("arqTemp.txt",nomeArq)!=0)
            {
               sprintf(mensagem,"erro ao renomear arquivo");
               *existeErro = 9;
            }   
          }  
      } 
      return mensagem;   
} 
/***********************************************************
*  Nome      : strIncmp                                    *  
*  Descricao : compara duas strings ignorando case         *
*  Parâmetros:                                             *
*             duas strings                                 *
*  Retorno   : 0, >0 ou < 0                                * 
************************************************************/
int strIncmp(char *str1, char *str2,int tam)
{
char*pStr1,*pStr2;
int retorno=0;
   pStr1 = (char*) malloc(sizeof(char) * (tam+1));
   if(pStr1 != NULL)
   {
        strncpy(pStr1,str1,tam);
        pStr1[tam] = '\0';
        strUpper(pStr1);
        pStr2 = (char*) malloc(sizeof(char) * (tam+1));
        if(pStr2 != NULL)
        {
           strncpy(pStr2,str2,tam);
           pStr1[tam] = '\0';
           strUpper(pStr2);
           retorno = strncmp(pStr1,pStr2,tam);
           free(pStr1);
           free(pStr2);
        }  
        else
        {
            free(pStr1);
        }     
   }  
   return retorno;  
} 
/***********************************************************
*  Nome      : leInt                                       *  
*  Descricao : le um numero inteiro                        *
*  Parâmetros: endereço de memória onde será armazenado    *
*               o número inteiro                           *
*              titulo                                      * 
*              linha e coluna para o titulo                *
* Retorno    : sem retorno                                 * 
************************************************************/
void leInt(int *nroInt, char *titulo, int linha, int coluna)
{
    do
    {
       fflush(stdin);
       gotoxy(coluna,linha);
       clreol();
       gotoxy(coluna,linha);
       printf("%s",titulo); 
    }while(scanf("%d",nroInt) != 1); 
    fflush(stdin);
} 
/***********************************************************
*  Nome      : leFloat                                     *  
*  Descricao : le um numero float                          *
*  Parâmetros: endereço de memória onde será armazenado    *
*               o número float                             *
*              titulo                                      * 
*              linha e coluna para o titulo                *
* Retorno    : sem retorno                                 * 
************************************************************/
void leFloat(float *nroFloat, char *titulo, int linha, int coluna)
{
    do
    {
       fflush(stdin);
       gotoxy(coluna,linha);
       clreol();
       gotoxy(coluna,linha);
       printf("%s",titulo); 
    }while(scanf("%f",nroFloat) != 1); 
    fflush(stdin);
} 
/***************************************************************
*  Nome      : validaTituloEleitoral                           *  
*  Descricao : valida o numero de um titulo eleitoral          *
*  Parâmetros: endereço inicial da string com o titulo         *
*              endereco inicial da string onde será colocada   *
*                o estado a que se refere o titulo             *
*  Retorno   : 1 - titulo eleitoral válido, 0 - titulo inválido* 
****************************************************************/ 
int validaTituloEleitoral (char *tituloEleitor,char *estadoEmissor)
{
char * estados[] = {"SP","MG","RJ","RS","BA","PR",
                    "CE","PE","SC","GO","MA","PB",
                    "PA","ES","PI","RN","AL","MT",
                    "MS","DF","SE","AM","RO","AC",
                    "AP","RR","TO","EX"};
// onde EX se refere aos títulos do exterior
#define TAM_TITULO 12
int nTitulo[12],existeErro,soma1=0,soma2=0,dig1,dig2,i,posicao;

    // titulo deve ter no mínimo TAM_TITULO caracteres
	if(strlen(tituloEleitor) != TAM_TITULO)
		   return 0;

    // verifica se so existem números
    existeErro =0;
    for(i=0;i<strlen(tituloEleitor);i++)
    {
         if(!isdigit(tituloEleitor[i]))
         {
             existeErro =1; 
             break;               
         }         
         else
         {
           // transforma caractere em numéricos
           nTitulo[i] =tituloEleitor[i] - '0';                                     
         }  
    }
    		   
    if(existeErro)
       return 0;
       
	
	for(i=0;i<8;i++){
		soma1+=(nTitulo[i]*(i+2));
	}
	
	dig1=(soma1%11);
	soma2=((nTitulo[8]*7)+(nTitulo[9]*8)+(dig1*9));
	dig2=(soma2%11);

	if(dig1!=nTitulo[10] && dig2!=nTitulo[11]){
		return 0;
	}
   
    // determinacao do estado
    posicao = nTitulo[8]*10 + nTitulo[9]-1;
    strcpy(estadoEmissor,estados[posicao]);
      
    return 1;
}
