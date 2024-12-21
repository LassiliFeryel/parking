#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "Reservation.h"
int temps;
char* ID_soul;
int check[]={0,0};
void
on_btnAnnulerAdd_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
   GtkWidget *Ajouter_Reservation;
    GtkWidget *Liste_de_Reservation;
    
    GtkWidget *treeview;
   
    Ajouter_Reservation= lookup_widget(button, "Ajouter_Reservation");
    gtk_widget_destroy(Ajouter_Reservation);
    Liste_de_Reservation= lookup_widget(button, "Reservations_Listes");
    Liste_de_Reservation = create_Reservations_Listes();
    gtk_widget_show (Liste_de_Reservation);

    treeview= lookup_widget(Liste_de_Reservation, "tvReservation");

    // Ajouter le signal row_activated pour supprimer une réservation 
    g_signal_connect(treeview, "row_activated", G_CALLBACK(on_tvReservation_row_activated), NULL);
    afficher_reservation(treeview);
}



void on_btnAjouterRes_clicked(GtkButton *button, gpointer user_data) {
    // Déclaration des widgets
    GtkWidget *id, *jour, *mois, *annee, *heure, *minute, *duree;
    GtkWidget *labelerr, *treeview;
    Reservation r;
    Parking p;
    int out, id_park = -1;
    GtkTreeModel *model;
    GtkTreeIter iter;
    char parking_id[10];
    GtkWidget *dialog;

    // Récupération des widgets de l'interface
    id = lookup_widget(button, "entryIdRes");
    jour = lookup_widget(button, "spinJourRes");
    mois = lookup_widget(button, "spinMoisRes");
    annee = lookup_widget(button, "spinAnneeRes");
    heure = lookup_widget(button, "spinHeureRes");
    minute = lookup_widget(button, "spinMinuteRes");
    duree = lookup_widget(button, "spinDureeRes");
    labelerr = lookup_widget(button, "labelErreur");
    treeview = lookup_widget(button, "tvParkingA");

    // Vérification de la sélection dans le TreeView
    if (!gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview)) ||
        !gtk_tree_selection_get_selected(GTK_TREE_SELECTION(gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview))), &model, &iter)) {
        // Afficher une boîte de dialogue si aucun parking n'est sélectionné
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                        GTK_DIALOG_MODAL,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK,
                                        "Veuillez sélectionner un parking.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Récupération de l'ID du parking sélectionné
    gtk_tree_model_get(model, &iter, 0, &id_park, -1);  // Supposons que l'ID est dans la première colonne
    if (id_park == -1) {
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                        GTK_DIALOG_MODAL,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK,
                                        "Veuillez sélectionner un parking valide.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Recherche du parking correspondant
    p = chercherParking("parkings.txt", id_park);
    if (p.id_parking == -1) {  // Vérification si le parking est trouvé
        gtk_label_set_text(GTK_LABEL(labelerr), "Parking introuvable.");
        return;
    }

    // Vérification des places disponibles
    if (p.nbPlaces <= 0) {
        gtk_label_set_text(GTK_LABEL(labelerr), "Le parking sélectionné est plein.");
        return;
    }

    // Mise à jour des places disponibles
    p.nbPlaces--;
    modifierParking("parkings.txt", p);

    // Affectation des données à la structure `Reservation`
    strcpy(r.id_reservation, gtk_entry_get_text(GTK_ENTRY(id)));

    // Date de début
    r.date_debut.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
    r.date_debut.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
    r.date_debut.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));

    // Heure et minute
    r.Hdebut = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(heure));
    r.Mdebut = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(minute));

    // Durée
    r.duree = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(duree));

    // Nature de la durée (à remplacer par une valeur définie)
    r.natureD = 1;  // Par exemple, 1 pour "heures"

    // Simulation d'utilisateur et parking (à adapter si nécessaire)
    strcpy(r.id_utilisateur, "nul");  // Exemple d'utilisateur statique
    sprintf(parking_id, "%d", id_park);
    strcpy(r.id_parking, parking_id);

    // Ajout de la réservation
    out = ajouterReservation("reservation.txt", r);

    // Affichage d'un message d'erreur ou de confirmation
    if (out == 0) {
        gtk_label_set_text(GTK_LABEL(labelerr), "Problème d'ajout de la réservation.");
    } else {
        gtk_label_set_text(GTK_LABEL(labelerr), "Réservation ajoutée avec succès !");
    }
}






