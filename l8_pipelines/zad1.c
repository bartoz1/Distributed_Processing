#include <unistd.h>
#include <stdio.h>
#define ODCZYT 0
#define ZAPIS 1

char* allLower(char* text) {
    int n = strlen(text);
    for(int i=0; i<n; i++)
        if (text[i] >= 'a')
            text[i] = text[i] - 32;
    return text;
}

int main () {

    int potok [2];
    int x;
    char buffer[50];

    char tekst[] = "HEllOwWorl";
    //allLower(tekst);
    //printf("%s \n", tekst);

    puts (" Program pipes startuje ") ;
    puts (" Tworze potok ") ;
    pipe ( potok ) ;
    puts (" fork ") ;
    if ( fork () ) {
        puts (" Proces macierzysty ") ;
        close ( potok [ ZAPIS ]) ;
        
        
        puts (" PRoces macierzysty czeka na wiadomosc ") ;
        read ( potok [ ODCZYT ] , &buffer , sizeof ( &buffer ) ) ;
        puts(" PROCES MACIERZYSTY OTRZYMUJE:");
        puts(buffer);
        


        //puts("TEkst: ");
        //puts(buffer);
    }
    else {
        
        int potoki2[2];
        close(potok[ODCZYT]);

        pipe(potoki2);

        if (fork()) {
            puts (" Proces potomny1 - zmieniajacy litery") ;
            close(potoki2[ZAPIS]);
            read ( potoki2 [ ODCZYT ] , &buffer , sizeof ( &buffer ) ) ;
            allLower(buffer);
            puts(" Proces potomny1 wysyla zmieniona wiadomosc" );
            write ( potok [ ZAPIS ] , &buffer , sizeof ( &buffer ) ) ;
            

            close(potoki2[ODCZYT]);
            close ( potok [ ZAPIS ]) ;
            close ( potok [ ODCZYT ]) ;

        } 
        else {
            puts(" Proces2 - odczytujacy");
            close ( potoki2 [ ODCZYT ]) ;
            puts("podaj testk: ");
            gets(buffer);
            puts (" Proces potomny2 wyslal wczytana wiadomosc ") ;
            write ( potoki2 [ ZAPIS ] , &buffer , sizeof ( &buffer ) ) ;
            close ( potoki2 [ ZAPIS ]) ;
            
        }

        
    }
    
}