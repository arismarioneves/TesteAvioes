//================= ESTRUTURAS =================================================

//-------------------------------------------------------------------------------
typedef struct
{
    char nome[MAX_NOME];
    char pais[MAX_PAIS];
}Cliente;

//-------------------------------------------------------------------------------
typedef struct
{
    char modelo[MAX_NOME];
    char codigoAviao[TAM_CODIGO];
    int capacidade;
    Cliente cliente;
       
}Aviao;

//-------------------------------------------------------------------------------
typedef struct
{
    int codigoPista;
    char endereco[MAX_NOME];
    char UF[3];                 
    float circuito;    //Tamanho em KM
    int velocidade;    //Velocidade Máxima Obtida - Atualizado Automaticamente
    char codigoAviao[TAM_CODIGO];       // Mesmo código do Avião
}Pista;

//-------------------------------------------------------------------------------
typedef struct
{
	char codigoAviao[TAM_CODIGO];      // Mesmo código do Avião
    int codigoPista;                   // Mesmo código da Pista
    int dia, mes, ano, hora, minuto;
    int velocidadeMax;
    int codigoTeste;                   //Valor criado para diferenciar um teste do outro
}Teste;
//-------------------------------------------------------------------------------
