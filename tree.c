#include <stdio.h>
#include <string.h>
#include <dirent.h>

void print_spaces(int count) {
    for (int i = 0; i < count; i++) {
        printf("    ");
    }
}

void make_tree(char *path, int level) {
    DIR *directory = opendir(path);

    if (directory == NULL) {
        return;
    }

    struct dirent *item;
    while ((item = readdir(directory)) != NULL) {
        char *filename = item->d_name;

        if (strcmp(filename, ".") == 0) {
            continue;
        }
        if (strcmp(filename, "..") == 0) {
            continue;
        }

        print_spaces(level);
        printf("|__ %s\n", filename);

        if (item->d_type == DT_DIR) {
            char next_path[1024];

            strcpy(next_path, path);
            strcat(next_path, "/");
            strcat(next_path, filename);

            make_tree(next_path, level + 1);
        }
    }
    closedir(directory);
}

int main(int argc, char *argv[]) {
    char *target = ".";

    if (argc > 1) {
        target = argv[1];
    }

    printf("%s\n", target);
    make_tree(target, 1);

    return 0;
}
