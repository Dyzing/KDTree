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
	void setPoint(Point const& p);
	KDNode& operator=(KDNode const& k);

	KDNode* getLeftChild() const;
	KDNode* getRightChild() const;
	void setLeftChild(KDNode* const & lc);
	void setRightChild(KDNode* const & rc);
};

