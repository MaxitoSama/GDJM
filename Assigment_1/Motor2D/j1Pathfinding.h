#ifndef __j1PATHFINDING_H__
#define __j1PATHFINDING_H__

#include "j1Module.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "p2List.h"
#include "p2PQueue.h"

#define DEFAULT_PATH_LENGTH 50
#define INVALID_WALK_CODE 255
#define COST_MAP 100

class j1PathFinding : public j1Module
{
public:

	j1PathFinding();

	// Destructor
	~j1PathFinding();

	// Called before quitting
	bool CleanUp();

	// Main function to request a path from A to B
	int CreatePath(const iPoint& origin, const iPoint& destination);

	// To request all tiles involved in the last generated path
	const p2DynArray<iPoint>* GetPath() const;



private:

	// size of the map
	uint width;
	uint height;
	// all map walkability values [0..255]
	uchar* map;
	// we store the created path here
	p2DynArray<iPoint>	path;
	p2PQueue<iPoint>	frontier;
	p2List<iPoint>		visited;
	p2List<iPoint>		breadcrumbs;
	uint				cost_so_far[COST_MAP][COST_MAP];
};


#endif // __j1PATHFINDING_H__