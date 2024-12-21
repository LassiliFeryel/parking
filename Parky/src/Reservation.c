#include <stdio.h>
#include "Reservation.h"
int estValideDate(Date date){
   if(date.annee<2024) return 0;
   if(date.mois<=0 || date.mois>12) return 0;
   if(date.jour<=0 || date.jour>31) return 0;
   return 1;
}
int estValide(Reservation r){
   if(!estValideDate(r.date_debut)){
    printf("La date donnee est invalide.\n");
    return 0;
   }
//    if(r.etat<0 || r.etat>1){
//     printf("L'etat donne est invalide.\n");
//     return 0;
//    }
   if(strlen(r.id_reservation)==0){
     printf("L'id de la reservation ne peut etre vide!.\n");
     return 0;
   }
   if(r.Hdebut<0 || r.Hdebut>23 || r.Mdebut<0 || r.Mdebut>59){
    printf("Heure ou Minute invalide.\n");
    return 0;
   }
   if(r.natureD==1){
    if(r.duree<0 || r.duree >15){
        printf("Nombre de jours invalide(15 max)");
        return 0;
    }
   }else{
    if(r.duree<0 || r.duree>23){
        printf("Nombre d'heures invalide(23 max)");
        return 0;
    }
   }
   return 1;
}
int estUnique(char *file,char *id){
   FILE *f = fopen(file, "r");
     // Déclaration de la structure pour la réservation
     Reservation r;
    // Initialisation de l'id_reservation à une chaîne vide
   

    if (f != NULL) {
        // Lire chaque réservation dans le fichier
        while (fscanf(f, "%s %d %d %d %d %d %d %d %d %s %s\n", 
                r.id_reservation, 
                &r.date_debut.jour, &r.date_debut.mois, &r.date_debut.annee, 
                &r.Hdebut, &r.Mdebut, 
                &r.duree, &r.etat, &r.natureD, 
                r.id_utilisateur, r.id_parking) != EOF) {

            // Vérifier si l'ID de la réservation correspond à l'ID recherché
            if (strcmp(id, r.id_reservation) == 0) {
                fclose(f); // Fermer le fichier avant de retourner
                printf("L'id de la reservation doit etre unique.\n");
                return 1; // Retourner la réservation trouvée
            }
        }
        fclose(f); // Fermer le fichier si aucune correspondance n'est trouvée
    }
     
    return 0;
}

int ajouterReservation(char *file,Reservation r){
   FILE *f=fopen(file,"a");
  
  if(f!=NULL){
  if (estUnique(file, r.id_reservation)) {
    printf("L'id de la reservation doit etre unique.\n");
    return 0;
}

if (!estValide(r)) {
    return 0; // Message d'erreur déjà affiché dans estValide.
}

  // Si toutes les conditions sont OK, on peut ajouter la réservation.
   r.etat = 1;
   fprintf(f, "%s %d %d %d %d %d %d %d %d %s %s\n",
        r.id_reservation,
        r.date_debut.jour,
        r.date_debut.mois,
        r.date_debut.annee,
        r.Hdebut,
        r.Mdebut,
        r.duree,
        r.etat,
        r.natureD,
        r.id_utilisateur,
        r.id_parking);
    fclose(f);
    return 1;


    
   } 
  
  return 0;
}

