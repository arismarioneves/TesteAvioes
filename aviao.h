//================= FUNÇÕES MANIPULAR AVIÕES ===============================

int listarAviao(Aviao *lista, int qtdeRegistros, int finalidade);
void contaRegistrosAviao(int *qtde);            
void centralPesquisaAviao(int finalidade);
int realocarAviao(Aviao **resultados, int qtde);
void escolhaUmAviao(Aviao *resultados, int qtde, int finalidade);
void alterarAviao(Aviao *alterar);
void alteracaoAviao(Aviao alterar);
void exclusaoAviao(Aviao resultado);
void encontraNumRegistroAviao(char *identificador, int *registro);                        
void ordenaResultadosAviao(Aviao *registro, int qtde);
void apresentaInfo(Aviao *dadoAviao, Pista *dadoPista, Teste *dadoTeste, char *msg);
void contaRegistrosTeste(int *);

//------------------------------------------------------------------------------
//Objetivo  : Listar aviões cadastrados de acordo com a finalidade.
//Parâmetros: Lista de aviões, quantidade de registros e finalidade
//            exclusão, consulta, alteração ou outros relatórios.
//Retorno   : Nenhum.
int listarAviao(Aviao *listar, int qtdeRegistros, int finalidade)
{
//Declarações
    FILE *arquivo;
    Aviao lista;
    char **dados=NULL, aux[7];
    int linha,cont=0,i,qtde=0,itemSelecionado=0,qtdeAlocada=0,existeErro=0,selecao=0,opcao=0;
    int comparaNomeAviao(const void * p1, const void *p2);
    void telaListarAviao(int);
    char temp[TAM_TEXT];
// Instruções
    telaListarAviao(finalidade);
    gotoxy(20,10);
   
    if(finalidade)
    {        
       if(qtdeRegistros != 0)
       {
       	
       	   // Ordena os dados dos aviões por modelo
           qsort(listar,qtdeRegistros,sizeof(Aviao),comparaNomeAviao);
         
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
                 
	    	              sprintf(dados[i],"#%d\t%-14.14s\t\t%-3.3d\t%-7.7s\t %-29.29s", i+1, listar[i].modelo,  listar[i].capacidade,
                              listar[i].codigoAviao, listar[i].cliente.nome);    					  					 
					  qtdeAlocada++;                     
                   }
                   else
                   {
                       imprimeMsg("Erro de alocação.", 17, 14, LIGHTRED, BLACK);
                       existeErro = 1;
                   }
                }    
           }
           else
           {
               imprimeMsg("Erro de alocação.", 17, 14, LIGHTRED, BLACK);
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
       	  sprintf(temp,"Nenhum avi%co foi cadastrado!",198);
       	  printf(temp);
          getch();
	  }
   }
   else 
   {
         linha = 8;
         contaRegistrosAviao(&qtdeRegistros);
         
         // ordena os dados dos aviões por nome
         //qsort(lista,qtdeRegistros,sizeof(Aviao),comparaNomeAviao);
         
         if(qtdeRegistros)
         {
             arquivo = abreArquivo(ARQ_AVIAO, "rb", "Erro ao abrir o arquivo de Aviao");
             while(qtde < qtdeRegistros)
             {
                  if(leArquivo(&lista, sizeof(Aviao), 1, arquivo))
                  {
                      gotoxy(3,24);
                      textcolor(BLACK);
                      textbackground(GREEN);
                      printf("[Apresentando %d de %d]", qtde + 1 ,qtdeRegistros);
                      gotoxy(3, linha);
                      textbackground((qtde % 2)? WHITE: LIGHTGRAY);   
                      
	
					  printf("%-14.14s\t%-3.3d\t%-8.8s\t%-14.14s\t%-14.14s", lista.modelo, lista.capacidade,
                          lista.codigoAviao, lista.cliente.nome, lista.cliente.pais);
		
		
                      linha++;
                      qtde++;
                      if(!(qtde % 16) && (qtde != qtdeRegistros))
                      {
                         getch();    
                         telaListarAviao(0);
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
              gotoxy (22,10);
         	  sprintf(temp,"Nenhum avi%co foi cadastrado!",198);
              printf(temp);

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
int comparaNomeAviao(const void * p1, const void *p2)
{
Aviao *aviao1,*aviao2;

  aviao1 = (Aviao*)p1;
  aviao2 = (Aviao*)p2;
  return stricmp((*aviao1).cliente.nome,(*aviao2).cliente.nome); 
}
//------------------------------------------------------------------------------
//Objetivo  : Monta a tela para o apresenta os aviões.
//Parâmetros: Finalidade exclusão, alteração ou consulta.
//Retorno   : Nenhum.
void telaListarAviao(int finalidade)
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
         fazBorda(38, 1, 24, 2, 0);
         gotoxy(27, 3);
     }
     else
     {
         fazBorda(52, 1, 14, 2, 0);
         gotoxy(17, 3);
     }
     printf("LISTA DE AVIOES ENCONTRADOS %s", (!finalidade)? "" : (finalidade == 1)? "PARA EXCLUSAO" : (finalidade == 2) ? "PARA ALTERACAO" : "PARA CONSULTA");
     gotoxy(3, 6);
     textcolor(YELLOW);
     if((finalidade < 1) || (finalidade >= 3) && (finalidade != 4))
		printf("MODELO\t CAPACIDADE\tCODIGO\t\tCLIENTE\t\tPAIS");
     else
        printf("REG\tMODELO\t\t CAPACIDADE\tCODIGO\t CLIENTE");
	 textcolor(WHITE);
     gotoxy(3, 7);
     printf("----------------------------------------------------------------------------");
}
//------------------------------------------------------------------------------
//Objetivo  : Conta quantos registros de aviões ja foram feitos.
//Parâmetros: Quantidade que será informada.
//Retorno   : Nenhum.
void contaRegistrosAviao(int *qtde)
{
     FILE *arquivo;
     Aviao ler;
     *qtde = 0;
     arquivo = abreArquivo(ARQ_AVIAO, "rb","Erro ao abrir o arquivo de Aviao");
     while(fread(&ler, sizeof(Aviao), 1, arquivo))
             (*qtde)++;
     fechaArquivo(arquivo);
}
//------------------------------------------------------------------------------
//Objetivo  : Consultar aviões existente.
//Parâmetros: Finalidade: consulta, alteração ou exclusão.
//Retorno   : Nenhum.
void centralPesquisaAviao(int finalidade)
{
//================= PROTÓTIPOS DAS FUNÇÕES =====================================
     void telaConsultaAviao(int);
     void pesquisaCodigoAviao(int);
     void pesquisaNomeAviao(int);
    // Declarações
     char *opcoesConsulta[2] = {"Consulta por Cliente",
                                "Voltar"};
     char *opcoesExclusao[2] = {"Exclusao por Cliente",
                                "Voltar"};
     char *opcoesAlteracao[2] = {"Alteracao por Cliente",
                                 "Voltar"};                                
     int opcao;
// Instruções
     do  
     {
     	 textbackground(BLACK);
         telaConsultaAviao(finalidade);
         gotoxy(27,10);
         
         opcao = menuVertical(1,(finalidade)? 2 :2,	 (finalidade == 1)? opcoesExclusao : (finalidade == 2) ? opcoesAlteracao : opcoesConsulta, 30);
                  
         limpaArea(27, 10, 42, 7);
         switch(opcao)
         {
              case 1:
                   pesquisaNomeAviao(finalidade); 
				   break;
              default:
                   return;   
         }
     }while(opcao != -1);
}
//------------------------------------------------------------------------------
//Objetivo  : Monta a tela para consulta do avião.
//Parâmetros: Finalidade de alteração, exclusão ou consulta.
//Retorno   : Nenhum.
void telaConsultaAviao(int finalidade)
{
     textcolor(WHITE);
     clrscr();
     textcolor(LIGHTGRAY);
     fazBorda(78, 27, 1, 1, 1); //X_X_X_X_1 - 1= Limpar área da tabela
     textcolor(WHITE);
     fazBorda(27, 1, 25, 2, 0);
     gotoxy(27, 3);
     printf("%s DE AVIOES", (finalidade == 1)? "EXCLUSAO" : (finalidade == 2)? "ALTERACAO" : "CONSULTA");
}
//------------------------------------------------------------------------------
//Objetivo  : Consultar avião por cliente.
//Parâmetros: Finalidade da pesquisa. 2 para alteração, 1 para exclusao e 0 para pesquisa.
//Retorno   : Nenhum.
void pesquisaNomeAviao(int finalidade)
{
     FILE *arquivo;
     char nome[MAX_NOME];
     int aux = 0, cont = 0, qtdeResult = 0, qtdeRegistro;
     Aviao verificar, *resultados = NULL;
     
     fazBorda(76, 1, 2, 10, 0);
     gotoxy(2,9);
     printf("Digite o Cliente dos avioes que deseja %s:", (finalidade == 1)? "excluir" : (finalidade == 2)? "alterar" : "consultar");
     textcolor(YELLOW);
     if(!(escrevaLimitado(2, 2, 11, 1, MAX_NOME, MAX_NOME - 1, nome, 0)))
                 return;
     contaRegistrosAviao(&qtdeRegistro);
     arquivo = abreArquivo(ARQ_AVIAO, "rb","Erro ao abrir o arquivo de Aviao");
     for(aux = 0; aux < qtdeRegistro; aux++)
     {
             if(!leArquivo(&verificar, sizeof(Aviao), 1, arquivo))
             {
                 fechaArquivo(arquivo);
                 return;
             }
             if(!strStr(verificar.cliente.nome, nome))
                continue;
             if(!realocarAviao(&resultados, qtdeResult))
                break;
             resultados[qtdeResult] = verificar;
             qtdeResult++;
     }
     fechaArquivo(arquivo);
     if(qtdeResult)
     {
          ordenaResultadosAviao(resultados, qtdeResult);
          escolhaUmAviao(resultados, qtdeResult, finalidade);
     }
     free(resultados);
     if(!qtdeResult){
         imprimeMsg("Nao foi encontrado nenhum registro correspondente.", 17, 14, LIGHTRED, BLACK);
         getch();
     }
}
//------------------------------------------------------------------------------
//Objetivo  : Ordenar alfabeticamente os nomes dos aviões de uma pesquisa pelo 
//            método da bolha.
//Parâmetros: Ponteiro de uma struct com os modelos e numero de Avião.
//Retorno   : Nenhum.
void ordenaResultadosAviao(Aviao *registro, int qtde)
{
    int aux, cont;
    Aviao troca;
    
    for(aux = 0; aux < cont - 1; aux ++)
        for(cont = aux + 1; cont < qtde; cont++)
            if(strcmp(registro[aux].modelo, registro[cont].modelo) > 0)
            {
                troca = registro[aux];
                registro[aux] = registro[cont];
                registro[cont] = troca;
            }
}
//------------------------------------------------------------------------------
//Objetivo  : Realocar lista de aviões na memória.
//Parâmetros: Lista de aviões, nova quantidade para ser realocada.
//Retorno   : Sucesso da operação.
int realocarAviao(Aviao **resultados, int qtde)
{
     Aviao *auxResult;
     
     if(!(auxResult = (Aviao *) realloc(*resultados, (qtde + 1) * sizeof(Aviao))))
     {
         printf("Erro ao alocar memoria!");
         getch();
         return 0;
     }
     *resultados = auxResult;
     return 1;
}
//------------------------------------------------------------------------------
//Objetivo  : Alterar ou excluir o registro especificado dentro de uma pesquisa.
//Parâmetros: Aviaos que se enquadram na pesquisa, numero de resultados
//            e finalidade alterar, excluir ou consultar.
//Retorno   : Nenhum.
void escolhaUmAviao(Aviao *resultados, int qtde, int finalidade)
{
     int numEscolhido(int, int*);
     int escolha;

     escolha=listarAviao(resultados, qtde, (!finalidade) ? 4 : finalidade);
     if(!escolha)
         return;
     textbackground(BLACK);
     
     if(finalidade == 2 || finalidade == 1)
        (finalidade == 2)? alteracaoAviao(resultados[escolha - 1]): exclusaoAviao(resultados[escolha - 1]);
     else
        if(qtde)
        {   
            limpaArea(2, 5, 78, 20);
            apresentaInfo(resultados + (escolha - 1), NULL, NULL, "DADOS ENCONTRADOS DESTE AVIAO");
            imprimeMsg("[Pressione qualquer tecla para continuar]", 3, 18, WHITE, BLACK);
            getch();
        }
}
//------------------------------------------------------------------------------
//Objetivo  : Alterar os dados de um avião já cadastrado.
//Parâmetros: Struct com informações do avião a alterar.
//Retorno   : Nenhum.
void alteracaoAviao(Aviao alterar)
{
     int registro, qtdeAviao;
     Aviao listar, alterado;
     FILE *arquivo;
     
     encontraNumRegistroAviao(alterar.codigoAviao, &registro);
     contaRegistrosAviao(&qtdeAviao);
     arquivo = abreArquivo(ARQ_AVIAO, "rb", "Erro ao abrir arquivo de Aviao.");
     fseek(arquivo, (registro - 1) * sizeof(Aviao), SEEK_SET);
     if(!leArquivo(&listar, sizeof(Aviao), 1, arquivo))
     {
         fechaArquivo(arquivo);
         return;
     }
     fechaArquivo(arquivo);
     alterarAviao(&listar);
     if(!listar.modelo[0])
          return;
     alterado = listar;
     arquivo = abreArquivo(ARQ_AVIAO, "rb+", "Erro ao abrir arquivo de Aviao.");
     fseek(arquivo, (registro - 1) * sizeof(Aviao), SEEK_SET);
     if(!escreveArquivo(&alterado, sizeof(Aviao), 1, arquivo))
        return;
     fechaArquivo(arquivo);
	 apresentaMsg("Aviao alterado com sucesso!", 20 , 10, WHITE);
     getch();
}
//------------------------------------------------------------------------------
//Objetivo  : Montar a tela para alterar os dados do avião e ler os novos dados.
//Parâmetros: Dados do avião a ser alterado.
//Retorno   : Nenhum.
void alterarAviao(Aviao *alterar)
{
     int opcao, retorno;
     char temporario[TAM_TEXT];   
     do
     {         
         clrscr();
		 telaCadastroAviao(2);
         imprimeMsg(alterar->modelo, 3, 7, YELLOW, BLACK);	
         imprimeMsg(alterar->codigoAviao, 28, 11, DARKGRAY, BLACK);
         imprimeMsg(alterar->cliente.nome, 3, 15, YELLOW, BLACK);     
         imprimeMsg(alterar->cliente.pais, 3, 19,YELLOW, BLACK);
         
         textcolor(YELLOW);
         gotoxy( 3, 11);
		 printf("%-3d",alterar->capacidade);
         
         if(retorno = escrevaLimitado(strlen(alterar->modelo) + 2, strlen(alterar->modelo) + 2, 7, 1, MAX_NOME, MAX_NOME - 1, alterar->modelo, strlen(alterar->modelo)))
		     if(retorno = lerValidaCapacidade(&alterar->capacidade, temporario, 1)){
    			 if(retorno = escrevaLimitado(strlen(alterar->cliente.nome) + 2, strlen(alterar->cliente.nome) + 2, 15, 1, MAX_NOME, MAX_NOME - 1, alterar->cliente.nome, strlen(alterar->cliente.nome)))
    		         retorno = selecionaPais(alterar->cliente.pais);
	         }

         if(!retorno)
         {
            alterar->modelo[0] = '\0';
            opcao = 1;
         }
         else
         {
             imprimeMsg("Os dados estao corretos? (S/N) : ", 45, 23, WHITE, BLACK);
             opcao = lerOpcao(78, 23);
         }
     }while(!opcao);
}
//------------------------------------------------------------------------------
//Objetivo  : Excluir um avião cadastrado dos registros.
//Parâmetros: Aviao a ser excluído.
//Retorno   : Nenhum.
void exclusaoAviao(Aviao resultado)
{  
     FILE *temp, *arquivo, *teste;
     int registro, aux = 0, existe = 0, qtdeTeste, qtdeAviao;
     Aviao estrutura;
     Teste listar;
     
     contaRegistrosTeste(&qtdeTeste);
     teste = abreArquivo(ARQ_TESTE, "rb", "Erro ao abrir arquivo de testes.");
     while((aux < qtdeTeste)&& !existe)
     {
         if(leArquivo(&listar, sizeof(Teste), 1, teste)){
             existe = (!strcmp(listar.codigoAviao,resultado.codigoAviao)) ? 1 : 0;
         }else
         {
             fechaArquivo(teste);
             return;
         } 
         aux++;
     }
     fechaArquivo(teste);

     aux = 0;                
     if(existe)
     {
        textcolor(YELLOW);
        apresentaMsg("Exclusao nao pode ser realizada.", 20, 12, LIGHTRED);
        getch();
        return;
     }
     
     limpaArea(2, 5, 78, 20);
     apresentaInfo(&resultado, NULL, NULL, "ATENCAO! AVIAO SUJEITO A EXCLUSAO!");
     imprimeMsg("Tem certeza que deseja excluir este Aviao? (S / N) : ", 3, 18, WHITE, BLACK);
     if(lerOpcao(57, 18))
     {
         encontraNumRegistroAviao(resultado.codigoAviao, &registro);
         contaRegistrosAviao(&qtdeAviao);
         temp = abreArquivo("temp", "wb","Erro ao abrir o arquivo temporario");
         arquivo = abreArquivo(ARQ_AVIAO, "rb","Erro ao abrir o arquivo de Aviao");
         while(aux < qtdeAviao)
         {   
                if(leArquivo(&estrutura, sizeof(Aviao), 1, arquivo))
                {
                    aux++;            
                    if(aux != registro)
                       if(!escreveArquivo(&estrutura, sizeof(Aviao), 1, temp))
                            break;
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
         if(removeArquivo(ARQ_AVIAO))
            return;   
         if(renomeiaArquivo("temp", ARQ_AVIAO))
            return;   
         apresentaMsg("Aviao excluido com sucesso!", 20 , 12, WHITE);
         getch();
     }
}
//------------------------------------------------------------------------------
//Objetivo  : Relacionar o numero atribuido a um avião numa pesquisa pelo ID
//              e a sua posição no registro do arquivo de aviões para alteção ou exclusão.
//Parâmetros: ID do avião e a sua posição no arquivo.
//Retorno   : Nenhum.
void encontraNumRegistroAviao(char *identificador, int *registro)
{
     FILE *arq;
     Aviao verificar;
     int aux = 0;
     
     arq = abreArquivo(ARQ_AVIAO, "rb","Erro ao abrir o arquivo de avioes");
     do
     {
          if(fread(&verificar, sizeof(Aviao), 1, arq))
              aux++;
     }while((!feof (arq)) && (strcmp(verificar.codigoAviao, identificador)));
     *registro = aux;
     fechaArquivo(arq);
}
