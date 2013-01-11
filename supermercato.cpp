/*
Puddu Andrea 4a A INFO. 23-05-05
Programma per gestire il magazzino di un supermarket.
Realizzato a scopi didattici.
Sono presenti funzioni relative a:
-Inserimento
-Visualizzazione
-Ricerca
-Cancellazzione logica
*/

# include <iostream.h>
# include <conio.h>
# include <string.h>
# include <stdio.h>

//struttura del record
typedef struct {
					char codice[11+1];
               char marca[20+1];
               double prezzo;
               int quantita;
               char misura[2+1];
					char descrizione[50+1];
               bool cancellato;
               } item;

//definizione delle funzioni
int CopyFile (item articoli, FILE * f);
void insert(item articoli, FILE * f);
void show(item articoli, FILE * f);
void showInfo(item articoli);
int find(item articoli, FILE * f);
char MainMenu();
void InsertInterface();
void ShowInterface();
char FindMenu();
char SubFindMenu();

int main ()
{

 FILE * f;
 char scelta;
 bool fine=false;
 item articoli;

 clrscr();
 textcolor(15);
 cout<<"\n\n\n\n\n\n\n\n\n\n\n";
 cprintf("*******************************************************************************\r\n\r\n\r\n\r\n");
 textcolor(10);
 cprintf("                               S U P E R M A R K E T                   \r\n\r\n\r\n");
 textcolor(11);
 cprintf("                                      store                            \r\n\r\n\r\n\r\n");
 textcolor(15);
 cprintf("*******************************************************************************");
 getch();

  do
	{
	 scelta=MainMenu();

  	 switch (scelta)
  	  {
  		case 'i':   insert(articoli,f);
  		break;
  		case 'v':   show(articoli,f);
  		break;
      case 'r':   find(articoli,f);
      break;
  		case 'e':   fine=true;
  		break;
  	  }
	}
  while (fine != true );

return 0;
}

//DEFINIZIONE DEI SOTTOPROGRAMMI

//Funzione che copia un record in un file. Restituisce:
//0 se la scrittura va a buon fine
//altrimenti 1, in caso di errore

int CopyFile (item articoli, FILE * f)
{
 int stato=1;
 f=fopen ("c:\\articoli.dat","a+b");
 if (f!=NULL)
   {
	  fwrite (&articoli, sizeof(item),1,f);
     stato=0;
     cout <<"\n\nInserito in archivio. ";
   }
 else
   cout <<"ERRORE!"<<endl;
 fclose(f);
 return stato;
}

//Funzione per l'inserimento sequenziale di un articolo in archivio.

void insert(item articoli, FILE * f)
{
  char risp;
   do
  	 {
    InsertInterface(); //menu di inserimento
      //legge il codice (alfanumerico,11 caratteri)
       do {
 		gotoxy(25,5);
      clreol();
		gets(articoli.codice);
         } while(strlen(articoli.codice)!=11);
      //legge la marca( max 20 caratteri)
       do {
 		gotoxy(25,6);
      clreol();
 		gets(articoli.marca);
         } while(strlen(articoli.marca)>20);
      //legge il prezzo (0, double]
      do {
		gotoxy(25,7);
      clreol();
 		cin>>articoli.prezzo;
         } while(articoli.prezzo <= 0 && articoli.prezzo > (sizeof(double)));
      //legge la quantita (0,10000)
      do {
 		gotoxy(25,8);
      clreol();
 		cin>>articoli.quantita;
         } while(articoli.quantita >9999 && articoli.quantita <=0);
      //legge l'unita di misura (kili,litri,pezzi)
      do {
 		gotoxy(25,9);
      clreol();
 		gets(articoli.misura);
      } while(strcmp(articoli.misura,"kg")!= 0 && strcmp(articoli.misura,"pz")!=0 && strcmp(articoli.misura,"l")!=0);
      //legge la descrizione (max 50 caratteri)
      do {
 		gotoxy(25,10);
      clreol();
 		gets(articoli.descrizione);
         } while(strlen(articoli.descrizione)>50);
      articoli.cancellato=false;
 		gotoxy(1,75);

      CopyFile(articoli,f); //inserisce l'articolo in archivio
      
 		cprintf("\r\n Un'altro articolo? (s/n) ");
 		do { risp=getch(); } while (risp!= 'n' && risp!= 's') ;
  }
  while (risp!='n') ;
}

