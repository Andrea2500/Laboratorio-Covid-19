//? Prototipi funzioni generali
void homemenu();
void pause(char *msg);

//! Prototipi intefaccia paziente
void menuPaziente(char *cf);

//! Prototipi intefaccia laboratorio
void menuLab();
void visualizzaRichiesteAppuntamenti();
void aggiungiRimuoviManualmenteLab();

//! Prototipi funzioni paziente
void registrati();
void loginPaziente();
void richiediPrenotazione(char *cf);
int giaRichiestaPrenotazione(char *cf);
void visualizzaAppuntamentoPaziente(char *cf);
void cancellaAppuntamentoPaziente(char *cf);
void visualizzaEsitoTampone(char *cf);

//! Prototipi funzioni laboratorio
void fissaAppuntamenti();
Pazienti *registraAppuntamentiDelGiorno(FILE *fp,Pazienti *lista,int index);
void visualizzaAppuntamentiFissati();
void aggiungiManLab();
void rimuoviManLab();
void visualizzaStoricoTamponi();
void visualizzaPazientiPositivi();

//! Prototipi funzioni piattaforma
void registraTamponiPiattaforma();
char *generaEsito();
void aggiornaPositivi(Risultato *lista);
void registraEsito(char *cf,int esito_bool);


//! Prototipi gestione lista pazienti
Pazienti *creaNodoPazienti(char cf[64], int sintomi);
void stampaListaPazienti(Pazienti *lista);
Pazienti *inserisciPerSintomi(Pazienti *lista, Pazienti *pazienti);
void deallocaListaPazienti(Pazienti *lista);

//! Prototipi gestione lista prenotazioni
Prenotazioni *creaNodoPrenotazioni(char cf[64], int sintomi, char orario[30]);
void stampaListaPrenotazioni(Prenotazioni *lista);
Prenotazioni *inserisciPrenotazioneInLista(Prenotazioni *lista, Prenotazioni *prenotazione);
void deallocaListaPrenotazioni(Prenotazioni *lista);

//! Prototipi gestione lista risultati
Risultato *creaNodoRisultato(char cf[64], char esito[30]);
void stampaListaRisultati(Risultato *lista);
Risultato *inserisciRisultatoInLista(Risultato *lista, Risultato *risultato);
void deallocaListaRisultati(Risultato *lista);
