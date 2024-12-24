#include <gtk/gtk.h>
#include "helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dataStructures.h"
#include <stdbool.h>

GtkWidget *window;
GtkWidget *stack;
GtkBuilder *builder;
GtkWidget *nameField;
GtkWidget *surnameField;
GtkWidget *citiesComboBox1;
GtkTreeModel *citiesModel;
GtkTreeIter iter1;

GtkWidget *customerIdField;
GtkWidget *descriptionField;
GtkWidget *citiesComboBox2;
GtkTreeIter iter2;
GtkTreeModel *citiesModel2;

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

GtkTreeStore *cargoTreeStore;
GtkTreeView *cargoView1;
GtkTreeViewColumn *c5;
GtkTreeViewColumn *c6;
GtkTreeViewColumn *c7;
GtkTreeViewColumn *c8;
GtkTreeViewColumn *c9;
GtkCellRenderer *cr5;
GtkCellRenderer *cr6;
GtkCellRenderer *cr7;
GtkCellRenderer *cr8;
GtkCellRenderer *cr9;

GtkTreeStore *cargoTreeStore2;
GtkTreeView *cargoView2;
GtkTreeViewColumn *c10;
GtkTreeViewColumn *c11;
GtkTreeViewColumn *c12;
GtkTreeViewColumn *c13;
GtkTreeViewColumn *c14;
GtkCellRenderer *cr10;
GtkCellRenderer *cr11;
GtkCellRenderer *cr12;
GtkCellRenderer *cr13;
GtkCellRenderer *cr14;

GtkTreeStore *cargoTreeStore3;
GtkTreeView *cargoView3;
GtkTreeViewColumn *c15;
GtkTreeViewColumn *c16;
GtkTreeViewColumn *c17;
GtkTreeViewColumn *c18;
GtkTreeViewColumn *c19;
GtkCellRenderer *cr15;
GtkCellRenderer *cr16;
GtkCellRenderer *cr17;
GtkCellRenderer *cr18;
GtkCellRenderer *cr19;

GtkWidget *searchByIDField;


void listCargos();
void showMessage(char* title, char* msg);

void undeliveredDetails(GtkButton *b)
{

    GtkTreeSelection *selection = gtk_tree_view_get_selection(cargoView1);
    priorityQueue* queue = (priorityQueue*) g_object_get_data(G_OBJECT(window),"priority_queue");
    sortedList* onTheWayDeliveries = (sortedList*) g_object_get_data(G_OBJECT(window),"onTheWayDeliveries");
    customer* head = (customer*) g_object_get_data(G_OBJECT(window),"customer_head");
    GtkTreeModel *model;
    GtkTreeIter iter;

    // Check if there is a selected row
    if (gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        gchar *value;
        gtk_tree_model_get(model, &iter, 0, &value, -1);

        int num_chars_parsed = 0;
        int numericId;

        // Try to parse the integer and capture where parsing ends
        if (sscanf(value, "%d%n", &numericId, &num_chars_parsed) == 1)
        {
            // Check if parsing consumed the entire string
            if (value[num_chars_parsed] == '\0')
            {

                int newSize = queue->items + onTheWayDeliveries->items;

                delivery** sortedArray = joinArrays(queue->heap,queue->items,onTheWayDeliveries->arr,onTheWayDeliveries->items);

                insertionSort(sortedArray,newSize);

                delivery* cargo = binarySearch(sortedArray,0,newSize-1,numericId);

                if(cargo != NULL)
                {

                    customer* owner = findCustomer(head,cargo->customerId);

                    if(owner == NULL){

                        g_print("The owner was not found");

                    }

                    char message[400];

                    snprintf(message, sizeof(message), "ID: %d | From: %s | To: %s \n Müşteri: %s %s | ID: %d \n Açıklama: %s | Teslimat süresi: %d gün", numericId, cargo->from,
                     cargo->to,owner->name,owner->surname,owner->id,cargo->description, cargo->distance);


                    showMessage("Detaylar", message);




                }
                else
                {

                    showMessage("Hata","Kargo bulunamadı");


                }

                free(sortedArray);


            }
            else
            {

                showMessage("Hata","Bir hata olmuştur");

            }

        }
        else
        {

            showMessage("Hata","Bir hata olmuştur");

        }

        g_free(value);

    }
    else
    {

        showMessage("Uyarı","Bir satır seçiniz");
    }

}

