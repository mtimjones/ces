// main.c

#include <stdio.h>
#include <curses.h>
#include "cestypes.h"

static WINDOW *mainwin;

int offsety, offsetx;

World world;

void win_startup( void )
{
   initscr( );
   cbreak( );
   noecho( );
   curs_set( 0 );
   nonl( );

   offsety = ( LINES - NLINES ) / 2;
   offsetx = ( COLS - NCOLS ) / 2;

   mainwin = newwin( NLINES, NCOLS, offsety, offsetx );
   nodelay( mainwin, TRUE );
   keypad( mainwin, TRUE );

   mousemask( BUTTON1_CLICKED, NULL );

   return;
}

void win_shutdown( void )
{
   delwin( mainwin );

   endwin( );

   mousemask( 0, NULL );

   return;
}

void win_update( void )
{
   wborder( mainwin, 0, 0, 0, 0, 0, 0, 0, 0 );

   mvwprintw( mainwin, 1, 1, "CES" );

   wrefresh( mainwin );

   return;
}

void getInput( UserInput *input )
{
   int c;
   static MEVENT event;

   c = wgetch( mainwin );

   if ( c == KEY_MOUSE )
   {
      if ( c == KEY_MOUSE )
      {
         if ( getmouse( &event ) == OK )
         {
            if ( event.bstate & BUTTON1_CLICKED )
            {
               input->y = event.y - offsety;
               input->x = event.x - offsetx;
               input->mouse_active = 1;
            }
         }
      }
   }
   else
   {
      input->key = (char)c;
      input->key_active = 1;
   }

}

int main( int argc, char *argv[] )
{
   UserInput input;

   input.key_active = input.mouse_active = 0;

   initEntities( &world );

   win_startup( );

   win_update( );

   // Create Entities

   createPlayer( &world, 34, 10 );

   createEnemy( &world,  6,  4 );
   createEnemy( &world, 60,  4 );
   createEnemy( &world,  6, 17 );
   createEnemy( &world, 60, 17 );

   while ( 1 )
   {
      getInput( &input );

      // Execute systems
      SystemAttackFunction( &world, mainwin, &input );
      SystemMovementFunction( &world, mainwin, &input );
      SystemDisplayFunction( &world, mainwin );

      wrefresh( mainwin );

   }

   win_shutdown( );

   return 0;
}

