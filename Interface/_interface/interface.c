#include <gtk/gtk.h>
//#include "../display/display_solved.h"

char *rotate_filename = ".rotate_image.png";
char *solve_filename = "solved_grid.png";
char *grid_filename = "grid_detection.png";
char *sudoku_grid_filename = "sudoku_grid.jpg";
char *global_filename = NULL;

GtkWidget *rotateLeftButton;
GtkWidget *rotateRightButton;
GtkWidget *saveButton;
GtkWidget *solveButton;
GtkWidget *gridButton;
GtkWidget *entry[9][9];

void load_image_rotate(const char *filename, gpointer user_data);
void on_loadButton_clicked(GtkButton *button, gpointer user_data);
void on_rotateLeftButton_clicked(GtkButton *button, gpointer user_data);
void on_rotateRightButton_clicked(GtkButton *button, gpointer user_data);

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
            int max_width = 900;
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

    gtk_widget_set_sensitive(GTK_WIDGET(rotateLeftButton), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(rotateRightButton), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(saveButton), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(solveButton), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(gridButton), TRUE);

    // Fermez la boîte de dialogue
    gtk_widget_destroy(dialog);
}

void load_image_rotate(const char *filename, gpointer user_data) {
    GtkWidget *imageWidget = GTK_WIDGET(user_data);

    // Load the image into a GdkPixbuf object
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(rotate_filename, NULL);

    // Cast user_data to GtkImage
    GtkImage *image = GTK_IMAGE(user_data);

    if (pixbuf != NULL) {
        // Set the desired maximum size (for example, width of 200 pixels)
        int max_width = 900;
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

void load_image_solve(const char *filename, gpointer user_data) {
    GtkWidget *imageWidget = GTK_WIDGET(user_data);

    // Load the image into a GdkPixbuf object
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(solve_filename, NULL);

    // Cast user_data to GtkImage
    GtkImage *image = GTK_IMAGE(user_data);

    if (pixbuf != NULL) {
        // Set the desired maximum size (for example, width of 200 pixels)
        int max_width = 900;
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
        printf("Filename: %s\n", solve_filename);
    }
}

void load_image_grid(const char *filename, gpointer user_data) {
    GtkWidget *imageWidget = GTK_WIDGET(user_data);

    // Load the image into a GdkPixbuf object
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(grid_filename, NULL);

    // Cast user_data to GtkImage
    GtkImage *image = GTK_IMAGE(user_data);

    if (pixbuf != NULL) {
        // Set the desired maximum size (for example, width of 200 pixels)
        int max_width = 900;
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
        printf("Filename: %s\n", solve_filename);
    }
}

void load_sudoku_grid(const char *filename, gpointer user_data) {
    GtkWidget *imageWidget = GTK_WIDGET(user_data);

    printf("Load sudoku grid\n");

    // Load the image into a GdkPixbuf object
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(grid_filename, NULL);

    // Cast user_data to GtkImage
    GtkImage *image = GTK_IMAGE(user_data);

    if (pixbuf != NULL) {
        // Set the desired maximum size (for example, width of 200 pixels)
        int max_width = 900;
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
        printf("Filename: %s\n", sudoku_grid_filename);
    }
}

int angle = 0;

void on_rotateLeftButton_clicked(GtkButton *button, gpointer user_data) {
    // Use the system() function to execute the rotation program
    angle = angle + 5;
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
    angle = angle - 5;
    char rotation_command_right[256];
    sprintf(rotation_command_right, "../rotate/save %s %d .rotate_image.png", global_filename, angle);
    int status = system(rotation_command_right);

    if (status != 0) {
        // Handle errors from executing the rotation program
        g_print("Error executing the rotation program.\n");
    }
}

void on_solveButton_clicked(GtkButton *button, gpointer user_data) {
    int result = system("./../../solver/solver ../../display/grid_00");

    // disable the rotate buttons
    gtk_widget_set_sensitive(GTK_WIDGET(rotateLeftButton), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(rotateRightButton), FALSE);
}

void on_gridButton_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *imageWidget = GTK_WIDGET(user_data); 

    printf("Grid button clicked\n");

    // disable the rotate buttons
    gtk_widget_set_sensitive(GTK_WIDGET(rotateLeftButton), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(rotateRightButton), FALSE);
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

void on_saveGridButton_clicked(GtkWidget *widget, gpointer data) {
    int sudokuGrid[9][9];

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            const char *text = gtk_entry_get_text(GTK_ENTRY(entry[i][j]));
            if (text[0] >= '1' && text[0] <= '9') {
                sudokuGrid[i][j] = text[0] - '0';  // Convert char to int
            } else {
                sudokuGrid[i][j] = 0;  // Empty cell
            }
        }
    }

    FILE *file = fopen("../../display/grid_00", "w");
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                fprintf(file, " ");
            }
            if (sudokuGrid[i][j] != 0) {
                fprintf(file, "%d", sudokuGrid[i][j]);
            } else {
                fprintf(file, ".");
            }
        }
        fprintf(file, "\n");
        if (i % 3 == 2 && i != 8) {
            fprintf(file, "\n");
        }
    }

    fclose(file);

    GtkWidget *window = gtk_widget_get_toplevel(widget);
    if (gtk_widget_is_toplevel(window)) {
        gtk_widget_destroy(window);
    }

    // Execute the display_solved file
    int result = system("./../../display/display_solved sudoku_image.jpg ../../display/grid_00");

    // Call load_sudoku_grid after your existing code
    load_sudoku_grid(sudoku_grid_filename, data);
}

