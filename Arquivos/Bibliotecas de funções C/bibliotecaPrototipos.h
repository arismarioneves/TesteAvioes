char * leStringTeclado(void);
char * leStringArquivo(FILE *arq, char terminador);
void strUpper(char * str);
int validaData(int dia, int mes, int ano);
int validaDataRestrita(int dia, int mes, int ano);
void obtemDataHoraAtual(int *dia, int * mes, int *ano, int *hora, 
                        int *minutos, int *segundos);
void tiraBrEsq(char *str);
void tiraBrDir(char *str);
void limpaJanela(int linhaInicial,int colunaInicial,int linhaFinal, 
                     int colFinal,int corFundo);
void desenhaMoldura(int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal,
          int corFundoAtual, int corLetraAtual);
int menuVertical(int n,char *imenu[],int c1,int c2,int linha,int coluna,int ini,
                int moldura,int corFundoAtual, int corLetraAtua);
void      retornaCor(int corFundo,int corTexto); 
int validaCPF (char *cpf);     
char * formataCPF (char *cpf);
int obtemDiaSemana(int dia, int mes, int ano); 
char * novaFgets(char *texto, int tamanho);
int validaISBN( char * isbn);  
int adicionaDiasData(int *dia, int *mes, int *ano,int qtdeDias);
char * strIstr(char *str1, char *str2);  
int validaCNPJ (char *cnpj);    
char * excluiRegArq(char *nomeArq, int tamReg, int regExcluir,int *existeErro); 
int strIncmp(char *str1, char *str2,int tam);
void leInt(int *nroInt, char *titulo, int linha, int coluna);
void leFloat(float *nroFloat, char *titulo, int linha, int coluna);
int validaTituloEleitoral (char *tituloEleitor,char *estadoEmissor);