//Funzione per la visualizzazione sequenziale degli articoli in archivio
void show(item articoli, FILE * f)
{
  char risp;
  f=fopen ("c:\\articoli.dat","rb");
  if (f!=NULL)
   {
    rewind(f); //posiziona il puntatore al file all'inizio
    while(fread(&articoli, sizeof(item),1,f) >0 && risp !='n' && articoli.cancellato==false)
     {
      //visualizza le informazioni
      ShowInterface();
      showInfo(articoli);
      cprintf("\r\n Un'altro articolo? (s/n) ");
 	   do { risp=getch(); } while (risp!= 'n' && risp!= 's') ;
     }
   }
   else cout <<"ERRORE!"<<endl;
 fclose(f);
}

void showInfo(item articoli)
{
      gotoxy(25,5);
      clreol();
 puts(articoli.codice);
 		gotoxy(25,6);
      clreol();
 puts(articoli.marca);
		gotoxy(25,7);
      clreol();
 cout<<articoli.prezzo;
 		gotoxy(25,8);
      clreol();
 cout<<articoli.quantita;
 		gotoxy(25,9);
      clreol();
 puts(articoli.misura);
 		gotoxy(25,10);
      clreol();
 puts(articoli.descrizione);
}

//funzione per la ricerca di un articolo all'interno del file
//ricerca per: CODICE,MARCA,PREZZO
//Restituisce:
//0 se la ricerca va a buon fine, 1 altrimenti
//-1 se non trova il file o in caso di uscita da parte dell'utente
int find(item articoli, FILE * f)
{
 char scelta;
 char codice[11+1],marca[20+1];
 double prezzo;
 bool ripeti;
 int trovato;
 fpos_t filepos;
 do
 {
 ripeti=false;
 f=fopen ("c:\\articoli.dat","rb");    //apre il file in lettura
  if (f!=NULL)
   { rewind(f); }
   else return -1;
 scelta=FindMenu();
 trovato=0;
 switch (scelta)    //effettua le ricerche in base al campo scelto
  	  {
  		case 'c':
      cout<<"\nCodice: ";
      gets(codice);
      while(fgetpos(f,&filepos)== 0 && !trovato && articoli.cancellato !=true && fread(&articoli, sizeof(item),1,f)>0)
      {
       if(strcmp(codice,articoli.codice)==0)
       trovato=1;
      }
      break;
  		case 'm':
      cout<<"\nMarca: ";
      gets(marca);
      while(fgetpos(f,&filepos)== 0 && !trovato && articoli.cancellato !=true && fread(&articoli, sizeof(item),1,f)>0)
      {
       if(strcmp(marca,articoli.marca)==0)
       trovato=1;
      }
  		break;
      case 'p' :
      cout<<"\nPrezzo: ";
      cin>>prezzo;
      while(fgetpos(f,&filepos)== 0 && !trovato && articoli.cancellato !=true && fread(&articoli, sizeof(item),1,f)>0)
      {
       if(prezzo==articoli.prezzo)
       trovato=1;
      }
      break;
  		case 't':
  		return -1;
  	  }
   if (trovato==1)
    {
      fsetpos(f,&filepos);
      ShowInterface();
      showInfo(articoli);
      scelta=SubFindMenu();
      switch(scelta)
      {
       case 'c':
       cprintf("\n\rLA VOCE VERRA RIMOSSA DALL'ARCHIVIO. Continuare? (s/n) ");
       do {scelta=getch();} while(scelta !='n' && scelta !='s');
        if(scelta=='s')
        {
       articoli.cancellato=true;
       textcolor(12);
       cprintf("\r\nCANCELLATO!");
       getch();
         }
       break;
       case 'r': ripeti=true;
       break;
      }
    }
    else
    {
     cprintf("\r\nARTICOLO NON PRESENTE IN MAGAZZINO");
     ripeti=true;
     getch();
    }
    fclose(f);
    }
    while (ripeti!=false);
    return trovato;
}

