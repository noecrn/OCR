#include <gtk/gtk.h>
#include "../../display/display_solved.h"

char *rotate_filename = ".rotate_image.png";
char *solve_filename = "solved_grid.png";
char *grid_filename = "grid_detection.png";
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

void load_image_solve(const char *filename, gpointer user_data) {
    GtkWidget *imageWidget = GTK_WIDGET(user_data);

    // Load the image into a GdkPixbuf object
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(solve_filename, NULL);

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
        printf("Filename: %s\n", solve_filename);
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
    // Use the system() function to execute the rotation program
    char solve_command[256];
    //sprintf(solve_command, "../solve/solve .rotate_image.png solved_grid.png");
    int status = system(solve_command);

    if (status != 0) {
        // Handle errors from executing the rotation program
        g_print("Error executing the rotation program.\n");
    }
}

void on_gridButton_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *imageWidget = GTK_WIDGET(user_data); 

    printf("Grid button clicked\n");

    // Create a confirmation dialog
    GtkWidget *dialog_grid = gtk_dialog_new_with_buttons("Grid confirmation",
                                                         NULL,
                                                         GTK_DIALOG_MODAL,
                                                         "Yes",
                                                         GTK_RESPONSE_YES,
                                                         "Try Again",
                                                         GTK_RESPONSE_NO,
                                                         NULL); // NULL sentinel

    // Set the default size of the dialog
    gtk_window_set_default_size(GTK_WINDOW(dialog_grid), 200, 100);

    // Set the border width (margin) of the dialog
    gtk_container_set_border_width(GTK_CONTAINER(dialog_grid), 10);

    // Create a label and add it to the dialog's content area
    GtkWidget *label = gtk_label_new("Is the grid correctly detected?");
    gtk_widget_set_size_request(label, 180, 100);  // Set the size of the label
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog_grid));
    gtk_container_add(GTK_CONTAINER(content_area), label);
    gtk_widget_show(label);

    // Create a box for the buttons
    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(button_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(button_box, GTK_ALIGN_CENTER);

    // Add the box to the dialog's content area
    gtk_container_add(GTK_CONTAINER(content_area), button_box);
    gtk_widget_show(button_box);

    gtk_dialog_set_default_response(GTK_DIALOG(dialog_grid), GTK_RESPONSE_YES);

    gint response = gtk_dialog_run(GTK_DIALOG(dialog_grid));

    if (response == GTK_RESPONSE_NO) {
        printf("Grid is not correctly detected\n");
        // Use the system() function to execute the grid program
        char grid_command[256];
        //sprintf(grid_command, "../grid/grid .rotate_image.png solved_grid.png");
        int status = system(grid_command);

        if (status != 0) {
            // Handle errors from executing the grid program
            g_print("Error executing the grid program.\n");
        }

        on_gridButton_clicked(button, imageWidget);
    }
    else{
        printf("Grid is correctly detected\n");
    }

    gtk_widget_destroy(dialog_grid);
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

void on_saveButton_clicked(GtkWidget *widget, gpointer data) {
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

    FILE *file = fopen("grid_00", "w");
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

    //call the display function from the display_solved.c file
    display_solved(sudokuGrid);

    // Close the window
    GtkWidget *window = gtk_widget_get_toplevel(widget);
    if (gtk_widget_is_toplevel(window)) {
        gtk_widget_destroy(window);
    }
}

void on_enterButton_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Enter Sudoku Grid");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            entry[i][j] = gtk_entry_new();
            gtk_entry_set_max_length(GTK_ENTRY(entry[i][j]), 1); 
            gtk_entry_set_width_chars(GTK_ENTRY(entry[i][j]), 2);  // Set width of text input field
            gtk_grid_attach(GTK_GRID(grid), entry[i][j], j, i, 1, 1);
        }
    }

    GtkWidget *saveButton = gtk_button_new_with_label("Save");
    gtk_grid_attach(GTK_GRID(grid), saveButton, 0, 9, 9, 1);
    g_signal_connect(saveButton, "clicked", G_CALLBACK(on_saveButton_clicked), NULL);

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

    gtk_window_set_default_size(GTK_WINDOW(window), 900, 600);

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