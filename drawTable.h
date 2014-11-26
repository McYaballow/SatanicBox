#ifndef MIS_DRAWTABLE_H
#define MIS_DRAWTABLE_H

typedef struct DrawEntity DrawEntity;
typedef struct DrawTier DrawTier;

struct DrawEntity
{
	void* entity;
	DrawEntity* prevDrawEntity;
	DrawEntity* nextDrawEntity;
	void (*drawFunction) (void*);
};

typedef struct DrawTier
{
	unsigned int entityCount;
	DrawEntity* firstDrawEntity;
	DrawTier* prevDrawTier;
	DrawTier* nextDrawTier;
} DrawTier;

typedef struct DrawTable
{
	unsigned int tierCount;
	DrawTier* firstDrawTier;
} DrawTable;

void initDrawEntity(DrawEntity* drawEntity);
void initDrawTier(DrawTier* tier);
void initDrawTable(DrawTable* table);
void drawTier(DrawTier* tier);
void drawTable(DrawTable* table);

#endif