void
on_btnAnnulerModRes_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *Modification;
    GtkWidget *Liste_de_Reservation;
    
    GtkWidget *treeview;
   
    Modification= lookup_widget(button, "Modification");
    gtk_widget_destroy(Modification);
    Liste_de_Reservation= lookup_widget(button, "Reservations_Listes");
    Liste_de_Reservation = create_Reservations_Listes();
    gtk_widget_show (Liste_de_Reservation);

    treeview= lookup_widget(Liste_de_Reservation, "tvReservation");

    // Ajouter le signal row_activated pour supprimer une réservation 
    g_signal_connect(treeview, "row_activated", G_CALLBACK(on_tvReservation_row_activated), NULL);
    afficher_reservation(treeview);
}

void
on_btnRechercher_clicked(GtkButton *button, gpointer user_data) {
    // Déclaration des widgets
    GtkWidget *id, *jour, *mois, *annee, *heure, *minute, *duree;
    GtkWidget *labelerr, *radioH, *radioJ;
    Reservation r;

    // Récupération des widgets de l'interface
    id = lookup_widget(button, "entryID_Res");
    jour = lookup_widget(button, "spinJourModRes");
    mois = lookup_widget(button, "spinMoisModRes");
    annee = lookup_widget(button, "spinAnneeModRes");
    heure = lookup_widget(button, "spinHeureModRes");
    minute = lookup_widget(button, "spinMinuteModRes");
    duree = lookup_widget(button, "spinDureeModRes");
    radioH = lookup_widget(button, "radioHeureModRes");
    radioJ = lookup_widget(button, "radioJourModRes");
    labelerr = lookup_widget(button, "labelErreurM");

    // Récupération de l'ID de réservation
   // strcpy(ID,gtk_entry_get_text(GTK_ENTRY(id)));
    ID_soul = gtk_entry_get_text(GTK_ENTRY(id));

    // Vérification si l'entrée ID est vide
    if (ID_soul == NULL || strcmp(ID_soul, "") == 0) {
        gtk_label_set_text(GTK_LABEL(labelerr), "Veuillez entrer un identifiant.");
        return;
    }

    // Rechercher la réservation
    r = rechercherReservation("reservation.txt", ID_soul);

    // Vérifier si la réservation existe
    if (strcmp(r.id_reservation, "") != 0) {
        // Mise à jour des champs avec les données de la réservation trouvée
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(jour), r.date_debut.jour);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(mois), r.date_debut.mois);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(annee), r.date_debut.annee);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(heure), r.Hdebut);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(minute), r.Mdebut);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(duree), r.duree);

        // Cocher le bon bouton radio pour la nature de la durée
        if (r.natureD == 0) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radioH), TRUE);
        } else {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radioJ), TRUE);
        }

        // Réinitialiser le label d'erreur
        gtk_label_set_text(GTK_LABEL(labelerr), "");
    } else {
        // Afficher un message d'erreur si la réservation n'existe pas
        gtk_label_set_text(GTK_LABEL(labelerr), "L'identifiant recherché n'existe pas.");
    }
}