int modifierReservation(char *file, char *id,Reservation Rmod) {
    FILE *f = fopen(file, "r");
    FILE *fnew = fopen("texte.txt", "w");
    Reservation r;
    int val = 0;

    if (f != NULL && fnew != NULL) {
        while (fscanf(f, "%s %d %d %d %d %d %d %d %d %s %s\n", 
                r.id_reservation, 
                &r.date_debut.jour, &r.date_debut.mois, &r.date_debut.annee, 
                &r.Hdebut, &r.Mdebut, 
                &r.duree, &r.etat, &r.natureD, 
                r.id_utilisateur, r.id_parking) != EOF) {

            if (strcmp(id,r.id_reservation) == 0) {
               r=Rmod;
                val = 1; // Indique que la modification a été effectuée
            }

            // Conserver les données inchangées pour l'écriture
            fprintf(fnew, "%s %d %d %d %d %d %d %d %d %s %s\n", 
                r.id_reservation, 
                r.date_debut.jour, r.date_debut.mois, r.date_debut.annee, 
                r.Hdebut, r.Mdebut, 
                r.duree, r.etat, r.natureD, 
                r.id_utilisateur, r.id_parking);
        }
    }

    fclose(f);
    fclose(fnew);
    remove(file);
    rename("texte.txt", file);

    return val;
}
int supprimerReservation(char *file, char *id) {
    int val = 0; // Variable pour indiquer si une réservation a été trouvée
    Reservation r;
    FILE *f = fopen(file, "r");
    FILE *f2 = fopen("texte.txt", "w"); // Fichier temporaire

    // Vérification que les fichiers ont été ouverts avec succès
    if (f != NULL && f2 != NULL) {
        // Lire chaque réservation dans le fichier
        while (fscanf(f, "%s %d %d %d %d %d %d %d %d %s %s\n", 
                r.id_reservation, 
                &r.date_debut.jour, &r.date_debut.mois, &r.date_debut.annee, 
                &r.Hdebut, &r.Mdebut, 
                &r.duree, &r.etat, &r.natureD, 
                r.id_utilisateur, r.id_parking) != EOF) {
            
            // Vérifier si l'ID de la réservation correspond à l'ID à supprimer
            if (strcmp(id, r.id_reservation) == 0) {
                val = 1; // Réservation trouvée
            } else {
                // Écrire la réservation dans le fichier temporaire si elle ne correspond pas
                fprintf(f2, "%s %d %d %d %d %d %d %d %d %s %s\n", 
                    r.id_reservation, 
                    r.date_debut.jour, r.date_debut.mois, r.date_debut.annee, 
                    r.Hdebut, r.Mdebut, 
                    r.duree, r.etat, r.natureD, 
                    r.id_utilisateur, r.id_parking);
            }
        }
    }
    fclose(f);
    fclose(f2);
    remove(file);
    rename("texte.txt", file);

    return val;
}
Reservation rechercherReservation(char *file, char *id) {
    FILE *f = fopen(file, "r");
    Reservation r; // Déclaration de la structure pour la réservation

    // Initialisation de l'id_reservation à une chaîne vide
   

    if (f != NULL) {
        // Lire chaque réservation dans le fichier
        while (fscanf(f, "%s %d %d %d %d %d %d %d %d %s %s\n", 
                r.id_reservation, 
                &r.date_debut.jour, &r.date_debut.mois, &r.date_debut.annee, 
                &r.Hdebut, &r.Mdebut, 
                &r.duree, &r.etat, &r.natureD, 
                r.id_utilisateur, r.id_parking) != EOF) {

            // Vérifier si l'ID de la réservation correspond à l'ID recherché
            if (strcmp(id, r.id_reservation) == 0) {
                fclose(f); // Fermer le fichier avant de retourner
                return r; // Retourner la réservation trouvée
            }
        }
        fclose(f); // Fermer le fichier si aucune correspondance n'est trouvée
    }
     strcpy(r.id_reservation, "");
    // Si aucune réservation n'est trouvée, l'id_reservation est déjà vide
    return r; // Retourner la réservation avec id_reservation vide
}
//Recherche de Parking
Parking chercherParking(char *file, int id) {
    FILE *f = fopen(file, "r");
    Parking p;

    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        Parking empty = {-1, "", "", 0, 0, 0, "", ""};
        return empty;
    }

    while (fscanf(f, "%d %s %s %d %d %d %s %s",
                  &p.id_parking,
                  p.nom_parking,
                  p.region_parking,
                  &p.capacite,
                  &p.nbPlaces,
                  &p.nombre_bloc,
                  p.type_terrain,
                  p.date_ajout) != EOF) {
        if (p.id_parking == id) {
            fclose(f);
            return p;
        }
    }

    fclose(f);
    Parking empty = {-1, "", "", 0, 0, 0, "", ""};
    return empty;
}
void modifierParking(char *file, Parking p) {
    FILE *f = fopen(file, "r");
    FILE *temp = fopen("temp.txt", "w");
    Parking temp_p;

    if (f == NULL || temp == NULL) {
        perror("Erreur lors de l'ouverture des fichiers");
        if (f != NULL) fclose(f);
        if (temp != NULL) fclose(temp);
        return;
    }

    while (fscanf(f, "%d %s %s %d %d %d %s %s",
                  &temp_p.id_parking,
                  temp_p.nom_parking,
                  temp_p.region_parking,
                  &temp_p.capacite,
                  &temp_p.nbPlaces,
                  &temp_p.nombre_bloc,
                  temp_p.type_terrain,
                  temp_p.date_ajout) != EOF) {
        if (temp_p.id_parking != p.id_parking) {
            fprintf(temp, "%d %s %s %d %d %d %s %s\n",
                    temp_p.id_parking,
                    temp_p.nom_parking,
                    temp_p.region_parking,
                    temp_p.capacite,
                    temp_p.nbPlaces,
                    temp_p.nombre_bloc,
                    temp_p.type_terrain,
                    temp_p.date_ajout);
        } else {
            fprintf(temp, "%d %s %s %d %d %d %s %s\n",
                    p.id_parking,
                    p.nom_parking,
                    p.region_parking,
                    p.capacite,
                    p.nbPlaces,
                    p.nombre_bloc,
                    p.type_terrain,
                    p.date_ajout);
        }
    }

    fclose(f);
    fclose(temp);

    // Remplacement du fichier d'origine par le fichier temporaire
    remove(file);
    rename("temp.txt", file);
}





