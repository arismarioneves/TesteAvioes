//================= FUN��ES MANIPULAR ARQUIVO ==================================

void arquivosNecessarios(void);
void erroArquivo (FILE *arquivo, char *msgErro);
FILE *abreArquivo (char *nome, char *tipo, char *msgErro);
int leArquivo(void *estrutura, size_t tamanho, size_t qtde, FILE *arquivo);
int escreveArquivo(void *estrutura, size_t tamanho, size_t qtde, FILE *arquivo);
void fechaArquivo (FILE *arquivo);
int removeArquivo(char *str);
int renomeiaArquivo(char *str1, char *str2);
void apresentaMsg(char *string, int coluna, int linha, int cor);

//------------------------------------------------------------------------------
//Objetivo  : Verificar a exist�ncia dos arquivos necessarios para executar o programa.
//Par�metros: Nenhum.
//Retorno   : Nenhum.
void arquivosNecessarios(void)
{
//Instru��es
     FILE *arq1, *arq2, *arq3;
     arq1=abreArquivo (ARQ_AVIAO,"ab+","Impossivel criar um dos arquivos necessarios para o programa.");
     fechaArquivo (arq1);
     arq2=abreArquivo (ARQ_PISTA,"ab+","Impossivel criar um dos arquivos necessarios para o programa.");
     fechaArquivo (arq2);
     arq3=abreArquivo (ARQ_TESTE,"ab+","Impossivel criar um dos arquivos necessarios para o programa.");
     fechaArquivo (arq3);
}
//------------------------------------------------------------------------------
//Objetivo : Informar caso ocorra um erro na abertura de um arquivo e encerrar o programa.
//Parametro: Ponteiro de arquivo e mensagem de erro.
//Retorno  : Nenhum.
void erroArquivo (FILE *arquivo, char *msgErro)
{
//Instru��es	
   if (!arquivo)
   {
       textcolor(YELLOW);
       textbackground(BLACK);
       apresentaMsg(msgErro, 7, 10, LIGHTRED);
       getch ();
       exit (1);  
   }
}
//------------------------------------------------------------------------------
//Objetivo : Abrir um arquivo.
//Parametro: Nome do arquivo e modo de abertura.
//Retorno  : Ponteiro do arquivo aberto.
FILE *abreArquivo (char *nome, char *tipo, char *msgErro)
{
//Instru��es	
   void erroArquivo (FILE *arquivo, char *msgErro);
   FILE *temp = fopen(nome,tipo);
   erroArquivo(temp, msgErro);
   return temp;
}
//------------------------------------------------------------------------------
//Objetivo  : Ler dados de um arquivo.
//Par�metros: Ponteiro da estrutura, tamanho da estrutura em bytes, quantidade de registros.
//            ponteiro do arquivo.
//Retorno   : 1 - leitura bem sucedida ou 0 - erro.
int leArquivo(void *estrutura, size_t tamanho, size_t qtde, FILE *arquivo)
{
//Instru��es
    if(fread(estrutura, tamanho, qtde, arquivo))
       return 1;
    textcolor(YELLOW);
    textbackground(BLACK);
    apresentaMsg("Erro ao ler do arquivo", 25, 11, LIGHTRED);
    getch();
    return 0;
}
//------------------------------------------------------------------------------
//Objetivo  : Escrever dados num arquivo.
//Par�metros: Ponteiro da estrutura, tamanho da estrutura em bytes, quantidade de registros.
//            ponteiro do arquivo.
//Retorno   : 1 - escrita bem sucedida ou 0 - erro.
int escreveArquivo(void *estrutura, size_t tamanho, size_t qtde, FILE *arquivo)
{
//Instru��es
    if(fwrite(estrutura, tamanho, qtde, arquivo))
        return 1;
    textcolor(YELLOW);
    textbackground(BLACK);
    apresentaMsg("Erro ao escrever do arquivo.", 21, 11, LIGHTRED);
    getch();
    return 0;
}
//------------------------------------------------------------------------------
//Objetivo : Fechar um arquivo.
//Parametro: Ponteiro de arquivo.
//Retorno  : Nenhum.
void fechaArquivo (FILE *arquivo)
{
//Instru��es
    if (fclose(arquivo))
    {
		printf ("\t\t\tErro ao tentar fechar o arquivo\n");
        printf ("\t\tO programa sera encerrado\n");
        getch ();
        exit (1);
    }
}
//------------------------------------------------------------------------------
//Objetivo  : Remover um arquivo.
//Par�metros: Nome do arquivo a ser removido.
//Retorno   : 0 - remo��o bem sucedida ou 1..n erro.
int removeArquivo(char *str)
{
//Declara��es
    int retorno = remove(str);
//Instru��es
    if(retorno){
        apresentaMsg("Erro ao remover arquivo", 25, 11, LIGHTRED);
        getch();
    }
    return retorno;
}
//------------------------------------------------------------------------------
//Objetivo  : Renomear um arquivo.
//Par�metros: Nome do arquivo a ser renomeado e novo nome.
//Retorno   : 0 - renomea��o bem sucedida ou 1..n erro.
int renomeiaArquivo(char *str1, char *str2)
{
//Declara��es
    int retorno = rename(str1, str2);
//Instru��es
    if(retorno){
        apresentaMsg("Erro ao renomear arquivo", 25, 11, LIGHTRED);
        getch();
    }
    return retorno;
}