void
on_btnModifierRes_clicked(GtkButton *button, gpointer user_data) {
    // Déclaration des widgets
    GtkWidget *id, *jour, *mois, *annee, *heure, *minute, *duree, *labelerr;
    Reservation r;
    int out;
    
    // Récupération des widgets de l'interface
    //id = lookup_widget(button, "entryID_Res");
    jour = lookup_widget(button, "spinJourModRes");
    mois = lookup_widget(button, "spinMoisModRes");
    annee = lookup_widget(button, "spinAnneeModRes");
    heure = lookup_widget(button, "spinHeureModRes");
    minute = lookup_widget(button, "spinMinuteModRes");
    duree = lookup_widget(button, "spinDureeModRes");
    labelerr = lookup_widget(button, "labelErreurM");

    // Vérification de l'ID de réservation
    //ID= gtk_entry_get_text(GTK_ENTRY(id));
    if (ID_soul == NULL || strcmp(ID_soul, "") == 0) {

        gtk_label_set_text(GTK_LABEL(labelerr), "Veuillez entrer un identifiant.");
        return;
    }
    strcpy(r.id_reservation, ID_soul);

    // Affectation des champs de la structure `Reservation`
    r.date_debut.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
    r.date_debut.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));

    // Limitation de l'année entre 2024 et 2100
    gtk_spin_button_set_range(GTK_SPIN_BUTTON(annee), 2024, 2100);
    r.date_debut.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));

    r.Hdebut = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(heure));
    r.Mdebut = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(minute));
    r.duree = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(duree));

    // Nature de la durée (heures ou jours)
    r.natureD = temps;

    // Simulations d'ID utilisateur et parking (à remplacer par les données réelles)
    strcpy(r.id_utilisateur, "Nul");
    strcpy(r.id_parking, "Nul");
    r.etat=1;
    // Appel de la fonction `modifierReservation`
    out = modifierReservation("reservation.txt", ID_soul, r);

    // Gestion des erreurs ou confirmation
    if (out == 0) {
        gtk_label_set_text(GTK_LABEL(labelerr), "Problème de modification de la réservation.");
    } else {
        gtk_label_set_text(GTK_LABEL(labelerr), "Réservation modifiée avec succès !");
    }
}
void
on_radioHeureModRes_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
        temps = 0; // Heure
    }
}
void
on_radioJourModRes_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
        temps = 1; // Jour
    }
}


void
on_btnAjouterFl_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *Ajouter_Reservation;
    GtkWidget *Liste_de_Reservation;
    
   
    Liste_de_Reservation= lookup_widget(button, "Reservations_Listes");
    gtk_widget_destroy(Liste_de_Reservation);
    
    Ajouter_Reservation = create_Ajouter_Reservation ();
    gtk_widget_show (Ajouter_Reservation);
}


void on_btnModifierFl_clicked(GtkButton *button, gpointer user_data) {
    // Récupérer la fenêtre de la liste des réservations
    GtkWidget *window_liste = lookup_widget(GTK_WIDGET(button), "Reservations_Listes");

    // Récupérer la TreeView pour la liste des réservations
    GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(window_liste, "tvReservation"));
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
    GtkTreeModel *model;
    GtkTreeIter iter;

    // Vérifier si une ligne est sélectionnée
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gchar *id_reservation;
        gtk_tree_model_get(model, &iter, 0,&id_reservation, -1);

        // Appeler la fonction de pré-remplissage avec l'ID de la réservation sélectionnée
        GtkWidget *Modification;
        Modification = create_Modification();

        // Recherchez les widgets nécessaires dans la fenêtre de modification
        GtkWidget *jour_spin = lookup_widget(Modification, "spinJourModRes");
        GtkWidget *mois_spin = lookup_widget(Modification, "spinMoisModRes");
        GtkWidget *annee_spin = lookup_widget(Modification, "spinAnneeModRes");
        GtkWidget *heure_spin = lookup_widget(Modification, "spinHeureModRes");
        GtkWidget *minute_spin = lookup_widget(Modification, "spinMinuteModRes");
        GtkWidget *duree_spin = lookup_widget(Modification, "spinDureeModRes");

        // Simulation de récupération des informations de la réservation à partir d'une source
        Reservation reservation;
        reservation = rechercherReservation("reservation.txt", id_reservation);

        if (strcmp(reservation.id_reservation, "") != 0) {
            ID_soul = id_reservation;

            // Pré-remplir les champs
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(jour_spin), reservation.date_debut.jour);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(mois_spin), reservation.date_debut.mois);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(annee_spin), reservation.date_debut.annee);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(heure_spin), reservation.Hdebut);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(minute_spin), reservation.Mdebut);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(duree_spin), reservation.duree);

            // Cocher le bon bouton radio
            GtkWidget *radioH = lookup_widget(Modification, "radioHeureModRes");
            GtkWidget *radioJ = lookup_widget(Modification, "radioJourModRes");
            if (reservation.natureD == 0) {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radioH), TRUE);
            } else {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radioJ), TRUE);
            }
        } else {
            g_warning("Réservation non trouvée pour l'ID : %s", id_reservation);
        }

        // Fermer la fenêtre de la liste des réservations
        gtk_widget_hide(window_liste);

        // Ouvrir la fenêtre de modification
        gtk_widget_show(Modification);
    } else {
        // Aucune ligne sélectionnée, afficher une boîte de dialogue
        GtkWidget *dialog = gtk_message_dialog_new(
            GTK_WINDOW(window_liste),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez sélectionner une réservation avant de continuer."
        );
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}




