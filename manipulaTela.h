//================= FUNÇÕES MANIPULAR JANELA ===================================

BOOL redimencionarConsole(COORD newSize);
void finalizarErro(char *textoErro);   

//------------------------------------------------------------------------------
BOOL redimencionarConsole(COORD newSize) {

    // Declaração de estruturas para chamadas das funções em windows.h
    // Consulte detalhes em http://msdn.microsoft.com/en-us/library/windows/desktop/ms682087
    CONSOLE_SCREEN_BUFFER_INFO infoConsole ;
    COORD curWindow ;
    SMALL_RECT newWindow ;
    HANDLE handleOut ;
    BOOL alteracao = FALSE ;

    // Definir HANDLE padrão de saída
    handleOut = GetStdHandle(STD_OUTPUT_HANDLE) ;
    if(handleOut == INVALID_HANDLE_VALUE) {
        finalizarErro("Erro em GetStdHandle") ;
    }

    // Recuperar os tamanhos atuais do buffer e window do console
    if(!GetConsoleScreenBufferInfo(handleOut , &infoConsole)) {
        finalizarErro("Erro em GetConsoleScreenBufferInfo") ;
    }

    // Recuperar o tamanho maximo permitido para a console
    infoConsole.dwMaximumWindowSize
            = GetLargestConsoleWindowSize(handleOut) ;
    if(infoConsole.dwMaximumWindowSize.X == 0
            && infoConsole.dwMaximumWindowSize.Y == 0) {
        finalizarErro("Erro em GetLargestConsoleWindowSize") ;
    }

    // Testar se o tamanho requerido é maior que o máximo permitido, retornar
    // FALSO após o aviso de erro.
    if(newSize.X > infoConsole.dwMaximumWindowSize.X
            || newSize.Y > infoConsole.dwMaximumWindowSize.Y) {
        printf("\nO tamanho maximo de %i x % i nao comporta %i x %i."
                , infoConsole.dwMaximumWindowSize.X
                , infoConsole.dwMaximumWindowSize.Y
                , newSize.X , newSize.Y) ;
        return FALSE ;
    }

    // calcular tamanho atual da window do console
    curWindow.X = infoConsole.srWindow.Right - infoConsole.srWindow.Left + 1 ;
    curWindow.Y = infoConsole.srWindow.Bottom - infoConsole.srWindow.Top + 1 ;
    // As funções de redimensionamento do console da Windows API retornam erro
    // se tentar definir uma window com qualquer dimensão maior que o buffer,
    // logo, para expandir o tamanho da tela o buffer precisa ser expandido
    // antes da window.
    if(infoConsole.dwSize.X < newSize.X || infoConsole.dwSize.Y < newSize.Y) {
        if(infoConsole.dwSize.X < newSize.X) infoConsole.dwSize.X = newSize.X ;
        if(infoConsole.dwSize.Y < newSize.Y) infoConsole.dwSize.Y = newSize.Y ;
        if(!SetConsoleScreenBufferSize(handleOut , newSize)) {
            finalizarErro("Erro em GetLargestConsoleWindowSize") ;
        }
    }
    // Redimensionar a window somente se houve alguma alteração, passando o
    // retorno para TRUE.
    if(curWindow.X != newSize.X || curWindow.Y != newSize.Y) {
        newWindow.Left = 0 ;
        newWindow.Top = 0 ;
        newWindow.Right = newSize.X - 1 ;
        newWindow.Bottom = newSize.Y - 1 ;

        if(!SetConsoleWindowInfo(handleOut , TRUE , &newWindow)) {
            finalizarErro("Erro em SetConsoleWindowInfo") ;
        } else alteracao = TRUE ;
    }
    // Redimensionar o buffer somente se não estiver ajustado à window.
    if(infoConsole.dwSize.X != newSize.X || infoConsole.dwSize.Y != newSize.Y) {
        infoConsole.dwSize.X = newSize.X ;
        infoConsole.dwSize.Y = newSize.Y ;
        if(!SetConsoleScreenBufferSize(handleOut , newSize)) {
            finalizarErro("Erro em GetLargestConsoleWindowSize") ;
        }
    }

    return alteracao ;
}

void finalizarErro(char *textoErro){
    printf("\n%s\n" , textoErro) ;
    exit(EXIT_FAILURE) ;

    return ;
}
