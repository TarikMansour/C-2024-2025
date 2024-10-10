#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 38
typedef struct {
    int anno_publicazione;
    double prezzo;
    char tipo[50]; 
    char titolo[50];
    char autore[50];
}Libro;
int CaricaLibri(Libro libri[MAX], const char *filename){
 FILE *file = fopen(filename, "r");
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
    return books;
}
void StampaLibreria(Libro libri[MAX], int numLibri){
 
    for (int i = 0; i<numLibri; i++){
        printf("Titolo [%s] Autore [%s] Anno [%d] Prezzo [%.2f] Categoria [%s]\n", 
        libri[i].titolo,
        libri[i].autore,
        libri[i].anno_publicazione,
        libri[i].prezzo,
        libri[i].tipo);
        printf("\n");
    }
}
void TrovaLibro (Libro libri[MAX], char titolo[20], int numlibri){

    for (int i = 0; i<numlibri; i++){
        if(strcmp(libri[i].titolo,titolo)==0){
            printf("il libro ricercato:\n");
            printf("Titolo [%s] Autore [%s] Anno [%d] Prezzo [%.2f] Categoria [%s]\n", 
            libri[i].titolo, 
            libri[i].autore, 
            libri[i].anno_publicazione,
            libri[i].prezzo,
            libri[i].tipo);
            printf("\n");
        }
    }
} 
void TrovaCategoria(Libro libri[MAX], char categoria[20], int numlibri){
    printf("i libri che appartengono a %s:\n", categoria);
     for (int i = 0; i<numlibri; i++){
        if(strcmp(libri[i].tipo,categoria)==0){
            printf("Titolo [%s] Autore [%s] Anno [%d] Prezzo [%.2f] Categoria [%s]\n", 
            libri[i].titolo, 
            libri[i].autore, 
            libri[i].anno_publicazione,
            libri[i].prezzo,
            libri[i].tipo);
            printf("\n");
        }
    }
}
int main() {
    Libro libri[MAX];
    int numLibri = CaricaLibri(libri, "libreria_libri.csv");
    if (numLibri == 0) {
        printf("non ci sono libri\n");
        return 1;
    }
    int scelta;
    char titolo[20];
    char categoria[20];
    printf("\n 0 per visualizzare la libreria \n 1 per ricercare un libro \n 2 per ricercare una categoria \n");
    printf("inserire scelta:\n");
    scanf("%d", &scelta);
    getchar(); //elimina il carattere di newline dsl buffer di input
    switch(scelta){
        case 0: 
        StampaLibreria(libri, numLibri);
        break;
        case 1:
        printf("inserire un libro da trovare \n");
        scanf("%[^\n]", titolo);
        TrovaLibro(libri,titolo,numLibri);
        break;
        case 2:
        printf("inserire una categoria da trovare \n");
        scanf("%s", categoria);
        TrovaCategoria(libri,categoria,numLibri);
        break;
    }
    return 0;
}