void
on_btnSupprimerFl_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(GTK_WIDGET(button), "tvReservation"));
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
    GtkTreeModel *model;
    GtkTreeIter iter;

    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gchar *id_reservation;

        // Obtenir l'ID de la réservation sélectionnée
        gtk_tree_model_get(model, &iter, 0, &id_reservation, -1);

        // Demander confirmation avant suppression
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_QUESTION,
                                                   GTK_BUTTONS_YES_NO,
                                                   "Voulez-vous vraiment supprimer la réservation %s ?", id_reservation);
        gint response = gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        if (response == GTK_RESPONSE_YES) {
            // Supprimer la réservation du fichier
            supprimerReservation("reservation.txt",id_reservation);

            // Supprimer la ligne du TreeView
            gtk_list_store_remove(GTK_LIST_STORE(model), &iter);

            // Message de succès
            GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                                                               GTK_DIALOG_MODAL,
                                                               GTK_MESSAGE_INFO,
                                                               GTK_BUTTONS_OK,
                                                               "La réservation %s a été supprimée avec succès.", id_reservation);
            gtk_dialog_run(GTK_DIALOG(success_dialog));
            gtk_widget_destroy(success_dialog);
        }

        g_free(id_reservation);
    } else {
        // Aucune ligne sélectionnée
        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                                                         GTK_DIALOG_MODAL,
                                                         GTK_MESSAGE_WARNING,
                                                         GTK_BUTTONS_OK,
                                                         "Veuillez sélectionner une réservation à supprimer.");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    }

}


void
on_btnAnnulerRes_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
  // Récupérer la fenêtre de la liste des réservations
    GtkWidget *window_liste = lookup_widget(GTK_WIDGET(button), "Reservations_Listes");

    // Récupérer la TreeView pour la liste des réservations
    GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(window_liste, "tvReservation"));
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
    GtkTreeModel *model;
    GtkTreeIter iter;

    // Vérifier si une ligne est sélectionnée
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gchar *id_reservation;
        gtk_tree_model_get(model, &iter, 0, &id_reservation, -1);

        // Confirmer l'annulation avec l'utilisateur
        GtkWidget *dialog = gtk_message_dialog_new(
            GTK_WINDOW(window_liste),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_QUESTION,
            GTK_BUTTONS_YES_NO,
            "Êtes-vous sûr de vouloir annuler la réservation avec l'ID : %s ?", id_reservation
        );
        int response = gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        if (response == GTK_RESPONSE_YES) {
            // Appeler la fonction pour annuler la réservation
            int success = annulerReservation("reservation.txt", id_reservation);

            if (success) {
                // Afficher un message de succès
                GtkWidget *success_dialog = gtk_message_dialog_new(
                    GTK_WINDOW(window_liste),
                    GTK_DIALOG_DESTROY_WITH_PARENT,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_OK,
                    "La réservation a été annulée avec succès."
                );
                gtk_dialog_run(GTK_DIALOG(success_dialog));
                gtk_widget_destroy(success_dialog);

                // Mettre à jour l'affichage du TreeView (recharger les données)
                // Vous devez implémenter la fonction `charger_reservations_treeview`
                afficher_reservation(treeview);
            } else {
                // Afficher un message d'erreur
                GtkWidget *error_dialog = gtk_message_dialog_new(
                    GTK_WINDOW(window_liste),
                    GTK_DIALOG_DESTROY_WITH_PARENT,
                    GTK_MESSAGE_ERROR,
                    GTK_BUTTONS_OK,
                    "Échec de l'annulation de la réservation. Veuillez réessayer."
                );
                gtk_dialog_run(GTK_DIALOG(error_dialog));
                gtk_widget_destroy(error_dialog);
            }
        }
    } else {
        // Aucune ligne sélectionnée, afficher un avertissement
        GtkWidget *warning_dialog = gtk_message_dialog_new(
            GTK_WINDOW(window_liste),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez sélectionner une réservation avant de continuer."
        );
        gtk_dialog_run(GTK_DIALOG(warning_dialog));
        gtk_widget_destroy(warning_dialog);
    }
}


