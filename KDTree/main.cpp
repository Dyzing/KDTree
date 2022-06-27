// KDTree.cpp : Ce fichier contient la fonction 'main'. L'ex�cution du programme commence et se termine � cet endroit.
//

#include <iostream>
#include "KDTree.h"
#include "KDNode.h"
#include "Point.h"
#include <vector>

int main()
{
    // Cr�ation du tree
    KDTree tree(2);

    // Cr�ation des points
    Point racine("A", { 40, 45 });
    Point pointB("B", { 15, 70 });
    Point pointC("C", { 70, 10 });

    // Creation des KDNode
    KDNode kdRacine(racine);
    KDNode kdB(pointB);
    KDNode kdC(pointC);

    // Ajout des points dans l'arbre
    tree.addNode(kdRacine, tree.getVect_Noeuds());
    tree.addNode(kdB, tree.getVect_Noeuds());
    tree.addNode(kdC, tree.getVect_Noeuds());

    // Affichage de l'arbre
    tree.toString();
}

