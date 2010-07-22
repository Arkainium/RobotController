/*
 * MCPainter.h
 *
 *  Created on: Jun 2, 2010
 *      Author: appleapple
 */

#ifndef MCPAINTER_H_
#define MCPAINTER_H_

#include <GL/gl.h>
#include <GL/glut.h>
#include <Map.h>
#include <MonteCarlo.h>
#include "MonteCarloVisualDebugger.h"

class MCPainter {
public:
	MCPainter();

	void drawGrid(Map * map);
	void drawMarkers(Map * map);
	void drawParticles(MonteCarloVisualDebugger * debugger);
	void drawObservations(MonteCarloVisualDebugger * debugger,
			MonteCarlo * mc);
	void drawPosition(MonteCarlo * mc, Position realPosition);
	void drawGoal(double goalX, double goalY);
};

#endif /* MCPAINTER_H_ */
