#include <iostream>
#include "KDTree.h"
#include <cmath>

KDTree::KDTree()
	:nb_dimension(1), discriminateur(0), niveau_total(0), niveau_actuel(0)
{
}

KDTree::KDTree(int const& nb_dim)
	: nb_dimension(nb_dim), discriminateur(0), niveau_total(0), niveau_actuel(0)
{
}

void KDTree::addNode(KDNode & kdn, std::vector<KDNode>& vn)
{
	//KDNode kdn(p);
	if (vn.size() == 0)
	{
		kdn.setLeftChild(nullptr);
		kdn.setRightChild(nullptr);
		++niveau_total;
		++niveau_actuel;
	}
	else
	{
		niveau_actuel = 0;
		Point point_courant(nb_dimension);
		KDNode noeud_courrant(point_courant);
		noeud_courrant = vn[0];
		int disc = niveau_actuel % nb_dimension;
		bool b = false;
		addNode_rec(kdn, vn[0], disc, vn, b);
	}
	vect_noeuds.push_back(kdn);

}

void KDTree::addNode_rec(KDNode &kdn, KDNode & nc, int disc, std::vector<KDNode>& vn, bool & b)
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
			int i = 0;
			while (i < vn.size())
			{
				if (vn[i].getPoint().isPointEquals(nc.getLeftChild()->getPoint()))
				{
					addNode_rec(kdn, *nc.getLeftChild(), disc, vn, b);
					//break;
				}
				if (vn[i].getPoint().isPointEquals(nc.getLeftChild()->getPoint())/* && b == false*/)
				{
					addNode_rec(kdn, vn[i], disc, vn, b);
					//b = true;
					break;
				}
				i++;
			}
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
			int i = 0;
			while (i < vn.size())
			{
				if (vn[i].getPoint().isPointEquals(nc.getRightChild()->getPoint()))
				{
					addNode_rec(kdn, *nc.getRightChild(), disc, vn, b);
					//addNode_rec(kdn, vn[i], disc, vn);
					//break;
				}
				if (vn[i].getPoint().isPointEquals(nc.getRightChild()->getPoint()) /*&& b == false*/)
				{
					addNode_rec(kdn, vn[i], disc, vn, b);
					//b = true;
					return;
				}
				i++;
			}
		}
	}
}

void KDTree::deleteNode(KDNode& kdn, std::vector<KDNode>& vn, std::vector<KDNode>& vec_childrens_stay)
{
	for (int i = 0; i < vn.size(); i++)
	{
		if (vn[i].getPoint().isPointEquals(kdn.getPoint()))
		{
			kdn = vn[i];
			break;
		}		
	}

	std::vector<KDNode> vec_descendance;
	if (vect_noeuds.size() == 0)
	{
		return;
	}
	else
	{
		niveau_actuel = 0;
		Point point_courant(nb_dimension);
		KDNode noeud_courrant(point_courant);
		noeud_courrant = vect_noeuds[0];
		int disc = niveau_actuel % nb_dimension;
		deleteNode_rec(kdn, vect_noeuds[0], disc, vec_descendance, vect_noeuds, vec_childrens_stay);
	}
}

void KDTree::deleteNode_rec(KDNode& kdn, KDNode & nc, int disc, std::vector<KDNode> vec_children, std::vector<KDNode>& vn, std::vector<KDNode>& vec_childrens_stay)
{
	Point temp_p(nb_dimension);
	KDNode temp_kdn(temp_p);
	if (kdn.getPoint().isPointEquals(nc.getPoint()))
	{
		if (nc.getLeftChild() != nullptr)
			putChildrenInVec_rec(*nc.getLeftChild(), disc, vec_children, vn, nc, vec_childrens_stay);
		if (nc.getRightChild() != nullptr)
			putChildrenInVec_rec(*nc.getRightChild(), disc, vec_children, vn, nc, vec_childrens_stay);
		if ((nc.getLeftChild() == nullptr) && (nc.getRightChild() == nullptr))
		{
			
			for (int i = 0; i < vn.size(); i++)
			{
				if (vn[i].getPoint().isPointEquals(nc.getPoint()))
				{
					vn.erase(vn.begin() + i);
					break;
					//nc.~KDNode();

				}
				if (vn[i].getLeftChild() != nullptr)
				{
					if (vn[i].getLeftChild()->getPoint().isPointEquals(nc.getPoint()))
					{
						vn[i].setLeftChild(nullptr);
					}
				}
				if (vn[i].getRightChild() != nullptr)
				{
					if (vn[i].getRightChild()->getPoint().isPointEquals(nc.getPoint()))
					{
						vn[i].setRightChild(nullptr);
					}
				}
			}

		}
		
		for(int i = vec_children.size() - 1; i >= 0; --i)
		{
			temp_kdn = vec_childrens_stay[i];
			//addNode_rec(vec_childrens_stay[i], vn[0], disc, vn);
			addNode(vec_childrens_stay[i], vn);
		}
		vec_children.clear();
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
			deleteNode_rec(kdn, *nc.getLeftChild(), disc, vec_children, vn, vec_childrens_stay);
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
			deleteNode_rec(kdn, *nc.getRightChild(), disc, vec_children, vn, vec_childrens_stay);
		}
	}
}

