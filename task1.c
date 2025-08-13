#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char text[100];

    // Check if filename is given
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open file in append mode (creates if it doesn't exist)
    file = fopen(argv[1], "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Keep taking input until "-1" is entered
    while (1) {
        printf("Enter text (or -1 to stop): ");
        fgets(text, sizeof(text), stdin);

        // Remove newline character
        text[strcspn(text, "\n")] = '\0';

        // Stop if user enters -1
        if (strcmp(text, "-1") == 0) {
            break;
        }

        fprintf(file, "%s\n", text); // Write to file
    }

    fclose(file);
    printf("Data saved to %s\n", argv[1]);
    return 0;
}