//FUNZIONI DI INTERFACCIA PER L'UTENTE:
//-MENU PRINCIPALE
char MainMenu()
{
   char risp;
   clrscr();
   textcolor(14);
   cprintf("I");
   cout<<"nserisci articolo/i in archivio."<<endl;
   cprintf("V");
   cout<<"isualizza informazioni articoli."<<endl;
   cprintf("R");
   cout<<"icerca un articolo, Modifica, Cancella."<<endl;
   cprintf("E");
   cout<<"sci dal programma."<<endl;
   do { risp=getch(); }
   while (risp!= 'i' && risp!= 'v' && risp!= 'c' && risp!= 'r' && risp!= 'e') ;
   return risp;
}


//-INSERIMENTO
void InsertInterface()
{
 clrscr();
 textcolor(15);
 cprintf("\r\n------------------------------------------------------");
 textcolor(12);
 cprintf("\r\n           INSERISCI INFORMAZIONI ARTICOLO/I    ");
 textcolor(15);
 cprintf("\r\n------------------------------------------------------");
 textcolor(10);
 cprintf("\r\nCodice prodotto: ");
 cprintf("\r\nMarca: ");
 cprintf("\r\nPrezzo: ");
 cprintf("\r\nQuantita : ");
 cprintf("\r\nMisura (Kg,l,Pz): ");
 cprintf("\r\nDescrizione: ");
 textcolor(15);
 cprintf("\r\n------------------------------------------------------");
}

//-VISUALIZZAZIONE
void ShowInterface()
{
 clrscr();
 textcolor(15);
 cprintf("\r\n------------------------------------------------------");
 textcolor(12);
 cprintf("\r\n            INFORMAZIONI   ARTICOLO    ");
 textcolor(15);
 cprintf("\r\n------------------------------------------------------");
 textcolor(10);
 cprintf("\r\nCodice: ");
 cprintf("\r\nMarca: ");
 cprintf("\r\nPrezzo: ");
 cprintf("\r\nQuantita: ");
 cprintf("\r\nMisura: ");
 cprintf("\r\nDescrizione: ");
 textcolor(15);
 cprintf("\r\n------------------------------------------------------");
}

//-RICERCA
char FindMenu()
{
 char risp;
   clrscr();
   textcolor(15);
   cprintf("\r\n------------------------------------------------------");
   textcolor(14);
   cprintf("\r\n          RICERCA UN ARTICOLO IN BASE AL \n\r");
   textcolor(15);
   cprintf("\r\n------------------------------------------------------\r\n");
   textcolor(14);
   cprintf("C");cout<<"odice"<<endl;
   cprintf("M");cout<<"arca"<<endl;
   cprintf("P");cout<<"rezzo"<<endl;
   cprintf("\n\rT");
   cout<<"orna al menu principale."<<endl;
   textcolor(15);
   cprintf("\r\n------------------------------------------------------\n\r");
   do { risp=getch(); }
   while (risp!= 'c' && risp!= 'm' && risp!= 'p' && risp!= 't') ;
 return risp;
}

//SOTTOMENU OPZIONI
char SubFindMenu()
{
 char risp;
   textcolor(15);
   cprintf("\r\n\r\n");
   textcolor(14);
   cprintf("C");cout<<"ancella"<<endl;
   cprintf("\n\rR");
   cout<<"itorna al menu di ricerca"<<endl;
   do { risp=getch(); }
   while (risp!= 'c' && risp!= 'm' && risp!= 'r') ;
 return risp;
}
