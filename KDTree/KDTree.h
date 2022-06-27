#pragma once

#include "KDNode.h"
#include <vector>

class KDTree
{
private:
	int nb_dimension;
	int discriminateur;
	int niveau_total;
	int niveau_actuel;
	std::vector<KDNode> vect_noeuds;

public:
	KDTree();
	KDTree(int const& nb_dim);

	void addNode(Point const & p);
	void addNode_rec(KDNode& kdn, KDNode & nc, int  disc);
	void deleteNode(Point p);
	void deleteNode_rec(KDNode& kdn, KDNode nc, int  disc, std::vector<KDNode> vec_children);
	void putChildrenInVec_rec(KDNode& nc, int  disc, std::vector<KDNode> vec_children);
	KDNode findNode(Point p);
	KDNode findNode_rec(KDNode kdn, KDNode nc, int  disc);

	void toString();
	void toString_rec(KDNode kdn);
};

