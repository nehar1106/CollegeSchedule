#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


typedef struct Course {
char crs_dept[10];
int crs_num;
char crs_dow[5];
char crs_sttm[10];
char crs_nm[50];

} Course;


typedef struct Catalog {

int capacity;
int count;
Course *cItm;

} Catalog;


typedef struct schdItem {
Course *i_cItm;
int active;

} schdItem;


typedef struct Schedule {

int capacity;
int count;
schdItem *s_cItm;

} schd;

/*--
typedef struct Schedule {

int capacity;
int count;
int active;
Course *cItm;

} schd;
--*/

typedef int (*compfn)(void const *va, void const *vb);

Catalog *makeCatalog() {

//	printf ("In makeCatalog\n");

   Catalog catalog1;

   Catalog *catalogptr = &catalog1;

   catalogptr->count = 0;
   catalogptr->capacity = 5;

   catalogptr = (Catalog *) malloc( (sizeof( Catalog)));


   catalogptr->count = 0;

   return catalogptr;

}


void trim_leading_spaces(char *str) {
    char *first_non_space = str;

    // Find the first non-space character
    while (*first_non_space && isspace(*first_non_space)) {
        first_non_space++;
    }

    if (first_non_space != str) {
        // Shift characters to the left
        size_t len = strlen(first_non_space) + 1; // +1 for the null-terminator
        memmove(str, first_non_space, len);
    }
}


void freeCatalog( Catalog *catalog ) {

   free (catalog->cItm);
   free (catalog);

}

int sortByDept(const void *va, const void *vb) {

    const Course *a = (const Course *) va;
    const Course *b = (const Course *) vb;

    // Compare fields of the courses (example: course number)
    
	if (strcmp(a->crs_dept, b->crs_dept) < 0) {
        return -1;
    } else if (strcmp(a->crs_dept, b->crs_dept) > 0) {
        return 1;
    } else if (a->crs_num < b->crs_num) {
        return -1;
    } else if (a->crs_num > b->crs_num) {
        return 1;
    } else {
        return 0;
    }
    
}

int sortByCrsId(const void *va, const void *vb) {

    const Course *a = (const Course *) va;
    const Course *b = (const Course *) vb;

    // Compare fields of the courses (example: course number)
    
    if (a->crs_num < b->crs_num) {
        return 1;
    } else if (a->crs_num > b->crs_num) {
        return -1;
    } else {
        return 0;
    }
}

