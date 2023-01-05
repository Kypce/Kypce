#include <stdio.h>
#include <string.h>
#include <sqlca.h>
#include <stdlib.h>
#include <sqlda.h>
#include <sqlcpr.h>

#define UNAME_LEN      20
#define PWD_LEN        11

/*
 * Use the precompiler typedef'ing capability to create
 * null-terminated strings for the authentication host
 * variables. (This isn't really necessary--plain char *'s
 * would work as well. This is just for illustration.)
 */
typedef char asciiz[PWD_LEN];

EXEC SQL TYPE asciiz IS CHARZ(PWD_LEN) REFERENCE;
asciiz     username;
asciiz     password;

struct query_1 {
    asciiz      date;
    asciiz      intType;
    asciiz      comments;
};

struct query_2 {
    asciiz      contId;
    asciiz      date;
    asciiz      intType;
    asciiz      comments;
};

struct query_3 {
    asciiz      contId;
    asciiz      fname;
    asciiz      lname;
    asciiz      gender;
    asciiz      jobtitle;
    asciiz      team;
    asciiz      homeAdd;
    asciiz      mailAdd;
    asciiz      comments;
};

struct query_4 {
    int         count;
};

struct query_5 {
    asciiz      contId;
    asciiz      fname;
    asciiz      lname;
    asciiz      jobtitle;
    asciiz      officeNum;
    asciiz      email;
};

struct query_6 {
    asciiz      manId;
    asciiz  fname;
    asciiz  lname;
};

struct query_7 {
    asciiz      compName;
    int         compSize;
};

struct query_8 {
    asciiz      contId;
    asciiz      fname;
    asciiz      lname;
};

struct query_9 {
    int         callAmount;
    int         emailAmount;
    int         mailAmount;
};

struct query_10 {
    asciiz      contId;
    asciiz      fname;
    asciiz      lname;
};


void sql_error(msg)
    char *msg;
{
    char err_msg[512];
    size_t buf_len, msg_len;

    EXEC SQL WHENEVER SQLERROR CONTINUE;

    printf("\n%s\n", msg);

/* Call sqlglm() to get the complete text of the
 * error message.
 */
    buf_len = sizeof (err_msg);
    sqlglm(err_msg, &buf_len, &msg_len);
    printf("%.*s\n", msg_len, err_msg);

    EXEC SQL ROLLBACK RELEASE;
    exit(EXIT_FAILURE);
}

void main() {
    struct query_1 *q1_rec_ptr;
    struct query_2 *q2_rec_ptr;
    struct query_3 *q3_rec_ptr;
    struct query_4 *q4_rec_ptr;
    struct query_5 *q5_rec_ptr;
    struct query_6 *q6_rec_ptr;
    struct query_7 *q7_rec_ptr;
    struct query_8 *q8_rec_ptr;
    struct query_9 *q9_rec_ptr;
    struct query_10 *q10_rec_ptr;

/* Allocate memory for emp_info struct. */
    if ((q1_rec_ptr =
        (struct query_1 *) malloc(sizeof(struct query_1))) == 0) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
    }
    if ((q2_rec_ptr =
        (struct query_2 *) malloc(sizeof(struct query_2))) == 0) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
    }
    if ((q3_rec_ptr =
        (struct query_3 *) malloc(sizeof(struct query_3))) == 0) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
    }
    if ((q4_rec_ptr =
        (struct query_4 *) malloc(sizeof(struct query_4))) == 0) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
    }
    if ((q5_rec_ptr =
        (struct query_5 *) malloc(sizeof(struct query_5))) == 0) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
    }
    if ((q6_rec_ptr =
        (struct query_6 *) malloc(sizeof(struct query_6))) == 0) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
    }
    if ((q7_rec_ptr =
        (struct query_7 *) malloc(sizeof(struct query_7))) == 0) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
    }
    if ((q8_rec_ptr =
        (struct query_8 *) malloc(sizeof(struct query_8))) == 0) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
    }
    if ((q9_rec_ptr =
        (struct query_9 *) malloc(sizeof(struct query_9))) == 0) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
    }
    if ((q10_rec_ptr =
        (struct query_10 *) malloc(sizeof(struct query_10))) == 0) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
    }


/* Connect to ORACLE. */
    strcpy(username, "mxc2097");
    strcpy(password, "~Ece8031");

    EXEC SQL WHENEVER SQLERROR DO sql_error("ORACLE error--");

    EXEC SQL CONNECT :username IDENTIFIED BY :password;
    printf("\nConnected to ORACLE as user: %s\n", username);