void deliveredDetails(GtkButton *b)
{

    GtkTreeSelection *selection = gtk_tree_view_get_selection(cargoView2);
    sortedList* deliveredDeliveries = (sortedList*) g_object_get_data(G_OBJECT(window),"deliveredDeliveries");
    customer* head = (customer*) g_object_get_data(G_OBJECT(window),"customer_head");
    GtkTreeModel *model;
    GtkTreeIter iter;

    // Check if there is a selected row
    if (gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        gchar *value;
        gtk_tree_model_get(model, &iter, 0, &value, -1);

        int num_chars_parsed = 0;
        int numericId;

        // Try to parse the integer and capture where parsing ends
        if (sscanf(value, "%d%n", &numericId, &num_chars_parsed) == 1)
        {
            // Check if parsing consumed the entire string
            if (value[num_chars_parsed] == '\0')
            {

                delivery* cargo = binarySearch(deliveredDeliveries->arr,0,deliveredDeliveries->items-1,numericId);

                if(cargo != NULL)
                {

                    customer* owner = findCustomer(head,cargo->customerId);

                    if(owner == NULL){

                        g_print("The owner was not found");

                    }

                    char message[400];

                    snprintf(message, sizeof(message), "ID: %d | From: %s | To: %s \n Müşteri: %s %s | ID: %d \n Açıklama: %s | Teslimat süresi: %d gün", numericId, cargo->from,
                     cargo->to,owner->name,owner->surname,owner->id,cargo->description, cargo->distance);


                    showMessage("Detaylar", message);


                }
                else
                {

                    showMessage("Hata","Kargo bulunamadı");

                }


            }
            else
            {

                showMessage("Hata","Bir hata olmuştur");

            }

        }
        else
        {

            showMessage("Hata","Bir hata olmuştur");

        }

        g_free(value);

    }
    else
    {

        showMessage("Uyarı","Bir satır seçiniz");
    }

}

void showMessage(char* title, char* msg)
{

    GtkWidget *dialog = gtk_dialog_new();
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));
    gtk_window_set_title(GTK_WINDOW(dialog), title);
    gtk_widget_set_size_request(dialog,200,150);
    gtk_widget_show(dialog);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_box_set_spacing(GTK_BOX(content_area), 10);

    GtkWidget *label = gtk_label_new(msg);

    gtk_widget_set_margin_top(label, 20);
    gtk_widget_set_margin_bottom(label, 20);
    gtk_widget_set_margin_start(label, 20);
    gtk_widget_set_margin_end(label, 20);

    gtk_container_add(GTK_CONTAINER(content_area), label);

    gtk_widget_show_all(dialog);


}

void processCargos()
{

    priorityQueue* queue = (priorityQueue*) g_object_get_data(G_OBJECT(window),"priority_queue");
    sortedList* onTheWayDeliveries = (sortedList*) g_object_get_data(G_OBJECT(window),"onTheWayDeliveries");
    sortedList* deliveredDeliveries = (sortedList*) g_object_get_data(G_OBJECT(window),"deliveredDeliveries");

    delivery* currentDelivery = dequeueDelivery(queue);

    if(currentDelivery != NULL)
    {

        currentDelivery->state++;

        //g_print("Processing the following delivery:\n");
        //g_print("From: %s To: %s\n",currentDelivery->from,currentDelivery->to);
        //g_print("State: %s, Distance %d\n",get_delivery_state_name(currentDelivery->state),currentDelivery->distance);

        addToList(onTheWayDeliveries,currentDelivery);

        printAllCargos(onTheWayDeliveries);

    }

    int i;

    for(i=0; i<onTheWayDeliveries->items; i++)
    {

        if(onTheWayDeliveries->arr[i]->remainingDays == 0)
        {

            //g_print("Quedan 0 dias\n");

            onTheWayDeliveries->arr[i]->state++;
            addToList(deliveredDeliveries,onTheWayDeliveries->arr[i]);
            removeFromList(onTheWayDeliveries,i);

        }
        else
        {

            //g_print("No quedan 0 dias\n");

            //g_print("Quedan %d dias\n",onTheWayDeliveries->arr[i]->remainingDays);

            onTheWayDeliveries->arr[i]->remainingDays--;

        }
    }

    const char *visible_child_name = gtk_stack_get_visible_child_name(GTK_STACK(stack));

    if (strcmp(visible_child_name,"cargo_info_page") == 0)
    {

        listCargos();

    }

}

