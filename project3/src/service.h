#ifndef SERVICE_H_INCLUDED
#define SERVICE_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

typedef struct {
char nom[50];
char id[50] ;
int prix ;
int type; //0 pour sécurité , 1pour nettoyage , 2 pour recharge d'une véhicule
char priorite_service[50] ;
int disponibilite[3];

}
Service;
int ajouter_service ( char* , Service );
int modifier_service ( char*, char *, Service );
int supprimer_service ( char* , char * );
Service chercher_service ( char* , char * );
int verifier_id_existant(const char *id);
int verifier_id_reservation(const char *id_reservation);
int affecter_service ( char *filename ,char *id_reservation, char *id_service);
void afficher_services(GtkWidget *liste);
#endif