void on_enterButton_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Enter Sudoku Grid");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            entry[i][j] = gtk_entry_new();
            gtk_entry_set_max_length(GTK_ENTRY(entry[i][j]), 1); 
            gtk_entry_set_width_chars(GTK_ENTRY(entry[i][j]), 7);  // Set width of text input field
            gtk_widget_set_size_request(entry[i][j], -1, 70);  // Set height of text input field
            gtk_grid_attach(GTK_GRID(grid), entry[i][j], j, i, 1, 1);
        }
    }

    GtkWidget *saveGridButton = gtk_button_new_with_label("Save");
    gtk_grid_attach(GTK_GRID(grid), saveGridButton, 0, 9, 9, 1);
    g_signal_connect(saveGridButton, "clicked", G_CALLBACK(on_saveGridButton_clicked), NULL);

    gtk_widget_show_all(window);
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

    GtkWidget *rotateButton = GTK_WIDGET(gtk_builder_get_object(builder, "rotateButton"));   
    GtkWidget *loadButton = GTK_WIDGET(gtk_builder_get_object(builder, "loadButton"));
    solveButton = GTK_WIDGET(gtk_builder_get_object(builder, "solveButton"));
    g_signal_connect(loadButton, "clicked", G_CALLBACK(on_loadButton_clicked), imageWidget);
    
    g_signal_connect(solveButton, "clicked", G_CALLBACK(on_solveButton_clicked), NULL);
    g_signal_connect(solveButton, "clicked", G_CALLBACK(load_image_solve), imageWidget);

    // Connectez le signal de fermeture de la fenêtre à la fonction de gestion
    g_signal_connect(window, "delete-event", 
    G_CALLBACK(on_window_delete_event), NULL);

    // Get the buttons from the builder
    rotateLeftButton = GTK_WIDGET(gtk_builder_get_object(builder, "rotateLeftButton"));
    rotateRightButton = GTK_WIDGET(gtk_builder_get_object(builder, "rotateRightButton"));

    // Connect the buttons to the respective functions
    g_signal_connect(rotateLeftButton, "clicked", G_CALLBACK(on_rotateLeftButton_clicked), NULL);
    g_signal_connect(rotateLeftButton, "clicked", G_CALLBACK(load_image_rotate), imageWidget);
    g_signal_connect(rotateRightButton, "clicked", G_CALLBACK(on_rotateRightButton_clicked), NULL);
    g_signal_connect(rotateRightButton, "clicked", G_CALLBACK(load_image_rotate), imageWidget);

    saveButton = GTK_WIDGET(gtk_builder_get_object(builder, "saveButton"));
    g_signal_connect(saveButton, "clicked", G_CALLBACK(unhide_file), NULL);

    gridButton = GTK_WIDGET(gtk_builder_get_object(builder, "gridButton"));
    g_signal_connect(gridButton, "clicked", G_CALLBACK(load_image_grid), imageWidget);
    g_signal_connect(gridButton, "clicked", G_CALLBACK(on_gridButton_clicked), NULL);

    GtkWidget *enterButton = GTK_WIDGET(gtk_builder_get_object(builder, "enterButton"));
    g_signal_connect(enterButton, "clicked", G_CALLBACK(on_enterButton_clicked), NULL);
   
    // Désactivez la redimension de la fenêtre
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    gtk_window_set_default_size(GTK_WINDOW(window), 1440, 960);

    gtk_widget_set_sensitive(GTK_WIDGET(rotateLeftButton), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(rotateRightButton), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(saveButton), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(solveButton), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(gridButton), FALSE);
    
    //gtk_window_is_maximized(GTK_WINDOW(window));

    gtk_widget_show_all(window); // Afficher tous les widgets de la fenêtre

    gtk_main();

    return 0;
}