#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student
{
	int roll;
	char name[20];
	float marks;
	struct student *next;
} ST;
ST*hptr=0;

void stud_add(ST**);
void stud_show(ST*);
void stud_del(void);
void roll_delete(ST**,int);
void name_delete(ST**,char *);
void stud_mod(void);
void roll_mod(ST**, int );
void name_mod(ST**,char *);
void percent_mod(ST**,int );
void stud_sort(void);
void name_sort(ST** );
void percent_sort(ST** );
void stud_delete(ST**);
void stud_rev(ST**);
void stud_save(ST* , const char*);


int main()
{


	printf("        .---------------------------.\n");
	printf("        |****** STUDENT RECORD *****|\n");
	printf("        .---------------------------.\n");
	printf("        |                           |\n");
	printf("        | a/A : add new record      |\n");
	printf("        | d/D : delete a record     |\n");
	printf("        | s/S : show the list       |\n");
	printf("        | m/M : modify the record   |\n");
	printf("        | v/V : save                |\n");
	printf("        | e/E : exit                |\n");
	printf("        | t/T : sort the list       |\n");
	printf("        | l/L : delete all record   |\n");
	printf("        | r/R : reverse the list    |\n");
	printf("        .___________________________.\n");
	printf("\n");

	char op;
	while(1)
	{
		printf("Enter your choice: ");
		scanf(" %c", &op);

		if(op=='a' || op=='A')
		{
			char po;
			do {
				stud_add(&hptr);
				printf("do you want to add another record(y/n): ");
				scanf(" %c",&po);
			} while( po == 'y' || po == 'Y' );
		}
		if(op=='d' || op=='D')
			stud_del();

		if(op=='s' || op=='S')
			stud_show(hptr);

		if(op=='m' || op=='M')
			stud_mod();

        if(op=='v' || op=='V')
            stud_save(hptr, "students_data.txt");

		if(op=='e' || op=='E')
			return 0;

		if(op=='t' || op=='T')
			stud_sort();

        if(op=='l' || op=='L')
            stud_delete(&hptr);

        if(op=='r' || op=='R')
            stud_rev(&hptr);

	}


}
void stud_add(ST** ptr)
{

	ST* temp = (ST*)malloc(sizeof(ST));
	if (temp == NULL) {  // Check if malloc succeeded
		printf("Memory allocation failed\n");
		return;
	}

	int highest_roll = 0;
	ST* current = *ptr;

	while (current != NULL) {
		if (current->roll > highest_roll) {
			highest_roll = current->roll;
		}
		current = current->next;
	}

	temp->roll = highest_roll + 1;

	printf("Enter the name and marks: ");
	scanf("%s %f", temp->name, &temp->marks);

	if(*ptr==0)
	{
		temp->next = *ptr;
		*ptr = temp;
	}
	else
	{
		ST*last=*ptr;
		while(last->next!=0)
			last=last->next;

		temp->next=last->next;
		last->next=temp;
	}


}

void stud_show(ST*ptr)
{
	while (ptr != NULL) {
		printf("%d %s %f\n", ptr->roll, ptr->name, ptr->marks);
		ptr = ptr->next;
	}
}

void stud_del(void)
{
	printf("        .---------------------------.\n");
	printf("        |                           |\n");
	printf("        | R/r : Enter roll to del   |\n");
	printf("        | N/n : Enter name to del   |\n");
	printf("        .___________________________.\n");
	printf("\n");

	char del;
	printf("Enter your choice: ");
	scanf(" %c",&del);

	if( del== 'r' || del== 'R' )
	{
		int roll;
		printf("Enter roll number to delete :");
		scanf("%d",&roll);
		roll_delete(&hptr,roll);
	}
	if( del== 'n' || del== 'N' )
	{
		char a[50];
		printf("Enter the name to delete :");
		scanf("%s",a);
		name_delete( &hptr,a);
	}



}