int annulerReservation(char *file,char *id){
     FILE *f = fopen(file, "r");
     FILE *fnew = fopen("texte.txt", "w");
     Reservation r;
     int val = 0;

    if (f != NULL && fnew != NULL) {
        while (fscanf(f,
        "%s %d %d %d %d %d %d %d %d %s %s\n", 
                r.id_reservation, 
                &r.date_debut.jour, &r.date_debut.mois, &r.date_debut.annee, 
                &r.Hdebut, &r.Mdebut, 
                &r.duree, &r.etat, &r.natureD, 
                r.id_utilisateur, r.id_parking) != EOF) {

            if (strcmp(id, r.id_reservation) == 0) {
                r.etat=0;
                val = 1; // Indique que la modification a été effectuée
            }

            // Conserver les données inchangées pour l'écriture
            fprintf(fnew, "%s %d %d %d %d %d %d %d %d %s %s\n", 
                r.id_reservation, 
                r.date_debut.jour, r.date_debut.mois, r.date_debut.annee, 
                r.Hdebut, r.Mdebut, 
                r.duree, r.etat, r.natureD, 
                r.id_utilisateur, r.id_parking);
        }
    }

    fclose(f);
    fclose(fnew);
    remove(file);
    rename("texte.txt", file);

    return val;
}
void afficherListeReservationParUtilisateur(char *file, char *id) {
    FILE *f = fopen(file, "r");
    Reservation r;
    
    if (f != NULL) {
        printf("Liste des reservations pour l'utilisateur %s :\n", id);

        while (fscanf(f, "%s %d %d %d %d %d %d %d %d %s %s\n", 
                r.id_reservation, 
                &r.date_debut.jour, &r.date_debut.mois, &r.date_debut.annee, 
                &r.Hdebut, &r.Mdebut, 
                &r.duree, &r.etat, &r.natureD, 
                r.id_utilisateur, r.id_parking) != EOF) {

            if (strcmp(id,r.id_utilisateur) == 0) {
                printf("Reservation ID: %s, Utilisateur: %s, Parking ID: %s\n",
                    r.id_reservation, r.id_utilisateur, r.id_parking);
            }
        }

        fclose(f);
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}


int compterReservation(char *file,char *idU){
    FILE *f = fopen(file, "r");
    Reservation r;
    int count = 0;

    if (f != NULL) {
        // Lecture des réservations dans un tableau
        while (fscanf(f, "%s %d %d %d %d %d %d %d %d %s %s\n", 
                r.id_reservation, 
                &r.date_debut.jour, &r.date_debut.mois, &r.date_debut.annee, 
                &r.Hdebut, &r.Mdebut, 
                &r.duree, &r.etat, &r.natureD, 
                r.id_utilisateur, r.id_parking) != EOF) {
                    if(!strcmp(idU,r.id_utilisateur))
            count++;
        }
        fclose(f);
        return count;
     }else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}

int comparerDates(Date d1,Date d2){
   if (d1.annee != d2.annee)
        return d1.annee - d2.annee;
    if (d1.mois != d2.mois)
        return d1.mois - d2.mois;
    return d1.jour - d2.jour;
}
void trierReservationParDateDebut(char *file,char *idU){
   Reservation r,*tabR; int i,j,max,n=0,nb;
   nb=compterReservation(file,idU);
   if(nb){
     tabR=(Reservation*)malloc(nb*sizeof(Reservation));
     if(tabR!=NULL){
        FILE *f = fopen(file, "r");
   if (f != NULL) {
        

        while (fscanf(f, "%s %d %d %d %d %d %d %d %d %s %s\n", 
                r.id_reservation, 
                &r.date_debut.jour, &r.date_debut.mois, &r.date_debut.annee, 
                &r.Hdebut, &r.Mdebut, 
                &r.duree, &r.etat, &r.natureD, 
                r.id_utilisateur, r.id_parking) != EOF) {
                if(!strcmp(idU,r.id_utilisateur)) {
                    tabR[n]=r;
                    n++;
                }
                
        }
        for(i=0;i<nb;i++){
            max=i;
            for(j=i+1;j<nb;j++){
                if(comparerDates(tabR[j].date_debut,tabR[max].date_debut)>0) max=j;
            }
            r=tabR[i];
            tabR[i]=tabR[max];
            tabR[max]=r;
        }
        printf("Reservations triees par date de debut:\n");
        for (i = 0; i < nb; i++) {
            printf("%s %d/%d/%d %d:%d Duree: %d Etat: %d NatureD: %d Utilisateur: %s Parking: %s\n", 
                    tabR[i].id_reservation, 
                    tabR[i].date_debut.jour, 
                    tabR[i].date_debut.mois, 
                    tabR[i].date_debut.annee, 
                    tabR[i].Hdebut, 
                    tabR[i].Mdebut, 
                    tabR[i].duree, 
                    tabR[i].etat, 
                    tabR[i].natureD, 
                    tabR[i].id_utilisateur, 
                    tabR[i].id_parking);
        }
        fclose(f); 
      } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
      }

     }else printf("La memoire n'a pas ete allouee .");
   
   }else{
    printf("Cet utilisateur n'a pas de reservation .\n");
   }
   
  free(tabR);
  
}
    