void goToMenu (GtkButton *b)
{


    gtk_stack_set_visible_child_name(GTK_STACK(stack),"menu_page");


}

void goToRouteMap (GtkButton *b)
{

    gtk_stack_set_visible_child_name(GTK_STACK(stack), "route_page");


}

void goToNewCustomer (GtkButton *b)
{

    gtk_stack_set_visible_child_name(GTK_STACK(stack), "new_costumer_page");


}

void goToNewCargo (GtkButton *b)
{

    gtk_stack_set_visible_child_name(GTK_STACK(stack), "new_cargo_page");


}

void goToListCustomers (GtkButton *b)
{

    gtk_stack_set_visible_child_name(GTK_STACK(stack), "list_customers_page");

    gtk_tree_store_clear(treeStore);

    customer* head = (customer*) g_object_get_data(G_OBJECT(window),"customer_head");

    if(head != NULL)
    {

        customer* temp = head;
        GtkTreeIter iter;

        while(temp != NULL)
        {

            char id_str[20];  // Buffer to hold the converted string
            snprintf(id_str, sizeof(id_str), "%d", temp->id);

            gtk_tree_store_append(treeStore,&iter,NULL);

            gtk_tree_store_set(treeStore,&iter,0,temp->name,1,temp->surname,2,temp->city,3,id_str,-1);

            temp = temp->next;

        }

    }
    else
    {

        showMessage("Uyarı","Kaydedilmiş müşteri yok");

    }

}

void on_goToListCargos_clicked(GtkButton *b)
{

    gtk_stack_set_visible_child_name(GTK_STACK(stack), "cargo_info_page");
    listCargos();
}

void on_goToCargoHistory_clicked(GtkButton *b)
{

    gtk_stack_set_visible_child_name(GTK_STACK(stack), "customer_history_page");

}

void listCargos()
{

    priorityQueue* queue = (priorityQueue*) g_object_get_data(G_OBJECT(window),"priority_queue");
    sortedList* onTheWayDeliveries = (sortedList*) g_object_get_data(G_OBJECT(window),"onTheWayDeliveries");
    sortedList* deliveredDeliveries = (sortedList*) g_object_get_data(G_OBJECT(window),"deliveredDeliveries");

    g_print("Printing all cargos: \n");

    g_print("Priority Queue: \n");

    g_print("Number of items of the list: %d\n",queue->items);
    g_print("Capacity of the list: %d\n",queue->capacity);

    printArray(queue->heap,queue->items);

    g_print("On the way: \n");

    printAllCargos(onTheWayDeliveries);

    g_print("Delivered: \n");

    printAllCargos(deliveredDeliveries);

    g_print("\n");

    gtk_tree_store_clear(cargoTreeStore);
    gtk_tree_store_clear(cargoTreeStore2);

    GtkTreeIter iter;

    int i;
    int newSize = queue->items + onTheWayDeliveries->items;

    delivery** sortedArray = joinArrays(queue->heap,queue->items,onTheWayDeliveries->arr,onTheWayDeliveries->items);

    mergeSort(sortedArray,0,newSize- 1);

    for(i=0; i<newSize; i++)
    {

        char id_str[20];  // Buffer to hold the converted string
        snprintf(id_str, sizeof(id_str), "%d", sortedArray[i]->id);

        gtk_tree_store_append(cargoTreeStore,&iter,NULL);

        gtk_tree_store_set(cargoTreeStore,&iter,0,id_str,1,sortedArray[i]->from,2,sortedArray[i]->to,-1);
        gtk_tree_store_set(cargoTreeStore,&iter,3,get_delivery_state_name(sortedArray[i]->state),4,sortedArray[i]->distance,-1);
    }

    for(i=0; i<deliveredDeliveries->items; i++)
    {

        char id_str[20];  // Buffer to hold the converted string
        snprintf(id_str, sizeof(id_str), "%d", deliveredDeliveries->arr[i]->id);

        gtk_tree_store_append(cargoTreeStore2,&iter,NULL);

        gtk_tree_store_set(cargoTreeStore2,&iter,0,id_str,1,deliveredDeliveries->arr[i]->from,2,deliveredDeliveries->arr[i]->to,-1);
        gtk_tree_store_set(cargoTreeStore2,&iter,3,get_delivery_state_name(deliveredDeliveries->arr[i]->state),4,deliveredDeliveries->arr[i]->distance,-1);
    }

    free(sortedArray);
    sortedArray = NULL;

}