void KDTree::putChildrenInVec_rec(KDNode& nc, int disc, std::vector<KDNode> & vec_children, std::vector<KDNode>& vn, KDNode& new_nc, std::vector<KDNode>& vec_childrens_stay)
{
	{
		if (nc.getLeftChild() != nullptr)
		{
			++niveau_actuel;
			disc = niveau_actuel % nb_dimension;
			putChildrenInVec_rec(*nc.getLeftChild(), disc, vec_children, vn, new_nc, vec_childrens_stay);
			vec_children.push_back(nc);
			nc.setLeftChild(nullptr);
		}
		if (nc.getRightChild() != nullptr)
		{
			++niveau_actuel;
			disc = niveau_actuel % nb_dimension;
			putChildrenInVec_rec(*nc.getRightChild(), disc, vec_children, vn, new_nc, vec_childrens_stay);
			nc.setRightChild(nullptr);
		}

		if (nc.getLeftChild() == nullptr && nc.getRightChild() == nullptr)
		{
			vec_children.push_back(nc);
			vec_childrens_stay.push_back(nc);

			for (int i = 0; i < vn.size(); i++)
			{
				if (vn[i].getPoint().isPointEquals(nc.getPoint()))
				{
					vn.erase(vn.begin() + i);
					break;

				}
				if (vn[i].getLeftChild() != nullptr)
				{
					if (vn[i].getLeftChild()->getPoint().isPointEquals(nc.getPoint()))
					{
						vn[i].setLeftChild(nullptr);
						new_nc = vn[i];
					}
				}
				if (vn[i].getRightChild() != nullptr)
				{
					if (vn[i].getRightChild()->getPoint().isPointEquals(nc.getPoint()))
					{
						vn[i].setRightChild(nullptr);
						new_nc = vn[i];
					}
				}
			}
		}
	}
}

KDNode KDTree::findNode(Point p)
{
	KDNode kdn(p);
	if (vect_noeuds.size() == 0)
	{
		Point p_default("default", { -1000, -1000 }, nb_dimension);
		KDNode default_node(p_default);
		return default_node;
	}
	else
	{
		niveau_actuel = 0;
		Point point_courant(nb_dimension);
		KDNode noeud_courrant(point_courant);
		noeud_courrant = vect_noeuds[0];
		int disc = niveau_actuel % nb_dimension;
		return findNode_rec(kdn, vect_noeuds[0], disc);
	}
}

KDNode KDTree::findNode_rec(KDNode & kdn, KDNode & nc, int disc)
{
	Point temp_p(nb_dimension);
	KDNode temp_kdn(temp_p);

	if (kdn.getPoint().isPointEquals(nc.getPoint()))
	{
		return nc;
	}
	else if (kdn.getPoint().getCoord()[disc] < nc.getPoint().getCoord()[disc])
	{
		if (nc.getLeftChild() == nullptr)
		{
			Point p_default("default", { -1000, -1000 }, nb_dimension);
			KDNode default_node(p_default);
			return default_node;
		}
		else
		{
			++niveau_actuel;
			disc = niveau_actuel % nb_dimension;
			temp_kdn = *nc.getLeftChild();
			return findNode_rec(kdn, temp_kdn, disc);
		}
	}
	else if (kdn.getPoint().getCoord()[disc] > nc.getPoint().getCoord()[disc])
	{
		if (nc.getRightChild() == nullptr)
		{
			Point p_default("default", { -1000, -1000 }, nb_dimension);
			KDNode default_node(p_default);
			return default_node;
		}
		else
		{
			++niveau_actuel;
			disc = niveau_actuel % nb_dimension;
			temp_kdn = *nc.getRightChild();
			return findNode_rec(kdn, temp_kdn, disc);
		}
	}
}

KDNode KDTree::findCloser_rec(KDNode& kdn, std::vector<KDNode>& vn, KDNode& closest_kdn)
{	
	int distance_pow_closest = 0;
	int distance_closest;
	int distance_closest_min = 100000;

	closest_kdn.getPoint().setCoord({ 100000, 100000 });

	for (int j = 0; j < vn.size(); j++)
	{
		if (kdn.getPoint().isPointEquals(vn[j].getPoint()))
		{
			continue;
		}
		else
		{
			distance_pow_closest = 0;
			for (int i = 0; i < nb_dimension; i++)
			{
				distance_pow_closest += pow(vn[j].getPoint().getCoord()[i] - kdn.getPoint().getCoord()[i], 2);
			}

			distance_closest = sqrt(distance_pow_closest);

			if (distance_closest < distance_closest_min)
			{
				distance_closest_min = distance_closest;
				closest_kdn = vn[j];
				closest_kdn.setPoint(vn[j].getPoint());
			}
		}

	}

	return closest_kdn;
	
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
		Point point_courant(nb_dimension);
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