// Fonction pour trier les parkings par nombre de places (décroissant) et filtrer ceux avec nbPlaces > 0 
void trierParkingParNbPlaces(Parking *resultat, int *taille) { 
  int i, j, max; Parking temp; // Filtrer les parkings avec nbPlaces > 0 
  int validCount = 0; 
   for (i = 0; i < *taille; i++) { 
    if (resultat[i].nbPlaces > 0) { 
      resultat[validCount++] = resultat[i];
     } 
   } // Si aucun parking valide, sortir 
   if (validCount == 0) { 
     *taille = 0; 
      return; 
      } 
    // Tri (sélection décroissant sur nbPlaces) 
    for (i = 0; i < validCount - 1; i++) { 
      max = i; for (j = i + 1; j < validCount; j++) { 
      if (resultat[j].nbPlaces > resultat[max].nbPlaces) { 
        max = j; 
       } 
      } 
   temp = resultat[i]; 
   resultat[i] = resultat[max]; 
   resultat[max] = temp; 
  } 
   // Mettre à jour la taille du tableau 
   *taille = validCount; 
} 


void pre_remplir_formulaire(GtkButton  *button,const gchar *id_reservation) {
    // Trouver la fenêtre de modification
    GtkWidget *window_modification = lookup_widget(GTK_WIDGET(button), "Modification");

    // Recherchez les widgets nécessaires dans la fenêtre de modification
    GtkWidget *id_entry = lookup_widget(window_modification, "entryID_Res");
    GtkWidget *jour_spin = lookup_widget(window_modification, "spinJourModRes");
    GtkWidget *mois_spin = lookup_widget(window_modification, "spinMoisModRes");
    GtkWidget *annee_spin = lookup_widget(window_modification, "spinAnneeModRes");
    GtkWidget *heure_spin = lookup_widget(window_modification, "spinHeureModRes");
    GtkWidget *minute_spin = lookup_widget(window_modification, "spinMinuteModRes");
    GtkWidget *duree_spin = lookup_widget(window_modification, "spinDureeModRes");

    // Simulation de récupération des informations de la réservation à partir d'une source
    // Par exemple, vous pouvez rechercher la réservation en utilisant l'ID
    Reservation reservation;
    reservation = rechercherReservation("reservation.txt",id_reservation);  // Vous devez implémenter cette fonction

    if (strcmp(reservation.id_reservation, "") != 0) {
        // Si la réservation est trouvée, pré-remplir les champs
        gtk_entry_set_text(GTK_ENTRY(id_entry), reservation.id_reservation);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(jour_spin), reservation.date_debut.jour);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(mois_spin), reservation.date_debut.mois);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(annee_spin), reservation.date_debut.annee);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(heure_spin), reservation.Hdebut);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(minute_spin), reservation.Mdebut);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(duree_spin), reservation.duree);
        // Cocher le bon bouton radio pour la nature de la durée
        GtkWidget *radioH = lookup_widget(window_modification, "radioHeureModRes");
        GtkWidget *radioJ = lookup_widget(window_modification, "radioJourModRes");
        if (reservation.natureD == 0) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radioH), TRUE);  // Sélectionner "Heure"
        } else {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radioJ), TRUE);  // Sélectionner "Jour"
        }

    } else {
        // Si la réservation n'est pas trouvée, afficher un message d'erreur
        g_warning("Réservation non trouvée pour l'ID : %s", id_reservation);
    }
}
gint compare_dates(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer user_data) {
    gchar *date_str_a, *date_str_b, *time_str_a, *time_str_b;
    int day_a, month_a, year_a, hour_a, minute_a;
    int day_b, month_b, year_b, hour_b, minute_b;

    // Récupérer les chaînes de date et d'heure des deux éléments
    gtk_tree_model_get(model, a, 4, &date_str_a, 5, &time_str_a, -1); // 4: Date, 5: Heure
    gtk_tree_model_get(model, b, 4, &date_str_b, 5, &time_str_b, -1);

    // Convertir les dates en entiers
    sscanf(date_str_a, "%02d/%02d/%04d", &day_a, &month_a, &year_a);
    sscanf(date_str_b, "%02d/%02d/%04d", &day_b, &month_b, &year_b);

    // Convertir les heures et minutes en entiers
    sscanf(time_str_a, "%02d:%02d", &hour_a, &minute_a);
    sscanf(time_str_b, "%02d:%02d", &hour_b, &minute_b);

    // Libérer la mémoire des chaînes
    g_free(date_str_a);
    g_free(date_str_b);
    g_free(time_str_a);
    g_free(time_str_b);

    // Comparer les dates
    if (year_a != year_b) return (year_a > year_b) ? -1 : 1; // Année
    if (month_a != month_b) return (month_a > month_b) ? -1 : 1; // Mois
    if (day_a != day_b) return (day_a > day_b) ? -1 : 1; // Jour

    // Comparer les heures
    if (hour_a != hour_b) return (hour_a > hour_b) ? -1 : 1;

    // Comparer les minutes
    if (minute_a != minute_b) return (minute_a > minute_b) ? -1 : 1;

    // Les deux lignes sont identiques en termes de date et d'heure
    return 0;
}