void
on_btnTriRes_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
   GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(button, "tvReservation"));
  GtkTreeSortable *sortable = GTK_TREE_SORTABLE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));

    // Définir le tri décroissant sur la colonne des dates
    gtk_tree_sortable_set_sort_column_id(sortable, 4, GTK_SORT_DESCENDING);
}



void
on_radioHeureRes_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
        temps = 0; // Heure
    }
}


void
on_radioJourRes_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 
   if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
        temps = 1; // Jours
    }

}

void
on_tvReservation_row_activated(GtkTreeView       *treeview,
                                GtkTreePath       *path,
                                GtkTreeViewColumn *column,
                                gpointer           user_data)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    gchar *id_reservation;

    // Récupérer le modèle et l'itérateur pour la ligne activée
    model = gtk_tree_view_get_model(treeview);
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        // Obtenir l'ID de la réservation
        gtk_tree_model_get(model, &iter, 0, &id_reservation, -1);

        // Créer une boîte de dialogue pour confirmer la suppression
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                                        GTK_DIALOG_MODAL,
                                        GTK_MESSAGE_QUESTION,
                                        GTK_BUTTONS_YES_NO,
                                        "Voulez-vous vraiment supprimer la réservation %s ?", id_reservation);

        // Obtenir la réponse de l'utilisateur
        gint response = gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog); // Détruire la boîte de dialogue après usage

        // Traiter la réponse de l'utilisateur
        if (response == GTK_RESPONSE_YES) {
            // Supprimer la réservation du fichier
            supprimerReservation("reservation.txt", id_reservation);

            // Supprimer la ligne du TreeView
            gtk_list_store_remove(GTK_LIST_STORE(model), &iter);

            // Afficher un message de succès
            GtkWidget *success_dialog;
            success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                                                    GTK_DIALOG_MODAL,
                                                    GTK_MESSAGE_INFO,
                                                    GTK_BUTTONS_OK,
                                                    "La réservation %s a été supprimée avec succès.", id_reservation);
            gtk_dialog_run(GTK_DIALOG(success_dialog));
            gtk_widget_destroy(success_dialog);
        }

        // Libérer la mémoire allouée pour l'ID de réservation
        g_free(id_reservation);
    }
}




void
on_tvParkingA_row_activated            (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}
void
on_btnSearchPark_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *entryRegion = lookup_widget(button, "comboRegion");
    GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(GTK_WIDGET(button), "tvParkingA"));
    char region[30];
    strcpy(region,gtk_combo_box_get_active_text(GTK_COMBO_BOX(entryRegion)));
    Parking *parkings = NULL;
    int taille = 0;

    // Rechercher les parkings par région
    parkings = rechercherParkingsParRegion("parkings.txt", region, &taille);

    // Trier les parkings trouvés par nombre de places
    if (taille > 0) {
        Parking *tri_parking = NULL;
        trierParkingParNbPlaces(parkings, &taille);
    }

    // Afficher les données triées dans le TreeView
    remplirTreeViewAvecDonnees(treeview, parkings, taille);

    if (parkings) free(parkings); // Libérer la mémoire
}

void
on_btnGestionReservation_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *Menu_User;
    GtkWidget *Liste_de_Reservation;
    GtkWidget *treeview;
   
    Menu_User= lookup_widget(button, "Menu_User");
    gtk_widget_destroy(Menu_User);
    Liste_de_Reservation= lookup_widget(button, "Reservations_Listes");
    Liste_de_Reservation = create_Reservations_Listes();
    gtk_widget_show (Liste_de_Reservation);

    treeview= lookup_widget(Liste_de_Reservation, "tvReservation");

    // Ajouter le signal row_activated pour supprimer une réservation 
    g_signal_connect(treeview, "row_activated", G_CALLBACK(on_tvReservation_row_activated), NULL);
    afficher_reservation(treeview);
}


