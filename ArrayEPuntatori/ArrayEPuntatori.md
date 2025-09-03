# ARRAY E PUNTATORI NON SONO LA STESSA COSA IN C!

## Gli array non sono puntatori 
Spesso si sente dire "Gli array sono la stessa cosa dei puntatori". Ma non è del tutto vero.
```C 
extern int *x;
extern int y[];
```
La prima riga dichiara x come ptr a un int.
La seconda dichiara y come array di int di dimensione non settata.

## Perché il mio codice non va?
Ecco una situazione classica:

file 1:
```C
int mango[100[;
```

file 2:

```C
extern int *mango;
```
Il primo file definisce mango come un array, ma il file 2 lo dichiara come un ptr. 
NON SONO LA STESSA COSA!

## Cos'è una dichiarazione? Cos'è Una definizione?
Ricordiamo un attimo la terminologia: un oggetto in C può avere una sola definizione e 
multiple dichiarazioni.
Una definizione è una dichiarazione particolare che crea un oggetto. 
Esempio:
```C 
int my_array[100];
```
Una dichiarazione indica un nome che ci permette di riferirci ad un oggetto.
```C
extern int my_array[];
```
La dichiarazione dice al compilatore il tipo e il nome dell'oggetto e che l'allocazione di 
memoria si farà altrove.

## Come si accede ad array e puntatori
Vediamo la differenza tra una reference che usa un array e una che usa un ptr. 
Innanzitutto distinguiamo tra l'indirizzo y e il contentuto dell'indirizzo y.
È una differenza sottile, am che dobbiamo considerare. Prendiamo il seguente assegnamento:
```C
x = y;
```
Il simbolo x è l'address ed è un l-value; gli l-value sono noti a compiletime e dicono dove
stoccare il risultato.
Il simbolo y è il contenuto dell'indirizzo che y rappresenta ed è un r-value, noto solo a runtime.
Il punto focale è che l'indirizzo di ogni simbolo è noto a compiletime, quindi il compilatore
può lavorare sugli indirizzi per aggiungere degli offset.
Il valore corrente di un puntatore, invece, deve essere recuperato a runtime prima di
dereferenziarlo.
In pratica con un array la prima cella ha un indirizzo pre-assegnato e l'accesso a celle
successive si fa prendendo l'indirizzo pre-assegnato e aggiungendogli il numero della cella:
```C
char a[9] = "abcdefgh"; /*...*/ c=a[i];
```
a ha indirizzo 9980. quindi prendiamo il valore di i, lo aggiungiamo a 9980 (9980+i) e
prendiamo il contenuto della cella.

Se dichiariamo
```C
char *p; /*...*/ c=*p;
```
Dobbiamo accedere a ciò che trova all'indirizzo di p e poi prendere il contenuto e usarlo
come indirizzo. In pratica prima prendiamo l'indirizzo del ptr e poi l'indirizzo di ciò a cui
punta.

## Cosa succede se definiamo un puntatore/reference come array?
Iniziamo a vedere il problema.
```C
char *p="abcdefgh"; /*...*/ c=p[i]
```
Il compilatore ha p nell'indirizzo 4624.
A runtime prendiamo il contenuto dell'indirizzo 4624, per esempio 5081
Aggiungiamo i ad 5081
Recuperiamo il contenuto all'indirizzo 5081+i

Quando scriviamo
```C
extern char *p;
```
e lo referenziamo come
```C
p[3]
```
Stiamo combinando i due quindi il il compilatore emette codice per:

1.Prendere l'indirizzo rappresentato da p e recupera il ptr.
2.Aggiunge l'offset che il subscript rappresenta al valore del ptr
3.Accede ai byte dell'indirizzo risultante.

Il compilatore sa che p è un ptr a un char. Siccome abbiamo dichiarato p come un ptr
l'accesso avviene in questo modo sia se p è definito come ptr o come array.
Quando prendiamo i contentuti di p[i] usando extern leggiamo il contenuto direttamente
senza fare il secondo salto, riempiendo il nostro codice di garbage.

