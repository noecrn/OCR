#include <gtk/gtk.h>

void on_loadButton_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *imageWidget = GTK_WIDGET(user_data); 

    // Créez une boîte de dialogue de sélection de fichiers
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;

    dialog = gtk_file_chooser_dialog_new("Open Image File",
                                         GTK_WINDOW(
                                            gtk_widget_get_toplevel(
                                                imageWidget)),
                                         action,
                                         "Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         "Open",
                                         GTK_RESPONSE_ACCEPT,
                                         NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        // Récupérez le chemin du fichier sélectionné
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)
        );

        // Chargez l'image dans un objet GdkPixbuf
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, NULL);

        if (pixbuf != NULL) {
            // Définissez la taille maximale souhaitée (par exemple, largeur de 200 pixels)
            int max_width = 500;
            int width = gdk_pixbuf_get_width(pixbuf);
            int height = gdk_pixbuf_get_height(pixbuf);

            // Calculez la nouvelle hauteur en maintenant le ratio
            int new_width, new_height;
            if (width > max_width) {
                new_width = max_width;
                new_height = (height * max_width) / width;
            } else {
                new_width = width;
                new_height = height;
            } 

            // Redimensionnez l'image
            GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, new_width, 
            new_height, GDK_INTERP_BILINEAR);

            // Affichez l'image redimensionnée dans le widget GtkImage
            gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidget), scaled_pixbuf);

            // Libérez la mémoire allouée pour les GdkPixbuf
            g_object_unref(pixbuf);
            g_object_unref(scaled_pixbuf);
        }

        // Libérez la mémoire allouée pour le nom du fichier
        g_free(filename);
    }

    // Fermez la boîte de dialogue
    gtk_widget_destroy(dialog);
}

void on_rotateButton_clicked(GtkButton *button, gpointer user_data) {
    // Utilisez la fonction system() pour exécuter le programme de rotation
    const char *rotation_command = "../image_transform/main"; // Assurez-vous que le chemin est correct
    int status = system(rotation_command);

    if (status == 0) {
        // Le programme de rotation s'est exécuté avec succès, rechargez l'image
        on_loadButton_clicked(button, user_data);
    } else {
        // Gérez les erreurs d'exécution du programme de rotation
        g_print("Erreur lors de l'exécution du programme de rotation.\n");
    }
}

// Déclaration de la fonction on_window_delete_event
gboolean on_window_delete_event(GtkWidget *widget, GdkEvent *event, 
gpointer data) 
{
    // Vous pouvez ajouter du code ici pour gérer la fermeture de la fenêtre
    // Par exemple, pour quitter l'application :
    gtk_main_quit(); // Ceci arrête la boucle principale GTK
    return FALSE; // Si vous ne retournez pas FALSE, la fenêtre ne se fermera pas
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkBuilder *builder;
    GtkWidget *window;
    GtkWidget *imageWidget;

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "interface.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    imageWidget = GTK_WIDGET(gtk_builder_get_object(builder, "image"));

    GtkWidget *rotateButton = 
    GTK_WIDGET(gtk_builder_get_object(builder, "rotateButton"));   
    GtkWidget *loadButton = 
    GTK_WIDGET(gtk_builder_get_object(builder, "loadButton"));
    g_signal_connect(loadButton, "clicked", 
    G_CALLBACK(on_loadButton_clicked), imageWidget);
    g_signal_connect(rotateButton, "clicked", 
    G_CALLBACK(on_rotateButton_clicked), imageWidget);
    

    // Connectez le signal de fermeture de la fenêtre à la fonction de gestion
    g_signal_connect(window, "delete-event", 
    G_CALLBACK(on_window_delete_event), NULL);
   
    // Désactivez la redimension de la fenêtre
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    gtk_window_set_default_size(GTK_WINDOW(window), 900, 600);
    
    //gtk_window_is_maximized(GTK_WINDOW(window));

    gtk_widget_show_all(window); // Afficher tous les widgets de la fenêtre

    gtk_main();

    return 0;
}

