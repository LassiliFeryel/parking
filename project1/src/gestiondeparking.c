#include "gestiondeparking.h"

// Fonction pour ajouter un parking
void ajouterParking(Parking p) {
    FILE *f = fopen(FICHIER_PARKINGS, "a");
    if (f != NULL) {
        fprintf(f, "%d %s %s %d %d %d %s %s %s\n", p.id_parking, p.nom_parking, p.region_parking, p.capacite,p.nbPlaces, p.nombre_bloc, p.type_terrain, p.date_ajout,p.id_agent);
        fclose(f);
    }
}

int modifier_Parking(char *file, int id_parking, Parking parkingMod) {
    FILE *f = fopen(file, "r");
    FILE *fnew = fopen("temp.txt", "w");
    Parking p;
    int val = 0;

    // Vérification de l'ouverture des fichiers
    if (f == NULL) {
        g_print("Erreur : Impossible d'ouvrir le fichier en lecture.\n");
        return 0;
    }
    if (fnew == NULL) {
        g_print("Erreur : Impossible d'ouvrir le fichier temporaire en écriture.\n");
        fclose(f);
        return 0;
    }

    // Lire les parkings depuis le fichier
    while (fscanf(f, "%d %s %s %d %d %d %s %s %s\n",
                  &p.id_parking,
                  p.nom_parking, p.region_parking,
                  &p.capacite, &p.nbPlaces, &p.nombre_bloc,
                  p.type_terrain, p.date_ajout, p.id_agent) != EOF) {

        if (p.id_parking == id_parking) {
            // Si l'ID correspond, on remplace les données du parking par celles de parkingMod
            p = parkingMod;
            val = 1; // Indique que la modification a été effectuée
        }

        // Écrire les données dans le fichier temporaire
        fprintf(fnew, "%d %s %s %d %d %d %s %s %s\n",
                p.id_parking,
                p.nom_parking, p.region_parking,
                p.capacite, p.nbPlaces, p.nombre_bloc,
                p.type_terrain, p.date_ajout, p.id_agent);
    }

    // Vérification si la modification a bien été effectuée
    if (val == 0) {
        g_print("Erreur : Parking avec ID %d non trouvé dans le fichier.\n", id_parking);
    }

    fclose(f);
    fclose(fnew);

    // Si la modification a eu lieu, remplacer l'ancien fichier par le fichier temporaire
    if (val == 1) {
        remove(file);     // Supprimer l'ancien fichier
        rename("temp.txt", file); // Renommer le fichier temporaire avec l'ancien nom
    }

    return val; // Retourne 1 si la modification a été effectuée, 0 sinon
}


