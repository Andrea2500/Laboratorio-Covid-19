#include "../headers/loader.h"

void pause(char *msg){
    fflush(stdin);
    char c[10];
    printf("\n\n%s\n\n",msg);
    printf("Digita un carattere per continuare...");  
    scanf("%s",c);
    fflush(stdin);
}




//!FUNZIONI PAZIENTE
void registrati(){
    system("clear");
    char nome[30], cognome[30], cf[20], password[60];
    printf("Inserisci il tuo codice fiscale: ");
    scanf("%s",cf);
    printf("Inserisci la tua password: ");
    scanf("%s",password);
    
    FILE *fp;
    fp = fopen("files/pazienti.txt","a");
    if(fp){
        fputs(cf,fp);
        fputs(" ",fp);
        fputs(password,fp);
        fputs("\n",fp);
        fclose(fp);
        pause("Registrazione avvenuta con successo!");
        return;
    }else{
        pause("Si è verificato un problema.\nRiprovare più tardi.");
        return;
    }
}

void loginPaziente(){
    system("clear");
    char cf[20],password[60],tmpCF[20],tmpPWD[60];
    int flag = 0;
    printf("Accesso paziente\n");
    printf("Inserisci codice fiscale: ");
    scanf("%s",cf);
    printf("Inserisci password: ");
    scanf("%s",password);

    FILE *fp;
    fp = fopen("files/pazienti.txt" , "r");
    if(fp == NULL){
        printf("Errore!");
        return;
    }

    while( fscanf(fp, "%s %s",tmpCF,tmpPWD) == 2 ){
        if(strcmp(cf,tmpCF) == 0 && strcmp(password,tmpPWD) == 0){
            flag = 1;
            fclose(fp);
            break;
        } 
    }
    if (flag == 1){
        menuPaziente(cf);
        return;
    }
    printf("\n Credenziali non valide.\n\n");
    printf("-Riprovare [1]\n");
    printf("-Torna indietro [2]\n");
    printf("--Seleziona: ");
    char opt[100];
    scanf("%s",opt);
    if (atoi(opt) == 1){
        loginPaziente();
    }
    return;
}

void richiediPrenotazione(char *cf){
    if(giaRichiestaPrenotazione(cf) == 1){
        system("clear");
        pause("Hai già fatto una richiesta di appuntamento!\n");
        return;
    }
    system("clear");
    fflush(stdin);
    int nSintomi = 0;
    printf("%s digita '1' per confermare o '0' per negare\n\n",cf);
    char *sintomi[] = {"Febbre","Tosse secca","Affaticamento",
                       "Produzione di espettorato","Problemi respiratori","Dolori muscolari",
                       "Mal di gola","Mal di testa","Vomito",
                       "Diarrea","Disgeusia","Anosmia"};
    for (int i = 0; i < 12; i++)
    {   
        char confirm[100];
        printf("%s: ",sintomi[i]);
        scanf("%s",confirm);
        if(atoi(confirm) == 1)
            nSintomi++;
    }
    FILE *fp = fopen("files/richiestePrenotazioni.txt","a");
    if (fp)
    {
        fprintf(fp,"%s %d\n",cf,nSintomi);
        fclose(fp);
    }
}