// Fonction pour afficher les réservations dans un GtkTreeView void

void afficher_reservation(GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;
    GtkTreeIter iter;

    // Variables pour stocker les données
    char id_reservation[15];
    Date date_debut;
    int Hdebut, Mdebut, duree, etat, natureD;
    char id_utilisateur[15], id_parking[15];
    char nom_utilisateur[30], prenom_utilisateur[30], nom_parking[30];
    char date_debut_str[12], heure_debut_str[6];
    FILE *f;

    // Récupération du modèle existant
    store = gtk_tree_view_get_model(GTK_TREE_VIEW(liste));

    // Attacher le modèle au TreeView
   gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
   g_object_unref(store); // Libération du modèle après l'attachement

   // Configurer la fonction de tri pour la colonne des dates
   GtkTreeSortable *sortable = GTK_TREE_SORTABLE(store);
   gtk_tree_sortable_set_sort_func(
      sortable,
      4, // Index de la colonne "Date Début"
      compare_dates,
      NULL, // Pas besoin de données utilisateur supplémentaires
      NULL  // Pas besoin de fonction de destruction
   );



    if (store == NULL) {
        // Configuration des colonnes du TreeView
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID Réservation", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom Utilisateur", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Prénom Utilisateur", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom Parking", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date Début", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Heure Début", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Durée", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("État", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }

    // Création d'un nouveau modèle
    store = gtk_list_store_new(8,
        G_TYPE_STRING, // ID Réservation
        G_TYPE_STRING, // Nom Utilisateur
        G_TYPE_STRING, // Prénom Utilisateur
        G_TYPE_STRING, // Nom Parking
        G_TYPE_STRING, // Date Début
        G_TYPE_STRING, // Heure Début
        G_TYPE_INT,    // Durée
        G_TYPE_STRING  // État
    );

    // Lecture des réservations à partir du fichier
    f = fopen("reservation.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%s %d %d %d %d %d %d %d %d %s %s",
                      id_reservation,
                      &date_debut.jour, &date_debut.mois, &date_debut.annee,
                      &Hdebut, &Mdebut, &duree, &etat, &natureD,
                      id_utilisateur, id_parking) != EOF) {

            // Conversion des données pour affichage
            sprintf(date_debut_str, "%02d/%02d/%04d", date_debut.jour, date_debut.mois, date_debut.annee);
            sprintf(heure_debut_str, "%02d:%02d", Hdebut, Mdebut);

            // Récupération du nom et prénom de l'utilisateur
            strcpy(nom_utilisateur, "Inconnu");
            strcpy(prenom_utilisateur, "Inconnu");
           // FILE *fu = fopen("utilisateur.txt", "r");
            /*if (fu != NULL) {
                char id_tmp[15], nom_tmp[30], prenom_tmp[30];
                while (fscanf(fu, "%s %s %s", id_tmp, nom_tmp, prenom_tmp) != EOF) {
                    if (strcmp(id_utilisateur, id_tmp) == 0) {
                        strcpy(nom_utilisateur, nom_tmp);
                        strcpy(prenom_utilisateur, prenom_tmp);
                        break;
                    }
                }
                fclose(fu);
            }*/

            // Récupération du nom du parking
            strcpy(nom_parking, "Inconnu");
            FILE *fp = fopen("parkings.txt", "r");
            if (fp != NULL) {
                char id_tmp[15], nom_tmp[30];
                while (fscanf(fp, "%s %s", id_tmp, nom_tmp) != EOF) {
                    if (strcmp(id_parking, id_tmp) == 0) {
                        strcpy(nom_parking, nom_tmp);
                        break;
                    }
                }
                fclose(fp);
            }

            // Ajout des données au modèle
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                0, id_reservation,
                1, nom_utilisateur,
                2, prenom_utilisateur,
                3, nom_parking,
                4, date_debut_str,
                5, heure_debut_str,
                6, duree,
                7, etat ? "Validee" : "Annulee", // État en texte
                -1);
        }
        fclose(f);
    }

    // Attacher le modèle au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), 
    GTK_TREE_MODEL(store));
    g_object_unref(store); // Libération du modèle après l'attachement
}

