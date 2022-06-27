#pragma once

#include <iostream>
#include <vector>
#include "Point.h"

class KDNode
{
private:
	Point point;
	KDNode* leftChild;
	KDNode* rightChild;

public:
	KDNode(Point p);
	~KDNode();

	Point getPoint() const { return point; };

	KDNode* getLeftChild();
	KDNode* getRightChild();
	void setLeftChild(KDNode* const & lc);
	void setRightChild(KDNode* const & rc);
};

