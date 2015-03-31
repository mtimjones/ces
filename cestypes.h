// cestypes.h

#define NLINES      22
#define NCOLS       68

#define TIME_DELTA  100000

typedef struct
{
   int key_active;
   char key;
   int mouse_active;
   int x;
   int y;
} UserInput;


typedef struct
{
   int x;
   int y;
} ComponentLocation;

typedef struct
{
   char type;
   
} ComponentAppearance;

typedef struct
{
   int hp;
} ComponentHealth;

typedef enum
{
   COMPONENT_NONE       = 0,
   COMPONENT_PLAYER     = 1 << 0,
   COMPONENT_ENEMY      = 1 << 1,
   COMPONENT_LOCATION   = 1 << 2,
   COMPONENT_APPEARANCE = 1 << 3,
   COMPONENT_HEALTH     = 1 << 4,
   COMPONENT_SCRIPT     = 1 << 5,
   COMPONENT_BOMB       = 1 << 6,
} Component;

#define MAX_ENTITIES   10

typedef struct
{
   int mask[ MAX_ENTITIES ];

   ComponentLocation   location[ MAX_ENTITIES ];
   ComponentAppearance appearance[ MAX_ENTITIES ];
   ComponentHealth     health[ MAX_ENTITIES ];

} World;

extern World world;

void initEntities( World *world );
void destroyEntity( World *world, unsigned int entity );
