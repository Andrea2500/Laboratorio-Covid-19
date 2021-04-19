#include "../headers/loader.h"

//*Gestione lista pazienti
Pazienti *creaNodoPazienti(char cf[64], int sintomi) {
    Pazienti *tmp;
    tmp = (Pazienti *)malloc(sizeof(Pazienti));
    if(tmp) {
        strcpy(tmp->cf, cf);
        tmp->numero_s = sintomi;
        tmp->next = NULL;
    }
    return tmp;
}

void stampaListaPazienti(Pazienti *lista) {
    if(lista) {
        printf("Codice fiscale: %s, numero di sintomi: %d\n", lista->cf, lista->numero_s);
        stampaListaPazienti(lista->next);
    }
    else {
        printf("\n");
    }
}

Pazienti *inserisciPerSintomi(Pazienti *lista, Pazienti *pazienti) {
    if(!lista) {
        return pazienti;
    }
    if(pazienti->numero_s > lista->numero_s) {
        pazienti->next = lista;
        return pazienti;
    }
    lista->next = inserisciPerSintomi(lista->next, pazienti);
    return lista;
}

void deallocaListaPazienti(Pazienti *lista) {
  if(!lista) {
    return;
  } else{
    deallocaListaPazienti(lista->next);
    free(lista);
  }
}

//!Gestione lista prenotazione
Prenotazioni *creaNodoPrenotazioni(char cf[64], int sintomi, char orario[30]) {
    Prenotazioni *tmp;
    tmp = (Prenotazioni *)malloc(sizeof(Prenotazioni));
    if(tmp) {
        strcpy(tmp->cf, cf);
        strcpy(tmp->orario, orario);
        tmp->numero_s = sintomi;
        tmp->next = NULL;
    }
    return tmp;
}

void stampaListaPrenotazioni(Prenotazioni *lista) {
    if(lista) {
        printf("Codice fiscale: %s, numero di sintomi: %d, orario di visita: %s\n", lista->cf, lista->numero_s,lista->orario);
        stampaListaPrenotazioni(lista->next);
    }
    else {
        printf("\n");
    }
}

Prenotazioni *inserisciPrenotazioneInLista(Prenotazioni *lista, Prenotazioni *prenotazione) { 
    if(lista) {
        lista->next = inserisciPrenotazioneInLista(lista->next, prenotazione);
    } else {
        lista = prenotazione;
    }
    return lista;
}

void deallocaListaPrenotazioni(Prenotazioni *lista) {
  if(!lista) {
    return;
  } else{
    deallocaListaPrenotazioni(lista->next);
    free(lista);
  }
}


//?Gestione lista risultati

Risultato *creaNodoRisultato(char cf[64], char esito[30]) {
    Risultato *tmp;
    tmp = (Risultato *)malloc(sizeof(Risultato));
    if(tmp) {
        strcpy(tmp->cf, cf);
        strcpy(tmp->esito, esito);
        tmp->next = NULL;
    }
    return tmp;
}

void stampaListaRisultati(Risultato *lista) {
    if(lista) {
        printf("Codice fiscale: %s [%s]\n", lista->cf, lista->esito);
        stampaListaRisultati(lista->next);
    }
    else {
        printf("\n");
    }
}

Risultato *inserisciRisultatoInLista(Risultato *lista, Risultato *risultato) { 
    if(lista) {
        lista->next = inserisciRisultatoInLista(lista->next, risultato);
    } else {
        lista = risultato;
    }
    return lista;
}

void deallocaListaRisultati(Risultato *lista) {
  if(!lista) {
    return;
  } else{
    deallocaListaRisultati(lista->next);
    free(lista);
  }
}