// Fonction pour modifier un parking
void modifierParking(Parking p) {
    FILE *f, *temp;
    Parking temp_p;

    // Ouvrir le fichier d'origine en lecture
    f = fopen(FICHIER_PARKINGS, "r");
    // Ouvrir le fichier temporaire en écriture
    temp = fopen("temp.txt", "w");

    // Vérification de l'ouverture des fichiers
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier d'origine");
        return;
    }

    if (temp == NULL) {
        perror("Erreur lors de la création du fichier temporaire");
        fclose(f);
        return;
    }

    // Lire chaque ligne du fichier d'origine
    while (fscanf(f, "%d %s %s %d %d %d %s %s %s\n", 
                  &temp_p.id_parking, 
                  temp_p.nom_parking, 
                  temp_p.region_parking, 
                  &temp_p.capacite, 
                  &temp_p.nbPlaces,
                  &temp_p.nombre_bloc, 
                  temp_p.type_terrain, 
                  temp_p.date_ajout,
                  temp_p.id_agent) != EOF) {
        
        // Afficher les données lues pour le débogage
        printf("Lecture: %d %s %s %d %d %d %s %s %s\n", 
                  temp_p.id_parking, 
                  temp_p.nom_parking, 
                  temp_p.region_parking, 
                  temp_p.capacite, 
                  temp_p.nbPlaces,
                  temp_p.nombre_bloc, 
                  temp_p.type_terrain, 
                  temp_p.date_ajout,
                  temp_p.id_agent);

        // Comparer l'ID du parking à modifier avec l'ID lu
        if (temp_p.id_parking != p.id_parking) {
            // Si ce n'est pas le parking à modifier, écrire les données originales
            fprintf(temp, "%d %s %s %d %d %d %s %s %s\n", 
                    temp_p.id_parking, 
                     temp_p.nom_parking, 
                    temp_p.region_parking, 
                  temp_p.capacite, 
                  temp_p.nbPlaces,
                  temp_p.nombre_bloc, 
                  temp_p.type_terrain, 
                  temp_p.date_ajout,
                  temp_p.id_agent);
        } else {
            // Si c'est le parking à modifier, écrire les nouvelles données
            fprintf(temp, "%d %s %s %d %d %d %s %s %s\n", 
                    temp_p.id_parking, 
                  temp_p.nom_parking, 
                  temp_p.region_parking, 
                  temp_p.capacite, 
                  temp_p.nbPlaces,
                  temp_p.nombre_bloc, 
                  temp_p.type_terrain, 
                  temp_p.date_ajout,
                  temp_p.id_agent);
            printf("Modification: %d %s %s %d %d %d %s %s %s\n", 
                   temp_p.id_parking, 
                  temp_p.nom_parking, 
                  temp_p.region_parking, 
                  temp_p.capacite, 
                  temp_p.nbPlaces,
                  temp_p.nombre_bloc, 
                  temp_p.type_terrain, 
                  temp_p.date_ajout,
                  temp_p.id_agent);
        }
    }

    // Fermer les fichiers
    fclose(f);
    fclose(temp);

    // Supprimer l'ancien fichier et renommer le fichier temporaire
    if (remove(FICHIER_PARKINGS) != 0) {
        perror("Erreur lors de la suppression du fichier d'origine");
    }
    
    if (rename("temp.txt", FICHIER_PARKINGS) != 0) {
        perror("Erreur lors du renommage du fichier temporaire");
    }
}

// Fonction pour afficher les parkings dans une GtkTreeView
void afficherParking(GtkTreeView *liste) {
    Parking p;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;
    GtkTreeIter iter;

    store = NULL;
    FILE *f;

    store = gtk_tree_view_get_model(liste);

    if (store == NULL) {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Région", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Capacité", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nombre de blocs", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }

    store = gtk_list_store_new(7, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);

    f = fopen(FICHIER_PARKINGS, "r");
    if (f != NULL) {
        while (fscanf(f, "%d %s %s %d %d %d %s %s %s\n", &p.id_parking, p.nom_parking, p.region_parking, &p.capacite,&p.nbPlaces, &p.nombre_bloc, p.type_terrain, p.date_ajout,p.id_agent) != EOF) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, 0, p.id_parking, 1, p.nom_parking, 2, p.region_parking, 3, p.capacite, 4, p.nombre_bloc, 5, p.type_terrain, 6, p.date_ajout, -1);
        }
        fclose(f);
    }

    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);
}


// Fonction pour supprimer un parking
void supprimerParking(int id) {
    FILE *f, *temp;
    Parking p;

    f = fopen(FICHIER_PARKINGS, "r");
    temp = fopen("temp.txt", "w");

    if (f == NULL || temp == NULL) {
        return;
    }

    while (fscanf(f, "%d %s %s %d %d %d %s %s %s\n", &p.id_parking, p.nom_parking, p.region_parking, &p.capacite,&p.nbPlaces, &p.nombre_bloc, p.type_terrain, p.date_ajout,p.id_agent) != EOF) {
        if (p.id_parking != id) {
            fprintf(temp, "%d %s %s %d %d %d %s %s %s\n", p.id_parking, p.nom_parking, p.region_parking, p.capacite,p.nbPlaces, p.nombre_bloc, p.type_terrain, p.date_ajout,p.id_agent);
        }
    }

    fclose(f);
    fclose(temp);

    remove(FICHIER_PARKINGS);
    rename("temp.txt", FICHIER_PARKINGS);
}

