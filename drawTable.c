#include <stdio.h>
#include "drawTable.h"

void initDrawEntity(DrawEntity* drawEntity)
{
	drawEntity->entity = NULL;
	drawEntity->drawFunction = NULL;
	drawEntity->nextDrawEntity = NULL;
	drawEntity->prevDrawEntity = NULL;
}

void initDrawTier(DrawTier* tier)
{
	tier->entityCount = 0;
	tier->firstDrawEntity = NULL;
	tier->nextDrawTier = NULL;
	tier->prevDrawTier = NULL;
}

void initDrawTable(DrawTable* table)
{
	table->firstDrawTier = NULL;
	table->tierCount = 0;
}

void drawTier(DrawTier* tier)
{
	DrawEntity* currentDrawEntity = tier->firstDrawEntity;
	while(currentDrawEntity)
	{
		currentDrawEntity->drawFunction(currentDrawEntity->entity);
		currentDrawEntity = currentDrawEntity->nextDrawEntity;
	}
}

void drawTable(DrawTable* table)
{
	DrawTier* currentDrawTier = table->firstDrawTier;
	while (currentDrawTier)
	{
		drawTier(currentDrawTier);
		currentDrawTier = currentDrawTier->nextDrawTier;
	}
}
