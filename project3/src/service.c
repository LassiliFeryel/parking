#include "service.h" 

int ajouter_service(char *file, Service s) {
    FILE *f = fopen(file, "a"); // Ouvrir le fichier en mode ajout

    if (f != NULL) {
        fprintf(f, "%s %s %d %d %s %d %d %d\n",
                s.nom,
                s.id,
                s.prix,
                s.type,
                s.priorite_service,
                s.disponibilite[0],
                s.disponibilite[1],
                s.disponibilite[2]);  
        fclose(f); // Fermer le fichier après écriture
        return 1; // Retourner 1 si l'ajout est réussi
    } else {
        return 0; // Retourner 0 si l'ouverture du fichier a échoué
    }
}
int modifier_service(char *file, char *id_service, Service nouveau_service) {
    FILE *f = fopen(file, "r");
    FILE *fnew = fopen("temp.txt", "w");
    Service s;
    int val = 0;  // Indicateur de modification

    if (f != NULL && fnew != NULL) {
        // Lire chaque service du fichier
        while (fscanf(f, "%s %s %d %d %s %d %d %d\n",
                      s.nom, s.id, &s.prix, &s.type,
                      s.priorite_service, &s.disponibilite[0],
                      &s.disponibilite[1], &s.disponibilite[2]) != EOF) {

            // Vérifier si l'ID correspond à celui du service à modifier
            if (strcmp(id_service, s.id) == 0) {
                // Remplacer les informations par celles du nouveau service
               /* fprintf(fnew, "%s %s %d %d %s %d %d %d\n",
                        nouveau_service.nom, nouveau_service.id,
                        nouveau_service.prix, nouveau_service.type,
                        nouveau_service.priorite_service,
                        nouveau_service.disponibilite[0],
                        nouveau_service.disponibilite[1],
                        nouveau_service.disponibilite[2]);*/
                s=nouveau_service;
                val = 1;  // Indique que la modification a été effectuée
            } else {
                // Conserver le service inchangé
                fprintf(fnew, "%s %s %d %d %s %d %d %d\n",
                        s.nom, s.id, s.prix, s.type,
                        s.priorite_service, s.disponibilite[0],
                        s.disponibilite[1], s.disponibilite[2]);
            }
        }
    }
    fclose(f);
    fclose(fnew);
    remove(file);
    rename("temp.txt", file);

    return val;
}

int supprimer_service(char *file, char *id) {
    int val = 0; // Variable pour indiquer si un service a été trouvé
    Service s;
    FILE *f = fopen(file, "r");
    FILE *f2 = fopen("temp.txt", "w"); // Fichier temporaire

    // Vérification que les fichiers ont été ouverts avec succès
    if (f != NULL && f2 != NULL) {
        // Lire chaque service dans le fichier
        while (fscanf(f, "%s %s %d %d %s %d %d %d\n",
                s.nom,
                s.id,
                &s.prix,
                &s.type,
                s.priorite_service,
                &s.disponibilite[0], &s.disponibilite[1], &s.disponibilite[2]) != EOF) {

            // Vérifier si l'ID du service correspond à l'ID à supprimer
            if (strcmp(s.id, id) == 0) {
                val = 1; // Service trouvé
            } else {
                // Écrire le service dans le fichier temporaire s'il ne correspond pas à l'ID à supprimer
                fprintf(f2, "%s %s %d %d %s %d %d %d\n",
                    s.nom,
                    s.id,
                    s.prix,
                    s.type,
                    s.priorite_service,
                    s.disponibilite[0], s.disponibilite[1], s.disponibilite[2]);
            }
        }
    }

    fclose(f);
    fclose(f2);
    remove(file);            // Supprimer le fichier original
    rename("temp.txt", file); // Renommer le fichier temporaire

    return val;
}

Service chercher_service(char *file, char *id) {
    FILE *f = fopen(file, "r");
    Service s;

    // Initialiser l'ID du service à une chaîne vide pour indiquer que le service n'a pas été trouvé

    if (f != NULL) {
        // Lire chaque service dans le fichier
        while (fscanf(f, "%s %s %d %d %s %d %d %d\n",
                s.nom,
                s.id,
                &s.prix,
                &s.type,
                s.priorite_service,
                &s.disponibilite[0],
                &s.disponibilite[1],
                &s.disponibilite[2]) != EOF) {

            // Vérifier si l'ID du service correspond à l'ID recherché
            if (strcmp(id, s.id) == 0) {
                fclose(f); // Fermer le fichier avant de retourner
                return s; // Retourner le service trouvé
            }
        }
        fclose(f); // Fermer le fichier si aucune correspondance n'est trouvée
    }
    strcpy(s.id, "");

    // Si aucun service n'est trouvé, l'ID est déjà vide
    return s; // Retourner le service avec l'ID vide
}

