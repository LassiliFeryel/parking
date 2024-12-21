#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "service.h" 

int type ; 
int disponibilite[3] = {0,0,0} ;
int i;
char *ID;
void
on_btnvalider_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{

GtkWidget *id , *nom,  *combo , *spin, *message;
    Service s; int out ;



    // Récupération des widgets
    id = lookup_widget(button, "entryID");
    nom = lookup_widget(button, "entryNOM");
    combo = lookup_widget(button, "combopriorite");
    spin = lookup_widget(button, "spinprix");
    message = lookup_widget(button, "labelmessage");
// Récupération des données saisies
    strcpy(s.id, gtk_entry_get_text(GTK_ENTRY(id)));
    strcpy(s.nom, gtk_entry_get_text(GTK_ENTRY(nom)));

 // Vérification si l'ID existe déjà
    if (verifier_id_existant(s.id)) {
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                        GTK_DIALOG_MODAL,
                                        GTK_MESSAGE_WARNING,
                                        GTK_BUTTONS_OK,
                                        "L'ID existe déjà. Veuillez en choisir un autre.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return; // Arrêter le processus si l'ID existe déjà
    }
// Récupération de la priorité
    const char *priorite = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo))
;
    if (priorite != NULL) {
        strcpy(s.priorite_service, priorite);
    } else {
        strcpy(s.priorite_service, "Non_spécifié");
    }
// Récupération du type
  s.type = type;
// Récupération de disponibilité 
  for (i=0;i<3;i++)
   { 
    s.disponibilite[i] = disponibilite[i];
   }
// Récupération du prix
    s.prix = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin));

// Validation des données
    if (strlen(s.id) == 0 || strlen(s.nom) == 0) {
        gtk_label_set_text(GTK_LABEL(message), "Veuillez remplir tous les champs obligatoires !");
        return;
    }
 
out =  ajouter_service ("service.txt" , s );
if (out == 0) 
 {gtk_label_set_text(GTK_LABEL(message), "service pas ajouté !"); 
 }
else 
 {
  gtk_label_set_text(GTK_LABEL(message), "service bien ajouté !");
 }
}
void
on_radiobtn1sec_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
  {
       type=0;
  }
}

void
on_radiobtn2nett_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) 
 {
       type=1;
 }
}


void
on_radiobtnrecharge_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
  {
       type=2;
   }
}
void
on_checkbtn1mois_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) 
 {
       disponibilite[0] =1 ;  // Mensuel
 }
}
void
on_checkbtn2an_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
 {
         disponibilite[1] =1;
 } // Annuel
}
void
on_checkbtn3pas_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) 
  {
         disponibilite[2] =1;
  } // Pas disponible 

}
 


void
on_btnannuler_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *Ajout;
    GtkWidget *listesServices;
    
    GtkWidget *treeview;
   
    Ajout= lookup_widget(button, "Ajout");
    gtk_widget_destroy(Ajout);
    listesServices= lookup_widget(button, "listesServices");
    listesServices = create_listesServices ();
    gtk_widget_show (listesServices);

       treeview= lookup_widget(listesServices, "treeviewliste");

    //Ajouter le signal row_activated pour supprimer un service
    g_signal_connect(treeview, "row_activated", G_CALLBACK(on_treeviewliste_row_activated), NULL);
    afficher_services(treeview);
}


void
on_btnvalider2_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *id , *nom,  *combo , *spin, *message;
    Service s; int out ;



    // Récupération des widgets
    
    nom = lookup_widget(button, "nouvnom");
    combo = lookup_widget(button, "comboboxentry2");
    spin = lookup_widget(button, "spinnvprix");
    message = lookup_widget(button, "labelerr");
// Récupération des données saisies
    strcpy(s.id, ID);
    strcpy(s.nom, gtk_entry_get_text(GTK_ENTRY(nom)));

// Récupération de la priorité
    const char *priorite = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo))
;
    if (priorite != NULL) {
        strcpy(s.priorite_service, priorite);
    } else {
        strcpy(s.priorite_service, "Non_spécifié");
    }
// Récupération du type
  s.type = type;
// Récupération de disponibilité 
  for (i=0;i<3;i++)
   { 
    s.disponibilite[i] = disponibilite[i];
   }
// Récupération du prix
    s.prix = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin));

// Validation des données
    if (strlen(s.id) == 0 || strlen(s.nom) == 0) {
        gtk_label_set_text(GTK_LABEL(message), "Veuillez remplir tous les champs obligatoires !");
        return;
    }
out = modifier_service ( "service.txt", ID, s );
if (out == 0) 
 {gtk_label_set_text(GTK_LABEL(message), "service pas modifié !"); 
 }
else 
 {
  gtk_label_set_text(GTK_LABEL(message), "service bien modifié !");
 }
}




void
on_radiobtnsecc_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
  {
       type=0;
  }
}


void
on_radiobtnnettt_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) 
 {
       type=1;
 }
}


