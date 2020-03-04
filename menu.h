//================= FUNÇÕES MENU ===============================================

void menuPrincipal(int *op1, int *op2);
int menuVertical(int opInicial, int tamanho, char *opcoes[], int maior);
int escolha(int * opcao, int tamanho);
void titulo(void);
void fazBorda (int comp, int larg, int coluna, int linha, int limpar);
void limpaArea(int coluna, int linha, int base, int altura);
int menuSelecao(int n,char *imenu[],int c1,int c2,int linha,int coluna,int ini, int moldura,int corFundoAtual, int corLetraAtual, int tamCorFundo, int largo);
void desenhaMoldura(int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal, int corFundoAtual, int corLetraAtual);
void limpaJanela(int linhaInicial,int colunaInicial,int linhaFinal, int colFinal,int corFundo);
void retornaCor(int corFundo,int corTexto);

//------------------------------------------------------------------------------
//Objetivo  : Cria o menu principal.
//Parâmetros: Opções 1 e 2, que serão informadas.
//Retorno   : Nenhum.
void menuPrincipal(int *op1, int *op2)
{
// Declarações

    char aviao[TAM_TEXT];
    sprintf(aviao,"AVI%cO             >",199);

    char *opcoes[] = {aviao,
                      "PISTA             >",
                      "TESTES            >",
                      "SAIR"};
                                          
    char *opcoes2[] = {"Cadastrar",
                       "Listar  ",
                       "Consultar",
                       "Alterar ",
                       "Excluir "}; 

    int opcao = 1, opcao2 = 0;
// Instruções
    titulo ();
    do
    {
        gotoxy(10,10);
        opcao2 = 0;
        opcao = menuVertical((opcao > 0) ? opcao : 1, 4, opcoes, 20);
        *op1 = opcao;
        if((opcao == 4) || (opcao == -1 ))
        {
            if(opcao == 4)
               return;
        }
        else
        {
            gotoxy(25,10);
            opcao2 = menuVertical(1, 5, opcoes2, 20);
            limpaArea(25, 10, 22, 7); // Area Menu
            *op2 = opcao2;
        }
    }while ((opcao2 == -1) || (opcao == -1));
    limpaArea(10, 10, 22, 6);
}
//------------------------------------------------------------------------------
//Objetivo  : Cria um menu vertical.
//Parâmetros: Opcao inicial, tamanho da lista, descrições da lista e comprimento 
//            maior desejado.
//Retorno   : -1 - no caso de cancelamento do menu ou a opcao escolhida.
int menuVertical(int opInicial, int tamanho, char *opcoes[], int maior)
{
//================= PROTÓTIPO DA FUNÇÃO ========================================
    void mudaFundo(int, int, int, int, int, char *[]);
// Declarações
    int escolha(int*, int);
    int opcao = opInicial, coluna = wherex(), linha = wherey(), saida = 0;
 // Instruções   
    do
    {
        if(saida != 2)
          mudaFundo(opcao, maior, coluna, linha, tamanho, opcoes);
    }while((saida = escolha(&opcao, tamanho)) > 0 );
    if(saida < 0)
        return -1;
    else
        return opcao;
}
//------------------------------------------------------------------------------
//Objetivo  : Funcão auxiliar da funcao menu, muda escopo da escolha.
//Parâmetros: Opcao, largura maior desejada, coordenadas de inicio, tamanho da 
//            lista  e descrição da lista.
//Retorno   : Nenhum.
void mudaFundo(int opcao, int maior, int coluna, int linha, int tamanho, char *opcoes[])
{
     int aux;
     fazBorda(maior, tamanho, coluna, linha, 1);
     for(aux = 0; aux < tamanho; aux ++)
     {
         gotoxy(coluna + 1, linha + aux + 1);
         printf(opcoes[aux]);
     }
     textbackground(GREEN);
     gotoxy(coluna + 1, opcao + linha);
     printf(opcoes[opcao - 1]);
     for(aux = 0; aux < (maior - strlen(opcoes[opcao - 1])); aux++)
             printf(" ");
     textbackground(BLACK);
}
//------------------------------------------------------------------------------
//Objetivo  : Funcão auxiliar da função menu, obtêm a tecla digitada do usuário e interpreta.
//Parâmetros: Opcao que será escolhida, e tamanho da lista.
//Retorno   : -1 - cancelamento, 0 - escolha feita, 1 - setas (cima e baixo) ou 2 - inválida.
int escolha(int * opcao, int tamanho)
{
    char tecla;
    switch(tecla = getch())
    {
       case 'P':
            if((*opcao) < tamanho)
                 (*opcao) ++;
            else 
               (*opcao) = 1;
            return 1;
       case 'H':
            if(*opcao > 1)
                 (*opcao) --;
            else
                 (*opcao) = tamanho;
            return 1;
       case 27: case 'K': case 8:
            return -1;
       case 13: case ' ':
            return 0;
       default:
            return 2;
    }
}
//------------------------------------------------------------------------------
//Objetivo  : Apresentar o titulo do menu principal.
//Parâmetros: Nenhum.
//Retorno   : Nenhum.
void titulo(void)
{
// Instruções
    textcolor(LIGHTGRAY);
    fazBorda(78, 27, 1, 1, 0); //Borda MENU
    fazBorda(35, 1, 20, 4, 1);
    gotoxy(32, 5);
    textcolor(LIGHTRED);
    printf("TESTE DE AVI%cES",229);
    
    char text[TAM_TEXT];

    //--------------------------------------------------------
    gotoxy(33,30);                      					//
    textcolor(GREEN);										//
    sprintf(text,"Arism%crio Neves",160);                   //
	printf(text);								         	//
	textcolor(LIGHTGRAY);									//
    printf(" - ");									        //
    textcolor(RED);										    //
    printf("2014");								            //
	textcolor(LIGHTGRAY);					    	    	//
	printf(" - mariodev%coutlook.com.br",64);       		//

	//--------------------------------------------------------
	textcolor(WHITE);
}
//Objetivo  : Apresenta um menu vertical e retorna a opcao selecionada. 
//Parâmetros: n - Numero de itens                             
//             imenu         - Descrição dos itens                    
//             c1            - cor do texto do menu                      
//             c2            - cor da marca do item selecionado          
//             linha         - linha inicial para instalação do menu  
//             coluna        - coluna inicial para instalação do menu
//             ini           - número da opção inicial do menu a ser selecionada                          
//             moldura       - indicador se deve desenhar o menu dentro de uma moldura
//             corFundoAtual - cor do fundo a ser restituida a tela com a retirada do menu               
//             corLetra      - cor da letra a ser restituida a tela com a retirada do menu
//             tamCorFundo   - tamanho da área do fundo  a ser restituida a tela com a retirada do menu(se = 0, a cor e ajustada automaticamente)
//             largo         - tamanho do menu(largo = 1)(pequeno = 0)      
//Retorno   : Número do item do menu selecionado.
int menuSelecao(int n,char *imenu[],int c1,int c2,int linha,int coluna,int ini, int moldura,int corFundoAtual, int corLetraAtual, int tamCorFundo, int largo)
{
		int tecla;	// Recebe a tecla pressionada
		int sel_b;	// Selecao de backup do menu
		int sel;
		int i;  		
		int val;		// 1 = tecla valida encontrada
						// 0 = tecla valida nao encontrada
        int tamMaiorTexto;
         

        // verifica se desenha com moldura e menu comeca na linha 1
        if(linha ==1 && moldura)
           linha++;
        // verifica se desenha com moldura e menu comeca na coluna 1
        if(coluna== 1 && moldura)
           coluna++;
            
		textcolor(c1);	// Atributo da cor das letras
		if(ini < 1)
		    ini=1;
		else if(ini>n)
           ini=n;
               
		sel=ini-1; 	// Primeiro item selecionado
		for (i=0;i<=n-1;i++)
			{
			    
				if (i==ini-1) textbackground(c2); // Escreve itens do menu
				else textbackground(corFundoAtual);           // e seleciona o item inicial
				gotoxy(coluna,linha+i);                    // setado no argumento passado
				printf(imenu[i]);
				if(i==0)
				  tamMaiorTexto = strlen(imenu[i]);
				else if(strlen(imenu[i]) > tamMaiorTexto)
				  tamMaiorTexto = strlen(imenu[i]);
                
			}
			// desenha a moldura
			if(moldura)
			{
			    desenhaMoldura(linha-1,coluna-1,linha+n,coluna+tamMaiorTexto+2,
                     corFundoAtual, corLetraAtual);
			}    
		do
			{
				do
					{
//						do
//							{
//							} while (!kbhit());

						tecla=toupper(getch()); 
						
						// Verificar pelas teclas validas pressionadas
						if(largo!=0){
							if (tecla==72||tecla==75||tecla==65) val=1;
							else 	if (tecla==77||tecla==80||tecla==90) val=1;
									else 	if (tecla==27||tecla==13||tecla==32) val=1;
											else val=0;
					    }else{
							if (tecla==72||tecla==75||tecla==65) val=1;
							else 	if (tecla==77||tecla==80||tecla==90) val=1;
									else 	if (tecla==27||tecla==13) val=1;
											else val=0;
					    }
					}while (!val);
				sel_b=sel; // Backup do item atual antes de modifica-lo
				if (tecla==72||tecla==75||tecla==65) sel--; // Sobe
				if (tecla==80||tecla==77||tecla==90) sel++; // Desce
				if (tecla==27||tecla==32) sel_b=-1; 		// Sai com ESC ou ESPAÇO
				if (sel<=-1) sel=n-1; // Se for menor vai para o ultmo item
				if (sel>=n) sel=0; // Se for maior vai para o primeiro item
				textcolor(c1);
				if (tecla!=13&&tecla!=27&&tecla!=32)
					{
						// Desseleciona o antigo item do menu...
						gotoxy(coluna,sel_b+linha); textbackground(corFundoAtual); printf(imenu[sel_b]);
						// Seleciona o novo item do menu...
						gotoxy(coluna,sel+linha); textbackground(c2); printf(imenu[sel]);
						// Descarrega o buffer do teclado...
						fflush(stdin);
					}
					
			} while (tecla!=13&&tecla!=27&&tecla!=32);
			
		//13 - ENTER
		//27 - ESC
		//32 - ESPAÇO 
		
		if(tecla==27) 
            sel_b=-1;
			
	    if(tecla==32)
		    sel_b=-2;  
            
        if(moldura)
           	limpaJanela(linha-2,coluna-1,linha+n,coluna+tamMaiorTexto+2,corFundoAtual);
        else if(tamCorFundo>0)
           	limpaJanela(linha,coluna,(linha+n)-1,coluna+tamCorFundo,corFundoAtual);
        else  
            limpaJanela(linha,coluna,(linha+n)-1,coluna+tamMaiorTexto,corFundoAtual);
            
		                 	// Retorna 0 se for apertado ESC.
		                    // Retorna -1 se for apertado ESPAÇO.
		return(sel_b+1);    // Retorna >1 se for apertado ENTER.		                    
}
//Objetivo  : Desenha uma moldura na tela.                  
//Parâmetros: linhaInicial   - linha inicial da moldura         
//             colunaInicial - coluna inicial da moldura     
//             linhaFinal    - linha final da moldura         
//             colunaFinal   - coluna final da moldura         
//             corFundoAtual - cor do fundo atual            
//             corLetra      - cor do fundo atual.              
//Retorno   : Nenhum.                               
void desenhaMoldura(int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal, int corFundoAtual, int corLetraAtual)
{
    int i=0,qtdeLinhas,qtdeColunas;
    
    qtdeLinhas  = linhaFinal - linhaInicial ;
    qtdeColunas = colunaFinal - colunaInicial ;
    textbackground(7);
    textcolor(8);
    // faz a borda superior
    gotoxy(colunaInicial,linhaInicial);
    for(i=0;i<=qtdeColunas;i++)
    {
        printf("\xCD");
    }

    // faz a borda inferior
    gotoxy(colunaInicial,linhaInicial+qtdeLinhas);
    for(i=0;i<=qtdeColunas;i++)
    {
        printf("\xCD");
    }

    // faz a lateral esquerda    
    for(i=0;i<=qtdeLinhas;i++)
    {
        gotoxy(colunaInicial,linhaInicial+i);
        printf("\xBA");
    }
    // faz a lateral direita
    for(i=0;i<=qtdeLinhas;i++)
    {
        gotoxy(colunaInicial+qtdeColunas,linhaInicial+i);
        printf("\xBA");
    }

    // fecha os cantos da moldura
    gotoxy(colunaInicial,linhaInicial);
    printf("\xC9");
    gotoxy(colunaInicial+qtdeColunas,linhaInicial);
    printf("\xBB");
    gotoxy(colunaInicial,linhaInicial+qtdeLinhas);
    printf("\xC8");
    gotoxy(colunaInicial+qtdeColunas,linhaInicial+qtdeLinhas);
    printf("\xBC");
    retornaCor(corFundoAtual, corLetraAtual);
}
//Objetivo  : Limpa uma janela da tela.                    
//Parâmetros: linhaInicial   - linha inicial da janela          
//             colunaInicial - coluna inicial da janela       
//             linhaFinal    - linha final da janela           
//             colunaFinal   - coluna final da janela           
//             corFundo      - cor do fundo da janela a ser limpa.
//Retorno   : Nenhum.
void limpaJanela(int linhaInicial,int colunaInicial,int linhaFinal, int colFinal,int corFundo)
{
int coluna=0,linha=0;

    for(coluna=colFinal;coluna>=colunaInicial;coluna--)
    {
        for(linha=linhaFinal;linha>=linhaInicial;linha--)        
        {
            textbackground(corFundo);
            gotoxy(coluna,linha);
            printf(" ");
        }
    }
}                            
//Objetivo  : Retorna a cor de fundo e de texto.
//Parâmetros: corFundo - cor de fundo
//            corTexto - cor do texto.
//Retorno   : Nenhum.
void retornaCor(int corFundo,int corTexto)
{
    textbackground(corFundo);
    textcolor(corTexto);
}    