void roll_delete(ST** ptr,int roll)
{
	ST* temp = *ptr;
	ST* prev = NULL;

	// If the head node itself holds the roll number to be deleted
	if (temp != NULL && temp->roll == roll) {
		*ptr = temp->next; // Change head
		free(temp); // Free old head
		return;
	}

	// Search for the roll number to be deleted
	while (temp != NULL && temp->roll != roll) {
		prev = temp;
		temp = temp->next;
	}

	// If the roll number was not found
	if (temp == NULL) {
		printf("Roll number %d not found in the list.\n", roll);
		return;
	}

	// Unlink the node from the linked list
	prev->next = temp->next;
	free(temp); // Free memory
}
void name_delete(ST** ptr,char *name)
{
	int cnt=0;
	ST*current=*ptr;
	ST*previous=NULL;
	printf("Nodes found with this name...\n");
	while(current!=NULL)
	{
		if(strcmp(name,current->name)==0)
		{
			cnt++;
			printf("%d %s %f\n",current->roll,current->name,current->marks);
		}
		current=current->next;

	}
	if(cnt==0)
		printf("No node found with this name\n");
	else if(cnt==1)
	{
		current=*ptr;
		previous=NULL;
		while(current!=NULL)
		{
			if(strcmp(name,current->name)==0)
			{
				if (previous == NULL)
				{
					*ptr = current->next;  // Move head to the next node
				}
				else
				{
					previous->next = current->next;  // Skip the current node
				}

				free(current);
				printf("Node deleted successfully.\n");
				return; // Exit after deleting the node
			}

			previous = current;
			current = current->next;
		}




	}
	else if(cnt>1)
	{
		int ab;
		printf("More than one record found with this name..\n");
		printf("Enter the roll number to delete:\n");
		scanf("%d",&ab);
		roll_delete(&hptr,ab);
	}

}
void stud_mod(void)
{
	char ba;
	printf("        .---------------------------.\n");
	printf("        |                           |\n");
	printf("        | R/r :Roll number based    |\n");
	printf("        | N/n :Name based           |\n");
	printf("        | P/p :Percentage based     |\n");
	printf("        .___________________________.\n");
	printf("\n");

	printf("Enter the choice: ");
	scanf(" %c",&ba);

	if( ba== 'r' || ba== 'R' )
	{
		int roll_modify;
		printf("Enter roll number to modify :");
		scanf("%d",&roll_modify);
		roll_mod(&hptr,roll_modify);
	}
	if( ba== 'n' || ba== 'N' )
	{
		char b[50];
		printf("Enter the name to modify :");
		scanf("%s",b);
		name_mod( &hptr,b);
	}

	if( ba== 'P' || ba== 'p' )
	{
		float c;
		printf("Enter the roll number whose percent has to modify :");
		scanf("%f",&c);
		percent_mod( &hptr,c);
	}


}

void roll_mod(ST**ptr, int roll_modify)
{
	int d;
	ST*current = *ptr;
	while(current!=NULL)
	{
		if(current->roll == roll_modify)
		{
			printf("Enter the roll to insert\n");
			scanf("%d",&d);

			current->roll=d;

		}
		current=current->next;
	}
}


void name_mod(ST** ptr,char *name)
{
	int count=0;
	char d[20];
	ST*current=*ptr;
	printf("Nodes found with this name...\n");
	while(current!=NULL)
	{
		if(strcmp(name,current->name)==0)
		{
			count++;
			printf("%d %s %f\n",current->roll,current->name,current->marks);
		}
		current=current->next;

	}
	if(count==0)
		printf("No node found with this name\n");
	else if(count==1)
	{
		current=*ptr;
		while(current!=NULL)
		{
			if(strcmp(name,current->name)==0)
			{
				printf("Enter the name to insert:\n");
				scanf("%s",d);

				strcpy(current->name,d);
			}

			current = current->next;
		}




	}
	else if(count>1)
	{
		current=*ptr;
		int f;
		char g[20];
		printf("More than one record found with this name..\n");
		printf("Enter the roll number to modify:\n");
		scanf("%d",&f);
		while(current!=NULL)
		{
			if(current->roll == f)
			{
				printf("Enter the name insert:\n");
				scanf("%s",g);
				strcpy(current->name,g);
			}

			current=current->next;

		}



	}

}

