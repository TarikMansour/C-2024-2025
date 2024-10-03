#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 38
#define MAX_LINE_LENGTH 1024
#define MAX_FIELDS 100
typedef enum {
    NARRATIVA, 
    SAGGISTICA, 
    SCIENZE, 
    ARTE
}Categoria;
typedef struct {
    int anno_publicazione;
    double prezzo;
    Categoria tipo; 
    char titolo[50];
    char autore[50];
}Libro;
Categoria stringToCategoria(const char* str) {
    if (strcmp(str, "NARRATIVA") == 0) return NARRATIVA;
    if (strcmp(str, "SAGGISTICA") == 0) return SAGGISTICA;
    if (strcmp(str, "SCIENZE") == 0) return SCIENZE;
    if (strcmp(str, "ARTE") == 0) return ARTE;
    return NARRATIVA; // Valore di default
}
void parseCSVLine(char *line, Libro *libro) {
    char *token = strtok(line, ",");
    if (token) strcpy(libro->titolo, token);
    token = strtok(NULL, ",");
    if (token) strcpy(libro->autore, token);
    token = strtok(NULL, ",");
    if (token) libro->tipo = stringToCategoria(token);
    token = strtok(NULL, ",");
    if (token) libro->anno_publicazione = atoi(token);
    if (token) libro->prezzo = atof(token);
}
int main() {
    Libro libri[MAX];
    FILE *file = fopen("libreria_libri.csv", "r");
    if (file == NULL) {
        printf("Errore nell'aprire il file \n");
    }
    int count = 0;
    char line[MAX_LINE_LENGTH];

   
    // Legge il file riga per riga
    while (fgets(line, sizeof(line), file) && count < MAX) {
        line[strcspn(line, "\n")] = '\0'; // Rimuove il newline finale
        parseCSVLine(line, &libri[count]);
        count++;
    }

    fclose(file);
    for (int i = 0; i < count; i++) {
        printf("Libro %d:\n", i + 1);
        printf("Titolo: %s\n", libri[i].titolo);
        printf("Autore: %s\n", libri[i].autore);
        printf("Categoria: %d\n", libri[i].tipo);
        printf("Anno: %d\n\n", libri[i].anno_publicazione);
        printf("Prezzo: %.2f\n\n", libri[i].prezzo); 
    }

    return 0;
}