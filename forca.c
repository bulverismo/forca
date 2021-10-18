#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<conio2.h>
#include<windows.h>

#define TAM_PALAVRA 30
#define TAM_DICA 30

#define LINHA '-'
#define COLUNA '|'
#define TEMPO 500

enum
{
    LIM_ESQ = 1,
    LIM_DIR = 80,
    LIM_CIMA = 1,
    LIM_BAIXO = 26,
};

enum
{
    TELA1 = 1,
    TELA2 = 2,
    TELA3 = 3,
    TELA4 = 4,
    TELA_STATUS = 5,
    TELA_ABAIXO = LIM_BAIXO +1
};

enum
{
    COR_LETRA = WHITE,
    COR_FUNDO = BLACK
};

enum
{
    ALT = LIM_BAIXO-2,
    LARG = 40
};

enum
{
    MEIA_TELA = LIM_DIR/2
};
void borda();
void verificaLetra( char letra,char palavra[TAM_PALAVRA],int largura,char escondida[],int *descoberta,int *erros);
void jogo();
void imprime_boneco(int, int, int);
void imprime_forca( int, int );

int main()
{

    borda();
    jogo();

    gotoxy(LIM_DIR,LIM_BAIXO);
    return 0;
}

void borda()
{
    int i;
    textcolor(BLUE);
    for(i = LIM_CIMA; i <= LIM_BAIXO; i++)
    {
        putchxy(LIM_ESQ, i, COLUNA);
        putchxy(LIM_DIR, i, COLUNA);
    }
    for(i = LIM_ESQ; i <= LIM_DIR; i++)
    {
        putchxy(i, LIM_CIMA, LINHA);
        putchxy(i, LIM_BAIXO, LINHA);
    }
}

void verificaLetra( char letra,char palavra[TAM_PALAVRA],int largura,char escondida[],int *descoberta,int *erros)
{
    int i;
    int acertou=0;

    gotoxy(LIM_ESQ+1,LIM_CIMA+TELA_STATUS);
    printf("%*s",MEIA_TELA," ");

    for (i=0; i<largura-1; i++)
    {
        if ( toupper(letra) == toupper(escondida[i]) )
        {
            gotoxy(LIM_ESQ+1,LIM_CIMA+TELA_STATUS);
            printf("Ja tentou essa letra!");

            return ;
        }
    }

    for (i=0; i<largura-1; i++)
    {
        if ( toupper(letra) == toupper(palavra[i]) )
        {
            escondida[i] = toupper(letra);
            (*descoberta)++;
            acertou=1;
        }
    }

    if ( !acertou )
    {
        (*erros)++;
    }
}

void jogo()
{
    int largura=0;
    int i=0;
    int parar=0;
    int descoberta=0;
    char palavra[TAM_PALAVRA];
    char p_escondida[TAM_PALAVRA];
    char dica[TAM_DICA];
    char tentativa;
    int erros=0;

    textcolor(COR_LETRA);
    gotoxy(LIM_ESQ+1,LIM_CIMA+TELA1);
    printf("Digite uma palavra: ");
    fgets(palavra, TAM_PALAVRA, stdin);
    gotoxy(LIM_ESQ+1,LIM_CIMA+TELA1);
    printf("%*s",MEIA_TELA," ");

    gotoxy(LIM_ESQ+1,LIM_CIMA+TELA1);
    printf("Digite uma dica: ");
    fgets(dica, TAM_PALAVRA, stdin);
    gotoxy(LIM_ESQ+1,LIM_CIMA+TELA1);
    printf("%*s",MEIA_TELA," ");

    largura = strlen(palavra);

    for (i=0; i<largura-1; i++)
    {
        p_escondida[i] = '*';
    }
    p_escondida[i] = '\0';

    imprime_forca(43,2);

    do
    {
        gotoxy(LIM_ESQ+1,LIM_CIMA+TELA1);
        printf("Palavra secreta: ");

        gotoxy(LIM_ESQ+1,LIM_CIMA+TELA2);
        printf("%s",p_escondida);

        gotoxy(LIM_ESQ+1,LIM_CIMA+TELA3);
        printf("Dica: %s",dica);

        gotoxy(LIM_ESQ+1,TELA_ABAIXO);
        printf("Digite uma letra: ");
        scanf(" %c",&tentativa);
        gotoxy(LIM_ESQ+1,TELA_ABAIXO);
        printf("%*s",MEIA_TELA," ");

        verificaLetra(tentativa,palavra,largura,p_escondida,&descoberta,&erros);

        imprime_boneco(erros, 57,5);

        gotoxy(LIM_ESQ+1,LIM_CIMA+TELA4);
        printf("%*s",MEIA_TELA," ");
        gotoxy(LIM_ESQ+1,LIM_CIMA+TELA4);
        printf("Erros: %d",erros);

        if (descoberta == largura-1 || erros==6)
        {
            parar=1;
        }

    }
    while(!parar);

    gotoxy(LIM_ESQ+1,LIM_CIMA+TELA1);
    printf("Palavra secreta: ");

    gotoxy(LIM_ESQ+1,LIM_CIMA+TELA2);
    printf("%s",p_escondida);

    if (erros==6)
        saudacao("Mas que pena perdeu!!!");
    else
        saudacao("Parabens venceu!");

}