## Fai corrsipondere le tue dichiarazioni alla definizione
Assicuriamoci che dichiarazioni e definizioni corrispondano.
```C
int mango[100];
```
file 2:
```C
extern int mango[];
```
La definizione di mango come array alloca spazio per 100 integers.

```C
int *raisin;
```
Invece la dichiarazione qui sopra richiede lo spazio per un puntatore di nome raisin che
punta ad un int o array di int. raisin sarà sempre nello stesso indirizzo, ma i suoi
contenuti possono cambiare.

## Altre differenza tra array e puntatori
### Puntatore:
* Contiene l'indirizzo dei dati
* Fa accedere ai dati in modo indiretto e se ha un subscript [i] si prende il contenuto
del ptr e gli si aggiunge i per poi usare il risultato come indirizzo.
* Si sua per strutture dati dinamiche
* Si usa spesso con malloc() e free()
* Spesso punta a dati anonimi

### Array:
* Contiene dati
* Fa accedere ai dati direttamente, per a[i] si accede ai contenuti della locazione a i unità da a.
* Si usa per mantenere un numero fisso di elementi dello stesso tipo
* È allocato e deallocato implicitamente
* È una variabile vera e propria.

Array e puntatori possono essere inizializzati con uno string literal nella definizione
```C
char *p="breadfruit";
```
Questo funziona SOLO per le stringhe. Cercare di cambiare la stringa scrivendo tramite p è
undefined behavior secondo lo std ANSI.
Al contrario il contentuto degli array inizializzati con uno string literal possono essere
cambiati.



# Altre informazioni sugli array

_"Non mangiare mai un posto chiamato "Da Mamma". Non giocare mai a carte con un uomo
chiamato "Doc.
E Mai e poi mai dimentica che C tratta un l-value di tipo array-di-T in una espressione con un puntatore al primo elemento dell'array."_

## Quando un array è un puntatore
Abbiamo visto prima la circostanza più comune in cui array e ptr non sono intercambiabili.
È molto comune che array e ptr siano intercambiabili.

Nel caso di una dichiarazione array e ptr NON sono equivalenti se non come parametri di
funzioni.
Nell'uso all'interno di espressioni (`c = a[i];`) invece tutto viene convertito in un ptr.
Le differenze generali rimangono, ovviamente.

## Come mai la confusione?
Perché molti pensano che array e ptr siano completamente interscambiabili? Perché nel
K&R 2 un cambio di pagina divide in due la spiegazione che array e ptr sono equivalenti nel
caso in cui siano parametri formali nella definizione di una funzione.
In più quando si lavora su un solo file è comune vedere cose come:
```C
char my_array[10];
char *my_ptr;
...
i=strlen(my_array);
j=strlen(my_ptr);
```

Oltre a cose come:
```C
printf("%s %s", my_ptr, my_array);
```
È facile non rendersi conto che ptr e array sono intercambiabili solo nel caso di
parametri a funzioni.
Peggio ancora si può scrivere:
```C
printf("l'array alla locazione %x contiene la stringa %s", a, a);
```
Idem per i parametri del `main`, `char **argv` o `char *argv[]`

Secondo lo standard C gli array SONO ptr quando:
* Il nome di un array in una espressione è trattato dal compilatore come un ptr al primo elemento dell'array
* Un subscript è sempre equivalente ad un offset da un ptr.
* Un array nella dichiarazione di un parametro a funzione è trattato del compilatore come un ptr al primo elemento dell'array.

Ci sono delle eccezioni che hanno a che vedere con gli array quando sono trattati nella loro
interezza.
Una reference ad un array NON è rimpiazzato da un ptr al primo elemento quando:
* sizeof()
* &
*

Vediamo un esempio.
`int a[10], *p, i=2;`
possiamo accedere ad a[i] in uno qualsiasi dei seguenti metodi:
```C
p=a;	p=a;	p=a+i;
p[i];	*(p+i);	*p;	
```
Il legame è ancora più forte:
* Ogni reference `a[i]` è sempre riscritta come `*(a+i)`
Il compilatore aggiusta la dimensione di i con la dimensione del tipo puntato:
nel caso degli int32_t (32 bit, 4 byte) `*(a+i);` diventa `(a+i*4);`
nel caso degli int64_t (64 bit, 8 byte) `*(a+i);` diventa `(a+i*8);`

