/*
 * File: Sierpinski.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski Triangle problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "gtypes.h"
using namespace std;


void drawSierpinskiTriangle(GWindow& gw, GPoint& topPoint,
        int MaxOrder, int startEdgeLength);

int main() {
    const int startEdgeLength = 400;
    const int MaxOrder = 4;

    GWindow gw(600, 500);
    int middleX = gw.getWidth() / 2;
    int middleY = gw.getHeight() / 2;
    // cout << middleY << endl;
    
    GPoint topPoint(middleX,
            middleY - startEdgeLength / sqrt(3));
    // cout << middleY - startEdgeLength / sqrt(3) << endl;
    drawSierpinskiTriangle(gw, topPoint, MaxOrder, 
            startEdgeLength);

	return 0;
}

void drawSierpinskiTriangle(GWindow& gw, GPoint& topPoint,
        int order, int edgeLength)
{
    int triangleHeight = edgeLength * (sqrt(3) / 2);

    if (order == 0) {
        pause(200);
        GPoint leftPoint(topPoint.getX() - edgeLength / 2,
                topPoint.getY() + triangleHeight); 
        GPoint rightPoint(topPoint.getX() + edgeLength / 2,
                topPoint.getY() + triangleHeight); 
        gw.drawLine(leftPoint, topPoint);
        gw.drawLine(topPoint, rightPoint);
        gw.drawLine(rightPoint, leftPoint);
    }
    else if (order != 0) {
        int nextEdgeLength = edgeLength / 2;
        int nextTriangleHeight = nextEdgeLength * (sqrt(3) / 2);

        if (nextEdgeLength > 0) {
            GPoint leftTriangleTopPoint(topPoint.getX() - 
                    nextEdgeLength / 2, topPoint.getY() +
                    nextTriangleHeight);
            GPoint topTriangleTopPoint(topPoint.getX(), 
                    topPoint.getY());
            GPoint rightTriangleTopPoint(topPoint.getX() + 
                    nextEdgeLength / 2, topPoint.getY() + 
                    nextTriangleHeight);

            drawSierpinskiTriangle(gw, leftTriangleTopPoint,
                    order - 1, nextEdgeLength);
            drawSierpinskiTriangle(gw, topTriangleTopPoint,
                    order - 1, nextEdgeLength);
            drawSierpinskiTriangle(gw, rightTriangleTopPoint,
                    order - 1, nextEdgeLength);
        }

    }


}
