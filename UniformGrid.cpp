#include "UniformGrid.h"
#include <cstdlib>
#include <GL/glut.h>

bool UniformGrid::init( const Vec3 &bboxMin, const Vec3 &bboxMax, int nXCells, int nYCells, int nZCells )
{
	if ( nXCells <= 0 || nYCells <= 0 || nZCells <= 0 )
	{
		std::cout << ": invalid cell size: " << std::endl;
		return false;
	}

	if ( bboxMin.x >= bboxMax.x || bboxMin.y >= bboxMax.y || bboxMin.z >= bboxMax.z )
	{
		std::cout << ": bboxMin coordinate(s) are larger than bboxMax coordinates:" << std::endl;
		return false;
	}

	over_box_min = bboxMin;
	over_box_max = bboxMax;

	num_xcells = nXCells;
	num_ycells = nYCells;
	num_zcells = nZCells;

	const Vec3 bboxSize = bboxMax - bboxMin;

	m_deltax = bboxSize.x/(float)num_xcells;
	m_deltay = bboxSize.y/(float)num_ycells;
	m_deltaz = bboxSize.z/(float)num_zcells;

	if (m_cells) delete [] m_cells;

	m_cells = new std::vector<BaseObject *>[ num_xcells * num_ycells * num_zcells ];

	return true;
}

void UniformGrid::addObject( const BaseObject *o )
{
	
	const Vec3 bboxMin = o->getBoundingBoxMin() - over_box_min;
	const Vec3 bboxMax = o->getBoundingBoxMax() - over_box_min;
 
	const int xStart = clampInt( 0,(int)floorf(bboxMin.x/m_deltax), num_xcells-1 );
	const int xEnd = clampInt( 0,(int)floorf(bboxMax.x/m_deltax),  num_xcells-1 );
	const int yStart = clampInt( 0,(int)floorf(bboxMin.y/m_deltay), num_ycells-1 );
	const int yEnd = clampInt( 0,(int)floorf(bboxMax.y/m_deltay), num_ycells-1 );
	const int zStart = clampInt( 0,(int)floorf(bboxMin.z/m_deltaz), num_zcells-1 );
	const int zEnd = clampInt( 0,(int)floorf(bboxMax.z/m_deltaz), num_zcells-1 );

	for (int zi=zStart; zi<=zEnd; zi++)
	{
		for (int yi=yStart; yi<=yEnd; yi++)
		{
			for (int xi=xStart; xi<=xEnd; xi++)
			{
				getCell(xi,yi,zi).push_back( const_cast<BaseObject *>(o) );
			}
		}
	}
}


