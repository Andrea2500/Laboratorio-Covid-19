typedef struct pazienti
{
    char cf[50];
    int numero_s;
    struct pazienti *next;
} Pazienti;

typedef struct prenotazioni
{
    char cf[50],orario[30];
    int numero_s;
    struct prenotazioni *next;
} Prenotazioni;

typedef struct risultato
{
    char cf[50],esito[30];
    struct risultato *next;
} Risultato;