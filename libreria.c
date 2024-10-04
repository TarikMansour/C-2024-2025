#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 38
#define MAX_LINE_LENGTH 1024
#define MAX_FIELDS 100
typedef struct {
    int anno_publicazione;
    double prezzo;
    char tipo[50]; 
    char titolo[50];
    char autore[50];
}Libro;
void TrovaLibro (Libro libri[MAX], char titolo[20]){

    for (int i = 0; i<MAX; i++){
        if(strcmp(libri[i].titolo,titolo)==0){
            printf("il libro ricercato:\n");
            printf("%s %s %d %.2f \n", 
            libri[i].titolo, 
            libri[i].autore, 
            libri[i].anno_publicazione,
            libri[i].prezzo);
        }
    }
} 
void TrovaCategoria(Libro libri[MAX], char categoria[20]){
    printf("i libri che appartengono a %s:\n", categoria);
     for (int i = 0; i<MAX; i++){
        if(strcmp(libri[i].tipo,categoria)==0){
            printf("%s %s %d %.2f \n", 
            libri[i].titolo, 
            libri[i].autore, 
            libri[i].anno_publicazione,
            libri[i].prezzo);
        }
    }
}
int main() {
    Libro libri[MAX];
    FILE *file = fopen("libreria_libri.csv", "r");
    if (file == NULL) {
        printf("Errore nell'aprire il file \n");
        return 1;
    }
    int read = 0;
    int books = 0;
    do{
        read = fscanf(file,"%49[^,],%49[^,],%d,%lf,%s\n",
        libri[books].titolo,
        libri[books].autore,
        &libri[books].anno_publicazione,
        &libri[books].prezzo,
        libri[books].tipo);
        if(read==5){
            books++;
        }
        else if(read !=5 && !feof(file)){
            printf("lettura non riuscita\n");
            return 1;
        }
    }while(!feof(file));
    fclose(file);
    for (int i = 0; i<books; i++){
        printf("%s %s %d %.2f %s\n", 
        libri[i].titolo,
        libri[i].autore,
        libri[i].anno_publicazione,
        libri[i].prezzo,
        libri[i].tipo);
        printf("\n");
    }
    char titolo[20];
    printf("inserire un libro da trovare \n");
    scanf("%[^\n]", titolo);
    TrovaLibro(libri, titolo);
    char categoria[20];
    printf("inserire una categoria da trovare \n");
    scanf("%s", categoria);
    TrovaCategoria(libri, categoria);
    return 0;
}