void
on_radiobtnrech_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{


if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) 
 {
       type=2;
 }
}

void
on_checkmois_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) 
 {
       disponibilite[0] =1 ;  // Mensuel
 }
}


void
on_checkan_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) 
 {
       disponibilite[1] =1 ;  // Mensuel
 }
}


void
on_checkpasdisp_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) 
 {
       disponibilite[2] =1 ;  // Mensuel
 }
}

void
on_btnannuler2_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *modif;
    GtkWidget *listesServices;
    
    GtkWidget *treeview; 
   
    modif= lookup_widget(button,"modif");
    gtk_widget_destroy(modif);
    listesServices= lookup_widget(button,"listesServices");
    listesServices = create_listesServices ();
    gtk_widget_show (listesServices);

    treeview= lookup_widget(listesServices, "treeviewliste");

    // Ajouter le signal row_activated pour supprimer un service 
    g_signal_connect(treeview, "row_activated", G_CALLBACK(on_treeviewliste_row_activated), NULL);
   afficher_services(treeview);
}


void
on_btnajouter_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *Ajout;
    GtkWidget *listesServices;
    
   
    listesServices = lookup_widget(button,"listesServices");
    gtk_widget_destroy( listesServices);
    
   Ajout = create_Ajout ();
    gtk_widget_show (Ajout);
}


void
on_btnsupp_clicked(GtkButton *button, gpointer user_data) {
    GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(GTK_WIDGET(button), "treeviewliste"));
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
    GtkTreeModel *model;
    GtkTreeIter iter;

    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gchar *id;

        // Obtenir l'ID du service sélectionné
        gtk_tree_model_get(model, &iter, 1, &id, -1);

        // Demander confirmation avant suppression
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_QUESTION,
                                                   GTK_BUTTONS_YES_NO,
                                                   "Voulez-vous vraiment supprimer ce service %s ?", id);
        gint response = gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        if (response == GTK_RESPONSE_YES) {
            // Supprimer le service du fichier
            supprimer_service("service.txt", id);

            // Supprimer la ligne du TreeView
            gtk_list_store_remove(GTK_LIST_STORE(model), &iter);

            // Message de succès
            GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                                                               GTK_DIALOG_MODAL,
                                                               GTK_MESSAGE_INFO,
                                                               GTK_BUTTONS_OK,
                                                               "Le service %s a été supprimé avec succès.", id);
            gtk_dialog_run(GTK_DIALOG(success_dialog));
            gtk_widget_destroy(success_dialog);
        }

        g_free(id);
    }
}

void
on_btnmodifer_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
    // Récupérer la fenêtre de la liste des services
    GtkWidget *window_liste = lookup_widget(GTK_WIDGET(button), "listesServices");
    
    // Récupérer la TreeView pour la liste des services
    GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(window_liste, "treeviewliste"));
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
    GtkTreeModel *model;
    GtkTreeIter iter;

    // Vérifier si une ligne est sélectionnée
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gchar *id;
        gtk_tree_model_get(model, &iter, 1, &id, -1);

        // Appeler la fonction de pré-remplissage avec l'ID du service sélectionné
        GtkWidget *modif;
        modif = create_modif();

        // Recherchez les widgets nécessaires dans la fenêtre de modification
        GtkWidget *spin = lookup_widget(modif, "spinnvprix");
        GtkWidget *combo = lookup_widget(modif, "comboboxentry2");
        GtkWidget *nom = lookup_widget(modif, "nouvnom");

        // Simulation de récupération des informations du service à partir d'une source
        Service s;
        s = chercher_service("service.txt", id);

        if (strcmp(s.id, "") != 0) {
            ID = id;

            // Pré-remplir les champs
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin), s.prix);

            // Pré-remplir le champ de texte pour le nom
            gtk_entry_set_text(GTK_ENTRY(nom), s.nom);

            // Pré-remplir le combobox pour la priorité 
            if (strcmp(s.priorite_service,"Basse")==0) {
                gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);  // Sélectionner le premier élément du combobox
            } else if (strcmp(s.priorite_service,"Moyenne")==0){
                gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 1);  // Sélectionner le deuxième élément du combobox
            } else {
                gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 2);  // Sélectionner le troisième élément du combobox
            }

            // Cocher le bon bouton radio
            GtkWidget *radio1 = lookup_widget(modif, "radiobtnsecc");
            GtkWidget *radio2 = lookup_widget(modif, "radiobtnnettt");
            GtkWidget *radio3 = lookup_widget(modif, "radiobtnrech");
            if (s.type == 0) {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio1), TRUE);
            } else if (s.type == 1) {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio2), TRUE);
            } else {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio3), TRUE);
            }

            // Cocher le checkbutton
            GtkWidget *check1 = lookup_widget(modif, "checkmois");
            GtkWidget *check2 = lookup_widget(modif, "checkan");
            GtkWidget *check3 = lookup_widget(modif, "checkpasdisp");
            if (s.disponibilite[0] == 1) {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check1), TRUE);
            } else if (s.disponibilite[1] == 1) {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check2), TRUE);
            } else {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check3), TRUE);
            }

        } else {
            g_warning("service non trouvé pour l'ID : %s", id);
        }

        // Fermer la fenêtre de la liste des services
        gtk_widget_hide(window_liste);

        // Ouvrir la fenêtre de modification
        gtk_widget_show(modif);

    } else {
        // Aucune ligne sélectionnée, afficher une boîte de dialogue
        GtkWidget *dialog = gtk_message_dialog_new(
            GTK_WINDOW(window_liste),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez sélectionner un service avant de continuer."
        );
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}