int sortByCrsNm(const void *va, const void *vb) {

    const Course *a = (const Course *) va;
    const Course *b = (const Course *) vb;

    // Compare fields of the courses (example: course number)
    
    if (strcmp(a->crs_nm, b->crs_nm) < 0) {
        return -1;
    } else if (strcmp(a->crs_nm, b->crs_nm) > 0)  {
        return 1;
    } else if (strcmp(a->crs_dept, b->crs_dept) < 0) {
        return -1;
    } else if (strcmp(a->crs_dept, b->crs_dept) > 0) {
        return 1;
    } else if (a->crs_num < b->crs_num) {
        return -1;
    } else if (a->crs_num > b->crs_num) {
        return 1;
    } else {
        return 0;
    }
    
}
int sortSchedule(const void *va, const void *vb) {

    const schdItem *a = (const schdItem *) va;
    const schdItem *b = (const schdItem *) vb;

    // Compare fields of the courses (example: course number)
//    printf ("---> 6. sortSchedule -- %p %s %d %s %s %s - %s %d %s %s %s \n", a, a->i_cItm->crs_dept, a->i_cItm->crs_num, a->i_cItm->crs_sttm, a->i_cItm->crs_nm,a->i_cItm->crs_dow, b->i_cItm->crs_dept, b->i_cItm->crs_num, b->i_cItm->crs_sttm, b->i_cItm->crs_nm,b->i_cItm->crs_dow );
	int st1;
	int st2;
	
	if (strcmp(a->i_cItm->crs_sttm,"8:30" ) == 0) 
		{st1 = 1;}
	else if (strcmp(a->i_cItm->crs_sttm,"10:00" ) == 0) 
		{st1 = 2;}

	else if (strcmp(a->i_cItm->crs_sttm,"11:30" ) == 0) 
		{st1 = 3;}

	else if (strcmp(a->i_cItm->crs_sttm,"1:00" ) == 0) 
		{st1 = 4;}

	else if (strcmp(a->i_cItm->crs_sttm,"2:30" ) == 0) 
		{st1 = 5;}

	else if (strcmp(a->i_cItm->crs_sttm,"4:00" ) == 0) 
		{st1 = 6;};
		
	if (strcmp(b->i_cItm->crs_sttm,"8:30" ) == 0) 
		{st2 = 1;}
	else if (strcmp(b->i_cItm->crs_sttm,"10:00" ) == 0) 
		{st2 = 2;}

	else if (strcmp(b->i_cItm->crs_sttm,"11:30" ) == 0) 
		{st2 = 3;}

	else if (strcmp(b->i_cItm->crs_sttm,"1:00" ) == 0) 
		{st2 = 4;}

	else if (strcmp(b->i_cItm->crs_sttm,"2:30" ) == 0) 
		{st2 = 5;}

	else if (strcmp(b->i_cItm->crs_sttm,"4:00" ) == 0) 
		{st2 = 6;};

    if (strcmp(a->i_cItm->crs_dow, b->i_cItm->crs_dow) < 0) {
        return -1;
    } else if (strcmp(a->i_cItm->crs_dow, b->i_cItm->crs_dow) > 0)  {
        return 1;
    } else if (st1 < st2)  {
        return -1;
    } else if (st1 > st2) {
        return 1;
    } else {
        return 0;
    };
		
/*--		
    if (strcmp(a->i_cItm->crs_dow, b->i_cItm->crs_dow) < 0) {
        return -1;
    } else if (strcmp(a->i_cItm->crs_dow, b->i_cItm->crs_dow) > 0)  {
        return 1;
    } else if (strcmp(a->i_cItm->crs_sttm, b->i_cItm->crs_sttm) < 0) {
        return -1;
    } else if (strcmp(a->i_cItm->crs_sttm, b->i_cItm->crs_sttm) > 0) {
        return 1;
    } else {
        return 0;
    }
--*/
    
}


void sortCourses(Catalog *catalog, int (*compare)(const void *va, const void *vb)) {

    int num_courses = catalog->count; // Assuming the catalog has a field num_courses
    Course *courses = catalog->cItm; // Assuming the catalog has a field courses

    qsort(courses, num_courses, sizeof(Course), compare);
    
}

// sortCourses(&catalog, compareCourses);