/* Declare the cursor. All static SQL explicit cursors
 * contain SELECT commands. 'salespeople' is a SQL identifier,
 * not a (C) host variable.
 */

    for(;;) {
            printf("Please type the leading number to indicate your choice . . .\n");
            printf("1: List all the interactions events with a selected contact\n");
            printf("2: List all the interaction events made during a selected time period\n");
            printf("3: List the information for all contacts uner selected company\n");
            printf("4: List the total number of phone calls made during a selected timer period\n");
            printf("5: List all subordinates information of a selected contact\n");
            printf("6: List all contacts that have more than 2 subordinates and a secretary\n");
            printf("7: List all companies and the number of contacts associated with them\n");
            printf("8: List all contacts with greater than 3 interaction events\n");
            printf("9: List total number of phone call events, total number of email events, and total number of mail events\n");
            printf("10: List all contacts with home address in selected city\n");
            printf("0: Exit\n");
            printf("> ");
            int choice;
            int leave = 1;
            scanf("%d", &choice);

            switch(choice) {
                    case 0:
                            leave = 0;
                            break;
                    case 1:
                            printf("Please type wanted contact ID: ");
                            char contchoice[20];
                            scanf("%s", &contchoice);

                            EXEC SQL DECLARE case1 CURSOR FOR
                                    SELECT intDate, intType, comments
                                    FROM InteractionEvents
                                    WHERE contact = :contchoice;

                            EXEC SQL OPEN case1;

                            printf("\n\nAll Interaction Events from %s--\n\n", contchoice);
                            printf("Interaction_Date  Interaction_Type  Comments\n");
                            printf("----------------  ----------------  --------\n");

                            EXEC SQL WHENEVER NOT FOUND DO break;
                            for (;;) {
                                    EXEC SQL FETCH case1 INTO :q1_rec_ptr;
                                    printf("%s %s %s\n", q1_rec_ptr->date, q1_rec_ptr->intType, q1_rec_ptr->comments);
                            }
                            EXEC SQL CLOSE case1;
                            printf("\n");

                            break;
                    case 2:
                            printf("When typing the month portion (MMM) please type the first three letters of the month\n");
                            printf("Example: Want Januray 01, 2002 . . . type 01-jan-02 OR 01-JAN-02\n");
                            printf("Please type the start of the wanted time period (format = DD-MMM-YY): ");
                            char time1choice[11];
                            scanf("%s", &time1choice);
                            printf("Please type the end of the wanted time period (format = DD-MMM-YY): ");
                            char time2choice[11];
                            scanf("%s", &time2choice);

                            EXEC SQL DECLARE case2 CURSOR FOR
                                    SELECT contact, intDate, intType, comments
                                    FROM InteractionEvents
                                    WHERE intDate BETWEEN :time1choice AND :time2choice;

                            EXEC SQL OPEN case2;

                            printf("\n\nDate given is in same format as the inputted date (DD-MMM-YY)\n");
                            printf("Interaction Events Made Between %s to %s--\n\n", time1choice, time2choice);
                            printf("Contact_ID  Date  Interaction_Type  Comments\n");
                            printf("----------  ----  ----------------  --------\n");

                            EXEC SQL WHENEVER NOT FOUND DO break;
                            for (;;) {
                                    EXEC SQL FETCH case2 INTO :q2_rec_ptr;
                                    printf("%s %s %s %s\n", q2_rec_ptr->contId, q2_rec_ptr->date, q2_rec_ptr->intType, q2_rec_ptr->comments);
                            }
                            EXEC SQL CLOSE case2;
                            printf("\n");

                            break;
                    case 3:
                            printf("Please type wanted company name: ");
                            char compchoice[20];
                            scanf("%s", &compchoice);

                            EXEC SQL DECLARE case3 CURSOR FOR
                                    SELECT id, Fname, Lname, gender, jobtitle, team, homeAdd, mailAdd, comments
                                    FROM Contacts
                                    WHERE employer = :compchoice;

                            EXEC SQL OPEN case3;

                            printf("\n\nAll Contacts within Company %s--\n\n", compchoice);
                            printf("Contact_ID  First_name  Last_name  Gender  Jobtitle  Team  Home_Address  Mail_Address  Comments\n");
                            printf("----------  ----------  ---------  ------  --------  ----  ------------  ------------  --------\n");

                            EXEC SQL WHENEVER NOT FOUND DO break;
                            for (;;) {
                                    EXEC SQL FETCH case3 INTO :q3_rec_ptr;
                                    printf("%s %s %s %s %s %s %s %s %s\n", q3_rec_ptr->contId, q3_rec_ptr->fname, q3_rec_ptr->lname, 
                                            q3_rec_ptr->gender, q3_rec_ptr->jobtitle, q3_rec_ptr->team, q3_rec_ptr->homeAdd, 
                                            q3_rec_ptr->mailAdd, q3_rec_ptr->comments);
                            }
                            EXEC SQL CLOSE case3;
                            printf("\n");

                            break;
                    case 4:
                            printf("When typing the month portion (MMM) please type the first three letters of the month\n");
                            printf("Example: Want Januray 01, 2002 . . . type 01-jan-02 OR 01-JAN-02\n");
                            printf("Please type the start of the wanted time period (format = DD-MMM-YYYY): ");
                            char time01choice[11];
                            scanf("%s", &time01choice);
                            printf("Please type the end of the wanted time period (format = DD-MMM-YYYY): ");
                            char time02choice[11];
                            scanf("%s", &time02choice);

                            EXEC SQL DECLARE case4 CURSOR FOR
                                    SELECT COUNT(intType)
                                    FROM InteractionEvents
                                    WHERE (intType = 'Call') AND
                                          intDate BETWEEN :time01choice AND :time02choice;

                            EXEC SQL OPEN case4;

                            printf("\n\nNumber of Calls Made between %s to %s--\n\n", time01choice, time02choice);
                            printf("Number_of_Calls\n");
                            printf("---------------\n");

                            EXEC SQL WHENEVER NOT FOUND DO break;
                            for (;;) {
                                    EXEC SQL FETCH case4 INTO :q4_rec_ptr;
                                    printf("%d\n", q4_rec_ptr->count);
                            }
                            EXEC SQL CLOSE case4;
                            printf("\n");

                            break;
                    case 5:
                            printf("Please type wanted contact: ");
                            char contchoice2[20];
                            scanf("%s", &contchoice2);

                            EXEC SQL DECLARE case5 CURSOR FOR
                                SELECT DISTINCT id, Fname, Lname, jobtitle, officeNum, email
                                FROM Contacts, Communication, Manager
                                WHERE (id <> :contchoice2) AND
                                      (id = commId) AND
                                      (team = (SELECT team
                                               FROM Contacts
                                               WHERE (id = :contchoice2) AND
                                                     (jobtitle IN ('Manager', 'Supervisor'))
                                              )
                                      OR (id = secretary) AND
                                         (manId = :contchoice2));

                            EXEC SQL OPEN case5;

                            printf("\n\nAll Subordinates of contact %s--\n\n", contchoice2);
                            printf("Contact_ID  Contact_First_Name  Contact_Last_Name  Contact_Office_Number  Contact_Email\n");
                            printf("----------  ------------------  -----------------  ---------------------  -------------\n");

                            EXEC SQL WHENEVER NOT FOUND DO break;
                            for(;;) {
                                EXEC SQL FETCH case5 INTO :q5_rec_ptr;
                                printf("%s %s %s %s %s %s\n", q5_rec_ptr->contId, q5_rec_ptr->fname, q5_rec_ptr->lname, q5_rec_ptr->jobtitle, q5_rec_ptr->officeNum, q5_rec_ptr->email);
                            }
                            EXEC SQL CLOSE case5;
                            printf("\n");

                            break;
                    case 6:
                            EXEC SQL DECLARE case6 CURSOR FOR
                                SELECT DISTINCT id, Fname, Lname
                                FROM Department, Contacts, Manager
                                WHERE (jobtitle = 'Manager' OR jobtitle = 'Supervisor') AND
                                      (deptSize > 2) AND
                                      secretary <> 'N/A';

                            EXEC SQL OPEN case6;

                            printf("\n\nAll Contacts with More than 2 Subordiantes and a Secretary--\n\n");
                            printf("Contact_ID  Contact_First_Name  Contact_Last_Name\n");
                            printf("----------  ------------------  -----------------\n");

                            EXEC SQL WHENEVER NOT FOUND DO break;
                            for(;;) {
                                EXEC SQL FETCH case6 INTO :q6_rec_ptr;
                                printf("%s %s %s\n", q6_rec_ptr->manId, q6_rec_ptr->fname, q6_rec_ptr->lname);
                            }
                            EXEC SQL CLOSE case6;
                            printf("\n");

                            break;
                    case 7:
                            EXEC SQL DECLARE case7 CURSOR FOR
                                    SELECT compNa, compSize
                                    FROM Company
                                    ORDER BY compSize DESC;

                            EXEC SQL OPEN case7;

                            printf("\n\nCompany Sizes in Descending Order--\n\n");
                            printf("Company_Name  Company_Size\n");
                            printf("------------  ------------\n");

                            EXEC SQL WHENEVER NOT FOUND DO break;
                            for (;;) {
                                    EXEC SQL FETCH case7 INTO :q7_rec_ptr;
                                    printf("%s %d\n", q7_rec_ptr->compName, q7_rec_ptr->compSize);
                            }
                            EXEC SQL CLOSE case7;
                            printf("\n");

                            break;
                    case 8:
                            EXEC SQL DECLARE case8 CURSOR FOR
                                    SELECT DISTINCT id, Fname, Lname
                                    FROM Contacts, InteractionEvents
                                    WHERE id = contact AND
                                          id IN (SELECT contact
                                                 FROM InteractionEvents
                                                 GROUP BY contact
                                                 HAVING COUNT(contact) > 3);

                            EXEC SQL OPEN case8;

                            printf("\n\nAll Contacts with Greater than Three Interaction Events--\n\n");
                            printf("Contact_ID  Contact_First_Name  Contact_Last_Name\n");
                            printf("----------  ------------------  -----------------\n");

                            EXEC SQL WHENEVER NOT FOUND DO break;
                            for (;;) {
                                    EXEC SQL FETCH case8 INTO :q8_rec_ptr;
                                    printf("%s %s %s\n", q8_rec_ptr->contId, q8_rec_ptr->fname, q8_rec_ptr->lname);
                            }
                            EXEC SQL CLOSE case8;
                            printf("\n");

                            break;
                    case 9:
                            EXEC SQL DECLARE case9 CURSOR FOR
                                    SELECT COUNT(DECODE (intType, 'Call', 1)),
                                           COUNT(DECODE (intType, 'Email', 1)),
                                           COUNT(DECODE (intType, 'Mail', 1))
                                    FROM InteractionEvents;

                            EXEC SQL OPEN case9;

                            printf("\n\nTotal Number of Phone Calls, Total Emails, and Total Mail Events--\n\n");
                            printf("Phone_Calls  Emails  Mail\n");
                            printf("-----------  ------  ----\n");

                            EXEC SQL WHENEVER NOT FOUND DO break;
                            for (;;) {
                                    EXEC SQL FETCH case9 INTO :q9_rec_ptr;
                                    printf("%d %d %d\n", q9_rec_ptr->callAmount, q9_rec_ptr->emailAmount, q9_rec_ptr->mailAmount);
                            }
                            EXEC SQL CLOSE case9;
                            printf("\n");      

                            break;
                    case 10:
                            printf("When typing input please put the percent sign (%) both in the front and end of the desired city\n");
                            printf("Please type wanted city: ");
                            char citychoice[20];
                            scanf("%s", &citychoice);

                            EXEC SQL DECLARE case10 CURSOR FOR
                                    SELECT id, Fname, Lname
                                    FROM Contacts
                                    WHERE homeAdd LIKE :citychoice;

                            EXEC SQL OPEN case10;

                            printf("\n\nContacts that live in city %s--\n\n", citychoice);
                            printf("Contact_ID  Contact_First_Name  Contact_Last_Name\n");
                            printf("----------  ------------------  ----------------\n");

                            EXEC SQL WHENEVER NOT FOUND DO break;
                            for (;;) {
                                    EXEC SQL FETCH case10 INTO :q10_rec_ptr;
                                    printf("%s %s %s\n", q10_rec_ptr->contId, q10_rec_ptr->fname, q10_rec_ptr->lname);
                            }
                            EXEC SQL CLOSE case10;
                            printf("\n");

                            break;
                    default:
                            printf("Invalid choice given. Please try again\n");
                            break;
            }
            if(leave == 0)
                    break;
    }

    printf("\nGOOD-BYE!!\n\n");

    EXEC SQL COMMIT WORK RELEASE;
    exit(EXIT_SUCCESS);
}