void on_newCargoButton_clicked(GtkButton *b)
{

    int id;
    const char* description = gtk_entry_get_text(GTK_ENTRY(descriptionField));
    const char* customerId = gtk_entry_get_text(GTK_ENTRY(customerIdField));
    gchar*  toCity = NULL;
    customer* head = (customer*) g_object_get_data(G_OBJECT(window),"customer_head");
    priorityQueue* queue = (priorityQueue*) g_object_get_data(G_OBJECT(window),"priority_queue");
    city* root = (city*) g_object_get_data(G_OBJECT(window),"cities_root");

    if(strlen(description) > 2 && strlen(customerId) == 9)
    {

        // Get the destination city from the comboBox
        if (gtk_combo_box_get_active_iter(GTK_COMBO_BOX(citiesComboBox2), &iter2))
        {
            gtk_tree_model_get(citiesModel2, &iter2, 0,&toCity, -1);
        }

        id = generateId();

        int num_chars_parsed = 0;
        int numericId;

        // Try to parse the integer and capture where parsing ends
        if (sscanf(customerId, "%d%n", &numericId, &num_chars_parsed) == 1)
        {

            // Check if parsing consumed the entire string
            if (customerId[num_chars_parsed] == '\0')
            {

                customer* c = findCustomer(head,numericId);

                if(c != NULL)
                {

                    int distance = calculateDistance(root,c->city,(char*)toCity);

                    if(distance >= 0)
                    {

                        delivery* newCargo = createNewDelivery(distance,c->city,(char*)toCity,numericId,id,description);

                        enqueueDelivery(queue,newCargo);

                        pushToStack(c,newCargo);

                        //g_print("A new delivery was created successfully\n");

                        gtk_entry_set_text(GTK_ENTRY(customerIdField), "");
                        gtk_entry_set_text(GTK_ENTRY(descriptionField), "");

                        g_free(toCity);
                        toCity = NULL;

                    }
                    else
                    {

                        showMessage("Hata","Mesafeyi hesaplarken bir sorun oluştu");

                    }



                }
                else
                {

                    showMessage("Uyarı","Lütfen geçerli bir müşteri ID giriniz");

                }

            }
            else
            {

                showMessage("Uyarı","Lütfen geçerli bir müşteri ID giriniz");

            }

        }
        else
        {

            showMessage("Uyarı","Lütfen geçerli bir müşteri ID giriniz");

        }

    }
    else
    {

        showMessage("Uyarı","Lütfen geçerli veri giriniz");

    }
}

void on_newCustomerButton_clicked (GtkButton *b)
{

    int id;
    const char* name = gtk_entry_get_text(GTK_ENTRY(nameField));
    const char* surname = gtk_entry_get_text(GTK_ENTRY(surnameField));
    gchar* city = NULL;
    customer* head = (customer*) g_object_get_data(G_OBJECT(window),"customer_head");

    if(strlen(name) > 2 && strlen(surname) > 2)
    {

        // Get the active row from the combo box
        if (gtk_combo_box_get_active_iter(GTK_COMBO_BOX(citiesComboBox1), &iter1))
        {
            gtk_tree_model_get(citiesModel, &iter1, 0,&city, -1);
        }

        id = generateId();

        head = newCustomer(head,name,surname,(char*)city,id);
        g_object_set_data(G_OBJECT(window), "customer_head", head);

        g_free(city);

        gtk_entry_set_text(GTK_ENTRY(nameField), "");
        gtk_entry_set_text(GTK_ENTRY(surnameField), "");


    }
    else
    {

        showMessage("Uyarı","Lütfen geçerli veri giriniz");

    }

}

