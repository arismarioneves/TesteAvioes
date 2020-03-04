//================= FUNÇÕES AUX ================================================

void fazBorda (int comp, int larg, int coluna, int linha, int limpar);
void limpaArea(int coluna, int linha, int base, int altura);
void apresentaMsg(char *string, int coluna, int linha, int cor);
void imprimeMsg (const char *msg, int coluna, int linha, int corCaracter, int corFundo);
void mostraMsgErro (char *msgErro, int coluna, int linha, int base, int altura);
void minusculo(char *string);
void maiusculo(char *string);
void trocarTerminador(char *string);

//------------------------------------------------------------------------------
//Objetivo  : Cria uma borda de linha dupla.
//Parâmetros: Comprimento e largura do conteúdo e coordenadas do inicio.
//Retorno   : Nenhum.
void fazBorda (int comp, int larg, int coluna, int linha, int limpar)
{
     int aux,aux2;
     gotoxy(coluna,linha);
     printf("\xC9");
     for(aux = 1;aux <= comp;aux++)
             printf("\xCD");
     printf("\xBB");
     linha++;
     for(aux2= 1;aux2<= larg;aux2++)
     {
             gotoxy(coluna,linha);
             printf("\xBA");
             if(limpar)
                for(aux = 0; aux < comp; aux++)
                   printf(" ");
             else
                gotoxy(coluna + comp + 1, linha);
             printf("\xBA");
             linha++;
     }
     gotoxy(coluna,linha);
     printf("\xC8");
     for(aux = 1;aux <= comp;aux++)
        printf("\xCD");
     printf("\xBC");
     gotoxy(1,1);
}
//------------------------------------------------------------------------------
//Objetivo  : Limpar uma área definida da tela.
//Parâmetros: Coordenadas de início, largura e comprimento da base.
//Retorno   : Nenhum.
void limpaArea(int coluna, int linha, int base, int altura)
{
     register int aux, cont;
     for(aux = 0; aux < altura; aux++)
         for(cont = 0; cont < base; cont++)
         {
              gotoxy(coluna + cont, linha + aux);
              printf(" ");
         }
}
//------------------------------------------------------------------------------
//Objetivo  : Apresentar um texto dentro de um quadro.
//Parâmetros: String, linha, coluna, cor do texto.
//Retorno   :  Nenhum.
void apresentaMsg(char *string, int coluna, int linha, int cor)
{
     fazBorda(strlen(string) + 6, 3, coluna, linha, 1);
     imprimeMsg(string, coluna + 4, linha + 2, cor, BLACK);
}
//------------------------------------------------------------------------------
//Objetivo:     Apresentar um texto formatado em cores definidas
//              e em posição específica.
//Parâmetros:   String, linha e coluna, cor do texto e cor
//              do fundo.
//Retorno:      Nenhum.
void imprimeMsg (const char *msg, int coluna, int linha, int corCaracter, int corFundo)
{
    gotoxy(coluna, linha);
    textcolor(corCaracter);
    textbackground(corFundo);
    printf(msg);
}
//------------------------------------------------------------------------------
//Objetivo  : Apresentar uma mensagem de erro.
//Parâmetros: String, abscissa, ordenada, base e altura da area da apresentação.
//Retorno   : Nenhum.
void mostraMsgErro (char *msgErro, int coluna, int linha, int base, int altura)
{
    imprimeMsg(msgErro, 48, 25, LIGHTRED, BLACK);
    limpaArea(coluna, linha, base, altura);
    textcolor(YELLOW);
}
//------------------------------------------------------------------------------
//Objetivo  : Passar os caracteres de uma string para minusculo.
//Parâmetros: Endereço da string.
//Retorno   : Nenhum.
void minusculo(char *string)
{
     int aux;
     for (aux = 0; string[aux]; aux++)
           string[aux] = tolower(string[aux]);
}
//------------------------------------------------------------------------------
//Objetivo  : Passar os caracteres de uma string para maiusculo.
//Parâmetros: Endereço da string.
//Retorno   : Nenhum.
void maiusculo(char *string)
{
     int aux;
     for (aux = 0; string[aux]; aux++)
           string[aux] = toupper(string[aux]);
}
//------------------------------------------------------------------------------
//Objetivo : Trocar \n da string por \0.
//Parâmetro: Endereço inicial da string.
//Retorno  : Nenhum.
void trocarTerminador(char *string) 
{
    if(*(string+strlen(string)-1)=='\n');
        *(string+strlen(string)-1)='\0';
}
