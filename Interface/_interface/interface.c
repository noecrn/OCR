#include <gtk/gtk.h>

char *rotate_filename = ".rotate_image.png";
char *global_filename = NULL;


void load_image(const char *filename, gpointer user_data);

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
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        global_filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

        // Load the image into a GdkPixbuf object
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, NULL);

        // Cast user_data to GtkImage
        GtkImage *image = GTK_IMAGE(user_data);

        if (pixbuf != NULL) {
            // Set the desired maximum size (for example, width of 200 pixels)
            int max_width = 500;
            int width = gdk_pixbuf_get_width(pixbuf);
            int height = gdk_pixbuf_get_height(pixbuf);

            // Calculate the new height while maintaining the ratio
            int new_width, new_height;
            if (width > max_width) {
                new_width = max_width;
                new_height = (height * max_width) / width;
            } else {
                new_width = width;
                new_height = height;
            } 

            // Resize the image
            GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, new_width, 
            new_height, GDK_INTERP_BILINEAR);

            // Display the resized image in the GtkImage widget
            gtk_image_set_from_pixbuf(image, scaled_pixbuf);

            // Free the memory allocated for the GdkPixbufs
            g_object_unref(pixbuf);
            g_object_unref(scaled_pixbuf);
            printf("Filename: %s\n", filename);
        }

        // Libérez la mémoire allouée pour le nom du fichier
        g_free(filename);
    }

    // Fermez la boîte de dialogue
    gtk_widget_destroy(dialog);
}

void load_image(const char *filename, gpointer user_data) {
    GtkWidget *imageWidget = GTK_WIDGET(user_data);

    // Load the image into a GdkPixbuf object
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(rotate_filename, NULL);

    // Cast user_data to GtkImage
    GtkImage *image = GTK_IMAGE(user_data);

    if (pixbuf != NULL) {
        // Set the desired maximum size (for example, width of 200 pixels)
        int max_width = 500;
        int width = gdk_pixbuf_get_width(pixbuf);
        int height = gdk_pixbuf_get_height(pixbuf);

        // Calculate the new height while maintaining the ratio
        int new_width, new_height;
        if (width > max_width) {
            new_width = max_width;
            new_height = (height * max_width) / width;
        } else {
            new_width = width;
            new_height = height;
        } 

        // Resize the image
        GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, new_width, 
        new_height, GDK_INTERP_BILINEAR);

        // Display the resized image in the GtkImage widget
        gtk_image_set_from_pixbuf(image, scaled_pixbuf);

        // Free the memory allocated for the GdkPixbufs
        g_object_unref(pixbuf);
        g_object_unref(scaled_pixbuf);
        printf("Filename: %s\n", rotate_filename);
    }
}

int angle = 0;

void on_rotateLeftButton_clicked(GtkButton *button, gpointer user_data) {
    // Use the system() function to execute the rotation program
    angle = angle + 90;
    char rotation_command_left[256];
    sprintf(rotation_command_left, "../rotate/save %s %d .rotate_image.png", global_filename, angle);
    int status = system(rotation_command_left);

    if (status != 0) {
        // Handle errors from executing the rotation program
        g_print("Error executing the rotation program.\n");
    }
}

void on_rotateRightButton_clicked(GtkButton *button, gpointer user_data) {
    // Use the system() function to execute the rotation program
    angle = angle - 90;
    char rotation_command_right[256];
    sprintf(rotation_command_right, "../rotate/save %s %d .rotate_image.png", global_filename, angle);
    int status = system(rotation_command_right);

    if (status != 0) {
        // Handle errors from executing the rotation program
        g_print("Error executing the rotation program.\n");
    }
}

// Déclaration de la fonction on_window_delete_event
gboolean on_window_delete_event(GtkWidget *widget, GdkEvent *event, 
gpointer data) 
{
    gtk_main_quit(); // Ceci arrête la boucle principale GTK
    return FALSE; // Si vous ne retournez pas FALSE, la fenêtre ne se fermera pas
}

void unhide_file() {
    if (rotate_filename[0] == '.') {
        char newname[256];
        strcpy(newname, &rotate_filename[1]);

        if (rename(rotate_filename, newname) == 0) {
            printf("File successfully renamed\n");
        } else {
            printf("Error renaming file\n");
        }
    } else {
        printf("File is not hidden\n");
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkBuilder *builder;
    GtkWidget *window;
    GtkWidget *imageWidget;
    GtkWidget *rotateLeftButton;
    GtkWidget *rotateRightButton;

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "interface.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    imageWidget = GTK_WIDGET(gtk_builder_get_object(builder, "image"));

    GtkWidget *rotateButton = GTK_WIDGET(gtk_builder_get_object(builder, "rotateButton"));   
    GtkWidget *loadButton = GTK_WIDGET(gtk_builder_get_object(builder, "loadButton"));
    g_signal_connect(loadButton, "clicked", G_CALLBACK(on_loadButton_clicked), imageWidget);
    

    // Connectez le signal de fermeture de la fenêtre à la fonction de gestion
    g_signal_connect(window, "delete-event", 
    G_CALLBACK(on_window_delete_event), NULL);

    // Get the buttons from the builder
    rotateLeftButton = GTK_WIDGET(gtk_builder_get_object(builder, "rotateLeftButton"));
    rotateRightButton = GTK_WIDGET(gtk_builder_get_object(builder, "rotateRightButton"));

    // Connect the buttons to the respective functions
    g_signal_connect(rotateLeftButton, "clicked", G_CALLBACK(on_rotateLeftButton_clicked), NULL);
    g_signal_connect(rotateLeftButton, "clicked", G_CALLBACK(load_image), imageWidget);
    g_signal_connect(rotateRightButton, "clicked", G_CALLBACK(on_rotateRightButton_clicked), NULL);
    g_signal_connect(rotateRightButton, "clicked", G_CALLBACK(load_image), imageWidget);

    GtkWidget *saveButton = GTK_WIDGET(gtk_builder_get_object(builder, "saveButton"));
    g_signal_connect(saveButton, "clicked", G_CALLBACK(unhide_file), NULL);
   
    // Désactivez la redimension de la fenêtre
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    gtk_window_set_default_size(GTK_WINDOW(window), 900, 600);
    
    //gtk_window_is_maximized(GTK_WINDOW(window));

    gtk_widget_show_all(window); // Afficher tous les widgets de la fenêtre

    gtk_main();

    return 0;
}