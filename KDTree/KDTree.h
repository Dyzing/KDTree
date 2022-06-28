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

	std::vector<KDNode>& getVect_Noeuds() { return vect_noeuds; };

	void addNode(KDNode& kdn, std::vector<KDNode>& vn);
	void addNode_rec(KDNode& kdn, KDNode & nc, int  disc, std::vector<KDNode>& vn);
	void deleteNode(KDNode& kdn, std::vector<KDNode>& vn, std::vector<KDNode>& vec_childrens_stay);
	void deleteNode_rec(KDNode& kdn, KDNode & nc, int disc, std::vector<KDNode> vec_children, std::vector<KDNode>& vn, std::vector<KDNode>& vec_childrens_stay);
	void putChildrenInVec_rec(KDNode& nc, int  disc, std::vector<KDNode> & vec_children, std::vector<KDNode>& vn, KDNode & new_nc, std::vector<KDNode>& vec_childrens_stay);
	KDNode findNode(Point p);
	KDNode findNode_rec(KDNode kdn, KDNode nc, int  disc);

	void toString();
	void toString_rec(KDNode kdn);
};