void readCourses ( char const *filename, Catalog *catalog) {

// printf ("reaCatalogFile pointers  %p %p %p\n",  catalog, catalog->cItm,filename);

	/*--
	int cnt = 0;

	char id[4];
	char name[20];
	char ctgy[15];
	int cost;
	--*/
	char ch = ' ';
	int row_cnt = 0;

	char input[100];
	char crs_dept[10];
	int crs_num;
	char crs_dow[5];
	char crs_sttm[10];
	char crs_nm[50];
	char rest[30];


   Course *saveptr;
   Course *restartptr;
   
// printf ("File name is %s", filename);

// printf ("--> In Readcatalog -start - catalog count and item %d %d \n", catalog->count, catalog->capacity  );


   if (catalog->capacity == 0) {
      catalog->capacity = 5;
      catalog->cItm = (struct Course *) malloc(catalog->capacity * (sizeof( Course)));
   };
   

         
   saveptr = catalog->cItm;
   
   for (int k = 1; k <= catalog->count ;k++) {
   
      catalog->cItm++;

   }

   while (fscanf( filename, "%c", &ch ) == 1) {

      if (ch == EOF) {
         printf("Program done \n"); break;
      }

      fseek(filename, -1, SEEK_CUR);

	  fgets(input, sizeof(input), filename);
	  
//	  validate_input(input);

/*--  Starting Input course validation --*/
	  
    int items_read = sscanf(input, "%3[A-Z]%3d%2s%5s%[^\n]", crs_dept, &crs_num, crs_dow, crs_sttm, crs_nm);

    if (items_read != 5) {
        printf("Invalid input.\n");
         exit(1);
    }
	trim_leading_spaces(crs_nm);

//    if (!(strlen(crs_dept) == 3 && isupper(crs_dept[0]) && isupper(crs_dept[1]) && isupper(crs_dept[2]))) {
    if (!(strlen(crs_dept) == 3 && (crs_dept[0] >= 'A' && crs_dept[0] <= 'Z') && (crs_dept[1] >= 'A' && crs_dept[1] <= 'Z') && (crs_dept[2] >= 'A' && crs_dept[2] <= 'Z'))) {

        printf("Invalid department.\n");
         exit(1);
    }

    if (crs_num < 000 || crs_num > 999) {
        printf("Invalid course number. %d\n", crs_num);
         exit(1);
    }

    if (strcmp(crs_dow, "MW") != 0 && strcmp(crs_dow, "TH") != 0) {
        printf("Invalid crs_dow.\n");
         exit(1);
    }

    const char *valid_crs_sttms[] = {"8:30", "10:00", "11:30", "1:00", "2:30", "4:00"};
    int valid_crs_sttm = 0;
    for (int i = 0; i < sizeof(valid_crs_sttms) / sizeof(valid_crs_sttms[0]); i++) {
        if (strcmp(crs_sttm, valid_crs_sttms[i]) == 0) {
            valid_crs_sttm = 1;
            break;
        }
    }

    if (!valid_crs_sttm) {
        printf("Invalid crs_sttm.\n");
         exit(1);
    }
//    printf ("---> File input %p %s %d %s %s %s \n", filename, crs_dept, crs_num, crs_dow,crs_sttm, crs_nm);
    

      catalog->count++;
//	printf ("B4Forwarding - Catalog Item - catalog_count - %d %d \n",catalog->count,catalog->capacity) ;
      if (catalog->count > catalog->capacity) {
         catalog->cItm = saveptr;
   
         for (int k = 1; k < catalog->count  ;k++) {
 //       	printf ("Forwarding0 - Catalog Item - Array loaded -- %d %p %s %s %s %s %d %d \n", k, catalog->cItm, catalog->cItm->crs_dept,    catalog->cItm->crs_dow, catalog->cItm->crs_nm , catalog->cItm->crs_sttm,catalog->cItm->crs_num,k );
           
            catalog->cItm++;
         
         }

         catalog->capacity = catalog->capacity * 2;

         catalog->cItm = saveptr;
// 	printf ("Inside realloc - Catalog Item - catalog_count - %d %d \n",catalog->count,catalog->capacity) ;

         catalog->cItm = (struct Course *) realloc(catalog->cItm, catalog->capacity * (sizeof( Course)));
         
         saveptr = catalog->cItm;
         
         for (int k = 1; k < catalog->count  ;k++) {
//        	printf ("Forwarding - Catalog Item - Array loaded -- %d %p %s %s %s %s %d %d \n", k, catalog->cItm, catalog->cItm->crs_dept,    catalog->cItm->crs_dow, catalog->cItm->crs_nm , catalog->cItm->crs_sttm,catalog->cItm->crs_num,k );
           
            catalog->cItm++;
         
         }
      }
      strcpy(catalog->cItm->crs_dept, crs_dept);
      catalog->cItm->crs_num = crs_num;
      strcpy(catalog->cItm->crs_dow, crs_dow);
      strcpy(catalog->cItm->crs_sttm, crs_sttm);
      strcpy(catalog->cItm->crs_nm, crs_nm);
//      printf ("\n++++----> Added to Array - Catalog Item -- %p %s %s %s %s %d \n\n", catalog->cItm, catalog->cItm->crs_dept,    catalog->cItm->crs_dow, catalog->cItm->crs_nm , catalog->cItm->crs_sttm,catalog->cItm->crs_num );

      catalog->cItm++;
         
      row_cnt++;

   };
   

   catalog->cItm = saveptr;
    

 
     for (int j = 1; j<= (catalog->count); j++) {
//       printf ("Catalog Item - Array loaded -- %d %p %s %s %s %s %d %d \n", j,catalog->cItm, catalog->cItm->crs_dept,    catalog->cItm->crs_dow, catalog->cItm->crs_nm , catalog->cItm->crs_sttm,catalog->cItm->crs_num,j );
      catalog->cItm++; 
     }
 
     catalog->cItm = saveptr;


}

