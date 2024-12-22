#include <gtk/gtk.h>
#include "helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dataStructures.h"

GtkWidget *window;
GtkWidget *stack;
GtkBuilder *builder;
GtkWidget *nameField;
GtkWidget *surnameField;
GtkWidget *citiesComboBox1;
GtkTreeModel *citiesModel;
GtkTreeIter iter1;

GtkTreeStore *treeStore;
GtkTreeView *customersView;
GtkTreeViewColumn *c1;
GtkTreeViewColumn *c2;
GtkTreeViewColumn *c3;
GtkTreeViewColumn *c4;
GtkCellRenderer *cr1;
GtkCellRenderer *cr2;
GtkCellRenderer *cr3;
GtkCellRenderer *cr4;



void goToMenu (GtkButton *b){


    gtk_stack_set_visible_child_name(GTK_STACK(stack),"menu_page");


}

void goToRouteMap (GtkButton *b){

    gtk_stack_set_visible_child_name(GTK_STACK(stack), "route_page");


}

void goToNewCustomer (GtkButton *b){

    gtk_stack_set_visible_child_name(GTK_STACK(stack), "new_costumer_page");


}

void goToNewCargo (GtkButton *b){

    gtk_stack_set_visible_child_name(GTK_STACK(stack), "new_cargo_page");


}

void goToListCustomers (GtkButton *b){

    gtk_stack_set_visible_child_name(GTK_STACK(stack), "list_customers_page");

    gtk_tree_store_clear(treeStore);

    customer* head = (customer*) g_object_get_data(G_OBJECT(window),"customer_head");

    if(head != NULL){

        customer* temp = head;
        GtkTreeIter iter;

        while(temp != NULL){

            char id_str[20];  // Buffer to hold the converted string
            snprintf(id_str, sizeof(id_str), "%d", temp->id);

            gtk_tree_store_append(treeStore,&iter,NULL);

            gtk_tree_store_set(treeStore,&iter,0,temp->name,1,temp->surname,2,temp->city,3,id_str,-1);

            temp = temp->next;

        }

    }else{

    g_print("There are no customers registered to show\n");

    }

}

void on_newCustomerButton_clicked (GtkButton *b){

    int id;
    const char* name = gtk_entry_get_text(GTK_ENTRY(nameField));
    const char* surname = gtk_entry_get_text(GTK_ENTRY(surnameField));
    gchar* city = NULL;
    customer* head = (customer*) g_object_get_data(G_OBJECT(window),"customer_head");

    if(strlen(name) > 2 && strlen(surname) > 2){

        // Get the active row from the combo box
        if (gtk_combo_box_get_active_iter(GTK_COMBO_BOX(citiesComboBox1), &iter1)) {
            gtk_tree_model_get(citiesModel, &iter1, 0,&city, -1);
        }

        id = generateId();

        /*
        g_print("Name: %s\n",name);
        g_print("Surname: %s\n",surname);
        g_print("City: %s\n",city);
        g_print("New ID: %d\n",id);*/

        head = newCustomer(head,name,surname,(char*)city,id);
        g_object_set_data(G_OBJECT(window), "customer_head", head);

        g_free(city);

        gtk_entry_set_text(GTK_ENTRY(nameField), "");
        gtk_entry_set_text(GTK_ENTRY(surnameField), "");


    }else{

        g_print("Please enter valid data\n");

    }


}

int main(int argc, char *argv[]) {

    gtk_init(&argc,&argv);

    builder = gtk_builder_new_from_file("gui.glade");

    //Obtain all necessary widgets
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window"));
    stack = GTK_WIDGET(gtk_builder_get_object(builder,"stack"));
    nameField = GTK_WIDGET(gtk_builder_get_object(builder,"name"));
    surnameField = GTK_WIDGET(gtk_builder_get_object(builder,"surname"));
    citiesComboBox1 = GTK_WIDGET(gtk_builder_get_object(builder,"citiesComboBox1"));
    customersView = GTK_TREE_VIEW(gtk_builder_get_object(builder,"treeStoreView"));
    treeStore = GTK_TREE_STORE(gtk_builder_get_object(builder,"treeStore"));

    c1 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"c1"));
    c2 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"c2"));
    c3 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"c3"));
    c4 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"c4"));

    cr1 = GTK_CELL_RENDERER(gtk_builder_get_object(builder,"cr1"));
    cr2 = GTK_CELL_RENDERER(gtk_builder_get_object(builder,"cr2"));
    cr3 = GTK_CELL_RENDERER(gtk_builder_get_object(builder,"cr3"));
    cr4 = GTK_CELL_RENDERER(gtk_builder_get_object(builder,"cr4"));

    gtk_tree_view_column_add_attribute(c1,cr1,"text",0);
    gtk_tree_view_column_add_attribute(c2,cr2,"text",1);
    gtk_tree_view_column_add_attribute(c3,cr3,"text",2);
    gtk_tree_view_column_add_attribute(c4,cr4,"text",3);


    gtk_tree_view_set_model(customersView, GTK_TREE_MODEL(treeStore));

    g_signal_connect(window,"destroy", G_CALLBACK(gtk_main_quit),NULL);

    gtk_builder_connect_signals(builder,NULL); //connects all signals with the callbacks defined in glade file

     // Load the CSS
    GtkCssProvider *provider = gtk_css_provider_new();
    GError *error = NULL;
    gtk_css_provider_load_from_path(provider, "styles.css", &error);

    // Get the default screen
    GdkScreen *screen = gdk_screen_get_default();

    if (error != NULL) {
        g_warning("Error loading CSS file: %s", error->message);
        g_error_free(error);
    }else {

        gtk_style_context_add_provider_for_screen(screen,
                                            GTK_STYLE_PROVIDER(provider),
                                            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    }

    g_object_unref(provider);

    gtk_widget_show_all(window);

    seedRand();
    citiesModel = gtk_combo_box_get_model(GTK_COMBO_BOX(citiesComboBox1));
    customer* head = (customer*) malloc(sizeof(customer));
    head = NULL;
    g_object_set_data(G_OBJECT(window), "customer_head", head);

    gtk_main();

    freeCustomers(head);

    return 0;

}