void imprime_boneco(int erros, int x, int y)
{
    int i;
    char cabeca[8][18] =
    {
        "      0000",
        "     0000000",
        "   0         0",
        "       0 0",
        " 0            0",
        "0      00000    0",
        "  0           0",
        "        0"
    };
    char tronco[5][18] =
    {
        "        0",
        "        0",
        "        0",
        "        0",
        "        0"
    };
    char braco1[4][18] =
    {
        "       0",
        "      0",
        "     0",
        "    0"
    };
    char braco2[4][18] =
    {
        "0",
        " 0",
        "  0",
        "   0"
    };
    char perna1[7][18] =
    {
        "       0",
        "      0",
        "     0",
        "    0",
        "   0"
    };
    char perna2[7][18] =
    {
        "0",
        " 0",
        "  0",
        "   0",
        "    0"
    };
    switch(erros)
    {
    case 1:
        for (i=0; i<8; i++)
        {
            gotoxy(x, y+i);
            printf("%s",cabeca[i]);
        }
        break;
    case 2:
        for (i=0; i<5; i++)
        {
            gotoxy(x, 8+y+i);
            printf("%s",tronco[i]);
        }
        break;
    case 3:
        for (i=0; i<4; i++)
        {
            gotoxy(x, 8+y+i);
            printf("%s",braco1[i]);
        }
        break;
    case 4:
        for (i=0; i<4; i++)
        {
            gotoxy(x+9, 8+y+i);
            printf("%s",braco2[i]);
        }
        break;
    case 5:
        for (i=0; i<5; i++)
        {
            gotoxy(x, 13+y+i);
            printf("%s",perna1[i]);
        }
        break;
    case 6:
        for (i=0; i<5; i++)
        {
            gotoxy(x+8, 13+y+i);
            printf("%s",perna2[i]);
        }
        break;

    }

}

void imprime_forca( int x, int y)
{
    int i;
    char arr[ALT][LARG] =
    {
        "--------------------------------",
        "|                 ||||||",
        "|               ---------",
        "|",
        "|",
        "|",
        "|",
        "|",
        "|",
        "|",
        "|",
        "|",
        "|",
        "|",
        "|",
        "|",
        "|",
        "|",
        "|",
        "|",
        "|",
        "|",
        "|",
        "--------------------------------"
    };

    for (i=0; i<ALT; i++)
    {
        gotoxy(x, y+i);
        printf("%s",arr[i]);
    }
}

void saudacao(char msg[])
{
    int i;

    for(i=0; i<5; i++)
    {
        gotoxy(LIM_ESQ+1,LIM_CIMA+10);
        printf("%s",msg);
        gotoxy(LIM_DIR,LIM_BAIXO);

        Sleep(TEMPO);

        gotoxy(LIM_ESQ+1,LIM_CIMA+10);
        printf("%*s",MEIA_TELA," ");
        gotoxy(LIM_DIR,LIM_BAIXO);

        Sleep(TEMPO);
    }
}
