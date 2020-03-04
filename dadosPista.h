//================= DADOS PISTA ================================================

void cadastraPista(void);
void telaCadastroPista(int finalidade);
void contaRegistrosPista(int *);
int lerValidaCodigoAviao(char *codigo, char *temp, int posicao);
int validaCodigo(char *codigo); 

//------------------------------------------------------------------------------
//Objetivo  : Cadastrar uma nova pista.
//Parâmetros: Nenhum.
//Retorno   : Nenhum.
void cadastraPista(void)	
{
//================= PROTÓTIPOS DAS FUNÇÕES =====================================
     int encontraProxPista(int *);
   	 int lerValidaUF(char *uf, int );
   	 int lerValidaCircuito(float *, char *, int );
   	 int lerValidaVelocidade(int *, char *, int );
	 
// Declarações
     char opcao;  
     Pista novo;     
     FILE *arquivo;
     char temporario[TAM_TEXT];    
// Instruções
     do
     {
         //clrscr();      
         system("cls");
		 telaCadastroPista(0);
         textcolor(YELLOW);
         
         gotoxy(3, 11);
         if(!encontraProxPista(&novo.codigoPista))
              return;
         printf("%d", novo.codigoPista);
         
         if(!(escrevaLimitado(2, 2, 7, 1, MAX_NOME, MAX_NOME - 1, novo.endereco, 0)))
             return;
  		 if(!( selecionaAviao(novo.codigoAviao, 0)))
             return;
         if(!lerValidaUF(novo.UF, 0))
             return;
         if(!lerValidaCircuito(&novo.circuito, temporario, 0))
             return; 
         if(!lerValidaVelocidade(&novo.velocidade, temporario, 0))
             return;     

         imprimeMsg("Os dados estao corretos? (S/N) : ", 4, 23, WHITE, BLACK);
         opcao = lerOpcao(37, 23);
     }while(!opcao);
     arquivo = abreArquivo(ARQ_PISTA, "ab","Erro ao abrir o arquivo de pistas");
     escreveArquivo(&novo, sizeof(Pista), 1, arquivo);
     fechaArquivo(arquivo);
}
//------------------------------------------------------------------------------
//Objetivo  : Monta a tela para cadastro de pistas.
//Parâmetros: Finalidade alteração ou cadastro.
//Retorno   : Nenhum.
void telaCadastroPista(int finalidade)
{
     char text[TAM_TEXT];
     textcolor(LIGHTGRAY);
     fazBorda(78, 27, 1, 1, 0); //Borda tela de Cadastro
     textcolor(WHITE);
     fazBorda(30, 1, 24, 2, 0);
     imprimeMsg((finalidade)? "  ALTERACAO DE PISTA" : "   CADASTRO DE PISTA", 28, 3, WHITE, BLACK);
     fazBorda(76, 1, 2, 6, 0);
	 imprimeMsg("Endereco", 4, 6, WHITE, BLACK);
     fazBorda(15, 1, 2, 10, 0);
     sprintf(text,"C%cdigo",162);
     imprimeMsg(text, 4, 10, WHITE, BLACK);
     fazBorda(15, 5, 27, 10, 0);
     sprintf(text,"C%cdigo Avi%co",162,198);
	 imprimeMsg(text, 29, 10, WHITE, BLACK);   
	 fazBorda(9, 1, 2, 14, 0);  
     imprimeMsg("UF", 4, 14, WHITE, BLACK);
     fazBorda(10, 1, 47, 14, 0);
     imprimeMsg("Circuito", 49, 14, WHITE, BLACK);
	 fazBorda(12, 1, 64, 14, 0);
     imprimeMsg("Velocidade", 66, 14, WHITE, BLACK);
      //int comp, int larg, int coluna, int linha, int limpar
}
//Objetivo  : Descobrir qual o próximo número identificador de pista a ser gerado.
//Parâmetros: Número identificador.
//Retorno   : 0 caso ocorra erro na leitura do arquivo e 1 caso bem sucedida.
int encontraProxPista(int *num)
{
     Pista listar;
     int qnt = 0, qntPista;
     FILE *arq;
     
     contaRegistrosPista(&qntPista);
     arq = abreArquivo(ARQ_PISTA, "rb", "Erro ao abrir arquivo de pistas.");
     while(qnt < qntPista)
     {
        if(leArquivo(&listar, sizeof(Pista), 1, arq))
            qnt++;
        else
        {
            fechaArquivo(arq);
            return 0;
        }
     }
     fechaArquivo(arq);
     if(qnt)
         *num = listar.codigoPista + 1;
     else
         *num = 1;
     return 1;
}
//------------------------------------------------------------------------------
//Objetivo  : Seleciona um código de avião cadastrado no arquivo.
//Parâmetros: Código a ser selecionado.
//Retorno   : Retorna falso em caso de desistência da leitura ou 1 caso bem sucedida.
int selecionaAviao(char *codigo, int posicao)
{
     FILE *arq;
     int cont, aux=0, existeErro=0, qtde, itemSelecionado, selecao=0, qtdeAviao, opcao=0;
     Aviao ler;
     char **codigos=NULL;
           
     arq = abreArquivo(ARQ_AVIAO, "rb","Erro ao abrir o arquivo de Aviao");
	  
     contaRegistrosAviao(&qtdeAviao);   
	    
     codigos  = (char **)malloc(sizeof(char *)*(qtdeAviao+1));
     if(codigos != NULL)
     {
	     for(cont=0;cont<qtdeAviao;cont++){
		     codigos[cont]= (char*)malloc(sizeof(char)*TAM_ALOC+1);
		     if(codigos[cont] != NULL)
             {     
                 fread(&ler, sizeof(Aviao), 1, arq);
                 
                 strcpy(codigos[cont],ler.codigoAviao);
                 
		     }
             else
             {
                 imprimeMsg("Erro de alocação.", 17, 14, LIGHTRED, BLACK);
                 existeErro = 1;
             }
		 }
	 }else{
         imprimeMsg("Erro de alocação.", 17, 14, LIGHTRED, BLACK);
         existeErro = 1;
     }
     
	 if(!existeErro)
     {
     	 if(qtdeAviao>5){
             imprimeMsg("Aperte a tecla ESPACO para listar os proximos itens.", 17, 25, LIGHTRED, BLACK);
             opcao=1;
     	 }
     	
         for (cont=0;cont<qtdeAviao;cont+=5)
         {  
			 qtde = qtdeAviao -cont > 5 ? 5: qtdeAviao-cont;   
             
             if(posicao==1){
			  	
			     if(!(itemSelecionado = menuSelecao(qtde,&codigos[cont],YELLOW,LIGHTGRAY,10,3,0,0,BLACK,YELLOW,0,opcao)))
                     return 0;
             }
			 else
			 {
			    
                 if(!(itemSelecionado = menuSelecao(qtde,&codigos[cont],YELLOW,LIGHTGRAY,11,28,0,0,BLACK,YELLOW,0,opcao)))
                     return 0;
             }
             if(cont+5<qtdeAviao)
             {
			     if(itemSelecionado!=-1)
              	     break;
              	 else
              	     selecao++;
             }
		     if(((selecao+1)*5) >= (qtdeAviao))
			     opcao=0;     
         }         
         limpaArea(17, 25, 52, 1); 
         
         itemSelecionado=(itemSelecionado+(5*selecao));
		 			 
		 strcpy(codigo,codigos[itemSelecionado-1]);
         if(posicao==1){
		     gotoxy(3,10);
             printf("%s",codigo);
         }else{
             gotoxy(28,11);
             printf("%s",codigo);   
         }
     } 
         
	 if(codigos !=NULL)
     {
        for (cont=0;cont<qtdeAviao;cont++)
            free(codigos[cont]); 
        free(codigos);           
     }
     return 1;
}         
//------------------------------------------------------------------------------
//Objetivo : Ler e validar uf de um endereço.
//Parâmetro: Endereço inicial do local onde armazenar uf, endereço inicial da memoria temporaria e valor de início.
//Retorno  : 0 - desistência da leitura ou 1 - bem sucedida.
int lerValidaUF(char *uf, int finalidade)
{
// Declarações
    int validaUF(char *sigla);
    int cont;
// Instruções
    do
    {
         if(finalidade)
         {
             if(!(escrevaLimitado(strlen(uf) + 2, strlen(uf) + 2, 15, 2, 3, 2, uf, strlen(uf ))))
                  return 0;
         }
         else
         {
             if(!(escrevaLimitado(2, 2, 15, 2, 3, 2, uf, 0)))
                  return 0;
         }
         maiusculo(uf);
		 if(!(validaUF(uf)))
         {
            mostraMsgErro ("\aUF invalido!", 3, 15, 9, 1);
            finalidade = 0;
         }
         else
           limpaArea(48, 25, 28, 1);
    }while(!(validaUF(uf)));
    return 1;
}
//------------------------------------------------------------------------------
//Objetivo   : Informar se a sigla do estado é ou não válida.
//Parâmetros : Sigla do estado.
//Retorno    : 0 - desistência da leitura ou 1 - bem sucedida.
int validaUF(char *sigla) 
{
// Declaracoes 
    int achei=0;
    // Instrucoes   
    if(!stricmp("AC",sigla)||!stricmp("AL",sigla)||!stricmp("AP",sigla)||!stricmp("AM",sigla)||
       !stricmp("BA",sigla)||!stricmp("CE",sigla)||!stricmp("DF",sigla)||!stricmp("ES",sigla)||
       !stricmp("GO",sigla)||!stricmp("MA",sigla)||!stricmp("MT",sigla)||!stricmp("MS",sigla)||
       !stricmp("MG",sigla)||!stricmp("PR",sigla)||!stricmp("PB",sigla)||!stricmp("PA",sigla)||
       !stricmp("PE",sigla)||!stricmp("PI",sigla)||!stricmp("RJ",sigla)||!stricmp("RN",sigla)||
       !stricmp("RS",sigla)||!stricmp("RO",sigla)||!stricmp("RR",sigla)||!stricmp("SC",sigla)||
       !stricmp("SE",sigla)||!stricmp("SP",sigla)||!stricmp("TO",sigla))
           achei=1;
    return achei;
}
//------------------------------------------------------------------------------
//Objetivo:   Ler e validar o tamanho do circuito.
//Parâmetros: Circuito a ser informado, string temporária para leitura e finalidade
//            de cadastro ou alteração.
//Retorno:    Retorna falso em caso de desistência da leitura ou 1 caso bem sucedida.
int lerValidaCircuito(float *circuito, char * temp, int finalidade)
{
    do
    {
         if(finalidade)
         {
             sprintf(temp, "%6.2f", *circuito);        
             if(!(escrevaLimitado(strlen(temp) + 47, strlen(temp) + 47, 15, 2, 8, 7, temp, strlen(temp))))
                  return 0;
         }
         else
         {
             if(!(escrevaLimitado(47, 47, 15, 2, 8, 7, temp, 0)))
                  return 0;
         }
         *circuito = atof(temp);
         if((*circuito <=1159) || (*circuito >= 4969))
         {
            mostraMsgErro ("Tamanho circuito invalido!", 48, 15, 10, 1);
            finalidade = 0;
         }
         else
           limpaArea(48, 25, 30, 1);
    }while((*circuito <= 1159) || (*circuito >= 4969));
    return 1;
}
//------------------------------------------------------------------------------
//Objetivo  : Ler e validar a velocidade maxima de um avião.
//Parâmetros: Velocidade a ser informado, string temporária para leitura e finalidade
//            de cadastro ou alteração.
//Retorno   : Retorna falso em caso de desistência da leitura ou 1 caso bem sucedida.
int lerValidaVelocidade(int *velocidade, char * temp, int finalidade)
{
    do
    {
         if(finalidade)
         {
             sprintf(temp, "%d", *velocidade);             
             if(!(escrevaLimitado(strlen(temp) + 64, strlen(temp) + 64, 15, 3, 5, 4, temp, strlen(temp))))
                  return 0;
         }
         else
         {
             if(!(escrevaLimitado(64, 64, 15, 3, 5, 4, temp, 0)))
                  return 0;
         }
         *velocidade = atof(temp);
         if((*velocidade <= 526) || (*velocidade >= 1021))
         {
            mostraMsgErro ("Velocidade invalida!", 65, 15, 10, 1);
            finalidade = 0;
         }
         else
           limpaArea(48, 25, 28, 1);
    }while((*velocidade <= 526) || (*velocidade >= 1021));
    return 1;
}
