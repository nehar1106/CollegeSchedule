#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "catalog.h"
#include "input.h"




typedef int (*compfn)(void const *va, void const *vb);

int compare(const void *aptr, const void *bptr);


int compare(const void *aptr, const void *bptr) 
{
 	printf ("In schedule - compare\n");


   Course *elem1 = (Course *)aptr;
   Course *elem2 = (Course *)bptr;
   
   if ( strcmp(elem1->crs_dept, elem2->crs_dept) < 0) {
      return -1;
   }

   else if (strcmp(elem1->crs_dept, elem2->crs_dept) > 0) {
      return 1;
   }
   
   else if ( strcmp(elem1->crs_num, elem2->crs_num) < 0) { 
      return -1;
   }

   else if (strcmp(elem1->crs_num, elem2->crs_num) > 0) {
      return 1;
   }

   else { 
      return 0;
   }

}


void print_schd_items (schd * sptr) {


	for (int j = 1 ; j <= sptr->count; j++) {
	
//		printf ("++--> schd add is %d - %p %d %s - %d - %d\n", j, sptr->s_cItm, sptr->count, sptr->s_cItm->i_cItm->crs_dept, sptr->s_cItm->active , sptr->s_cItm->i_cItm->crs_num);
//		printf ("+++----> In Print %p %p %s %d %s %s %d\n",sptr->s_cItm,sptr->s_cItm->i_cItm,sptr->s_cItm->i_cItm->crs_dept,sptr->s_cItm->i_cItm->crs_num,sptr->s_cItm->i_cItm->crs_sttm, sptr->s_cItm->i_cItm->crs_dow , sptr->s_cItm->active);
	
		sptr->s_cItm++;	
	}

}

int check_4_existing_schd (schd * sptr, char const *crs_dept, int crs_num, char const *save_dow,char *save_sttm) {

	
	for (int j = 1 ; j <= sptr->count; j++) {
	
		
//		printf ("+++----> check 4 exists %p %p %s %d %s %s\n",sptr->s_cItm,sptr->s_cItm->i_cItm,sptr->s_cItm->i_cItm->crs_dept,sptr->s_cItm->i_cItm->crs_num,sptr->s_cItm->i_cItm->crs_sttm, sptr->s_cItm->i_cItm->crs_dow );
//		printf ("+++----> check 4a exists %s %d %s %s\n",crs_dept, crs_num, save_dow,save_sttm );
		
		if ((strcmp(sptr->s_cItm->i_cItm->crs_dept,crs_dept) == 0) && sptr->s_cItm->i_cItm->crs_num == crs_num &&  sptr->s_cItm->active == 1) {
		
//			printf ("In first check %s %s \n",save_dow,save_sttm);
			return 1;

		}
		
		else if ((strcmp(sptr->s_cItm->i_cItm->crs_dow,save_dow) == 0) && (strcmp(sptr->s_cItm->i_cItm->crs_sttm,save_sttm) == 0) && sptr->s_cItm->active == 1) {
//			printf ("In 2nd check %s %s %s %d %d\n",save_dow,save_sttm, sptr->s_cItm->i_cItm->crs_dept, sptr->s_cItm->i_cItm->crs_num,sptr->s_cItm->active);

			return 1;
		}

		sptr->s_cItm++;

	}
	return 0;

}

bool test( struct Course const *course, char const *str1, char const *str2 ) {


	if (str1[0] == '\0' && str2[0] == '\0' ) {

		return 0;
	}
	else if (str1[0] != '\0' && (strcmp(str1,course->crs_dept) == 0 )) {

	return 0;
	}
	else if (str1[0] != '\0' && str2[0] != '\0'   && (strcmp(str1,course->crs_dow) == 0 ) && (strcmp(str2,course->crs_sttm) == 0 )) {

	return 0;
	}
	else if ((strcmp(str1," ") == 0) && (strcmp(str2," ") == 0)) {

	return 0;

	} else {

	return 1;
	};

}



void print_course_info(const Course course) {
    printf("Department: %s, Number: %d, DOW: %s, Time: %s, Name: %s\n",
           course.crs_dept, course.crs_num, course.crs_dow,
           course.crs_sttm, course.crs_nm);
}


