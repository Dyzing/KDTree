#include "KDNode.h"

KDNode::KDNode(Point p)
	:point(p), leftChild(nullptr), rightChild(nullptr)
{
}

KDNode::~KDNode()
{
}

KDNode* KDNode::getLeftChild()
{
	return leftChild;
}

KDNode* KDNode::getRightChild()
{
	return rightChild;
}

void KDNode::setLeftChild(KDNode* const& lc)
{
	if (leftChild != nullptr)
		delete(leftChild);
	leftChild = lc;
}

void KDNode::setRightChild(KDNode* const& rc)
{
	if (rightChild != nullptr)
		delete(rightChild);
	rightChild = rc;
}