void showHistory(GtkButton *b)
{

    const char* customerId = gtk_entry_get_text(GTK_ENTRY(searchByIDField));
    customer* head = (customer*) g_object_get_data(G_OBJECT(window),"customer_head");

    if(strlen(customerId) == 9)
    {

        int num_chars_parsed = 0;
        int numericId;

        // Try to parse the integer and capture where parsing ends
        if (sscanf(customerId, "%d%n", &numericId, &num_chars_parsed) == 1)
        {

            // Check if parsing consumed the entire string
            if (customerId[num_chars_parsed] == '\0')
            {

                customer* c = findCustomer(head,numericId);

                if(c != NULL)
                {


                    if(c->mostRecent != NULL)
                    {


                        gtk_tree_store_clear(cargoTreeStore3);

                        GtkTreeIter iter;

                        delivery* currentNode = c->mostRecent;

                        while(currentNode != NULL)
                        {

                            char id_str[20];  // Buffer to hold the converted string
                            snprintf(id_str, sizeof(id_str), "%d", currentNode->id);

                            gtk_tree_store_append(cargoTreeStore3,&iter,NULL);

                            gtk_tree_store_set(cargoTreeStore3,&iter,0,id_str,1,currentNode->from,2,currentNode->to,-1);
                            gtk_tree_store_set(cargoTreeStore3,&iter,3,get_delivery_state_name(currentNode->state),4,currentNode->distance,-1);

                            currentNode = currentNode->previous;
                        }


                    }
                    else
                    {


                        showMessage("Sonuç","Gösterilecek bir kargo geçmişi yok");

                    }

                }
                else
                {

                    showMessage("Uyarı","Lütfen geçerli bir müşteri ID giriniz");

                }

            }
            else
            {

                showMessage("Uyarı","Lütfen geçerli bir müşteri ID giriniz");

            }

        }
        else
        {

            showMessage("Uyarı","Lütfen geçerli bir müşteri ID giriniz");

        }

    }
    else
    {

        showMessage("Uyarı","Lütfen geçerli bir müşteri ID giriniz");

    }

}

