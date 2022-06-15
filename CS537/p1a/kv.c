// Writen by Zhiwei Cao
// Project: P1a
// COMP SCI 537
// Professor: Remzi
// Basic idea to solve this project:
// used read and write into the file again and again to formate the data. 
// and use several tempperate array to store the value I need
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#define MAX 256

// The method is from website https://stackoverflow.com/questions/30133210/check-if-file-is-empty-or-not-in-c/30133326
int get_size(const char* file_name) // this funcion is use to check the size of the txt, check if the file is empty without any key and values
{
	FILE *file = fopen(file_name, "r");
	if(file == NULL)
		return 0;
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fclose(file);

	return size;
}
// Delete method is from website http://www.tutorialspanel.com/delete-a-specific-line-from-a-text-file-using-c/index.htm
void delete(int line){
	int count = 0;
			char ten;
			FILE *fp1, *fp2;
			fp1 = fopen("database.txt", "r");
			char str[MAX], temp_txt[] = "temp.txt";
			fp2 = fopen(temp_txt,"w");
			while(!feof(fp1))
			{
				strcpy(str,"\0");
				fgets(str,MAX,fp1);
				if (!feof(fp1))
				{
					count++;
					if (count != line)
					{
						fprintf(fp2,"%s",str);
					}
				}
			}
			fclose(fp1);
			fclose(fp2);
			remove("database.txt");
			rename(temp_txt,"database.txt");
			fp1 = fopen("database.txt","r");
			ten = fgetc(fp1);
			while(ten!= EOF)
			{
				ten = fgetc(fp1);
			}
			fclose(fp1);
}