void
on_btnGestionAvis_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btnAcceuilFl_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *Menu_User;
    GtkWidget *Reservations_Liste;
    
   
    Reservations_Liste= lookup_widget(button, "Reservations_Liste");
    
    gtk_widget_destroy(Reservations_Liste);
   Menu_User= lookup_widget(button, "Menu_User");
    Menu_User = create_Menu_User();
    gtk_widget_show (Menu_User);
   
}


void
on_btnAfficherFactureM_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
  
}


void
on_checkStatus_toggled                 (GtkToggleButton *toggle_button,
                                        gpointer         user_data)
{
  GtkWidget *comboEtat = lookup_widget(GTK_WIDGET(toggle_button), "comboEtat");

    if (gtk_toggle_button_get_active(toggle_button)) {
        gtk_widget_set_sensitive(comboEtat, TRUE);
    } else {
        gtk_widget_set_sensitive(comboEtat, FALSE);
        gtk_combo_box_set_active(GTK_COMBO_BOX(comboEtat), -1); // Réinitialise
    }
}


void
on_checkDateDebut_toggled              (GtkToggleButton *toggle_button,
                                        gpointer         user_data)
{
   GtkWidget *jour = lookup_widget(GTK_WIDGET(toggle_button), "spinJourFl");
    GtkWidget *mois = lookup_widget(GTK_WIDGET(toggle_button), "spinMoisFl");
    GtkWidget *annee = lookup_widget(GTK_WIDGET(toggle_button), "spinAnneeFl");

    if (gtk_toggle_button_get_active(toggle_button)) {
        gtk_widget_set_sensitive(jour, TRUE);
        gtk_widget_set_sensitive(mois, TRUE);
        gtk_widget_set_sensitive(annee, TRUE);
    } else {
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(jour), 0);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(mois), 0);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(annee), 0);
        gtk_widget_set_sensitive(jour, FALSE);
        gtk_widget_set_sensitive(mois, FALSE);
        gtk_widget_set_sensitive(annee, FALSE);
    }
}


void on_btnFiltreRes_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *treeview;
    GtkWidget *Liste_de_Reservation;
    Liste l = NULL;

    // Widgets des cases à cocher
    GtkWidget *checkDateDebut = lookup_widget(button, "checkDateDebut");
    GtkWidget *checkStatus = lookup_widget(button, "checkStatus");

    // Widgets des SpinButtons et ComboBox
    GtkWidget *jour = lookup_widget(button, "spinJourFl");
    GtkWidget *mois = lookup_widget(button, "spinMoisFl");
    GtkWidget *annee = lookup_widget(button, "spinAnneeFl");
    GtkWidget *comboEtat = lookup_widget(button, "comboEtat");

    // Récupérer les filtres activés
    gboolean filtreDate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkDateDebut));
    gboolean filtreEtat = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkStatus));

    // Récupération des valeurs des filtres
    int etat = -1; // Par défaut : pas de filtre par état
    if (filtreEtat) {
        const char *etat_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboEtat));
        if (etat_text != NULL) {
            if (strcmp(etat_text, "Annulee") == 0) {
                etat = 0;
            } else if (strcmp(etat_text, "Validee") == 0) {
                etat = 1;
            }
        }
    }

    Date dateDebut = {0, 0, 0}; // Par défaut : pas de filtre par date
    if (filtreDate) {
        dateDebut.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
        dateDebut.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
        dateDebut.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));
    }

    // Récupération du TreeView
    Liste_de_Reservation = lookup_widget(button, "Reservations_Listes");
    treeview = lookup_widget(Liste_de_Reservation, "tvReservation");

    // Récupération de l'ID utilisateur courant (exemple, à adapter)
    char *idU = "nul"; // ID par défaut

    // Appliquer le filtre
    l = filtreReservationCombine("reservation.txt", etat, dateDebut, idU);

    // Charger les résultats dans le TreeView
    if (l != NULL) {
        chargerListeFiltreeDansTreeView(treeview, l);
    } else {
        printf("Aucune réservation trouvée pour les filtres appliqués.\n");
    }
}




void
on_btnGestionAgent_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btnGestionCompte_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btnGestionService_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btnParking_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{

}





