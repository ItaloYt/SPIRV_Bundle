#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if(argc == 1) {
        (void) fputs("error: no input file\n", stderr);

        exit(1);
    }

    unsigned output_index = 0;

    for(unsigned index = 1; index < argc; ++index) {
        if(argv[index][0] == '-' && argv[index][1] == 'o') {
            output_index = index + 1;

            break;
        }
    }

    if(output_index == 0 || output_index >= argc) {
        (void) fputs("error: no output file specified. Use './bundle <input files> -o <output file>'", stderr);

        exit(1);
    }   

    FILE *output = fopen(argv[output_index], "w");

    if(!output) {
        (void) fprintf(stderr, "error: couldn't open/create output file '%s' - %s\n", argv[output_index], strerror(errno));

        exit(1);
    }

    FILE *input = 0x0;
    unsigned length = 0;
    unsigned name_length = 0;

    for(unsigned file_index = 1; file_index < argc; ++file_index) {
        if(file_index == output_index - 1 || file_index == output_index)
            continue;

        input = fopen(argv[file_index], "r");

        if(!input) {
            (void) fprintf(stderr, "error: couldn't open file '%s' - %s\n'", argv[file_index], strerror(errno));

            continue;
        }

        (void) fseek(input, 0, SEEK_END);
        length = ftell(input);
        (void) fseek(input, 0, SEEK_SET);

        char buffer[length];
        (void) fread(buffer, 1, length, input);

        name_length = strlen(argv[file_index]);

        for(unsigned char_index = 0; char_index < name_length; ++char_index) {
            if(argv[file_index][char_index] == '/' || argv[file_index][char_index] == '.') argv[file_index][char_index] = '_';
        }

        //"0x12345678, "

        char content[length * 3 + 1];

        for(unsigned char_index = 0; char_index < length; char_index += 4) {
            (void) sprintf(content + char_index * 3, "0x%08x, ", *(unsigned *) (buffer + char_index));
        }

        const unsigned write_length = snprintf(0x0, 0, "const unsigned %s[] = { %s };\nconst unsigned %s_length = %u;\n", argv[file_index], content, argv[file_index], length) + 1;
        char write_buffer[write_length];

        (void) snprintf(write_buffer, write_length, "const unsigned %s[] = { %s };\nconst unsigned %s_length = %u;\n", argv[file_index], content, argv[file_index], length);

        (void) fwrite(write_buffer, 1, write_length - 1, output);

        (void) fclose(input);
    }

    (void) fclose(output);
}
