#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "framemaster.h"

void getMaxLength(frame *frame_list, unsigned length, unsigned *max_header, unsigned *max_info) {
    (*max_header) = 0;
    (*max_info) = 0;

    for (int i = 0; i < length; i++) {
        (*max_header) = (strlen(frame_list[i].header) > (*max_header)) ? strlen(frame_list[i].header) : (*max_header);
        (*max_info) = (strlen(frame_list[i].info) > (*max_info)) ? strlen(frame_list[i].info) : (*max_info);
    }
}

void showAll(frame *frame_list, unsigned length) {
    printf("Frames:\n");

    unsigned max_header, max_info;

    getMaxLength(frame_list, length, &max_header, &max_info);

    unsigned fst_sp_counter = (max_header - 3) / 2;

    for (int i = 0; i < max_header + max_info + 7; i++) {
        printf("=");
    }
    printf("\n| ");

    for (int i = 0; i < fst_sp_counter; i++) {
        printf(" ");
    }

    printf("TAG");

    for (int i = fst_sp_counter + 3; i < max_header; i++) {
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

    for (int i = 0; i < length; i++) {
        if (frame_list[i].header[0] != 0 && frame_list[i].info[0] != 0) {

            unsigned cur_length = strlen(frame_list[i].header);
            unsigned fst_sp_counter = (max_header - cur_length) / 2;

            printf("| ");

            for (int j = 0; j < fst_sp_counter; j++) {
                printf(" ");
            }

            printf("%s", frame_list[i].header);

            for (int j = fst_sp_counter + cur_length; j < max_header; j++) {
                printf(" ");
            }

            printf(" | ");

            cur_length = strlen(frame_list[i].info);
            fst_sp_counter = (max_info - cur_length) / 2;

            for (int j = 0; j < fst_sp_counter; j++) {
                printf(" ");
            }

            printf("%s", frame_list[i].info);

            for (int j = fst_sp_counter + cur_length; j < max_info; j++) {
                printf(" ");
            }

            printf(" |\n");
        }
    }
    for (int i = 0; i < max_header + max_info + 7; i++) {
        printf("=");
    }
    printf("\n");
}

char *getInfo(frame *frame_list, unsigned length, char *header) {
    for (int i = 0; i < length; i++) {
        if (!strcmp(frame_list[i].header, header)) {
            return frame_list[i].info;
        }
    }
    printf("Frame not found\n");
    return NULL;
}

void setInfo(tag *tag_info, frame *frame_list, unsigned length, char *header, char *value) {
    for (int i = 0; i < length; i++) {
        if (!strcmp(frame_list[i].header, header)) {
            (*tag_info).size += strlen(value);
            (*tag_info).size -= strlen(frame_list[i].info);
            strcpy(frame_list[i].info, value);
            return;
        }
    }
    printf("Frame not found\n");
}

void fprint10(FILE *out) {
    fseek(out, -1, SEEK_CUR);
    char prev_char = fgetc(out);
    fseek(out, -1, SEEK_CUR);
    fputc(10, out);
    fseek(out, -2, SEEK_CUR);
    fputc(prev_char, out);
    fseek(out, 1, SEEK_CUR);
}

void createFile(char *out_file, tag tag_info, frame *frame_list, unsigned length) {
    unsigned byte_num = (tag_info.version >= 3) ? 4 : 3;
    FILE *out = fopen(out_file, "r+");

    if (out == NULL) {
        printf("File writing error\n");
        return;
    }

    unsigned power = 16;
    char cur_char;

    fprintf(out, "%s", tag_info.signature);
    fprintf(out, "%c%c", tag_info.version, 0);

    char byte_for_flags = 0;

    byte_for_flags += power * tag_info.flags.unsynchronisation;
    power *= 2;
    byte_for_flags += power * tag_info.flags.extended_header;
    power *= 2;
    byte_for_flags += power * tag_info.flags.exp_indicator;
    power *= 2;
    byte_for_flags += power * tag_info.flags.footer_present;

    fputc(byte_for_flags, out);

    power = INITIAL7;

    for (int i = 0; i < 4; i++) {
        cur_char = tag_info.size / power;
        tag_info.size -= cur_char * power;

        fputc(cur_char, out);

        power /= 128;
    }

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < byte_num; j++) {
            fputc(frame_list[i].header[j], out);
        }

        unsigned frame_size = strlen(frame_list[i].info) + 1;

        power = INITIAL7;

        for (int j = 0; j < 4; j++) {
            cur_char = frame_size / power;
            frame_size -= cur_char * power;
            if (cur_char == 10) {
                fprint10(out);
            } else {
                fputc(cur_char, out);
            }
            power /= 128;
        }

        fputc(frame_list[i].flag[0], out);
        fputc(frame_list[i].flag[1], out);

        fputc(frame_list[i].encoding, out);


        frame_size = strlen(frame_list[i].info);

        if (!strcmp(frame_list[i].header, "COMM")) {
            frame_list[i].info[3] = 0;
        }

        for (int j = 0; j < frame_size; j++) {
            fputc(frame_list[i].info[j], out);
        }

    }

    fclose(out);
}

int main(int argc, char **argv) {
    char *filename = argv[argc - 1];

    frame *frame_list = NULL;
    unsigned last_frame = 0;

    tag tag_info;

    FILE *in = fopen(filename, "r");

    if (in == NULL) {
        printf("File reading error\n");
    }

    getBasicData(in, &tag_info);

    while (ftell(in) < tag_info.size) {
        frame_list = getNextFrame(in, &tag_info, frame_list, &last_frame);
    }

    fclose(in);

    short isChanged = 0;

    for (int i = 1; i < argc - 1; i++) {
        char *command = argv[i];
        if (!strcmp(command, "--show")) {
            showAll(frame_list, last_frame + 1);
        } else {
            if (strlen(command) >= 6) {
                command[5] = 0;
            }
            if (!strcmp(command, "--set")) {
                command[5] = '=';
                char *next_command = argv[++i];

                char *prop_name = strchr(command, '=') + 1;
                char *prop_value = strrchr(next_command, '=') + 1;

                setInfo(&tag_info, frame_list, last_frame + 1, prop_name, prop_value);
                isChanged = 1;
            } else if (!strcmp(command, "--get")) {
                command[5] = '=';
                char *prop_name = strchr(command, '=') + 1;

                printf("%s\n", getInfo(frame_list, last_frame + 1, prop_name));
            } else {
                if (strlen(command) >= 6) {
                    command[5] = '=';
                }
                printf("Command '%s' is unacceptable\n", command);
            }
        }
    }

    if (isChanged) {
        createFile(filename, tag_info, frame_list, last_frame + 1);
    }

    free(frame_list);
    frame_list = NULL;
    return 0;
}
