#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0

char * stringsearch(const char * haystack, const char * needle){
	return strstr(haystack, needle);
}
FILE * openfile(char * name, char * extension, char * modes){
	char path[strlen(name) + strlen(extension)];
	strcpy(path, name);
	strcat(path, extension);
	return fopen(path, modes);
}
unsigned long int flen(FILE * f){
	fseek(f, 0, SEEK_END);
	unsigned long int len = ftell(f);
	rewind(f);
	return len;
}

int main(int argc, char ** argv){

	char navbar_placeholder[] = "%navbar%";
	char markdown_placeholder[] = "%markdown%";

	char navbar_element[] = "<a href=\"%link%\" class=\"%class%\">%name%</a>";
	char active[] = "active";
	char inactive[] = "inactive";
	char link_placeholder[] = "%link%";
	char class_placeholder[] = "%class%";
	char name_placeholder[] = "%name%";

	unsigned long int num_links = argc - 1;
	unsigned long int name_arg_offset = 1;

	for(int i = name_arg_offset; i < argc; i++){

		FILE * markdown = openfile(argv[i], ".markdown", "r");
		FILE * template = openfile(argv[i], ".template", "r");

		if(markdown == NULL || template == NULL){
			continue;
		}

		unsigned long int mark_len = flen(markdown);
		unsigned long int temp_len = flen(template);

		char markdown_str[mark_len];
		char template_str[temp_len];

		fread(markdown_str, mark_len, 1, markdown);
		fread(template_str, temp_len, 1, template);

		markdown_str[mark_len] = 0;
		template_str[temp_len] = 0;

		char * pagename = argv[i];

		FILE * output = openfile(argv[i], ".html", "w");

		char * navbar_location = stringsearch(template_str, navbar_placeholder);
		char * markdown_location = stringsearch(template_str, markdown_placeholder);

		for(int i = 0; i < strlen(template_str); i++){

			if((template_str + i) == navbar_location){

				for(int i = 0; i < num_links; i++){

					char * current_page = argv[i + name_arg_offset];

					char * link_location = stringsearch(navbar_element, link_placeholder);
					char * class_location = stringsearch(navbar_element, class_placeholder);
					char * name_location = stringsearch(navbar_element, name_placeholder);

					for(int i = 0; i < strlen(navbar_element); i++){
						if((navbar_element + i) == link_location){
							fprintf(output, "%s.html", current_page);
							i += strlen(link_placeholder);
						}
						if((navbar_element + i) == class_location){
							if(strcmp(pagename, current_page) == 0){
								fprintf(output, "%s", active);
							}
							else{
								fprintf(output, "%s", inactive);
							}
							i += strlen(class_placeholder);
						}
						if((navbar_element + i) == name_location){
							fprintf(output, "%s", current_page);
							i += strlen(name_placeholder);
						}
						fprintf(output, "%c", navbar_element[i]);
					}

				}

				i += strlen(navbar_placeholder);
			}
			if((template_str + i) == markdown_location){

				fprintf(output, "%s", markdown_str);

				i += strlen(markdown_placeholder);
			}

			fprintf(output, "%c", template_str[i]);
		}

		fclose(markdown);
		fclose(template);
		fclose(output);
	}
}