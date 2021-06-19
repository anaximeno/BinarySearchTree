#ifndef COMMON_H
#define COMMON_H

#define MAX_CLEAN_REPEAT_TIMES 32
#define NOMEMAX 32

#ifdef unix
    #include <unistd.h>
    #define SLEEP(milisecs) ( usleep((milisecs*1000)) )
    #define CLEAR "clear"
#endif // unix

#ifdef _WIN32
    #include <Windows.h>
    #define SLEEP(milisecs) ( Sleep(milisecs) )
    #define CLEAR "cls"
#endif // _WIN32


/* Limpa/liberta as variáveis no final da execução. */
void freedom(void);


/* Mostra o cabeçalho do programa. */
void header(void);


/* Limpa o terminal. */
void clearScreen(void);


/* Limpa o buffer. */
void cleanbuf(void);


/* Mostra o menu e retorna a opção escolhida. */
int menu(void);


/* Toma e retorna um valor inteiro do stdin. */
int get_int(void);


/* Mostra uma mensagem que pede para clicar em
enter para continuar e depois limpa a tela*/
void enterpoint(void);


/* Mostra uma string de forma 'animada'
em que cada caractere aparece intervalado em 'milisecs'. */
void animate(const char *texto, unsigned int milisecs);


/* Retorna uma string sem a sua extensão. */
char *getName(char *txtname);


#endif // COMMON_H
