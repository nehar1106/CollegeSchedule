/**
@file menu.h
@author Neha Ramesh (nramesh3)
This programs helps with reading and listing the menu items
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*--
typedef struct MenuItem {
char ID[10];
char name[50];
char category[50];
int cost;

} MnuItm;

typedef struct Menu {

int capacity;
int count;
MnuItm *mItm;

} Menu;

---*/

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


/*--

typedef struct Schedule {

int capacity;
int count;
int active[10];
Course *cItm;

} schd;

typedef struct OrderItem {
MnuItm *o_mItm;
int qty;

} OrdItm;

typedef struct Order {

int capacity;
int count;
OrdItm *oItm;

} Ordr;
--*/

typedef struct schdItem {
Course *i_cItm;
int active;

} schdItem;


typedef struct Schedule {

int capacity;
int count;
schdItem *s_cItm;

} schd;


Catalog *makeCatalog();

void freeCatalog (Catalog *catalog);

void readCourses(char const *filename, Catalog *catalog);
//void listMenuItems( Menu *menu, int (*compare)( void const *va, void const *vb ), bool (*test)( struct MenuItem const *item, char const *str), char const *str );

void listCourses( Catalog *catalog, bool (*test)( Course const *course, char const *str1, char const *str2 ), char const *str1, char const *str2 );

//void sortCourses( Catalog *catalog, int (* compare) (void const *va, void const *vb ));
int sortByDept(const void *va, const void *vb) ;
int sortByCrsId(const void *va, const void *vb);
int sortByCrsNm(const void *va, const void *vb);
void sortCourses(Catalog *catalog, int (*compare)(const void *va, const void *vb));
void listSchd ( schd *schdptr, bool (*test)( Course const *course, char const *str1, char const *str2 ), char const *str1, char const *str2 );
int sortSchedule(const void *va, const void *vb);

