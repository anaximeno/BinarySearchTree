#ifndef COMMON_H
#define COMMON_H

#ifdef unix
    #include <unistd.h>
    #define CLEAR() (system("clear"));
#endif // linux

#ifdef _WIN32
    #include <Windows.h>
    #define CLEAR() (system("cls"))
#endif // _WIN32


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
em que cada carcatere aparece intervalado em 'microsecs'. */
void animate(const char *texto, unsigned int microsecs);


#endif // COMMON_H