void
on_treeviewliste_row_activated         (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
/*GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(button, "treeviewliste"));
  GtkTreeSortable *sortable = GTK_TREE_SORTABLE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));

    // Définir le tri décroissant sur la colonne des dates
    gtk_tree_sortable_set_sort_column_id(sortable, 5, GTK_SORT_DESCENDING);*/

}


void on_btnaffecter_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *entry_id_service;  // Champ pour l'ID Service
    GtkWidget *entry_id_reservation; // Champ pour l'ID Réservation
    GtkWidget *erreur;
    int out;
    char *id_service, *id_reservation;

    // Récupérer les widgets (champs de saisie)
    entry_id_service = lookup_widget(button, "entryidservice");
    entry_id_reservation = lookup_widget(button, "entryidres");
    erreur = lookup_widget(button, "erreeurr");


    // Récupérer les valeurs saisies dans les champs
    id_service = gtk_entry_get_text(GTK_ENTRY(entry_id_service));
    id_reservation = gtk_entry_get_text(GTK_ENTRY(entry_id_reservation));

    if (!verifier_id_existant(id_service)) {
        gtk_label_set_text(GTK_LABEL(erreur), "L'ID du service n'existe pas.");
        return;
    }

    // Vérifier si l'ID de la réservation existe
    if (!verifier_id_reservation(id_reservation)) {
        gtk_label_set_text(GTK_LABEL(erreur), "L'ID de réservation n'existe pas.");
        return;
    }

    out = affecter_service("affectation.txt", id_reservation, id_service);
    if (out == 0) {
        gtk_label_set_text(GTK_LABEL(erreur), "Service non affecté !");
    } else {
        gtk_label_set_text(GTK_LABEL(erreur), "Service bien affecté !");
    }

    // Réinitialiser les champs de saisie
    gtk_entry_set_text(GTK_ENTRY(entry_id_service), "");
    gtk_entry_set_text(GTK_ENTRY(entry_id_reservation), "");
}

 
 


void
on_btnannul_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *Affectation;
    GtkWidget *listesServices;
    
    GtkWidget *treeview;
   
    Affectation= lookup_widget(button,"Affectation");
    gtk_widget_destroy(Affectation);
    listesServices= lookup_widget(button,"listesServices");
    listesServices = create_listesServices ();
    gtk_widget_show (listesServices);

    treeview= lookup_widget(listesServices, "treeviewliste");

    // Ajouter le signal row_activated pour supprimer un service 
    g_signal_connect(treeview, "row_activated", G_CALLBACK(on_treeviewliste_row_activated), NULL);
   afficher_services(treeview);
}


void
on_afficheer_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{

GtkWidget *treeview;
treeview=lookup_widget(button, "treeviewliste");
afficher_services(treeview);

}

void on_btnaffect_clicked(GtkButton *button, gpointer user_data)
{
    Service s;

    // Récupérer la fenêtre de la liste des services
    GtkWidget *window_liste = lookup_widget(GTK_WIDGET(button), "listesServices");
    GtkWidget *ID_widget;

    // Récupérer la TreeView pour la liste des services
    GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(window_liste, "treeviewliste"));
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
    GtkTreeModel *model;
    GtkTreeIter iter;

    // Vérifier si une ligne est sélectionnée
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        char *id_service;

        // Récupérer l'ID du service sélectionné
        gtk_tree_model_get(model, &iter, 1, &id_service, -1);

        // Fermer la fenêtre de la liste des services
        gtk_widget_hide(window_liste);

        // Ouvrir la fenêtre d'affectation
        GtkWidget *Affectation = create_Affectation();

        // Assurez-vous que la fenêtre d'affectation est affichée
        gtk_widget_show(Affectation);

        // Récupérer le widget d'entrée pour l'ID du service
        ID_widget = lookup_widget(Affectation, "entryidservice");

        // Pré-remplir le champ d'entrée avec l'ID du service
        if (id_service != NULL) {
            gtk_entry_set_text(GTK_ENTRY(ID_widget), id_service); // Pré-remplir avec l'ID du service
        }

    } else {
        // Aucune ligne sélectionnée, afficher une boîte de dialogue
        GtkWidget *dialog = gtk_message_dialog_new(
            GTK_WINDOW(window_liste),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez sélectionner un service avant de continuer."
        );
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}