GtkListStore *creerModeleTreeView() {
    // Crée un modèle avec 4 colonnes : ID, Nom, Région, Places disponibles
    GtkListStore *store = gtk_list_store_new(4,
                                             G_TYPE_INT,    // Colonne 0 : ID du parking
                                             G_TYPE_STRING, // Colonne 1 : Nom du parking
                                             G_TYPE_STRING, // Colonne 2 : Région
                                             G_TYPE_INT     // Colonne 3 : Places disponibles
    );
    return store;
}

void configurerTreeView(GtkTreeView *treeview) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    // Colonne 1 : ID
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne 2 : Nom
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne 3 : Région
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Région", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne 4 : Places disponibles
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Places Disponibles", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(treeview, column);
}
void remplirTreeViewAvecDonnees(GtkTreeView *treeview, Parking *parkings, int taille) {
    GtkListStore *store;
    GtkTreeIter iter;

    // Récupérer ou créer un modèle pour le TreeView
    store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    if (store == NULL) {
        configurerTreeView(treeview);
        store = creerModeleTreeView();
        gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));
        g_object_unref(store); // Décrémenter le compteur de référence
    } else {
        gtk_list_store_clear(store); // Nettoyer les données précédentes
    }

    // Insérer les données dans le modèle
    for (int i = 0; i < taille; i++) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, parkings[i].id_parking,
                           1, parkings[i].nom_parking,
                           2, parkings[i].region_parking,
                           3, parkings[i].nbPlaces,
                          -1);
    }
}
Parking *rechercherParkingsParRegion(char *file, char *region, int *taille) {
    FILE *f = fopen(file, "r");
    Parking *resultat = NULL, p;
    int n = 0;

    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        *taille = 0;
        return NULL;
    }

    // Parcourir le fichier et collecter les parkings correspondants
    while (fscanf(f, "%d %s %s %d %d %d %s %s\n",
                  &p.id_parking, p.nom_parking, p.region_parking,
                  &p.capacite, &p.nbPlaces,&p.nombre_bloc, p.type_terrain, p.date_ajout) != EOF) {
        if (strcmp(p.region_parking, region) == 0) {
            resultat = realloc(resultat, (n + 1) * sizeof(Parking));
            resultat[n++] = p;
        }
    }

    fclose(f);
    *taille = n;
    return resultat;
}