int main (int argc, char** argv) {


   char ip_file[50];

   char ip_cmd[20];
   
   char cmd[20];
   char parm1[20];
   char parm2[20];
   char parm3[20];
   char parm4[20];
   char id_fnd = " ";
   char ch;
   char *str;
   
   char liststr1[20];
   char liststr2[20];
	
   int i2 = 0;
   int i3 = 0;
   int i4 = 0;
   
   schd * ord_itm;
   schd * schdptr;
   int exists_flg = 0;
   Course *save_c_ptr;
   Course *save_o_ptr;

	char crs_dept[10];
	int crs_num;
	char crs_dow[5];
	char crs_sttm[10];
	char crs_nm[50];
	char save_dow[5];
	char save_sttm[10];
   char ordr_existing;
   int crs_fnd1 = 0;
   int crs_fnd2 = 0;


   if (argc <= 1) {
      fprintf( stderr, "usage: schedule <course-file>*\n");  exit (1);
    }
  
	
   schdptr = (schd *) malloc( (sizeof( schd)));
   
   schdptr->count = 0;
   
   if (schdptr->capacity == 0) {
      schdptr->capacity = 20;
      schdptr->s_cItm = (schdItem *) malloc(schdptr->capacity * (sizeof( schdItem)));
      save_o_ptr = schdptr->s_cItm;

   };

   
    Catalog *cptr = makeCatalog();


    for (int i = 1; i < argc; i++) {    
      strcpy(ip_file, argv[i]);
      
      FILE *i_fp = fopen( ip_file, "r" );
      if ( !i_fp ) {      
         fprintf( stderr, "Can't open file: %s\n", ip_file ); 
         exit(1); 
      }
      readCourses ( i_fp, cptr);

      fclose (i_fp);

   }
   
   char s_ctgy[10];
   strcpy(s_ctgy, " ");
   char *srch_ctgy = s_ctgy;
   
      

schdptr->count = 0;

 while (fscanf( stdin, "%c", &ch ) == 1) {

      if (ch == EOF) {  break;}
      ungetc( ch, stdin);
      
      str = readLine ( stdin);   
      if (strcmp(str,"qu111") != 0) {printf ("cmd> %s\n", str);}
      
      strcpy(cmd, "                  ");
      strcpy(parm1, "                  ");
      strcpy(parm2, "                  ");
      strcpy(parm3, "                  ");
      strcpy(parm4, "                  ");
      
      int parms_cnt = 0;


      
      parms_cnt = sscanf (str, "%s%s%s%s", cmd, parm1, parm2, parm3);
 

	  if (parms_cnt < 1 || (strcmp(cmd, "list") != 0 || strcmp(cmd, "add") != 0 || strcmp(cmd, "drop") != 0 || strcmp(cmd, "quit") != 0)) {

      if ((strcmp(cmd,"list") != 0) && (strcmp(cmd,"add") != 0) && (strcmp(cmd,"drop") != 0) && (strcmp(cmd,"quit") != 0)) {
         printf ("Invalid command\n\n");continue; 
      }

      else if ((strcmp(cmd,"list") == 0) && 
      ((strcmp(parm1,"courses") != 0) && (strcmp(parm1,"names") != 0) && (strcmp(parm1,"department") != 0) && (strcmp(parm1,"schedule") != 0) && (strcmp(parm1,"timeslot") != 0))
      ) {
         printf ("Invalid command\n\n");continue; 
      };
         
      if ((strcmp(cmd,"list") == 0) && (strcmp(parm1,"department") == 0) 
      && strcmp(parm2, "                  ") == 0) 
      {printf ("Invalid command\n\n");continue;};

      sscanf (str, "%s%s", cmd, parm1);
   
      if ((strcmp(cmd,"list") == 0) && (strcmp(parm1,"courses") == 0)) {
//         listCourses( cptr, compare, test, srch_ctgy);
		 liststr1[0] = '\0';
		 liststr2[0] = '\0';

		 sortCourses(cptr, sortByDept );
         listCourses( cptr, test, liststr1,liststr2);

      }
      else if ((strcmp(cmd,"list") == 0) && (strcmp(parm1,"names") == 0)) {
		 liststr1[0] = '\0';
		 liststr2[0] = '\0';
		 sortCourses(cptr, sortByCrsNm );
         listCourses( cptr, test, liststr1,liststr2);
		 sortCourses(cptr, sortByDept );

      }  
      else if ((strcmp(cmd,"list") == 0) && (strcmp(parm1,"schedule") == 0)) {
		 liststr1[0] = '\0';
		 liststr2[0] = '\0';

		 schdptr->s_cItm = save_o_ptr;
//		 sortCourses(schdptr->s_cItm->i_cItm, sortSchedule );
		 
		 listSchd(schdptr, test, liststr1,liststr2);

      } 
      else if ((strcmp(cmd,"list") == 0) && (strcmp(parm1,"department") == 0)) {


         sscanf (str, "%s%s%3[A-Z]", cmd, parm1, parm2);
         
         if (strlen(parm2) > 15) {printf ("Invalid command15\n");continue;}
         else if (strcmp(parm2,"                  ") == 0) {printf ("Invalid command\n");continue;};

		 strcpy(liststr1,parm2);
		 liststr2[0] = '\0';
		 
		 sortCourses(cptr, sortByDept );

         listCourses( cptr, test, liststr1,liststr2);

      }
      else if ((strcmp(cmd,"list") == 0) && (strcmp(parm1,"timeslot") == 0)) {
      
         sscanf (str, "%s%s%2[A-Z]%s", cmd, parm1, parm2, parm3);

         if (strlen(parm2) > 15) {printf ("Invalid command15\n");continue;}
         else if (parm2 == '\0') {printf ("Invalid command1\n");continue;}
         
         else if (parm3 == '\0') {printf ("Invalid command2\n");continue;};

		 strcpy(liststr1,parm2);
		 strcpy(liststr2,parm3);
		 sortCourses(cptr, sortByDept );
         listCourses( cptr, test, liststr1,liststr2);

      }
      else if ((strcmp(cmd,"quit") == 0)) {
      

         free (cptr->cItm);
         free (cptr);
         exit (0);
      }
      else if ((strcmp(cmd,"add") == 0) || (strcmp(cmd,"drop") == 0)) {
      
		schdptr->s_cItm = save_o_ptr;
		print_schd_items (schdptr);
//		printf ("\n");
		sscanf (str, "%s%s%3d", cmd, crs_dept, &crs_num);


		save_c_ptr = cptr->cItm;
		
		crs_fnd1 = 0;

		for (int j = 0; j < (cptr->count); j++) {
				
			if (schdptr->count >= 20) {printf ("--> 4. Too many courses added - %d\n",schdptr->count);};
	
//			printf ("--> 5. %s %s %d\n", cmd, crs_dept, crs_num);
	
			if ((strcmp(cptr->cItm->crs_dept, crs_dept) == 0) && cptr->cItm->crs_num == crs_num ) {
			
				crs_fnd1 = 1;
			
				strcpy(save_dow,cptr->cItm->crs_dow );
				strcpy(save_sttm,cptr->cItm->crs_sttm );

				if (strcmp(cmd,"add") == 0) {
				
//			printf ("--> 5b. %s %s %d\n", cmd, crs_dept, crs_num);


					exists_flg = 0;
					schdptr->s_cItm = save_o_ptr;
					exists_flg = check_4_existing_schd(schdptr, crs_dept,crs_num,save_dow,save_sttm);
					
//			printf ("--> 5c. %s %s %d %d\n", cmd, crs_dept, crs_num, exists_flg);

					if (exists_flg == 0) {
					
						schdptr->s_cItm = save_o_ptr;
						schdptr->count++;					
						
						for (int i1 = 0; i1 < schdptr->count - 1; i1++) {
						
//							printf ("Forwarding Address1 for schdptr->cItm is %p %p %s %d %d %s\n", schdptr->s_cItm, save_o_ptr, schdptr->s_cItm->i_cItm->crs_dept, schdptr->s_cItm->i_cItm->crs_num, schdptr->count, cptr->cItm);
							schdptr->s_cItm++;
							
						}

						schdptr->s_cItm->i_cItm = cptr->cItm;	
						schdptr->s_cItm->active = 1;
						
//						printf ("Adding to schedule schdptr->cItm is %p %p %s %d %d %s %d\n", schdptr->s_cItm, schdptr->s_cItm->i_cItm, schdptr->s_cItm->i_cItm->crs_dept, schdptr->s_cItm->i_cItm->crs_num, schdptr->count, cptr->cItm, schdptr->s_cItm->active);


					}
					else {printf ("Invalid command\n");}
					printf("\n");
	
				}
				else if (strcmp(cmd,"drop") == 0) {

					schdptr->s_cItm = save_o_ptr;

					crs_fnd2 = 0;
					for (int i1 = 1; i1 <= schdptr->count ; i1++) {


						if ((strcmp(schdptr->s_cItm->i_cItm->crs_dept, crs_dept) == 0)   && schdptr->s_cItm->i_cItm->crs_num == crs_num) {

							schdptr->s_cItm->active = 0;
							crs_fnd2 = 1;
//						printf ("Drop from  schedule schdptr->cItm is %p %p %s %d %d %s %d\n", schdptr->s_cItm, schdptr->s_cItm->i_cItm, schdptr->s_cItm->i_cItm->crs_dept, schdptr->s_cItm->i_cItm->crs_num, schdptr->count, cptr->cItm, schdptr->s_cItm->active);

							break;					
						}
						
						schdptr->s_cItm++;
	
					}
					
					if (crs_fnd2 == 0) {printf ("Invalid command\n");};
					printf("\n");

					schdptr->s_cItm = save_o_ptr;
				
				}
					
			}

		cptr->cItm++;
		} 
		if (crs_fnd1 == 0) {printf ("Invalid command\n\n");};
		
		cptr->cItm = save_c_ptr;


  }
  
	schdptr->s_cItm = save_o_ptr;

	print_schd_items(schdptr);

   }

   
}
printf ("cmd> ");


}