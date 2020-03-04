//================= FUNÇÕES MANIPULAR TESTE ====================================

int listarTeste(Teste *lista, int qntRegistros, int finalidade);
void contaRegistrosTeste(int *);
void centralPesquisaTeste(int finalidade);
void escolhaUmaTeste(Teste *resultados, int cont, int finalidade);
void alteracaoTeste(Teste alterar);
void alterarTeste(Teste *alterar);
void exclusaoTeste(Teste resultado);
int lerData(long int *data, long int dataAnterior);
int validaData(int dia, int mes, int ano);
int realocarTeste(Teste **resultados, int qnt);
void ordenaResultadosTeste(Teste *registro, int cont);
int strCmp(char *string1, char *string2);
void encontraNumRegistroTeste(int identificador, int *registro);
void apresentaInfo(Aviao *dadoAviao, Pista *dadoPista, Teste *dadoTeste, char *msg);

//------------------------------------------------------------------------------
//Objetivo:   Listar os testes cadastradas de acordo com a finalidade.
//Parâmetros: Lista de testes, quantidade de registros e finalidade
//            exclusão, consulta ou outros relatórios.
//Retorno:    Nenhum.
int listarTeste(Teste *listar, int qtdeRegistros, int finalidade)
{
//Declarações
    FILE *arquivo;
    Teste lista;
    char **dados=NULL, aux[7];
    int linha,cont=0,i,qtde=0,itemSelecionado=0,qtdeAlocada=0,existeErro=0,selecao=0,opcao=0;
    int comparaCodigoTeste(const void * p1, const void *p2);
    void telaListarTeste(int);
// Instruções
    telaListarTeste(finalidade);
    gotoxy(20,10);
   
    if(finalidade)
    {     
       if(qtdeRegistros != 0)
       {
       	   // Ordena os dados dos teste por código
           qsort(listar,qtdeRegistros,sizeof(Teste),comparaCodigoTeste);
         
           // Carrega o menu vertical
           dados = (char**) malloc(sizeof(char*)* (qtdeRegistros+1)) ;   
           if(dados != NULL)
           {
                for(i=0;i<qtdeRegistros;i++)
                {   
                   dados[i] = (char*) malloc(sizeof(char)*(TAM_ALOC+1));
                   if(dados[i] != NULL)
                   {       
                      gotoxy(3,24);
                      textcolor(BLACK);
                      textbackground(GREEN);
                      printf("[Apresentando %d de %d]", i + 1 ,qtdeRegistros);

                      if(finalidade == 1)
                          imprimeMsg("[Selecione o registro que deseja EXCLUIR]", 38, 24, BLACK, LIGHTRED);
                      else if(finalidade == 2)
                          imprimeMsg("[Selecione o registro que deseja ALTERAR]", 38, 24, BLACK, LIGHTRED);
                      else
                          imprimeMsg("[Selecione o registro que deseja CONSULTAR]", 36, 24, BLACK, LIGHTRED);             
                                   
                          sprintf(dados[i],"#%d%12.12s\t\t%12d\t%14d\t    %d/%02d/%d", i+1, listar[i].codigoAviao, listar[i].codigoPista, listar[i].velocidadeMax,
                              listar[i].dia, listar[i].mes, listar[i].ano);	   
                              		 
					  qtdeAlocada++;                     
                   }
                   else
                   {
                       imprimeMsg("Erro de alocacao.", 17, 14, LIGHTRED, BLACK);
                       existeErro = 1;
                   }
                }    
           }
           else
           {
               imprimeMsg("Erro de alocacao.", 17, 14, LIGHTRED, BLACK);
               existeErro = 1;
           }
          
           if(!existeErro)
           {
           	   if(qtdeRegistros>10){
                   imprimeMsg("Aperte a tecla ESPACO para listar os proximos itens.", 17, 22, LIGHTRED, BLACK);
                   opcao=1;
     	       }  
               for (i=0;i<qtdeRegistros;i+=10)
               {  
                   qtde = qtdeRegistros -i > 10 ? 10: qtdeRegistros-i;   
                   
                   if(!(itemSelecionado = menuSelecao(qtde,&dados[i],BLACK,RED,8,3,1,0,WHITE,WHITE,75,opcao)))
                       return 0;
                   
                    if(i+10<qtdeRegistros)
                    {
			            if(itemSelecionado!=-1)
              	            break;
              	        else
              	            selecao++;
					}
				    if(((selecao+1)*10) >= (qtdeRegistros))
			            opcao=0;
			  }
			  itemSelecionado=(itemSelecionado+(10*selecao));   
          }       
          if(dados !=NULL)
          {
             for (i=0;i<qtdeAlocada;i++)
                 free(dados[i]); 
             free(dados);           
          }
      }
      else 
      {
          textcolor(LIGHTRED);
          gotoxy (22,10);
          printf("Nenhum teste foi cadastrado.");
          getch();
	  }
   }
   else 
   {
         linha = 8;
         contaRegistrosTeste(&qtdeRegistros);
         if(qtdeRegistros)
         {
             arquivo = abreArquivo(ARQ_TESTE,"rb","Erro ao abrir o arquivo de testes.");
             while(qtde < qtdeRegistros)
             {
                  if(leArquivo(&lista, sizeof(Teste), 1, arquivo))
                  {
                      gotoxy(3,24);
                      textcolor(BLACK);
                      textbackground(GREEN);
                      printf("[Mostrando %d de %d]", qtde + 1 ,qtdeRegistros);
                      gotoxy(3, linha);
                      textbackground((qtde % 2)? WHITE: LIGHTGRAY);
                      
                      printf("%-12.12s\t\t%12d\t%14d\t    %d/%02d/%d - %02d:%02d", lista.codigoAviao, lista.codigoPista, lista.velocidadeMax,
                       lista.dia, lista.mes, lista.ano, lista.hora, lista.minuto);
                      linha++;
                      qtde++;
                      if(!(qtde % 16) && (qtde != qtdeRegistros))
                      {
                         getch();    
                         telaListarTeste(0);
                         linha = 8;
                      }
                  }
                  else
                  {
                      fechaArquivo(arquivo);
                      return;
                  }
                  
             }
             fechaArquivo(arquivo); 
         }
         else
         {
             textcolor(LIGHTRED);
             gotoxy (25,10);
             printf("Nenhum teste foi cadastrado.");
         }
   }
   textbackground(BLACK);
   if(!finalidade)
      getch();
     
   return itemSelecionado; 
}
//------------------------------------------------------------------------------
//Objetivo  : Compara os dados a serem ordenados pela qsort.
//Parâmetros: Endereço para os elementos a serem pesquisados na ordenação.
//Retorno   : =0 --> dados iguais
//            >0 --> dados desordenados
//            <0 --> dados ordenados 
int comparaCodigoTeste(const void * p1, const void *p2)
{
Teste *teste1,*teste2;

  teste1 = (Teste*)p1;
  teste2 = (Teste*)p2;
  return stricmp((*teste1).codigoAviao,(*teste2).codigoAviao); 
}
//------------------------------------------------------------------------------
//Objetivo  : Monta a tela para o listar os testes.
//Parâmetros: Finalidade exclusão ou consulta.
//Retorno   : Nenhum.
void telaListarTeste(int finalidade)
{
     textbackground(BLACK);
     textcolor(WHITE);
     //clrscr();
     system("cls");
	 textcolor(LIGHTGRAY);
     fazBorda(78, 27, 1, 1, 0);
     textcolor(WHITE);
     fazBorda(76, 18, 2, 5, 1);  
     if(!finalidade)
     {
         fazBorda(35, 1, 24, 2, 0);
         gotoxy(27, 3);
     }
     else
     {
         fazBorda(57, 1, 14, 2, 0);
         gotoxy(17, 3);
     }             
     printf("LISTA DE TESTE ENCONTRADOS %s", (!finalidade)? "" : (finalidade == 1)? "PARA EXCLUSAO" : (finalidade == 2) ? "PARA ALTERACAO" : "PARA CONSULTA");
     gotoxy(3, 6);
     textcolor(YELLOW);
     
     if((finalidade < 1) || (finalidade >= 3) && (finalidade != 4))
     
         printf("CODIGO AVIAO\t\tCODIGO PISTA\tVELOCIDADE MAX\t    DATA E HORA");
     else
         printf("REG    CODIGO AVIAO\t\tCODIGO PISTA\tVELOCIDADE MAX\t   DATA E HORA");
     textcolor(WHITE);
     gotoxy(3, 7);
     printf("----------------------------------------------------------------------------");
}
//------------------------------------------------------------------------------
//Objetivo  : Conta quantos registros de testes ja foram feitos.
//Parâmetros: Quantidade que será informada.
//Retorno   : Nenhum.
void contaRegistrosTeste(int *qnt)
{
     FILE *arq;
     Teste ler;
     *qnt = 0;
     arq = abreArquivo(ARQ_TESTE, "rb","Erro ao abrir o arquivo de testes");
     while(fread(&ler, sizeof(Teste), 1, arq))
             (*qnt)++;
     fechaArquivo(arq);
}
//------------------------------------------------------------------------------
//Objetivo  : Consultar testes existente.
//Parâmetros: Finalidade da consulta, alteração, exclusão ou simples consulta.
//Retorno   : Nenhum.
void centralPesquisaTeste(int finalidade)
{
     void telaConsultaTeste(int);
	 void pesqTestePista(int finalidade);
	 void pesqTesteVelocidade(int finalidade);	 
	 void pesqVelocidadeMaxima(int finalidade);
	 void pesqTesteCodigoPeriodo(int finalidade);

	 
    // Declarações
	 char *opcoesConsulta[5] = {"Consulta por Pista",
                                "Consulta por Velocidade",
                                "Consulta por Velocidade Maxima",
                                "Consulta por Pista e Data",
                                "Voltar"};
     char *opcoesExclusao[4] = {"Exclusao por Pista",
                                "Exclusao por Velocidade",
                                "Consulta por Pista e Data",
                                "Voltar"};
     char *opcoesAlteracao[4] = {"Alteracao por Pista",
                                 "Alteracao por Velocidade",
                                 "Consulta por Pista e Data",
                                 "Voltar"};                                
     int opcao;
// Instruções
     do  
     {
     	 textbackground(BLACK);
         telaConsultaTeste(finalidade);
         gotoxy(27,10);
         opcao = menuVertical(1,(finalidade)? 4 :5, (finalidade == 1)? opcoesExclusao : (finalidade == 2) ? opcoesAlteracao : opcoesConsulta, 40);
         limpaArea(27, 10, 42, 7);
         switch(opcao)
         {
              case 1: 
                   pesqTestePista(finalidade);
				   break;
              case 2:
                   pesqTesteVelocidade(finalidade);   
                   break;
              case 3:
				   pesqVelocidadeMaxima(0);
				   break;
              case 4:
              	   if(finalidade)
              	       return;
              	   pesqTesteCodigoPeriodo(finalidade);   
              	   break;
              default:
                   return;
         }
     }while(opcao != -1);
}
//------------------------------------------------------------------------------
//Objetivo  : Monta a tela para consulta de Teste.
//Parâmetros: Finalidade de exclusão, alteração ou consulta.
//Retorno   : Nenhum.
void telaConsultaTeste(int finalidade)
{
     textcolor(WHITE);
     clrscr();
     textcolor(LIGHTGRAY);
     fazBorda(78, 27, 1, 1, 0);
     textcolor(WHITE);
     fazBorda(27, 1, 25, 2, 0);
     gotoxy(27, 3);
     printf("%s DE TESTES", (finalidade == 1)? "EXCLUSAO" : (finalidade == 2)? "ALTERACAO" : "CONSULTA");
}
//------------------------------------------------------------------------------
//Objetivo  : Pesquisa Testes realizadas por pista.
//Parâmetros: Finalidade de exclusão, alteração ou consulta.
//Retorno   : Nenhum.
void pesqTestePista(int finalidade)
{
     int qntTeste, aux, cont, qnt = 0;
     int identificador;
     Teste listar, *resultados = NULL;
     FILE *arqTeste;
     int lerIdentificadorTeste(int *identificador);
     
     fazBorda(15, 1, 2, 9, 0);
     imprimeMsg("Codigo Pista", 4, 9, WHITE, BLACK);
     textcolor(YELLOW);
     if(!lerIdentificadorTeste(&identificador))
         return;
     contaRegistrosTeste(&qntTeste);
     arqTeste = abreArquivo(ARQ_TESTE, "rb", "Erro ao abrir arquivo de Testes.");
     for(aux = 0; aux < qntTeste; aux++)
     {
         if(!leArquivo(&listar, sizeof(Teste), 1, arqTeste))
         {
              fechaArquivo(arqTeste);
              return;
         }
         textcolor(WHITE);
         
         if(!(identificador == listar.codigoPista))
	             continue;
	             
        	 if(!realocarTeste(&resultados, qnt))
                  return;                      
             resultados[qnt] = listar;
             qnt++;
     }
     fechaArquivo(arqTeste);
     ordenaResultadosTeste(resultados, qnt);
     if(qnt)
         escolhaUmaTeste(resultados, qnt, finalidade);   
     free(resultados);
     if(!qnt){
        imprimeMsg("Nenhum Teste foi encontrado nesta pista!", 11, 13, LIGHTRED, BLACK);
        getch();        
	 }
}
//------------------------------------------------------------------------------
//Objetivo  : Pesquisa relatorio de Testes de uma pista realizadas em num periodo de tempo.
//Parâmetros: Finalidade de exclusão, alteração ou consulta.
//Retorno   : Nenhum.
void pesqTesteCodigoPeriodo(int finalidade)
{
     long int dataInicial, dataFinal, dataComparar;
     int qntTeste, aux, cont, qnt = 0;
     int identificador;
     Teste listar, *resultados = NULL;
     FILE *arqTeste;
     int lerIdentificadorTeste(int *identificador);
     
     fazBorda(15, 1, 2, 9, 0);
     imprimeMsg("Codigo Pista", 4, 9, WHITE, BLACK);
     fazBorda(14, 1, 24, 9, 0);
     imprimeMsg("Data Inicial", 26, 9, WHITE, BLACK);
     fazBorda(14, 1, 50, 9, 0);
     imprimeMsg("  /  /", 25, 10, WHITE, BLACK);
     imprimeMsg("Data Final", 52, 9, WHITE, BLACK);
     imprimeMsg("  /  /", 51, 10, WHITE, BLACK);
     textcolor(YELLOW);
     if(!lerIdentificadorTeste(&identificador))
         return;
     if(!lerData(&dataInicial, 0))
         return;
     if(!lerData(&dataFinal, dataInicial))
         return;
     contaRegistrosTeste(&qntTeste);
     arqTeste = abreArquivo(ARQ_TESTE, "rb", "Erro ao abrir arquivo de Testes.");
     for(aux = 0; aux < qntTeste; aux++)
     {
         if(!leArquivo(&listar, sizeof(Teste), 1, arqTeste))
         {
              fechaArquivo(arqTeste);
              return;
         }
         dataComparar = listar.ano * 10000 + listar.mes * 100 + listar.dia;
         textcolor(WHITE);
         
         if(identificador == listar.codigoPista){
	         if(!((dataComparar <= dataFinal) && (dataComparar >= dataInicial)))
	             continue;
	             
        	 if(!realocarTeste(&resultados, qnt))
                  return;                      
             resultados[qnt] = listar;
             qnt++;
             //break;
         }
     }
     fechaArquivo(arqTeste);
     ordenaResultadosTeste(resultados, qnt);
     if(qnt)
         escolhaUmaTeste(resultados, qnt, finalidade);   
     free(resultados);
     if(!qnt){
        imprimeMsg("Nenhuma Teste foi encontrada neste intervalo de data!", 11, 13, LIGHTRED, BLACK);
        getch();        
	 }
}
//------------------------------------------------------------------------------
//Objetivo  : Pesquisa relatorio de Testes de uma pista entre intervalos de velocidade.
//Parâmetros: Finalidade de exclusão, alteração ou consulta.
//Retorno   : Nenhum.
void pesqTesteVelocidade(int finalidade)
{
     int velocidadeInicial, velocidadeFinal;
     int qntTeste, aux, cont, qnt = 0;
     Teste listar, *resultados = NULL;
     FILE *arqTeste;
     fazBorda(16, 1, 18, 9, 0);
     imprimeMsg("Velocidade MIN", 20, 9, WHITE, BLACK);
     fazBorda(16, 1, 45, 9, 0);
     imprimeMsg("Velocidade MAX", 47, 9, WHITE, BLACK);
     textcolor(YELLOW);
     if(!lerVelocidade(&velocidadeInicial, 0))
         return;
     if(!lerVelocidade(&velocidadeFinal, velocidadeInicial))
         return;
     contaRegistrosTeste(&qntTeste);
     arqTeste = abreArquivo(ARQ_TESTE, "rb", "Erro ao abrir arquivo de Testes.");
     for(aux = 0; aux < qntTeste; aux++)
     {
         if(!leArquivo(&listar, sizeof(Teste), 1, arqTeste))
         {
              fechaArquivo(arqTeste);
              return;
         }
         
         textcolor(WHITE);
         if(!((velocidadeInicial <= listar.velocidadeMax) && (velocidadeFinal >= listar.velocidadeMax)))
             continue;
         if(!realocarTeste(&resultados, qnt))
              return;                      
         resultados[qnt] = listar;
         qnt++;
     }
     fechaArquivo(arqTeste);
     ordenaResultadosTeste(resultados, qnt);
     if(qnt)
         escolhaUmaTeste(resultados, qnt, finalidade);   
     free(resultados);
     if(!qnt){
        imprimeMsg("Nenhuma Teste foi encontrado entre esses intervalos de velocidade!", 11, 13, LIGHTRED, BLACK);
        getch();        
	 }
}
//------------------------------------------------------------------------------
//Objetivo  : Pesquisa relatorio de Testes cuja velocidade obtida foi superior a velocidade máxima.
//Parâmetros: Finalidade de consulta.
//Retorno   : Nenhum.
void pesqVelocidadeMaxima(int finalidade)
{
	 FILE *arq, *arq2;
     int aux = 0, cont = 0, qntResult = 0, qntRegistro, qntRegistroTeste;
     Teste ler;
     Pista verificar, *resultados = NULL;
     
	 contaRegistrosPista(&qntRegistro);
	 arq2 = abreArquivo(ARQ_PISTA, "rb","Erro ao abrir o arquivo de pista"); 
	 for(cont = 0; cont < qntRegistro; cont++)
	 { 
         if(!leArquivo(&verificar, sizeof(Pista), 1, arq2))
         {
             fechaArquivo(arq2);
             return;
         }
	     //--------------------------------------------------------------------
		 contaRegistrosTeste(&qntRegistroTeste);
		 arq = abreArquivo(ARQ_TESTE, "rb","Erro ao abrir o arquivo de teste");
		 for(aux = 0; aux < qntRegistroTeste; aux++)
	     {
	         if(!leArquivo(&ler, sizeof(Teste), 1, arq))
			 {
	             fechaArquivo(arq);
	             return;
	         }
	             if(!(verificar.codigoPista == ler.codigoPista))
	                 continue;
				 if(!(verificar.velocidade == ler.velocidadeMax))   
	                 continue;
	             if(!realocarPista(&resultados, qntResult))
	                 break;
	             resultados[qntResult] = verificar;
	             qntResult++;
	     }
	     fechaArquivo(arq);
    }
    fechaArquivo(arq2);
	 
    if(qntResult)
        escolhaUmaPista(resultados, qntResult, finalidade);
    free(resultados);
    if(!qntResult){
        imprimeMsg("Nenhuma Teste com velocidade superior a velocidade Maxima!", 17, 14, LIGHTRED, BLACK);
        getch();
    }
}
//------------------------------------------------------------------------------
//Objetivo  : Consultar ou excluir o registro especificado dentro de uma pesquisa.
//Parâmetros: Testes que se enquadram na pesquisa, numero de resultados e finalidade
//               excluir ou consultar.
//Retorno   : Nenhum.
void escolhaUmaTeste(Teste *resultados, int cont, int finalidade)
{
    int numEscolhido(int, int*);
    int escolha;
    
    escolha=listarTeste(resultados, cont, (!finalidade) ? 4 : finalidade);
    if(!escolha)
        return;
    textbackground(BLACK);
      
    if(finalidade)
         (finalidade == 2)? alteracaoTeste(resultados[escolha - 1]): exclusaoTeste(resultados[escolha - 1]);
    else
    if(cont)
    {
        limpaArea( 2, 5, 78, 20);
        apresentaInfo(NULL, NULL, resultados + (escolha - 1), "DADOS ENCONTRADOS DESTE TESTE");
        imprimeMsg("[Pressione qualquer tecla para continuar]", 3, 18, WHITE, BLACK);
        getch();
    } 
}    
//------------------------------------------------------------------------------
//Objetivo  : Ler uma data.
//Parâmetros: Ponteiro da data a ser lida e data anterior.
//Retorno   : 0 em caso de cancelamento e 1 caso bem sucedida.
int lerData(long int *data, long int dataAnterior)
{
     int validaData(int, int, int);
     int dia, mes, ano, local = (!dataAnterior)? 24 : 50;
     int retorno;
     char strDia[3], strMes[3], strAno[5];
     do
     {
         if(!escrevaLimitado(local, local, 10, 2, 3, 2, strDia, 0))
            return 0;
         dia = atoi(strDia);
         if(!escrevaLimitado(local + 3, local + 3, 10, 2, 3, 2, strMes, 0))
            return 0;
         mes = atoi(strMes);     
         if(!escrevaLimitado(local + 6, local + 6, 10, 4, 5, 4, strAno, 0))
            return 0;
         ano = atoi(strAno);
         *data = ano * 10000 + mes * 100 + dia;
         if(!(retorno = validaData(dia, mes, ano)))
         {
             mostraMsgErro("Data invalida!         ", local + 1, 10, 2, 1);
             limpaArea(local + 4, 10, 2, 1);
             limpaArea(local + 7, 10, 4, 1);
         }
         else if((*data < dataAnterior) && (dataAnterior))
         {
             mostraMsgErro("Data abaixo da inicial!", local + 1, 10, 2, 1);
             limpaArea(local + 4, 10, 2, 1);
             limpaArea(local + 7, 10, 4, 1);
             retorno = 0;
         }
         else
             limpaArea(48, 25, 28, 1);
     }while(!retorno);
     return 1;
}
//------------------------------------------------------------------------------
//Objetivo  : Validar uma data.
//Parâmetros: Dia, mes e ano.
//Retorno   : 0 em caso de data inválida e 1 para data válida.
int validaData(int dia, int mes, int ano)
{
    int retorno=1;    
    if(ano < 0 || mes < 1 || mes > 12 || dia > 31 || dia < 1)
       return 0;          
    switch(mes)
    {
       case 4:
       case 6:
       case 9:
       case 11:
            if(dia > 30)
               retorno = 0;
            break;
       case 2:
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
//------------------------------------------------------------------------------
//Objetivo  : Ler uma velocidade.
//Parâmetros: Ponteiro da velocidade min a ser lida e velocidade max.
//Retorno   : 0 em caso de cancelamento e 1 caso bem sucedida.
int lerVelocidade(int *max, int min)
{
    int local = (!min)? 24 : 51, inferior;
    char temp[TAM_CODIGO];
    do
    {
         sprintf(temp, "%d", *max);             
         if(!(escrevaLimitado(local, local, 10, 3, 5, 4, temp, 0)))
             return 0;
             
         *max = atof(temp);
         if((*max <= 526) || (*max >= 1021))
         {        
             mostraMsgErro("Velocidade invalida!         ", local + 1, 10, 4, 1);
             inferior = 0;
         }
         else if((*max < min) && (min))
         {
             mostraMsgErro("Velocidade abaixo da inicial!", local + 1, 10, 4, 1);
             inferior = 0;
         } 
         else{
             limpaArea(48, 25, 31, 1); 
             inferior=1;
         } 
    }while(inferior!=1);
    return 1;
}
//------------------------------------------------------------------------------
//Objetivo  : Realocar lista de Testes na memória.
//Parâmetros: Lista de Testes, nova quantidade para ser realocada.
//Retorno   : Sucesso da operação.
int realocarTeste(Teste **resultados, int qnt)
{
     Teste *auxResult;
     
     if(!(auxResult = (Teste *) realloc(*resultados, (qnt + 1) * sizeof(Teste))))
     {
         printf("Erro ao alocar memoria!");
         getch();
         return 0;
     }
     *resultados = auxResult;
     return 1;
}
//------------------------------------------------------------------------------
//Objetivo  : Ordenar alfabeticamente os nomes des testes de uma pesquisa.
//Parâmetros: Ponteiro de uma struct com os testes e numero de testes.
//Retorno   : Nenhum.
void ordenaResultadosTeste(Teste *registro, int cont)
{
     int aux, list;
     Teste troca;
     for(aux = 0; aux < cont - 1; aux ++)
         for(list = aux + 1; list < cont; list++)
                  if(registro[aux].codigoPista == registro[list].codigoPista)
                  {
                       troca = registro[aux];
                       registro[aux] = registro[list];
                       registro[list] = troca;
                  }
}
//------------------------------------------------------------------------------
//Objetivo  : Ler o identificador.
//Parâmetros: Identificador a ser informado.
//Retorno   : Retorna falso em caso de desistência da leitura ou 1 caso bem sucedida.
int lerIdentificadorTeste(int *identificador)
{
    char temp[TAM_TEXT];
// Instruções
    do
    {
        sprintf(temp, "%d", *identificador);  
        if(!(escrevaLimitado( 2, 2, 10, 1, 6, 5, temp, 0))){
            return 0;
         }
         *identificador = atof(temp);
         if(*identificador <= 0)
         {
            mostraMsgErro ("Codigo invalido!", 3, 10, 10, 1); //COL|LIN|BASE|ALTURA
         }
         else
           limpaArea(48, 25, 28, 1);
    }while(*identificador <= 0);
    return 1;
}
//------------------------------------------------------------------------------
//Objetivo  : Alterar os dados de um teste já cadastrado.
//Parâmetros: Struct com informações do teste a alterar.
//Retorno   : Nenhum.
void alteracaoTeste(Teste alterar)
{
     int registro, qntTeste;
     Teste listar, alterado;
     FILE *arq;
     
     encontraNumRegistroTeste(alterar.codigoTeste, &registro);
     
     contaRegistrosTeste(&qntTeste);
     arq = abreArquivo(ARQ_TESTE, "rb", "Erro ao abrir arquivo de Teste.");
     fseek(arq, (registro - 1) * sizeof(Teste), SEEK_SET);
     if(!leArquivo(&listar, sizeof(Teste), 1, arq))
     {
         fechaArquivo(arq);
         return;
     }
     fechaArquivo(arq);
     alterarTeste(&listar);
     // Diference - Return = dados int, not [:(] char like another
     alterado = listar;
     
     atualizaVelocidadePista(alterado);
     
     arq = abreArquivo(ARQ_TESTE, "rb+", "Erro ao abrir arquivo de Teste.");
     fseek(arq, (registro - 1) * sizeof(Teste), SEEK_SET);
     if(!escreveArquivo(&alterado, sizeof(Teste), 1, arq))
        return;
     fechaArquivo(arq);
     apresentaMsg("Teste alterado com sucesso!", 20 , 10, WHITE);
     getch();
}
//------------------------------------------------------------------------------
//Objetivo  : Montar a tela para alterar os dados do teste e ler os novos dados.
//Parâmetros: Dados do teste a ser alterado.
//Retorno   : Nenhum.
void alterarTeste(Teste *alterar)
{
     int opcao, retorno;
     char temporario[TAM_TEXT];
     do
     {
         clrscr();
         telaCadastroTeste(1);
         
         textcolor(YELLOW);    
         obtemDataHoraAtual(&alterar->dia, &alterar->mes, &alterar->ano, &alterar->hora, &alterar->minuto);
         gotoxy(57, 10);
         printf("%02d/%02d/%d - %02d:%02d", alterar->dia, alterar->mes, alterar->ano, alterar->hora, alterar->minuto);
         
         imprimeMsg(alterar->codigoAviao, 3, 10, DARKGRAY, BLACK);
         textcolor(DARKGRAY);
         gotoxy( 28, 10);
		 printf("%d",alterar->codigoPista);
		 textcolor(YELLOW);
         gotoxy(56, 14);
		 printf("%d",alterar->velocidadeMax);
             
         if(!(retorno = lerValidaVelocidadeMax(&alterar->velocidadeMax, temporario, 1)))
             opcao = 1;
         else
         {
             imprimeMsg("Os dados estao corretos? (S/N) : ", 4, 23, WHITE, BLACK);
             opcao = lerOpcao(37, 23);
         }
     }while(!opcao);
}
//------------------------------------------------------------------------------
//Objetivo  : Excluir uma teste cadastrada dos registros.
//Parâmetros: Teste a ser excluído.
//Retorno   : Nenhum.
void exclusaoTeste(Teste resultado)
{  
     FILE *temp, *arquivo, *teste;
     int registro, aux = 0, existe = 0, qtdeTeste, i=0;
     Teste estrutura;
     void removeVelocidadePista(Teste pesquisa);

     limpaArea(2, 5, 78, 20);

     apresentaInfo( NULL, NULL, &resultado, "ATENCAO! TESTE SUJEITO A EXCLUSAO!");
     imprimeMsg("Tem certeza que deseja excluir este Teste? (S / N) : ", 3, 18, WHITE, BLACK);
     if(lerOpcao(56, 18))
     {               
         encontraNumRegistroTeste(resultado.codigoTeste, &registro);
         
         contaRegistrosTeste(&qtdeTeste);
         temp = abreArquivo("temp", "wb","Erro ao abrir o arquivo temporario");
         arquivo = abreArquivo(ARQ_TESTE, "rb","Erro ao abrir o arquivo de Teste");
         while(aux < qtdeTeste)
         {   
                if(leArquivo(&estrutura, sizeof(Teste), 1, arquivo))
                {
                    aux++;            
                    if(aux != registro)
                        escreveArquivo(&estrutura, sizeof(Teste), 1, temp);
                        //break;
                    else
                        removeVelocidadePista(estrutura);
			    }   
                else
                {
                    fechaArquivo(arquivo);
                    fechaArquivo(temp);
                    return;
                }
         }
         fechaArquivo(arquivo);
         fechaArquivo(temp);
         if(removeArquivo(ARQ_TESTE))
            return;   
         if(renomeiaArquivo("temp", ARQ_TESTE))
            return;   
         apresentaMsg("Teste excluido com sucesso!", 20 , 12, WHITE);
         getch();
     }
}
//------------------------------------------------------------------------------
//Objetivo  : Remove a velocidade de pista em um texto excluido a struct pista.
//Parâmetros: Struct com informações de testes a alterar na struct pistas.
//Retorno   : Nenhum.
void removeVelocidadePista(Teste pesquisa)
{
     int registro, aux, velocidadeMin;
     Pista alterar, alterado;
     FILE *arq;
     int buscaVelocidadeMin(Teste busca);

     velocidadeMin=buscaVelocidadeMin(pesquisa);
     
     encontraNumRegistroPista(pesquisa.codigoPista, &registro);
     
	 arq = abreArquivo(ARQ_PISTA, "rb", "Erro ao abrir arquivo de pista.");
     fseek(arq, (registro-1) * sizeof(Pista), SEEK_SET);
     if(!leArquivo(&alterar, sizeof(Pista), 1, arq))
     {
         fechaArquivo(arq);
         return;
     }
     fechaArquivo(arq);
     	
	 if(velocidadeMin!=0){
         aux=alterar.velocidade - velocidadeMin;
         alterar.velocidade = (alterar.velocidade - aux);
     }  
     alterado = alterar;   
        
     arq = abreArquivo(ARQ_PISTA, "rb+", "Erro ao abrir arquivo de pista.");
     fseek(arq, (registro-1) * sizeof(Pista), SEEK_SET);
     if(!escreveArquivo(&alterado, sizeof(Pista), 1, arq))
        return;
     fechaArquivo(arq);
}
//------------------------------------------------------------------------------
//Objetivo  : Verifica a velocidade cadastrada em uma pista no aquivo de teste..
//Parâmetros: Ponteiro do identificador a ser verificado.
//Retorno   : 0 em caso de erro na manipulação dos arquivos e 1 caso bem sucedida.
int buscaVelocidadeMin(Teste busca)
{
   FILE *arq;
   int qnt, aux = 0, time=0, velocidadeAux;
   Teste ler;
   
   contaRegistrosTeste(&qnt);
   arq = abreArquivo(ARQ_TESTE, "rb", "Erro ao abrir arquivo de testes.");
   do
   {
        if(!leArquivo(&ler, sizeof(Teste), 1, arq))
        {
             fechaArquivo(arq);
             return 0;
        }
        if(busca.codigoPista == ler.codigoPista)
        {
        	if(time==0)
    	        if((busca.velocidadeMax >= ler.velocidadeMax) && (busca.codigoTeste != ler.codigoTeste)){ // Verifica se existe algum teste com velocidade menor
    		        velocidadeAux = ler.velocidadeMax;
    		        time=1;
				}
			if((busca.velocidadeMax <= ler.velocidadeMax)  && (busca.codigoTeste != ler.codigoTeste)){ // Verifica se existe algum teste com velocidade maior
    		   time=2;
			}
			if(time==1)
			    if((busca.velocidadeMax >= ler.velocidadeMax) && (velocidadeAux <= ler.velocidadeMax) && (busca.codigoTeste != ler.codigoTeste)){
				    velocidadeAux = ler.velocidadeMax;      
				}       
        }  
        aux++;
   }while(aux < qnt); 
	 
   if(time==0)
       velocidadeAux=527;
   if(time==2)
       velocidadeAux=0;	   
	   
   fechaArquivo(arq);
   return velocidadeAux;
}
//------------------------------------------------------------------------------
//Objetivo  : Relacionar o numero atribuido a uma Teste numa pesquisa por identificador
//              e a sua posição no registro do arquivo de Teste para alteção ou exclusão.
//Parâmetros: Identificador de Teste e posição no arquivo.
//Retorno   : Nenhum.
void encontraNumRegistroTeste(int identificador, int *registro)
{
     FILE *arq;
     Teste verificar;
     int aux = 0, qnt;

     contaRegistrosTeste(&qnt);     
     arq = abreArquivo(ARQ_TESTE, "rb","Erro ao abrir o arquivo de Teste");
     do
     {
          if(fread(&verificar, sizeof(Teste), 1, arq))
              aux++;
     }while((aux<qnt) && (verificar.codigoTeste != identificador));
	 *registro = aux;
     fechaArquivo(arq);
}