void listCourses( Catalog *catalog, bool (*test)( Course const *course, char const *str1, char const *str2 ), char const *str1, char const *str2 )

{
// 	printf ("In listCourses - %s - %s - %s %p\n", str1, str2, catalog, catalog->cItm->crs_dept  );


   int rtn = 0;
   int rtn_cnt = 0;

   Course *saveptr;
   saveptr = catalog->cItm;

   struct Course * item = item;
   int i;

   if (strcmp(str1, " ") == 0) {
   
     for (int j = 1; j<= (catalog->count); j++) {
//       printf (">>>> %d %s %s %s %s %d %d \n", j, catalog->cItm->crs_dept,    catalog->cItm->crs_dow, catalog->cItm->crs_nm , catalog->cItm->crs_sttm,catalog->cItm->crs_num,j );
      catalog->cItm++; 
     }
 
      catalog->cItm = saveptr;

   } else {

	    printf ("%-7s %-30s %-8s\n","Course", "Name", "Timeslot");
       for (i = 1; i <= catalog->count; i++)
       {
    

         rtn = test(catalog->cItm,str1,str2);

         if (rtn == 0) {
            rtn_cnt++;
            printf ("%-3s %d %-30s %-2s %5s\n",catalog->cItm->crs_dept, catalog->cItm->crs_num, catalog->cItm->crs_nm ,   catalog->cItm->crs_dow, catalog->cItm->crs_sttm);


         }
         catalog->cItm++;

       };
       printf("\n");

       catalog->cItm = saveptr;

   };


}

void listSchd ( schd *schdptr, bool (*test)( Course const *course, char const *str1, char const *str2 ), char const *str1, char const *str2 )

{
	int rtn = 0;
	int rtn_cnt = 0;

	int i;

    int num_courses = schdptr->count;  
    schdItem *courses = schdptr->s_cItm;  

    qsort(courses, num_courses, sizeof(schdItem), sortSchedule);

	printf ("%-7s %-30s %-8s\n","Course", "Name", "Timeslot");

	for (i = 1; i <= schdptr->count; i++)
	{

//		 rtn = test(schdptr->s_cItm->i_cItm,str1,str2);
//		printf ("B4 schd list - %d %-3s %d %-30s %-2s %5s\n",num_courses,schdptr->s_cItm->i_cItm->crs_dept, schdptr->s_cItm->i_cItm->crs_num, schdptr->s_cItm->i_cItm->crs_nm ,   schdptr->s_cItm->i_cItm->crs_dow, schdptr->s_cItm->i_cItm->crs_sttm);
		rtn = 0;
		 if (rtn == 0) {
			rtn_cnt++;
			if (schdptr->s_cItm->active == 1) {
			printf ("%-3s %d %-30s %-2s %5s\n",schdptr->s_cItm->i_cItm->crs_dept, schdptr->s_cItm->i_cItm->crs_num, schdptr->s_cItm->i_cItm->crs_nm ,   schdptr->s_cItm->i_cItm->crs_dow, schdptr->s_cItm->i_cItm->crs_sttm);
			}
		 }

		 schdptr->s_cItm++;

	};
	printf("\n");



}