int main(int argc, char const *argv[])
{
	// command-line args
	FILE *file = fopen("database.txt","a+"); // main file to write key and value into the file
	int i; // this i only for cound the argv 
	for (i = 1; i < argc; ++i)
	{
		char *token, *string, *to_free;
		to_free = string = strdup(argv[i]);
		assert(string != NULL);
		char array[3][200]; // set an array to store the instructions like p,g,a,c
		int i = 0; // use to check the bad command check if the instruction is in the right format
		while ((token = strsep(&string, ","))!= NULL){
			if (i >= 3)//to prevent the situdtaion like p,1,1,1
			{
				printf("bad command\n");
				exit(0);
			}
			strcpy(array[i],token);// seperate instruction by common and store into the temp array
				i++;
		}
		free(to_free);
		int size_of_char=0;
		int arr_count = 0; // use to count the count temp array which tstore the value of each key

		//***********************************************************************************************************************************************************
		if (strcmp("p",array[0]) == 0) // put instruction
		{
			if (i != 3) // if the length of the instruction is not three, print the bad command
			{
				printf("bad command\n");
				exit(0);
			}
			char *temp = malloc(sizeof(char) * 2000); // set a huge size for the array for test 13 to prevent the memory problem
			FILE *fi = fopen("database.txt","a+"); // append and read the txt file
			char *comm = ",";
			char *li = "\n";
			int del = 0; // the line that need to be deleted
			int line_count = 0; // cound the loop and get the line that have the same key value
			FILE *fp;
			fp = fopen("database.txt", "r"); // only use to read
			assert(fp != NULL);
			char *line = NULL;
			size_t linecap = 0;
			ssize_t linelen;
			// int check = 0; 
			// char tem_arr[2][20];
			char *tem_arr[2]; // init an array to store the key and value from the file
			for (int i = 0; i < 2; ++i)
			{
				tem_arr[i] = (char *)malloc(2000 * sizeof(char));
			}
				// my idea is to split each instruection and store each key into a temp array
				// then assign the temp array to compare if there are same key, then delete the line that has same key
				// and put the new key and value into the file
			while((linelen = getline(&line, &linecap, fp)) > 0){
				// here split each instruction
				char *to, *str, *tf;
				tf = str = strdup(line);
				assert(str != NULL);
				int i = 0;
				while ((to = strsep(&str, ","))!= NULL){
					strcpy(tem_arr[i],to); // store all spilted instrucion into ter_arr[] like (p,1,2) ter_arr[0]=1 ,ter_arr[2]=2 
					size_of_char++;
					i++;
				}
				strcpy(&temp[arr_count],tem_arr[0]); // and the store each key into temp array, only get the key of each put insturetion
				if(atoi(&temp[arr_count]) == atoi(array[1])){ // when meet the same key
					del = line_count+1; // remember the line that has the same key and ready for delete
					// check++;
				}
				arr_count++;
				line_count++;
				free(tf);
			}
			int test = atoi(array[1]); // cast key to int
			if (test == 0)// when the key is not integer print the bad command (situation like p,a,123)
			{
				printf("bad command\n");
				exit(0);
			}
			// write each key and value into file
			fprintf(fi,"%s",array[1]);
			fprintf(fi,"%s",comm);
			fprintf(fi,"%s",array[2]);
			fprintf(fi,"%s",li);
			fclose(fi);

			// delete the line if meet the line wihch has the same key
			if(del != 0){
				delete(del);
			}

			free(temp);
			fclose(fp);
			// free the temp array
			for (int j = 0; j < 2; ++j)
			{
				char *curr = tem_arr[j];
				free(curr);
			}
			
		}
		//***********************************************************************************************************************************************************
		else if (strcmp("g",array[0]) == 0)
		{
			if (i != 2) // prevent the situation like g or g,1,1
			{
				printf("bad command\n");
			}
			else{
				char *temp = malloc(sizeof(char) * 2000); // set a huge size for the array for test 13 to prevent the memory problem
				FILE *fp;
				fp = fopen("database.txt", "r"); // only for read
				assert(fp != NULL);
				char *line = NULL;
				size_t linecap = 0;
				ssize_t linelen;
				int check = 0; // use to check if meet the same key in the file
				// int cou = 0;
				while((linelen = getline(&line, &linecap, fp)) > 0){
					char *to, *str, *tf;
					tf = str = strdup(line);
					assert(str != NULL);
					char *tem_arr[2]; // to store the key and value from the file
					for (int i = 0; i < 2; ++i)
					{
						tem_arr[i] = (char *)malloc(2000 * sizeof(char));
					}
					int i = 0;
					while ((to = strsep(&str, ","))!= NULL){
						strcpy(tem_arr[i],to); // spilt by common and store into the array
						i++;
					}
					free(tf);
					strcpy(&temp[arr_count],tem_arr[0]); // only store key in the temp array
					if(atoi(&temp[arr_count]) == atoi(array[1])){
						printf("%s,%s", tem_arr[0],tem_arr[1]); // when meet the same key, print the line and stop seaching
						check++; // for further insturction, for not found situation
						break; // stop seaching
					}
					for (int j = 0; j < 2; ++j)
					{
						char *curr = tem_arr[j];
						free(curr);
					}
					// free(tem_arr);
					// free(temp);
					arr_count++;
					
				}

				if(get_size("database.txt") == 0) // if the database is empty, print not found
				{
					printf("%s not found\n", array[1]);
					// free(temp);
				}else if(check == 0){ // when didnt find the same key, print not found
					printf("%s not found\n", array[1]);
					// free(temp);
				}
				free(temp);
				fclose(fp);
			}
			
		}
		//***********************************************************************************************************************************************************
		else if (strcmp("d",array[0]) == 0)
		{
			// basiclly has the same idea like before find the line with the same keyand delete
			if (i != 2)
			{
				printf("bad command\n");
			}
			else{
			   // char temp[20][20];
			char *temp = malloc(sizeof(char) * 1000);
			int line_count = 0;
			int del;
			FILE *fp;
			fp = fopen("database.txt", "r");
			assert(fp != NULL);
			char *line = NULL;
			size_t linecap = 0;
			ssize_t linelen;
			while((linelen = getline(&line, &linecap, fp)) > 0){
				char *to, *str, *tf;
				tf = str = strdup(line);
				assert(str != NULL);
				char tem_arr[2][20];
				int i = 0;
				while ((to = strsep(&str, ","))!= NULL){
					strcpy(tem_arr[i],to);
					size_of_char++;
					i++;
				}
				strcpy(&temp[arr_count],tem_arr[0]);
				if(atoi(&temp[arr_count]) == atoi(array[1])){
					del = line_count+1;
					// printf("%d\n", del);
				}
				arr_count++;
				free(tf);
				line_count++;
			}

			delete(del); // call delete method

			free(temp);
			fclose(fp); 
			}
			
		}
		//***********************************************************************************************************************************************************
		else if (strcmp("c",array[0]) == 0)
		{
			fopen("database.txt","w"); // rewrite the file
		}
		//***********************************************************************************************************************************************************
		else if (strcmp("a",array[0]) == 0)
		{
			// just print each line of the file
			FILE *fp;
			fp = fopen("database.txt", "r");
			assert(fp != NULL);
			char *line = NULL;
			size_t linecap = 0;
			ssize_t linelen;
			while((linelen = getline(&line, &linecap, fp)) > 0){
				printf("%s", line);
			}
			fclose(fp);
		}
		//***********************************************************************************************************************************************************
		else
		{
			printf("bad command\n");
			exit(0);
		}
	}
	fclose(file);
	return 0;
}
