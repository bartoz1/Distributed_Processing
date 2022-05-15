#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
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
    int x, f, f_intern;
    char buffer[50];
    mkfifo ( " test " , S_IRWXU ) ;
    mkfifo ( " intern " , S_IRWXU ) ;

    char tekst[] = "HEllOwWorl";
    //allLower(tekst);
    //printf("%s \n", tekst);

    puts (" Program pipes startuje ") ;
    puts (" Tworze potok ") ;
    // O_RDWR -- O_WRONLY -- O_RDONLY
    f = open (" test " , O_RDWR ) ;
    puts (" fork ") ;
    if ( fork () ) {
        puts (" Proces macierzysty ") ;
        //close ( potok [ ZAPIS ]) ;
        
        
        puts (" PRoces macierzysty czeka na wiadomosc ") ;
        read ( f , &buffer , sizeof ( &buffer ) ) ;
        puts(" PROCES MACIERZYSTY OTRZYMUJE:");
        puts(buffer);
        


        //puts("TEkst: ");
        //puts(buffer);
    }
    else {
        
        int potoki2[2];
        //close(potok[ODCZYT]);
        pipe(potoki2);

        if (fork()) {
            f_intern = open (" intern " , O_RDONLY ) ;
            puts (" Proces potomny1 - zmieniajacy litery") ;
            //close(potoki2[ZAPIS]);
            read ( f_intern, &buffer , sizeof ( &buffer ) ) ;
            allLower(buffer);
            puts(" Proces potomny1 wysyla zmieniona wiadomosc" );
            write ( f , &buffer , sizeof ( &buffer ) ) ;
            

            //close(potoki2[ODCZYT]);
            //close ( potok [ ZAPIS ]) ;
            //close ( potok [ ODCZYT ]) ;
            close ( f_intern) ;
        } 
        else {
            f_intern = open (" intern " , O_WRONLY ) ;
            
            puts(" Proces2 - odczytujacy");
            //close ( potoki2 [ ODCZYT ]) ;
            puts("podaj testk: ");
            gets(buffer);
            puts (" Proces potomny2 wyslal wczytana wiadomosc ") ;
            write ( f_intern, &buffer , sizeof ( &buffer ) ) ;
            close ( f_intern) ;
            
        }

        
    }
    close (f);
    
}