### C tratta i subscript degli array come offset di puntatori
Questa regola deriva dal BCPL (l'antenato del C) e causa problemi nell'implementare
controlli a runtime per validare il range dell'array (accessi al di fuori dell'array).

### Un array nella dichiarazione di un parametro a funzione è un puntatore
Prima di partire un po' di terminologia.
Parametro: una variabile definita in una definizione di una funzione o nella dichiarazione
di una funzione prototipo. Alcuni lo chiamano "parametro formale".
* Esempio:
`int power(int base, int n);`
base ed in sono parametri.

Argomento:
È un valore usato in una particolare chiamata a funzione.
* Esempio:
`i = power(10, j)`
10 e j sono argomenti.
Siccome nel caso della definizione di fz il compilatore è obbligato a riscrivere un array in
un ptr al suo primo elemento vediamo che
```C
my_function(int *turnip) {...}
my_function(int turnip[]) {...}
my_function(int turnip[200]) {...}

```
Sono perfettamente equivalenti

## Sì, ma perchè?
La ragione è che l'equivalenza fu messa per favorire l'efficienza. Tutti gli argomenti
non-array sono passati effettuando una copia dell'argomento originale. Tuttavia copiare un
array è costoso; quindi si passa solo un puntatore all'array.
Possiamo passare i dati come ptr o array usando l'operatore 'indirizzo di', `&`.

## Come si fa una reference ad un parametro array
Si fa come si facesse un lookup di un ptr con subscript. 
Tuttavia a volte si fanno degli usi comuni di parametri attuali con intenti differenti.
* `func (&my_int);` Passiamo l'indirizzo di un int per fare una chiamata per reference.
* `func(my_int_ptr);`Passiamo un ptr ad un int
* `func(my_int_array);` Passiamo un array di int per passare un array.
* `func(&my_int_array[i]);`Passiamo l'indirizzo di un elemento di un array per passare una slice di array.
Da dentro `func()` è difficile capire come è stata effettuata la chiamata. Con il ptr
passato al posto dell'array possiamo effettuare le normali operazioni che faremmo sull'array
ma non possiamo controllare le dimensioni dell'array con `sizeof`.

## Il C ha gli array multidimensionali, ma tutti gli altri linguaggi li chiamano 'array di array'
Ada esplicita chiaramente che array multidimensionali e array di array sono cose diverse.
Pascal esplicita chiaramente che sono la stessa cosa.
Il C ha un approcio tutto suo: l'unico modo di definiere e referenziare gli array multidimensionali è tramite gli array di array.
Non possiamo collassare vari indici come `[i][j][j]` in una espressione simil-Pascal come:
`[i, j, k]`, possiamo, volendo, calcolare quanto valga l'offest di i, j e k e referenziarlo
con un subscript `[z]`.
Ancora peggio: [i, j, z] è un'espressione legale...

## Come gli array multidimensionali si dividono in componenti

Se abbiamo `int apricot[2][3][5]` apricot conterrà tutto l'array,
apricot[0] sarà la metà di apricot.
apricot[0][0] prenderà il primo degli elementi del sottoarray dalla prima metà di apricot.
e così via.
Il subscript più a destra è il più interno e varia più velocemente. 

## Come inizializzare gli array
Nel caso degli array monodimensionali:
```C
float banana[5] = {0.0, 1.0, 2.72, 3.14, 25.625};
float honeydew[]= {0.0, 1.0, 2.72, 3.14, 25.625}
```
Questo si può fare solo durante la dichiarazione.

Gli array multidimensionali invece possono essere inizializzati nestando le parentesi:
```C
short cantaloupe[2][5] = {
  {10, 12, 3, 4, -5},
  {31, 22, 6, 0, -5},
};

int rhubarb[][3] = { {0,0,0}, {1,1,1}};
Se le dimensioni dell'array è più grande dei valori iniziali le celle rimanenti saranno
settate a zero. Se sono puntatori sono settate a NULL.

Ecco come inizializzare un array di stringhe bidimensionale:
```C
char vegetables[][9] = {"beet",
			"barley",
			"basil",
			"broccoli",
			"beans"};
