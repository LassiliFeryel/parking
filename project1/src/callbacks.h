#include <gtk/gtk.h>


void
on_RBSOUSTERRAIN_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_RBSURFACE_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_RBAERIEN_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_confirmation_fekher_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_ajouter_parking_clicked             (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_annuler_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_Ajouter_PARKY_clicked               (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_modifier_fekher_clicked             (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_afficher_fekher_clicked             (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_supprimer_fekher_clicked            (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_treeview_parking_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_loop_clicked                        (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_RBSOUSTERRAIN_m_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_RBSURFACE_m_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_RBAERIEN_m_toggled                  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_filtrer_PARKY_clicked               (GtkWidget        *objet,
                                        gpointer         user_data);

void
on_CBdate_affichage_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_CBregion_affichage_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_affecter_agent_clicked              (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_annuler_affectation_clicked         (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_return_affect_clicked               (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_affecter_fekher_clicked             (GtkButton       *objet,
                                        gpointer         user_data);

void
on_affectation_agent_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_afficher_affect_agent_clicked       (GtkButton       *button,
                                        gpointer         user_data);
