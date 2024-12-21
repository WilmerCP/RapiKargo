#include <gtk/gtk.h>

GtkWidget *window;
GtkWidget *stack;
GtkBuilder *builder;


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

int main(int argc, char *argv[]) {

    gtk_init(&argc,&argv);

    builder = gtk_builder_new_from_file("gui.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder,"window"));
    stack = GTK_WIDGET(gtk_builder_get_object(builder,"stack"));

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

    gtk_main();

    return 0;

}
