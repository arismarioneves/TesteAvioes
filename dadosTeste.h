//================= DADOS TESTE ================================================

void cadastraTeste(void);
void telaCadastroTeste(int finalidade);
void contaRegistrosTeste(int *qnt);
int selecionaAviao(char *codigo, int posicao);
int selecionaPista(int *codigo);

//------------------------------------------------------------------------------
//Objetivo  : Cadastrar novo teste.
//Parâmetros: Nenhum.
//Retorno   : Nenhum.
void cadastraTeste(void)	
{
//================= PROTÓTIPOS DAS FUNÇÕES =====================================
	 void obtemDataHoraAtual(int *dia, int * mes, int *ano, int* hora, int *minuto);
     int lerValidaVelocidadeMax(int *velocidade, char * temp, int finalidade);
     void atualizaVelocidadePista(Teste pesquisa);
	 
// Declarações
     int qntAviao, qntPista;
     char temporario[TAM_TEXT], opcao;  
     Teste novo;
     FILE *arquivo;
// Instruções
     contaRegistrosAviao(&qntAviao);
     contaRegistrosPista(&qntPista);
     if(!qntAviao || !qntAviao)
     {
          apresentaMsg("Nenhum aviao ou pista cadastrados.", 15, 12, LIGHTRED);
          getch();
          return;
     }
	do
     {
         //clrscr();
         system("cls");
		 telaCadastroTeste(0);
         textcolor(YELLOW);
         obtemDataHoraAtual(&novo.dia, &novo.mes, &novo.ano, &novo.hora, &novo.minuto);
         gotoxy(57, 10);
         printf("%02d/%02d/%d - %02d:%02d", novo.dia, novo.mes, novo.ano, novo.hora, novo.minuto);
         if(!encontraProxTeste(&novo.codigoTeste))
              return;
		 if(!(selecionaAviao(novo.codigoAviao, 1)))
             return;   
		 if(!(selecionaPista(&novo.codigoPista)))
             return;
         if(!lerValidaVelocidadeMax(&novo.velocidadeMax, temporario, 0))
             return;     
		 
		 imprimeMsg("Os dados estao corretos? (S/N) : ", 4, 23, WHITE, BLACK);
         opcao = lerOpcao(37, 23);	       
     }while(!opcao);
     
     atualizaVelocidadePista(novo);
     
     arquivo = abreArquivo(ARQ_TESTE, "ab","Erro ao abrir o arquivo de Testes");
     escreveArquivo(&novo, sizeof(Teste) , 1, arquivo);
     fechaArquivo(arquivo);
}
//-----------------------------------------------------------------------------
//Objetivo  : Monta a tela para o cadastro do teste.
//Parâmetros: Nenhum.
//Retorno   : Nenhum.
void telaCadastroTeste(int finalidade)
{
     char text[TAM_TEXT];
     textcolor(LIGHTGRAY);
     fazBorda(78, 27, 1, 1, 0); //Borda tela de Cadastro
     textcolor(WHITE);
     fazBorda(30, 1, 24, 2, 0);
     imprimeMsg((finalidade)? "  ALTERACAO DE TESTES" : "   CADASTRO DE TESTES", 28, 3, WHITE, BLACK);
     fazBorda(15, 5, 2, 9, 0);
     sprintf(text,"C%cdigo Avi%co",162,198);
     imprimeMsg(text, 4, 9, WHITE, BLACK);
     fazBorda(15, 5, 27, 9, 0);
     sprintf(text,"C%cdigo Pista",162);
     imprimeMsg(text, 29, 9, WHITE, BLACK);
     fazBorda(16, 1, 55, 13, 0);
	 imprimeMsg("Velocidade MAX", 57, 13, WHITE, BLACK);
     fazBorda(20, 1, 55, 9, 0);
     imprimeMsg("Data/Hora Cadastro", 57, 9, WHITE, BLACK);
}
//------------------------------------------------------------------------------
//Objetivo  : Obter a data e hora atuais.
//Parâmetros: Dia, Mês e Ano, hora e minutos que serão informados.
//Retorno   : Nenhum.
void obtemDataHoraAtual(int *dia, int * mes, int *ano, int* hora, int *minuto)
{
   time_t t;
   struct tm *dataAtual;
   t = time(NULL);
   dataAtual = localtime(&t);
   *dia      = dataAtual->tm_mday;
   *mes      = dataAtual->tm_mon+1;
   *ano      = 1900 + dataAtual->tm_year;
   *hora     = dataAtual->tm_hour;
   *minuto  = dataAtual->tm_min;
}
//------------------------------------------------------------------------------
//Objetivo  : Descobrir qual o próximo número identificador de teste a ser gerado.
//Parâmetros: Número identificador.
//Retorno   : 0 caso ocorra erro na leitura do arquivo e 1 caso bem sucedida.
int encontraProxTeste(int *num)
{
     Teste listar;
     int qnt = 0, qntTeste;
     FILE *arq;
     
     contaRegistrosTeste(&qntTeste);
     arq = abreArquivo(ARQ_TESTE, "rb", "Erro ao abrir arquivo de testes.");
     while(qnt < qntTeste)
     {
        if(leArquivo(&listar, sizeof(Teste), 1, arq))
            qnt++;
        else
        {
            fechaArquivo(arq);
            return 0;
        }
     }
     fechaArquivo(arq);
     if(qnt)
         *num = listar.codigoTeste + 1;
     else
         *num = 1;
     return 1;
}
//------------------------------------------------------------------------------
//Objetivo  : Seleciona um código de uma pista cadastrada no arquivo.
//Parâmetros: Código a ser selecionado.
//Retorno   : Retorna falso em caso de desistência da leitura ou 1 caso bem sucedida.
int selecionaPista(int *codigo)
{
     FILE *arq;
     int cont, aux=0, existeErro=0, qtde, itemSelecionado, selecao=0, qtdePista, opcao=0;
     Pista ler;
     char **codigos=NULL, temp[TAM_CODIGO];
           
     arq = abreArquivo(ARQ_PISTA, "rb","Erro ao abrir o arquivo de Pista");
	  
     contaRegistrosPista(&qtdePista);   
	    
     codigos  = (char **)malloc(sizeof(char *)*(qtdePista+1));
     if(codigos != NULL)
     {
	     for(cont=0;cont<qtdePista;cont++){
		     codigos[cont]= (char*)malloc(sizeof(char)*TAM_ALOC+1);
		     if(codigos[cont] != NULL)
             {     
                 fread(&ler, sizeof(Pista), 1, arq);
                 
                 sprintf(temp, "%d", ler.codigoPista);  
                 
                 strcpy(codigos[cont],temp);

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
         if(qtdePista>5){
             imprimeMsg("Aperte a tecla ESPACO para listar os proximos itens.", 17, 25, LIGHTRED, BLACK);
             opcao=1;
     	 }
     	 
         for (cont=0;cont<qtdePista;cont+=5)
         {  
		     qtde = qtdePista -cont > 5 ? 5: qtdePista-cont;   
              			 
		     if(!(itemSelecionado = menuSelecao(qtde,&codigos[cont],YELLOW,LIGHTGRAY,10,28,0,0,BLACK,YELLOW,0,opcao)))
                 return 0;
              
			 if(cont+5<qtdePista)
             {
			     if(itemSelecionado!=-1)
              	     break;
              	 else
              	     selecao++;
             }
             if(((selecao+1)*5) >= (qtdePista))
			     opcao=0;    
         }
         limpaArea(17, 25, 52, 1);
         
         itemSelecionado=(itemSelecionado+(5*selecao));   		 
		 			 
		 strncpy(temp,codigos[itemSelecionado-1],1);
		 
         *codigo = atof(temp); 

	     gotoxy(28,10);
	     printf("%s",codigos[itemSelecionado-1]);
     } 
         
	 if(codigos !=NULL)
     {
        for (cont=0;cont<qtdePista;cont++)
            free(codigos[cont]); 
        free(codigos);           
     }
     return 1;
}         
//------------------------------------------------------------------------------
//Objetivo  : Ler e validar o código de uma pista.
//Parâmetros: Código a ser informado, string temporaria.
//Retorno   : Retorna falso em caso de desistência da leitura ou 1 caso bem sucedida.
int lerValidaCodigoPista(char *codigo, char *temp)
{
    sprintf(temp, "%d", *codigo);
    do
    {
        if(!(escrevaLimitado(27, 27, 10, 1, 7, 6, temp, 0)))
            return 0;  
        *codigo = atoi(temp);    
        if(*codigo <= 0){
            sprintf(temp,"C%cdigo inv%clido!     ",162,160);
            mostraMsgErro (temp,28, 10, 10, 1);
        }
        else                
            limpaArea(48, 25, 28, 1);
    }while(*codigo <= 0);
    return 1;
}
//------------------------------------------------------------------------------
//Objetivo  : Ler e validar a velocidade maxima de um avião.
//Parâmetros: Velocidade maxima a ser informada, string temporária para leitura e finalidade
//            de cadastro ou alteração.
//Retorno   : Retorna falso em caso de desistência da leitura ou 1 caso bem sucedida.
int lerValidaVelocidadeMax(int *velocidade, char * temp, int finalidade)
{
    do
    {
         if(finalidade)
         {
             sprintf(temp, "%d", *velocidade);             
             if(!(escrevaLimitado(strlen(temp) + 55, strlen(temp) + 55, 14, 3, 5, 4, temp, strlen(temp))))
                  return 0;
         }
         else
         {
             if(!(escrevaLimitado(55, 55, 14, 3, 5, 4, temp, 0)))
                  return 0;
         }
         *velocidade = atof(temp);
         if((*velocidade <= 526) || (*velocidade >= 1021))
         {
            mostraMsgErro ("Velocidade invalida!", 56, 14, 6, 1);
            finalidade = 0;
         }
         else
           limpaArea(48, 25, 28, 1);
    }while((*velocidade <= 526) || (*velocidade >= 1021));
    return 1;
}
//------------------------------------------------------------------------------
//Objetivo  : Atualizar a velocidade maxima de uma pista após um teste realizado.
//Parâmetros: Struct com informações de teste a alterar na struct pista.
//Retorno   : Nenhum.
void atualizaVelocidadePista(Teste pesquisa)
{
     int registro, qntPista, aux=0;
     Pista alterar, alterado;
     FILE *arq;

     encontraNumRegistroPista(pesquisa.codigoPista, &registro);
	 
	 contaRegistrosPista(&qntPista);
     do{
         arq = abreArquivo(ARQ_PISTA, "rb", "Erro ao abrir arquivo de pista.");
         fseek(arq, (registro - 1) * sizeof(Pista), SEEK_SET);
         if(!leArquivo(&alterar, sizeof(Pista), 1, arq))
         {
             fechaArquivo(arq);
             return;
         }
         fechaArquivo(arq);
         
         if(pesquisa.codigoPista==alterar.codigoPista)
             if(pesquisa.velocidadeMax > alterar.velocidade){    
                 alterar.velocidade = pesquisa.velocidadeMax;
             } 
			 alterado = alterar;
         arq = abreArquivo(ARQ_PISTA, "rb+", "Erro ao abrir arquivo de pista.");
         fseek(arq, (registro - 1) * sizeof(Pista), SEEK_SET);
         if(!escreveArquivo(&alterado, sizeof(Pista), 1, arq))
            return;
         fechaArquivo(arq);
         aux++;
     }while(aux < qntPista); 
}
