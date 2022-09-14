#pragma region includes

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>

#pragma endregion

void Mostra(char *nome){
    int ficheiro, tamanho;
    char linhas[999];
    ficheiro = open(nome, O_RDONLY);

    if (ficheiro == -1){
        perror("\nFicheiro nao encontrado");
        exit(1);
    }

    tamanho = read (ficheiro, linhas, sizeof(linhas));
    write(STDOUT_FILENO, linhas, tamanho);
    close(ficheiro);
}

void Copiar(char *nome){
    int ficheiro, fd, tamanho;
    char linhas[999];

    char *nome_ficheiro = "ficheiro.copia";
    creat(nome_ficheiro, S_IRUSR | S_IWUSR | S_IXUSR);

    ficheiro = open(nome, O_RDONLY);
    
    if (ficheiro == -1){
        perror("\nFicheiro nao encontrado");
        exit(1);
    }

    fd = open("ficheiro.copia", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    tamanho = read(ficheiro, linhas, sizeof(linhas));
    write(fd, linhas, tamanho);

    close(fd);
    close(ficheiro);
}

void Adicionar(char *nome1, char *nome2){
    int origem, destino, tamanho;
    char linhas[999];

    origem = open(nome1, O_RDONLY);
    destino = open(nome2, O_RDWR | O_APPEND);


    if (origem == -1){
        perror("\nFicheiro nao encontrado");
        exit(1);
    }

    if (destino == -1){
        perror("\nFicheiro nao encontrado");
        exit(1);
    }

    tamanho = read(origem, linhas, sizeof(linhas));
    write(destino, linhas, tamanho);

    close(origem);
    close(destino);
}

void Contar(char *nome){
    char linhas[999];
    int tamanho, ficheiro;
    int contador = 0;

    ficheiro = open(nome, O_RDONLY);

    if (ficheiro == -1){
        perror("\nFicheiro nao encontrado");
        exit(1);
    }

    tamanho = read(ficheiro, linhas, sizeof(linhas));

    for (int i=0; i<tamanho; i++){
        if (linhas[i] == '\n'){
            contador++;
        }
    }

    printf("\n\nO ficheiro %s tem %d linhas\n", nome, contador);
    close(ficheiro);
}

void Apagar(char *nome){
    int ficheiro;

    ficheiro = open(nome, O_RDONLY);
    
    if (ficheiro == -1){
        perror("\nFicheiro nao encontrado");
        exit(1);
    }

    close(ficheiro);
    int apagar;
    apagar = unlink(nome);
}

void Informar(char *nome){
    struct stat informacao;
    struct passwd *pwd;
    int ficheiro;

    ficheiro = open(nome, O_RDONLY);

    if (ficheiro == -1) { 
        perror("\nFicheiro nao encontrado" );
        exit(1);
    }

    stat(nome, &informacao);

    printf("Nome do ficheiro: %s\n", nome);
    printf("Inode: %lu\n", informacao.st_ino);
    printf("Tipo: ");
    if(S_ISREG(informacao.st_mode)){
        printf("Ficheiro");
    }
    if(S_ISDIR(informacao.st_mode)){
        printf("Diretoria");
    }
    if(S_ISLNK(informacao.st_mode)){
        printf("Link");
    }
    if(S_ISFIFO(informacao.st_mode)){
        printf("Pipe");
    }
    printf("\n");

    pwd = getpwuid(informacao.st_uid);
    if (pwd == NULL) {
      perror("getpwuid");
      exit(EXIT_FAILURE);
    }
    printf("Nome utilizador: %s\n", pwd->pw_name);
    printf("Data de criação: %s", ctime(&informacao.st_ctime));
    printf("Data de modificação: %s", ctime(&informacao.st_mtime));
    printf("Data de leitura: %s", ctime(&informacao.st_atime));

    close(ficheiro);
}

void Listar(){
    DIR *d;

    struct dirent *dir;

    d = opendir(".");

    if (d){
        while((dir = readdir(d)) != NULL){
            printf("\n%s\n", dir->d_name);
        }

        closedir(d);
    }
}

int main(){
    int opc;
    char *teste;
    char *origem;
    char *destino;
    char *outro;
    char diretoria[1000];
    teste = "teste.txt";
    origem = "origem.txt";
    destino = "destino.txt";
    outro = "ficheiro.copia";
    strcpy(diretoria, ".");

    printf("-------------------MENU------------------------\n");
    printf("\n1 - Mostrar um ficheiro\n");
    printf("2 - Copiar um ficheiro\n");
    printf("3 - Acrescentar a origem ao destino\n");
    printf("4 - Contar as linhas de um ficheiro\n");
    printf("5 - Apagar um ficheiro\n");
    printf("6 - Apresentar informacao de um ficheiro\n");
    printf("7 - Listar a diretoria\n");
    scanf("%d", &opc);

    switch (opc)
    {
    case 1:
        printf("\n\n\n");
        Mostra(teste);
        main();
        break;
    case 2:
        printf("\n\n\n");
        Copiar(teste);
        main();
        break;
    case 3:
        printf("\n\n\n");
        Adicionar(origem, destino);
        main();
        break;
    case 4:
        printf("\n\n\n");
        Contar(teste);
        main();
        break;
    case 5:
        printf("\n\n\n");
        Apagar(outro);
        main();
        break;
    case 6:
        printf("\n\n\n");
        Informar(teste);
        main();
        break;
    case 7:
        printf("\n\n\n");
        Listar(diretoria);
        main();
        break;
        
    default:
        exit(0);
    }
}