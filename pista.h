//================= FUNÇÕES MANIPULAR PISTA ====================================

int listarPista(Pista *lista, int qtdeRegistros, int finalidade);
void contaRegistrosPista(int *);
void centralPesquisaPista(int finalidade);
int realocarPista(Pista **resultados, int qnt);
void escolhaUmaPista(Pista *resultados, int cont, int finalidade);
void alteracaoPista(Pista alterar);
void alterarPista(Pista *alterar);
void exclusaoPista(Pista resultado);
void encontraNumRegistroPista(int codigo, int *registro);
void apresentaInfo(Aviao *dadoAviao, Pista *dadoPista, Teste *dadoTeste, char *msg);

//------------------------------------------------------------------------------
//Objetivo  : Listar pistas cadastradas de acordo com a finalidade.
//Parâmetros: Lista de pistas, quantidade de registros e finalidade
//            exclusão, consulta, alteração ou outros relatórios.
//Retorno   : Nenhum.
int listarPista(Pista *listar, int qtdeRegistros, int finalidade)
{
//Declarações
    FILE *arquivo;
    Pista lista;
    char **dados=NULL, aux[7];
    int linha,cont=0,i,qtde=0,itemSelecionado=0,qtdeAlocada=0,existeErro=0,selecao=0,opcao=0;
    int comparaEnderecoPista(const void * p1, const void *p2);
    void telaListarPista(int);
// Instruções
    telaListarPista(finalidade);
    gotoxy(20,10);
   
    if(finalidade)
    {     
       if(qtdeRegistros != 0)
       {
       	   // Ordena os dados das pistas por endereço
           qsort(listar,qtdeRegistros,sizeof(Pista),comparaEnderecoPista);
         
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
                          
                          sprintf(dados[i],"#%-4.d %-20.20s\t%7d\t%-2.2s\t  %10.d    %14.2f", i+1, listar[i].endereco, listar[i].codigoPista,
                              listar[i].UF, listar[i].velocidade, listar[i].circuito);	
	 
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
          printf("Nenhuma pista foi cadastrada.");
          getch();
	  }
   }
   else 
   {
         linha = 8;
         contaRegistrosPista(&qtdeRegistros);
         if(qtdeRegistros)
         {
             arquivo = abreArquivo(ARQ_PISTA, "rb", "Erro ao abrir o arquivo de Pista");
             while(qtde < qtdeRegistros)
             {
                  if(leArquivo(&lista, sizeof(Pista), 1, arquivo))
                  {
                      gotoxy(3,24);
                      textcolor(BLACK);
                      textbackground(GREEN);
                      printf("[Apresentando %d de %d]", qtde + 1 ,qtdeRegistros);
                      gotoxy(3, linha);
                      textbackground((qtde % 2)? WHITE: LIGHTGRAY);
                      printf("%-20.20s\t%12.12s\t%6.d\t%2.2s  %10.d    %12.2f", lista.endereco, lista.codigoAviao, lista.codigoPista,
                              lista.UF, lista.velocidade, lista.circuito);   
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
             printf("Nenhuma pista foi cadastrada.");
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
int comparaEnderecoPista(const void * p1, const void *p2)
{
Pista *pista1,*pista2;

  pista1 = (Pista*)p1;
  pista2 = (Pista*)p2;
  return stricmp((*pista1).UF,(*pista2).UF); 
}
//------------------------------------------------------------------------------
//Objetivo  : Monta a tela para listar as pistas.
//Parâmetros: Finalidade exclusão, alteração ou consulta.
//Retorno   : Nenhum.
void telaListarPista(int finalidade)
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
     printf("LISTA DE PISTAS ENCONTRADAS %s", (!finalidade)? "" : (finalidade == 1)? "PARA EXCLUSAO" : (finalidade == 2) ? "PARA ALTERACAO" : "PARA CONSULTA");
     gotoxy(3, 6);
     textcolor(YELLOW);
     
     if((finalidade < 1) || (finalidade >= 3) && (finalidade != 4))
     
        printf("%-20.20s\t%12.12s\t%6.6s\t%2.2s  %10.10s    %12.12s","ENDERECO","CODIGO AVIAO","CODIGO","UF","VELOCIDADE","TAM CIRCUITO");
     else
		printf("#%-5.5s%-21.21s\t%7.7s\t%2.2s\t  %10.10s    %14.12s","REG","ENDERECO","CODIGO","UF","VELOCIDADE","TAM CIRCUITO");       
	 textcolor(WHITE);
     gotoxy(3, 7);
     printf("----------------------------------------------------------------------------");
}
//------------------------------------------------------------------------------
//Objetivo  : Conta quantos registros de pistas ja foram feitos.
//Parâmetros: Quantidade que será informada.
//Retorno   : Nenhum.
void contaRegistrosPista(int *qnt)
{
     FILE *arq;
     Pista ler;
     *qnt = 0;
     arq = abreArquivo(ARQ_PISTA, "rb","Erro ao abrir o arquivo de pistas");
     while(fread(&ler, sizeof(Pista), 1, arq))
             (*qnt)++;
     fechaArquivo(arq);
}
//------------------------------------------------------------------------------
//Objetivo  : Consultar aviões existente.
//Parâmetros: Finalidade: consulta, alteração ou exclusão.
//Retorno   : Nenhum.
void centralPesquisaPista(int finalidade)
{
//================= PROTÓTIPOS DAS FUNÇÕES =====================================
     void telaConsultaPista(int);
     void pesquisaCodigoPista(int);
     void pesquisaEnderecoPista(int);
     int lerCodigoPista(int *);
    // Declarações
     char *opcoesConsulta[3] = {"Consulta por Codigo",
                                "Consulta por Endereco",
                                "Voltar"};
     char *opcoesExclusao[3] = {"Exclusao por Codigo",
                                "Exclusao por Endereco",
                                "Voltar"};
     char *opcoesAlteracao[3] = {"Alteracao por Codigo",
                                 "Alteracao por Endereco",
                                 "Voltar"};                                
     int opcao;
// Instruções
     do  
     {
     	 textbackground(BLACK);
         telaConsultaPista(finalidade);
         gotoxy(27,10);
         opcao = menuVertical(1,(finalidade)? 3 :3, (finalidade == 1)? opcoesExclusao : (finalidade == 2) ? opcoesAlteracao : opcoesConsulta, 40);
         limpaArea(27, 10, 42, 7);
         switch(opcao)
         {
              case 1: 
                   pesquisaCodigoPista(finalidade);
				   break;
              case 2:
                   pesquisaEnderecoPista(finalidade);   
                   break;
              default:
                   return;
         }
     }while(opcao != -1);
}
//------------------------------------------------------------------------------
//Objetivo  : Monta a tela para consulta do pistas.
//Parâmetros: Finalidade de alteração, exclusão ou consulta.
//Retorno   : Nenhum.
void telaConsultaPista(int finalidade)
{
     textcolor(WHITE);
     clrscr();
     textcolor(LIGHTGRAY);
     fazBorda(78, 27, 1, 1, 0);
     textcolor(WHITE);
     fazBorda(27, 1, 25, 2, 0);
     gotoxy(27, 3);
     printf("%s DE PISTA", (finalidade == 1)? "EXCLUSAO" : (finalidade == 2)? "ALTERACAO" : "CONSULTA");
}
//------------------------------------------------------------------------------
//Objetivo  : Consultar pista pelo identificador.
//Parâmetros: Finalidade, consulta, exclusão ou alteração.
//Retorno   : Nenhum.
void pesquisaCodigoPista(int finalidade)
{
     FILE *arquivo;
     int aux = 0, cont = 0, qtdeRegistro;
     int codigo;
     Pista resultadoPesquisa;
     int lerCodigoPista(int *);
     
     gotoxy(2,9);
     printf("Informe o codigo do pista que deseja %s: ", (finalidade == 1)? "excluir": (finalidade == 2)? "alterar" : "consultar");
     fazBorda(15, 1, 2, 10, 0);
	 //-----------------------------------------------------------
     textcolor(WHITE);
     fazBorda(76, 9, 2, 14, 0);
     gotoxy(3, 15);
     textcolor(YELLOW);
     printf("%-20.20s\t%12.12s\t%6.6s\t%2.2s\t%10.10s%12.12s","ENDERECO","CODIGO AVIAO","CODIGO","UF","VELOCIDADE","CIRCUITO");
     textcolor(WHITE);
     gotoxy(3, 16);
     printf("----------------------------------------------------------------------------");
 	 //-----------------------------------------------------------     
     textcolor(YELLOW);
     if(!lerCodigoPista(&codigo))
        return;
     gotoxy(3, 17);
     contaRegistrosPista(&qtdeRegistro);
     arquivo = abreArquivo(ARQ_PISTA, "rb","Erro ao abrir o arquivo de Pista");
     while(aux < qtdeRegistro)
     {      
          if(leArquivo(&resultadoPesquisa, sizeof(Pista), 1, arquivo))
          {
               if(resultadoPesquisa.codigoPista == codigo)
               {
                   cont++;
                   break;
               }
               aux++;
          }
          else
          {
              fechaArquivo(arquivo);
              return;
          }
     }
     fechaArquivo(arquivo);
     if(cont) 
     {
     //-----------------------------------------------------------	
        textbackground(WHITE);
        textcolor(BLACK);
        printf("%-20.20s\t%12.12s\t%6.d\t%2.2s\t%10.d%12.2f", resultadoPesquisa.endereco, resultadoPesquisa.codigoAviao, resultadoPesquisa.codigoPista,
                              resultadoPesquisa.UF, resultadoPesquisa.velocidade, resultadoPesquisa.circuito);
        textbackground(BLACK);	
        getch();
	 //-----------------------------------------------------------	
		//textcolor(BLACK);
        if(finalidade == 1)
           exclusaoPista(resultadoPesquisa);
        else if (finalidade == 2)
           alteracaoPista(resultadoPesquisa);
        else
        {
           apresentaInfo(NULL, &resultadoPesquisa, NULL, "DADOS ENCONTRADOS DESTA PISTA");
           imprimeMsg("[Pressione qualquer tecla para continuar]", 3, 18, WHITE, BLACK);
        }  
     }
     else
     {
         textcolor(LIGHTRED);
         gotoxy(13, wherey());
         printf("Nao foi encontrado nenhum registro correspondente.");
         if(finalidade != 0)
            getch();
     }
     if(!finalidade)
        getch();
}
//------------------------------------------------------------------------------
//Objetivo  : Consultar pista por endereço.
//Parâmetros: Finalidade da pesquisa. 2 para alteração, 1 para exclusao e 0 para pesquisa.
//Retorno   : Nenhum.
void pesquisaEnderecoPista(int finalidade)
{
     FILE *arq;
     char descricaoPista[MAX_NOME];
     int aux = 0, cont = 0, qntResult = 0, qntRegistro;
     Pista verificar, *resultados = NULL;
     
     fazBorda(76, 1, 2, 10, 0);
     gotoxy(2,9);
     printf("Digite a descricao da pista que deseja %s:", (finalidade == 1)? "excluir" : (finalidade == 2)? "alterar" : "consultar");
     textcolor(YELLOW);
     if(!(escrevaLimitado(2, 2, 11, 0, 76, MAX_NOME - 1, descricaoPista, 0)))
         return;
     contaRegistrosPista(&qntRegistro);
     arq = abreArquivo(ARQ_PISTA, "rb","Erro ao abrir o arquivo de pista");
     for(aux = 0; aux < qntRegistro; aux++)
     {
             if(!leArquivo(&verificar, sizeof(Pista), 1, arq))
             {
                 fechaArquivo(arq);
                 return;
             }
             if(!strStr(verificar.endereco, descricaoPista))
                continue;
             if(!realocarPista(&resultados, qntResult))
                break;
             resultados[qntResult] = verificar;
             qntResult++;
     }
     fechaArquivo(arq);
     if(qntResult)
         escolhaUmaPista(resultados, qntResult, finalidade);
     free(resultados);
     if(!qntResult){
         imprimeMsg("Nao foi encontrado nenhum registro correspondente.", 17, 14, LIGHTRED, BLACK);
         getch();
     }     
}
//------------------------------------------------------------------------------
//Objetivo  : Realocar lista de pistas na memória.
//Parâmetros: Lista de pistas, nova quantidade para ser realocada.
//Retorno   : Sucesso da operação.
int realocarPista(Pista **resultados, int qnt)
{
     Pista *auxResult;
     
     if(!(auxResult = (Pista *) realloc(*resultados, (qnt + 1) * sizeof(Pista))))
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
//Parâmetros: Moveis que se enquadram na pesquisa, numero de resultados e finalidade
//               alterar, excluir ou consultar.
//Retorno   : Nenhum.
void escolhaUmaPista(Pista *resultados, int cont, int finalidade)
{
     int numEscolhido(int, int*);
     int escolha;
    
     escolha=listarPista(resultados, cont, (!finalidade) ? 4 : finalidade);
     if(!escolha)
         return;
     textbackground(BLACK);
	 
     if(finalidade)
         (finalidade == 2)? alteracaoPista(resultados[escolha - 1]): exclusaoPista(resultados[escolha - 1]);
	 else
     	 if(cont)
     	 {
     	 	 limpaArea( 2, 5, 78, 20);
	         apresentaInfo(NULL, resultados + (escolha - 1), NULL, "DADOS ENCONTRADOS DESTA PISTA");
	         imprimeMsg("[Pressione qualquer tecla para continuar]", 3, 18, WHITE, BLACK);
	         getch();
	     }
}
//------------------------------------------------------------------------------
//Objetivo  : Alterar os dados de uma pista já cadastrado.
//Parâmetros: Struct com informações da pista a alterar.
//Retorno   : Nenhum.
void alteracaoPista(Pista alterar)
{
     int registro, qntPista;
     Pista listar, alterado;
     FILE *arq;
     
     encontraNumRegistroPista(alterar.codigoPista, &registro);
     
     contaRegistrosPista(&qntPista);
     arq = abreArquivo(ARQ_PISTA, "rb", "Erro ao abrir arquivo de pista.");
     fseek(arq, (registro - 1) * sizeof(Pista), SEEK_SET);
     if(!leArquivo(&listar, sizeof(Pista), 1, arq))
     {
         fechaArquivo(arq);
         return;
     }
     fechaArquivo(arq);
     alterarPista(&listar);
     if(!listar.endereco[0])
          return;
     alterado = listar;
     arq = abreArquivo(ARQ_PISTA, "rb+", "Erro ao abrir arquivo de pista.");
     fseek(arq, (registro - 1) * sizeof(Pista), SEEK_SET);
     if(!escreveArquivo(&alterado, sizeof(Pista), 1, arq))
        return;
     fechaArquivo(arq);
     apresentaMsg("Pista alterada com sucesso!", 20 , 10, WHITE);
     getch();
}
//------------------------------------------------------------------------------
//Objetivo  : Montar a tela para alterar os dados da pista e ler os novos dados.
//Parâmetros: Dados da pista a ser alterada.
//Retorno   : Nenhum.
void alterarPista(Pista *alterar)
{
     int opcao, retorno;
     char temporario[TAM_TEXT];
     do
     {
         clrscr();
         telaCadastroPista(1);
             
         imprimeMsg(alterar->endereco, 3, 7, YELLOW, BLACK);
         imprimeMsg(alterar->codigoAviao, 28, 11, DARKGRAY, BLACK);
         imprimeMsg(alterar->UF, 3, 15, YELLOW, BLACK);     
         textcolor(DARKGRAY);
         gotoxy( 3, 11);
		 printf("%d",alterar->codigoPista);
		 textcolor(YELLOW);
         gotoxy( 48, 15);
		 printf("%6.2f",alterar->circuito);
         gotoxy( 65, 15);
		 printf("%d",alterar->velocidade);
             
		 if(retorno = escrevaLimitado(strlen(alterar->endereco) + 2, strlen(alterar->endereco) + 2, 7, 1, MAX_NOME, MAX_NOME - 1, alterar->endereco, strlen(alterar->endereco)))
               if(retorno = lerValidaUF(alterar->UF, 1)){
                   if(retorno = lerValidaCircuito(&alterar->circuito, temporario, 1))
                       retorno = lerValidaVelocidade(&alterar->velocidade, temporario, 1);   
               }
		 if(!retorno)
         {
            alterar->endereco[0] = '\0';
            opcao = 1;
         }
         else
         {
             imprimeMsg("Os dados estao corretos? (S/N) : ", 4, 23, WHITE, BLACK);
             opcao = lerOpcao(37, 23);
         }
     }while(!opcao);
}
//------------------------------------------------------------------------------
//Objetivo  : Excluir uma pista cadastrado dos registros.
//Parâmetros: Pista a ser excluída.
//Retorno   : Nenhum.
void exclusaoPista(Pista resultado)
{  
     FILE *temp, *arquivo, *teste;
     int registro, aux = 0, existe = 0, qtdePista, qtdeTeste;
     Pista estrutura;
     Teste listar;

     contaRegistrosTeste(&qtdeTeste);
     teste = abreArquivo(ARQ_TESTE, "rb", "Erro ao abrir arquivo de testes.");
     while((aux < qtdeTeste)&& !existe)
     {
         if(leArquivo(&listar, sizeof(Teste), 1, teste)){
             existe = (listar.codigoPista == resultado.codigoPista) ? 1 : 0;
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
     apresentaInfo( NULL, &resultado, NULL, "ATENCAO! PISTA SUJEITO A EXCLUSAO!");
     imprimeMsg("Tem certeza que deseja excluir esta Pista? (S / N) : ", 3, 18, WHITE, BLACK);
     if(lerOpcao(56, 18))
     {
         encontraNumRegistroPista(resultado.codigoPista, &registro);
         contaRegistrosPista(&qtdePista);
         temp = abreArquivo("temp", "wb","Erro ao abrir o arquivo temporario");
         arquivo = abreArquivo(ARQ_PISTA, "rb","Erro ao abrir o arquivo de Pista");
         while(aux < qtdePista)
         {   
                if(leArquivo(&estrutura, sizeof(Pista), 1, arquivo))
                {
                    aux++;            
                    if(aux != registro)
                       if(!escreveArquivo(&estrutura, sizeof(Pista), 1, temp))
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
         if(removeArquivo(ARQ_PISTA))
            return;   
         if(renomeiaArquivo("temp", ARQ_PISTA))
            return;   
         apresentaMsg("Pista excluida com sucesso!", 20 , 12, WHITE);
         getch();
     }
}
//------------------------------------------------------------------------------
//Objetivo  : Relacionar o numero atribuido a uma pista numa pesquisa por código
//               e a sua posição no registro do arquivo de pistas para alteção ou exclusão.
//Parâmetros: Identificador da pista e posição no arquivo.
//Retorno   : Nenhum.
void encontraNumRegistroPista(int codigo, int *registro)
{
     FILE *arquivo;
     Pista verificar;
     int aux = 0, qnt;
     
     contaRegistrosPista(&qnt);
     arquivo = abreArquivo(ARQ_PISTA, "rb","Erro ao abrir o arquivo de pista");
     do
     {
          if(fread(&verificar, sizeof(Pista), 1, arquivo))
              aux++;
     }while((aux<qnt) && (verificar.codigoPista != codigo));
     *registro = aux;
     fechaArquivo(arquivo);
}
//------------------------------------------------------------------------------
//Objetivo  : Ler o código de uma pista.
//Parâmetros: Código a ser informado.
//Retorno   : Retorna falso em caso de desistência da leitura ou 1 caso bem sucedida.
int lerCodigoPista(int *codigo)
{
    char temp[TAM_TEXT];
    do
    {
         sprintf(temp, "%d", *codigo);             
         if(!(escrevaLimitado(2, 2, 11, 1, 6, 5, temp, 0)))
              return 0;

         *codigo = atof(temp);
         if(*codigo <= 0)
         {
            mostraMsgErro ("Codigo invalido!", 3, 11, 10, 1); //COL|LIN|BASE|ALTURA
         }
         else
           limpaArea(48, 25, 28, 1);
    }while(*codigo <= 0);
    return 1;
}