void afficherparking2(GtkTreeView *liste) {
    Parking p;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;
    GtkTreeIter iter;

    store = NULL;
    FILE *f;

    // Récupérer le modèle actuel du TreeView
    store = GTK_LIST_STORE(gtk_tree_view_get_model(liste));

    // Si aucun modèle n'existe encore, on initialise les colonnes
    if (store == NULL) {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Région", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Capacité", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nombre de blocs", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }

    // Créer un nouveau modèle pour la liste
    store = gtk_list_store_new(7, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);

    // Ouvrir le fichier contenant les parkings
    f = fopen(FICHIER_PARKINGS, "r");
    if (f != NULL) {
        while (fscanf(f, "%d %s %s %d %d %d %s %s %s\n",
                      &p.id_parking,
                      p.nom_parking,
                      p.region_parking,
                      &p.capacite,
                      &p.nbPlaces,
                      &p.nombre_bloc,
                      p.type_terrain,
                      p.date_ajout,
                      p.id_agent) != EOF) {
            // Vérifier si le parking n'a pas d'agent assigné
            if (strcmp(p.id_agent, "null") == 0 || strlen(p.id_agent) == 0) {
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter,
                                   0, p.id_parking,
                                   1, p.nom_parking,
                                   2, p.region_parking,
                                   3, p.capacite,
                                   4, p.nombre_bloc,
                                   5, p.type_terrain,
                                   6, p.date_ajout,
                                   -1);
            }
        }
        fclose(f);
    } else {
        g_print("Erreur : Impossible d'ouvrir le fichier 'parkings.txt'.\n");
    }

    // Appliquer le modèle au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store); // Libérer la mémoire allouée pour le modèle
}

const char *regions[] = {
    "Centre_ville_Tunis",
    "Sidi_Bousaid",
    "El_Manzeh",
    "Lac1",
    "Lac2",
    "Marsa",
    "Carthage",
    "Centre_ville_Manouba",
    "Zone_Indus_Manouba",
    "Centre_Ville_Ben_Arous",
    "Zone_Indus_Ben_Arous",
    "Azur_City",
    "Tunis_City",
    "Manar_City",
    "Tunisia_Mall"
};

int region_index(const char *region_name) {
    for (int i = 0; i < sizeof(regions) / sizeof(regions[0]); i++) {
        if (strcmp(region_name, regions[i]) == 0) {
            return i;
        }
    }
    return -1; // Si non trouvé
}

// Fonction pour chercher un parking par ID
Parking chercherParking(int id) {
    FILE *f = fopen(FICHIER_PARKINGS, "r");
    Parking p;

    if (f != NULL) {
        char line[256]; // Buffer pour stocker chaque ligne
        while (fgets(line, sizeof(line), f) != NULL) {
            // Utiliser sscanf pour analyser la ligne
            if (sscanf(line, "%d %s %s %d %d %d %s %s %s", 
                       &p.id_parking, 
                       p.nom_parking, 
                       p.region_parking, 
                       &p.capacite, 
                       &p.nbPlaces,
                       &p.nombre_bloc, 
                       p.type_terrain, 
                       p.date_ajout,
                       p.id_agent) !=EOF) {
                if (p.id_parking == id) {
                    fclose(f);
                    return p; // Parking trouvé
                }
            }
        }
        fclose(f);
    }

    // Retourner un parking vide en cas d'absence
    Parking empty = {0, "", "", 0, 0,0, "", "",""};
    return empty;
}



// Fonction pour affecter un agent à un parking
/*int affecterParking(int id_parking, char* id_agent) {
    FILE *f = fopen("parkings.txt", "a"); // Fichier contenant les affectations
    if (f != NULL) {
        fprintf(f, "%d %d\n", id_parking, id_agent); // Enregistrer l'affectation
        fclose(f);
    } else {
        perror("Erreur lors de l'ouverture du fichier des affectations");
    }
}*/