void percent_mod(ST** ptr,int roll)
{
	float h;
	ST*current = *ptr;
	while(current!=NULL)
	{
		if(current->roll == roll)
		{
			printf("%d %s %f\n",current->roll,current->name,current->marks);
			printf("Enter percent to insert: ");
			scanf("%f",&h);

			current->marks=h;

		}
		current=current->next;
	}
}

void stud_sort(void)
{
	char ca;
	printf("        .---------------------------.\n");
	printf("        |                           |\n");
	printf("        | N/n :Name based           |\n");
	printf("        | P/p :Percentage based     |\n");
	printf("        .___________________________.\n");
	printf("\n");

	printf("Enter the choice: ");
	scanf(" %c",&ca);

	if( ca== 'n' || ca== 'N' )
	{
		name_sort( &hptr);
	}

	if( ca== 'P' || ca== 'p' )
	{
		percent_sort( &hptr);
	}
}

void name_sort(ST** ptr) 
{
    if (*ptr == NULL || (*ptr)->next == NULL) {
        printf("List is already sorted or empty.\n");
        return;
    }

    ST *current, *prev, *temp;
    int swapped;

    do {
        swapped = 0;
        current = *ptr;
        prev = NULL;

        while (current->next != NULL) {
            if (strcmp(current->name, current->next->name) > 0) {
                // Swap nodes by adjusting pointers
                temp = current->next;
                current->next = temp->next;
                temp->next = current;

                if (prev == NULL) {
                    *ptr = temp; // Update head pointer
                } else {
                    prev->next = temp;
                }

                swapped = 1;
            } else {
                current = current->next;
            }
            prev = current;
        }
    } while (swapped);

    printf("List sorted by name successfully.\n");
}

void percent_sort(ST** ptr) 
{
    if (*ptr == NULL || (*ptr)->next == NULL) {
        printf("List is already sorted or empty.\n");
        return;
    }

    int swapped;
    ST *current, *prev, *temp;

    do {
        swapped = 0;
        current = *ptr;
        prev = NULL;

        while (current->next != NULL) {
            if (current->marks < current->next->marks) { // Sort in descending order
                // Swap nodes by adjusting pointers
                temp = current->next;
                current->next = temp->next;
                temp->next = current;

                if (prev == NULL) {
                    *ptr = temp; // Update the head pointer
                } else {
                    prev->next = temp;
                }

                swapped = 1;

                // After swapping, `prev` should not move because `current` has shifted down
                prev = temp;
            } else {
                // Move `prev` to the current node before moving `current`
                prev = current;
                current = current->next;
            }
        }
    } while (swapped);

    printf("List sorted by percentage successfully.\n");
}

void stud_delete(ST** ptr)
{
    ST* current = *ptr;
    ST* temp;

    while (current != NULL) {
        temp = current;         // Store the current node
        current = current->next; // Move to the next node
        free(temp);             // Free the current node
    }

    *ptr = NULL; // Set the head pointer to NULL
    printf("All nodes are deleted successfully.\n");
}
void stud_rev(ST**ptr)
{
    ST* prev = NULL;       // Pointer to track the previous node
    ST* current = *ptr;    // Pointer to track the current node
    ST* next = NULL;       // Pointer to track the next node

    while (current != NULL) {
        next = current->next; // Store the next node
        current->next = prev; // Reverse the current node's pointer
        prev = current;       // Move the previous pointer forward
        current = next;       // Move the current pointer forward
    }

    *ptr = prev; // Update the head pointer to the new head
    printf("List reversed successfully.\n");

}
void stud_save(ST*ptr, const char* filename)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Unable to open file for writing.\n");
        return;
    }

    ST* current = ptr;
    while (current != NULL) {
        fprintf(file, "%d %s %.2f\n", current->roll, current->name, current->marks);
        current = current->next;
    }

    fclose(file);
    printf("Data saved successfully to file: %s\n", filename); 
}