```
Una cosa comoda è preparare un array di puntatori: gli string literals possono essere usati
per inizializzare gli array e il compilatore stoccherà correttamente gli indirizzi nell'
array.
Quindi:
```C
char *vegetables[] = {"carrot",
     		      "celery",
		      "corn",
		      "cilantro",
		      "crispy fried potatoes"};
		      //funziona perfettamente.
```
SOLO gli string literals possono inizializzare gli array di ptr:
```C
int *weights[] = {
    	       {1,2,3,4,5},
	       {6,7},
	       {8,9,10}
};
//NON compila
```
Il trucco è creare le righe come array e usare i nomi degli array per inizializzare:
```C
int row_1[]= {1,2,3,4,5,-1}; //-1 è il marker di end-of-row
int row_2[]= {6,7,-1};
int row_3[]= {8,9,10};

int *weights[] = {
    	       	 row_1,
		 row_2,
		 row_3
};

```



# Aggiunte sui puntatori
_Non dimenticare mai che, quando punti il dito a qualcuno, tre delle tue dita stanno puntando a te..._
-Proverbio della spia sospettosa

## Il layout degli array multidimensionali
Gli array multidimensionali non sono comuni nella programmazioni di sistemi, e il C non
implementa dei runtime per supportarli.
Prendendo:
`char pea[4][6];`
Se accediamo a
`pea[i][j]`
il compilatore lo risolverà in:
`*(*(pea+i)+j)`
Ma il significato di "`pea[i]`" dipende da come abbiamo definito pea.

## Un array di puntatori è un "vettore di Iliffe"
Un effetto simile ad un array bidimensionale si può ottenere definendo un array di ptr a stringhe.
L'array deve essere inizializzato con puntatori alla memoria allocata per le stringhe.
Questo si fa a compile time con l'inizializzazione con string literals o a runtime così:
```C
for (j=0; j<4; j++) {
    pea[j] = malloc(6);
}
```
Oppure:
```C
malloc(row_size * column_size * sizeof(char));
```
E poi usando un loop per assegnare i puntatori alle locazioni in quella regione.
Come per un array multidimensionale i caratteri di un vettore di Iliffe saranno referenziati
con due indice, quindi
`pea[i][j]`
che decade in:
`*(*(pea+i)+j)`
come se fosse un array multidimensionale. Peccato che nei due casi il tipo di referenza
effettuata sia diversa...


Un problema è che vedere una reference `squash[i][j]` non ci dice se squash è dichiarato come
```C
int squash[23][12]; //array [23] di array [12] di int

//oppure:

int *squash[23]; //un vettore di Iliffe di 23 puntatori a int

//oppure

int **squash; //Un puntatore a puntatore di int

//o addirittura

