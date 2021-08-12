#ifndef COMMON_H
#define COMMON_H

#define NORMAL_STRING_SIZE 32
#define BIG_STRING_SIZE 4*NORMAL_STRING_SIZE

#ifdef unix
    #include <unistd.h>
    #define SLEEP(milisecs) ( usleep((milisecs*1000)) )
    #define CLEAR "clear"
    #define BRANCH_SPACES "  "
    #define VERTICAL_BRANCH "│ "
    #define LEFT_BRANCH "└──"
    #define RIGHT_BRANCH "┌──"
    #define ROOT_BRANCH "━"
    #define MIDDLE_BRANCH "├──"
    #define LINE_BRANCH "───"
#endif // unix

#ifdef _WIN32
    #include <Windows.h>
    #define SLEEP(milisecs) ( Sleep(milisecs) )
    #define CLEAR "cls"
    #define BRANCH_SPACES "  "
    #define VERTICAL_BRANCH "| "
    #define LEFT_BRANCH "'--"
    #define RIGHT_BRANCH ".--"
    #define ROOT_BRANCH "="
    #define MIDDLE_BRANCH "|--"
    #define LINE_BRANCH "---"
#endif // _WIN32


/* Desenha uma linha de tamanho lim. */
void drawLine(char *symbol, int times);


/* Limpa/liberta as variáveis no final da execução. */
void freeMemory(void);


/* Mostra o cabeçalho do programa. */
void header(void);


/* Limpa o terminal, e mostra o header se show_header for true. */
void clearScreen(bool show_header);


/* Limpa o buffer. */
void freeBuffer(void);


/* Mostra o menu e retorna a opção escolhida. */
int menu(void);


/* Toma e retorna um valor inteiro do stdin. */
int get_int(void);      // TODO: put to receive an string and outputs it when getting the value


/* Mostra uma mensagem que pede para clicar em
enter para continuar e depois limpa a tela*/
void enterpoint(bool show_header);


/* Mostra uma string de forma 'animada'
em que cada caractere aparece intervalado em 'milisecs'. */
void animateOutput(const char *texto, unsigned int milisecs);


/* Retorna uma string sem a sua extensão. */
char *getName(char *txtname);


/* Mostra o primeiro menu do programa e retorna a opção.*/
int menu_1(void);


/* Mostra o menu do cliente e retorna a opção. */
char menu_2(void);

/* Mostra o menu de Administrador e retorna a opção escolhida. */
char menu_3(void);

#endif // COMMON_H