void libererListeReservations(Liste list) {
    ReservationNode *temp;
    while (list != NULL) {
        temp = list;
        list = list->next;
        free(temp);
    }
}


// Chargement de la liste filtrée dans le TreeView
void chargerListeFiltreeDansTreeView(GtkWidget *treeview, Liste list) {
    GtkListStore *store;
    GtkTreeIter iter;

    // Créer un modèle ListStore pour le TreeView
    store = gtk_list_store_new(8,
        G_TYPE_STRING, // ID Réservation
        G_TYPE_STRING, // Nom Utilisateur
        G_TYPE_STRING, // Prénom Utilisateur
        G_TYPE_STRING, // Nom Parking
        G_TYPE_STRING, // Date Début
        G_TYPE_STRING, // Heure Début
        G_TYPE_INT,    // Durée
        G_TYPE_STRING  // État
    );

    char date_debut_str[12], heure_debut_str[6];

    // Parcourir la liste des réservations filtrées
    while (list != NULL) {
        char nom_utilisateur[30] = "Inconnu";
        char prenom_utilisateur[30] = "Inconnu";
        char nom_parking[30] = "Inconnu";

        // Récupérer les informations utilisateur
        FILE *fu = fopen("utilisateur.txt", "r");
        if (fu != NULL) {
            char id_tmp[15], nom_tmp[30], prenom_tmp[30];
            while (fscanf(fu, "%s %s %s", id_tmp, nom_tmp, prenom_tmp) != EOF) {
                if (strcmp(list->data.id_utilisateur, id_tmp) == 0) {
                    strcpy(nom_utilisateur, nom_tmp);
                    strcpy(prenom_utilisateur, prenom_tmp);
                    break;
                }
            }
            fclose(fu);
        }

        // Conversion de l'ID de parking (chaîne en entier)
        int id_parking_reservation = atoi(list->data.id_parking);

        // Récupérer les informations parking
        FILE *fp = fopen("parkings.txt", "r");
        if (fp != NULL) {
            Parking p;
            while (fscanf(fp, "%d %s %s %d %d %d %s %s",
                          &p.id_parking, p.nom_parking, p.region_parking,
                          &p.capacite, &p.nbPlaces, &p.nombre_bloc,
                          p.type_terrain, p.date_ajout) != EOF) {
                if (id_parking_reservation == p.id_parking) {
                    strcpy(nom_parking, p.nom_parking);
                    break;
                }
            }
            fclose(fp);
        }

        // Conversion des données pour affichage
        sprintf(date_debut_str, "%02d/%02d/%04d", list->data.date_debut.jour, list->data.date_debut.mois, list->data.date_debut.annee);
        sprintf(heure_debut_str, "%02d:%02d", list->data.Hdebut, list->data.Mdebut);

        // Ajouter la réservation au modèle
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
            0, list->data.id_reservation,
            1, nom_utilisateur,
            2, prenom_utilisateur,
            3, nom_parking,
            4, date_debut_str,
            5, heure_debut_str,
            6, list->data.duree,
            7, list->data.etat ? "Validee" : "Annulee",
            -1
        );

        list = list->next;
    }

    // Libérer la liste des réservations
    libererListeReservations(list);

    // Associer le modèle au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store); // Libérer le store
}