int main(int argc, char *argv[])
{

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
    customerIdField = GTK_WIDGET(gtk_builder_get_object(builder,"customerid"));
    descriptionField = GTK_WIDGET(gtk_builder_get_object(builder,"description"));
    citiesComboBox2 = GTK_WIDGET(gtk_builder_get_object(builder,"citiesComboBox2"));

    searchByIDField = GTK_WIDGET(gtk_builder_get_object(builder,"searchById"));

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

    g_object_set(cr4, "editable", TRUE, NULL);


    gtk_tree_view_set_model(customersView, GTK_TREE_MODEL(treeStore));

    c5 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"c5"));
    c6 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"c6"));
    c7 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"c7"));
    c8 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"c8"));
    c9 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"c9"));

    cr5 = GTK_CELL_RENDERER(gtk_builder_get_object(builder,"cr5"));
    cr6 = GTK_CELL_RENDERER(gtk_builder_get_object(builder,"cr6"));
    cr7 = GTK_CELL_RENDERER(gtk_builder_get_object(builder,"cr7"));
    cr8 = GTK_CELL_RENDERER(gtk_builder_get_object(builder,"cr8"));
    cr9 = GTK_CELL_RENDERER(gtk_builder_get_object(builder,"cr9"));

    gtk_tree_view_column_add_attribute(c5,cr5,"text",0);
    gtk_tree_view_column_add_attribute(c6,cr6,"text",1);
    gtk_tree_view_column_add_attribute(c7,cr7,"text",2);
    gtk_tree_view_column_add_attribute(c8,cr8,"text",3);
    gtk_tree_view_column_add_attribute(c9,cr9,"text",4);

    cargoView1 = GTK_TREE_VIEW(gtk_builder_get_object(builder,"cargoView1"));
    cargoTreeStore = GTK_TREE_STORE(gtk_builder_get_object(builder,"cargoTreeStore"));

    gtk_tree_view_set_model(cargoView1, GTK_TREE_MODEL(cargoTreeStore));

    c10 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"c10"));
    c11 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"c11"));
    c12 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"c12"));
    c13 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"c13"));
    c14 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"c14"));

    cr10 = GTK_CELL_RENDERER(gtk_builder_get_object(builder,"cr10"));
    cr11 = GTK_CELL_RENDERER(gtk_builder_get_object(builder,"cr11"));
    cr12 = GTK_CELL_RENDERER(gtk_builder_get_object(builder,"cr12"));
    cr13 = GTK_CELL_RENDERER(gtk_builder_get_object(builder,"cr13"));
    cr14 = GTK_CELL_RENDERER(gtk_builder_get_object(builder,"cr14"));

    gtk_tree_view_column_add_attribute(c10,cr10,"text",0);
    gtk_tree_view_column_add_attribute(c11,cr11,"text",1);
    gtk_tree_view_column_add_attribute(c12,cr12,"text",2);
    gtk_tree_view_column_add_attribute(c13,cr13,"text",3);
    gtk_tree_view_column_add_attribute(c14,cr14,"text",4);

    cargoView2 = GTK_TREE_VIEW(gtk_builder_get_object(builder,"cargoView2"));
    cargoTreeStore2 = GTK_TREE_STORE(gtk_builder_get_object(builder,"cargoTreeStore2"));

    gtk_tree_view_set_model(cargoView2, GTK_TREE_MODEL(cargoTreeStore2));

    c15 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"c15"));
    c16 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"c16"));
    c17 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"c17"));
    c18 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"c18"));
    c19 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"c19"));

    cr15 = GTK_CELL_RENDERER(gtk_builder_get_object(builder,"cr15"));
    cr16 = GTK_CELL_RENDERER(gtk_builder_get_object(builder,"cr16"));
    cr17 = GTK_CELL_RENDERER(gtk_builder_get_object(builder,"cr17"));
    cr18 = GTK_CELL_RENDERER(gtk_builder_get_object(builder,"cr18"));
    cr19 = GTK_CELL_RENDERER(gtk_builder_get_object(builder,"cr19"));

    gtk_tree_view_column_add_attribute(c15,cr15,"text",0);
    gtk_tree_view_column_add_attribute(c16,cr16,"text",1);
    gtk_tree_view_column_add_attribute(c17,cr17,"text",2);
    gtk_tree_view_column_add_attribute(c18,cr18,"text",3);
    gtk_tree_view_column_add_attribute(c19,cr19,"text",4);

    cargoView3 = GTK_TREE_VIEW(gtk_builder_get_object(builder,"cargoView3"));
    cargoTreeStore3 = GTK_TREE_STORE(gtk_builder_get_object(builder,"cargoTreeStore3"));

    gtk_tree_view_set_model(cargoView3, GTK_TREE_MODEL(cargoTreeStore3));

    g_signal_connect(window,"destroy", G_CALLBACK(gtk_main_quit),NULL);

    gtk_builder_connect_signals(builder,NULL); //connects all signals with the callbacks defined in glade file

    // Load the CSS
    GtkCssProvider *provider = gtk_css_provider_new();
    GError *error = NULL;
    gtk_css_provider_load_from_path(provider, "styles.css", &error);

    // Get the default screen
    GdkScreen *screen = gdk_screen_get_default();

    if (error != NULL)
    {
        g_warning("Error loading CSS file: %s", error->message);
        g_error_free(error);
    }
    else
    {

        gtk_style_context_add_provider_for_screen(screen,
                GTK_STYLE_PROVIDER(provider),
                GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    }

    g_object_unref(provider);

    gtk_widget_show_all(window);

    seedRand();
    citiesModel = gtk_combo_box_get_model(GTK_COMBO_BOX(citiesComboBox1));
    citiesModel2 = gtk_combo_box_get_model(GTK_COMBO_BOX(citiesComboBox2));

    customer* head = (customer*) malloc(sizeof(customer));
    head = NULL;
    g_object_set_data(G_OBJECT(window), "customer_head", head);

    city* citiesRoot = createCityTree();
    g_object_set_data(G_OBJECT(window), "cities_root", citiesRoot);

    priorityQueue* queue = createNewQueue(10);
    g_object_set_data(G_OBJECT(window),"priority_queue",queue);

    sortedList* onTheWayDeliveries = createNewList(20);
    g_object_set_data(G_OBJECT(window),"onTheWayDeliveries",onTheWayDeliveries);

    sortedList* deliveredDeliveries = createNewList(20);
    g_object_set_data(G_OBJECT(window),"deliveredDeliveries",deliveredDeliveries);

    gtk_main();

    freeList(onTheWayDeliveries);
    onTheWayDeliveries = NULL;
    freeList(deliveredDeliveries);
    deliveredDeliveries = NULL;
    freeQueue(queue);
    queue = NULL;
    freeCustomers(head);
    head = NULL;
    freeCities(citiesRoot);
    citiesRoot = NULL;

    return 0;

}
