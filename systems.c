
#include <stdio.h>
#include <ncurses.h>
#include "cestypes.h"


#if 0
void SystemAttackFunction( World *world, WINDOW *win, UserInput *input )
{
   int entity;

   if ( input->mouse_active )
   {
      input->mouse_active = 0;

      for ( entity = 0 ; entity < MAX_ENTITIES ; entity++ )
      {
         if ( world->mask[ entity ] & COMPONENT_ENEMY )
         {
            if ( ( world->location[ entity ].x == input->x ) &&
                 ( world->location[ entity ].y == input->y ) )
            {
               if ( --world->health[ entity ].hp == 0 )
               {
                  mvwprintw( win, world->location[entity].y,
                                  world->location[entity].x, " " );

                  world->mask[ entity ] = COMPONENT_NONE;
               }
            }
         }

      }
   }

   return;
}
#endif

void SystemAttackFunction( World *world, WINDOW *win, UserInput *input )
{
   int entity;

   if ( input->mouse_active )
   {
      input->mouse_active = 0;

      (void)createBomb( world, input->x, input->y );
   }

   return;
}

void SystemMovementFunction( World *world, WINDOW *win, UserInput *input )
{
   unsigned int entity;

   if ( input->key_active )
   {
      input->key_active = 0;

      for ( entity = 0 ; entity < MAX_ENTITIES ; entity++ )
      {
         if ( world->mask[ entity ] & COMPONENT_PLAYER )
         {

            mvwprintw( win, world->location[entity].y,
                         world->location[entity].x, " " );

            switch( input->key )
            {
               case 'w':
                  if ( world->location[ entity ].y > 1 ) 
                  {
                     world->location[ entity ].y--;
                  }
                  break;
               case 'a':
                  if ( world->location[ entity ].x > 1 )
                  {
                     world->location[ entity ].x--;
                  }
                  break;
               case 's':
                  if ( world->location[ entity ].y < NLINES-2 ) 
                  {
                     world->location[ entity ].y++;
                  }
                  break;
               case 'd':
                  if ( world->location[ entity ].x < NCOLS-2 )
                  {
                     world->location[ entity ].x++;
                  }
                  break;
               default:
                  break;
            }

            break;

         }
      }
   }

   return;
}

void SystemDisplayFunction( World *world, WINDOW *win )
{
   unsigned int entity;
   unsigned int mask = COMPONENT_APPEARANCE | COMPONENT_LOCATION;

   for ( entity = 0 ; entity < MAX_ENTITIES ; entity++ )
   {
      if ( world->mask[ entity ] & mask )
      {
         if ( world->mask[ entity ] & COMPONENT_PLAYER )
         {
            mvwprintw( win, world->location[ entity ].y,
                            world->location[ entity ].x, "P" );
         }
         else if ( world->mask[ entity ] & COMPONENT_ENEMY )
         {
            mvwprintw( win, world->location[ entity ].y,
                            world->location[ entity ].x, "E" );
         }
         else if ( world->mask[ entity ] & COMPONENT_BOMB )
         {
            int x = world->location[ entity ].x;
            int y = world->location[ entity ].y;

            if ( world->appearance[ entity ].state == 0 )
            {
               mvwprintw( win, y, x, "*" );
            } 
            else if (world->appearance[ entity ].state == 4 )
            {
               mvwprintw( win, y  , x  , " " );
               mvwprintw( win, y-1, x-1, "*" );
               mvwprintw( win, y-1, x  , "*" );
               mvwprintw( win, y-1, x+1, "*" );
               mvwprintw( win, y  , x-1, "*" );
               mvwprintw( win, y  , x+1, "*" );
               mvwprintw( win, y+1, x-1, "*" );
               mvwprintw( win, y+1, x  , "*" );
               mvwprintw( win, y+1, x+1, "*" );
            }
            else if (world->appearance[ entity ].state == 8 )
            {
               mvwprintw( win, y-1, x-1, " " );
               mvwprintw( win, y-1, x  , " " );
               mvwprintw( win, y-1, x+1, " " );
               mvwprintw( win, y  , x-1, " " );
               mvwprintw( win, y  , x+1, " " );
               mvwprintw( win, y+1, x-1, " " );
               mvwprintw( win, y+1, x  , " " );
               mvwprintw( win, y+1, x+1, " " );
               mvwprintw( win, y-2, x-1, "*" );
               mvwprintw( win, y-2, x  , "*" );
               mvwprintw( win, y-2, x+1, "*" );
               mvwprintw( win, y+2, x-1, "*" );
               mvwprintw( win, y+2, x  , "*" );
               mvwprintw( win, y+2, x+1, "*" );
               mvwprintw( win, y-1, x+2, "*" );
               mvwprintw( win, y  , x+2, "*" );
               mvwprintw( win, y+1, x+2, "*" );
               mvwprintw( win, y-1, x-2, "*" );
               mvwprintw( win, y  , x-2, "*" );
               mvwprintw( win, y+1, x-2, "*" );
            }
            else if (world->appearance[ entity ].state == 12 )
            {
               mvwprintw( win, y-2, x-1, " " );
               mvwprintw( win, y-2, x  , " " );
               mvwprintw( win, y-2, x+1, " " );
               mvwprintw( win, y+2, x-1, " " );
               mvwprintw( win, y+2, x  , " " );
               mvwprintw( win, y+2, x+1, " " );
               mvwprintw( win, y-1, x+2, " " );
               mvwprintw( win, y  , x+2, " " );
               mvwprintw( win, y+1, x+2, " " );
               mvwprintw( win, y-1, x-2, " " );
               mvwprintw( win, y  , x-2, " " );
               mvwprintw( win, y+1, x-2, " " );
               mvwprintw( win, y-2, x-2, "*" );
               mvwprintw( win, y-2, x+2, "*" );
               mvwprintw( win, y+2, x-2, "*" );
               mvwprintw( win, y+2, x+2, "*" );
            }
            else if (world->appearance[ entity ].state == 16 )
            {
               mvwprintw( win, y-2, x-2, " " );
               mvwprintw( win, y-2, x+2, " " );
               mvwprintw( win, y+2, x-2, " " );
               mvwprintw( win, y+2, x+2, " " );

               destroyEntity( world, entity );
            }

            world->appearance[ entity ].state++;

         }
      }
   }

   return;
}

