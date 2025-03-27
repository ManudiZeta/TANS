Il presente progetto inscena i processi di simulazione e ricostruzione FAST2, che avvengono in un esperimento a collider, nell'ipotesi che le particelle siano ultra relativistiche. Quest'ultima permette di trascurare l'effetto di un ipotetico campo magnetico, implicando solo traiettorie rettilinee.  



*** MACROSTRUTTURA ***

Si articola in 4 directories principali:

-work_TANS --> conserva il cuore della consegna, ossia le macro per avviare la simulazione, la rivelazione e la ricostruzione (residui e event display aggiuntivi)

-classes_TANS --> vi sono le classi impiegate durante lo svolgimento della consegna


-dat_TANS --> raccoglie alcune distribuzioni utili sulla cinematica delle particelle, oltre ai risultati ( organizzati in TTree ) delle suddette fasi, conservati all'interno di file .root

-results_TANS --> raccoglie immagini salienti di grandezze o screenshot del rivelatore, relativo alla simulazione. Si consiglia, comunque, di guardare i dati / risultati completi sui file .root presenti nella precedente directory, organizzati come TTree oppure di scorrere i risultati stampati a video


*** CLASSI ***

*Points_TANS*

- cPoint = implementa il concetto di punto (x, y, z) in coordinate cartesiane
- cilPoint = classe che implementa il concetto di punto (Raggio, Phi, Z) in coordinate cilindriche. Utile per lo sparpagliamento dovuto allo smearing
- pAng = classe di supporto per trattare gli angoli, soprattutto  per collegare la grandezza pseudorapidità all'angolo theta


*detectors_TANS*

- dLayer.h = classe che implementa il concetto di detector di raggio r, lunghezza l e spessore w. Costruisce anche l'ambiente per l'event display, sfruttando la classe TGeo
- smLayer = classe di supporto che implementa lo smearing dovuto al processo di rivelazione e di generazione di rumore nei rivelatori


*Phy_tans*

- pKinematic = classe che si incarica della cinematica legata alle particelle in relazione ai rivelatori (controllare che stiano dentro ai layer e determinare le intersezioni)
- rTklet = classe che, in fase di ricostruzione, accoppia i phi di diversi layer, determinando potenziali z_rec. Quest'ultimi vengono scremati e raccolti in un unico Z-rec, attraverso un processo di running window (dimensionabile) su un vector
- multS = classe di supporto che implementa il multiple scattering dovuto al processo fisico di scattering, ruotando un vettore di componenti angolari (phi, theta)
- lHit = classe che accorpa un cPoint e il raggio del Layer. Serve per descrivere un hit, fornendone coordinate e layer su cui avviene


*infrast_TANS*

-sConj = classe di infrastruttura utile ad alcune stampe di dati




*** ESEMPIO OPERATIVO ***

Preservando la gerarchia delle directories, ci si colloca in ../work_TANS, per poi aprire una sessione ROOT, nel quale si svolgono in sequenza i seguenti step.

STEP 0) Caricamento del necessario

Interpreto la macro ".x compiler_TANS.C", che serve a caricare tutte le classi e le macro operative. Tempo impiegato: circa 2 minuti 


STEP 1) Produzione della realtà Monte Carlo (SIMULAZIONE)

Lancio una simulazione chiamando la funzione " simulaz_TANS (int n_eve, bool MS, string mul_sel ) ", che ha diversi argomenti, come il numero di eventi da simulare (collisioni p-p), la presenza di multiple scattering o meno e la scelta della distribuzione di molteplicità, che può essere quella assegnata, quella uniforme o un valore fisso, che va messo tra " " . Il programma è creato in modo tale per cui verrebbe stampata una frase di controllo e di guida, qualora si sbagliasse input.

Viene salvato un file, che di default si chiama "MC_truth.root", ovvero la realtà fisica estranea ai processi di rivelazione, all'interno della directory dat_TANS. Questo file contiene un TTree che conserva variabili come la posizione del vertice di ogni evento, la molteplicità, la posizione degli hit sulla beam pipe e sui rivelatori e gli angoli .
A schermata viene riportata la frequenza di produzione di eventi ( circa 1000 eventi/s con distro assegnata )



STEP 2) Avviamento del processo di RIVELAZIONE

Dopo aver creato il processo fisico puro, ha luogo il processo di rivelazione: si lancia la funzione "dataReal_TANS (bool spur, double noise)". Questa ricrea il comportamento dei due layer in silicio, implementando anche la risposta in termini di risoluzione del rivelatore, attraverso un processo di smearing gaussiano. 
Gli argomenti sono opzionabili affinché venga anche inscenata la presenza di rumore (spur = 1) o meno (spur = 0) e, nel primo caso, si può anche decidere, tunando opportunamente l'argomento noise, la quantità di rumore da iniettare. Se noise = 0, non si ha rumore. Se noise = 1, si è sommersi totalmente dal rumore.

Viene creato il file "data.root", che rappresenta il pool di dati simulato a seguito della rivelazione. Al suo interno vi sono gli hit sui layer 2 e 3, che corrispondono ai rivelatori. Questo è il dataset reale, ovvero quello che ci si aspetta di ottenere a seguito di una presa dati 



STEP 3) Creazione del processo di RICOSTRUZIONE (della z del vertice d'interazione)

Si avvia un processo di ricostruzione del vertice di questi dati simulati presenti sul file "data.root", chiamando la funzione ricostruz_TANS( double window ), che si incarica di prendere gli oggetti creati dalla rivelazione e di determinare la posizione del vertice evento per evento, salvando tutto nel file "ricostruz.root". Si può scegliere quanto essere "elastici" nella restrizione del dataset z_rec attraverso la scelta di window, che modula la rispettiva finestra di taglio in unità di deviazione standard. 


STEP 4) Scarti tra Z_true e Z_rec

Si lancia la funzione " residues_TANS () " che preleva Z_true e Z_rec dai rispettivi TTree e ne stampa il residuo.


STEP 5)

Si lancia la funzione " TGeo_personal(int ev) ", che si incarica di svolgere un event display ( molto rudimentale ) della realtà Monte Carlo e come argomento ha il numero dell'evento che si vuole rappresentare. Viene ristampato il risultato finale, ossia il Z_true e Z_rec. 
Per una miglior interfaccia, si consiglia di utilizzare un 3D Viewer quale OpenGL, selezionabile direttamente dal TCanvas in uscita (View -> View With -> OpenGL)






