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
    KDTree tree(nb_dim);

    // Création des points
    Point racine("A", { 40, 45 }, nb_dim);
    Point pointB("B", { 15, 70 }, nb_dim);
    Point pointC("C", { 70, 10 }, nb_dim);
    Point pointD("D", { 69, 50 }, nb_dim);

    // Creation des KDNode
    KDNode kdRacine(racine);
    KDNode kdB(pointB);
    KDNode kdC(pointC);
    KDNode kdD(pointD);

    // Ajout des points dans l'arbre
    tree.addNode(kdRacine, tree.getVect_Noeuds());
    tree.addNode(kdB, tree.getVect_Noeuds());
    tree.addNode(kdC, tree.getVect_Noeuds());
    tree.addNode(kdD, tree.getVect_Noeuds());

    // Recherche simple de noeud 
    KDNode nouveau_noeud = tree.findNode(pointD);
    nouveau_noeud = tree.findNode(pointC);

    //Supression des points dans l'arbre
    std::vector<KDNode> vec_children_stay;
    tree.deleteNode(kdC, tree.getVect_Noeuds(), vec_children_stay);

    // Affichage de l'arbre
    tree.toString();
}

