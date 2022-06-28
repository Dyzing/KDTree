#include "KDNode.h"

KDNode::KDNode(Point p)
	:point(p), leftChild(nullptr), rightChild(nullptr)
{
}

KDNode::~KDNode()
{
	this->point.~Point();
	this->leftChild = nullptr;
	this->rightChild = nullptr;
}

KDNode& KDNode::operator=(KDNode const& k)
{
	this->point = k.getPoint();
	this->leftChild = k.getLeftChild();
	this->rightChild = k.getRightChild();
	return *this;
}

KDNode* KDNode::getLeftChild() const
{
	return leftChild;
}

KDNode* KDNode::getRightChild() const
{
	return rightChild;
}

void KDNode::setLeftChild(KDNode* const& lc)
{
	//if (leftChild != nullptr)
	//	delete(leftChild);
	leftChild = lc;
}

void KDNode::setRightChild(KDNode* const& rc)
{
	//if (rightChild != nullptr)
	//	delete(rightChild);
	rightChild = rc;
}
