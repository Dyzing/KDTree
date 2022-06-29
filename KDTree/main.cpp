// KDTree.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "KDTree.h"
#include "KDNode.h"
#include "Point.h"
#include <vector>

int main()
{
    // Création du tree
    int nb_dim = 2;

    std::cout << "\n Enter the number of dimension" << std::endl;
    std::cin >> nb_dim;

    KDTree tree(nb_dim);

    // Création des points
    Point racine("A", { 40, 45 }, nb_dim);
    Point pointB("B", { 15, 70 }, nb_dim);
    Point pointC("C", { 70, 10 }, nb_dim);
    Point pointD("D", { 69, 50 }, nb_dim);
    Point pointF("F", { 85, 90 }, nb_dim);

    // Creation des KDNode
    KDNode kdRacine(racine);
    KDNode kdB(pointB);
    KDNode kdC(pointC);
    KDNode kdD(pointD);
    KDNode kdF(pointF);

    // Ajout des points dans l'arbre
    tree.addNode(kdRacine, tree.getVect_Noeuds());
    tree.addNode(kdB, tree.getVect_Noeuds());
    tree.addNode(kdC, tree.getVect_Noeuds());
    tree.addNode(kdD, tree.getVect_Noeuds());
    tree.addNode(kdF, tree.getVect_Noeuds());

    // Recherche simple de noeud 
    KDNode nouveau_noeud = tree.findNode(pointD);
    nouveau_noeud = tree.findNode(pointC);

    // Supression des points dans l'arbre
    std::vector<KDNode> vec_children_stay;
    //tree.deleteNode(kdC, tree.getVect_Noeuds(), vec_children_stay);

    // Recherche du plus proche voisin de A
    Point temp_p(nb_dim);
    KDNode noeud_ppA(temp_p);
    noeud_ppA = tree.findCloser_rec(kdRacine, tree.getVect_Noeuds(), noeud_ppA);

    // Affichage de l'arbre
    std::cout << "\n Current tree \n" << std::endl;
    tree.toString();


    // ---------------------------------------------------------------------------

    std::string pn, var_coord, name_of_node;
    int choice = -1;
    Point temp_p_stay(nb_dim);
    KDNode temp_kdnode_stay(temp_p_stay);
    do {
        std::cout << "\nSelect operation:\n"
            "(1) Add a node\n"
            "(2) Delete a node\n"
            "(3) Find a node\n"
            "(4) Find closest neighboor of node X\n"
            "(5) Display of tree\n"
            "(0) Quit\n" << std::endl;
        std::cin >> choice;
        switch (choice) {
            case 1: // Add a node
            {
                // Création des points
                std::cout << "\n Enter the name of the point" << std::endl;
                std::cin >> pn;
                std::vector<int> temp_vec_coord;
                for (int i = 0; i < nb_dim; i++)
                {
                    std::cout << "\n Enter the coord one by one" << std::endl;
                    std::cin >> var_coord;
                    temp_vec_coord.push_back(std::stoi(var_coord));
                }
                Point temp_point(pn, temp_vec_coord, nb_dim); 

                // Creation des KDNode
                KDNode temp_kdnode(temp_point);    
                temp_kdnode_stay = temp_kdnode;
                //  Ajout des points dans l'arbre
                tree.addNode(temp_kdnode_stay, tree.getVect_Noeuds());

                std::cout << "\n Node " + pn + "(";
                for (int i = 0; i < nb_dim - 1; i++)
                {
                    int coordX = temp_kdnode_stay.getPoint().getCoord()[i];
                    std::cout << std::to_string(coordX)+ ", ";
                }
                std::cout << std::to_string(temp_kdnode_stay.getPoint().getCoord()[nb_dim - 1]) + ")";
                std::cout << " added \n" << std::endl;
                break;
            }
            case 2: //Delete a node
            {
                // Supression des points dans l'arbre
                std::vector<KDNode> temp_vec_children_stay;
                std::cout << "\n Enter the name of the point to delete : " << std::endl;
                std::cin >> name_of_node;
                for (int i = 0; i < tree.getVect_Noeuds().size(); i++)
                {
                    if (tree.getVect_Noeuds()[i].getPoint().getPointName() == name_of_node)
                    {
                        KDNode temp_kdnode = tree.getVect_Noeuds()[i];
                        tree.deleteNode(temp_kdnode, tree.getVect_Noeuds(), vec_children_stay);
                        break;
                    }
                }
                
                break;
            }
            case 3:
            {//Find a node
                // Recherche simple de noeud 
                std::cout << "\n Enter the name of the point to find : " << std::endl;
                std::cin >> name_of_node;
                for (int i = 0; i < tree.getVect_Noeuds().size(); i++)
                {
                    if (tree.getVect_Noeuds()[i].getPoint().getPointName() == name_of_node)
                    {
                        KDNode temp_kdnode = tree.getVect_Noeuds()[i];
                        Point temp_point = temp_kdnode.getPoint();
                        KDNode temp_nouveau_noeud = tree.findNode(temp_point);

                        // Affichage du point trouvé
                        std::cout << "\n Node " + name_of_node + "(";
                        for (int i = 0; i < nb_dim - 1; i++)
                        {
                            int coordX = temp_nouveau_noeud.getPoint().getCoord()[i];
                            std::cout << std::to_string(coordX) + ", ";
                        }
                        std::cout << std::to_string(temp_nouveau_noeud.getPoint().getCoord()[nb_dim - 1]) + ")" << std::endl;
                        if (temp_nouveau_noeud.getLeftChild() != nullptr)
                            std::cout << "Left child : " + temp_nouveau_noeud.getLeftChild()->getPoint().getPointName();
                        else
                            std::cout << "Left child : no child";
                        if (temp_nouveau_noeud.getRightChild() != nullptr)
                            std::cout << ", Right child : " + temp_nouveau_noeud.getRightChild()->getPoint().getPointName() << std::endl;
                        else
                            std::cout << ", Right child : no child\n";
                        break;
                    }
                }
                break;
            }
            case 4:
            {// Find closest neighboor of node X
                // Recherche du plus proche voisin de noeud X
                std::cout << "\n Enter the name of the point to find : " << std::endl;
                std::cin >> name_of_node;
                Point temp_point(nb_dim);
                KDNode noeud_ppX(temp_point);
                for (int i = 0; i < tree.getVect_Noeuds().size(); i++)
                {
                    if (tree.getVect_Noeuds()[i].getPoint().getPointName() == name_of_node)
                    {
                        KDNode temp_kdnode = tree.getVect_Noeuds()[i];
                        noeud_ppX = tree.findCloser_rec(temp_kdnode, tree.getVect_Noeuds(), noeud_ppX);

                        // Affichage du point trouvé
                        std::cout << "\n Node " + noeud_ppX.getPoint().getPointName() + "(";
                        for (int i = 0; i < nb_dim - 1; i++)
                        {
                            int coordX = noeud_ppX.getPoint().getCoord()[i];
                            std::cout << std::to_string(coordX) + ", ";
                        }
                        std::cout << std::to_string(noeud_ppX.getPoint().getCoord()[nb_dim - 1]) + ")" << std::endl;
                        if (noeud_ppX.getLeftChild() != nullptr)
                            std::cout << "Left child : " + noeud_ppX.getLeftChild()->getPoint().getPointName();
                        else
                            std::cout << "Left child : no child";
                        if (noeud_ppX.getRightChild() != nullptr)
                            std::cout << ", Right child : " + noeud_ppX.getRightChild()->getPoint().getPointName() << std::endl;
                        else
                            std::cout << ", Right child : no child \n";
                        break;
                    }
                }
                break;
            }
            case 5: // Display of tree
            {
                // Affichage de l'arbre
                std::cout << "\n Affichage de l'arbre : \n" << std::endl;
                tree.toString();
                break;
            }
            default:
                break;
        }
    } while (choice != 0);

    std::cout << "\n";
}

