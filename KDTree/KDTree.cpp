#include <iostream>
#include "KDTree.h"

KDTree::KDTree()
	:nb_dimension(1), discriminateur(0), niveau_total(0), niveau_actuel(0)
{
}

KDTree::KDTree(int const& nb_dim)
	: nb_dimension(nb_dim), discriminateur(0), niveau_total(0), niveau_actuel(0)
{
}

void KDTree::addNode(Point const& p)
{
	KDNode kdn(p);
	if (vect_noeuds.size() == 0)
	{
		kdn.setLeftChild(nullptr);
		kdn.setRightChild(nullptr);
		++niveau_total;
		++niveau_actuel;
	}
	else
	{
		niveau_actuel = 0;
		Point point_courant;
		KDNode noeud_courrant(point_courant);
		noeud_courrant = vect_noeuds[0];
		int disc = niveau_actuel % nb_dimension;
		addNode_rec(kdn, vect_noeuds[0], disc);
	}
	vect_noeuds.push_back(kdn);

}

void KDTree::addNode_rec(KDNode &kdn, KDNode & nc, int disc)
{
	if (kdn.getPoint().getCoord()[disc] < nc.getPoint().getCoord()[disc])
	{
		if (nc.getLeftChild() == nullptr)
		{
			nc.setLeftChild(&kdn);
			++niveau_actuel;
			++niveau_total;
		}
		else
		{
			++niveau_actuel;
			disc = niveau_actuel % nb_dimension;
			addNode_rec(kdn, *nc.getLeftChild(), disc);
		}
	}
	else if (kdn.getPoint().getCoord()[disc] > nc.getPoint().getCoord()[disc])
	{
		if (nc.getRightChild() == nullptr)
		{
			nc.setRightChild(&kdn);
			++niveau_actuel;
			++niveau_total;
		}
		else
		{
			++niveau_actuel;
			disc = niveau_actuel % nb_dimension;
			addNode_rec(kdn, *nc.getRightChild(), disc);
		}
	}
}

void KDTree::deleteNode(Point p)
{
	KDNode kdn(p);
	std::vector<KDNode> vec_descendance;
	if (vect_noeuds.size() == 0)
	{
		return;
	}
	else
	{
		niveau_actuel = 0;
		Point point_courant;
		KDNode noeud_courrant(point_courant);
		noeud_courrant = vect_noeuds[0];
		int disc = niveau_actuel % nb_dimension;
		deleteNode_rec(kdn, noeud_courrant, disc, vec_descendance);
	}
}

void KDTree::deleteNode_rec(KDNode& kdn, KDNode nc, int disc, std::vector<KDNode> vec_children)
{
	if (kdn.getPoint().isPointEquals(nc.getPoint()))
	{
		if (nc.getLeftChild() != nullptr)
			putChildrenInVec_rec(*nc.getLeftChild(), disc, vec_children);
		if (nc.getRightChild() != nullptr)
			putChildrenInVec_rec(*nc.getRightChild(), disc, vec_children);
		else if((nc.getLeftChild() == nullptr) && (nc.getRightChild() == nullptr))		
			vect_noeuds.pop_back();
		for (KDNode child : vec_children)
		{
			addNode(child.getPoint());
		}
	}
	else if (kdn.getPoint().getCoord()[disc] < nc.getPoint().getCoord()[disc])
	{
		if (nc.getLeftChild() == nullptr)
		{
			return;
		}
		else
		{
			++niveau_actuel;
			disc = niveau_actuel % nb_dimension;
			deleteNode_rec(kdn, *nc.getLeftChild(), disc, vec_children);
		}
	}
	else if (kdn.getPoint().getCoord()[disc] > nc.getPoint().getCoord()[disc])
	{
		if (nc.getRightChild() == nullptr)
		{
			return;
		}
		else
		{
			++niveau_actuel;
			disc = niveau_actuel % nb_dimension;
			deleteNode_rec(kdn, *nc.getRightChild(), disc, vec_children);
		}
	}
}

void KDTree::putChildrenInVec_rec(KDNode& nc, int disc, std::vector<KDNode> vec_children)
{
	if (nc.getLeftChild() == nullptr && nc.getRightChild() == nullptr)
	{
		vec_children.push_back(nc);
		delete(&nc);
	}
	else
	{
		if (nc.getLeftChild() != nullptr)
		{
			++niveau_actuel;
			disc = niveau_actuel % nb_dimension;
			putChildrenInVec_rec(*nc.getLeftChild(), disc, vec_children);
			vec_children.push_back(nc);
			nc.setLeftChild(nullptr);
		}
		if (nc.getRightChild() != nullptr)
		{
			++niveau_actuel;
			disc = niveau_actuel % nb_dimension;
			putChildrenInVec_rec(*nc.getRightChild(), disc, vec_children);
			nc.setRightChild(nullptr);
		}
	}
}

KDNode KDTree::findNode(Point p)
{
	KDNode kdn(p);
	if (vect_noeuds.size() == 0)
	{
		Point p_default("default", { -1000, -1000 });
		KDNode default_node(p_default);
		return default_node;
	}
	else
	{
		niveau_actuel = 0;
		Point point_courant;
		KDNode noeud_courrant(point_courant);
		noeud_courrant = vect_noeuds[0];
		int disc = niveau_actuel % nb_dimension;
		return findNode_rec(kdn, noeud_courrant, disc);
	}
}

KDNode KDTree::findNode_rec(KDNode kdn, KDNode nc, int disc)
{
	if (kdn.getPoint().isPointEquals(nc.getPoint()))
	{
		return nc;
	}
	else if (kdn.getPoint().getCoord()[disc] < nc.getPoint().getCoord()[disc])
	{
		if (nc.getLeftChild() == nullptr)
		{
			Point p_default("default", { -1000, -1000 });
			KDNode default_node(p_default);
			return default_node;
		}
		else
		{
			++niveau_actuel;
			disc = niveau_actuel % nb_dimension;
			findNode_rec(kdn, *nc.getLeftChild(), disc);
		}
	}
	else if (kdn.getPoint().getCoord()[disc] > nc.getPoint().getCoord()[disc])
	{
		if (nc.getRightChild() == nullptr)
		{
			Point p_default("default", { -1000, -1000 });
			KDNode default_node(p_default);
			return default_node;
		}
		else
		{
			++niveau_actuel;
			disc = niveau_actuel % nb_dimension;
			findNode_rec(kdn, *nc.getRightChild(), disc);
		}
	}
}

void KDTree::toString()
{
	if (vect_noeuds.size() == 0)
	{
		std::cout << "No tree to display";
	}
	else
	{
		niveau_actuel = 0;
		Point point_courant;
		KDNode noeud_courrant(point_courant);
		noeud_courrant = vect_noeuds[0];
		int disc = niveau_actuel % nb_dimension;
		toString_rec(noeud_courrant);
	}
}

void KDTree::toString_rec(KDNode kdn)
{	
	Point p = kdn.getPoint();
	std::cout << p.getPointName() + "(" + std::to_string(p.getCoord()[0]) + ", " + std::to_string(p.getCoord()[1]) + ") \n";
	if (kdn.getLeftChild() != nullptr)
	{
		toString_rec(*kdn.getLeftChild());
	}
	if (kdn.getRightChild() != nullptr)
	{
		toString_rec(*kdn.getRightChild());
	}
	else
	{
		return;
	}
}
