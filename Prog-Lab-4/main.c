#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "framemaster.h"

void getMaxLength(FrameList *frames, unsigned *max_tag, unsigned *max_info) {
    (*max_tag) = 0;
    (*max_info) = 0;

    for (int i = 0; i < frames->size; i++) {

        (*max_tag) = (strlen(frames->values[i].tag) > (*max_tag)) ?
                     strlen(frames->values[i].tag) : (*max_tag);

        (*max_info) = (strlen(frames->values[i].info) > (*max_info)) ?
                      strlen(frames->values[i].info) : (*max_info);
    }
}

void showAll(FrameList *frames) {
    unsigned max_tag, max_info;

    // alignment frame searching
    getMaxLength(frames, &max_tag, &max_info);

    // title printing
    int title_idx = (max_tag + max_info + 1) / 2;

    for (int i = 0; i < title_idx - 1; i++) {
        printf("=");
    }

    printf(" FRAMES ");

    for (int i = title_idx + 7; i < max_tag + max_info + 7; i++) {
        printf("=");
    }
    printf("\n| ");

    int fst_sp_counter = (max_tag - 3) / 2;

    for (int i = 0; i < fst_sp_counter; i++) {
        printf(" ");
    }

    printf("TAG");

    for (int i = fst_sp_counter + 3; i < max_tag; i++) {
        printf(" ");
    }

    printf(" | ");

    fst_sp_counter = (max_info - 4) / 2;

    for (int i = 0; i < fst_sp_counter; i++) {
        printf(" ");
    }

    printf("INFO");

    for (int i = fst_sp_counter + 4; i < max_info; i++) {
        printf(" ");
    }
    printf(" |\n");

    // frames printing
    for (int i = 0; i < frames->size; i++) {
        if (frames->values[i].tag[0] != 0 && frames->values[i].info[0] != 0) {

            unsigned cur_length = strlen(frames->values[i].tag);
            fst_sp_counter = (max_tag - cur_length) / 2;

            printf("| ");

            for (int j = 0; j < fst_sp_counter; j++) {
                printf(" ");
            }

            printf("%s", frames->values[i].tag);

            for (int j = fst_sp_counter + cur_length; j < max_tag; j++) {
                printf(" ");
            }

            printf(" | ");

            cur_length = strlen(frames->values[i].info);
            fst_sp_counter = (max_info - cur_length) / 2;

            for (int j = 0; j < fst_sp_counter; j++) {
                printf(" ");
            }

            printf("%s", frames->values[i].info);

            for (int j = fst_sp_counter + cur_length; j < max_info; j++) {
                printf(" ");
            }

            printf(" |\n");
        }
    }
    for (int i = 0; i < max_tag + max_info + 7; i++) {
        printf("=");
    }
    printf("\n");
}

char *getInfo(FrameList *frames, char *tag) {
    for (int i = 0; i < frames->size; i++) {
        if (!strcmp(frames->values[i].tag, tag)) {
            return frames->values[i].info;
        }
    }
    printf("Frame not found\n");
    return NULL;
}

void setInfo(header *header_info, FrameList *frames, char *tag, char *value) {
    for (int i = 0; i < frames->size; i++) {
        if (!strcmp(frames->values[i].tag, tag)) {
            (*header_info).size += strlen(value);
            (*header_info).size -= strlen(frames->values[i].info);
            strcpy(frames->values[i].info, value);
            return;
        }
    }
    printf("Frame not found\n");
}

void createFile(char *out_file, header header_info, FrameList *frames) {
    unsigned byte_num = (header_info.version >= 3) ? 4 : 3;
    FILE *out = fopen(out_file, "r+b");

    if (out == NULL) {
        printf("File writing error\n");
        return;
    }

    unsigned power = 16;
    char cur_char;

    // signature printing
    fprintf(out, "%s", header_info.signature);

    // version printing
    fprintf(out, "%c%c", header_info.version, 0);

    // flags printing
    char byte_for_flags = 0;

    byte_for_flags += power * header_info.flags.unsynchronisation;
    power *= 2;
    byte_for_flags += power * header_info.flags.extended_header;
    power *= 2;
    byte_for_flags += power * header_info.flags.exp_indicator;
    power *= 2;
    byte_for_flags += power * header_info.flags.footer_present;

    fputc(byte_for_flags, out);

    // header size printing
    power = INITIAL7;

    for (int i = 0; i < 4; i++) {
        cur_char = header_info.size / power;
        header_info.size -= cur_char * power;

        fputc(cur_char, out);

        power /= 128;
    }

    // frames printing
    for (int i = 0; i < frames->size; i++) {
        for (int j = 0; j < byte_num; j++) {
            fputc(frames->values[i].tag[j], out);
        }

        unsigned frame_size = strlen(frames->values[i].info) + 1;

        power = INITIAL7;

        for (int j = 0; j < 4; j++) {
            cur_char = frame_size / power;
            frame_size -= cur_char * power;

            fputc(cur_char, out);

            power /= 128;
        }

        fputc(frames->values[i].flag[0], out);
        fputc(frames->values[i].flag[1], out);

        fputc(frames->values[i].encoding, out);


        frame_size = strlen(frames->values[i].info);

        // COMM conversion to printable view
        if (!strcmp(frames->values[i].tag, "COMM")) {
            frames->values[i].info[3] = 0;
        }

        for (int j = 0; j < frame_size; j++) {
            fputc(frames->values[i].info[j], out);
        }

    }

    fclose(out);
}

int main(int argc, char **argv) {
    char *filename = argv[argc - 1];

    FrameList *frames = declare_list();

    header header_info;

    FILE *in = fopen(filename, "r");

    if (in == NULL) {
        printf("File reading error\n");
    }

    getBasicData(in, &header_info);

    while (ftell(in) < header_info.size) {
        frames = getNextFrame(in, &header_info, frames);
    }

    fclose(in);

    short isChanged = 0;

    for (int i = 1; i < argc - 1; i++) {
        char *command = argv[i];
        if (!strcmp(command, "--show")) {
            showAll(frames);
        } else {
            if (strlen(command) >= 6) {
                command[5] = 0;
            }
            if (!strcmp(command, "--set")) {
                command[5] = '=';
                char *next_command = argv[++i];

                char *prop_name = strchr(command, '=') + 1;
                char *prop_value = strrchr(next_command, '=') + 1;

                setInfo(&header_info, frames, prop_name, prop_value);
                isChanged = 1;
            } else if (!strcmp(command, "--get")) {
                command[5] = '=';
                char *prop_name = strchr(command, '=') + 1;

                printf("%s\n", getInfo(frames, prop_name));
            } else {
                if (strlen(command) >= 6) {
                    command[5] = '=';
                }
                printf("Command '%s' is unacceptable\n", command);
            }
        }
    }

    if (isChanged) {
        printf("Do you want to save changes? (y/n)\n");
        if (getchar() == 'y') {
            createFile(filename, header_info, frames);
        }
    }

    free(frames);
    frames = NULL;
    return 0;
}