int (*squash)[12]; //Un puntatore a un array di 12 int
```

Torniamo al vettore di Iliffe vs array-di-array
### Caso array-di-array
`char a[4][6]`
La tabella dei simboli del compilatore mantiene a come indirizzo 9980
* Passo 1 a runtime: prendi il valore _i_, scalalo per le dimensioni di una linea (6 bytes qui) e aggiungilo a 9980
* Passo 2 a runtime: prendi il valore _j_, scalalo per le dimensioni di un elemento (1 byte qui) e aggiungilo al risultato del Passo 1
* Passo 3 a runtime: prendi i contenuti dall'indirizzo (9980 + i*fattore-di-scala1+j*fattore-di-scala2)
Il lookup va all' i-esimo dei quattro array e prende il j-esimo carattere in quell'array.

### Caso array di puntatori a stringhe
`char *p[4]`
La tabella dei simboli del compilatore ha p come indirizzo 4624
* Passo 1 a runtime: prendi il valore _i_, scalalo per le dimensioni di un ptr (4 bytes qui) e aggiungilo a 4624.
* Passo 2 a runtime: prendi i contenuti dall'indirizzo (4624+valore scalato i), diciamo 5081
* Passo 3 a runtime: prendi il valore _j_, scalalo per la dimensione di un elemento, e aggiungilo a 5081.
* Passo 4 a runtime: prendi i contenuti dall'indirizzo 5081+j
`p[i][j]`

La regola per cui il nome di un array è riscritto come puntatore all'argomento non è ricorsive.
Quindi:
un array di array `char c[8][10];`	diventa `char (*c)[10]` ovver un ptr ad array
un array di puntatori `char *c[15];` 	diventa `char **c;` puntatore a puntatore
un puntatore ad array `char (*c)[64]` 	diventa `char (*c)[64]`
un puntatore a puntatore `char **c;` 	diventa `char **c;`

## Passaggio di un array a una funzione
Un array monodimensionale diventa sempre un puntatore al primo elemento.
Ma possiamo indicare esplicitamente le dimensioni dell'array in due modi:
* mandiamo un parametro aggiuntivo che ci specifica il numeri di elementi (`argc`)
* Diamo all'ultimo elemento dell'array un valore speciale che indica la fine dei dati; dobbiamo essere sicuri che altrimenti non apparirà mai.

## Uso dei puntatori per passare array multidimensionali a una funzione
Abbiamo un po' di problemi: demarcare le dimensioni degli array, ma sopratutto la dichiarazione dell'array dentro la funzione.
Il meglio che possiamo fare è trasformare `array[x][y]` in un array monodimensionale `array[x+1` dipuntatori ad `array[y]`, poi stocchiamo un NULL ptr nell'elemento più grande per indicare la fine dei ptr.

## Uso dei puntatori per ritornare un array da una funzione
Non possiamo ritornare un array direttamente, ma possiamo sempre ritornare dei puntatori.
`int (*paf())[20]`
_paf_ è una fz che ritorna un ptr ad un array di 20 int.
La definizione può essere:

```C
int (*paf())[20] {
    int (*pear)[20]; //ptr a un array di 20 elementi
    pear=calloc(20, sizeof(int));
    if (!pear) longjmp(error, 1);
    return pear;
}
```
Chiameremo la fz così:
```C
int (*result)[20];

result = paf();
(*result)[3]=12; //accesso all'array
```
Oppure possiamo usare una struct
```C
struct a_tag {
       int array[20];
} x, y;

struct a_tag my_function() {... return y}
//Ciò permette anche:

x=y;
x=my_function();
//al costo di:
x.array[i] = 38;
```

## Uso dei puntatori per creazione ed utilizzo di array dinamici
Usiamo gli array dinamici se non conosciamo a priori le dimensioni dei dati.
Nello GNU C è possibile dichiarare array le cui dimensioni sono settate a runtime
```C
// esempio con VLA (Variable Length Array)
int function(int x, int y) {
    char pippo[y];
    ....


}
```
Fortunatamente possiamo scrivere i nostri array dinamici.
L'idea di base è usarea _malloc()_ per ottenere un ptr ad un'area di memoria e poi referenziarla come un array, usando il fatto che un array con subscript decade in un ptr+offset.

```C
#include <stdlib.h>
#include <stdio.h>
...

int size;
char *dynamic;
char input[10];
printf("Enter the size of the array: ");
size= atoi(fgets(input, 7, stdin));
dynamic = (char *)malloc(size);
...
dynamic[0] = 'a';
dynamic[size-1]='z'
```
Per ora tutto bene. Ma esiste una funzione di libreria che rialloca un blocco di memoria esistente ad una dimensione diversa, mantenendo intatti i contenuti.
Se abbiamo una tabella dei simboli l'operazione è:
1) Controllare che la tabella sia già piena
2)Se lo è _realloc_ ad una dimensione maggiore, controllo che la riallocazione sia andata bene
3)Aggiungiamo il dato

In C:
```C
int current_element=0;
int total_element=128;
char *dynamic=malloc(total_element);

void add_element(char c) {
     if (current_element==total_element-1) {
     	total_element*=2;
	dynamic= (char *) realloc(dynamic, total_element);
	if (dynamic==NULL) perror("Table was not expanded");
     }
     current_element++;
     dynamic[current_element]= c;
}
```
In realtà non dovremmo assegnare il retvalue di _calloc_ al ptr originale o rischiamo di
perdere tutti i dati.


Il seguente file è basato sul libro "Expert C Programming - Deep C Secrets" di Peter Van Der Linden



