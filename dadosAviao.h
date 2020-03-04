//================= DADOS AVIÕES ===============================================

void cadastrarAviao(void);
void telaCadastroAviao(int finalidade);
void contaRegistrosAviao(int *);
int lerValidaCodigoAviao(char *codigo, char *temp, int posicao);
int validaCodigo(char *codigo); 

//------------------------------------------------------------------------------
//Objetivo  : Cadastrar novo avião.
//Parâmetros: Nenhum.
//Retorno   : Nenhum.
void cadastrarAviao(void)	
{
//================= PROTÓTIPOS DAS FUNÇÕES =====================================
     int lerValidaCapacidade(int *, char *, int);
     int verificaCodigoAviao(char *, char *);
     int selecionaPais(char *pais);
// Declarações
     char opcao;
     Aviao novo;     
     FILE *arquivo;
     char temporario[TAM_TEXT];    
// Instruções
     do
     {
         //clrscr();      
         system("cls");
		 telaCadastroAviao(0);
         textcolor(YELLOW);
         if(!(escrevaLimitado(2, 2, 7, 1, MAX_NOME, MAX_NOME - 1, novo.modelo, 0)))
             return;
         if(!(lerValidaCapacidade(&novo.capacidade, temporario, 0)))
             return;
		 if(!(verificaCodigoAviao(novo.codigoAviao, temporario)))
             return;
         if(!(escrevaLimitado(2, 2, 15, 1, MAX_NOME, MAX_NOME - 1, novo.cliente.nome, 0))) //CLIENTE - NOME
             return;
         if(!selecionaPais(novo.cliente.pais))//CLIENTE - PAÍS
             return; 
         imprimeMsg("Os dados estao corretos? (S/N) : ", 45, 23, WHITE, BLACK);
         opcao = lerOpcao(78, 23);
     }while(!opcao);
     arquivo = abreArquivo(ARQ_AVIAO, "ab","Erro ao abrir o arquivo de Avioes");
     escreveArquivo(&novo, sizeof(Aviao), 1, arquivo);
     fechaArquivo(arquivo);
}
//------------------------------------------------------------------------------
//Objetivo  : Monta a tela para cadastro de aviões.
//Parâmetros: Finalidade alteração ou cadastro.
//Retorno   : Nenhum.
void telaCadastroAviao(int finalidade)
{
     char text[TAM_TEXT];
     textcolor(LIGHTGRAY);
     fazBorda(78, 27, 1, 1, 0); //Borda tela de Cadastro
     textcolor(WHITE);
     fazBorda(30, 1, 24, 2, 0);
     imprimeMsg((finalidade)? "ALTERACAO DE AVIOES" : "CADASTRO DE AVIOES", 28, 3, WHITE, BLACK);
     fazBorda(76, 1, 2, 6, 0);
	 imprimeMsg("Modelo", 4, 6, WHITE, BLACK);
     fazBorda(16, 1, 2, 10, 0);
     imprimeMsg("Capacidade", 4, 10, WHITE, BLACK);
     fazBorda(10, 1, 27, 10, 0);
     sprintf(text,"C%cdigo",162);
	 imprimeMsg(text, 29, 10, WHITE, BLACK);     
     fazBorda(76, 1, 2, 14, 0);
     imprimeMsg("Nome Cliente", 4, 14, WHITE, BLACK);
     fazBorda(40, 9, 2, 18, 0);
     sprintf(text,"Pa%cs Origem",161);
     imprimeMsg(text, 4, 18, WHITE, BLACK);
}
//------------------------------------------------------------------------------
//Objetivo  : Ler e validar capacidade de passageiros em um avião.
//Parâmetros: Capacidade a ser informado, string temporária para leitura e finalidade
//            de cadastro ou alteração.
//Retorno   : Retorna falso em caso de desistência da leitura ou 1 caso bem sucedida.
int lerValidaCapacidade(int *capacidade, char * temp, int finalidade)
{
	do
    {
         if(finalidade)
         {
             sprintf(temp, "%d", *capacidade);             
             if(!(escrevaLimitado(strlen(temp) + 2, strlen(temp) + 2, 11, 2, 4, 3, temp, strlen(temp))))
                  return 0;
         }
         else
         {
             if(!(escrevaLimitado(2, 2, 11, 2, 4, 3, temp, 0)))
                  return 0;
         }
         *capacidade = atof(temp);
         if((*capacidade <= 69) || (*capacidade >= 125))
         {
         	sprintf(temp,"Capacidade inv%clida!",160);
            mostraMsgErro (temp, 3, 11, 14, 1);
            finalidade = 0;
         }
         else
           limpaArea(48, 25, 28, 1);
    }while((*capacidade <= 69) || (*capacidade >= 125));
    return 1;
}
//------------------------------------------------------------------------------
//Objetivo  : Verifica se há código repetido.
//Parâmetros: Código a ser informado, string temporaria.
//Retorno   : Retorna falso em caso de desistência da leitura ou 1 caso bem sucedida.
int verificaCodigoAviao(char *codigo, char *temp)
{
    int aux = 0, qnt;
    Aviao ler;
    FILE *arq;
    
    contaRegistrosAviao(&qnt);
    if(!lerValidaCodigoAviao(codigo, temp, 1))
        return 0;
    sprintf(temp,"Erro ao abrir o arquivo de Avi%ces",228);
    arq = abreArquivo(ARQ_AVIAO,"rb",temp);
    while(aux < qnt)
    {
        if(!leArquivo(&ler, sizeof(Aviao), 1, arq))
        {
            fechaArquivo(arq);
            return 0;
        }
        while(!strcmp(codigo, ler.codigoAviao))
        {              
        	sprintf(temp,"C%cdigo j%c cadastrado!",162,160);
            mostraMsgErro(temp, 28, 11, 10, 1);
            if(!lerValidaCodigoAviao(codigo, temp, 1))
            {
                fechaArquivo(arq);
                return 0;
            }
            aux = -1;
            
            rewind(arq);
        }
        aux++;
    }
    fechaArquivo(arq);
    return 1;
}
//------------------------------------------------------------------------------
//Objetivo  : Ler e validar o código de um avião.
//Parâmetros: Código a ser informado, string temporaria.
//Retorno   : Retorna falso em caso de desistência da leitura ou 1 caso bem sucedida.
int lerValidaCodigoAviao(char *codigo, char *temp, int posicao)
{
    do
    {
    	if(posicao==1)
		{	
	        if(!(escrevaLimitado(20, 27, 11, 7, 8, 7, codigo, 0)))
	            return 0; 
			    if(!(validaCodigo(codigo))){
	        	    sprintf(temp,"C%cdigo inv%clido!     ",162,160);	
				    mostraMsgErro (temp,28, 11, 10, 1);
	        }
	        else                
	            limpaArea(48, 25, 28, 1);
	            
	    }else{    
	           
	        if(!(escrevaLimitado(2, 2, 10, 7, 8, 7, codigo, 0)))
	            return 0; 
	        if(!(validaCodigo(codigo))){
	        	    sprintf(temp,"C%cdigo inv%clido!     ",162,160);
	                mostraMsgErro (temp,3, 10, 10, 1);
	        }
            else                
            limpaArea(48, 25, 28, 1);         
        }    
    }while(!(validaCodigo(codigo)));
    return 1;
}
//------------------------------------------------------------------------------
//Objetivo  : Verifica um código.
//Parâmetros: Código.
//Retorno   : 0(Inválida) ou 1(Válida).
int validaCodigo(char *codigo)
{
    int flag=1, cont, aux;
    
    for(cont=0; cont<3; cont++){
        if(!isalpha(codigo[cont])){
            flag=0;
            break;
        }
    }
    for(aux = 3; aux <7; aux++){
        if(!isdigit(codigo[aux])){
            flag=0;
            break; 
        }
    }  
    return flag;
}
//------------------------------------------------------------------------------
//Objetivo  : Selecionar um pais.
//Parâmetros: Pais a ser selecionado.
//Retorno   : Retorna falso em caso de desistência da leitura ou 1 caso bem sucedida.
int selecionaPais(char *pais)
{
      FILE *arq;
	  int cont, existeErro=0, qtde, itemSelecionado, selecao=0;
	  
	  char **paises=NULL, tecla, aux[MAX_PAIS];
	           
      arq = abreArquivo("paises.txt", "rb","Erro ao abrir o arquivo de Paises");
	    
     paises  = (char **)malloc(sizeof(char *)*(TOTAL_PAISES+1));
     if(paises != NULL)
     {
	     for(cont=0;cont<TOTAL_PAISES;cont++){
		     paises[cont]= (char*)malloc(sizeof(char)*TAM_ALOC+1);
		     if(paises[cont] != NULL)
             {     
		         fgets(paises[cont],MAX_PAIS,arq);
	             trocarTerminador(paises[cont]);
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
         for (cont=0;cont<TOTAL_PAISES;cont+=9)
         {  
			 qtde = TOTAL_PAISES -cont > 9 ? 9: TOTAL_PAISES-cont;   
			 
			 if(!(itemSelecionado = menuSelecao(qtde,&paises[cont],YELLOW,LIGHTGRAY,19,3,0,0,BLACK,YELLOW,0,0)))
                 return 0;

              if(cont+9<TOTAL_PAISES)
              {
				  if(itemSelecionado!=9)
              	      break;
              	  else
              	      selecao++;
              }     
         }
         
         itemSelecionado=(itemSelecionado+(9*selecao));
		 			 
		 strcpy(pais,paises[itemSelecionado-1]);
		 gotoxy(3,19);
         printf("%s",pais);   
     } 
         
	 if(paises !=NULL)
     {
        for (cont=0;cont<TOTAL_PAISES;cont++)
            free(paises[cont]); 
        free(paises);           
     }
     return 1;
}         