// Fonction pour vérifier si l'ID existe déjà dans le fichier
int verifier_id_existant(const char *id) {
    FILE *file = fopen("service.txt", "r");
    if (file == NULL) {
        return 0; // Si le fichier n'existe pas, on considère que l'ID n'est pas utilisé
    }

    Service s;
    while (fscanf(file, "%s %s %s %d %d %d",s.nom, s.id, s.priorite_service, &s.prix, &s.type, &s.disponibilite[0]) != EOF) {
        if (strcmp(s.id, id) == 0) {
            fclose(file);
            return 1; // L'ID existe déjà
        }
    }

    fclose(file);
    return 0; // L'ID n'existe pas
}
// Fonction pour vérifier si l'ID de la réservation existe dans le fichier "reservation.txt"
int verifier_id_reservation(const char *id_reservation) {
    FILE *f = fopen("reservation.txt", "r");
    if (f == NULL) {
        return 0; // Erreur d'ouverture du fichier
    }

    char id[50]; // Pour stocker les IDs des réservations
    while (fscanf(f, "%s\n", id) != EOF) {
        if (strcmp(id, id_reservation) == 0) {
            fclose(f);
            return 1; // Réservation trouvée
        }
    }
    fclose(f);
    return 0; // Réservation non trouvée
}


int affecter_service(char *filename, char *id_reservation, char *id)
{
 FILE *f = fopen(filename, "a");
  // Ouvrir le fichier en mode ajout (append)
if (f != NULL)
 {
  // Écrire les ID de la réservation et du service dans le fichier 
  fprintf(f, "%s %s\n", id_reservation, id);
 fclose(f); // Fermer le fichier après écriture
return 1; // Retourner 1 pour succès
}
  else 
{ 
  printf("Erreur : Impossible d'ouvrir le fichier %s.\n", filename); 
  return 0;
  // Retourner 0 en cas d'échec 
} 
} 





// Fonction pour afficher les services dans un GtkTreeView
void afficher_services(GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;
    GtkTreeIter iter;

    // Récupération du modèle existant
    store = gtk_tree_view_get_model(GTK_TREE_VIEW(liste));

    // Attacher le modèle au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store); // Libération du modèle après l'attachement

    if (store == NULL) {
        // Configuration des colonnes du TreeView
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom Service", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID Service", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Prix", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Priorité", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Disponibilité", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }

    // Création d'un nouveau modèle pour 6 colonnes
    store = gtk_list_store_new(6,
        G_TYPE_STRING, // Nom Service
        G_TYPE_STRING, // ID Service
        G_TYPE_INT,    // Prix
        G_TYPE_STRING, // Type
        G_TYPE_STRING, // Priorité
        G_TYPE_STRING  // Disponibilité
    );

    // Lecture du fichier de services
    FILE *f = fopen("service.txt", "r");
    if (f != NULL) {
        Service service;
        while (fscanf(f, "%s %s %d %d %s %d %d %d", 
                      service.nom, service.id, &service.prix, 
                      &service.type, service.priorite_service, 
                      &service.disponibilite[0], &service.disponibilite[1], &service.disponibilite[2]) != EOF) {

            // Convertir le type de service en texte
            char type_str[20];
            switch (service.type) {
                case 0: strcpy(type_str, "Sécurité"); break;
                case 1: strcpy(type_str, "Nettoyage"); break;
                case 2: strcpy(type_str, "Recharge véhicule"); break;
                default: strcpy(type_str, "Inconnu");
            }

            // Convertir la disponibilité en chaîne de caractères
            char disponibilite_str[100];
            snprintf(disponibilite_str, sizeof(disponibilite_str), "%d %d %d", service.disponibilite[0], service.disponibilite[1], service.disponibilite[2]);


            // Ajouter les données au modèle
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                0, service.nom,
                1, service.id,
                2, service.prix,
                3, type_str,
                4, service.priorite_service,
                5, disponibilite_str,
                -1);
        }
        fclose(f);
    } else {
        printf("Erreur de lecture du fichier.\n");
    }

    // Attacher le modèle au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store); // Libération du modèle après l'attachement
}



















