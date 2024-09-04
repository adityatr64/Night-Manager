#include <gtk/gtk.h>
#include <vte/vte.h>

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Split Window with Terminal");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // Create a vertical box to hold the top and bottom halves
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // Create a label for the top half
    GtkWidget *label = gtk_label_new("Hello, World!");
    gtk_widget_set_size_request(label, 1, 100); // Set a fixed height for demonstration

    // Create a VTE terminal for the bottom half
    GtkWidget *terminal = vte_terminal_new();
    vte_terminal_spawn_async(VTE_TERMINAL(terminal), VTE_PTY_DEFAULT, NULL,
                             (char *[]){"/bin/bash", NULL}, NULL,
                             G_SPAWN_DEFAULT, NULL, NULL, NULL, -1, NULL, NULL, NULL);

    // Pack the label and terminal into the vertical box
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(vbox), terminal, TRUE, TRUE, 0);

    // Add the vertical box to the window
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Connect the destroy signal to quit GTK
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}