int giaRichiestaPrenotazione(char *cf){
    fflush(stdin);
    FILE *fp = fopen("files/richiestePrenotazioni.txt","r");
    char tmpcf[100];
    int tmpnsintomi;
    while (fscanf(fp,"%s %d",tmpcf,&tmpnsintomi) == 2)
    {
        if(strcmp(cf,tmpcf) == 0){
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0; 
}

void visualizzaAppuntamentoPaziente(char *cf){
    system("clear");
    FILE *fp;
    char tmpcf[60],tmpOrario[20];
    int nsintomi;
    fp = fopen("files/prenotazioni.txt","r");
    if (fp)    {
        while (fscanf(fp,"%s %d %s",tmpcf,&nsintomi,tmpOrario) == 3){
            char msg[100];
            if (strcmp(cf,tmpcf) == 0){
                sprintf(msg,"%s hai appuntamento di %s",cf,tmpOrario);
                fclose(fp);
                pause(msg);
                return;
            }
        }
        pause("Non hai appuntamenti fissati.");
    }else{
        pause("Impossibile leggere il file!");
    }
}

void cancellaAppuntamentoPaziente(char *cf){
    char cftmp[60],orariotmp[30];
    int sintomitmp, trovato = 0;
    Prenotazioni *tmp, *lista = NULL;
    FILE *fp;

    system("clear");

    fp = fopen("files/prenotazioni.txt","r");
    if (fp){
        while (fscanf(fp,"%s %d %s",cftmp,&sintomitmp,orariotmp) == 3){
            if (strcmp(cf,cftmp) == 0){
                trovato = 1;
                continue;
            }
            tmp = creaNodoPrenotazioni(cftmp,sintomitmp,orariotmp);
            lista = inserisciPrenotazioneInLista(lista,tmp);
        }
        fclose(fp);
    }else{
        pause("Si è verificato un errore di lettura dei dati");
        return;
    }

    fp = fopen("files/prenotazioni.txt","w");
    if (fp){
        while (lista){
            fprintf(fp,"%s %d %s\n",lista->cf,lista->numero_s,lista->orario);
            tmp = lista;
            lista = lista->next;
            free(tmp);
        }
        fclose(fp);
    }else{
        pause("Si è verificato un errore di lettura dei dati");
        return;
    }
    if (trovato == 0){
        pause("Non hai nessun appuntamento fissato!\n"); 
    }else{
        pause("Appuntamento rimosso correttamente!\n"); 
    }
}

void visualizzaEsitoTampone(char *cf){
    system("clear");
    FILE *fp;
    char tmpcf[60],esito[20],tmpesito[20],msg[100];
    int trovato = 0;
    fp = fopen("files/storicoTamponi.txt","r");
    if (fp){
        while (fscanf(fp,"%s %s",tmpcf,tmpesito) == 2){
            if (strcmp(cf,tmpcf) == 0){
                trovato = 1;
                strcpy(esito,tmpesito);
            }
        }
        fclose(fp);
    }

    if (trovato == 0){
        pause("Non hai effettuato alcun tampone!");
    }else{
        sprintf(msg,"Il risultato del tuo ultimo tampone è: %s",esito);
        pause(msg);
    }
}



//? FUNZIONI LABORATORIO
void fissaAppuntamenti(){
    system("clear");
    Pazienti *lista = NULL;
    Pazienti *nodo;
    Pazienti *tmp;
    FILE *fp;
    char tmpCF[60];
    int tmpS,index = 0;

    //!Compilo la lista
    fp = fopen("files/richiestePrenotazioni.txt","r");
    if (fp){
        while (fscanf(fp,"%s %d",tmpCF,&tmpS) == 2){
            nodo = creaNodoPazienti(tmpCF,tmpS);
            lista = inserisciPerSintomi(lista,nodo);
        }
        fclose(fp);
    }else{
        pause("Si è verificato un problema con il file richiestaPrenotazioni.txt");
    }
    
    //!Compilo le prenotazioni
    fp = fopen("files/prenotazioni.txt","a");
    if (fp){
        lista = registraAppuntamentiDelGiorno(fp, lista,index);
        fclose(fp);
    }else{
        pause("Si è verificato un problema con il file prenotazioni.txt");
    }

    //!Scrivi sulle richieste i clienti non prenotati
    fp = fopen("files/richiestePrenotazioni.txt", "w");
    if (fp){
        while (lista){
            fprintf(fp,"%s %d\n",lista->cf,lista->numero_s + 1);
            tmp = lista;
            lista = lista->next;
            free(tmp);
        }
        fclose(fp);
    }else{
        pause("Si è verificato un problema con il file prenotazioni.txt pt2");
    }
    
    //deallocaListaPazienti(lista);
    pause("Tutti gli appuntamenti sono stati fissati\n");
}

Pazienti *registraAppuntamentiDelGiorno(FILE *fp,Pazienti *lista, int index){
    char orario[20];
    if (lista != NULL && index < 6){
        switch (index){
            case 0:
                strcpy(orario,"Mattina");
                break;
            case 1:
                strcpy(orario,"Mattina");
                break;
            case 2:
                strcpy(orario,"Pomeriggio");
                break;
            case 3:
                strcpy(orario,"Pomeriggio");
                break;
            case 4:
                strcpy(orario,"Sera");
                break;
            case 5:
                strcpy(orario,"Sera");
                break;
        }
        fprintf(fp,"%s %d %s\n",lista->cf,lista->numero_s,orario);
        Pazienti *tmp;
        tmp = lista;
        lista = lista->next;
        free(tmp);
        return registraAppuntamentiDelGiorno(fp,lista,index+1);
    }
    return lista;
}

void visualizzaAppuntamentiFissati(){
    system("clear");
    FILE *fp;
    char tmpcf[60],tmpOrario[20];
    int nsintomi,trovato = 0;
    fp = fopen("files/prenotazioni.txt","r");
    if (fp){
        while (fscanf(fp,"%s %d %s",tmpcf,&nsintomi,tmpOrario) == 3){
            if (trovato == 0){
                printf("Prenotazioni fissate:\n\n");
                trovato = 1;
            }
            printf("-%s ha appuntamento di %s\n",tmpcf,tmpOrario);
        }
        fclose(fp);
    }else{
        pause("Impossibile leggere il file!");
    }

    if (trovato == 0){
        pause("Non ci sono appuntamenti fissati!");
    }else{
        pause("");
    }

}

void aggiungiManLab(){
    char cf[60], orario[30],choice[100],nSintomi[100];
    FILE *fp;
    system("clear");
    printf("Inserisci codice fiscale: ");
    scanf("%s",cf);
    printf("Inserici numero sintomi: ");
    scanf("%s",nSintomi);
    printf("Seleziona fascia oraria:\n -Mattina [1]\n -Pomeriggio [2]\n -Sera [3]\nSeleziona: ");
    scanf("%s",choice);
    switch (atoi(choice)){
        case 1:
            sprintf(orario,"%s","Mattina");
            break;
        case 2:
            sprintf(orario,"%s","Pomeriggio");
            break;
        case 3:
            sprintf(orario,"%s","Sera");
            break;
        default:
            sprintf(orario,"%s","Mattina");
            break;
    }
    fp = fopen("files/prenotazioni.txt","a");
    if (fp){
        fprintf(fp,"%s %d %s\n",cf,atoi(nSintomi),orario);
        fclose(fp);
        pause("Appuntamento registrato correttamente\n");
    }else{
        pause("Si è verificato un errore!");
    }
}

void rimuoviManLab(){
    char cf[60],cftmp[60],orariotmp[30];
    int sintomitmp, trovato = 0;
    Prenotazioni *tmp, *lista = NULL;
    FILE *fp;

    system("clear");
    printf("Inserisci il codice fiscale da eliminare: ");
    scanf("%s",cf);

    fp = fopen("files/prenotazioni.txt","r");
    if (fp){
        while (fscanf(fp,"%s %d %s",cftmp,&sintomitmp,orariotmp) == 3){
            if (strcmp(cf,cftmp) == 0){
                trovato = 1;
                continue;
            }
            tmp = creaNodoPrenotazioni(cftmp,sintomitmp,orariotmp);
            lista = inserisciPrenotazioneInLista(lista,tmp);
        }
        fclose(fp);
    }else{
        pause("Si è verificato un errore di lettura dei dati");
        return;
    }

    fp = fopen("files/prenotazioni.txt","w");
    if (fp){
        while (lista){
            fprintf(fp,"%s %d %s\n",lista->cf,lista->numero_s,lista->orario);
            tmp = lista;
            lista = lista->next;
            free(tmp);
        }
        fclose(fp);
    }else{
        pause("Si è verificato un errore di scrittura dei dati");
        return;
    }
    if (trovato == 0){
        pause("Codice fiscale non trovato nella lista degli appuntamenti!\n"); 
    }else{
        pause("Appuntamento rimosso correttamente!\n"); 
    }
}

void visualizzaStoricoTamponi(){
    system("clear");
    FILE *fp;
    char tmpcf[60],esito[20];
    int trovato = 0;
    fp = fopen("files/storicoTamponi.txt","r");
    if (fp){
        while (fscanf(fp,"%s %s",tmpcf,esito) == 2){
            if (trovato == 0){
                printf("Lista tamponi effetuati:\n\n");
                trovato = 1;
            }
            printf("-Paziente: %s [%s]\n",tmpcf,esito);
        }
        fclose(fp);
    }

    if (trovato == 0){
        pause("Non sono stati effettuati tamponi!");
    }else{
        pause("");
    }
}

void visualizzaPazientiPositivi(){
    system("clear");
    FILE *fp;
    char tmpcf[60],esito[20];
    int trovato = 0;
    fp = fopen("files/positivi.txt","r");
    if (fp){
        while (fscanf(fp,"%s %s",tmpcf,esito) == 2){
            if (trovato == 0){
                printf("Pazienti attualmente positivi:\n\n");
                trovato = 1;
            }
            printf("-%s \n",tmpcf);
        }
        fclose(fp);
    }else{
        pause("Impossibile leggere il file!");
    }

    if (trovato == 0){
        pause("Non ci sono pazienti positivi!");
    }else{
        pause("");
    }
}



//* FUNZIONI PIATTAFORMA
void registraTamponiPiattaforma(){
    system("clear");
    char cftmp[60],orariotmp[30],esito[20];
    int sintomitmp;
    Prenotazioni *tmp, *lista = NULL;
    Risultato  *listaRisultati = NULL,*nodoRisultato;
    FILE *fp, *fp2;
    srand((unsigned)time(NULL));
    
    //? LEGGI PRENOTAZIONI
    fp = fopen("files/prenotazioni.txt","r");
    if (fp){
        while (fscanf(fp,"%s %d %s",cftmp,&sintomitmp,orariotmp) == 3){
            tmp = creaNodoPrenotazioni(cftmp,sintomitmp,orariotmp);
            lista = inserisciPrenotazioneInLista(lista,tmp);
        }
        fclose(fp);
    }else{
        pause("Si è verificato un errore di lettura dei dati");
        return;
    }

    fp = fopen("files/prenotazioni.txt","w");
    if (fp){
        fputs("",fp);
        fclose(fp);
    }else{
        pause("Si è verificato un errore di scrittura dei dati");
        return;
    }
    
    fp = fopen("files/storicoTamponi.txt","a");
    if (fp){
        while (lista){
            sprintf(esito,"%s",generaEsito());
            fprintf(fp,"%s %s\n",lista->cf,esito);
            nodoRisultato = creaNodoRisultato(lista->cf,esito);
            listaRisultati = inserisciRisultatoInLista(listaRisultati,nodoRisultato);
            lista = lista->next;
        }
        fclose(fp);
    }else{
        pause("Si è verificato un errore di scrittura dei dati");
        return;
    }
    if(listaRisultati){
        aggiornaPositivi(listaRisultati);
    }
    deallocaListaRisultati(listaRisultati);
    pause("Tutti i tamponi sono stati registrati sulla piattaforma");
}

char *generaEsito(){
    int r = rand();
    if (r%10 < 5)
    {
        return "Positivo";
    }else{
        return "Negativo";
    }
}

void aggiornaPositivi(Risultato *listaNuoviRisultati){
    if (listaNuoviRisultati){
        if (strcmp(listaNuoviRisultati->esito,"Positivo") == 0){
            registraEsito(listaNuoviRisultati->cf,1);
        }else{
            registraEsito(listaNuoviRisultati->cf,0);
        }
        aggiornaPositivi(listaNuoviRisultati->next);
    }
}

void registraEsito(char *cf,int esito_bool){
    char cftmp[60],esito[30];
    int sintomitmp, trovato = 0;
    Risultato *tmp, *lista = NULL;
    FILE *fp;
    if(esito_bool){
        fp = fopen("files/positivi.txt","r");
        if (fp){
            while (fscanf(fp,"%s %s",cftmp,esito) == 2){
                if (strcmp(cf,cftmp) == 0){
                    trovato = 1;
                }
            }
            fclose(fp);
        }else{
            pause("Si è verificato un errore di lettura dei dati");
            return;
        }

        if(trovato == 1)
            return;
        fp = fopen("files/positivi.txt","a");
        if (fp){
            fprintf(fp,"%s %s\n",cf,"Positivo");
            fclose(fp);
        }else{
            pause("Si è verificato un errore di lettura dei dati E2");
            return;
        }
    }else{
        fp = fopen("files/positivi.txt","r");
        if (fp){
            while (fscanf(fp,"%s %s",cftmp,esito) == 2){
                if (strcmp(cf,cftmp) == 0){
                    trovato = 1;
                    continue;
                }
                tmp = creaNodoRisultato(cftmp,esito);
                lista = inserisciRisultatoInLista(lista,tmp);
            }
            fclose(fp);
        }else{
            pause("Si è verificato un errore di lettura dei dati");
            return;
        }

        fp = fopen("files/positivi.txt","w");
        if (fp){
            while (lista){
                fprintf(fp,"%s %s\n",lista->cf,lista->esito);
                tmp = lista;
                lista = lista->next;
                free(tmp);
            }
            fclose(fp);
        }else{
            pause("Si è verificato un errore di lettura dei dati");
            return;
        }
    }
}