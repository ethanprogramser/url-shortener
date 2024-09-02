#include<curl/curl.h>
#include<gtk/gtk.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

GtkWidget *window;
GtkWidget *button;
GtkWidget *label;
GtkWidget *entry;
GtkWidget *box;
GtkWidget *ent2;

void read_and_d() {

    FILE *fp = fopen("t.txt", "r");
    char buffer[100] = { 0 };

    fgets(buffer, 100, fp);
    gtk_entry_set_text(GTK_ENTRY(ent2), buffer);
    gtk_container_add(GTK_CONTAINER(box), ent2);
    gtk_widget_show_all(window);
}

static void request(GtkWidget *but, gpointer *data) {
    char buffer[100] = { 0 };
    const gchar *p = gtk_entry_get_text(GTK_ENTRY(entry));
    strcat(buffer, "curl 'https://is.gd/create.php?format=simple&url=");
    strcat(buffer, p);
    strcat(buffer, "' > t.txt");
    
    char *r = strtok(buffer, "");

    system(r);

    read_and_d();
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    label = gtk_label_new("paste url here:");
    entry = gtk_entry_new();
    button = gtk_button_new_with_label("get url");
    ent2 = gtk_entry_new();

    g_signal_connect(button, "clicked", G_CALLBACK(request), NULL);
  
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_container_add(GTK_CONTAINER(box), label);
    gtk_container_add(GTK_CONTAINER(box), entry);
    gtk_container_add(GTK_CONTAINER(box), button);

    gtk_widget_show_all(window);
    gtk_main();
    
    return 0;
}
