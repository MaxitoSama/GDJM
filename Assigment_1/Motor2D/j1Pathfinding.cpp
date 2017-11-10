#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Map.h"
#include "j1PathFinding.h"

j1PathFinding::j1PathFinding() : j1Module(), path(DEFAULT_PATH_LENGTH), width(0), height(0)
{
	name.create("pathfinding");
}

// Destructor
j1PathFinding::~j1PathFinding()
{
}

// Called before quitting
bool j1PathFinding::CleanUp()
{
	LOG("Freeing pathfinding library");
	path.Clear();
	return true;
}

// To request all tiles involved in the last generated path
const p2DynArray<iPoint>* j1PathFinding::GetPath() const
{
	return &path;
}

void j1PathFinding::ResetPath()
{
	frontier.Clear();
	visited.clear();
	breadcrumbs.clear();
	frontier.Push(iPoint(19, 4), 0);
	visited.add(iPoint(19, 4));
	breadcrumbs.add(iPoint(19, 4));
	memset(cost_so_far, 0, sizeof(uint) * COST_MAP * COST_MAP);
}


// ----------------------------------------------------------------------------------
// Actual A* algorithm: return number of steps in the creation of the path or -1 ----
// ----------------------------------------------------------------------------------
int j1PathFinding::CreatePath(const iPoint& origin, const iPoint& destination)
{
	// TODO 1: if origin or destination are not walkable, return -1
	int ret = 0;

	if (App->map->MovementCost(destination.x, destination.y) == 0)
	{
		ret = -1;
	}

	if (ret != -1)
	{
		iPoint curr;
		int x, y;
		App->input->GetMousePosition(x, y);

		iPoint goal = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
		frontier.Push(origin,0);

		while (frontier.Count() != 0)
		{
			if (curr == goal)
			{
				break;
			}
			if (frontier.Pop(curr))
			{
				iPoint neighbors[4];
				neighbors[0].create(curr.x + 1, curr.y + 0);
				neighbors[1].create(curr.x + 0, curr.y + 1);
				neighbors[2].create(curr.x - 1, curr.y + 0);
				neighbors[3].create(curr.x + 0, curr.y - 1);

				for (uint i = 0; i < 4; ++i)
				{
					//uint Distance = sqrt(pow((goal.x-neighbors[i].x),2)+pow((goal.y- neighbors[i].y),2));
					uint Distance = neighbors[i].DistanceTo(goal);

					if (App->map->MovementCost(neighbors[i].x, neighbors[i].y) >= 0)
					{
						if (breadcrumbs.find(neighbors[i]) == -1 && visited.find(neighbors[i]) == -1)
						{
							cost_so_far[neighbors[i].x][neighbors[i].y] = Distance;
							frontier.Push(neighbors[i], Distance);							//El nou cost es la distancia
							visited.add(curr);
							breadcrumbs.add(curr);
						}
					}
				}
			}
		}
	}

	return ret;
}

