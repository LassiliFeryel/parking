#ifndef GESTIONDEPARKING_H
#define GESTIONDEPARKING_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
// Structure représentant un parking
typedef struct {
    int id_parking;           // Identifiant unique du parking
    char nom_parking[100];    // Nom du parking
    char region_parking[100]; // Région du parking
    int capacite;             // Capacité du parking
    int nbPlaces; //nombre de places disponibles
    int nombre_bloc;          // Nombre de blocs dans le parking
    char type_terrain[20];    // Type de parking (aérien, souterrain, sur surface)
    char date_ajout[20];      // Date d'ajout du parking
    char id_agent[20];        // Identifiant unique d'un agent 
} Parking;

typedef struct {
int jour;
int mois;
int annee;
}Date;

typedef struct Node Node ;

 struct Node {
    Parking parking;
    struct Node *next;
};
typedef Node* Liste;

// Constantes
#define FICHIER_PARKINGS "parkings.txt"          // Nom du fichier contenant les parkings

// Déclaration des fonctions CRUD
int modifier_Parking(char *file, int id_parking, Parking parkingMod);
void afficherParking(GtkTreeView * liste);
void ajouterParking(Parking);
void supprimerParking(int id);
void modifierParking(Parking);
Parking chercherParking(int id);
void afficherparking2(GtkTreeView *liste) ;
int region_index(const char *region_name);

int affecterParking(int id_parking, char *id_agent);

#endif // GESTIONDEPARKING_H

