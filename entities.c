// entities.c

#include "cestypes.h"


unsigned int createEntity( World *world )
{
   unsigned int entity;

   for ( entity = 0 ; entity < MAX_ENTITIES ; entity++ )
   {
      if ( world->mask[ entity ] == COMPONENT_NONE )
      {
         return entity;
      }
   }

   return MAX_ENTITIES;
}


void destroyEntity( World *world, unsigned int entity )
{
   world->mask[ entity ] = COMPONENT_NONE;

   return;
}


void initEntities( World *world )
{
   unsigned int entity;

   for ( entity = 0 ; entity < MAX_ENTITIES ; entity++ )
   {
      destroyEntity( world, entity );
   }

   return;
}


unsigned int createPlayer( World *world, int x, int y )
{
   int entity;

   entity = createEntity( world );

   if ( entity < MAX_ENTITIES )
   {
      world->mask[ entity ] = COMPONENT_PLAYER     |
                              COMPONENT_LOCATION   | 
                              COMPONENT_APPEARANCE ;

      world->location[ entity ].x = x;
      world->location[ entity ].y = y;

      world->appearance[ entity ].type = 'P';

   }

   return entity;
}


unsigned int createEnemy( World *world, int x, int y )
{
   int entity;

   entity = createEntity( world );

   if ( entity < MAX_ENTITIES )
   {
      world->mask[ entity ] = COMPONENT_ENEMY      |
                              COMPONENT_LOCATION   | 
                              COMPONENT_APPEARANCE | 
                              COMPONENT_HEALTH     |
                              COMPONENT_SCRIPT ;

      world->location[ entity ].x = x;
      world->location[ entity ].y = y;

      world->appearance[ entity ].type = 'E';

      world->health[ entity ].hp = 3;

   }

   return entity;
}


