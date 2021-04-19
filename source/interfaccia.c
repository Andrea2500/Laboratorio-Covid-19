#include "../headers/loader.h"

void homemenu(){
    system("clear");
    char choice[100];
    fflush(stdin);
    printf("Seleziona una delle seguenti voci di menu:\n");
    printf("-Registrati [1]\n");
    printf("-Accesso paziente [2]\n");
    printf("-Accesso laboratorio [3]\n");
    printf("-Chiudi [99]\n");
    printf("Inserisci il numero indicato di fianco: ");
    scanf("%s",choice);
    
    
    switch (atoi(choice)){
        case 1:
            registrati();
            break;
        case 2:
            loginPaziente();
            break;
        case 3:
            menuLab(0);
            break;
        case 99:
            registraTamponiPiattaforma();
            exit(0);
            break;
        default:
            fflush(stdin);
            printf("Scelta non valida!\n\n\n");
            break;
    }
    
    homemenu();
}


//! INTERFACCE PAZIENTE
void menuPaziente(char *cf){
    system("clear");
    char choice[100];
    fflush(stdin);
    printf("Ciao %s, come vuoi procedere?\n",cf);
    printf("-Richiedi prenotazione [1]\n");
    printf("-Visualizza appuntamenti [2]\n");
    printf("-Cancella appuntamento [3]\n");
    printf("-Visualizza esito tampone [4]\n");
    printf("-Esci [99]\n");
    printf("Inserisci il numero indicato di fianco: ");
    scanf("%s",choice);
    
    switch (atoi(choice)){
        case 1:
            richiediPrenotazione(cf);
            break;
        case 2:
            visualizzaAppuntamentoPaziente(cf);
            break;
        case 3:
            cancellaAppuntamentoPaziente(cf);
            break;
        case 4:
            visualizzaEsitoTampone(cf);
            break;
        case 99:
            return;
            break;
        default:
            fflush(stdin);
            printf("Scelta non valida!\n\n\n");
            //menuPaziente(cf);
            break;
    }

    menuPaziente(cf);
}


//? INTERFACCE LABORATORIO
void menuLab(int accesso){
    system("clear");
    char choice[100];
    char userid[60],pwd[60];
    if (accesso == 0){
        printf("UserID: ");
        scanf("%s",userid);
        printf("Password: ");
        scanf("%s",pwd);
    
        if (strcmp("accessolab",userid) != 0 || strcmp("labpwd",pwd) != 0){
            printf("\n Credenziali non valide.\n\n");
            printf("-Riprovare [1]\n");
            printf("-Torna indietro [2]\n");
            printf("--Seleziona: ");
            int opt;
            scanf("%d",&opt);
            if (opt == 1){
                menuLab(0);
            }
            return;
        }
    }
    
    system("clear");
    fflush(stdin);
    printf("Come vuoi procedere?\n");
    printf("-Storico tamponi [1]\n");
    printf("-Visualizza richieste di appuntamento [2]\n");
    printf("-Visualizza appuntamenti fissati [3]\n");
    printf("-Visualizza pazienti positivi [4]\n");
    printf("-Aggiungi/Rimuovi appuntamenti [5]\n");
    printf("-Registra esiti sulla piattaforma [6]\n");
    printf("-Esci [99]\n");
    printf("Inserisci il numero indicato di fianco: ");
    scanf("%s",choice);
    
    
    switch (atoi(choice)){
        case 1:
            visualizzaStoricoTamponi();
            break;
        case 2:
            visualizzaRichiesteAppuntamenti();
            break;
        case 3:
            visualizzaAppuntamentiFissati();
            break;
        case 4:
            visualizzaPazientiPositivi();
            break;
        case 5:
            aggiungiRimuoviManualmenteLab();
            break;
        case 6:
            registraTamponiPiattaforma();
            break;
        case 99:
            return;
            break;
        default:
            fflush(stdin);
            printf("Scelta non valida!\n\n\n");
            //menuLab(1);
            break;
    }
    menuLab(1);
}

void visualizzaRichiesteAppuntamenti(){
    system("clear");
    FILE *fp;
    char tmpCF[60];
    int tmpS,trovato = 0;
    char choice[100];
    fp = fopen("files/richiestePrenotazioni.txt","r");
    while (fscanf(fp,"%s %d",tmpCF,&tmpS) == 2)
    {   
        if (trovato == 0){
            printf("Richieste di prenotazione effettuate dai clienti: \n\n");
            trovato = 1;
        }
        printf("Paziente %s con %d sintomi\n",tmpCF,tmpS);
    }
    fclose(fp);
    if(trovato == 1){
        printf("\n\n Come vuoi procedere?\n");
        printf("- Fissa appuntamenti [1]\n");
        printf("- Torna indietro [2]\n");
        printf("Seleziona: ");
        scanf("%s",choice);

        if (atoi(choice) == 1){
            fissaAppuntamenti();
        }else if (atoi(choice) == 2){
            return;
        }else{
            visualizzaRichiesteAppuntamenti();
        } 
    }else{
        pause("Non ci sono richieste di appuntamento");
    }
      
}

void aggiungiRimuoviManualmenteLab(){
    system("clear");
    char choice[100];
    fflush(stdin);
    printf("Come vuoi procedere?\n");
    printf("-Aggiungi appuntamento [1]\n");
    printf("-Rimuovi appuntamento [2]\n");
    printf("-Indietro [99]\n");
    printf("Inserisci il numero indicato di fianco: ");
    scanf("%s",choice);
    
    
    switch (atoi(choice)){
        case 1:
            aggiungiManLab();
            break;
        case 2:
            rimuoviManLab();
            break;
        case 99:
            return;
            break;
        default:
            fflush(stdin);
            printf("Scelta non valida!\n\n\n");
            aggiungiRimuoviManualmenteLab();
            break;
    }
    aggiungiRimuoviManualmenteLab();
}