Liste filtreReservationCombine(char *file, int etat, Date dateDebut, char *idU) {
    FILE *f = fopen(file, "r");
    Reservation r;
    Liste head = NULL, temp = NULL, newNode = NULL;

    if (f != NULL) {
        while (fscanf(f, "%s %d %d %d %d %d %d %d %d %s %s\n",
                      r.id_reservation,
                      &r.date_debut.jour, &r.date_debut.mois, &r.date_debut.annee,
                      &r.Hdebut, &r.Mdebut,
                      &r.duree, &r.etat, &r.natureD,
                      r.id_utilisateur, r.id_parking) != EOF) {
            // Filtrer par utilisateur
            if (strcmp(idU, r.id_utilisateur) != 0) {
                continue;
            }

            // Gestion de la condition pour l'état
            int conditionEtat = (etat == -1) ? 0 : (r.etat == etat);

            // Gestion de la condition pour la date
            int conditionDate = (dateDebut.jour == 0 && dateDebut.mois == 0 && dateDebut.annee == 0) ?
                                0 :
                                (r.date_debut.jour == dateDebut.jour &&
                                 r.date_debut.mois == dateDebut.mois &&
                                 r.date_debut.annee == dateDebut.annee);

            // Ajouter la réservation si l'une des conditions est remplie
            if (conditionEtat || conditionDate) {
                newNode = (ReservationNode*)malloc(sizeof(ReservationNode));
                if (newNode == NULL) {
                    printf("Erreur d'allocation mémoire\n");
                    break;
                }
                newNode->data = r;
                newNode->next = NULL;

                if (head == NULL) {
                    head = newNode;
                } else {
                    temp->next = newNode;
                }
                temp = newNode;
            }
        }
        fclose(f);
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }

    return head;
}


